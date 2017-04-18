/***
*wcstombs.c - Convert wide char string to multibyte char string.
*
*       Copyright (c) 1990-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       Convert a wide char string into the equivalent multibyte char string.
*
*******************************************************************************/


#include <cruntime.h>
#include <stdlib.h>
#include <limits.h>
#include <internal.h>
#include <mtdll.h>
#include <dbgint.h>
#include <errno.h>

#ifndef _MAC
#include <locale.h>
#include <setlocal.h>
#endif  /* _MAC */

/***
*int __cdecl wcsncnt - count wide characters in a string, up to n.
*
*Purpose:
*       Internal local support function. Counts characters in string including NULL.
*       If NULL not found in n chars, then return n.
*
*Entry:
*       const wchar_t *string   - start of string
*       int n                   - character count
*
*Exit:
*       returns number of wide characters from start of string to
*       NULL (inclusive), up to n.
*
*Exceptions:
*
*******************************************************************************/

static int __cdecl wcsncnt (
        const wchar_t *string,
        int cnt
        )
{
        int n = cnt+1;
        wchar_t *cp = (wchar_t *)string;

        while (--n && *cp)
            cp++;

        if (n && !*cp)
            return cp - string + 1;
        return cnt;
}

/***
*size_t wcstombs() - Convert wide char string to multibyte char string.
*
*Purpose:
*       Convert a wide char string into the equivalent multibyte char string,
*       according to the LC_CTYPE category of the current locale.
*       [ANSI].
*
*       NOTE:  Currently, the C libraries support the "C" locale only.
*              Non-C locale support now available under _INTL switch.
*Entry:
*       char *s            = pointer to destination multibyte char string
*       const wchar_t *pwc = pointer to source wide character string
*       size_t           n = maximum number of bytes to store in s
*
*Exit:
*       If s != NULL, returns    (size_t)-1 (if a wchar cannot be converted)
*       Otherwise:       Number of bytes modified (<=n), not including
*                    the terminating NUL, if any.
*
*Exceptions:
*       Returns (size_t)-1 if s is NULL or invalid mb character encountered.
*
*******************************************************************************/

#ifdef _MT

size_t __cdecl wcstombs
        (
        char * s,
        const wchar_t * pwcs,
        size_t n
        )
{
        int retval;
        int local_lock_flag;

        _lock_locale( local_lock_flag )
        retval = _wcstombs_lk(s, pwcs, n);
        _unlock_locale( local_lock_flag );
        return retval;
}

#endif  /* _MT */

#ifdef _MT
size_t __cdecl _wcstombs_lk
#else  /* _MT */
size_t __cdecl wcstombs
#endif  /* _MT */
        (
        char * s,
        const wchar_t * pwcs,
        size_t n
        )
{
        size_t count = 0;
#ifndef _MAC
        int i, retval;
        char buffer[MB_LEN_MAX];
        BOOL defused = 0;
#endif  /* _MAC */
        if (s && n == 0)
            /* dest string exists, but 0 bytes converted */
            return (size_t) 0;

        _ASSERTE(pwcs != NULL);

#ifndef _MAC


        /* if destination string exists, fill it in */
        if (s)
        {
            if (__lc_handle[LC_CTYPE] == _CLOCALEHANDLE)
            {
                /* C locale: easy and fast */
                while(count < n)
                {
                    if (*pwcs > 255)  /* validate high byte */
                    {
                        errno = EILSEQ;
                        return (size_t)-1;  /* error */
                    }
                    s[count] = (char) *pwcs;
                    if (*pwcs++ == L'\0')
                        return count;
                    count++;
                }
                return count;
            } else {

                if (1 == MB_CUR_MAX)
                {
                    /* If SBCS, one wchar_t maps to one char */

                    /* WideCharToMultiByte will compare past NULL - reset n */
                    if (n > 0)
                        n = wcsncnt(pwcs, n);

                    if ( ((count = WideCharToMultiByte( __lc_codepage,
                                                        WC_COMPOSITECHECK |
                                                            WC_SEPCHARS,
                                                        pwcs,
                                                        n,
                                                        s,
                                                        n,
                                                        NULL,
                                                        &defused )) != 0) &&
                         (!defused) )
                    {
                        if (*(s + count - 1) == '\0')
                            count--; /* don't count NUL */

                        return count;
                    }

                    errno = EILSEQ;
                    return (size_t)-1;
                }
                else {

                    /* If MBCS, wchar_t to char mapping unknown */

                    /* Assume that usually the buffer is large enough */
                    if ( ((count = WideCharToMultiByte( __lc_codepage,
                                                        WC_COMPOSITECHECK |
                                                            WC_SEPCHARS,
                                                        pwcs,
                                                        -1,
                                                        s,
                                                        n,
                                                        NULL,
                                                        &defused )) != 0) &&
                         (!defused) )
                    {
                        return count - 1; /* don't count NUL */
                    }

                    if (defused || GetLastError() != ERROR_INSUFFICIENT_BUFFER)
                    {
                        errno = EILSEQ;
                        return (size_t)-1;
                    }

                    /* buffer not large enough, must do char by char */
                    while (count < n)
                    {
                        if ( ((retval = WideCharToMultiByte( __lc_codepage,
                                                             0,
                                                             pwcs,
                                                             1,
                                                             buffer,
                                                             MB_CUR_MAX,
                                                             NULL,
                                                             &defused )) == 0)
                             || defused )
                        {
                            errno = EILSEQ;
                            return (size_t)-1;
                        }

                        if (count + retval > n)
                            return count;

                        for (i = 0; i < retval; i++, count++) /* store character */
                            if((s[count] = buffer[i])=='\0')
                                return count;

                        pwcs++;
                    }

                    return count;
                }
            }
        }
        else { /* s == NULL, get size only, pwcs must be NUL-terminated */

            if (__lc_handle[LC_CTYPE] == _CLOCALEHANDLE)
                return wcslen(pwcs);
            else {
                if (((count=WideCharToMultiByte(__lc_codepage,
                WC_COMPOSITECHECK | WC_SEPCHARS,
                pwcs, -1, NULL, 0, NULL, &defused)) == 0) || (defused))
                {
                    errno = EILSEQ;
                    return (size_t)-1;
                }

                return count - 1;
            }
        }

#else  /* _MAC */

        /* if destination string exists, fill it in */
        if (s)
        {
            /* C locale: easy and fast */
            while(count < n)
            {
                if (*pwcs > 255)  /* validate high byte */
                {
                    errno = EILSEQ;
                    return (size_t)-1;  /* error */
                }
                s[count] = (char) *pwcs;
                if (*pwcs++ == L'\0')
                    return count;
                count++;
            }
            return count;

        } else { /* s == NULL, get size only, pwcs must be NUL-terminated */
            const wchar_t *eos = pwcs;

            while( *eos++ ) ;

            return( (size_t)(eos - pwcs - 1) );
        }

#endif  /* _MAC */
}
