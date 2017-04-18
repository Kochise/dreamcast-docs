/* KallistiOS 1.1.6

   arch/dreamcast/include/syscall.h
   (c)2000-2001 Dan Potter

   $Id: syscall.h,v 1.2 2002/01/05 07:33:50 bardtx Exp $

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
		thd_schedule(); \
	return; } while(0)


/* This macro can be used in normal mode to jump into kernel
   mode convienently */
#define SYSCALL(routine) \
	__asm__("mov	%0,r3\n" \
	    "trapa	#0\n" : : "r"(routine))

__END_DECLS

#endif	/* __ARCH_SYSCALL_H */



