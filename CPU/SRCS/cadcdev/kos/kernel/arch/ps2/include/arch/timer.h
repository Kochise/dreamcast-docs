/* KallistiOS ##version##

   arch/ps2/include/timer.h
   (c)2000-2002 Dan Potter

   $Id: timer.h,v 1.2 2002/11/03 03:40:55 bardtx Exp $

*/

#ifndef __ARCH_TIMER_H
#define __ARCH_TIMER_H

#include <sys/cdefs.h>
__BEGIN_DECLS

#include <arch/types.h>

/* Bus clock speed on the PS2 is 147.456MHz; these are spelt out here
   so that it's easier to calculate the type you need. Unfortunately the
   next slowest thing you can latch to is HSYNC, which is based on
   refresh rates and not real time. -_- */
#define TIMER_BUSCLK	147456000
#define TIMER_BUSCLK16	9216000
#define TIMER_BUSCLK256	576000

/* Timer sources -- we get four on the SH4 */
#define TIMER0	0	/* Unused */
#define TIMER1	1	/* Used for timer_spin_sleep() */
#define TIMER2	2	/* Will for timer_ms_gettime() maybe */
#define TIMER3	3	/* Off limits during thread operation */

/* The main timer for the task switcher to use */
#define TIMER_ID TIMER3

/* Pre-initialize a timer; set values but don't start it */
int timer_prime(int which, uint32 speed, int interrupts);

/* Start a timer -- starts it running (and interrupts if applicable) */
int timer_start(int which);

/* Stop a timer -- and disables its interrupt */
int timer_stop(int which);

/* Returns the count value of a timer */
uint32 timer_count(int which);

/* Clears the timer underflow bit and returns what its value was */
int timer_clear(int which);

/* Spin-loop kernel sleep func: uses the secondary timer in the
   SH-4 to very accurately delay even when interrupts are disabled */
void timer_spin_sleep(int ms);

/* Enable timer interrupts (high priority); needs to move
   to irq.c sometime. */
void timer_enable_ints(int which);

/* Disable timer interrupts; needs to move to irq.c sometime. */
void timer_disable_ints(int which);

/* Check whether ints are enabled */
int timer_ints_enabled(int which);

/* Enable the millisecond timer */
void timer_ms_enable();
void timer_ms_disable();

/* Return the number of ticks since KOS was booted */
void timer_ms_gettime(uint32 *secs, uint32 *msecs);

/* Enable the main kernel timer */
void timer_primary_enable();
void timer_primary_disable();

/* Init function */
int timer_init();

/* Shutdown */
void timer_shutdown();

__END_DECLS

#endif	/* __ARCH_TIMER_H */

