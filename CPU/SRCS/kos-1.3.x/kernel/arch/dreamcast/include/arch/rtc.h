/* KallistiOS ##version##

   arch/dreamcast/include/rtc.h
   (c)2000-2001 Dan Potter

   $Id: rtc.h,v 1.4 2002/11/16 02:11:58 bardtx Exp $

 */

#ifndef __ARCH_RTC_H
#define __ARCH_RTC_H

#include <sys/cdefs.h>
__BEGIN_DECLS

#include <time.h>

/* Returns the date/time value as a UNIX epoch time stamp */
time_t rtc_unix_secs();

/* Returns the date/time that the system was booted as a UNIX epoch time
   stamp. Adding this to the value from timer_ms_gettime() will
   produce a current timestamp. */
time_t rtc_boot_time();

/* Init / Shutdown */
int rtc_init();
void rtc_shutdown();

__END_DECLS

#endif	/* __ARCH_RTC_H */

