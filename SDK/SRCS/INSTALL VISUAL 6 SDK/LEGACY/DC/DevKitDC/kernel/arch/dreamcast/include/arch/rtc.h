/* KallistiOS 1.1.6

   arch/dreamcast/include/rtc.h
   (c)2000-2001 Dan Potter

   $Id: rtc.h,v 1.2 2002/01/05 07:33:50 bardtx Exp $

 */

#ifndef __ARCH_RTC_H
#define __ARCH_RTC_H

#include <sys/cdefs.h>
__BEGIN_DECLS

#include <arch/types.h>

/* Dreamcast UNIX timestamp type */
typedef uint32 time_t;

/* Returns the date/time value as a UNIX epoch time stamp */
time_t rtc_unix_secs();

__END_DECLS

#endif	/* __ARCH_RTC_H */

