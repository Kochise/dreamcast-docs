/* KallistiOS ##version##

   kernel/net/netarp.c
   (c)2002 Dan Potter
*/

#include <string.h>
#include <malloc.h>
#include <stdio.h>
#include <kos/net.h>
#include <kos/thread.h>

CVSID("$Id: net_arp.c,v 1.1 2002/01/30 06:54:27 bardtx Exp $");

/*

  ARP handling system
 
*/

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

	/* Look for the entry */
	LIST_FOREACH(cur, &net_arp_cache, ac_list) {
		if (!memcmp(ip_in, cur->ip, 4)) {
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
            
/* Receive an ARP packet and process it (called by net_input) */
int net_arp_input(netif_t *nif, const uint8 *pkt_in, int len) {
	return -1;
}

/* Generate an ARP who-has query on the given device */
int net_arp_query(netif_t *nif, uint8 ip[4]) {
	return -1;
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
		free(a2);
		a1 = a2;
	}

	LIST_INIT(&net_arp_cache);
}



