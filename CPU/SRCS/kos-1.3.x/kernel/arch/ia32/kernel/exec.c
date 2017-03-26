/* KallistiOS ##version##

   exec.c
   Copyright (C)2003 Dan Potter
*/

#include <arch/arch.h>
#include <arch/exec.h>
#include <arch/irq.h>
#include <arch/cache.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>

CVSID("$Id: exec.c,v 1.1 2003/08/01 03:18:37 bardtx Exp $");

/* Pull the shutdown function in from main.c */
void arch_shutdown();

/* Replace the currently running image with whatever is at
   the pointer; note that this call will never return. */
void arch_exec_at(const void *image, uint32 length, uint32 address) {
	panic("ENOSYS");
}

void arch_exec(const void *image, uint32 length) {
	panic("ENOSYS");
}
