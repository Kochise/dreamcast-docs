/* KallistiOS ##version##

   ia32/irq.h
   Copyright (C)2000,2001,2003 Dan Potter

   $Id: irq.h,v 1.2 2003/08/02 09:14:46 bardtx Exp $
  
*/

#ifndef __ARCH_IRQ_H
#define __ARCH_IRQ_H

#include <sys/cdefs.h>
__BEGIN_DECLS

#include <arch/types.h>

/* The number of bytes required to save thread context. This should
   include all general CPU registers, FP registers, and status regs (even
   if not all of these are actually used). */
#define REG_BYTE_CNT 256

/* Architecture-specific structure for holding the processor state (register
   values, etc). The size of this structure should be less than or equal
   to the above value. */
typedef struct irq_context {
	uint32		eax, ebx, ecx, edx;	// GPRs
	uint32		esi, edi;		// String regs
	uint32		ebp, esp;		// Stack
	uint32		eip;			// Program counter
	uint32		eflags;			// CPU flags
	// We'll certainly need more later (FPRs, LDT, etc) but that's a
	// good enough start.
} irq_context_t;

// A couple of architecture independent access macros
#define CONTEXT_PC(c)	((c).eip)
#define CONTEXT_FP(c)	((c).ebp)
#define CONTEXT_SP(c)	((c).esp)
#define CONTEXT_RET(c)	((c).eax)

// ia32-specific exception codes
#define EXC_DIVIDE_ERROR	0x0000
#define EXC_DEBUG		0x0001
#define EXC_NMI			0x0002
#define EXC_BREAKPOINT		0x0003
#define EXC_OVERFLOW		0x0004
#define EXC_BOUND		0x0005
#define EXC_INVALID_OPCODE	0x0006
#define EXC_DEV_NOT_AVAILABLE	0x0007
#define EXC_EXC_DOUBLE_FAULT	0x0008	// Error code
#define EXC_COPROC_OVERRUN	0x0009
#define EXC_INVALID_TSS		0x000a	// Error code
#define EXC_SEG_NOT_PRESENT	0x000b
#define EXC_STACK_FAULT		0x000c	// Error code
#define EXC_GEN_PROT_FAULT	0x000d	// Error code
#define EXC_PAGE_FAULT		0x000e
#define EXC_COPROC_ERROR	0x0010

// We will assign hardware interrupts to 0x70 - 0x7f using the PIC.
#define EXC_IRQ0		0x0070
#define EXC_IRQ1		0x0071
#define EXC_IRQ2		0x0072
#define EXC_IRQ3		0x0073
#define EXC_IRQ4		0x0074
#define EXC_IRQ5		0x0075
#define EXC_IRQ6		0x0076
#define EXC_IRQ7		0x0077
#define EXC_IRQ8		0x0078
#define EXC_IRQ9		0x0079
#define EXC_IRQA		0x007a
#define EXC_IRQB		0x007b
#define EXC_IRQC		0x007c
#define EXC_IRQD		0x007d
#define EXC_IRQE		0x007e
#define EXC_IRQF		0x007f

// This is a software-generated one (double-fault) for when an exception
// happens inside an ISR. This is different from the hardware-generated
// "double fault" that happens above when the processor is trying to
// service an exception and gets an exception.
#define EXC_DOUBLE_FAULT	0x0100

/* Software-generated for unhandled exception */
#define EXC_UNHANDLED_EXC	0x0101

/* The value of the timer IRQ */
#define TIMER_IRQ		EXC_IRQ0

/* The type of an interrupt identifier */
typedef uint32 irq_t;

/* The type of an IRQ handler */
typedef void (*irq_handler)(irq_t source, irq_context_t *context);

/* Are we inside an interrupt handler? */
int irq_inside_int();

/* Pretend like we just came in from an interrupt and force
   a context switch back to the "current" context. Make sure
   you've called irq_set_context()! */
void irq_force_return();

/* Set a handler, or remove a handler (see codes above) */
int irq_set_handler(irq_t source, irq_handler hnd);

/* Non-public function */
struct kprocess;
int _irq_set_handler(struct kprocess * proc, irq_t src, irq_handler hnd);

/* Get the address of the current handler */
irq_handler irq_get_handler(irq_t source);

/* Set a global exception handler */
int irq_set_global_handler(irq_handler hnd);

/* Non-public version */
int _irq_set_global_handler(struct kprocess * proc, irq_handler hnd);

/* Get the global exception handler */
irq_handler irq_get_global_handler();

/* Switch out contexts (for interrupt return) */
void irq_set_context(irq_context_t *regbank);

/* Return the current IRQ context */
irq_context_t *irq_get_context();

/* Fill a newly allocated context block for usage with supervisor/kernel
   or user mode. The given parameters will be passed to the called routine (up
   to the architecture maximum). */
void irq_create_context(irq_context_t *context, ptr_t stack_pointer,
	ptr_t routine, uint32 *args, int usermode);

/* Enable/Disable interrupts */
int irq_disable();		/* Will leave exceptions enabled */
int irq_enable();		/* Enables all ints including external */
void irq_restore(int v);

/* Remove all IRQ handlers for the named process */
void irq_remove_process(struct kprocess * proc);

/* Low-level IRQ/Exception setup, located in entry.s */
void irq_low_setup();

/* Init routine */
int irq_init();

/* Shutdown */
void irq_shutdown();

__END_DECLS

#endif	/* __ARCH_IRQ_H */

