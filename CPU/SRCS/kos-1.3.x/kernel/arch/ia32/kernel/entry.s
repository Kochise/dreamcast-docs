# KallistiOS ##version##
#
# arch/ia32/kernel/entry.s
# Copyright (C)2003 Dan Potter
#
# Assembler code for entry and exit to/from the kernel via exceptions
#

	.data

	.global idt
	.global idt_info

	.align	32
idt:	.zero	8*256		# Leave enough for all 256 interrupts

idt_info:
	.short	8*256		# Length in bytes
	.long	0		# Linear base address (to be filled in)

exception:
	.long	0
excp_errcode:
	.long	0

excp_addrs:
	.long	excp_0
	.long	excp_1
	.long	excp_2
	.long	excp_3
	.long	excp_4
	.long	excp_5
	.long	excp_6
	.long	excp_7
	.long	excp_8
	.long	excp_9
	.long	excp_a
	.long	excp_b
	.long	excp_c
	.long	excp_d
	.long	excp_e
	.long	excp_f

intr_addrs:
	.long	intr_0
	.long	intr_1
	.long	intr_2
	.long	intr_3
	.long	intr_4
	.long	intr_5
	.long	intr_6
	.long	intr_7
	.long	intr_8
	.long	intr_9
	.long	intr_a
	.long	intr_b
	.long	intr_c
	.long	intr_d
	.long	intr_e
	.long	intr_f

	.global irq_srt_addr
irq_srt_addr:
	.long	0

	.text
	.global irq_disable
	.global irq_enable
	.global irq_restore
	.global irq_low_setup
	.global irq_force_return

# Disable external interrupts and return the previous value.
irq_disable:
	pushfl
	cli
	popl	%eax
	andl	$(1<<9),%eax	# Take only IF
	ret

# Enable external interrupts and return the previous value.
irq_enable:
	pushfl
	sti
	popl	%eax
	andl	$(1<<9),%eax	# Take only IF
	ret

# Using a value from irq_disable or irq_enable, restore the interrupt
# state before the call that returned the value.
irq_restore:
	movl	4(%esp),%eax
	cmp	$0,%eax		# Were they turned on before?
	je	restore_off
	sti			# They were on.
	ret
restore_off:
	cli			# They were off.
	ret


# Exception vectors
excp_0:
	movl	$0,exception
	jmp	excp_common
excp_1:
	movl	$1,exception
	jmp	excp_common
excp_2:
	movl	$2,exception
	jmp	excp_common
excp_3:
	movl	$3,exception
	jmp	excp_common
excp_4:
	movl	$4,exception
	jmp	excp_common
excp_5:
	movl	$5,exception
	jmp	excp_common
excp_6:
	movl	$6,exception
	jmp	excp_common
excp_7:
	movl	$7,exception
	jmp	excp_common
excp_8:
	movl	$8,exception
	jmp	excp_common
excp_9:
	movl	$9,exception
	jmp	excp_common
excp_a:
	movl	$10,exception
	jmp	excp_common
excp_b:
	movl	$11,exception
	jmp	excp_common
excp_c:
	movl	$12,exception
	jmp	excp_common
excp_d:
	movl	$13,exception
	jmp	excp_common
excp_e:
	movl	$14,exception
	jmp	excp_common
excp_f:
	movl	$15,exception
	jmp	excp_common

# Common handler for all exceptions.
excp_common:
	# Stack is currently EFLAGS, CS, EIP, and maybe ERRCODE. Currently
	# nothing is saved except those things.

	# Bootstrap-save eax.
	pushl	%eax

	# Get the address of the IRQ context we're using
	movl	irq_srt_addr,%eax

	# Save all the basic regs
	movl	%ebx,4(%eax)
	movl	%ecx,8(%eax)
	movl	%edx,12(%eax)
	movl	%esi,16(%eax)
	movl	%edi,20(%eax)
	movl	%ebp,24(%eax)

	# Get back our saved eax and store it
	popl	%ebx
	movl	%ebx,0(%eax)

	# 8, 10-14 have an error code with them. Grab the error and
	# put it in ecx.
	xor	%ecx,%ecx
	cmp	$8,exception
	je	err_code
	cmp	$10,exception
	jl	err_none
	cmp	$14,exception
	jg	err_none
err_code:
	popl	%ecx
	andl	$0x0000ffff,%ecx
err_none:

	# Stack is now EFLAGS, CS, EIP.

	# Save ESP, EIP and EFLAGS now that we know where they are 100%
	popl	%ebx			# eip
	movl	%ebx,32(%eax)
	addl	$4,%esp			# cs
	popl	%ebx			# eflags
	movl	%ebx,36(%eax)
	movl	%esp,28(%eax)		# esp (w/o iret frame)

	# Stack is now empty. Push the exception and error codes.
	pushl	%ecx
	movl	exception,%eax
	pushl	%eax

	# Call the common C-level handler
	call	irq_handle_exception

