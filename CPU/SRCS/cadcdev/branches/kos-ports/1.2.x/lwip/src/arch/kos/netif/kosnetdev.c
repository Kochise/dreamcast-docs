/* KallistiOS ##version##

   kosnetdev.c
   (c)2002 Dan Potter

   KOS NetCore interface
   Based loosely on Adam Dunkels' tunif.c and cs8900if.c

*/

#include <string.h>
#include <sys/queue.h>
#include <kos/net.h>
#include <lwip/lwip.h>      

#include "netif/arp.h"

/* Our interface name */
#define IFNAME0 'n'
#define IFNAME1 '0'

static const struct eth_addr ethbroadcast = {{0xff,0xff,0xff,0xff,0xff,0xff}};

/* #define DEBUG_DEATH */

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

/*-----------------------------------------------------------------------------------*/
/*
 * low_level_output():
 *
 * Should do the actual transmission of the packet. The packet is
 * contained in the pbuf that is passed to the function. This pbuf
 * might be chained.
 *
 */
/*-----------------------------------------------------------------------------------*/
static err_t
low_level_output(netif_t *netif, struct pbuf *p) {
	struct pbuf	*q;
	uint8		buf[1600];
	int		len;

	len = 0;
	for(q = p; q != NULL; q = q->next) {
	    if (q == p) {
		memcpy(buf + len, q->payload+2, q->len-2);
		len += q->len-2;
	    } else {
		memcpy(buf + len, q->payload, q->len);
		len += q->len;
	}
	}
	assert( len <= 1500 );

#ifdef DEBUG_DEATH
	printf("low_level_output: copied %d bytes from a pbuf at %08lx\n",
		len, (uint32)p);
	dump_hex(buf, len);
#endif

	netif->if_tx(netif, buf, len, NETIF_BLOCK);
	netif->if_tx_commit(netif);
	
	return ERR_OK;
}

/*-----------------------------------------------------------------------------------*/
/*
 * low_level_input():
 *
 * Should allocate a pbuf and transfer the bytes of the incoming
 * packet from the interface into the pbuf.
 *
 */
/*-----------------------------------------------------------------------------------*/
static struct pbuf *
low_level_input(netif_t *netif, const uint8 * pkt, int len) {
	struct pbuf	*p, *q;

	/* We allocate a pbuf chain of pbufs from the pool. */
	p = pbuf_alloc(PBUF_LINK, len+2, PBUF_POOL);
	/* printf("low_level_input: copied %d bytes into pbuf at %08lx\n",
		len, (uint32)p); */
  
	if (p != NULL) {
		/* We iterate over the pbuf chain until we have read the entire
		   packet into the pbuf. */
		for(q = p; q != NULL; q = q->next) {
			/* Read enough bytes to fill this pbuf in the chain. The
			   avaliable data in the pbuf is given by the q->len
			   variable. */
		    if (q == p) {
			memcpy(q->payload+2, pkt, q->len-2);
			pkt += q->len-2;
		    } else {
			memcpy(q->payload, pkt, q->len);
			pkt += q->len;
		}
		}
	} else {
		/* drop packet(); */
	}

	return p;  
}

/*-----------------------------------------------------------------------------------*/
/*
 * kosnetdev_output():
 *
 * This function is called by the TCP/IP stack when an IP packet
 * should be sent. It calls the function called low_level_output() to
 * do the actuall transmission of the packet.
 *
 */
/*-----------------------------------------------------------------------------------*/
static err_t kosnetdev_output(struct lwipif *netif, struct pbuf *p,  struct ip_addr *ipaddr) {
	struct pbuf	*q;
	struct eth_hdr	*ethhdr;
	struct eth_addr	*dest, mcastaddr;
	struct ip_addr	*queryaddr;
	netif_t		*knetif = (netif_t *)(netif->state);
	err_t		err;
	int		i;
	    
#ifdef DEBUG_DEATH
	dump_pbuf_hex(p);
#endif
	
	/* Make room for Ethernet header. */
	if (pbuf_header(p, PBUF_LINK_HLEN) != 0) {
		/* The pbuf_header() call shouldn't fail, but we allocate an extra
		   pbuf just in case. */
		q = pbuf_alloc(PBUF_LINK, PBUF_LINK_HLEN, PBUF_RAM);
		if (q == NULL) {
			return ERR_MEM;
		}
		pbuf_chain(q, p);
		p = q;
	}

	/* Construct Ethernet header. Start with deciding which
	   MAC address to use as a destination address. Broadcasts and
	   multicasts are special, all other addresses are looked up in the
	   ARP table. */
	queryaddr = ipaddr;
	if (ip_addr_isany(ipaddr) || ip_addr_isbroadcast(ipaddr, &(netif->netmask))) {
		dest = (struct eth_addr *)&ethbroadcast;
	} else if (ip_addr_ismulticast(ipaddr)) {
		assert_msg(0, "No multicast support yet");
	} else {
		if (ip_addr_maskcmp(ipaddr, &(netif->ip_addr), &(netif->netmask))) {
			/* Use destination IP address if the destination is on the same
			   subnet as we are. */
			queryaddr = ipaddr;
		} else {
			/* Otherwise we use the default router as the address to send
			   the Ethernet frame to. */
			queryaddr = &(netif->gw);
		}
		dest = arp_lookup(queryaddr);
	}

	/* If the arp_lookup() didn't find an address, we send out an ARP
	   query for the IP address. */
	if (dest == NULL) {
		q = arp_query(netif, (struct eth_addr *)knetif->mac_addr, queryaddr);
		if (q != NULL) {
		        q->payload-=2;
			q->len+=2;
			err = low_level_output(knetif, q);
                        q->payload+=2;
			q->len-=2;
			pbuf_free(q);
			return err;
		}
		return ERR_MEM;
	}

	ethhdr = p->payload+2;
	for (i=0; i<6; i++) {
		ethhdr->dest.addr[i] = dest->addr[i];
		ethhdr->src.addr[i] = knetif->mac_addr[i];
	}
	ethhdr->type = htons(ETHTYPE_IP);
	
	return low_level_output((netif_t *)netif->state, p);
}

