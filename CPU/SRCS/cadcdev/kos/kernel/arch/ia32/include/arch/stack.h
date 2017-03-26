/* KallistiOS ##version##

   arch/dreamcast/include/arch/stack.h
   (c)2002 Dan Potter
   
   $Id: stack.h,v 1.1 2003/08/01 03:18:37 bardtx Exp $
*/

#ifndef __ARCH_STACK_H
#define __ARCH_STACK_H

#include <sys/cdefs.h>
__BEGIN_DECLS

#include <arch/types.h>

/* Do a stack trace from the current function; leave off the first n frames
   (i.e., in assert()). */
void arch_stk_trace(int n);

/* Do a stack trace from the given frame pointer (useful for things like
   tracing from an ISR); leave off the first n frames. */
void arch_stk_trace_at(uint32 fp, int n);

__END_DECLS

#endif	/* __ARCH_EXEC_H */

