/* KallistiOS ##version##

   timer.c
   Copyright (C)2000, 2001, 2002,2004 Dan Potter
*/

#include <stdio.h>
#include <arch/timer.h>
#include <arch/irq.h>

/* Quick access macros */
#define TIMER8(o) ( *((volatile uint8*)(0xffd80000 + (o))) )
#define TIMER16(o) ( *((volatile uint16*)(0xffd80000 + (o))) )
#define TIMER32(o) ( *((volatile uint32*)(0xffd80000 + (o))) )
#define TOCR	0x00
#define TSTR	0x04
#define TCOR0	0x08
#define TCNT0	0x0c
#define TCR0	0x10
#define TCOR1	0x14
#define TCNT1	0x18
#define TCR1	0x1c
#define TCOR2	0x20
#define TCNT2	0x24
#define TCR2	0x28
#define TCPR2	0x2c

static int tcors[] = { TCOR0, TCOR1, TCOR2 };
static int tcnts[] = { TCNT0, TCNT1, TCNT2 };
static int tcrs[] = { TCR0, TCR1, TCR2 };

/* Pre-initialize a timer; set values but don't start it */
int timer_prime(int which, uint32 speed, int interrupts) {
	/* P0/64 scalar, maybe interrupts */
	if (interrupts)
		TIMER16(tcrs[which]) = 32 | 2;
	else
		TIMER16(tcrs[which]) = 2;
		
	/* Initialize counters; formula is P0/(tps*64) */
	TIMER32(tcnts[which]) = 50000000 / (speed*64);
	TIMER32(tcors[which]) = 50000000 / (speed*64);
	
	return 0;
}

/* Start a timer -- starts it running (and interrupts if applicable) */
int timer_start(int which) {
	TIMER8(TSTR) |= 1 << which;
	return 0;
}

/* Stop a timer -- and disables its interrupt */
int timer_stop(int which) {
	/* Stop timer */
	TIMER8(TSTR) &= ~(1 << which);

	return 0;
}

/* Clears the timer underflow bit and returns what its value was */
int timer_clear(int which) {
	uint16 value = TIMER16(tcrs[which]);
	TIMER16(tcrs[which]) &= ~0x100;
	
	return (value & 0x100) ? 1 : 0;
}

/* Spin-loop kernel sleep func: uses the secondary timer in the
   SH-4 to very accurately delay even when interrupts are disabled */
void timer_spin_sleep(int ms) {
	timer_stop(TMU1);
	timer_prime(TMU1, 1000, 0);
	timer_clear(TMU1);
	timer_start(TMU1);

	while (ms > 0) {
		while (!(TIMER16(tcrs[TMU1]) & 0x100))
			;
		timer_clear(TMU1);
		ms--;
	}

	timer_stop(TMU1);
}

/* Init */
int timer_init() {
	/* Disable all timers */
	TIMER8(TSTR) = 0;
	
	/* Set to internal clock source */
	TIMER8(TOCR) = 0;

	return 0;
}

/* Shutdown */
void timer_shutdown() {
	/* Disable all timers */
	TIMER8(TSTR) = 0;
}



