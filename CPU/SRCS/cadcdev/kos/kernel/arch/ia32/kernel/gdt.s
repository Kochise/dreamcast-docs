# KallistiOS ##version##
#
# arch/ia32/kernel/gdt.s
# Copyright (C)2003 Dan Potter
#
# Global Descriptor Table handling
#
# Our usage of segments is very simplistic, so we pretty much just set up
# the GDT and ignore it.
#

	.data
	.align	32

# We'll place the new GDT here
gdt:
	.zero	16*8

gdt_info:
	.zero	6

	.text
	.global _gdt_init


# We're called by startup.s, so no need to save any regs.
_gdt_init:
	# Save the old GDTR
	sgdt	gdt_info

	# Move three descriptors
	movl	gdt_info+2,%esi		# Base of old GDT
	movl	$gdt,%edi		# Base of new GDT
	movl	$(3*8),%ecx		# Moving 3 descriptors
	cld
	rep
	movsb

	# Setup GDTR info for new GDT
	movl	$gdt,%esi
	movl	%esi,gdt_info+2
	movw	$(3*8),%si
	movw	%si,gdt_info
	lgdt	gdt_info

	# Reload our segments
	movl	$(2*8),%eax
	movw	%ax,%ds
	movw	%ax,%es
	movw	%ax,%fs
	movw	%ax,%gs
	movw	%ax,%ss

	# And CS as well...
	.byte	0xea
	.long	gdt_flush
	.word	8
gdt_flush:

	ret
