/***
*mbstowcs.c - Convert multibyte char string to wide char string.
*
*       Copyright (c) 1990-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       Convert a multibyte char string into the equivalent wide char string.
*
*******************************************************************************/


#ifndef _MAC
#include <internal.h>
#include <locale.h>
#include <setlocal.h>
#include <errno.h>
#endif  /* _MAC */

#include <cruntime.h>
#include <stdlib.h>
#include <string.h>
#include <mtdll.h>
#include <dbgint.h>

#include <stdio.h>

/***
*size_t mbstowcs() - Convert multibyte char string to wide char string.
*
*Purpose:
*       Convert a multi-byte char string into the equivalent wide char string,
*       according to the LC_CTYPE category of the current locale.
*       [ANSI].
*
*Entry:
*       wchar_t *pwcs = pointer to destination wide character string buffer
*       const char *s = pointer to source multibyte character string
*       size_t      n = maximum number of wide characters to store
*
*Exit:
*       If s != NULL, returns:  number of words modified (<=n)
*               (size_t)-1 (if invalid mbcs)
*
*Exceptions:
*       Returns (size_t)-1 if s is NULL or invalid mbcs character encountered
*
*******************************************************************************/

#ifdef _MT

size_t __cdecl mbstowcs
(
        wchar_t  *pwcs,
        const char *s,
        size_t n
        )
{
        size_t retval;
        int local_lock_flag;

        _lock_locale( local_lock_flag )
        retval = _mbstowcs_lk(pwcs, s, n);
        _unlock_locale( local_lock_flag )
        return retval;
}
#endif  /* _MT */

#ifdef _MT
size_t __cdecl _mbstowcs_lk
#else  /* _MT */
size_t __cdecl mbstowcs
#endif  /* _MT */
        (
        wchar_t  *pwcs,
        const char *s,
        size_t n
        )
{
        size_t count = 0;

        if (pwcs && n == 0)
            /* dest string exists, but 0 bytes converted */
            return (size_t) 0;

        _ASSERTE(s != NULL);

#ifndef _MAC

        /* if destination string exists, fill it in */
        if (pwcs)
        {
            if (__lc_handle[LC_CTYPE] == _CLOCALEHANDLE)
            {
                /* C locale: easy and fast */
                while (count < n)
                {
                    *pwcs = (wchar_t) ((unsigned char)s[count]);
                    if (!s[count])
                        return count;
                    count++;
                    pwcs++;
                }
                return count;

            } else {
                int bytecnt, charcnt;
                unsigned char *p;

                /* Assume that the buffer is large enough */
                if ( (count = MultiByteToWideChar( __lc_codepage,
                                                   MB_PRECOMPOSED |
                                                    MB_ERR_INVALID_CHARS,
                                                   s,
                                                   -1,
                                                   pwcs,
                                                   n )) != 0 )
                    return count - 1; /* don't count NUL */

                if (GetLastError() != ERROR_INSUFFICIENT_BUFFER)
                {
                    errno = EILSEQ;
                    return (size_t)-1;
                }

                /* User-supplied buffer not large enough. */

                /* How many bytes are in n characters of the string? */
                charcnt = n;
                for (p = (unsigned char *)s; (charcnt-- && *p); p++)
                {
                    if (isleadbyte(*p))
                        p++;
                }
                bytecnt = ((int) ((char *)p - (char *)s));

                if ( (count = MultiByteToWideChar( __lc_codepage,
                                                   MB_PRECOMPOSED,
                                                   s,
                                                   bytecnt,
                                                   pwcs,
                                                   n )) == 0 )
                {
                    errno = EILSEQ;
                    return (size_t)-1;
                }

                return count; /* no NUL in string */
            }
        }
        else { /* pwcs == NULL, get size only, s must be NUL-terminated */
            if (__lc_handle[LC_CTYPE] == _CLOCALEHANDLE)
                return strlen(s);

            else {
                if ( (count = MultiByteToWideChar( __lc_codepage,
                                                   MB_PRECOMPOSED |
                                                    MB_ERR_INVALID_CHARS,
                                                   s,
                                                   -1,
                                                   NULL,
                                                   0 )) == 0 )
                {
                    errno = EILSEQ;
                    return (size_t)-1;
                }

                return count - 1;
            }
        }

#else  /* _MAC */

        /* if destination string exists, fill it in */
        if (pwcs)
        {
            /* C locale: easy and fast */
            while (count < n)
            {
                *pwcs = (wchar_t) ((unsigned char)s[count]);
                if (!s[count])
                    return count;
                count++;
                pwcs++;
            }
            return count;

        } else { /* pwcs == NULL, get size only, s must be NUL-terminated */
            return strlen(s);
        }

#endif  /* _MAC */
}
