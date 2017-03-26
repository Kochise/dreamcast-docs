! KallistiOS ##version##
!
! startup.s
! (c)2000-2001 Dan Potter
!
! This file must appear FIRST in your linking order, or your program won't
! work correctly as a raw binary.
!
! This is very loosely based on Marcus' crt0.s/startup.s
!

.globl start
.globl _start
.globl _arch_real_exit
.globl _syscall		! From C
.globl _loader_magic

_start:
start:
	! Jump over the magic and syscalls
	bra	real_start
	nop

	! Pretend we are dcload
_loader_magic:
	.long	0xdeadbeef

	! Our syscall
	.long	_syscall

real_start:
	! Disable interrupts (if they're enabled)
	mov.l	old_sr_addr,r0
	stc	sr,r1
	mov.l	r1,@r0
	mov.l	init_sr,r0
	ldc	r0,sr

	! Run in the P2 area
	mov.l	setup_cache_addr,r0
	mov.l	p2_mask,r1
	or	r1,r0
	jmp	@r0
	nop

setup_cache:
	! Now that we are in P2, it's safe to enable the cache
	! Check to see if we should enable OCRAM.
	mov.l	ccr_addr,r0
	mov.l	ccr_data,r1
	mov.l	r1,@r0

	! After changing CCR, eight instructions must be executed before
	! it's safe to enter a cached area such as P1
	nop			! 1
	nop			! 2
	nop			! 3
	nop			! 4
	nop			! 5 (d-cache now safe)
	nop			! 6
	mov.l	init_addr,r0	! 7
	mov	#0,r1		! 8
	jmp	@r0		! go
	mov	r1,r0
	nop

init:
	! Save old PR on old stack so we can get to it later
	sts.l	pr,@-r15

	! Save the current stack, and set a new stack (higher up in RAM)
	mov.l	old_stack_addr,r0
	mov.l	r15,@r0
	mov.l	new_stack,r15

	! Save VBR
	mov.l	old_vbr_addr,r0
	stc	vbr,r1
	mov.l	r1,@r0

	! Setup a sentinel value for frame pointer in case we're using
	! FRAME_POINTERS for stack tracing.
	mov	#-1,r14

	! Jump to the kernel main
	mov.l	main_addr,r0
	jsr	@r0
	nop

	! Program can return here (not likely) or jump here directly
	! from anywhere in it to go straight back to the monitor
_arch_real_exit:
	! Reset SR
	mov.l	old_sr,r0
	ldc	r0,sr

	! Disable MMU, invalidate TLB
	mov	#4,r0
	mov.l	mmu_addr,r1
	mov.l	r0,@r1

	! Wait (just in case)
	nop				! 1
	nop				! 2
	nop				! 3
	nop				! 4
	nop				! 5
	nop				! 6
	nop				! 7
	nop				! 8
	
	! Restore VBR
	mov.l	old_vbr,r0
	ldc	r0,vbr

	! Set back the stack and return (presumably to a serial debug)
normal_exit:
	mov.l	old_stack,r15
	lds.l	@r15+,pr
	rts
	nop

! Misc variables
	.align	2
setup_cache_addr:
	.long	setup_cache
init_addr:
	.long	init
old_sr_addr:
	.long	old_sr
old_sr:
	.long	0
old_vbr_addr:
	.long	old_vbr
old_vbr:
	.long	0
init_sr:
	.long	0x500000f0
old_stack_addr:
	.long	old_stack
old_stack:
	.long	0
new_stack:
	.long	_start + 0xc000
p2_mask:
	.long	0xa0000000
main_addr:
	.long	_arch_main
mmu_addr:
	.long	0xff000010
ccr_addr:
	.long	0xff00001c
ccr_data:
	.long	0x0000090b
