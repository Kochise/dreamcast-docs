/* KallistiOS ##version##

   liblwip.c
   (c)2002 Dan Potter

*/

#include <assert.h>
#include <kos.h>
#include <lwip/lwip.h>

/* Glue code between a KOS program and the rest of lwIP */

CVSID("$Id: liblwip.c,v 1.3 2002/03/28 08:22:40 bardtx Exp $");

/* Semaphore callback */
static void tcpip_init_done(void *arg) {
	sys_sem_t *sem = (sys_sem_t *)arg;
	sys_sem_signal(*sem);
}

/* Detect available interfaces and add each with a static IP */
static void add_all_interfaces_static(struct ip_addr * i_ipaddr, struct ip_addr * i_netmask, struct ip_addr * i_gw) {
	netif_t *n;
	struct lwipif *lwif;

	LIST_FOREACH(n, &net_if_list, if_list) {
		if (n->flags & NETIF_RUNNING) {
			dbglog(DBG_INFO, "lwip_init_static: adding interface '%s'\n", n->descr);
			lwif = netif_add(i_ipaddr, i_netmask, i_gw, kosnetdev_init, tcpip_input);
			netif_set_default(lwif);
			kosnetdev_set_netif(lwif, n);
		} else {
			dbglog(DBG_INFO, "lwip_init_static: skipping interface '%s'\n", n->descr);
		}
	}
}

/* Detect available interfaces and add each with a dynamic IP */
static void add_all_interfaces_dhcp() {
	struct ip_addr	addr;
	netif_t		*n;
	struct lwipif	*lwif;
	struct dhcp_state *client;

	/* All DHCP interfaces will get null IPs for now */
	IP4_ADDR(&addr, 0,0,0,0);
	
	LIST_FOREACH(n, &net_if_list, if_list) {
		if (n->flags & NETIF_RUNNING) {
			/* Add the interface to lwIP */
			dbglog(DBG_INFO, "lwip_init_dhcp: adding interface '%s'\n", n->descr);
			lwif = netif_add(&addr, &addr, &addr, kosnetdev_init, tcpip_input);
			netif_set_default(lwif);
			kosnetdev_set_netif(lwif, n);

			/* Start a DHCP process for it */
			client = dhcp_start(lwif);
		} else {
			dbglog(DBG_INFO, "lwip_init_dhcp: skipping interface '%s'\n", n->descr);
		}
	}
}

/* Init common to both */
static int lwip_init_common(const char * name) {
	int		rv;
	sys_sem_t	sem;
	struct ip_addr	ipaddr, netmask, gw;
	
	/* Check for the proper threading type */
	assert_msg(__kos_init_flags & INIT_THD_PREEMPT, "lwIP cannot be enabled without pre-emptive threads");
	if (!(__kos_init_flags & INIT_THD_PREEMPT))
		return -1;
	
	/* Did we already initialize networking? */
	if (!(__kos_init_flags & INIT_NET)) {
		rv = net_init();
		if (rv < 0) {
			dbglog(DBG_ERROR, "%s: net_init() failed, giving up\n", name);
			return -1;
		}
	}

	/* Initialize all the basic stuff */
	sys_init();
	mem_init();
	memp_init();
	pbuf_init();

	/* Initialize network interfaces */
	netif_init();

	/* Now init TCP/IP and wait for it to finish */
	sem = sys_sem_new(0);
	tcpip_init(tcpip_init_done, &sem);
	sys_sem_wait(sem);
	sys_sem_free(sem);
	dbglog(DBG_INFO, "%s: TCP/IP initialized\n", name);

	/* Setup a loopback address */
	IP4_ADDR(&gw, 127,0,0,1);
	IP4_ADDR(&ipaddr, 127,0,0,1);
	IP4_ADDR(&netmask, 255,0,0,0);
	netif_add(&ipaddr, &netmask, &gw, loopif_init, tcpip_input);

	return 0;
}

/* Initialize lwIP using DHCP */
int lwip_init_dhcp() {
	if (lwip_init_common("lwip_init_dhcp") < 0)
		return -1;

	/* Setup the DHCP client */
	dhcp_init();

	/* Add a timer callback for it */
	sys_timeout(DHCP_COARSE_TIMER_SECS * 1000, (void (*)())dhcp_coarse_tmr, NULL);
	sys_timeout(DHCP_FINE_TIMER_MSECS, (void (*)())dhcp_fine_tmr, NULL);

	/* Setup inet addresses dynamically */
	add_all_interfaces_dhcp();
	
	dbglog(DBG_INFO, "lwip_init_dhcp: Complete (pending DHCP lease)\n");
	
	return -1;
}

/* Initialize lwIP using static IP address info */
int lwip_init_static(struct ip_addr * i_ipaddr, struct ip_addr * i_netmask, struct ip_addr * i_gw) {
	if (lwip_init_common("lwip_init_static") < 0)
		return -1;

	/* Setup inet addresses statically */
	add_all_interfaces_static(i_ipaddr, i_netmask, i_gw);

	dbglog(DBG_INFO, "lwip_init_static: Complete\n");
	
	return 0;
}

/* Shut down lwIP */
void lwip_shutdown() {
}

