#
# Generic startup and interrupt handler for ARM7 CPU.
#
# Note:	Stack is allocated at 0xf000, keep the binary short.  :-)
#
	
	.globl	_start, timer

	.text


	# Exception vectors
_start:
	b	reset
	b	undef
	b	softint
	b	pref_abort
	b	data_abort
	b	rsrvd
	b	irq


	# "Fast interrupt" handler
fiq:

	# Check type of interrupt

	ldr	r8,intreq
	ldr	r9,[r8]
	and	r9,r9,#7
	cmp	r9,#2
	bne	fiq_done

	# Type 2 is timer interrupt.

	# Increment timer variable
	
	adr	r8,timer
	ldr	r9,[r8]
	add	r9,r9,#1
	str	r9,[r8]

	# Request a new timer interrupt in about
	# one millisecond
	
	ldr	r8,fooaddr
	mov	r9,#256-(44100/1000)
	str	r9,[r8,#0x10]
	mov	r9,#0x40
	str	r9,[r8,#0x24]
	b	fiq_done

	# Return from interrupt

fiq_done:
	ldr	r8,intclr
	mov	r9,#1
	str	r9,[r8]
	str	r9,[r8]
	str	r9,[r8]
	str	r9,[r8]
	subs	pc,r14,#4


intreq:
	.long	0x802d00
intclr:
	.long	0x802d04
fooaddr:
	.long	0x802880
timer:
	.long	0

	
	# No-op handlers for the remaining vectors

undef:
softint:
	movs	pc,r14

pref_abort:
irq:
rsrvd:
	subs	pc,r14,#4
	
data_abort:
	subs	pc,r14,#8


	# Reset entry point
	
reset:
	# Disable IRQ and enable FIQ
	mrs	r0,CPSR
	orr	r0,r0,#0x80
	bic	r0,r0,#0x40
	msr	CPSR,r0
	# Set stack
	mov	sp,#0xf000

	# Call main
	bl	main

	# Done.  Stay put.
done:	b	done


	.end

