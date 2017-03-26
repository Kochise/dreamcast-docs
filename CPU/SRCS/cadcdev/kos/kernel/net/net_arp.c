/* KallistiOS ##version##

   kernel/net/net_arp.c

   Copyright (C) 2002 Dan Potter
   Copyright (C) 2005 Lawrence Sebald
*/

#include <string.h>
#include <malloc.h>
#include <stdio.h>
#include <kos/net.h>
#include <kos/thread.h>
#include "net_ipv4.h"

CVSID("$Id: net_arp.c,v 1.1 2002/01/30 06:54:27 bardtx Exp $");

/*

  ARP handling system
 
*/

/* ARP Packet Structre */
#define packed __attribute__((packed))
typedef struct {
	uint8 hw_type[2]    packed;
	uint8 pr_type[2]    packed;
	uint8 hw_size       packed;
	uint8 pr_size       packed;
	uint8 opcode[2]     packed;
	uint8 hw_send[6]    packed;
	uint8 pr_send[4]    packed;
	uint8 hw_recv[6]    packed;
	uint8 pr_recv[6]    packed;
} arp_pkt_t;
#undef packed

/**************************************************************************/
/* Variables */

/* ARP cache */        
struct netarp_list net_arp_cache;

/**************************************************************************/
/* Cache management */

/* Garbage collect timed out entries */
int net_arp_gc() {
	netarp_t *a1, *a2;

	a1 = LIST_FIRST(&net_arp_cache);
	while (a1 != NULL) {
		a2 = LIST_NEXT(a1, ac_list);
		if (a1->timestamp && jiffies >= (a1->timestamp + 600*HZ)) {
			LIST_REMOVE(a1, ac_list);
			free(a1);
		}
		a1 = a2;
	}

	return 0;
}

/* Add an entry to the ARP cache manually */
int net_arp_insert(netif_t *nif, uint8 mac[6], uint8 ip[4], uint32 timestamp) {
	netarp_t *cur;
	
	/* First make sure the entry isn't already there */
	LIST_FOREACH(cur, &net_arp_cache, ac_list) {
		if (!memcmp(ip, cur->ip, 4)) {
			memcpy(cur->mac, mac, 6);
			cur->timestamp = timestamp;
			return 0;
		}
	}

	/* It's not there, add an entry */
	cur = (netarp_t *)malloc(sizeof(netarp_t));
	memcpy(cur->mac, mac, 6);
	memcpy(cur->ip, ip, 4);
	cur->timestamp = timestamp;
	LIST_INSERT_HEAD(&net_arp_cache, cur, ac_list);

	/* Garbage collect expired entries */
	net_arp_gc();

	return 0;
}

/* Look up an entry from the ARP cache; if no entry is found, then an ARP
   query will be sent and an error will be returned. Thus your packet send
   should also fail. Later when the transmit retries, hopefully the answer
   will have arrived. */
int net_arp_lookup(netif_t *nif, uint8 ip_in[4], uint8 mac_out[6]) {
	netarp_t *cur;

	/* Garbage collect expired entries */
	net_arp_gc();

	/* Look for the entry */
	LIST_FOREACH(cur, &net_arp_cache, ac_list) {
		if (!memcmp(ip_in, cur->ip, 4)) {
			if(cur->mac[0] == 0 && cur->mac[1] == 0 && 
			   cur->mac[2] == 0 && cur->mac[3] == 0 &&
			   cur->mac[4] == 0 && cur->mac[5] == 0) {
				return -1;
			}

			memcpy(mac_out, cur->mac, 6);
			if (cur->timestamp != 0)
				cur->timestamp = jiffies;
			return 0;
		}
	}

	/* It's not there... Add an incomplete ARP entry */
	memset(mac_out, 0, 6);
	net_arp_insert(nif, mac_out, ip_in, jiffies);
	
	/* Generate an ARP who-has packet */
	net_arp_query(nif, ip_in);

	/* Return failure */
	return -1;
}

/* Do a reverse ARP lookup: look for an IP for a given mac address; note
   that if this fails, you have no recourse. */
int net_arp_revlookup(netif_t *nif, uint8 ip_out[4], uint8 mac_in[6]) {
	netarp_t *cur;

	/* Look for the entry */
	LIST_FOREACH(cur, &net_arp_cache, ac_list) {
		if (!memcmp(mac_in, cur->mac, 6)) {
			memcpy(ip_out, cur->ip, 4);
			if (cur->timestamp != 0)
				cur->timestamp = jiffies;
			return 0;
		}
	}

	return -1;
}

