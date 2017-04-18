/*
 * netinet/tcp.h
 *
 * This is a direct implementation of the tcp.h header file, from
 * IEEE P1003.1g/D6.1, the POSIX network specification,
 * section A.3.5.2.
 *
 * Copyright 1996 PlanetWeb, Inc.
 * Created 4 Nov 96 by scole
 *
 * $Header: c:/planetweb/katana/h:/RCS/api/netinet/tcp.h 1.2 1996-11-27 19:45:54+00 scole Exp $
 *
 * $Log: tcp.h $
 * Revision 1.2  1996-11-27 19:45:54+00  scole
 * Replaced tabs with blanks for better formatting.
 *
 * Revision 1.1  1996-11-18 11:49:06-0800  scole
 * Initial revision
 *
 */
#ifndef __TCP_H__
#ifdef __cplusplus
extern "C" {
#endif
#define __TCP_H__

/*
 * Option values for setsockopt() and getsockopt() for TCP
 */
#define TCP_KEEPALIVE       20          /* keepalive interval */
#define TCP_MAXRXT          21          /* maximum retransmit time */
#define TCP_NODELAY         22          /* avoid coalescing of small segments */
#define TCP_MAXSEG          23          /* TCP segment size (get only) */
#define TCP_STDURG          24          /* standardized handling of urgent data sent */

#ifdef __cplusplus
}
#endif
#endif /* __TCP_H__ */
