/* KallistiOS ##version##

  entry.S
  (c)2002 Dan Potter

  IRQ entry point vectors and other such utilities

  These will all need to be copied down to the exception handler RAM
  before any exceptions can be processed.
*/

	.set noat
	.set noreorder

	.global _ps2ev_tlb_refill
	.global _ps2ev_tlb_refill_end
	.global _ps2ev_counter
	.global _ps2ev_counter_end
	.global _ps2ev_debug
	.global _ps2ev_debug_end
	.global _ps2ev_common
	.global _ps2ev_common_end
	.global _ps2ev_interrupt
	.global _ps2ev_interrupt_end
	.global irq_srt_addr
	.global irq_enable
	.global irq_disable
	.global irq_restore

	#include <ps2/asmregs.h>

	.text

// ------------------------ TLB Vector --------------------------- //

// We used la/jr in this and all the other handlers because this code
// will be moved down to low memory after boot -- so relative branches
// won't work here.
_ps2ev_tlb_refill:
	la	k0,(ev_common)
	jr	k0
	li	k1,0
_ps2ev_tlb_refill_end:

// ---------------------- Counter Vector ------------------------- //

_ps2ev_counter:
	la	k0,(ev_common)
	jr	k0
	li	k1,1
_ps2ev_counter_end:

// ----------------------- Debug Vector -------------------------- //

_ps2ev_debug:
	la	k0,(ev_common)
	jr	k0
	li	k1,2
_ps2ev_debug_end:

// ---------------------- Common Vector -------------------------- //

_ps2ev_common:
	la	k0,(ev_common)
	jr	k0
	li	k1,3
_ps2ev_common_end:

// --------------------- Interrupt Vector ------------------------ //

_ps2ev_interrupt:
	la	k0,(ev_common)
	jr	k0
	li	k1,4
_ps2ev_interrupt_end:

// ------------------------ Common Code -------------------------- //

#define GPR(x) ((x) * 16)
#define FPR(x) ((x) * 4)

// This will be called from the above handlers to save the actual context
// state and jump into the C-based IRQ processing.
ev_common:
	la	k0,(irq_srt_addr)	// Get the location of the reg store
	lw	k0,0(k0)

	// Save GPRs 1 - 15
	.irp	i,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15
	sq	$\i,GPR(\i)(k0)
	.endr
	
	// Save GPRs 16 - 31
	.irp	i,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31
	sq	$\i,GPR(\i)(k0)
	.endr

	// Scoot up to the next part
	addiu	k0,k0,16*32

	// Save lo and hi
	mflo	k1
	sd	k1,0(k0)
	mflo1	k1
	sd	k1,8(k0)
	mfhi	k1
	sd	k1,16(k0)
	mfhi1	k1
	sd	k1,24(k0)

	// Save sa
	mfsa	k1
	sd	k1,32(k0)

	// Save relevant COP0 regs
	mfc0	v0,cp0status
	sw	v0,40(k0)
	mfc0	k1,cp0epc
	sw	k1,44(k0)
	mfc0	k1,cp0cause
	sw	k1,48(k0)
	mfc0	k1,cp0config
	sw	k1,52(k0)
	mfc0	k1,cp0badvaddr
	sw	k1,56(k0)
	mfc0	k1,cp0badpaddr
	sw	k1,60(k0)

	// Is the FPU enabled? If not, don't bother with this part...
	srl	v0,v0,16
	andi	v0,v0,0x2000
	beqz	v0,1f
	nop

	// Scoot up to the next part
	addiu	k0,k0,64

	// Save FPRs 0 - 15
	.irp	i,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15
	swc1	$\i,FPR(\i)(k0)
	.endr
	
	// Save FPRs 16 - 31
	.irp	i,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31
	swc1	$\i,FPR(\i)(k0)
	.endr

	// Save FCR31 and ACC
	cfc1	k1,$31
	sw	k1,32*4(k0)
	// XXX: How do we save ACC? msub.s with zeroed regs?
	
1:
	// Jump up into the C-level handler
	jal	irq_handle_exception
	nop

	// Ok, now put everything back in reverse order... //////////////////////
	la	k1,(irq_srt_addr)	// Get the location of the reg store
	lw	k0,0(k1)
	addiu	k0,k0,576

	// Is the FPU enabled? If not, don't bother with this part...
	mfc0	v0,cp0status
	srl	v0,v0,16
	andi	v0,v0,0x2000
	beqz	v0,2f
	nop

	// Load FPRs 0 - 15
	.irp	i,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15
	lwc1	$\i,FPR(\i)(k0)
	.endr
	
	// Load FPRs 16 - 31
	.irp	i,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31
	lwc1	$\i,FPR(\i)(k0)
	.endr

	// Load FCR31 and ACC
	lw	k1,32*4(k0)
	ctc1	k1,$31
	// XXX: How do we load ACC?
	
2:
	// Scoot back to the next part
	addiu	k0,k0,-64

	// Save lo and hi
	ld	k1,0(k0)
	mtlo	k1
	ld	k1,8(k0)
	mtlo1	k1
	ld	k1,16(k0)
	mthi	k1
	ld	k1,24(k0)
	mthi1	k1

	// Save sa
	ld	k1,32(k0)
	mtsa	k1

	// Load relevant COP0 regs
	// We don't re-load everything we saved here because several of
	// the saved regs are only relevant in an informational way (i.e.,
	// for the kernel to decide what to do).
	lw	k1,40(k0)
	mtc0	k1,cp0status
	lw	k1,44(k0)
	mtc0	k1,cp0epc
	lw	k1,48(k0)
	mtc0	k1,cp0cause
	sync.p

	// Scoot bacl to the next part
	addiu	k0,k0,-16*32

	// Load GPRs 1 - 15
	.irp	i,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15
	lq	$\i,GPR(\i)(k0)
	.endr
	
	// Load GPRs 16 - 31
	.irp	i,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31
	lq	$\i,GPR(\i)(k0)
	.endr

	// Return from the exception
	sync.l	// In case it was an interrupt
	eret
	nop


// Call to disable external interrupts. Note that unlike the DC, it is
// not possible to disable exceptions. Yer stuck with 'em. :) Returns
// a value suitable to pass to irq_restore.
//
// DI and EI don't seem to function.. :(
//
irq_disable:
	la	t1,(~1)
	mfc0	t0,cp0status
	and	t0,t0,t1
	mtc0	t0,cp0status
	sync.p
	move	v0,t0
	andi	v0,v0,1
	jr	ra
	nop

// Call to enable external interrupts. Returns a value suitable to pass
// to irq_restore.
irq_enable:
	mfc0	v0,cp0status
	move	t0,v0
	andi	v0,v0,1
	ori	t0,t0,1
	mtc0	t0,cp0status
	sync.p
	jr	ra
	nop

// Takes the value returned from either irq_disable or irq_enable and sets
// the interrupt state back to that state.
irq_restore:
	mfc0	at,cp0status
	or	at,at,a0
	mtc0	at,cp0status
	sync.p
	jr	ra
	nop

// IRQ save-regs pointer
	.bss
	.align 2
irq_srt_addr:	.space	4

	.ident "KOS $Id: entry.S,v 1.2 2002/11/03 03:40:55 bardtx Exp $"
