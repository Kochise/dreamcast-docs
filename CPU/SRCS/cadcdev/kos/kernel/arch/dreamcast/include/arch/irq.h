/* KallistiOS ##version##

   arch/dreamcast/include/irq.h
   (c)2000-2001 Dan Potter

   $Id: irq.h,v 1.9 2003/02/14 06:33:47 bardtx Exp $
  
*/

#ifndef __ARCH_IRQ_H
#define __ARCH_IRQ_H

#include <sys/cdefs.h>
__BEGIN_DECLS

#include <arch/types.h>

/* The number of bytes required to save thread context. This should
   include all general CPU registers, FP registers, and status regs (even
   if not all of these are actually used). */
#define REG_BYTE_CNT 256			/* Currently really 228 */

/* Architecture-specific structure for holding the processor state (register
   values, etc). The size of this structure should be less than or equal
   to the above value. */
typedef struct irq_context {
	uint32		r[16];			/* 16 general purpose regs */
	uint32		pc, pr, gbr, vbr;	/* Various system words */
	uint32		mach, macl, sr;
	uint32		frbank[16];		/* Secondary float regs */
	uint32		fr[16];			/* Primary float regs */
	uint32		fpscr, fpul;		/* Float control regs */
} irq_context_t;

/* A couple of architecture independent access macros */
#define CONTEXT_PC(c)	((c).pc)
#define CONTEXT_FP(c)	((c).r[14])
#define CONTEXT_SP(c)	((c).r[15])
#define CONTEXT_RET(c)	((c).r[0])

/* Dreamcast-specific exception codes.. use these when getting or setting an
   exception code value. */

/* Reset type */
#define EXC_RESET_POWERON	0x0000	/* Power-on reset */
#define EXC_RESET_MANUAL	0x0020	/* Manual reset */
#define EXC_RESET_UDI		0x0000	/* Hitachi UDI reset */
#define EXC_ITLB_MULTIPLE	0x0140	/* Instruction TLB multiple hit */
#define EXC_DTLB_MULTIPLE	0x0140	/* Data TLB multiple hit */

/* Re-Execution type */
#define EXC_USER_BREAK_PRE	0x01e0	/* User break before instruction */
#define EXC_INSTR_ADDRESS	0x00e0	/* Instruction address */
#define EXC_ITLB_MISS		0x0040	/* Instruction TLB miss */
#define EXC_ITLB_PV		0x00a0	/* Instruction TLB protection violation */
#define EXC_ILLEGAL_INSTR	0x0180	/* Illegal instruction */
#define EXC_SLOT_ILLEGAL_INSTR	0x01a0	/* Slot illegal instruction */
#define EXC_GENERAL_FPU		0x0800	/* General FPU exception */
#define EXC_SLOT_FPU		0x0820	/* Slot FPU exception */
#define EXC_DATA_ADDRESS_READ	0x00e0	/* Data address (read) */
#define EXC_DATA_ADDRESS_WRITE	0x0100	/* Data address (write) */
#define EXC_DTLB_MISS_READ	0x0040	/* Data TLB miss (read) */
#define EXC_DTLB_MISS_WRITE	0x0060	/* Data TLB miss (write) */
#define EXC_DTLB_PV_READ	0x00a0	/* Data TLB P.V. (read) */
#define EXC_DTLB_PV_WRITE	0x00c0	/* Data TLB P.V. (write) */
#define EXC_FPU			0x0120	/* FPU exception */
#define EXC_INITIAL_PAGE_WRITE	0x0080	/* Initial page write exception */

/* Completion type */
#define EXC_TRAPA		0x0160	/* Unconditional trap */
#define EXC_USER_BREAK_POST	0x01e0	/* User break after instruction */

/* Interrupt (completion type) */
#define EXC_NMI			0x01c0	/* Nonmaskable interrupt */
#define EXC_IRQ0		0x0200	/* External IRL requests */
#define EXC_IRQ1		0x0220
#define EXC_IRQ2		0x0240
#define EXC_IRQ3		0x0260
#define EXC_IRQ4		0x0280
#define EXC_IRQ5		0x02a0
#define EXC_IRQ6		0x02c0
#define EXC_IRQ7		0x02e0
#define EXC_IRQ8		0x0300
#define EXC_IRQ9		0x0320
#define EXC_IRQA		0x0340
#define EXC_IRQB		0x0360
#define EXC_IRQC		0x0380
#define EXC_IRQD		0x03a0
#define EXC_IRQE		0x03c0
#define EXC_TMU0_TUNI0		0x0400	/* TMU0 underflow */
#define EXC_TMU1_TUNI1		0x0420	/* TMU1 underflow */
#define EXC_TMU2_TUNI2		0x0440	/* TMU2 underflow */
#define EXC_TMU2_TICPI2		0x0460	/* TMU2 input capture */
#define EXC_RTC_ATI		0x0480
#define EXC_RTC_PRI		0x04a0
#define EXC_RTC_CUI		0x04c0
#define EXC_SCI_ERI		0x04e0	/* SCI Error receive */
#define EXC_SCI_RXI		0x0500	/* Receive ready */
#define EXC_SCI_TXI		0x0520	/* Transmit ready */
#define EXC_SCI_TEI		0x0540	/* Transmit error */
#define EXC_WDT_ITI		0x0560	/* Watchdog timer */
#define EXC_REF_RCMI		0x0580
#define EXC_REF_ROVI		0x05a0
#define EXC_UDI			0x0600	/* Hitachi UDI */
#define EXC_GPIO_GPIOI		0x0620
#define EXC_DMAC_DMTE0		0x0640
#define EXC_DMAC_DMTE1		0x0660
#define EXC_DMAC_DMTE2		0x0680
#define EXC_DMAC_DMTE3		0x06a0
#define EXC_DMA_DMAE		0x06c0
#define EXC_SCIF_ERI		0x0700	/* SCIF Error receive */
#define EXC_SCIF_RXI		0x0720
#define EXC_SCIF_BRI		0x0740
#define EXC_SCIF_TXI		0x0760

/* This is a software-generated one (double-fault) for when an exception
   happens inside an ISR. */
#define EXC_DOUBLE_FAULT	0x0ff0

/* Software-generated for unhandled exception */
#define EXC_UNHANDLED_EXC	0x0fe0

/* The following are a table of "type offsets" (see the Hitachi PDF).
   These are the 0x000, 0x100, 0x400, and 0x600 offsets. */
#define EXC_OFFSET_000		0
#define EXC_OFFSET_100		1
#define EXC_OFFSET_400		2
#define EXC_OFFSET_600		3

/* The value of the timer IRQ */
#define TIMER_IRQ		EXC_TMU0_TUNI0

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

/* Set or remove a trapa handler */
int trapa_set_handler(irq_t code, irq_handler hnd);

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
void irq_create_context(irq_context_t *context, uint32 stack_pointer,
	uint32 routine, uint32 *args, int usermode);

/* Enable/Disable interrupts */
int irq_disable();		/* Will leave exceptions enabled */
void irq_enable();		/* Enables all ints including external */
void irq_restore(int v);

/* Init routine */
int irq_init();

/* Shutdown */
void irq_shutdown();

__END_DECLS

#endif	/* __ARCH_IRQ_H */

