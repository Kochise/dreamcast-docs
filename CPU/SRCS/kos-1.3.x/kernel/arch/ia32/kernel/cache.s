# KallistiOS ##version##
#
# arch/ia32/kernel/cache.s
# Copyright (C)2003 Dan Potter
#
# Instruction and data cache handling stuff. We really don't need this on
# the PC for now. Maybe later if we want to attempt some DMA...?
#

	.text
	.global dcache_flush_range
	.global dcache_inval_range
	.global icache_flush_range

dcache_flush_range:
	ret

dcache_inval_range:
	ret

icache_flush_range:
	ret

