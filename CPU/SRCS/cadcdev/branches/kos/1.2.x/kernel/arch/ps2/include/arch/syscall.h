/* KallistiOS ##version##

   arch/ps2/include/syscall.h
   (c)2000-2002 Dan Potter

   $Id: syscall.h,v 1.3 2002/11/14 06:50:06 bardtx Exp $

*/

#ifndef __ARCH_SYSCALL_H
#define __ARCH_SYSCALL_H

#include <sys/cdefs.h>
__BEGIN_DECLS

#include <arch/types.h>
#include <arch/irq.h>

/* Set the return value for a syscall for a dormant thread */
void syscall_set_return(irq_context_t *context, int value);

/* Handles all the nasty work */
#define SET_RETURN(thread, value) \
	syscall_set_return(&(thread->context), (value))

/* Ditto */
#define SET_MY_RETURN(value) \
	SET_RETURN(thd_current, value)

/* Ditto */
#define RETURN(value) do { \
	SET_RETURN(thd_current, value); \
	/* if (thd_current->state != STATE_RUNNING) */ \
		thd_schedule(0); \
	return; } while(0)


/* This macro can be used in normal mode to jump into kernel
   mode convienently. XXX Need to update for new syntax usage. */
#define SYSCALL(routine, p1, p2, p3, p4) do { \
	__asm__("la	$8,0(%0);" \
	        "syscall;" \
	        "nop;" : : "r"(routine)); \
	} while(0)

__END_DECLS

#endif	/* __ARCH_SYSCALL_H */



