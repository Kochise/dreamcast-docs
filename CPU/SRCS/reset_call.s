	.section .text
	.global _reset_call
	
_reset_call:

	stc	sr,r0
	mov.l	dc_sr_data,r1
	and	r1,r0
	ldc	r0,sr		! 0xdfffffff mask
	mov.l	dc_zero_data,r0
	lds	r0,mach
	mov.l	dc_other_data,r0	! 0x28 ?? why sould we put this value ??
	lds	r0,macl
	mov.l	dc_zero_data,r0
	lds	r0,pr
	mov.l	dc_vbr_data,r0	! 0x8c00f400 exception handler
	ldc	r0,vbr
	mov.l	dc_gbr_data,r0	! 0x8c000000 base address
	ldc	r0,gbr
	mov.l	dc_spc_data,r0	! 0xac010000 exec address
	ldc	r0,spc
	mov.l	dc_ssr_data,r0	! 0x700000f0
	ldc	r0,ssr
	mov.l	gdGdcReset,r0	! 0x8c0100a0 = gdGdcReset vector ? maybe :)
	mov.l	dc_sct_data,r1	! 0x800	= 2048 sector mode
	mov.l	dc_sct_data,r2
	mov.l	dc_zero_data,r3
	mov.l	dc_zero_data,r4
	mov.l	dc_zero_data,r5
	mov.l	dc_zero_data,r6
	mov.l	dc_zero_data,r7
	mov.l	dc_zero_data,r8
	mov.l	dc_zero_data,r9
	mov.l	dc_zero_data,r10
	mov.l	dc_zero_data,r11
	mov.l	dc_zero_data,r12
	mov.l	dc_zero_data,r13
	mov.l	dc_zero_data,r14
	mov.l	dc_vbr_data,r15	! 0x8c00f400 copy of exception handler vector
	rte
	nop
	
	.align 4
	
dc_sr_data:
	.long 0xdfffffff
dc_vbr_data:
	.long 0x8c00f400
dc_gbr_data:
	.long 0x8c000000
dc_spc_data:
	.long 0xac010000
dc_ssr_data:
	.long 0x700000f0
gdGdcReset:
	.long 0x8c0100a0
dc_sct_data:
	.long 0x800
dc_zero_data:
	.long 0x0
dc_other_data:
	.long 0x28