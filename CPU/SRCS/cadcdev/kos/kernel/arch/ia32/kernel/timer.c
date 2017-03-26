/* KallistiOS ##version##

   timer.c
   Copyright (c)2003 Dan Potter
*/

#include <assert.h>

#include <stdio.h>
#include <arch/arch.h>
#include <arch/timer.h>
#include <arch/irq.h>
#include <ia32/ports.h>

CVSID("$Id: timer.c,v 1.3 2003/08/02 23:11:43 bardtx Exp $");

volatile uint32 jiffies = 0;

// Set the PIC Timer 0 speed
void timer_set_speed(int tps) {
	uint32 factor;

	assert( tps != 0 ); if (!tps) tps++;
	factor = 1193181 / tps;

	outb(0x43, 0x34);
	outb(0x40, factor & 0xff);
	outb(0x40, (factor >> 8) & 0xff);
}

/* Spin-loop kernel sleep func: uses the secondary timer in the
   SH-4 to very accurately delay even when interrupts are disabled */
void timer_spin_sleep(int ms) {
}


/* Millisecond timer */
static uint32 timer_ms_counter = 0;
static uint32 timer_ms_countdown;
static void timer_ms_handler(irq_t source, irq_context_t *context) {
	timer_ms_counter++;
}

void timer_ms_enable() {
}

void timer_ms_disable() {
}

/* Return the number of ticks since KOS was booted */
void timer_ms_gettime(uint32 *secs, uint32 *msecs) {
	*secs = jiffies / HZ;
	*msecs = (jiffies % HZ) * 1000 / HZ;
}

uint64 timer_ms_gettime64() {
	return (uint64)jiffies * 1000 / HZ;
}

timer_primary_callback_t tp_callback;
static void tp_handler(irq_t src, irq_context_t * cxt) {
	if (tp_callback)
		tp_callback(cxt);
	jiffies++;
}

static void timer_primary_init() {
	// Clear out our vars
	tp_callback = NULL;

	// Hook the timer IRQ
	irq_set_handler(TIMER_IRQ, tp_handler);

	// Enable the external interrupt
	outb(0x21, inb(0x21) & ~1);
}

timer_primary_callback_t timer_primary_set_callback(timer_primary_callback_t cb) {
	timer_primary_callback_t cbold = tp_callback;
	tp_callback = cb;
	return cbold;
}

void timer_primary_wakeup(uint32 millis) {
	// We always wakeup after 1000/HZ millis for now
}


/* Init */
int timer_init() {
	// Set the primary timer speed
	timer_set_speed(HZ);

	// Hook the timer interrupt
	timer_primary_init();

	return 0;
}

/* Shutdown */
void timer_shutdown() {
}



