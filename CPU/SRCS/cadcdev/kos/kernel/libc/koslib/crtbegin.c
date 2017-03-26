/* KallistiOS ##version##

   crtbegin.c
   Copyright (C)2002 Dan Potter
*/

/* Handles ctors and dtors (for C++ programs). This is modeled on the 
   FreeBSD crtbegin.c code. Note that the default linker scripts for
   GCC will automatically put our ctors at the front of the list. */

#include <arch/types.h>

/* Here we gain access to the ctor and dtor sections of the program by
   defining new data in them. */
typedef void (*fptr)(void);

static fptr ctor_list[1] __attribute__((section(".ctors"))) = { (fptr) -1 };
static fptr dtor_list[1] __attribute__((section(".dtors"))) = { (fptr) -1 };

void __verify_newlib_patch();

/* Call this to execute all ctors */
void arch_ctors() {
	fptr *fpp;

	__verify_newlib_patch();

	/* Run up to the end of the list (defined by crtend) */
	for (fpp=ctor_list + 1; *fpp != 0; ++fpp)
		;

	/* Now run the ctors backwards */
	while (--fpp > ctor_list)
		(**fpp)();
}

/* Call this to execute all dtors */
void arch_dtors() {
	fptr *fpp;

	/* Do the dtors forwards */
	for (fpp=dtor_list + 1; *fpp != 0; ++fpp )
		(**fpp)();
}

