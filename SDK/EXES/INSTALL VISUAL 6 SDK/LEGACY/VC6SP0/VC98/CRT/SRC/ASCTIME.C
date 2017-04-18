/***
*asctime.c - convert date/time structure to ASCII string
*
*       Copyright (c) 1985-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       Contains asctime() - convert a date/time structure to ASCII string.
*
*******************************************************************************/

#include <cruntime.h>
#include <time.h>
#include <internal.h>
#include <mtdll.h>
#ifdef _MT
#include <malloc.h>
#include <stddef.h>
#endif  /* _MT */
#include <tchar.h>
#include <dbgint.h>

#define _ASCBUFSIZE   26
static _TSCHAR buf[_ASCBUFSIZE];

/*
** This prototype must be local to this file since the procedure is static
*/

static _TSCHAR * __cdecl store_dt(_TSCHAR *, int);

static _TSCHAR * __cdecl store_dt (
        REG1 _TSCHAR *p,
        REG2 int val
        )
{
        *p++ = (_TSCHAR)(_T('0') + val / 10);
        *p++ = (_TSCHAR)(_T('0') + val % 10);
        return(p);
}


/***
*char *asctime(time) - convert a structure time to ascii string
*
*Purpose:
*       Converts a time stored in a struct tm to a charcater string.
*       The string is always exactly 26 characters of the form
*               Tue May 01 02:34:55 1984\n\0
*
*Entry:
*       struct tm *time - ptr to time structure
*
*Exit:
*       returns pointer to static string with time string.
*
*Exceptions:
*
*******************************************************************************/

_TSCHAR * __cdecl _tasctime (
        REG1 const struct tm *tb
        )
{
#ifdef _MT

        _ptiddata ptd = _getptd();

        REG2 _TSCHAR *p;                        /* will point to asctime buffer */
        _TSCHAR *retval;                        /* holds retval pointer */

#else  /* _MT */

        REG2 _TSCHAR *p = buf;

#endif  /* _MT */

        int day, mon;
        int i;

#ifdef _MT

        /* Use per thread buffer area (malloc space, if necessary) */

#ifdef _UNICODE
        if ( (ptd->_wasctimebuf != NULL) || ((ptd->_wasctimebuf =
            (wchar_t *)_malloc_crt(_ASCBUFSIZE * sizeof(wchar_t))) != NULL) )
                p = ptd->_wasctimebuf;
#else  /* _UNICODE */
        if ( (ptd->_asctimebuf != NULL) || ((ptd->_asctimebuf =
            (char *)_malloc_crt(_ASCBUFSIZE * sizeof(char))) != NULL) )
                p = ptd->_asctimebuf;
#endif  /* _UNICODE */
        else
                p = buf;        /* error: use static buffer */

        retval = p;                     /* save return value for later */

#endif  /* _MT */

        /* copy day and month names into the buffer */

        day = tb->tm_wday * 3;          /* index to correct day string */
        mon = tb->tm_mon * 3;           /* index to correct month string */
        for (i=0; i < 3; i++,p++) {
                *p = *(__dnames + day + i);
                *(p+4) = *(__mnames + mon + i);
        }

        *p = _T(' ');                   /* blank between day and month */

        p += 4;

        *p++ = _T(' ');
        p = store_dt(p, tb->tm_mday);   /* day of the month (1-31) */
        *p++ = _T(' ');
        p = store_dt(p, tb->tm_hour);   /* hours (0-23) */
        *p++ = _T(':');
        p = store_dt(p, tb->tm_min);    /* minutes (0-59) */
        *p++ = _T(':');
        p = store_dt(p, tb->tm_sec);    /* seconds (0-59) */
        *p++ = _T(' ');
        p = store_dt(p, 19 + (tb->tm_year/100)); /* year (after 1900) */
        p = store_dt(p, tb->tm_year%100);
        *p++ = _T('\n');
        *p = _T('\0');


#ifdef _MT
        return (retval);
#else  /* _MT */
        return ((_TSCHAR *) buf);
#endif  /* _MT */
}
