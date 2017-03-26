/* KallistiOS ##version##

   netif/kosnetif.c
   Copyright (C)2003 Dan Potter

   Couple of pieces based on the Xilinx driver:
   Copyright (C) 2001-2003 Swedish Institute of Computer Science
      (Adam Dunkels <adam@sics.se>)
   Copyright (C) 2001, 2002 Xilinx, Inc.
      (Chris Borrelli <chris.borrelli@xilinx.com>)
*/

#include <kos/net.h>
#include <kos/thread.h>
#include <kos/sem.h>
#include <arch/timer.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#include "lwip/debug.h"
#include "lwip/opt.h"
#include "lwip/def.h"
#include "lwip/mem.h"
#include "lwip/pbuf.h"
#include "lwip/stats.h"
#include "lwip/sys.h"
#include "lwip/netif.h"
#include "netif/etharp.h"
#include "netif/kosnetif.h"

/* Network interface name */
#define IFNAME0 'k'
#define IFNAME1 'n'

/* We only ever have one of each of these. Maybe if we port to a device
   that has multiple network interfaces later, we can adapt this. */
static struct netif * netif = NULL;
static netif_t * kif = NULL;

/* The old network input function */
static net_input_func oldfunc = NULL;

/* Our ethernet packet queueing thread */
#define ETH_THD_CNT 1
static kthread_t * eth_thd[ETH_THD_CNT] = { NULL };


/************************************************************************/
/* Some debugging fun */

// #define DEBUG_DEATH

#ifdef DEBUG_DEATH
void dump_hex(uint8 * data, int len) {
	int i;

	printf("dumping hex:\n");
	for (i=0; i<len; i++) {
		if (i && !(i % 16))
			printf("\n");
		printf("%02x ", data[i]);
	}
	printf("\n");
}
void dump_pbuf_hex(struct pbuf *p) {
	struct pbuf	*q;
	int		i, o;

	printf("dumping pbuf:\n");
	o = 0;
	for (q=p; q!=NULL; q=q->next) {
		for (i=0; i<q->len; i++, o++) {
			if (o && !(o % 16))
				printf("\n");
			printf("%02x ", ((uint8*)q->payload)[i]);
		}
	}
	printf("\n");
}
#endif

/************************************************************************/
/* Low-level I/O interface */

/* Should do the actual transmission of the packet. The packet is
   contained in the pbuf that is passed to the function. This pbuf
   might be chained. */
static err_t low_level_output(struct netif * nif, struct pbuf *p) {
	struct pbuf	* q;
	uint8		frame_buffer[1600];
	uint8		* frame_ptr;
	int		payload_size = 0, i;

	assert( nif == netif );

	if (!kif)
		return ERR_IF;

	frame_ptr = frame_buffer;

	for (q=p; q; q=q->next) {
		/*
		  Send the data from the pbuf to the interface, one pbuf at a
		  time. The size of the data in each pbuf is kept in the ->len
		  variable.
		*/
		for (i=0; i<q->len; i++) {
			*(frame_ptr++) = (uint8) *(((u8_t *) q->payload) + i);
			payload_size++;
		}
	}

	assert( payload_size <= 1600 );

#ifdef DEBUG_DEATH
	printf("low_level_output: copied %d bytes from a pbuf at %p\n", payload_size, p);
	dump_hex(frame_buffer, payload_size);
#endif

	kif->if_tx(kif, frame_buffer, payload_size, NETIF_BLOCK);

#ifdef LINK_STATS
	lwip_stats.link.xmit++;
#endif /* LINK_STATS */

	return ERR_OK;
}

/* Allocates a pbuf pool and transfers bytes of
   incoming packet from the interface into the pbuf. */
static struct pbuf * low_level_input(const uint8 * pkt, int pktlen) {
	struct pbuf	* p = NULL, *q = NULL;
	int		i;

#ifdef DEBUG_DEATH
	printf("received packet of size %d at %p:\n", pktlen, pkt);
	dump_hex(pkt, pktlen);
#endif

	/* Allocate a pbuf chain of pbufs from the pool. */
	p = pbuf_alloc(PBUF_RAW, pktlen, PBUF_POOL);

