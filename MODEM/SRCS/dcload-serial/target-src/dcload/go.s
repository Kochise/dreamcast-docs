	.section .text
	.global _go
	
_go:
	mov.l	stack_addr_k,r0
	mov.l	@r0,r15
	mov.l	entry_addr_k,r0
	mov.l	@r0,r0
	lds	r0,pr
	mov.l	sr_data_k,r0
	mov.l	@r0,r0
	ldc	r0,sr
	mov.l	vbr_data_k,r0
	mov.l	@r0,r0
	ldc	r0,vbr
	mov.l	fpscr_data_k,r0
	mov.l	@r0,r0
	lds	r0,fpscr
	mov	#0,r0
	mov	r0,r1
	mov	r0,r2
	mov	r0,r3
	mov	r0,r5
	mov	r0,r6
	mov	r0,r7
	mov	r0,r8
	mov	r0,r9
	mov	r0,r10
	mov	r0,r11
	mov	r0,r12
	mov	r0,r13
	mov	r0,r14
	jmp	@r4
	mov	r0,r4

	.align 4
stack_addr_k:
	.long	stack_addr
stack_addr:
	.long	0x8c00f400
entry_addr_k:
	.long	entry_addr
entry_addr:
	.long	0x8c004000
sr_data_k:
	.long	sr_data
sr_data:
	.long	0x600000f0
vbr_data_k:
	.long	vbr_data
vbr_data:
	.long	0x8c00f400
fpscr_data_k:
	.long	fpscr_data
fpscr_data:
	.long	0x40001
	