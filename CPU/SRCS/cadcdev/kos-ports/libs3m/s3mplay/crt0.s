# Adapted from Marcus' AICA example among a few other sources =)

.text
.globl	arm_main
.globl	timer
.globl	jps

# Exception vectors
	b	start
	b	undef
	b	softint
	b	pref_abort
	b	data_abort
	b	rsrvd
	b	irq


# FIQ code adapted from the Marcus AICA example
fiq:
	# Save regs
	#stmdb	sp!, {r0-r14}

	# Grab interrupt type (store as parameter)
	ldr	r8,intreq
	ldr	r9,[r8]
	and	r9,r9,#7
	cmp	r9,#2
	bne	fiq_done

	# Type 2 is timer interrupt. Increment timer variable.
	adr	r8,timer
	ldr	r9,[r8]
	add	r9,r9,#1
	str	r9,[r8]
	
	# Request a new timer interrupt. We'll calculate the number
	# put in here based on the "jps" (jiffies per second). 
	ldr	r8, timer_control
	mov	r9,#256-(44100/4410)
#	ldr	r9,jps
	str	r9,[r8,#0x10]
	mov	r9,#0x40
	str	r9,[r8,#0x24]
	b	fiq_done
	
	# Return from interrupt
fiq_done:

	# Clear interrupt
	ldr	r8,intclr
	mov	r9,#1
	str	r9,[r8]
	str	r9,[r8]
	str	r9,[r8]
	str	r9,[r8]

	# Restore regs and return
	#ldmdb	sp!, {r0-r14}
	subs	pc,r14,#4

intreq:
	.long	0x00802d00
intclr:
	.long	0x00802d04
timer_control:
	.long	0x00802880
timer:
	.long	0
jps:
	.long	256-(44100/1000)


start:
	# Setup a basic stack, disable IRQ, enable FIQ
	mov	sp,#0xb000
	mrs	r10,CPSR
	orr	r10,r10,#0x80
	bic	r10,r10,#0x40
	msr	CPSR_all,r10

	# Call the main for the SPU
	bl	arm_main

	# Loop infinitely if we get here
here:	b	here


# Handlers we don't bother to catch
undef:
softint:
	mov	pc,r14
pref_abort:
data_abort:
irq:
rsrvd:
	sub	pc,r14,#4






