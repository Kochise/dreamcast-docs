/* KallistiOS ##version##

   crtend.c
   Copyright (C)2002 Dan Potter
*/

/* Handles ctors and dtors (for C++ programs). This is modeled on the 
   FreeBSD crtend.c code. Note that the default linker scripts for
   GCC will automatically put our ctors at the end of the list. */

#include <sys/cdefs.h>

CVSID("$Id: crtend.c,v 1.1 2003/07/15 07:57:20 bardtx Exp $");

/* Here we gain access to the ctor and dtor sections of the program by
   defining new data in them. */
typedef void (*fptr)(void);

static fptr ctor_list[1] __attribute__((section(".ctors"))) = { (fptr) 0 };
static fptr dtor_list[1] __attribute__((section(".dtors"))) = { (fptr) 0 };

/* Ensures that this gets linked in */
void __crtend_pullin() {
	(void)ctor_list;
	(void)dtor_list;
}

