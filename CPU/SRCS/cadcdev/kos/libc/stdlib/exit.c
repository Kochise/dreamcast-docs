/* KallistiOS ##version##

   exit.c
   (c)2001 Dan Potter

   $Id: exit.c,v 1.1 2002/02/09 06:15:43 bardtx Exp $
*/

#include <arch/arch.h>

/* exit() */
void exit() {
	arch_exit();
}

