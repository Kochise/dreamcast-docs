/***
*towupper.c - convert wide character to upper case
*
*       Copyright (c) 1991-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       Defines towupper().
*
*******************************************************************************/


#include <cruntime.h>
#include <ctype.h>
#include <stdio.h>
#include <locale.h>
#include <setlocal.h>
#include <mtdll.h>
#include <awint.h>

/***
*wchar_t towupper(c) - convert wide character to upper case
*
*Purpose:
*       towupper() returns the uppercase equivalent of its argument
*
*Entry:
*       c - wchar_t value of character to be converted
*
*Exit:
*       if c is a lower case letter, returns wchar_t value of upper case
*       representation of c. otherwise, it returns c.
*
*Exceptions:
*
*******************************************************************************/

wchar_t __cdecl towupper (
        wchar_t c
        )
{

#ifdef _MT

        int local_lock_flag;

        if (__lc_handle[LC_CTYPE] == _CLOCALEHANDLE)
        {
            if ( (c >= L'a') && (c <= L'z') )
                c = c - L'a' + L'A';
            return c;
        }

        _lock_locale( local_lock_flag )

        c = _towupper_lk(c);

        _unlock_locale( local_lock_flag )

        return c;
}

/***
*wchar_t _towupper_lk(c) - convert wide character to upper case
*
*Purpose:
*       Multi-thread function only! Non-locking version of towupper.
*
*Entry:
*
*Exit:
*
*Exceptions:
*
*******************************************************************************/

wchar_t __cdecl _towupper_lk (
        wchar_t c
        )
{

#endif  /* _MT */

        wchar_t widechar;

        if (c == WEOF)
            return c;

        if (__lc_handle[LC_CTYPE] == _CLOCALEHANDLE) {
            if ( (c >= L'a') && (c <= L'z') )
                c = c - L'a' + L'A';
            return c;
        }

        /* if checking case of c does not require API call, do it */
        if (c < 256) {
            if (!iswlower(c)) {
                return c;
            }
        }

        /* convert wide char to uppercase */
        if ( 0 == __crtLCMapStringW( __lc_handle[LC_CTYPE],
                                     LCMAP_UPPERCASE,
                                     (LPCWSTR)&c,
                                     1,
                                     (LPWSTR)&widechar,
                                     1,
                                     0) )
        {
            return c;
        }

        return widechar;

}
