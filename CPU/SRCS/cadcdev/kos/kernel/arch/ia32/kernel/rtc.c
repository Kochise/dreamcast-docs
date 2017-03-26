/* KallistiOS ##version##

   rtc.c
   Copyright (C)2003 Dan Potter
*/

/* Real Time Clock support

   The functions in here return various info about the real-world time and
   date stored in the machine. The general process here is to retrieve
   the date/time value and then use the other functions to interpret it.

   rtc_get_time() should return a UNIX-epoch time stamp, and then the normal
   BSD library functions can be used to interpret that time stamp.

 */

#include <arch/rtc.h>

CVSID("$Id: rtc.c,v 1.1 2003/08/01 03:18:37 bardtx Exp $");

/* The boot time; we'll save this in rtc_init() */
static time_t boot_time = 0;

/* Returns the date/time value as a UNIX epoch time stamp */
time_t rtc_unix_secs() {
	return 0;
}


/* Returns the date/time that the system was booted as a UNIX epoch time
   stamp. Adding this to the value from timer_ms_gettime() will
   produce a current timestamp. */
time_t rtc_boot_time() {
	return boot_time;
}

int rtc_init() {
	boot_time = rtc_unix_secs();
	return 0;
}

void rtc_shutdown() {
}
