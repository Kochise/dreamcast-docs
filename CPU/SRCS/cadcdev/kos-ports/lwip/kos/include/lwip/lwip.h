/* KallistiOS ##version##

   lwip/lwip.h
   Copyright (C)2002,2003 Dan Potter

   $Id: lwip.h,v 1.4 2003/07/31 00:49:41 bardtx Exp $

   Note that for this to work properly, you will need to add the lwIP
   include paths to your CFLAGS; see addons/lwip/Makefile.

*/

#ifndef __LWIP_LWIP_H
#define __LWIP_LWIP_H

#include <sys/cdefs.h>
__BEGIN_DECLS

#include "lwip/debug.h"
#include <stdlib.h>
#include "lwip/opt.h"
#include "lwip/mem.h"
#include "lwip/memp.h"
#include "lwip/sys.h"
#include "lwip/stats.h"
#include "lwip/tcpip.h"
#include "netif/kosnetif.h"
#include "netif/loopif.h"
#include "lwip/ip_addr.h"
#include "arch/perf.h"
#include "lwip/dhcp.h"
// #include "dcload/dcload-lwip.h"

int lwip_kos_init();
int lwip_kos_shutdown();

/* Initialize lwIP using static IP address info */
int lwip_init_all_static(struct ip_addr * i_ipaddr, struct ip_addr * i_netmask, struct ip_addr * i_gw);

/* Initialize lwIP using DHCP */
int lwip_init_dhcp();

/* Shut down lwIP */
void lwip_shutdown_all();

/* Query about IP info */
int lwip_get_ipaddr(struct ip_addr * out);
int lwip_get_gateway(struct ip_addr * out);
int lwip_get_netmask(struct ip_addr * out);

/* KOS-happy implementations of the socket API, and related stuff. These are
   just the administrative details. For the actual user API, use the
   existing <lwip/sockets.h>. */
void tcp_timer_needed();
int kti_init();

/* Netcfg as read by the lwIP init in lwip_kos_init */
#include <kos/netcfg.h>
extern netcfg_t lwip_netcfg;

/* Sockets stuff */
#include <lwip/sockets.h>
int lwip_accept(int s, struct sockaddr *addr, socklen_t *addrlen);
int lwip_bind(int s, struct sockaddr *name, socklen_t namelen);
int lwip_shutdown(int s, int how);
int lwip_getpeername (int s, struct sockaddr *name, socklen_t *namelen);
int lwip_getsockname (int s, struct sockaddr *name, socklen_t *namelen);
int lwip_getsockopt (int s, int level, int optname, void *optval, socklen_t *optlen);
int lwip_setsockopt (int s, int level, int optname, const void *optval, socklen_t optlen);
int lwip_close(int s);
int lwip_connect(int s, struct sockaddr *name, socklen_t namelen);
int lwip_listen(int s, int backlog);
int lwip_recv(int s, void *mem, int len, unsigned int flags);
int lwip_read(int s, void *mem, int len);
int lwip_recvfrom(int s, void *mem, int len, unsigned int flags,
	struct sockaddr *from, socklen_t *fromlen);
int lwip_send(int s, const void *dataptr, int size, unsigned int flags);
int lwip_sendto(int s, const void *dataptr, int size, unsigned int flags,  
	struct sockaddr *to, socklen_t tolen);
int lwip_socket(int domain, int type, int protocol);
int lwip_write(int s, const void *dataptr, int size);
int lwip_select(int maxfdp1, fd_set *readset, fd_set *writeset, fd_set *exceptset,
	struct timeval *timeout);
int lwip_ioctl(int s, long cmd, void *argp);

// Simple DNS client
int lwip_gethostbyname(const struct sockaddr_in * dnssrv, const char * name, uint8 * ipout);

__END_DECLS

#endif	/* __LWIP_LWIP_H */

