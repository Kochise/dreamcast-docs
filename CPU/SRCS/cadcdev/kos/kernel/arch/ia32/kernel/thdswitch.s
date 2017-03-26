# KallistiOS ##version##
#
# arch/ia32/kernel/entry.s
# Copyright (C)2003 Dan Potter
#
# Assembler code for swapping out running threads
#
# See the Dreamcast thdswitch.s for more info.
#

	.text
	.global thd_block_now

thd_block_now:
	# Save eflags for later...
	pushfl

	# Disable interrupts
	call	irq_disable

	# Save all the basic regs (we don't care about eax here since it
	# is the return value and is expected to be clobbered anyway)
	movl	8(%esp),%eax
	movl	%ebx,4(%eax)
	movl	%ecx,8(%eax)
	movl	%edx,12(%eax)
	movl	%esi,16(%eax)
	movl	%edi,20(%eax)
	movl	%ebp,24(%eax)

	# Save original eflags
	popl	%ebx
	movl	%ebx,36(%eax)

	# Pop off the return value and store it as the new eip, as if we
	# had returned (that will be the effect).
	popl	%ebx
	movl	%ebx,32(%eax)
	movl	%esp,28(%eax)

	# Ok, everything is saved now. Find a new thread to run.
	call	thd_choose_new

	# To swap in the new task, we'll just force an interrupt return.
	jmp	irq_force_return
