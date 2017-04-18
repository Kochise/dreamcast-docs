/*
 * errno2.h
 *
 * Defines for POSIX errno values that aren't in a particular distribution of
 * errno.h.
 *
 * Created 5 Nov 96 by scole
 * Copyright 1996 PlanetWeb, Inc.
 *
 * $Header: c:/planetweb/katana/h:/RCS/api/errno2.h 1.14 1999-04-28 13:30:15+00 soohoo Exp $
 *
 * $Log: errno2.h $
 * Revision 1.14  1999-04-28 13:30:15+00  soohoo
 * Added luxsonor.
 *
 * Revision 1.13  1999-03-15 14:51:45-0800  soohoo
 * Removed commented out EINVAL.
 *
 * Revision 1.12  1999-02-11 14:44:38-0800  may
 * toshiba change
 *
 * Revision 1.11  1998-12-17 10:02:39-0800  soohoo
 * Added MediaMatics.
 *
 * Revision 1.10  1998-07-14 13:34:25-0700  soohoo
 * Added katana support.
 *
 * Revision 1.9  1998-06-04 11:53:02-0700  jason
 * Don't use this file if we're on the Video Surfer.
 *
 * Revision 1.8  1998-04-22 16:34:16-0700  scole
 * Fixed the KATANA #ifdef.
 *
 * Revision 1.7  1998-04-13 10:28:26-0700  scole
 * Removed EINVAL from PUMA
 *
 * Revision 1.6  1998-04-09 12:23:32-0700  soohoo
 * Added katana.
 *
 * Revision 1.4  1998-03-06 17:06:38-0800  scole
 * Puma fixes.
 *
 * Revision 1.3  1997-01-15 14:11:11-0800  scole
 * Changes for PSX added.
 *
 * Revision 1.2  1996-11-27 11:51:01-0800  scole
 * - Replaced tabs with blanks for better formatting.
 * - Added ENFILE define for the 8x8 platform.
 *
 * Revision 1.1  1996-11-18 11:44:36-0800  scole
 * Initial revision
 *
 */
#ifndef __ERRNO2_H__
#if !__VSURF__

#ifdef __cplusplus
extern "C" {
#endif
#define __ERRNO2_H__

#if (!__KATANA__ || !defined(__GNUC__)) && (!__LUXSONOR__)
#define EPROTONOSUPPORT     3000
#define ESOCKTNOSUPPORT     3001
#define ENOBUFS             3002
#define EAFNOSUPPORT        3003
#define EADDRNOTAVAIL       3004
#define ENETDOWN            3005
#define EADDRINUSE          3006
#if !__PSX__
#define EALREADY            3007
#endif
#define EISCONN             3008
#if !__PSX__
#define EINPROGRESS         3009
#endif
#define ECONNABORTED        3010
#define ECONNREFUSED        3011
#define ECONNRESET          3012
#define EHOSTUNREACH        3013
#define EMSGSIZE            3014
#define ENETRESET           3015
#define ENETUNREACH         3016
#define ENOPROTOOPT         3017
#define ENOTCONN            3018
#define ENOTSOCK            3019
#define EOPNOTSUPP          3020
#define EPROTOTYPE          3021
#define ETIMEDOUT           3022
#if !__PSX__
#define EWOULDBLOCK         3023
#endif
#if __8x8__ || __PUMA__ || (__KATANA__ && !defined(__GNUC__)) || __MMATICS__ || __TOSHIBA__
#define ENFILE              3024
#endif
#if __PUMA__ || __MMATICS__ || __TOSHIBA__
#define EBADF				3025
#endif
#if (__KATANA__ && !defined(__GNUC__)) || __MMATICS__
#define EINVAL				3026
#endif
#endif /* !__KATANA__ */

#ifdef __cplusplus
}
#endif

#endif /* !__VSURF__ */
#endif /* __ERRNO2_H__ */
