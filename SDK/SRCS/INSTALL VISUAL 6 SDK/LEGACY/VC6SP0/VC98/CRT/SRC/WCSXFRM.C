/***
*wcsxfrm.c - Transform a wide-character string using locale information
*
*       Copyright (c) 1988-1998, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       Transform a wide-character string using the locale information as set by
*       LC_COLLATE.
*
*******************************************************************************/


#include <cruntime.h>
#include <windows.h>
#include <string.h>
#include <limits.h>
#include <locale.h>
#include <setlocal.h>
#include <stdlib.h>
#include <mtdll.h>
#include <awint.h>
#include <dbgint.h>

/***
*size_t wcsxfrm() - Transform a string using locale information
*
*Purpose:
*       Transform the wide string pointed to by _string2 and place the
*       resulting wide string into the array pointed to by _string1.
*       No more than _count wide characters are placed into the
*       resulting string (including the null).
*
*       The transformation is such that if wcscmp() is applied to
*       the two transformed strings, the return value is equal to
*       the result of wcscoll() applied to the two original strings.
*       Thus, the conversion must take the locale LC_COLLATE info
*       into account.
*
*       In the C locale, wcsxfrm() simply resolves to wcsncpy()/wcslen().
*
*Entry:
*       wchar_t *_string1       = result string
*       const wchar_t *_string2 = source string
*       size_t _count           = max wide chars to move
*
*       [If _count is 0, _string1 is permitted to be NULL.]
*
*Exit:
*       Length of the transformed string (not including the terminating
*       null).  If the value returned is >= _count, the contents of the
*       _string1 array are indeterminate.
*
*Exceptions:
*       Non-standard: if OM/API error, return INT_MAX.
*
*******************************************************************************/

size_t __cdecl wcsxfrm (
        wchar_t *_string1,
        const wchar_t *_string2,
        size_t _count
        )
{

        int size = INT_MAX;
        unsigned char *bbuffer;
#if defined (_MT)
        int local_lock_flag;
#endif  /* defined (_MT) */

        if (__lc_handle[LC_COLLATE] == _CLOCALEHANDLE) {
            wcsncpy(_string1, _string2, _count);
            return wcslen(_string2);
        }

        _lock_locale( local_lock_flag )

#if defined (_MT)
        if (__lc_handle[LC_COLLATE] == _CLOCALEHANDLE) {
            _unlock_locale( local_lock_flag )
            wcsncpy(_string1, _string2, _count);
            return wcslen(_string2);
        }
#endif  /* defined (_MT) */

        /*
         * When using LCMAP_SORTKEY, LCMapStringW handles BYTES not wide
         * chars. We use a byte buffer to hold bytes and then convert the
         * byte string to a wide char string and return this so it can be
         * compared using wcscmp(). User's buffer is _count wide chars, so
         * use an internal buffer of _count bytes.
         */

        if (NULL == (bbuffer = (unsigned char *)_malloc_crt(_count)))
            goto error_cleanup;

        if ( 0 == (size = __crtLCMapStringW( __lc_handle[LC_COLLATE],
                                             LCMAP_SORTKEY,
                                             _string2,
                                             -1,
                                             (wchar_t *)bbuffer,
                                             _count,
                                             __lc_collate_cp )) )
        {
            /* buffer not big enough, get size required. */

            if ( 0 == (size = __crtLCMapStringW( __lc_handle[LC_COLLATE],
                                                 LCMAP_SORTKEY,
                                                 _string2,
                                                 -1,
                                                 NULL,
                                                 0,
                                                 __lc_collate_cp )) )
                   size = INT_MAX; /* default error */
            else
                size--; /* don't count NULL */

        } else {
            int i;
            /* string successfully mapped, convert to wide char */

            for (i = 0; i < size; i++)
                _string1[i] = (wchar_t)bbuffer[i];

            size--; /* don't count NULL */
        }

error_cleanup:
        _unlock_locale( local_lock_flag )
        _free_crt(bbuffer);

        return (size_t)size;


}

