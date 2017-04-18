	.global	_vbuf
	.global	_matrix
	.section .bss

	.align	5
_vbuf:
	.space 4096*96

	.align	5
_matrix:
	.space 4*16*8
