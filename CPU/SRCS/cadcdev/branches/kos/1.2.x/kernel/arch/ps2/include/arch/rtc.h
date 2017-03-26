/* KallistiOS ##version##

   arch/ps2/include/rtc.h
   (c)2000-2002 Dan Potter

   $Id: rtc.h,v 1.1 2002/10/26 08:04:00 bardtx Exp $

 */

#ifndef __ARCH_RTC_H
#define __ARCH_RTC_H

#include <sys/cdefs.h>
__BEGIN_DECLS

#include <time.h>

/* Returns the date/time value as a UNIX epoch time stamp */
time_t rtc_unix_secs();

__END_DECLS

#endif	/* __ARCH_RTC_H */

