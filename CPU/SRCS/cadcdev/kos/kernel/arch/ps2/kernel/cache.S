//
// cache.S
// (c)2002 Dan Potter
//
// Cache maintenance for R5900
//
// Apparently this amazing chicken dance is required to guarantee that
// any newly written instructions will actually be properly fetched and
// executed next time around. This is modeled after eCos' approach.
//

	.set noreorder

	.text
	.global cache_flush_all

	#include <ps2/asmregs.h>

cache_flush_all:
// Step 1: disable interrupts (if they're enabled)
	addiu	sp,sp,-4
	sw	ra,(sp)

	jal	irq_disable	// Old value will be in v0
	nop

// Step 2: Index-writeback-invalidate for data cache
	.macro	iwid
	li	t0,0x80000000
	li	t1,0x80001000
1:
	// Invalidate 0x40 bytes of data cache
	sync.l
	cache	0x14,0(t0)
	sync.l
	cache	0x14,1(t0)
	sync.l

	// Move to the next line
	addiu	t0,0x40
	sltu	t2,t0,t1
	bne	zero,t2,1b
	nop

	.endm

	iwid

// Step 3: Disable both icache and dcache
	mfc0	t0,cp0config
	la	t1,(~0x30000)
	and	t0,t0,t1
	mtc0	t0,cp0config
	sync.p

// Step 4: Index-writeback-invalidate for data cache _again_
	iwid

// Step 5: Invalidate all of the instruction cache
	move	t0,zero
	li	t1,0x2000	// 8kb of instr cache
1:
	// Invalidate 0x40 bytes of instruction cache
	sync.l; sync.p
	cache	0x07,0(t0)
	sync.l; sync.p
	cache	0x07,1(t0)
	sync.l; sync.p

	// Move to the next line
	addiu	t0,0x40
	sltu	t2,t0,t1
	bne	zero,t2,1b
	nop

// Step 6: Re-enable both caches
	mfc0	t0,cp0config
	li	t1,0x30000
	or	t0,t0,t1
	mtc0	t0,cp0config
	sync.p

// Step 7: Re-enable interrupts if necessary
	move	a0,v0
	jal	irq_restore
	nop

// Step 8: ...
	lw	ra,(sp)
	addiu	sp,sp,4

// Step 9: Profit!
	jr	ra
	nop

	.ident	"KOS $Id: cache.S,v 1.2 2002/11/03 03:40:55 bardtx Exp $"

