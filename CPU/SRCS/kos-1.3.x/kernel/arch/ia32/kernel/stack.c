/* KallistiOS ##version##

   stack.c
   Copyright (C)2003 Dan Potter
*/

/* Functions to tinker with the stack, includeing obtaining a stack
   trace when frame pointers are enabled. If frame pointers are enabled,
   then you'll need to also define FRAME_POINTERS to get support for stack
   traces.

   We could probably technically move this into arch indep with a bit more
   work... */

#include <arch/arch.h>
#include <arch/dbgio.h>
#include <arch/stack.h>

CVSID("$Id: stack.c,v 1.2 2003/08/02 09:14:46 bardtx Exp $");

/* Do a stack trace from the current function; leave off the first n frames
   (i.e., in assert()). */
void arch_stk_trace(int n) {
}

/* Do a stack trace from the given frame pointer (useful for things like
   tracing from an ISR); leave off the first n frames. */
void arch_stk_trace_at(uint32 fp, int n) {
	uint32 foo = fp + 5;
	dbgio_printf("%d\n", foo);
#ifdef FRAME_POINTERS
	dbgio_printf("-------- Stack Trace (innermost first) ---------\n");
	dbgio_printf("-------------- End Stack Trace -----------------\n");
#else
	dbgio_printf("Stack Trace: frame pointers not enabled!\n");
#endif
}