/*-----------------------------------------------------------------------------------*/
/*
 * kosnetdev_input():
 *
 * This function should be called when a packet is ready to be read
 * from the interface. It uses the function low_level_input() that
 * should handle the actual reception of bytes from the network
 * interface.
 *
 */
/*-----------------------------------------------------------------------------------*/
#define PKT_QUEUE_SIZE 16
static struct lwipif 	* kn_lwipif;
static struct pbuf	* pkt_q[PKT_QUEUE_SIZE];
static int 		pkt_q_head, pkt_q_tail, pkt_q_cnt;
static semaphore_t	*wait_p;

static void pkt_enq(struct pbuf *pkt) {
	assert( pkt_q_cnt < PKT_QUEUE_SIZE );
	pkt_q[pkt_q_head] = pkt;
	pkt_q_head = (pkt_q_head + 1) % PKT_QUEUE_SIZE;
	pkt_q_cnt++;
}

static struct pbuf * pkt_deq() {
	struct pbuf *rv;
	
	if (pkt_q_cnt == 0)
		return NULL;

	rv = pkt_q[pkt_q_tail];
	pkt_q_tail = (pkt_q_tail + 1) % PKT_QUEUE_SIZE;
	pkt_q_cnt--;

	return rv;
}

static void kosnetdev_thread(void * blagh) {
	struct eth_hdr *ethhdr;
	struct pbuf *p;
	netif_t *netif;

	for (;;) {
		sem_wait(wait_p);
		p = pkt_deq();
		if (p == NULL) break;

		netif = (netif_t*)kn_lwipif->state;

		ethhdr = p->payload+2;
		switch (htons(ethhdr->type)) {
		case ETHTYPE_IP:
			arp_ip_input(kn_lwipif, p);
			pbuf_header(p, -PBUF_LINK_HLEN);
			kn_lwipif->input(p, kn_lwipif);
			break;
		case ETHTYPE_ARP:
		        p->payload+=2;
			p = arp_arp_input(kn_lwipif, (struct eth_addr *)netif->mac_addr, p);
			if (p != NULL) {
			        p->payload-=2;
				low_level_output(netif, p);
				pbuf_free(p);
			}
			break;
		default:
			pbuf_free(p);
			break;
		}
	}
}

static int kosnetdev_input(netif_t *netif, const uint8 *data, int len) {
	struct pbuf *p;
	int i;

#ifdef DEBUG_DEATH
	dump_hex(data, len);
#endif

	assert( kn_lwipif != NULL );

	/* Can we accept it yet? */
	if (pkt_q_cnt >= PKT_QUEUE_SIZE) {
		dbglog(DBG_ERROR, "kosnetdev_input: lagging\n");
		return 0;
	}

	p = low_level_input(netif, data, len);

	if (p == NULL) {
		dbglog(DBG_ERROR, "kosnetdev_input: low_level_input returned NULL\n");
		return 0;
	}

	pkt_enq(p);
	sem_signal(wait_p);

	return 0;
}

void kosnetdev_init(struct lwipif *netif) {
	kn_lwipif = netif;

	netif->state = NULL;		/* We'll want this to be a ptr to netif_t later */
	netif->name[0] = IFNAME0;
	netif->name[1] = IFNAME1;
	netif->output = kosnetdev_output;

	net_input_set_target(kosnetdev_input);

	arp_init();

	wait_p = sem_create(0);
	pkt_q_head = pkt_q_tail = pkt_q_cnt = 0;
	sys_thread_new(kosnetdev_thread, NULL);
}

void kosnetdev_set_netif(struct lwipif *lw, netif_t *netif) {
	lw->state = netif;
	memcpy(lw->hwaddr, netif->mac_addr, 6);
}

