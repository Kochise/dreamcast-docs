# crt0.S - ARM startup + interrupt routines

	.globl	_start, interval, counter
	.xref	main
	.text

_start:
	b	reset
	b	not_handled
	b	not_handled
	b	not_handled
	b	not_handled
	b	not_handled
	b	not_handled

# FIQ directly without a branch (wow! this is major optimization =)
	ldr	r8,intpend
	ldr	r9,[r8]
	and	r9,r9,#7
	cmp	r9,#2
	bne	done

# set interrupt interval
	ldr	r8,timerctrl
	ldr	r9,interval
	str	r9,[r8,#0x10]
# this prolly enables the interrupt
	mov	r9,#0x40
	str	r9,[r8,#0x24]

# update counter
	ldr	r8,counter
	add	r8,r8,#1
	str	r8,counter

done:
	ldr	r8,intclear
	mov	r9,#1
# the sega-driver does these 4 writes...
	str	r9,[r8]
	str	r9,[r8]
	str	r9,[r8]
	str	r9,[r8]
not_handled:
	subs	pc,lr,#4

stackptr:
	.long	0x00000000

intpend:
	.long	0x00802d00
intclear:
	.long	0x00802d04
timerctrl:
	.long	0x00802880
interval:
	.long	(256-(44100/4410))
counter:
	.long	0x00000000

id:
	.ascii	"dxm $Id: crt0.S,v 1.1.1.1 2001/09/08 10:48:15 ejstans Exp $"
	.byte	0

	.align	2
reset:
# setup stacks
# save 0xb000 at address 0xaffc and read it back to USER sp
	mov	sp,#0xb000
	stmfd	sp,{sp}
	ldmea	sp,{sp}^
	nop
# enable FIQ and go from SUPERVISOR to USER mode
	mrs	r14,cpsr
	bic	r14,r14,#0x43
	msr	cpsr,r14

# call main routine
	b	main
