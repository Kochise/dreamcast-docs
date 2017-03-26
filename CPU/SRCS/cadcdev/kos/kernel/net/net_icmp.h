/* KallistiOS ##version##

   kernel/net/net_icmp.h
   Copyright (C) 2002 Dan Potter
   Copyright (C) 2005, 2007 Lawrence Sebald

*/

#ifndef __LOCAL_NET_ICMP_H
#define __LOCAL_NET_ICMP_H

#include <sys/cdefs.h>
__BEGIN_DECLS

#include <kos/net.h>
#include "net_ipv4.h"

#define packed __attribute__((packed))
typedef struct {
	uint8	type		packed;
	uint8	code		packed;
	uint16	checksum	packed;
	uint8	misc[4]		packed;
} icmp_hdr_t;
#undef packed

int net_icmp_input(netif_t *src, ip_hdr_t *ih, const uint8 *data, int size);

__END_DECLS

#endif	/* __LOCAL_NET_ICMP_H */
