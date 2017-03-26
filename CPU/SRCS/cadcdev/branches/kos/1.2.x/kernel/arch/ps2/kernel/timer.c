/* KallistiOS ##version##

   timer.c
   (c)2002 Dan Potter
*/

#include <assert.h>
#include <stdio.h>
#include <arch/arch.h>
#include <arch/timer.h>
#include <arch/irq.h>
#include <ps2/ioports.h>

CVSID("$Id: timer.c,v 1.1 2002/11/03 03:40:55 bardtx Exp $");

/* Pre-initialize a timer; set values but don't start it */
int timer_prime(int which, uint32 speed, int interrupts) {
	/* Note: speed must be at least 100 here! Otherwise,
	   the count value will overflow. */
	assert( speed >= 100 );

	if (interrupts)
		timer_enable_ints(which);
	else
		timer_disable_ints(which);

	TIMER_COMP(which) = TIMER_BUSCLK256 / speed;
	TIMER_COUNT(which) = 0;
	TIMER_HOLD(which) = 0;
	TIMER_MODE(which) = TIMER_CLKS_BUSCLK256
		| TIMER_ZRET_ENABLE
		| TIMER_CMPE_ENABLE
		| TIMER_EQUF
		| TIMER_OVFF;

	return 0;
}

/* Start a timer -- starts it running (and interrupts if applicable) */
int timer_start(int which) {
	TIMER_MODE(which) |= TIMER_CUE_ENABLE;
	return 0;
}

/* Stop a timer -- and disables its interrupt */
int timer_stop(int which) {
	TIMER_MODE(which) &= ~TIMER_CUE_ENABLE;
	return 0;
}

/* Returns the count value of a timer */
uint32 timer_count(int which) {
	return TIMER_COUNT(which);
}

/* Clears the timer EQUF bit and returns what its value was */
int timer_clear(int which) {
	uint32 tmp = TIMER_MODE(which);
	TIMER_MODE(which) = tmp | TIMER_EQUF;

	return (tmp & TIMER_EQUF) != 0;
}

/* Spin-loop kernel sleep func: uses timer 1 in the
   EE to very accurately delay even when interrupts are disabled */
void timer_spin_sleep(int ms) {
	timer_prime(1, 1000, 0);
	timer_start(1);

	while (ms > 0) {
		while (!(TIMER_MODE(1) & TIMER_EQUF))
			;
		timer_clear(1);
		ms--;
	}

	timer_stop(1);
}

/* Enable timer interrupts (high priority); needs to move
   to irq.c sometime. */
void timer_enable_ints(int which) {
	INTC_MASK_SET(INTM_TIMER0 << which);
}

/* Disable timer interrupts; needs to move to irq.c sometime. */
void timer_disable_ints(int which) {
	INTC_MASK_CLEAR(INTM_TIMER0 << which);
}

/* Check whether ints are enabled */
int timer_ints_enabled(int which) {
	return (INTC_MASK & (INTM_TIMER0) << which) != 0;
}

/* Millisecond timer -- this is unfunctional right now because we can't
   get a timer slower than about 100Hz (might as well piggyback on jiffies).
   Probably should set it up later to trigger on VSYNC or something. */
static uint32 timer_ms_counter = 0;
static uint32 timer_ms_countdown;
static void timer_ms_handler(irq_t source, irq_context_t *context) {
	timer_ms_counter++;
}

void timer_ms_enable() {
	/* irq_set_handler(EXC_INTR_TIMER2, timer_ms_handler);
	timer_prime(2, 100, 1);
	timer_ms_countdown = TIMER_COMP(2);
	timer_clear(2);
	timer_start(2); */
}

void timer_ms_disable() {
	/* timer_stop(2);
	timer_disable_ints(2); */
}

/* Return the number of ticks since KOS was booted */
void timer_ms_gettime(uint32 *secs, uint32 *msecs) {
	uint32 used;

	/* Seconds part comes from ms_counter / 100 */
	if (secs) {
		*secs = timer_ms_counter;
	}

	/* Milliseconds, we check how much of the timer has elapsed */
	if (msecs) {
		// used = timer_ms_countdown - timer_count(TMU2);
		used = 0;
		*msecs = (uint32)(used * 1000.0 / timer_ms_countdown);
	}
}

/* Enable / Disable primary kernel timer */
void timer_primary_enable() {
	/* Preinit and enable timer with interrupts, with HZ for jiffies */
	timer_prime(TIMER_ID, HZ, 0);
	timer_start(TIMER_ID);
}

void timer_primary_disable() {
	timer_disable_ints(TIMER_ID);
	timer_stop(TIMER_ID);
}

/* Init */
int timer_init() {
	int i;
	
	/* Disable all timers */
	for (i=0; i<4; i++) {
		TIMER_MODE(i) = 0;
		timer_disable_ints(i);
	}
	
	return 0;
}

/* Shutdown */
void timer_shutdown() {
	int i;
	
	/* Disable all timers */
	for (i=0; i<4; i++) {
		TIMER_MODE(i) = 0;
		timer_disable_ints(i);
	}
}



