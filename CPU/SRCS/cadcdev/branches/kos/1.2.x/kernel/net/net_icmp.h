/* KallistiOS ##version##

   net_icmp.h
   (c)2002 Dan Potter

   $Id: net_icmp.h,v 1.2 2002/03/24 00:27:05 bardtx Exp $

*/

#ifndef __LOCAL_NET_ICMP_H
#define __LOCAL_NET_ICMP_H

#include <sys/cdefs.h>
__BEGIN_DECLS

#include <kos/net.h>

int net_icmp_input(netif_t *src, uint8 *pkt, int pktsize);

__END_DECLS

#endif	/* __LOCAL_NET_ICMP_H */

