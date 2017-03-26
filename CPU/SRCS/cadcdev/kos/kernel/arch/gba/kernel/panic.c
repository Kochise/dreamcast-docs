/* KallistiOS ##version##

   panic.c
   (c)2001 Dan Potter
*/

static char id[] = "KOS $Id: panic.c,v 1.1.1.1 2001/09/26 07:05:11 bardtx Exp $";

/* Setup basic kernel services (printf, etc) */
#include <stdio.h>
#include <malloc.h>

/* If something goes badly wrong in the kernel and you don't think you
   can recover, call this. This is a pretty standard tactic from *nixy
   kernels which ought to be avoided if at all possible. */
void panic(const char *msg) {
	printf("%s\r\n", msg);
	arch_exit();
}

