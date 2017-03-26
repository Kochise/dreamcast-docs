/* KallistiOS ##version##

   math.h
   (c)2001 Dan Potter

   $Id: math.h,v 1.6 2002/10/26 07:56:58 bardtx Exp $
*/

#ifndef __KOS_MATH_H
#define __KOS_MATH_H

#include <sys/cdefs.h>
__BEGIN_DECLS

/* Just pull in the Newlib math routines for the right platform */
#ifdef _arch_dreamcast
#include <newlib-libm-sh4/math.h>
#elif _arch_gba
#include <newlib-libm-arm/math.h>
#elif _arch_ps2
#include <newlib-libm-sh4/math.h>	/* XXX Not correct yet */
#else
#error Invalid architecture or no architecture specified
#endif

__END_DECLS

#endif	/* __KOS_MATH_H */

