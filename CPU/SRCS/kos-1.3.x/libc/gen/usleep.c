/* KallistiOS ##version##

   usleep.c
   (c)2001 Dan Potter

   $Id: usleep.c,v 1.1 2002/02/09 06:15:42 bardtx Exp $
*/

#include <arch/timer.h>

/* usleep() */
void usleep(unsigned long usec) {
	timer_spin_sleep (usec / 1000);
}

