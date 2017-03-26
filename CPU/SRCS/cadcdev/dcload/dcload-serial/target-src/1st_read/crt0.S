	.section .text
	.global	start
	.global _atexit
start:
	mov.l	setup_cache_k,r0
	mov.l	p2_mask,r1
	or	r1,r0
	jmp	@r0
	nop
setup_cache:
	mov.l	ccr_addr,r0
	mov.w	ccr_data,r1
	mov.l	r1,@r0
	mov.l	start_2_k,r0	
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	jmp	@r0	
	nop
start_2:		
	mov.l	old_stack_k,r14
	mov.l	r15,@r14
	mov.l	old_pr_k,r14
	sts	pr,r15
	mov.l	r15,@r14
	mov.l	stack_k,r15

	! zero out bss
	mov.l	edata_k,r0
	mov.l	end_k,r1
	mov	#0,r2
start_l:
	mov.l	r2,@r0
	add	#4,r0
	cmp/ge	r0,r1
	bt	start_l

	mov.l set_fpscr_k, r1
	jsr @r1
	mov #0,r4
	lds r3,fpscr

	! call the mainline	
	mov.l	main_k,r0
	jsr	@r0
	nop

	mov.l	old_pr_k,r14
	mov.l	@r14,r15
	lds	r15,pr
	mov.l	old_stack_k,r14
	mov.l	@r14,r15

_atexit:
	rts
	nop
	
	.align 4
set_fpscr_k:
	.long	___set_fpscr
stack_k:
	.long	_stack	
edata_k:
	.long	_edata
end_k:
	.long	_end
main_k:
	.long	_main
old_stack_k:
	.long	_old_stack
old_pr_k:
	.long	_old_pr
_old_stack:
	.long	0
_old_pr:
	.long	0
setup_cache_k:
	.long	setup_cache
start_2_k:	
	.long	start_2	
p2_mask:
	.long	0xa0000000
ccr_addr:
	.long	0xff00001c
ccr_data:
	.word	0x090b

	.align 4
		
#ifdef __ELF__
	.section .stack,"aw"
#else
	.section .stack
#endif

