/***
*wcslwr.c - routine to map upper-case characters in a wchar_t string
*       to lower-case
*
*       Copyright (c) 1985-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       Converts all the upper case characters in a wchar_t string
*       to lower case, in place.
*
*******************************************************************************/


#include <cruntime.h>
#include <string.h>
#include <malloc.h>
#include <locale.h>
#include <ctype.h>
#include <setlocal.h>
#include <mtdll.h>
#include <awint.h>
#include <dbgint.h>

/***
*wchar_t *_wcslwr(string) - map upper-case characters in a string to lower-case
*
*Purpose:
*       wcslwr converts upper-case characters in a null-terminated wchar_t
*       string to their lower-case equivalents.  The result may be longer or
*       shorter than the original string.  Assumes enough space in string
*       to hold the result.
*
*Entry:
*       wchar_t *wsrc - wchar_t string to change to lower case
*
*Exit:
*       input string address
*
*Exceptions:
*       on an error, the original string is unaltered
*
*******************************************************************************/

wchar_t * __cdecl _wcslwr (
        wchar_t * wsrc
        )
{

        wchar_t *p;             /* traverses string for C locale conversion */
        wchar_t *wdst = NULL;   /* wide version of string in alternate case */
        int dstlen;             /* len of wdst string, wide chars, with null */
#if defined (_MT)
        int local_lock_flag;
#endif  /* defined (_MT) */

        if (__lc_handle[LC_CTYPE] == _CLOCALEHANDLE) {
                for (p=wsrc; *p; p++)
                        if ( (*p >= (wchar_t)L'A') && (*p <= (wchar_t)L'Z') )
                                *p = *p - L'A' + L'a';
                return (wsrc);
        } /* C locale */

        _lock_locale( local_lock_flag )

#if defined (_MT)
        if (__lc_handle[LC_CTYPE] == _CLOCALEHANDLE) {
                _unlock_locale( local_lock_flag )
                for (p=wsrc; *p; p++)
                        if ( (*p >= (wchar_t)L'A') && (*p <= (wchar_t)L'Z') )
                                *p = *p - L'A' + L'a';
                return (wsrc);
        } /* C locale */
#endif  /* defined (_MT) */

        /* Inquire size of wdst string */
        if ((dstlen=__crtLCMapStringW(__lc_handle[LC_CTYPE], LCMAP_LOWERCASE,
            wsrc, -1, wdst, 0, 0)) == 0)
                goto error_cleanup;

        /* Allocate space for wdst */
        if ((wdst = (wchar_t *) _malloc_crt(dstlen*sizeof(wchar_t))) == NULL)
                goto error_cleanup;

        /* Map wrc string to wide-character wdst string in alternate case */
        if (__crtLCMapStringW(__lc_handle[LC_CTYPE], LCMAP_LOWERCASE,
            wsrc, -1, wdst, dstlen, 0) == 0)
                goto error_cleanup;

        /* Copy wdst string to user string */
        wcscpy (wsrc, wdst);

error_cleanup:
        _unlock_locale( local_lock_flag )
        _free_crt (wdst);

        return (wsrc);
}

