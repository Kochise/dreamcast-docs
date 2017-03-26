/* KallistiOS ##version##

   kernel/net/net_input.c
   Copyright (C) 2002 Dan Potter
   Copyright (C) 2005 Lawrence Sebald
*/

#include <stdio.h>
#include <kos/net.h>
#include <arpa/inet.h>
#include "net_ipv4.h"

CVSID("$Id: net_input.c,v 1.2 2002/03/24 00:27:05 bardtx Exp $");

/*

  Main packet input system
 
*/

static int net_default_input(netif_t *nif, const uint8 *data, int len) {
	uint16 *proto = (uint16 *)(data + 12);

	switch(ntohs(*proto)) {
		case 0x0800:
			return net_ipv4_input(nif, data + sizeof(eth_hdr_t),
                                  len - sizeof(eth_hdr_t));
		case 0x0806:
			return net_arp_input(nif, data, len);
		default:
			dbglog(DBG_KDEBUG, "net_input: unhandled ethernet "
			       "protocol: %x\n", ntohs(*proto));
			return 0;
	}
}

/* Where will input packets be routed? */
net_input_func net_input_target = net_default_input;

/* Process an incoming packet */
int net_input(netif_t *device, const uint8 *data, int len) {
	if (net_input_target != NULL)
		return net_input_target(device, data, len);
	else
		return 0;
}

/* Setup an input target; returns the old target */
net_input_func net_input_set_target(net_input_func t) {
	net_input_func old = net_input_target;
	net_input_target = t;
	return old;
}
