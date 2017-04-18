/***
*time.c - get current system time
*
*       Copyright (c) 1989-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       defines time() - gets the current system time and converts it to
*                        internal (time_t) format time.
*
*******************************************************************************/


#include <cruntime.h>
#include <time.h>
#include <internal.h>

#ifdef _WIN32
#include <windows.h>
#else  /* _WIN32 */
#if defined (_M_MPPC) || defined (_M_M68K)
#include <macos\osutils.h>     /* get DataTimeRec type */
#endif  /* defined (_M_MPPC) || defined (_M_M68K) */
#endif  /* _WIN32 */

#ifdef _WIN32

/*
 * Cache holding the last time (GMT) for which the Daylight time status was
 * determined by an API call.
 */
static SYSTEMTIME gmt_cache;

/*
 * Three values of dstflag_cache and dstflag (local variable in code
 * below)
 */
#define DAYLIGHT_TIME   1
#define STANDARD_TIME   0
#define UNKNOWN_TIME    -1

static int dstflag_cache;

#endif  /* _WIN32 */

/***
*time_t time(timeptr) - Get current system time and convert to time_t value.
*
*Purpose:
*       Gets the current date and time and stores it in internal (time_t)
*       format. The time is returned and stored via the pointer passed in
*       timeptr. If timeptr == NULL, the time is only returned, not stored in
*       *timeptr. The internal (time_t) format is the number of seconds since
*       00:00:00, Jan 1 1970 (UTC).
*
*       Note: We cannot use GetSystemTime since its return is ambiguous. In
*       Windows NT, in return UTC. In Win32S, probably also Win32C, it
*       returns local time.
*
*Entry:
*       time_t *timeptr - pointer to long to store time in.
*
*Exit:
*       returns the current time.
*
*Exceptions:
*
*******************************************************************************/

time_t __cdecl time (
        time_t *timeptr
        )
{
        time_t tim;

#ifdef _WIN32

        SYSTEMTIME loct, gmt;
        TIME_ZONE_INFORMATION tzinfo;
        DWORD tzstate;
        int dstflag;

        /*
         * Get local time from Win32
         */
        GetLocalTime( &loct );

        /*
         * Determine whether or not the local time is a Daylight Saving
         * Time. On Windows NT, the GetTimeZoneInformation API is *VERY*
         * expensive. The scheme below is intended to avoid this API call in
         * many important case by caching the GMT value and dstflag.In a
         * subsequent call to time(), the cached value of dstflag is used
         * unless the new GMT differs from the cached value at least in the
         * minutes place.
         */
        GetSystemTime( &gmt );

        if ( (gmt.wMinute == gmt_cache.wMinute) &&
             (gmt.wHour == gmt_cache.wHour) &&
             (gmt.wDay == gmt_cache.wDay) &&
             (gmt.wMonth == gmt_cache.wMonth) &&
             (gmt.wYear == gmt_cache.wYear) )
        {
            dstflag = dstflag_cache;
        }
        else
        {
            if ( (tzstate = GetTimeZoneInformation( &tzinfo )) != 0xFFFFFFFF )
            {
                /*
                 * Must be very careful in determining whether or not DST is
                 * really in effect.
                 */
                if ( (tzstate == TIME_ZONE_ID_DAYLIGHT) &&
                     (tzinfo.DaylightDate.wMonth != 0) &&
                     (tzinfo.DaylightBias != 0) )
                    dstflag = DAYLIGHT_TIME;
                else
                    /*
                     * When in doubt, assume standard time
                     */
                    dstflag = STANDARD_TIME;
            }
            else
                dstflag = UNKNOWN_TIME;

            dstflag_cache = dstflag;
            gmt_cache = gmt;
        }

        /* convert using our private routine */

        tim = __loctotime_t( (int)loct.wYear,
                             (int)loct.wMonth,
                             (int)loct.wDay,
                             (int)loct.wHour,
                             (int)loct.wMinute,
                             (int)loct.wSecond,
                             dstflag );

#else  /* _WIN32 */
#if defined (_M_MPPC) || defined (_M_M68K)

        DateTimeRec dt;

        GetTime(&dt);
        /* convert using our private routine */
        tim = _gmtotime_t((int)dt.year,
                          (int)dt.month,
                          (int)dt.day,
                          (int)dt.hour,
                          dt.minute,
                          dt.second);

#endif  /* defined (_M_MPPC) || defined (_M_M68K) */
#endif  /* _WIN32 */

        if (timeptr)
                *timeptr = tim;         /* store time if requested */

        return tim;
}

