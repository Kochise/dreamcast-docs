/* ps2-load-ip

   main.c

   Copyright (c)2002 Dan Potter
   License: BSD

   $Id: go.S,v 1.4 2002/11/02 09:33:58 bardtx Exp $
*/

	.set noat
	.set noreorder

	.global go
	.global go_reboot
	.global sc_exit_post

	#include "asmregs.h"

	.bss
	.align 2
__go_save_sp:	.space 4
	
	.text

// Run a sub-program: we need to flush caches and then jump to the program.
go:
	// Save our ra, sp, gp, cp0 regs, and any callee-saved regs here
	addiu	sp,sp,-4*4
	sw	ra,0(sp)
	mfc0	at,cp0status
	sw	at,4(sp)
	mfc0	at,cp0config
	sw	at,8(sp)
	sw	gp,12(sp)

	addiu	sp,sp,-16*9
	sd	s0,0x00(sp)
	sd	s1,0x10(sp)
	sd	s2,0x20(sp)
	sd	s3,0x30(sp)
	sd	s4,0x40(sp)
	sd	s5,0x50(sp)
	sd	s6,0x60(sp)
	sd	s7,0x70(sp)
	sd	s8,0x80(sp)

	la	at,(__go_save_sp)
	sw	sp,(at)

	// Jump to the program
	jal	a0
	nop

	// Returned normally (they didn't call sc_exit, so we'll do it
	// for them ;)
	la	gp,_gp
	j	sc_exit
	nop

	// Restore regs
sc_exit_post:
	la	at,(__go_save_sp)
	lw	sp,(at)

	ld	s0,0x00(sp)
	ld	s1,0x10(sp)
	ld	s2,0x20(sp)
	ld	s3,0x30(sp)
	ld	s4,0x40(sp)
	ld	s5,0x50(sp)
	ld	s6,0x60(sp)
	ld	s7,0x70(sp)
	ld	s8,0x80(sp)
	addiu	sp,sp,16*9

	lw	ra,0(sp)
	lw	at,4(sp)
	mtc0	at,cp0status
	lw	at,8(sp)
	mtc0	at,cp0config
	lw	gp,12(sp)
	addiu	sp,sp,4*4
	
	jr	ra
	nop

// This pretty closely emulates a reset exception to try to convince
// the PS2 BIOS to start over (instead of a real power cycle...)
// XXX Doesn't function yet...
go_reboot:
	// Set Status.ERL=Status.BEV=1, Status.BEM=0
	li	$1,0x00400004
	mtc0	$1,cp0status
	sync.p

	// Set Config.DIE=ICE=DCE=NBE=BPE=0
	li	$1,2
	mtc0	$1,cp0config
	sync.p

	// Jump to 0xbfc00000
	li	$1,0xbfc00000
	jr	$1
	nop
