/* KallistiOS ##version##

   time.c
   (c)2002 Dan Potter

   $Id: time.c,v 1.1 2002/02/24 01:24:00 bardtx Exp $
*/

#include <time.h>
#include <arch/rtc.h>

/* time() */
time_t time(time_t *ptr) {
	time_t t;

	t = rtc_unix_secs();
	if (ptr) {
		*ptr = t;
	}
	return t;
}

/* time() */
double difftime(time_t time1, time_t time0) {
	return (double)(time1 - time0);
}

