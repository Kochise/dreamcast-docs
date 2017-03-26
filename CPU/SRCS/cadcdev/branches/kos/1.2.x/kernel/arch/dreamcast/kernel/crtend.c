/* KallistiOS ##version##

   crtend.c
   (c)2002 Dan Potter
*/

/* Handles ctors and dtors (for C++ programs). This is modeled on the 
   FreeBSD crtend.c code. Note that the default linker scripts for
   GCC will automatically put our ctors at the end of the list. */

#include <sys/cdefs.h>

CVSID("$Id: crtend.c,v 1.1 2002/01/06 01:55:43 bardtx Exp $");

/* Here we gain access to the ctor and dtor sections of the program by
   defining new data in them. */
typedef void (*fptr)(void);

static fptr ctor_list[1] __attribute__((section(".ctors"))) __unused = { (fptr) 0 };
static fptr dtor_list[1] __attribute__((section(".dtors"))) __unused = { (fptr) 0 };

/* Ensures that this gets linked in */
void __crtend_pullin() { }