irq_force_return:
	# Get the new esp from irq_srt_addr
	movl	irq_srt_addr,%eax
	movl	28(%eax),%esp

	# Stack is now empty from the new task. Fill in the new values
	# of eip and eflags.
	movl	36(%eax),%ebx		# eflags
	pushl	%ebx
	movl	%cs,%ebx		# cs
	pushl	%ebx
	movl	32(%eax),%ebx		# eip
	pushl	%ebx

	# Restore the other registers from the new irq_srt_addr
	movl	4(%eax),%ebx
	movl	8(%eax),%ecx
	movl	12(%eax),%edx
	movl	16(%eax),%esi
	movl	20(%eax),%edi
	movl	24(%eax),%ebp
	movl	0(%eax),%eax
	
	# Return back to the new task
	iretl
	
	
# Interrupt vectors
intr_0:
	movl	$0,exception
	jmp	intr_common
intr_1:
	movl	$1,exception
	jmp	intr_common
intr_2:
	movl	$2,exception
	jmp	intr_common
intr_3:
	movl	$3,exception
	jmp	intr_common
intr_4:
	movl	$4,exception
	jmp	intr_common
intr_5:
	movl	$5,exception
	jmp	intr_common
intr_6:
	movl	$6,exception
	jmp	intr_common
intr_7:
	movl	$7,exception
	jmp	intr_common
intr_8:
	movl	$8,exception
	jmp	intr_common
intr_9:
	movl	$9,exception
	jmp	intr_common
intr_a:
	movl	$10,exception
	jmp	intr_common
intr_b:
	movl	$11,exception
	jmp	intr_common
intr_c:
	movl	$12,exception
	jmp	intr_common
intr_d:
	movl	$13,exception
	jmp	intr_common
intr_e:
	movl	$14,exception
	jmp	intr_common
intr_f:
	movl	$15,exception
	jmp	intr_common

IRQ_BASE = 0x70
IRQ_PIC_VALUE = 0x7870

# Common handler for all IRQ requests
intr_common:
	# Save eax while we're using it.
	pushl	%eax

	# What was the IRQ index?
	movl	exception,%eax

	# Which PIC?
	cmpl	$8,%eax
	jge	second_pic

	movb	$0x20,%al
	outb	%al,$0x20
	jmp	done_pic
second_pic:
	movb	$0x20,%al
	outb	%al,$0xa0
done_pic:

	# Get the IRQ index again
	movl	exception,%eax

	# Adjust it for exception codes and save it back
	addl	$IRQ_BASE,%eax
	movl	%eax,exception

	# Restore eax and jump to the normal exception handler
	popl	%eax
	jmp	excp_common


# Low-level IRQ/Exception setup. We setup an IDT here that hooks into our
# handler routines.
irq_low_setup:
	pushal

	# Reprogram the PIC so that IRQs go from IRQ_BASE - IRQ_BASE+0xf.
	movw	$IRQ_PIC_VALUE,%bx
	call	set_pic

	# Setup the first 16 interrupts as CPU exception handlers.
	movl	$excp_addrs,%esi
	movl	$idt,%edi
	movl	$16,%ecx
	call	setup_idt_chunk

	# Setup 16 interrupts as IRQ handlers (starting with IRQ_BASE)
	movl	$intr_addrs,%esi
	movl	$(idt+IRQ_BASE*8),%edi
	movl	$16,%ecx
	call	setup_idt_chunk

	# Load the IDT
	movl	$idt,idt_info+2
	lidt	idt_info

	popal
	ret

setup_idt_chunk:
	movw	(%esi),%ax
	movw	2(%esi),%bx
	movw	%ax,(%edi)	# Fill in offset 15..0
	movw	%cs,2(%edi)	# Fill in selector
	movb	$0,4(%edi)	# All unused
	movb	$0x8e,5(%edi)	# Put some flags (present, DPL=0)
	movw	%bx,6(%edi)	# Fill in offset 31..16

	addl	$4,%esi		# Increment input pointer
	addl	$8,%edi		# Increment output pointer
	decl	%ecx		# Decrement counter
	jnz	setup_idt_chunk

	ret

# BX = 0xYYZZ, where YY = base of high IRQs, ZZ = base of low IRQs
set_pic:
	movb	$0x11,%al
	outb	%al,$0x20
	outb	%al,$0xa0
	movb	%bl,%al
	outb	%al,$0x21
	movb	%bh,%al
	outb	%al,$0xa1
	movb	$4,%al
	outb	%al,$0x21
	movb	$2,%al
	outb	%al,$0xa1
	movb	$1,%al
	outb	%al,$0x21
	outb	%al,$0xa1
	ret

