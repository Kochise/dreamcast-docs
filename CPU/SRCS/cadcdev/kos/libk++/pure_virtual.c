/* KallistiOS ##version##

   pure_virtual.c
   Copyright (C)2003 Dan Potter

   Provides a libsupc++ function for using pure virtuals. Thanks to
   Bero for the info.
 */

#include <arch/arch.h>

CVSID("$Id: pure_virtual.c,v 1.1 2003/05/23 02:26:50 bardtx Exp $");

void __cxa_pure_virtual() {
	panic("Pure virtual method called");
}

