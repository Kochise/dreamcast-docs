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

/* Sockets stuff */
#include <lwip/sockets.h>
struct kprocess;
int _lwip_accept(struct kprocess * proc, int s, struct sockaddr *addr, socklen_t *addrlen);
int _lwip_bind(struct kprocess * proc, int s, struct sockaddr *name, socklen_t namelen);
int _lwip_shutdown(struct kprocess * proc, int s, int how);
int _lwip_getpeername (struct kprocess * proc, int s, struct sockaddr *name, socklen_t *namelen);
int _lwip_getsockname (struct kprocess * proc, int s, struct sockaddr *name, socklen_t *namelen);
int _lwip_getsockopt (struct kprocess * proc, int s, int level, int optname, void *optval, socklen_t *optlen);
int _lwip_setsockopt (struct kprocess * proc, int s, int level, int optname, const void *optval, socklen_t optlen);
int _lwip_close(struct kprocess * proc, int s);
int _lwip_connect(struct kprocess * proc, int s, struct sockaddr *name, socklen_t namelen);
int _lwip_listen(struct kprocess * proc, int s, int backlog);
int _lwip_recv(struct kprocess * proc, int s, void *mem, int len, unsigned int flags);
int _lwip_read(struct kprocess * proc, int s, void *mem, int len);
int _lwip_recvfrom(struct kprocess * proc, int s, void *mem, int len, unsigned int flags,
	struct sockaddr *from, socklen_t *fromlen);
int _lwip_send(struct kprocess * proc, int s, const void *dataptr, int size, unsigned int flags);
int _lwip_sendto(struct kprocess * proc, int s, const void *dataptr, int size, unsigned int flags,  
	struct sockaddr *to, socklen_t tolen);
int _lwip_socket(struct kprocess * proc, int domain, int type, int protocol);
int _lwip_write(struct kprocess * proc, int s, const void *dataptr, int size);
int _lwip_select(struct kprocess * proc, int maxfdp1, fd_set *readset, fd_set *writeset, fd_set *exceptset,
	struct timeval *timeout);
int _lwip_ioctl(struct kprocess * proc, int s, long cmd, void *argp);

__END_DECLS

#endif	/* __LWIP_LWIP_H */

