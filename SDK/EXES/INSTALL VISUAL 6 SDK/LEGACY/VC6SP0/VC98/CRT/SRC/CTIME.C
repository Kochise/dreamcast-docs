/***
*ctime.c - convert time argument into ASCII string
*
*       Copyright (c) 1985-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       contains ctime() - convert time value to string
*
*******************************************************************************/

#include <cruntime.h>
#include <time.h>
#include <stddef.h>
#include <tchar.h>

/***
*_TSCHAR *ctime(time) - converts a time stored as a long to a ASCII string
*
*Purpose:
*       Converts a time stored as a long (time_t) to an ASCII string of
*       the form:
*              Tue May 1 14:25:03 1984
*
*Entry:
*       long *time - time value in XENIX format
*
*Exit:
*       returns pointer to static string or NULL if time is before
*       Jan 1 1980.
*
*Exceptions:
*
*******************************************************************************/

_TSCHAR * __cdecl _tctime (
        const time_t *timp
        )
{
        struct tm *tmtemp;

        if ((tmtemp=localtime(timp)) != NULL)
                return(_tasctime((const struct tm *)tmtemp));
        else
                return(NULL);
}
