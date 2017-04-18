/*
 * arpa/inet.h
 *
 * This is a direct implementation of the inet.h header file, from
 * IEEE P1003.1g/D6.1, the POSIX network specification,
 * section 7.2.1.
 *
 * Copyright 1996 PlanetWeb, Inc.
 * Created 4 Nov 96 by scole
 *
 * $Header: c:/planetweb/katana/h:/RCS/api/arpa/inet.h 1.11 1999-04-28 13:32:30+00 soohoo Exp $
 *
 * $Log: inet.h $
 * Revision 1.11  1999-04-28 13:32:30+00  soohoo
 * Added luxsonor.
 *
 * Revision 1.10  1999-03-15 14:53:28-0800  soohoo
 * Changed from double slash comments.
 *
 * Revision 1.9  1999-02-11 15:16:02-0800  may
 * add toshiba define
 *
 * Revision 1.8  1999-01-13 15:57:06-0800  may
 * Added special for toshiba.
 *
 * Revision 1.7  1998-07-14 13:36:43-0700  soohoo
 * Changed htonl and htons to externs.
 *
 * Revision 1.6  1998-06-04 13:21:59-0700  jason
 * Added defines to reduce namespace conflicts.
 *
 * Revision 1.5  1998-03-24 14:12:51-0800  scole
 * htonl & s changes.
 *
 * Revision 1.4  1998-03-04 10:59:19-0800  scole
 * Added non-GNUC versions of little endian htons and htonl.
 *
 * Revision 1.3  1997-01-15 14:12:41-0800  scole
 * Changed the htonl and htons macros so that their argument is only
 * evaluated once (on little-endian machines).
 *
 * Revision 1.2  1996-11-27 11:43:07-0800  scole
 * - Put type casts into htonl() and htons(), because the sign bit was
 *   getting smeared on little-endian machines.
 * - Replaced tabs with blanks for better formatting.
 *
 * Revision 1.1  1996-11-18 11:49:42-0800  scole
 * Initial revision
 *
 */
#ifndef __INET_H__
#ifdef __cplusplus
extern "C" {
#endif
#define __INET_H__

#include <netinet/in.h>

#ifndef __LUXSONOR__
#define __LUXSONOR__ 0
#endif

#if __LUXSONOR__
#include <mips/endian.h>
#else

#if __BIG_ENDIAN__
#define htonl(host32)       (host32)
#define htons(host16)       (host16)
#elif __LITTLE_ENDIAN__
#ifdef __GNUC__
#define htonl(host32)       ({ in_addr_t _val = (host32); (((((in_addr_t)(_val))&0xff) << 24) | ((((in_addr_t)(_val))&0xff00) << 8) | ((((in_addr_t)(_val))&0xff0000) >> 8) | (((in_addr_t)(_val)) >> 24)); })
#define htons(host16)       ({ in_port_t _val = (host16); (((((in_port_t)(_val))&0xff) << 8) | (((in_port_t)(_val)) >> 8)); })
#else /* not __GNUC__ */
#ifdef INLINES_BROKEN
extern in_addr_t htonl(in_addr_t);
extern in_port_t htons(in_port_t);
#else /* not INLINES_BROKEN */
extern inline in_addr_t htonl(in_addr_t host32)
{
	in_addr_t _val = (host32);
	return (((_val & 0xff) << 24)
			| ((_val & 0xff00) << 8)
			| ((_val & 0xff0000) >> 8)
			| (_val >> 24));
}
extern inline in_port_t htons(in_port_t host16)
{
	return (((host16 & 0xff) << 8)
			| (host16 >> 8));
}
#endif /* not INLINES_BROKEN */
#endif /* not __GNUC__ */
#else
#error Either __BIG_ENDIAN__ or __LITTLE_ENDIAN__ must be nonzero!
#endif
#define ntohl(net32)        htonl(net32)
#define ntohs(net16)        htons(net16)

#endif

#define inet_addr pw_inet_addr
#define inet_lnaof pw_inet_lnaof
#define inet_makeaddr pw_inet_makeaddr
#define inet_netof pw_inet_netof
#define inet_network pw_inet_network
#define inet_ntoa pw_inet_ntoa

in_addr_t       inet_addr(const char *cp);
in_addr_t       inet_lnaof(struct in_addr in);
struct in_addr  inet_makeaddr(in_addr_t net, in_addr_t lna);
in_addr_t       inet_netof(struct in_addr in);
in_addr_t       inet_network(const char *cp);
char *          inet_ntoa(struct in_addr in);

#ifdef __cplusplus
}
#endif

#endif /* __INET_H__ */
