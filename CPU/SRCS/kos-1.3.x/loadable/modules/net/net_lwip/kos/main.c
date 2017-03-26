/* KallistiOS ##version##

   lwip/main.c
   Copyright (C)2003 Dan Potter
*/

#include <stdio.h>
#include "lwip/lwip.h"

static void callback(void *foo) {
	printf("tcpip: init completed\n");
	sem_signal((semaphore_t *)foo);
}

int lwip_init_all_static(struct ip_addr * i_ipaddr, struct ip_addr * i_netmask, struct ip_addr * i_gw) {
	struct ip_addr  ipaddr, netmask, gw;
	semaphore_t * sem;

	sys_init();
	stats_init();
	mem_init();
	memp_init();
	pbuf_init();
	netif_init();

	ip_init();
	udp_init();
	tcp_init();

	/* sem = sem_create(0);

	tcpip_init(callback, sem);
	sem_wait(sem);
	sem_destroy(sem);
	printf("lwip: TCP/IP initialized\n"); */

	kti_init();
	printf("lwip: KOS TCP/IP Sockets initialized\n");

	IP4_ADDR(&gw, 127,0,0,1);
	IP4_ADDR(&ipaddr, 127,0,0,1);
	IP4_ADDR(&netmask, 255,0,0,0);
	netif_add(&ipaddr, &netmask, &gw, NULL, loopif_init, ip_input);
	netif_set_default(netif_add(i_ipaddr, i_netmask, i_gw, NULL, kosnetif_init, ip_input));

	// netif_add(&ipaddr, &netmask, &gw, NULL, loopif_init, tcpip_input);
	// netif_set_default(netif_add(i_ipaddr, i_netmask, i_gw, NULL, kosnetif_init, tcpip_input));

	return 0;
}

void lwip_shutdown_all() {
	kosnetif_shutdown();
}
