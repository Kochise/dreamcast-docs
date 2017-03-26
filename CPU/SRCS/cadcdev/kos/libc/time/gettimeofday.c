/* KallistiOS ##version##

   gettimeofday.c
   (c)2002 Dan Potter

   $Id: gettimeofday.c,v 1.3 2002/11/16 02:11:57 bardtx Exp $
*/

#include <assert.h>
#include <time.h>
#include <arch/timer.h>
#include <arch/rtc.h>

/* This is kind of approximate and works only with "localtime" */
int gettimeofday(struct timeval *tv, struct timezone *tz) {
	uint32	m, s;
	
	assert( tv != NULL );

	timer_ms_gettime(&s, &m);
	tv->tv_sec = rtc_boot_time() + s;
	tv->tv_usec = m * 1000;

	return 0;
}
