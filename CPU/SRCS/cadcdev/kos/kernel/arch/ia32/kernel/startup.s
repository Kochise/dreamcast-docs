# KallistiOS ##version##
#
# arch/ia32/kernel/startup.s
# Copyright (C)2003 Dan Potter
#
# This will be the first thing executed in protected mode after the boot
# loader. We expect to be loaded at 0x10000 like a Linux zImage.
#

	.text
	.global _start

_start:
	# Switch to a bigger, more luxurious stack, right under us.
	movw	%ds,%ax
	movw	%ax,%ss
	movl	$0x10000,%esp
	
	# Relocate our GDT
	call	_gdt_init

	# Jump to main
	jmp	arch_main

	ret
