/* KallistiOS ##version##

   arch/dreamcast/include/syscall.h
   (c)2000-2001 Dan Potter

   $Id: syscall.h,v 1.4 2002/11/14 06:55:46 bardtx Exp $

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
   mode convienently. Up to 4 parameters can be passed. An
   int value will be returned. You can pass dummy values for
   any of the four parameters and/or ignore the return value. */
#define SYSCALL(routine, p1, p2, p3, p4) ({ \
	register uint32 __routine __asm__("r3") = (uint32)(routine); \
	register uint32 __p1 __asm__("r4")  = (uint32)(p1); \
	register uint32 __p2 __asm__("r5")  = (uint32)(p2); \
	register uint32 __p3 __asm__("r6")  = (uint32)(p3); \
	register uint32 __p4 __asm__("r7")  = (uint32)(p4); \
	int __value; \
	__asm__ volatile( \
		"trapa	#0\n" \
	: "=r"(__value) \
	: "r"(__routine), "r"(__p1), "r"(__p2), "r"(__p3), "r"(__p4) \
	); \
	__value; })

__END_DECLS

#endif	/* __ARCH_SYSCALL_H */



