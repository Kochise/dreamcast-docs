/***
*mbtowc.c - Convert multibyte char to wide char.
*
*       Copyright (c) 1990-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       Convert a multibyte character into the equivalent wide character.
*
*******************************************************************************/


#include <cruntime.h>
#include <stdlib.h>
#include <mtdll.h>
#include <errno.h>
#include <dbgint.h>
#include <ctype.h>

#ifndef _MAC
#include <internal.h>
#include <locale.h>
#include <setlocal.h>
#endif  /* _MAC */

/***
*int mbtowc() - Convert multibyte char to wide character.
*
*Purpose:
*       Convert a multi-byte character into the equivalent wide character,
*       according to the LC_CTYPE category of the current locale.
*       [ANSI].
*
*       NOTE:  Currently, the C libraries support the "C" locale only.
*              Non-C locale support now available under _INTL switch.
*Entry:
*       wchar_t  *pwc = pointer to destination wide character
*       const char *s = pointer to multibyte character
*       size_t      n = maximum length of multibyte character to consider
*
*Exit:
*       If s = NULL, returns 0, indicating we only use state-independent
*       character encodings.
*       If s != NULL, returns:  0 (if *s = null char)
*                               -1 (if the next n or fewer bytes not valid mbc)
*                               number of bytes comprising converted mbc
*
*Exceptions:
*
*******************************************************************************/

#ifdef _MT
int __cdecl mbtowc(
        wchar_t  *pwc,
        const char *s,
        size_t n
        )
{
        int retval;
        int local_lock_flag;

        _lock_locale( local_lock_flag )
        retval = _mbtowc_lk(pwc, s, n);
        _unlock_locale( local_lock_flag )
        return retval;
}
#endif  /* _MT */

#ifdef _MT
int __cdecl _mbtowc_lk
#else  /* _MT */
int __cdecl mbtowc
#endif  /* _MT */
        (
        wchar_t  *pwc,
        const char *s,
        size_t n
        )
{
        _ASSERTE (MB_CUR_MAX == 1 || MB_CUR_MAX == 2);

        if ( !s || n == 0 )
            /* indicate do not have state-dependent encodings,
               handle zero length string */
            return 0;

        if ( !*s )
        {
            /* handle NULL char */
            if (pwc)
                *pwc = 0;
            return 0;
        }

#ifndef _MAC

        if ( __lc_handle[LC_CTYPE] == _CLOCALEHANDLE )
        {
            if (pwc)
                *pwc = (wchar_t)(unsigned char)*s;
            return sizeof(char);
        }

        if ( isleadbyte((unsigned char)*s) )
        {
            /* multi-byte char */

            if ( (MB_CUR_MAX <= 1) || ((int)n < MB_CUR_MAX) ||
                 (MultiByteToWideChar( __lc_codepage,
                                      MB_PRECOMPOSED | MB_ERR_INVALID_CHARS,
                                      s,
                                      MB_CUR_MAX,
                                      pwc,
                                      (pwc) ? 1 : 0 ) == 0) )
            {
                /* validate high byte of mbcs char */
                if ( (n < (size_t)MB_CUR_MAX) || (!*(s + 1)) )
                {
                    errno = EILSEQ;
                    return -1;
                }
            }
            return MB_CUR_MAX;
        }
        else {
            /* single byte char */

            if ( MultiByteToWideChar( __lc_codepage,
                                      MB_PRECOMPOSED | MB_ERR_INVALID_CHARS,
                                      s,
                                      1,
                                      pwc,
                                      (pwc) ? 1 : 0 ) == 0 )
            {
                errno = EILSEQ;
                return -1;
            }
            return sizeof(char);
        }

#else  /* _MAC */

        /* stuck the "C" locale again */
        if (pwc)
            *pwc = (wchar_t)(unsigned char)*s;
        return sizeof(char);

#endif  /* _MAC */
}
