/***
*wctomb.c - Convert wide character to multibyte character.
*
*       Copyright (c) 1990-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       Convert a wide character into the equivalent multibyte character.
*
*******************************************************************************/


#include <cruntime.h>
#include <stdlib.h>
#include <mtdll.h>
#include <errno.h>

#ifndef _MAC
#include <locale.h>
#include <setlocal.h>
#endif  /* _MAC */

/***
*int wctomb() - Convert wide character to multibyte character.
*
*Purpose:
*       Convert a wide character into the equivalent multi-byte character,
*       according to the LC_CTYPE category of the current locale.
*       [ANSI].
*
*       NOTE:  Currently, the C libraries support the "C" locale only.
*              Non-C locale support now available under _INTL switch.
*Entry:
*       char *s          = pointer to multibyte character
*       wchar_t wchar        = source wide character
*
*Exit:
*       If s = NULL, returns 0, indicating we only use state-independent
*       character encodings.
*       If s != NULL, returns:
*                   -1 (if error) or number of bytes comprising
*                   converted mbc
*
*Exceptions:
*
*******************************************************************************/

#ifdef _MT

int __cdecl wctomb
        (
        char *s,
        wchar_t wchar
        )
{
        int retval;
        int local_lock_flag;

        _lock_locale( local_lock_flag )
        retval = _wctomb_lk(s, wchar);
        _unlock_locale( local_lock_flag )
        return retval;
}

#endif  /* _MT */

#ifdef _MT
int __cdecl _wctomb_lk
#else  /* _MT */
int __cdecl wctomb
#endif  /* _MT */
        (
        char *s,
        wchar_t wchar
        )
{
        if ( !s )
            /* indicate do not have state-dependent encodings */
            return 0;

#ifndef _MAC


        if ( __lc_handle[LC_CTYPE] == _CLOCALEHANDLE )
        {
            if ( wchar > 255 )  /* validate high byte */
            {
                errno = EILSEQ;
                return -1;
            }

            *s = (char) wchar;
            return sizeof(char);
        } else {
            int size;
            BOOL defused = 0;

            if ( ((size = WideCharToMultiByte( __lc_codepage,
                                               WC_COMPOSITECHECK |
                                                WC_SEPCHARS,
                                               &wchar,
                                               1,
                                               s,
                                               MB_CUR_MAX,
                                               NULL,
                                               &defused) ) == 0) ||
                 (defused) )
            {
                errno = EILSEQ;
                return -1;
            }

            return size;
        }

#else  /* _MAC */

        if ( wchar > 255 )  /* validate high byte */
        {
            errno = EILSEQ;
            return -1;
        }

        *s = (char) wchar;
        return sizeof(char);

#endif  /* _MAC */
}
