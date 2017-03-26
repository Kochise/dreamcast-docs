/* KallistiOS ##version##

   lwip/lwip.h
   (c)2002 Dan Potter

   $Id: lwip.h,v 1.1 2003/02/27 03:46:30 bardtx Exp $

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
#include "netif/kosnetdev.h"
#include "netif/loopif.h"
#include "lwip/ip_addr.h"
#include "arch/perf.h"
#include "lwip/dhcp.h"
// #include "dcload/dcload-lwip.h"

/* Initialize lwIP using static IP address info */
int lwip_init_static(struct ip_addr * i_ipaddr, struct ip_addr * i_netmask, struct ip_addr * i_gw);

/* Initialize lwIP using DHCP */
int lwip_init_dhcp();

/* Shut down lwIP */
void lwip_shutdown();

__END_DECLS

#endif	/* __LWIP_LWIP_H */

