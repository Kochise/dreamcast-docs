/* KallistiOS 1.1.6

   math.h
   (c)2001 Potter

   $Id: math.h,v 1.3 2002/01/05 07:23:32 bardtx Exp $
*/

#ifndef __KOS_MATH_H
#define __KOS_MATH_H

#include <sys/cdefs.h>
__BEGIN_DECLS

/* Just pull in the Newlib math routines for the right platform */
#ifdef _arch_dreamcast
#include <newlib-libm-sh4/math.h>
#elif _arch_gba
#error No math.h support for GBA yet
#else
#error Invalid architecture or no architecture specified
#endif

__END_DECLS

#endif	/* __KOS_MATH_H */

