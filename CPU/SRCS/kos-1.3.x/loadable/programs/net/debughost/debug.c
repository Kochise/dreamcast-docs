/* KallistiOS ##version##

   debug.c
   Copyright (C)2003 Dan Potter

   $Id: debug.c,v 1.2 2003/07/31 00:50:53 bardtx Exp $
*/

#include <kos.h>
#include <lwip/lwip.h>
#include "debug.h"

/*

This program implements a debug host. It's not really meant to be used by
a user on the DC target itself, but by a host PC. It reads its config
from the first VMU. If the config isn't present, it will give up.

*/

extern uint8 romdisk[];

static void pstats() {
	struct ip_addr ip, gw, nm;
	struct netif_list * list;
	struct knetif * netif;

	lwip_get_ipaddr(&ip);
	lwip_get_gateway(&gw);
	lwip_get_netmask(&nm);

	list = net_get_if_list();
	netif = LIST_FIRST(list);

	tty_setcol(TTY_YELLOW, TTY_DEFAULT_BG);
	tty_printf("Driver:  %s\n", netif->name);
	tty_printf("IP:      %d.%d.%d.%d\n", ip4_addr1(&ip), ip4_addr2(&ip), ip4_addr3(&ip), ip4_addr4(&ip));
	tty_printf("Gateway: %d.%d.%d.%d\n", ip4_addr1(&gw), ip4_addr2(&gw), ip4_addr3(&gw), ip4_addr4(&gw));
	tty_printf("Netmask: %d.%d.%d.%d\n", ip4_addr1(&nm), ip4_addr2(&nm), ip4_addr3(&nm), ip4_addr4(&nm));
	tty_setcol(TTY_DEFAULT_FG, TTY_DEFAULT_BG);
}

int main(int argc, char **argv) {
	printf("debug beginning\n");

	/* Setup the display */
	vid_init(DEFAULT_VID_MODE, DEFAULT_PIXEL_MODE);

	/* Setup the minimalist TTY for status output */
	fs_romdisk_mount("/debugrd", romdisk);
	fs_chdir("/debugrd");
	tty_init();
	fs_romdisk_unmount("/debugrd");

	/* Print some startup stats */
	pstats();

	/* Change to the root so that all sub-processes will start there */
	fs_chdir("/");

	/* Do that thang */
	net_doloop();

	tty_shutdown();
	printf("debug finished\n");

	return 0;
}