	if (p != NULL) {
		/* Iterate over the pbuf chain until we have
		   read the entire packet into the pbuf. */
		for (q=p; q; q=q->next) {
			/* Read enough bytes to fill this pbuf 
			   in the chain.  The available data in 
			   the pbuf is given by the q->len variable. */
			for (i=0; i<q->len; i++) {
				((u8_t *)q->payload)[i] = *(pkt++);
			}
		}

#ifdef LINK_STATS
		lwip_stats.link.recv++;
#endif /* LINK_STATS */      
	} else {
#ifdef LINK_STATS
		lwip_stats.link.memerr++;
		lwip_stats.link.drop++;
#endif /* LINK_STATS */ 
	}
	return p;  
}

/* This function is called by the TCP/IP stack when an IP packet
   should be sent. It calls the function called low_level_output() to
   do the actual transmission of the packet. */
static err_t kosnetif_output(struct netif * nif,
                             struct pbuf *p,
                             struct ip_addr *ipaddr)
{
	assert( nif == netif );

	p = etharp_output(netif, ipaddr, p);

	if (p != NULL) {
		/* send the frame */
		low_level_output(netif, p);
	}
	return ERR_OK;
}

/************************************************************************/
/* Incoming packet queue interface */

/* Max number of queued packets */
#define PKT_QUEUE_SIZE 64

/* Packet queue struct */
typedef struct {
	uint8	pkt[1600];
	int	len;
	uint64	arrival;
} pkt_t;

/* The packet queue itself */
static pkt_t		* pkt_q[PKT_QUEUE_SIZE];
static int		pkt_q_head, pkt_q_tail, pkt_q_cnt;
static semaphore_t	*wait_p; 
static uint64		avgtime = 0;
static int		total_cnt = 0;

/* Init the packet queue */
static void low_input_init() {
	int i;

	for (i=0; i<PKT_QUEUE_SIZE; i++)
		pkt_q[i] = calloc(1, sizeof(pkt_t));

	wait_p = sem_create(0);
	pkt_q_head = pkt_q_tail = pkt_q_cnt = 0;
}

/* Shutdown the packet queue */
static void low_input_shutdown() {
	int i;

	sem_destroy(wait_p);

	for (i=0; i<PKT_QUEUE_SIZE; i++) {
		free(pkt_q[i]);
		pkt_q[i] = NULL;
	}
}

/* Enqueue a "quit" packet */
static void pkt_enq_quit() {
	int old;

	assert( pkt_q_cnt < PKT_QUEUE_SIZE );
	old = irq_disable();
	pkt_q[pkt_q_head]->len = -1;
	pkt_q_head = (pkt_q_head + 1) % PKT_QUEUE_SIZE;
	pkt_q_cnt++;
	irq_restore(old);
}

/* Called from inside the IRQ to post a packet and wake the ethernet
   processing thread. */
static void pkt_enq(const uint8 * pkt, int pktlen) {
	assert( pkt_q_cnt < PKT_QUEUE_SIZE );

	assert( pktlen <= 1600 );
	memcpy(pkt_q[pkt_q_head]->pkt, pkt, pktlen);
	pkt_q[pkt_q_head]->len = pktlen;
	pkt_q[pkt_q_head]->arrival = timer_ms_gettime64();

	pkt_q_head = (pkt_q_head + 1) % PKT_QUEUE_SIZE;
	pkt_q_cnt++;
}

/* Called from the processing thread to grab a new packet. */
static struct pbuf * pkt_deq() {
	int old;
	struct pbuf *rv;
	pkt_t * p;

	if (pkt_q_cnt == 0)
		return NULL;

	/* HACK */
	p = pkt_q[pkt_q_tail];
	if (p->len < 0)
		return (struct pbuf *)1;

	avgtime = (avgtime + (timer_ms_gettime64() - p->arrival)) / 2;
	total_cnt++;
	if (!(total_cnt % 100)) {
		printf("%d packets received, avg latency %lu msec\n", total_cnt, (uint32)avgtime);
	}
	rv = low_level_input(p->pkt, p->len);
	
	pkt_q_tail = (pkt_q_tail + 1) % PKT_QUEUE_SIZE;

	old = irq_disable();
	pkt_q_cnt--;
	irq_restore(old);

	return rv;
}

/* The processing thread. This should ideally run at a better priority than
   other things to lower latency, but we leave it at normal for now to avoid
   lockups on bugs. */
