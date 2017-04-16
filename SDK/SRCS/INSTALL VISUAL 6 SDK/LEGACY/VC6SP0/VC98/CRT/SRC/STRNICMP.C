/***
*strnicmp.c - compare n chars of strings, ignoring case
*
*       Copyright (c) 1985-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       defines _strnicmp() - Compares at most n characters of two strings,
*       without regard to case.
*
*******************************************************************************/

#include <cruntime.h>
#include <string.h>

#ifdef _WIN32
#include <mtdll.h>
#include <ctype.h>
#include <setlocal.h>
#include <locale.h>
#endif  /* _WIN32 */

/***
*int _strnicmp(first, last, count) - compares count char of strings, ignore case
*
*Purpose:
*       Compare the two strings for lexical order.  Stops the comparison
*       when the following occurs: (1) strings differ, (2) the end of the
*       strings is reached, or (3) count characters have been compared.
*       For the purposes of the comparison, upper case characters are
*       converted to lower case.
*
*Entry:
*       char *first, *last - strings to compare
*       size_t count - maximum number of characters to compare
*
*Exit:
*       returns <0 if first < last
*       returns 0 if first == last
*       returns >0 if first > last
*
*Exceptions:
*
*******************************************************************************/

int __cdecl _strnicmp (
        const char * first,
        const char * last,
        size_t count
        )
{
        int f,l;
#ifdef _MT
        int local_lock_flag;
#endif  /* _MT */

        if ( count )
        {
#if defined (_WIN32)
            if ( __lc_handle[LC_CTYPE] == _CLOCALEHANDLE ) {
#endif  /* defined (_WIN32) */

                do {
                    if ( ((f = (unsigned char)(*(first++))) >= 'A') &&
                         (f <= 'Z') )
                        f -= 'A' - 'a';

                    if ( ((l = (unsigned char)(*(last++))) >= 'A') &&
                         (l <= 'Z') )
                        l -= 'A' - 'a';

                } while ( --count && f && (f == l) );
#if defined (_WIN32)
            }
            else {
                _lock_locale( local_lock_flag )

                do {
                    f = _tolower_lk( (unsigned char)(*(first++)) );
                    l = _tolower_lk( (unsigned char)(*(last++)) );
                } while (--count && f && (f == l) );

                _unlock_locale( local_lock_flag )
            }
#endif  /* defined (_WIN32) */

            return( f - l );
        }

        return( 0 );
}
