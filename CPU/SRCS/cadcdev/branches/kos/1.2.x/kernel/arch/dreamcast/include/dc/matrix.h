/* KallistiOS ##version##

   matrix.h
   (c)2000 Dan Potter

   $Id: matrix.h,v 1.2 2002/09/06 06:29:08 bardtx Exp $
*/

#ifndef __DC_MATRIX_H
#define __DC_MATRIX_H

#include <sys/cdefs.h>
__BEGIN_DECLS

#include <kos/vector.h>

/* Copy the internal matrix out to a memory one */
void mat_store(matrix_t *out);

/* Copy a memory matrix into the internal one */
void mat_load(matrix_t *out);

/* Clear internal to an identity matrix */
void mat_identity();

/* "Apply" a matrix: multiply a matrix onto the "internal" one */
void mat_apply(matrix_t *src);

/* Transform zero or more sets of vectors using the current internal
   matrix. Each vector is three floats long. */
void mat_transform(vector_t *invecs, vector_t *outvecs, int veccnt, int vecskip);

/* Inline mat_transform which works on the three coordinates passed in;
   this works most efficiently if you've already got the three numbers
   (x,y,z) in the right registers (fr0,fr1,fr2). */
#define mat_trans_single(x, y, z) { \
	register float __x __asm__("fr0") = (x); \
	register float __y __asm__("fr1") = (y); \
	register float __z __asm__("fr2") = (z); \
	__asm__ __volatile__( \
		"fldi1	fr3\n" \
		"ftrv	xmtrx,fv0\n" \
		"fdiv	fr3,fr0\n" \
		"fdiv	fr3,fr1\n" \
		"fldi1	fr2\n" \
		"fdiv	fr3,fr2\n" \
		: "=f" (__x), "=f" (__y), "=f" (__z) \
		: "0" (__x), "1" (__y), "2" (__z) \
		: "fr3" ); \
	x = __x; y = __y; z = __z; \
}

/* Same as above, but allows an input to and preserves the Z/W value */
#define mat_trans_single4(x, y, z, w) { \
	register float __x __asm__("fr0") = (x); \
	register float __y __asm__("fr1") = (y); \
	register float __z __asm__("fr2") = (z); \
	register float __w __asm__("fr3") = (w); \
	__asm__ __volatile__( \
		"ftrv	xmtrx,fv0\n" \
		"fdiv	fr3,fr0\n" \
		"fdiv	fr3,fr1\n" \
		"fdiv	fr3,fr2\n" \
		"fldi1	fr4\n" \
		"fdiv	fr3,fr4\n" \
		"fmov	fr4,fr3\n" \
		: "=f" (__x), "=f" (__y), "=f" (__z), "=f" (__w) \
		: "0" (__x), "1" (__y), "2" (__z), "3" (__w) \
		: "fr4" ); \
	x = __x; y = __y; z = __z; w = __w; \
}

/* This is like mat_trans_single, but it leaves z/w instead of 1/w
   for the z component. */
#define mat_trans_single3(x, y, z) { \
	register float __x __asm__("fr0") = (x); \
	register float __y __asm__("fr1") = (y); \
	register float __z __asm__("fr2") = (z); \
	__asm__ __volatile__( \
		"fldi1	fr3\n" \
		"ftrv	xmtrx,fv0\n" \
		"fdiv	fr3,fr0\n" \
		"fdiv	fr3,fr1\n" \
		"fdiv	fr3,fr2\n" \
		: "=f" (__x), "=f" (__y), "=f" (__z) \
		: "0" (__x), "1" (__y), "2" (__z) \
		: "fr3" ); \
	x = __x; y = __y; z = __z; \
}


__END_DECLS

#endif	/* __DC_MATRIX_H */

