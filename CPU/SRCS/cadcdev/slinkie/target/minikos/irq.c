/* KallistiOS ##version##

   arch/dreamcast/kernel/irq.c
   Copyright (C)2000,2001,2004 Dan Potter
*/

/* This module contains low-level handling for IRQs and related exceptions. */

#include <string.h>
#include <stdio.h>
#include <arch/types.h>
#include <arch/irq.h>
#include <dc/scif.h>

CVSID("$Id: irq.c,v 1.12 2003/02/14 06:33:47 bardtx Exp $");

/* Default IRQ context location */
static irq_context_t irq_context_default;

/* Print a kernel panic reg dump */
extern irq_context_t *irq_srt_addr;
void irq_dump_regs(int code, int evt) {
	uint32 *regs = irq_srt_addr->r;
	/* dbglog(DBG_DEAD, "Unhandled exception: PC %08lx, code %d, evt %04x\n",
		irq_srt_addr->pc, code, (uint16)evt);
	dbglog(DBG_DEAD, " R0-R7: %08lx %08lx %08lx %08lx %08lx %08lx %08lx %08lx\n",
		regs[0], regs[1], regs[2], regs[3], regs[4], regs[5], regs[6], regs[7]);
	dbglog(DBG_DEAD, " R8-R15: %08lx %08lx %08lx %08lx %08lx %08lx %08lx %08lx\n",
		regs[8], regs[9], regs[10], regs[11], regs[12], regs[13], regs[14], regs[15]);
	dbglog(DBG_DEAD, " SR %08lx PR %08lx\n", irq_srt_addr->sr, irq_srt_addr->pr);
	arch_stk_trace_at(regs[14], 0); */
	/* dbgio_printf(" Vicinity code ");
	dbgio_printf(" @%08lx: %04x %04x %04x %04x %04x\n",
		srt_addr->pc-4, *((uint16*)(srt_addr->pc-4)), *((uint16*)(srt_addr->pc-2)),
		*((uint16*)(srt_addr->pc)), *((uint16*)(srt_addr->pc+2)), *((uint16*)(srt_addr->pc+4))); */
}

/* The C-level routine that processes context switching and other
   types of interrupts. NOTE: We are running on the stack of the process
   that was interrupted! */
void irq_handle_exception(int code) {
	/* Get the exception code */
	volatile uint32 *expevt = (uint32*)0xff000024;
	volatile uint32 *intevt = (uint32*)0xff000028;
	uint32 evt = 0;

	/* If it's a code 0, well, we shouldn't be here. */
	// if (code == 0) panic("spurious RESET exception");
	
	/* If it's a code 1 or 2, grab the event from expevt. */
	if (code == 1 || code == 2) evt = *expevt;
	
	/* If it's a code 3, grab the event from intevt. */
	if (code == 3) evt = *intevt;

	irq_dump_regs(code, evt);

	while(1)
		;
}

extern void irq_vma_table();

/* Init routine */
int irq_init() {
	/* Make sure interrupts are disabled */
	irq_disable();

	irq_srt_addr = &irq_context_default;

	/* Set VBR to our exception table above, but don't enable
	   exceptions and IRQs yet. */
	asm("	! Set VBR\n"
	    "	mov.l	_vbr_addr,r0\n"
	    "	ldc	r0,vbr\n"
	    "	bra	_after_vbr\n"
	    "	nop\n"
	    "	.align 2\n"
	"_vbr_addr:\n"
	    "	.long	_irq_vma_table - 0x100\n"
	"_after_vbr:\n");

	return 0;
}
