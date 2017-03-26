/* KallistiOS ##version##

   include/kos/net.h
   (c)2002 Dan Potter

   $Id: net.h,v 1.7 2003/02/25 07:43:12 bardtx Exp $

*/

#ifndef __KOS_NET_H
#define __KOS_NET_H

#include <sys/cdefs.h>
__BEGIN_DECLS

#include <arch/types.h>
#include <sys/queue.h>

/* All functions in this header return < 0 on failure, and 0 on success. */



/* Structure describing one usable network device; this is pretty ethernet
   centric, though I suppose you could stuff other things into this system
   like PPP. */
typedef struct knetif {
	/* Device list handle */
	LIST_ENTRY(knetif)		if_list;

	/* Device name ("bba", "la", etc) */
	const char 			*name;

	/* Long description of the device */
	const char			*descr;

	/* Unit index (starts at zero and counts upwards for multiple
	   network devices of the same type) */
	int				index;

	/* Internal device ID (for whatever the driver wants) */
	uint32				dev_id;

	/* Interface flags */
	uint32				flags;

	/* The device's MAC address */
	uint8				mac_addr[6];

	/* The device's IP address (if any) */
	uint8				ip_addr[4];

	/* All of the following callback functions should return a negative
	   value on failure, and a zero or positive value on success. Some
	   functions have special values, as noted. */

	/* Attempt to detect the device */
	int (*if_detect)(struct knetif * self);

	/* Initialize the device */
	int (*if_init)(struct knetif * self);

	/* Shutdown the device */
	int (*if_shutdown)(struct knetif * self);

	/* Start the device (after init or stop) */
	int (*if_start)(struct knetif * self);

	/* Stop (hibernate) the device */
	int (*if_stop)(struct knetif * self);

	/* Queue a packet for transmission; see special return values
	   below the structure */
	int (*if_tx)(struct knetif * self, const uint8 * data, int len, int blocking);

	/* Commit any queued output packets */
	int (*if_tx_commit)(struct knetif * self);

	/* Poll for queued receive packets, if neccessary */
	int (*if_rx_poll)(struct knetif * self);

	/* Set flags; you should generally manipulate flags through here so that
	   the driver gets a chance to act on the info. */
	int (*if_set_flags)(struct knetif * self, uint32 flags_and, uint32 flags_or);
} netif_t;

/* Flags for netif_t */
#define NETIF_NO_FLAGS		0x00000000
#define NETIF_REGISTERED	0x00000001		/* Is it registered? */
#define NETIF_DETECTED		0x00000002		/* Is it detected? */
#define NETIF_INITIALIZED	0x00000004		/* Has it been initialized? */
#define NETIF_RUNNING		0x00000008		/* Has start() been called? */
#define NETIF_PROMISC		0x00010000		/* Promiscuous mode */
#define NETIF_NEEDSPOLL		0x01000000		/* Needs to be polled for input */

/* Return types for if_tx */
#define NETIF_TX_OK		0
#define NETIF_TX_ERROR		-1
#define NETIF_TX_AGAIN		-2

/* Blocking types */
#define NETIF_NOBLOCK		0
#define NETIF_BLOCK		1


/* Define the list type */
LIST_HEAD(netif_list, knetif);


/* Structure describing an ARP entry; each entry contains a MAC address,
   an IP address, and a timestamp from 'jiffies'. The timestamp allows
   aging and eventual removal. */
typedef struct netarp {
	/* ARP cache list handle */
	LIST_ENTRY(netarp)		ac_list;

	/* Mac address */
	uint8				mac[6];

	/* Associated IP address */
	uint8				ip[4];

	/* Cache entry time; if zero, this entry won't expire */
	uint32				timestamp;
} netarp_t;

/* Define the list type */
LIST_HEAD(netarp_list, netarp);

/***** net_arp.c **********************************************************/

/* ARP cache */
extern struct netarp_list net_arp_cache;


/* Init */
int net_arp_init();

/* Shutdown */
void net_arp_shutdown();

/* Garbage collect timed out entries */
int net_arp_gc();

/* Add an entry to the ARP cache manually */
int net_arp_insert(netif_t *nif, uint8 mac[6], uint8 ip[4], uint32 timestamp);

/* Look up an entry from the ARP cache; if no entry is found, then an ARP
   query will be sent and an error will be returned. Thus your packet send
   should also fail. Later when the transmit retries, hopefully the answer
   will have arrived. */
int net_arp_lookup(netif_t *nif, uint8 ip_in[4], uint8 mac_out[6]);

/* Do a reverse ARP lookup: look for an IP for a given mac address; note
   that if this fails, you have no recourse. */
int net_arp_revlookup(netif_t *nif, uint8 ip_out[4], uint8 mac_in[6]);

/* Receive an ARP packet and process it (called by net_input) */
int net_arp_input(netif_t *nif, const uint8 *pkt, int len);

/* Generate an ARP who-has query on the given device */
int net_arp_query(netif_t *nif, uint8 ip[4]);


/***** net_input.c *********************************************************/

/* Type of net input callback */
typedef int (*net_input_func)(netif_t *, const uint8 *, int);

/* Where will input packets be routed? */
extern net_input_func net_input_target;

/* Device drivers should call this function to submit packets received
   in the background; this function may or may not return immidiately
   but it won't take an infinitely long time (so it's safe to call inside
   interrupt handlers, etc) */
int net_input(netif_t *device, const uint8 *data, int len);

/* Setup an input target; returns the old target */
net_input_func net_input_set_target(net_input_func t);

/***** net_core.c *********************************************************/

/* Interface list; note: do not manipulate directly */
extern struct netif_list net_if_list;

/* Register a network device */
int net_reg_device(netif_t *device);

/* Unregister a network device */
int net_unreg_device(netif_t *device);


/* Init */
int net_init();

/* Shutdown */
void net_shutdown();

__END_DECLS

#endif	/* __KOS_NET_H */

