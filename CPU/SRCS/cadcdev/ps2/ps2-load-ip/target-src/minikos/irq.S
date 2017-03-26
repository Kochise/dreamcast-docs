/* ps2-load-ip

   irq.S
   Copyright (c)2002 Dan Potter
   License: BSD

   $Id: irq.S,v 1.1 2002/10/30 05:34:13 bardtx Exp $
*/
            
// Adapted from KOS/PS2's entry.S

	.set noat
	.set noreorder

	.global irq_enable
	.global irq_disable
	.global irq_restore

	#include "asmregs.h"

	.text

// Call to disable external interrupts. Note that unlike the DC, it is
// not possible to disable exceptions. Yer stuck with 'em. :) Returns
// a value suitable to pass to irq_restore.
//
// DI and EI don't seem to function.. :(
//
irq_disable:
	la	t1,(~1)
	mfc0	t0,cp0status
	and	t0,t0,t1
	mtc0	t0,cp0status
	sync.p
	move	v0,t0
	andi	v0,v0,1
	jr	ra
	nop

// Call to enable external interrupts. Returns a value suitable to pass
// to irq_restore.
irq_enable:
	mfc0	v0,cp0status
	move	t0,v0
	andi	v0,v0,1
	ori	t0,t0,1
	mtc0	t0,cp0status
	sync.p
	jr	ra
	nop

// Takes the value returned from either irq_disable or irq_enable and sets
// the interrupt state back to that state.
irq_restore:
	mfc0	at,cp0status
	or	at,at,a0
	mtc0	at,cp0status
	sync.p
	jr	ra
	nop

	.ident "KOS $Id: irq.S,v 1.1 2002/10/30 05:34:13 bardtx Exp $"
