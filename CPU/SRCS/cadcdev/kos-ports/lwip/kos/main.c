/* KallistiOS ##version##

   lwip/main.c
   Copyright (C)2003 Dan Potter
*/

#include <stdio.h>
#include "lwip/lwip.h"

//****************************** vvv PPP vvv *********************************//
#include <kos/thread.h>
#include "lwip/ip_addr.h"
#include "lwip/sio.h"
#include "../lwip/src/netif/ppp/ppp.h"

static void callback(void *foo) {
	printf("tcpip: init completed\n");
	sem_signal((semaphore_t *)foo);
}

void ppp_trace(int level, const char *format,...) {
	//char foo[1024];
	va_list ap;

	va_start(ap, format);
	//vsprintf(foo, format, ap);
	va_end(ap);

	//dbgio_printk(foo);
}

void pppLinkStatusCallback(void * ctx, int errCode, void * arg) {
	printf("ppp status callback: errCode = %d\n", errCode);
	if (errCode == PPPERR_NONE) {
		/*struct ppp_addrs *ppp_addrs = arg;

		printf("pppLinkStatusCallback: PPPERR_NONE");
		printf(" our_ipaddr=%s", inet_ntoa(ppp_addrs->our_ipaddr.addr));
		printf(" his_ipaddr=%s", inet_ntoa(ppp_addrs->his_ipaddr.addr));
		printf(" netmask=%s", inet_ntoa(ppp_addrs->netmask.addr));
		printf(" dns1=%s", inet_ntoa(ppp_addrs->dns1.addr));
		printf(" dns2=%s\n", inet_ntoa(ppp_addrs->dns2.addr)); */
	}
}

u32_t sys_jiffies() { return jiffies; }

err_t tcpip_callback(void (*f)(void *ctx), void *ctx) {
	f(ctx);
	return ERR_OK;
}

int lwip_init_all_ppp() {
	sys_init();
	stats_init();
	mem_init();
	memp_init();
	pbuf_init();
	netif_init();

	ip_init();
	udp_init();
	tcp_init();

	pppInit();
	sio_open(0);
	pppOpen(0, pppLinkStatusCallback, NULL);

	return 0;
}
//****************************** ^^^ PPP ^^^ *********************************//

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
