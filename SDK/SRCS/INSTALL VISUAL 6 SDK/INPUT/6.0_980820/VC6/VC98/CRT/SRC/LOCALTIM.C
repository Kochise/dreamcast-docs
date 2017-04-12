/***
*localtim.c - Convert time_t value to time structure
*
*       Copyright (c) 1985-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       Converts time stored as a time_t value to a structure of type
*       struct tm expressed as local time.
*
*******************************************************************************/

#include <cruntime.h>
#include <limits.h>
#include <time.h>
#include <stddef.h>
#include <ctime.h>
#include <internal.h>

/***
*struct tm *localtime(ptime) - convert time_t value to tm structure
*
*Purpose:
*       Convert a value in internal (time_t) format to a tm struct
*       containing the corresponding local time.
*
* NOTES:
*       (1) gmtime must be called before _isindst to ensure that the tb time
*           structure is initialized.
*       (2) gmtime and localtime use a single statically allocated buffer.
*           Each call to one of these routines destroys the contents of the
*           previous call.
*       (3) It is assumed that time_t is a 32-bit long integer representing
*           the number of seconds since 00:00:00, 01-01-70 (UTC) (i.e., the
*           Posix/Unix Epoch. Only non-negative values are supported.
*       (4) It is assumed that the maximum adjustment for local time is
*           less than three days (include Daylight Savings Time adjustment).
*           This only a concern in Posix where the specification of the TZ
*           environment restricts the combined offset for time zone and
*           Daylight Savings Time to 2 * (24:59:59), just under 50 hours.
*
*Entry:
*       time_t *ptime - pointer to a long time value
*
*Exit:
*       If *ptime is non-negative, returns a pointer to the tm structure.
*       Otherwise, returns NULL.
*
*Exceptions:
*       See items (3) and (4) in the NOTES above. If these assumptions are
*       violated, behavior is undefined.
*
*******************************************************************************/

struct tm * __cdecl localtime (
        const time_t *ptime
        )
{
        REG1 struct tm *ptm;
        long ltime;

        /*
         * Check for illegal time_t value
         */
        if ( (long)*ptime < 0L )
                return( NULL );

#ifdef _WIN32
        __tzset();
#else  /* _WIN32 */
#if defined (_M_MPPC) || defined (_M_M68K)
        _tzset();
#endif  /* defined (_M_MPPC) || defined (_M_M68K) */
#endif  /* _WIN32 */

        if ( (*ptime > 3 * _DAY_SEC) && (*ptime < LONG_MAX - 3 * _DAY_SEC) ) {
                /*
                 * The date does not fall within the first three, or last
                 * three, representable days of the Epoch. Therefore, there
                 * is no possibility of overflowing or underflowing the
                 * time_t representation as we compensate for timezone and
                 * Daylight Savings Time.
                 */

                ltime = (long)*ptime - _timezone;
                ptm = gmtime( (time_t *)&ltime );

                /*
                 * Check and adjust for Daylight Saving Time.
                 */
                if ( _daylight && _isindst( ptm ) ) {
                        ltime -= _dstbias;
                        ptm = gmtime( (time_t *)&ltime );
                        ptm->tm_isdst = 1;
                }
        }
        else {
                ptm = gmtime( ptime );

                /*
                 * The date falls with the first three, or last three days
                 * of the Epoch. It is possible the time_t representation
                 * would overflow or underflow while compensating for
                 * timezone and Daylight Savings Time. Therefore, make the
                 * timezone and Daylight Savings Time adjustments directly
                 * in the tm structure. The beginning of the Epoch is
                 * 00:00:00, 01-01-70 (UTC) and the last representable second
                 * in the Epoch is 03:14:07, 01-19-2038 (UTC). This will be
                 * used in the calculations below.
                 *
                 * First, adjust for the timezone.
                 */
                if ( _isindst(ptm) )
                        ltime = (long)ptm->tm_sec - (_timezone + _dstbias);
                else
                        ltime = (long)ptm->tm_sec - _timezone;
                ptm->tm_sec = (int)(ltime % 60);
                if ( ptm->tm_sec < 0 ) {
                        ptm->tm_sec += 60;
                        ltime -= 60;
                }

                ltime = (long)ptm->tm_min + ltime/60;
                ptm->tm_min = (int)(ltime % 60);
                if ( ptm->tm_min < 0 ) {
                        ptm->tm_min += 60;
                        ltime -= 60;
                }

                ltime = (long)ptm->tm_hour + ltime/60;
                ptm->tm_hour = (int)(ltime % 24);
                if ( ptm->tm_hour < 0 ) {
                        ptm->tm_hour += 24;
                        ltime -=24;
                }

                ltime /= 24;

                if ( ltime > 0L ) {
                        /*
                         * There is no possibility of overflowing the tm_mday
                         * and tm_yday fields since the date can be no later
                         * than January 19.
                         */
                        ptm->tm_wday = (ptm->tm_wday + ltime) % 7;
                        ptm->tm_mday += ltime;
                        ptm->tm_yday += ltime;
                }
                else if ( ltime < 0L ) {
                        /*
                         * It is possible to underflow the tm_mday and tm_yday
                         * fields. If this happens, then adjusted date must
                         * lie in December 1969.
                         */
                        ptm->tm_wday = (ptm->tm_wday + 7 + ltime) % 7;
                        if ( (ptm->tm_mday += ltime) <= 0 ) {
                                ptm->tm_mday += 31;
                                ptm->tm_yday = 364;
                                ptm->tm_mon = 11;
                                ptm->tm_year--;
                        }
                        else {
                                ptm->tm_yday += ltime;
                        }
                }


        }


        return(ptm);
}