static void kosnetif_thread(void * blegh) {
	struct eth_hdr * ethernet_header;
	struct pbuf *p, *q;
	int i;

	for (;;) {
		// lwIP totally ignores TCP_TMR_INTERVAL and assumes it is 100,
		// so we'll just do our own thing here...
		i = sem_wait_timed(wait_p, 20);
		if (i < 0) {
			tcp_tmr();
			continue;
		}
		// sem_wait(wait_p);
		p = pkt_deq();
		if (p == (struct pbuf *)1) break;
		if (!p) continue;

		ethernet_header = p->payload;

		q = NULL;
		switch (htons(ethernet_header->type)) {
		case ETHTYPE_IP:
			q = etharp_ip_input(netif, p);
			pbuf_header(p, -14);
			netif->input(p, netif);
			break;
		case ETHTYPE_ARP:
			q = etharp_arp_input(netif, (struct eth_addr *)(kif->mac_addr), p);
			break;
		default:
			pbuf_free(p);
			break;
		}
		
		if (q != NULL) {
			low_level_output(netif, q);
			pbuf_free(q);
		}
	}
}

/* Called from the driver IRQ handler */
static int knet_input_low(netif_t * dev, const uint8 * pkt, int pktlen) {
	if (dev != kif)
		return -1;

	if (pkt_q_cnt >= PKT_QUEUE_SIZE) {
		dbglog(DBG_ERROR, "kosnetif_input: lagging\n");
		return 0;
	}

	pkt_enq(pkt, pktlen);
	sem_signal(wait_p);

	return 0;
}

/***************************************************************************/

/* static void etharp_timer_thread(void *arg) {
	sys_sem_t * psem = (sys_sem_t *)psem;

	sys_timeout(ARP_TMR_INTERVAL, (sys_timeout_handler)arp_timer, NULL);
	sys_sem_signal(*psem);
}

static void etharp_timer_init(void *arg) {
	sys_thread_new(etharp_timer_thread, arg, DEFAULT_THREAD_PRIO);
} */

/* Should be called at the beginning of the program to set up the
   network interface. It calls the function low_level_init() to do the
   actual setup of the hardware. */
err_t kosnetif_init(struct netif *netif_ptr) {
	struct netif_list * listhead;
	int i;

	printf("kosnetif: starting init\n");

	// Find a device for us
	listhead = net_get_if_list();
	LIST_FOREACH(kif, listhead, if_list) {
		if (kif->flags & NETIF_RUNNING)
			break;
	}
	if (kif == NULL) {
		printf("can't find an active KOS network device\n");
		return ERR_IF;
	}

	// Set our globals
	netif = netif_ptr;

	// Setup some parameters
	netif_ptr->mtu = 1500;
	netif_ptr->hwaddr_len = 6;
	netif_ptr->hwaddr[0] = kif->mac_addr[0];
	netif_ptr->hwaddr[1] = kif->mac_addr[1];
	netif_ptr->hwaddr[2] = kif->mac_addr[2];
	netif_ptr->hwaddr[3] = kif->mac_addr[3];
	netif_ptr->hwaddr[4] = kif->mac_addr[4];
	netif_ptr->hwaddr[5] = kif->mac_addr[5];
	netif_ptr->name[0] = IFNAME0;
	netif_ptr->name[1] = IFNAME1;
	netif_ptr->output = kosnetif_output;
	netif_ptr->linkoutput = low_level_output;

	low_input_init();
	for (i=0; i<ETH_THD_CNT; i++) {
		eth_thd[i] = thd_create(kosnetif_thread, NULL);
	//	thd_set_prio(eth_thd[i], PRIO_DEFAULT-2);
	}
	oldfunc = net_input_set_target(knet_input_low);

	etharp_init();

	printf("kosnetif: init complete\n");
	return ERR_OK;
}

err_t kosnetif_shutdown() {
	int i;
	
	net_input_set_target(oldfunc);

	printf("kosnetif: waiting for thread to quit\n");
	for (i=0; i<ETH_THD_CNT; i++) {
		pkt_enq_quit();
		sem_signal(wait_p);
	}
	for (i=0; i<ETH_THD_CNT; i++)
		thd_wait(eth_thd[i]);
	low_input_shutdown();

	netif = NULL;
	kif = NULL;

	printf("kosnetif: shut down complete\n");
	return ERR_OK;
}
