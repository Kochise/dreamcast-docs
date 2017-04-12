/***
*_mbslen.c - Return number of multibyte characters in a multibyte string
*
*       Copyright (c) 1989-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       Return number of multibyte characters in a multibyte string
*       excluding the terminal null.  Locale-dependent.
*
*******************************************************************************/

#include <cruntime.h>
#include <internal.h>
#include <stdlib.h>
#include <ctype.h>
#include <mtdll.h>
#include <locale.h>
#include <setlocal.h>
#include <dbgint.h>

/***
*_mbstrlen - Return number of multibyte characters in a multibyte string
*
*Purpose:
*       Return number of multibyte characters in a multibyte string
*       excluding the terminal null.  Locale-dependent.
*
*Entry:
*       char *s = string
*
*Exit:
*       Returns the number of multibyte characters in the string, or
*       (size_t)-1 if the string contains an invalid multibyte character.
*
*Exceptions:
*
*******************************************************************************/

size_t __cdecl _mbstrlen(
        const char *s
        )
{
        int n;
#ifdef _MT
        int local_lock_flag;
#endif  /* _MT */

        _ASSERTE (MB_CUR_MAX == 1 || MB_CUR_MAX == 2);

        if ( MB_CUR_MAX == 1 )
            /* handle single byte character sets */
            return (int)strlen(s);


        _lock_locale( local_lock_flag )

        /* verify all valid MB chars */
        if ( MultiByteToWideChar( __lc_codepage,
                                  MB_PRECOMPOSED | MB_ERR_INVALID_CHARS,
                                  s,
                                  -1,
                                  NULL,
                                  0 )
             == 0 ) {
            /* bad MB char */
            _unlock_locale( local_lock_flag )
            return (size_t)-1;
        }

        /* count MB chars */
        for (n = 0; *s; n++, s++) {
            if ( isleadbyte((unsigned char)*s) ) {
                if (*++s == '\0')
                    break;
            }
        }

        _unlock_locale( local_lock_flag )


        return(n);
}
