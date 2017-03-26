/* KallistiOS ##version##

   abort.c
   (c)2001 Dan Potter

   $Id: abort.c,v 1.2 2002/09/23 23:03:33 gilm Exp $
*/

#include <stdlib.h>
#include <arch/arch.h>

CVSID("$Id: abort.c,v 1.2 2002/09/23 23:03:33 gilm Exp $");

/* This is probably the closest mapping we've got for abort() */
void abort() {
	arch_exit();
}

