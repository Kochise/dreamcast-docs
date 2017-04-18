/*
 * netinet/in.h
 *
 * This is a direct implementation of the in.h header file, from
 * IEEE P1003.1g/D6.1, the POSIX network specification,
 * section A.3.5.1.
 *
 * Copyright 1996 PlanetWeb, Inc.
 * Created 4 Nov 96 by scole
 *
 * $Header: c:/planetweb/katana/h:/RCS/api/netinet/in.h 1.4 1999-08-25 11:23:09-07 doug Exp $
 *
 * $Log: in.h $
 * Revision 1.4  1999-08-25 11:23:09-07  doug
 * Added IN_CLASSxxxx macros.
 *
 * Revision 1.3  1999-04-28 06:33:06-0700  soohoo
 * Added luxsonor.
 *
 * Revision 1.2  1996-11-27 11:45:29-0800  scole
 * Replaced tabs with blanks for better formatting.
 *
 * Revision 1.1  1996-11-18 11:48:47-0800  scole
 * Initial revision
 *
 */
#ifndef __IN_H__
#ifdef __cplusplus
extern "C" {
#endif
#define __IN_H__

#ifndef __LUXSONOR__
#define __LUXSONOR__ 0
#endif

#if __LUXSONOR__
#include <mips/endian.h>
#else
typedef unsigned long in_addr_t;
typedef unsigned short in_port_t;
#endif

struct in_addr {
    in_addr_t   s_addr;
};

struct sockaddr_in {
    sa_family_t         sin_family;     /* must be AF_INET */
    in_port_t           sin_port;       /* port number */
    struct in_addr      sin_addr;       /* Internet address */
};

struct ip_opts {
    struct in_addr      ip_dst;         /* First-hop destination (for source route) */
    char                ip_opts[40];    /* IP options, may be smaller */
};

/*
 * Definitions of bits in internet address integers.
 * On subnets, the decomposition of addresses to host and net parts
 * is done according to subnet mask, not the masks here.
 */

#define	IN_CLASSA(i)		(((in_addr_t)(i) & 0x80000000) == 0)
#define	IN_CLASSA_NET		0xff000000
#define	IN_CLASSA_NSHIFT	24
#define	IN_CLASSA_HOST		0x00ffffff
#define	IN_CLASSA_MAX		128

#define	IN_CLASSB(i)		(((in_addr_t)(i) & 0xc0000000) == 0x80000000)
#define	IN_CLASSB_NET		0xffff0000
#define	IN_CLASSB_NSHIFT	16
#define	IN_CLASSB_HOST		0x0000ffff
#define	IN_CLASSB_MAX		65536

#define	IN_CLASSC(i)		(((in_addr_t)(i) & 0xe0000000) == 0xc0000000)
#define	IN_CLASSC_NET		0xffffff00
#define	IN_CLASSC_NSHIFT	8
#define	IN_CLASSC_HOST		0x000000ff

#define	IN_CLASSD(i)		(((in_addr_t)(i) & 0xf0000000) == 0xe0000000)
#define	IN_CLASSD_NET		0xf0000000	/* These ones aren't really */
#define	IN_CLASSD_NSHIFT	28		/* net and host fields, but */
#define	IN_CLASSD_HOST		0x0fffffff	/* routing needn't know.    */
#define	IN_MULTICAST(i)		IN_CLASSD(i)

#define	IN_EXPERIMENTAL(i)	(((in_addr_t)(i) & 0xf0000000) == 0xf0000000)
#define	IN_BADCLASS(i)		(((in_addr_t)(i) & 0xf0000000) == 0xf0000000)

#define	INADDR_ANY			(in_addr_t)0x00000000
#define	INADDR_LOOPBACK		(in_addr_t)0x7f000001
#define	INADDR_BROADCAST	(in_addr_t)0xffffffff	/* must be masked */
#define	INADDR_NONE			0xffffffff				/* -1 return */

#define	INADDR_UNSPEC_GROUP		(in_addr_t)0xe0000000	/* 224.0.0.0 */
#define	INADDR_ALLHOSTS_GROUP	(in_addr_t)0xe0000001	/* 224.0.0.1 */
#define	INADDR_ALLRTRS_GROUP	(in_addr_t)0xe0000002	/* 224.0.0.2 */
#define	INADDR_MAX_LOCAL_GROUP	(in_addr_t)0xe00000ff	/* 224.0.0.255 */

#define	IN_LOOPBACKNET		127			/* official! */

#define IPPROTO_IP          255
#define IPPROTO_ICMP        1
#define IPPROTO_TCP         6
#define IPPROTO_UDP         17
#define IPPROTO_RAW         0

/*
 * Option ID's for getsockopt() and setsockopt()
 */
#define IP_OPTIONS          15          /* IP Protocol options */
#define IP_TOS              16          /* IP type-of-service value */
#define IP_TTL              17          /* initial time to live value */
#define IP_RECVDSTADDR      18          /* Request the destination addr of incoming */
#define IP_HDRINCL          19          /* IP header included with outgoing datagrams */


#ifdef __cplusplus
}
#endif
#endif /* __IN_H__ */