/* Send an ARP reply packet on the specified network adapter */
static int net_arp_send(netif_t *nif, arp_pkt_t *pkt)	{
	arp_pkt_t pkt_out;
	eth_hdr_t eth_hdr;
	uint8 buf[sizeof(arp_pkt_t) + sizeof(eth_hdr_t)];

	/* First, fill in the ARP packet. */
	pkt_out.hw_type[0] = 0;
	pkt_out.hw_type[1] = 1;
	pkt_out.pr_type[0] = 0x08;
	pkt_out.pr_type[1] = 0x00;
	pkt_out.hw_size = 6;
	pkt_out.pr_size = 4;
	pkt_out.opcode[0] = 0;
	pkt_out.opcode[1] = 2;
	memcpy(pkt_out.hw_send, nif->mac_addr, 6);
	memcpy(pkt_out.pr_send, nif->ip_addr, 4);
	memcpy(pkt_out.pr_recv, pkt->pr_send, 4);
	memcpy(pkt_out.hw_recv, pkt->hw_send, 6);

	/* Fill in the ethernet header. */
	memcpy(eth_hdr.src, nif->mac_addr, 6);
	memcpy(eth_hdr.dest, pkt->hw_send, 6);
	eth_hdr.type[0] = 0x08; /* ARP */
	eth_hdr.type[1] = 0x06;

	memcpy(buf, &eth_hdr, sizeof(eth_hdr_t));
	memcpy(buf + sizeof(eth_hdr_t), &pkt_out, sizeof(arp_pkt_t));

	/* Send it away */
	nif->if_tx(nif, buf, sizeof(eth_hdr_t) + sizeof(arp_pkt_t), NETIF_BLOCK);
	
	return 0;
}
            
/* Receive an ARP packet and process it (called by net_input) */
int net_arp_input(netif_t *nif, const uint8 *pkt_in, int len) {
	eth_hdr_t *eth_hdr;
	arp_pkt_t *pkt;

	eth_hdr = (eth_hdr_t *)pkt_in;
	pkt = (arp_pkt_t *)(pkt_in + sizeof(eth_hdr_t));

	switch(pkt->opcode[1]) {
		case 1: /* ARP Request */
			net_arp_send(nif, pkt);
		case 2: /* ARP Reply */
			/* Insert into ARP cache */
			net_arp_insert(nif, pkt->hw_send, pkt->pr_send, jiffies);
			break;
		default:
			dbglog(DBG_KDEBUG, "net_arp: Unknown ARP Opcode: %d\n", pkt->opcode[1]);
	}

	return 0;
}

/* Generate an ARP who-has query on the given device */
int net_arp_query(netif_t *nif, uint8 ip[4]) {
	arp_pkt_t pkt_out;
	eth_hdr_t eth_hdr;
	uint8 buf[sizeof(arp_pkt_t) + sizeof(eth_hdr_t)];

	/* First, fill in the ARP packet. */
	pkt_out.hw_type[0] = 0;
	pkt_out.hw_type[1] = 1;
	pkt_out.pr_type[0] = 0x08;
	pkt_out.pr_type[1] = 0x00;
	pkt_out.hw_size = 6;
	pkt_out.pr_size = 4;
	pkt_out.opcode[0] = 0;
	pkt_out.opcode[1] = 1;
	memcpy(pkt_out.hw_send, nif->mac_addr, 6);
	memcpy(pkt_out.pr_send, nif->ip_addr, 4);
	memcpy(pkt_out.pr_recv, ip, 4);
	pkt_out.hw_recv[0] = 0xFF; /* Ethernet broadcast address */
	pkt_out.hw_recv[1] = 0xFF;
	pkt_out.hw_recv[2] = 0xFF;
	pkt_out.hw_recv[3] = 0xFF;
	pkt_out.hw_recv[4] = 0xFF;
	pkt_out.hw_recv[5] = 0xFF;

	/* Fill in the ethernet header. */
	memcpy(eth_hdr.src, nif->mac_addr, 6);
	eth_hdr.dest[0] = 0xFF; /* Ethernet broadcast address */
	eth_hdr.dest[1] = 0xFF;
	eth_hdr.dest[2] = 0xFF;
	eth_hdr.dest[3] = 0xFF;
	eth_hdr.dest[4] = 0xFF;
	eth_hdr.dest[5] = 0xFF;
	eth_hdr.type[0] = 0x08; /* ARP */
	eth_hdr.type[1] = 0x06;

	memcpy(buf, &eth_hdr, sizeof(eth_hdr_t));
	memcpy(buf + sizeof(eth_hdr_t), &pkt_out, sizeof(arp_pkt_t));

	/* Send it away */
	nif->if_tx(nif, buf, sizeof(eth_hdr_t) + sizeof(arp_pkt_t), NETIF_BLOCK);
	
	return 0;
}

/*****************************************************************************/
/* Init/shutdown */

/* Init */
int net_arp_init() {
	/* Initialize the ARP cache */
	LIST_INIT(&net_arp_cache);

	return 0;
}

/* Shutdown */
void net_arp_shutdown() {
	/* Free all ARP entries */
	netarp_t *a1, *a2;

	a1 = LIST_FIRST(&net_arp_cache);
	while (a1 != NULL) {
		a2 = LIST_NEXT(a1, ac_list);
		free(a1);
		a1 = a2;
	}

	LIST_INIT(&net_arp_cache);
}
