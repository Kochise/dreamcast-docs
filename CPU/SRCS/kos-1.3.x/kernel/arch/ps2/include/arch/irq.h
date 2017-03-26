/* KallistiOS ##version##

   arch/ps2/include/irq.h
   (c)2000-2002 Dan Potter

   $Id: irq.h,v 1.3 2002/11/03 03:40:55 bardtx Exp $
  
*/

#ifndef __ARCH_IRQ_H
#define __ARCH_IRQ_H

#include <sys/cdefs.h>
__BEGIN_DECLS

#include <arch/types.h>

/* The number of bytes required to save thread context. This should
   include all general CPU registers, FP registers, and status regs (even
   if not all of these are actually used). */
#define REG_BYTE_CNT (32*16 + 2*16 + 8 + 6*4 + 32*4 + 2*4)

/* Architecture-specific structure for holding the processor state (register
   values, etc). The size of this structure should be less than or equal
   to the above value. We currently don't save the full 128-bit GPRs. */
typedef struct irq_context {
	uint128		r[32];			/* 31 general purpose regs (+ $zero) */
	uint128		lo, hi;			/* LO, HI */
	uint64		sa;			/* Shift amount */
	uint32		status, pc;		/* COP0 regs relevant to context */
	uint32		cause, config,		/* Not really part of context, but kernel will need them */
			badvaddr,badpaddr;
	uint32		fr[32];			/* 32 floating point regs */
	uint32		fcr31, facc;		/* Control/Status, Accumulator */
} irq_context_t;

/* A couple of architecture independent access macros. For PS2 these
   are a bit nastier because of the data widths. */
#define CONTEXT_128_TO_32(c) (*((uint32 *)&(c)))
#define CONTEXT_PC(c)	(CONTEXT_128_TO_32((c).pc))
#define CONTEXT_FP(c)	(CONTEXT_128_TO_32((c).r[30]))	/* $fp */
#define CONTEXT_SP(c)	(CONTEXT_128_TO_32((c).r[29]))	/* $sp */

/* Catchable exceptions -- the 0xf0 digit refers to the vector index (where
   the exception is vectered to) while the 0x0f digit is ExcCode. */
#define EXC_TLB_REFILL		0x0000
#define EXC_PERF_COUNTER	0x0010
#define EXC_DEBUG		0x0020
#define EXC_COMMON		0x0030
#define EXC_TLB_MODIFIED	0x0031
#define EXC_TLB_INVALID_IL	0x0032
#define EXC_TLB_INVALID_S	0x0033
#define EXC_ADDR_ERROR_IL	0x0034
#define EXC_ADDR_ERROR_S	0x0035
#define EXC_BUS_ERROR_IL	0x0036
#define EXC_BUS_ERROR_S		0x0037
#define EXC_SYSCALL		0x0038
#define EXC_BREAK		0x0039
#define EXC_COP_UNUSABLE	0x003b
#define EXC_OVERFLOW		0x003c
#define EXC_TRAP		0x003d
#define EXC_INTR		0x0040
#define EXC_INTR_0		0x0040		/* Used for INTC */
#define EXC_INTR_1		0x0041		/* Used for DMAC */

/* INT0-based interrupts; we encode the actual processor interrupt as the
   bottom byte here, and the top byte will be used as an index into a
   secondary table. This is somewhat like the ASIC module on the DC. */
#define EXC_INTR_GS		0x0040
#define EXC_INTR_SBUS		0x0140
#define EXC_INTR_VB_ON		0x0240		/* Vertical blank start */
#define EXC_INTR_VB_OFF		0x0340		/* Vertical blank end */
#define EXC_INTR_VIF0		0x0440
#define EXC_INTR_VIF1		0x0540
#define EXC_INTR_VU0		0x0640
#define EXC_INTR_VU1		0x0740
#define EXC_INTR_IPU		0x0840
#define EXC_INTR_TIMER0		0x0940
#define EXC_INTR_TIMER1		0x0a40
#define EXC_INTR_TIMER2		0x0b40
#define EXC_INTR_TIMER3		0x0c40
#define EXC_INTR_SFIFO		0x0d40		/* SFIFO transfer error */
#define EXC_INTR_VU0WD		0x0e40		/* VU0 watchdog */

/* INT1-based interrupts. */
#define EXC_INTR_DMAC		0x0041

/* This is a software-generated one (double-fault) for when an exception
   happens inside an ISR. */
#define EXC_DOUBLE_FAULT	0x00ff

/* Software-generated for unhandled exception */
#define EXC_UNHANDLED_EXC	0x00fe

/* The value of the timer IRQ */
#define TIMER_IRQ		EXC_INTR_TIMER0

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

/* Get the address of the current handler */
irq_handler irq_get_handler(irq_t source);

/* Set a global exception handler */
int irq_set_global_handler(irq_handler hnd);

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
	ptr_t routine, uint64 *args, int usermode);

/* Enable/Disable interrupts */
int irq_disable();
void irq_enable();
static inline void irq_enable_exc() { }		/* NOP on MIPS */
void irq_restore(int v);

/* Init routine */
int irq_init();

/* Shutdown */
void irq_shutdown();

__END_DECLS

#endif	/* __ARCH_IRQ_H */

