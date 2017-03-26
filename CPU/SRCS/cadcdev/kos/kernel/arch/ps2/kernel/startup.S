/* KallistiOS ##version##

 startup.s
 (c)2002 Dan Potter

 Unlike the DC port, there's no need for this to appear at any
 particular place in your binary as long as you're loading an ELF file. */


	.set noat
	.set noreorder

	.global _start
	.global arch_real_exit

	#include <ps2/asmregs.h>

	.text

// Where we'll put our main stack
stack_addr = 0x81ff0000

// Initial value for COP0 Status:
// - COP0,COP1 usable only in kernel
// - EI bit is enabled
// - All interrupts are unmasked
// - EI is off (so no interrupts will happen)
cop0_status = 0x30018C00
// cop0_status = 0x30010000

// Initial value for COP0 Config
// cop0_config =

_start:
	// Save old $ra and $gp on old stack so we can get to them later
	addiu	sp,sp,-4*2
	sw	ra,0(sp)
	sw	gp,4(sp)

	// Save the current stack
	la	$2,(__old_sp)
	sw	sp,($2)

	// Set a new stack (high up in RAM)
	li	sp,stack_addr

	// Save the old exception vectors (in case we write over them)
	la	$2,(__old_vectors)
	la	$3,(0x80000000)
	li	$4,0x280/16
1:
	nop
	nop
	lq	$1,($3)
	addiu	$4,$4,-1
	sq	$1,($2)
	addiu	$2,$2,16
	bne	$4,$0,1b
	addiu	$3,$3,16

	// Save important COP0 regs that we'll tweak; this list will
	// probably grow over time.
	la	$2,(__old_cop0)
	mfc0	$1,$12		// Status
	sw	$1,0($2)
	mfc0	$1,$13		// Cause
	sw	$1,4($2)
	mfc0	$1,$16		// Config
	sw	$1,8($2)

	// Setup some COP0 reg values now (including disabling
	// external interrupts)
	li	$1,cop0_status
	mtc0	$1,$12
	sync.p

	// Load our GP
	la	gp,_gp

	// Clear BSS
	la	$2,(_fbss)
	la	$3,(_end)
1:
	nop
	nop
	sq	$0,($2)
	sltu	$1,$2,$3
	bne	$1,$0,1b
	addiu	$2,$2,16

	// Jump to the kernel main
	jal	arch_main
	nop

arch_real_exit:
	// Disable interrupts if they were enabled
	jal	irq_disable
	nop

	// Reset exception vectors
	la	$2,(__old_vectors)
	la	$3,(0x80000000)
	li	$4,0x280/16
1:
	nop
	nop
	lq	$1,($2)
	addiu	$2,$2,16
	addiu	$4,$4,-1
	sq	$1,($3)
	bne	$4,$0,1b
	addiu	$3,$3,16

	// Flush the d/i-cache
	jal	cache_flush_all
	nop

	// Set back the old stack
	la	$2,(__old_sp)
	lw	sp,($2)

 	// Reset COP0 values
	la	$2,(__old_cop0)
	lw	$1,0($2)
	mtc0	$1,$12		// Status
	sync.p
	lw	$1,4($2)
	mtc0	$1,$13		// Cause
	sync.p
	lw	$1,8($2)
	mtc0	$1,$16		// Config
	sync.p

	// Grab the old $ra and $gp, and return
	lw	ra,0(sp)
	lw	gp,4(sp)
	addiu	sp,sp,4*2
	jr	ra
	nop


//	.data

// We'll store the old stack pointer here
	.align	2
__old_sp:
	.space	4

// Store the old exception vectors here
	.align	4
__old_vectors:
	.space	0x280

// Store old COP0 registers here
	.align	2
__old_cop0:
	.space	4*3

	.ident	"KOS $Id: startup.S,v 1.2 2002/11/03 03:40:55 bardtx Exp $"
