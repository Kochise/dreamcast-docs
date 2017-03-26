/*
	sh_utils.h

	(c) 2002 heinrich tillack <tillack@web.de>

 	under GPL or new BSD license
*/

#ifndef SH_UTILS_H
#define SH_UTILS_H

#include <dc/matrix.h>

//PUSH and POP of the internal Sh4 matrix


static matrix_t temp __attribute__((aligned(32)));

#define  PUSH_SH4M() mat_store(&temp)
#define  POP_SH4M()  mat_load(&temp)

/*
 	use this like

 	float result = mat_sqrtipr(x,y,z)

	for

	result= SQRT(x*x+y*y+z*z)
*/

#define mat_sqrtipr(x, y, z) ({ \
	register float __x __asm__("fr0") = (x); \
	register float __y __asm__("fr1") = (y); \
	register float __z __asm__("fr2") = (z); \
	register float __result __asm__("fr3"); \
	__asm__ __volatile__( \
		"fldi0	fr3\n" \
		"fipr	fv0,fv0\n" \
		"fsqrt	fr3\n" \
		: "=f" (__result) \
		: "f" (__x), "f" (__y), "f" (__z) \
		); \
	__result; \
})

/*
 	use this like

 	float result = mat_ipr(x,y,z)

	for

	result= (x*x+y*y+z*z)
*/
#define mat_ipr(x, y, z) ({ \
	register float __x __asm__("fr0") = (x); \
	register float __y __asm__("fr1") = (y); \
	register float __z __asm__("fr2") = (z); \
	register float __result __asm__("fr3"); \
	__asm__ __volatile__( \
		"fldi0	fr3\n" \
		"fipr	fv0,fv0\n" \
		: "=f" (__result) \
		: "f" (__x), "f" (__y), "f" (__z) \
		); \
	__result; \
})

#define vec_length mat_ipr


#endif

