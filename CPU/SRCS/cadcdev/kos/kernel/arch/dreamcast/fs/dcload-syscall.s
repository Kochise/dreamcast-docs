! KallistiOS ##version##
!
! dcload-syscall.s
! (c)2000-2001 Andrew Kieschnick
!
! $Id: dcload-syscall.s,v 1.1.1.1 2001/09/26 07:05:11 bardtx Exp $
!

	.section .text
	.global	_dcloadsyscall
	
_dcloadsyscall:
	mov.l dcloadsyscall_k,r0
	mov.l @r0,r0
	jmp @r0
	nop
	
.align 4
dcloadsyscall_k:
	.long	0x8c004008
	
