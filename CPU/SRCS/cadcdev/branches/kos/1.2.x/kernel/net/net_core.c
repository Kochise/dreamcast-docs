/* KallistiOS ##version##

   kernel/net/netcore.c
   (c)2002 Dan Potter
*/

#include <string.h>
#include <malloc.h>
#include <stdio.h>
#include <kos/net.h>

CVSID("$Id: net_core.c,v 1.5 2002/10/26 07:59:50 bardtx Exp $");

/*

This module, and others in this tree, handle the architecture-independent
part of the networking system of KOS. They serve the following purposes:

- Specific network card drivers may register themselves using the functions
  here, if their hardware is present
- Link-level messages will be handled here, such as ARP
- The whole networking system can be enabled or disabled from here
 
*/

/**************************************************************************/
/* Variables */

/* Active network devices list */
struct netif_list net_if_list = LIST_HEAD_INITIALIZER(0);

/* ARP cache */        
struct netarp_list net_arp_cache = LIST_HEAD_INITIALIZER(0);

/**************************************************************************/
/* Driver list management
   Note that this stuff might be used before net_core is actually
   itself initialized. This lets us let the drivers build up the available
   driver list, and then we'll come back later and look through them all. */

/* Register a network device */
int net_reg_device(netif_t *device) {
	/* Make sure it's not already registered */
	if (device->flags & NETIF_REGISTERED) {
		dbglog(DBG_WARNING, "net_reg_device: '%s' is already registered\n",
			device->name);
		return -1;
	}

	/* Insert it into the interface list */
	LIST_INSERT_HEAD(&net_if_list, device, if_list);

	/* Mark it as registered */
	device->flags |= NETIF_REGISTERED;

	/* We need to do more processing in here eventually like looking for
	   duplicate device IDs and assigning new indeces, but that can
	   wait until we're actually supporting a box with the possibility
	   of more than one network interface... which probably won't happen
	   any time soon... */

	/* Success */
	return 0;
}

/* Unregister a network device */
int net_unreg_device(netif_t *device) {
	/* Make sure it really was registered */
	if (!(device->flags & NETIF_REGISTERED)) {
		dbglog(DBG_WARNING, "net_unreg_device: '%s' isn't registered\n",
			device->name);
		return -1;
	}

	/* Remove it from the list */
	LIST_REMOVE(device, if_list);

	/* Mark it as unregistered */
	device->flags &= ~NETIF_REGISTERED;

	/* Success */
	return 0;
}

/*****************************************************************************/
/* Init/shutdown */

/* Device detect / init */
int net_dev_init() {
	int detected = 0;
	netif_t *cur;

	LIST_FOREACH(cur, &net_if_list, if_list) {
		/* Make sure we have one */
		if (cur->if_detect(cur) < 0)
			continue;

		/* Ok, we do -- initialize it */
		if (cur->if_init(cur) < 0)
			continue;

		/* It's initialized, so now enable it */
		if (cur->if_start(cur) < 0) {
			cur->if_shutdown(cur);
			continue;
		}

		detected++;
	}

	dbglog(DBG_DEBUG, "net_dev_init: detected %d usable network device(s)\n", detected);

	return 0;
}

/* Init */
int net_init() {
	/* Detect and potentially initialize devices */
	if (net_dev_init() < 0)
		return -1;
	
	/* Initialize the ARP cache */
	/* net_arp_init(); */

	return 0;
}

/* Shutdown */
void net_shutdown() {
	/* Shut down all activated network devices */
	netif_t *cur;

	LIST_FOREACH(cur, &net_if_list, if_list) {
		if (cur->flags & NETIF_RUNNING && cur->if_stop)
			cur->if_stop(cur);
		if (cur->flags & NETIF_INITIALIZED && cur->if_shutdown)
			cur->if_shutdown(cur);
		cur->flags &= ~NETIF_REGISTERED;
	}

	/* Blank out the list */
	LIST_INIT(&net_if_list);

	/* Shut down the ARP cache */
	/* net_arp_shutdown(); */
}



