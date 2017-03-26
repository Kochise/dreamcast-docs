	! Simple C startup strap
	!
	! Just enables cache, clears BSS and jumps to main
	!

	.globl	start
	
	.text

start:	
	stc	sr,r0
	or	#0xf0,r0
	ldc	r0,sr
	! First, make sure to run in the P2 area
	mov.l	setup_cache_addr,r0
	mov.l	p2_mask,r1
	or	r1,r0
	jmp	@r0
	nop
setup_cache:
	! Now that we are in P2, it's safe
	! to enable the cache
	mov.l	ccr_addr,r0
	mov.w	ccr_data,r1
	mov.l	r1,@r0
	! After changing CCR, eight instructions
	! must be executed before it's safe to enter
	! a cached area such as P1
	mov.l	initaddr,r0	! 1
	mov	#0,r1		! 2
	nop			! 3
	nop			! 4
	nop			! 5
	nop			! 6
	nop			! 7
	nop			! 8
	jmp	@r0		! go
	mov	r1,r0


	! Clear BSS section
init:
	mov.l	bss_start_addr,r0
	mov.l	bss_end_addr,r2
	mov	#3,r1
	add	r1,r0
	add	r1,r2
	not	r1,r1
	and	r1,r0
	and	r1,r2
	sub	r0,r2
	shlr	r2
	shlr	r2
	mov	#0,r1
.loop:	dt	r2
	mov.l	r1,@r0
	bf/s	.loop
	add	#4,r0
	mov	#0,r2
	mov	#0,r1
	mov.l	mainaddr,r0
	jmp	@r0
	mov	r1,r0

	
	.align	2
mainaddr:
	.long	_main
initaddr:
	.long	init
bss_start_addr:
	.long	__bss_start
bss_end_addr:
	.long	_end
p2_mask:
	.long	0xa0000000
setup_cache_addr:
	.long	setup_cache
ccr_addr:
	.long	0xff00001c
ccr_data:
	.word	0x090b


	.end

