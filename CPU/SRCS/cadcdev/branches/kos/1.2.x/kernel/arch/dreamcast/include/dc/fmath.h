/* KallistiOS ##version##

   dc/fmath.h
   (C)2001 Andrew Kieschnick

   $Id: fmath.h,v 1.3 2002/01/05 07:33:51 bardtx Exp $

*/

#ifndef __DC_FMATH_H
#define __DC_FMATH_H

#include <sys/cdefs.h>
__BEGIN_DECLS

#include <arch/types.h>

/* Inline functions for the DC's special math instructions */

/* PI constant (if you don't want full math.h) */
#define F_PI 3.1415926f


#define __fsin(x) \
({ float __value, __arg = (x), __scale = 10430.37835; \
	asm(	"fmul	%2,%1\n\t" \
		"ftrc	%1,fpul\n\t" \
		".short	0xf0fd\n\t" \
		"fmov	fr0,%0" \
	: "=f" (__value), "+&f" (__scale) \
	: "f" (__arg) \
	: "fpul", "fr0", "fr1"); \
	__value; })

#define __fcos(x) \
({ float __value, __arg = (x), __scale = 10430.37835; \
	asm(	"fmul	%2,%1\n\t" \
		"ftrc	%1,fpul\n\t" \
		".short	0xf0fd\n\t" \
		"fmov	fr1,%0" \
	: "=f" (__value), "+&f" (__scale) \
	: "f" (__arg) \
	: "fpul", "fr0", "fr1"); \
	__value; })

#define __ftan(x) \
({ float __value, __arg = (x), __scale = 10430.37835; \
	asm(	"fmul	%2,%1\n\t" \
		"ftrc	%1,fpul\n\t" \
		".short	0xf0fd\n\t" \
                "fdiv   fr1, fr0\n\t" \
		"fmov	fr0,%0" \
	: "=f" (__value), "+&f" (__scale) \
	: "f" (__arg) \
	: "fpul", "fr0", "fr1"); \
	__value; })


#define __fisin(x) \
({ float __value, __arg = (x); \
	asm(	"lds	%1,fpul\n\t" \
		".short	0xf0fd\n\t" \
		"fmov	fr0,%0" \
	: "=f" (__value) \
	: "r" (__arg) \
	: "fpul", "fr0", "fr1"); \
	__value; })

#define __ficos(x) \
({ float __value, __arg = (x); \
	asm(	"lds	%1,fpul\n\t" \
		".short	0xf0fd\n\t" \
		"fmov	fr1,%0" \
	: "=f" (__value) \
	: "r" (__arg) \
	: "fpul", "fr0", "fr1"); \
	__value; })

#define __fitan(x) \
({ float __value, __arg = (x); \
	asm(	"lds	%1,fpul\n\t" \
		".short	0xf0fd\n\t" \
                "fdiv   fr1, fr0\n\t" \
		"fmov	fr0,%0" \
	: "=f" (__value) \
	: "r" (__arg) \
	: "fpul", "fr0", "fr1"); \
	__value; })


#define __fsqrt(x) \
({ float __arg = (x); \
	asm(	"fsqrt %0\n\t" \
	: "=f" (__arg) : "0" (__arg)); \
	__arg; })

#define __frsqrt(x) \
({ float __value, __arg = (x); \
	asm(	"fmov	%1,fr0\n\t" \
		".short	0xf07d\n\t" \
		"fmov	fr0,%0\n\t" \
	: "=f" (__value) : "f" (__arg)); \
	__value; })


/* Returns sin(r), where r is [0..2*PI] */
extern inline float fsin(float r) {
	return __fsin(r);
}

/* Returns cos(r), where r is [0..2*PI] */
extern inline float fcos(float r) {
	return __fcos(r);
}

/* Returns tan(r), where r is [0..2*PI] */
extern inline float ftan(float r) {
	return __ftan(r);
}

/* Returns sin(d), where d is [0..65535] */
extern inline float fisin(int d) {
	return __fisin(d);
}

/* Returns cos(d), where d is [0..65535] */
extern inline float ficos(int d) {
	return __ficos(d);
}

/* Returns tan(d), where d is [0..65535] */
extern inline float fitan(int d) {
	return __fitan(d);
}

/* Returns sqrt(f) */
extern inline float fsqrt(float f) {
	return __fsqrt(f);
}

/* Returns 1.0f / sqrt(f) */
extern inline float frsqrt(float f) {
	return __frsqrt(f);
}

__END_DECLS

#endif	/* __DC_FMATH_H */

