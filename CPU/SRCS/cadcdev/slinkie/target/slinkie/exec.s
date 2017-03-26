!
! slinkie/exec.s
! Copyright (C)2004 Dan Potter
!

.globl _exec
.globl _exec_exit

! int exec(uint32 addr, int args, char ** argv);
_exec:
	! Save PR
	sts.l	pr,@-r15

	! Save a bunch of registers
	mov.l	r8,@-r15
	mov.l	r9,@-r15
	mov.l	r10,@-r15
	mov.l	r11,@-r15
	mov.l	r12,@-r15
	mov.l	r13,@-r15
	mov.l	r14,@-r15

	! Disable interrupts (if they're enabled)
	mov.l	old_sr_addr,r0
	stc	sr,r1
	mov.l	r1,@r0
	mov.l	init_sr,r0
	ldc	r0,sr

	! Save the old stack pointer
	mov.l	old_sp_addr,r0
	mov.l	r15,@r0

	! Run in the P2 area
	mov.l	setup_cache1_addr,r0
	mov.l	p2_mask,r1
	or	r1,r0
	jmp	@r0
	nop

setup_cache1:
	! Now that we are in P2, it's safe to disable the cache
	mov.l	ccr_addr,r0
	mov.l	ccr_data_dis,r1
	mov.l	r1,@r0

	! After changing CCR, eight instructions must be executed.
	! it's safe to enter a cached area such as P1
	nop			! 1
	nop			! 2
	nop			! 3
	nop			! 4
	nop			! 5 (d-cache now safe)
	nop			! 6
	nop			! 7
	nop			! 8

	! Load up FPSCR
	mov.l	init_fpscr,r0
	lds	r0,fpscr  

	! Shift parameters
	mov	r4,r0
	mov	r5,r4
	mov	r6,r5

	! Call the function
	jsr	@r0
	nop

_exec_exit:
	! Re-enable the cache. Make sure we're in P2 again.
	mov.l	setup_cache2_addr,r0
	mov.l	p2_mask,r1
	or	r1,r0
	jmp	@r0
	nop

setup_cache2:
	! Now that we are in P2, it's safe to enable the cache
	mov.l	ccr_addr,r0
	mov.l	ccr_data_en,r1
	mov.l	r1,@r0

	! After changing CCR, eight instructions must be executed.
	! it's safe to enter a cached area such as P1
	nop			! 1
	nop			! 2
	nop			! 3
	nop			! 4
	nop			! 5 (d-cache now safe)
	nop			! 6
	nop			! 7
	nop			! 8

	! Get our stack back
	mov.l	old_sp,r15

	! Restore a bunch of registers
	mov.l	@r15+,r14
	mov.l	@r15+,r13
	mov.l	@r15+,r12
	mov.l	@r15+,r11
	mov.l	@r15+,r10
	mov.l	@r15+,r9
	mov.l	@r15+,r8

	! Set our SR back
	mov.l	old_sr,r1
	ldc	r1,sr

	! Restore PR and return to the caller
	lds.l	@r15+,pr
	rts
	nop

	.align	2
setup_cache1_addr:
	.long	setup_cache1
setup_cache2_addr:
	.long	setup_cache2
old_sp_addr:
	.long	old_sp
old_sp:
	.long	0
old_sr_addr:
	.long	old_sr
old_sr:
	.long	0
init_sr:
	.long	0x500000f0
init_fpscr:
	.long	0x40001
p2_mask:
	.long	0xa0000000
ccr_addr:
	.long	0xff00001c
ccr_data_dis:
	.long	0x00000808
ccr_data_en:
	.long	0x0000090b
