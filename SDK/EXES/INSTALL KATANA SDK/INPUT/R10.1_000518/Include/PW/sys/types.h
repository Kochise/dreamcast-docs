/*
 * sys/types2.h
 *
 * POSIX types that aren't in the sys/types.h file in the compiler
 * distribution.
 *
 * Created 5 Nov 96 by scole
 * Copyright 1996 PlanetWeb, Inc.
 *
 * $Header: /locker/cvs/kage/3rdparty/pweb/include/sys/types.h,v 1.1 1999/09/27 17:47:32 taborm Exp $
 *
 * $Log: types.h,v $
 * Revision 1.1  1999/09/27 17:47:32  taborm
 * New version from PlanetWeb
 *
 *
 */

#ifndef __TYPES_H__
#ifdef __cplusplus
extern "C" {
#endif
#define __TYPES_H__

/* Fancy preprocessor stuff so that we can use this file without first
 * including port.h.
 */
#ifdef __KATANA__
#if __KATANA__
#ifndef __GNUC__
#define __DOIT
#endif
#endif
#endif

#ifdef __DOIT
#ifndef _SIZE_T
#define _SIZE_T
	typedef unsigned long size_t;
#endif
#undef __DOIT
#endif

#ifdef __cplusplus
}
#endif

typedef	unsigned char	u_char;
typedef	unsigned short	u_short;
typedef	unsigned int	u_int;
typedef	unsigned long	u_long;
typedef	unsigned short	ushort;		/* System V compatibility */
typedef	unsigned int	uint;		/* System V compatibility */

#endif /* __TYPES_H__ */

