/*
 * sys/types2.h
 *
 * POSIX types that aren't in the sys/types.h file in the compiler
 * distribution.
 *
 * Created 5 Nov 96 by scole
 * Copyright 1996 PlanetWeb, Inc.
 *
 * $Header: c:/planetweb/katana/h:/RCS/api/sys/types2.h 1.9 1999-08-25 11:19:41-07 doug Exp $
 *
 * $Log: types2.h $
 * Revision 1.9  1999-08-25 11:19:41-07  doug
 * ssize_t declaration moved to local pwtypes.h for Mitsui, Gct, and Win32.
 *
 * Revision 1.8  1999-03-18 16:45:14-0800  soohoo
 * Added Katana code to avoid GCC dependencies.
 *
 * Revision 1.7  1999-03-10 17:03:59-0800  doug
 * Added GCT and WIN32.
 *
 * Revision 1.6  1998-10-26 10:09:29-0800  doug
 * Added GCT.
 *
 * Revision 1.5  1998-03-24 14:10:50-0800  scole
 * PUMA fixes.
 *
 * Revision 1.4  1997-11-06 14:08:12-0800  soohoo
 * Added mitsui.
 *
 * Revision 1.3  1996-12-03 21:43:17-0800  soohoo
 * Added PSX into ssize
 *
 * Revision 1.2  1996-11-27 11:47:11-0800  scole
 * Replaced tabs with blanks for better formatting.
 *
 * Revision 1.1  1996-11-18 11:47:39-0800  scole
 * Initial revision
 *
 */
#ifndef __TYPES2_H__
#ifdef __cplusplus
extern "C" {
#endif
#define __TYPES2_H__

/* Fancy preprocessor stuff so that we can use this file without first
 * including port.h.
 */
#ifdef __SATURN__
#if __SATURN__
#define __DOIT
#endif
#endif
#ifdef __8x8__
#if __8x8__
#define __DOIT
#endif
#endif
#ifdef __PSX__
#if __PSX__
#define __DOIT
#endif
#endif
#ifdef __KATANA__
#if __KATANA__
#ifndef __GNUC__
#define __DOIT
#endif
#endif
#endif

#ifdef __DOIT
#ifndef __SSIZE_T__
#define __SSIZE_T__
typedef long ssize_t;           /* a "signed" size_t */
#undef __DOIT
#endif
#endif

#ifdef __cplusplus
}
#endif

#endif /* __TYPES2_H__ */

