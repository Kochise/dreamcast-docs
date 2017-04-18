/***
*towlower.c - convert wide character to lower case
*
*       Copyright (c) 1991-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       Defines towlower().
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
*wchar_t towlower(c) - convert wide character to lower case
*
*Purpose:
*       towlower() returns the lowercase equivalent of its argument
*
*Entry:
*       c - wchar_t value of character to be converted
*
*Exit:
*       if c is an upper case letter, returns wchar_t value of lower case
*       representation of c. otherwise, it returns c.
*
*Exceptions:
*
*******************************************************************************/

wchar_t __cdecl towlower (
        wchar_t c
        )
{

#ifdef _MT

        int local_lock_flag;

        if ( c == WEOF )
            return c;

        if ( __lc_handle[LC_CTYPE] == _CLOCALEHANDLE ) {
            if ( (c >= L'A') && (c <= L'Z') )
                c = c - L'A' + L'a';
            return c;
        }

        _lock_locale( local_lock_flag )

        c = _towlower_lk(c);

        _unlock_locale( local_lock_flag )

        return c;
}

/***
*wchar_t _towlower_lk(c) - convert wide character to lower case
*
*Purpose:
*       Multi-thread function only! Non-locking version of towlower.
*
*Entry:
*
*Exit:
*
*Exceptions:
*
*******************************************************************************/

wchar_t __cdecl _towlower_lk (
        wchar_t c
        )
{

#endif  /* _MT */

        wchar_t widechar;

        if (c == WEOF)
            return c;


        if (__lc_handle[LC_CTYPE] == _CLOCALEHANDLE) {
            if ( (c >= L'A') && (c <= L'Z') )
                c = c - L'A' + L'a';
            return c;
        }

        /* if checking case of c does not require API call, do it */
        if (c < 256) {
            if (!iswupper(c)) {
                return c;
            }
        }

        /* convert wide char to lowercase */
        if ( 0 == __crtLCMapStringW( __lc_handle[LC_CTYPE],
                                     LCMAP_LOWERCASE,
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
