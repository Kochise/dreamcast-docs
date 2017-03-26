!
! 1st_read/cache.s
! Copyright (C)2004 Dan Potter
!

.globl start
start:
	! Run in the P2 area
	mov.l	setup_cache1_addr,r0
	mov.l	p2_mask,r1
	or	r1,r0
	jmp	@r0
	nop

	.align	2
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

	mov.l	start_addr,r0
	jmp	@r0
	nop

	.align	2
start_addr:
	.long	_start
setup_cache1_addr:
	.long	setup_cache1
p2_mask:
	.long	0xa0000000
ccr_addr:
	.long	0xff00001c
ccr_data_dis:
	.long	0x00000808
