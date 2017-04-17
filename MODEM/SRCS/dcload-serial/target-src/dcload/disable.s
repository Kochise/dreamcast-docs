	.section .text
	.global _disable_cache
	
_disable_cache:
	mov.l   disable_cache_k,r0
        mov.l   p2_mask,r1
        or      r1,r0
        jmp     @r0
        nop
disable_cache:
	mov.l	ccr_addr,r0
	mov.l	ccr_data_k,r1
	mov.l	@r1,r1
	mov.l	r1,@r0
	nop
        nop
        nop
        nop
        nop
        nop
        nop
        nop
	rts
        nop

	.align 4
		
disable_cache_k:
        .long   disable_cache
p2_mask:
        .long   0xa0000000
ccr_addr:
        .long   0xff00001c
ccr_data_k:
	.long	ccr_data
ccr_data:
	.long	0x00000808
