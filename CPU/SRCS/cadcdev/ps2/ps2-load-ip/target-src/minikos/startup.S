/* ps2-load-ip

   startup.S
   Copyright (c)2002 Dan Potter
   License: BSD

   $Id: startup.S,v 1.5 2002/11/03 10:12:02 bardtx Exp $
*/
                    
// Adapted from KallistiOS for PS2/RTE

	.set noat
	.set noreorder

	.global _start
	.global arch_real_exit
	.global ps2lip_vectors

	#include "asmregs.h"

// Initial value for COP0 Status:
// - COP0,COP1 usable only in kernel
// - EI bit is enabled
// - All interrupts are masked
// - EI is off
cop0_status = 0x30010000

	.text
ps2lip_vectors:
	.word	0xdeadbeef	// 0xdeadbeef
	.word	0		// 1 if the PC console is enabled
	.word	sc_entry	// Syscalls will be routed to sc_entry
	.word	0		// Padding

// Pointers to all of the available syscalls (compatible with DC numbers)
sc_table:
	.word	sc_read			// 0
	.word	sc_write
	.word	sc_open
	.word	sc_close
	.word	sc_creat
	.word	sc_link			// 5
	.word	sc_unlink
	.word	sc_chdir
	.word	sc_chmod
	.word	sc_lseek
	.word	sc_fstat		// 10
	.word	sc_time
	.word	sc_stat
	.word	sc_utime
	.word	sc_gsconsprint
	.word	sc_exit			// 15
	.word	sc_opendir
	.word	sc_closedir
	.word	sc_readdir
	.word	sc_gethostinfo		// 19

	.space	32		// Padding

// Syscalls will be routed here
sc_entry:
	// a0 is the syscall id; we'll pull that and then scoot
	// all the other args back
	move	t0,a0
	move	a0,a1
	move	a1,a2
	move	a2,a3
	move	a3,zero

	// Get the actual address
	la	t1,(sc_table)
	sll	t0,t0,2
	add	t0,t0,t1
	lw	t1,(t0)

	// Save the prog's GP/RA and load ours
	addiu	sp,sp,-16*2
	sd	gp,0(sp)
	sd	ra,16(sp)
	la	gp,_gp

	// Jump the routine
	jalr	t1
	nop

	// Restore GP/RA and jump back
	ld	gp,0(sp)
	ld	ra,16(sp)
	addiu	sp,sp,16*2

	jr	ra
	nop

_start:
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

	// Save old $ra on old stack so we can get to it later
	addiu	sp,sp,-4
	sw	ra,0(sp)

	// Save the current stack
	la	$2,(__old_sp)
	sw	sp,($2)

	// Set a new stack
	move	sp,$2

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

	// Jump to the kernel main
	jal	arch_main
	nop

arch_real_exit:
	// Disable interrupts if they were enabled
	mfc0	t0,cp0status
	li	t1,~1
	and	t0,t0,t1
	mtc0	t0,cp0status
	sync.p

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

	/* Force the console back to telnet (for some reason KOS
	   triggers its flight-or-fight response, and in this weird
	   sort of passive aggressive way, it manages to do both by
	   switching consoles back to the non-functional GS input :) */
	jal	0x80f102b8	// net_io_assume_console
	nop

	// Similarly, it sometimes decides it doesn't have a net connect anymore
	la	$1,(0x80f1976c)
	li	$2,1
	sw	$2,($1)

	// Grab the old $ra and return
	lw	$31,0(sp)
	addiu	sp,sp,4
	jr	$31
	nop


	.bss

// A stack for us to use while not running a sub-program, and a place
// to store the old sp/cop0 regs during debugging via RedBoot.
	.align	4
__stack:
	.space	16384
__old_sp:
	.space	4
__old_cop0:
	.space	4*3



	.ident	"$Id: startup.S,v 1.5 2002/11/03 10:12:02 bardtx Exp $"
