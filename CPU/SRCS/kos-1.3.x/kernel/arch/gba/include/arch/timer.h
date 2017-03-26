/* KallistiOS ##version##

   arch/gba/include/timer.h
   (c)2000-2001 Dan Potter

   $Id: timer.h,v 1.2 2003/02/17 00:47:38 bardtx Exp $

*/

#ifndef __ARCH_TIMER_H
#define __ARCH_TIMER_H

#include <arch/types.h>
#include <arch/irq.h>

/* Does the same as timer_ms_gettime(), but it merges both values
   into a single 64-bit millisecond counter. May be more handy  
   in some situations. */
uint64 timer_ms_gettime64();

/* Set the callback target for the primary timer. Set to NULL
   to disable callbacks. Returns the address of the previous
   handler. */
typedef void (*timer_primary_callback_t)(irq_context_t *);
timer_primary_callback_t timer_primary_set_callback(timer_primary_callback_t callback);

/* Request a wakeup in approximately N milliseconds. You only get one
   simultaneous wakeup. Any subsequent calls here will replace any 
   pending wakeup. */
void timer_primary_wakeup(uint32 millis);

/* Init function */
int timer_init();

/* Shutdown */
void timer_shutdown();

#endif	/* __ARCH_TIMER_H */

