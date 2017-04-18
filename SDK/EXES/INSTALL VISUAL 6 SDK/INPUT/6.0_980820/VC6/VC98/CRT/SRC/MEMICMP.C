/***
*memicmp.c - compare memory, ignore case
*
*   Copyright (c) 1988-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       defines _memicmp() - compare two blocks of memory for lexical
*       order.  Case is ignored in the comparison.
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

#define _TOLOWER(c) ( ((c) >= 'A') && ((c) <= 'Z') ? ((c) - 'A' + 'a') :\
              (c) )

/***
*int _memicmp(first, last, count) - compare two blocks of memory, ignore case
*
*Purpose:
*   Compares count bytes of the two blocks of memory stored at first
*   and last.  The characters are converted to lowercase before
*   comparing (not permanently), so case is ignored in the search.
*
*Entry:
*   char *first, *last - memory buffers to compare
*   unsigned count - maximum length to compare
*
*Exit:
*   returns < 0 if first < last
*   returns 0 if first == last
*   returns > 0 if first > last
*
*Uses:
*
*Exceptions:
*
*******************************************************************************/

int __cdecl _memicmp (
        const void * first,
        const void * last,
        unsigned int count
        )
{
        int f = 0;
        int l = 0;
#ifdef _MT
        int local_lock_flag;
#endif  /* _MT */

#if defined (_WIN32)
        if ( __lc_handle[LC_CTYPE] == _CLOCALEHANDLE ) {
#endif  /* defined (_WIN32) */
            while ( count-- )
            {
                if ( (*(unsigned char *)first == *(unsigned char *)last) ||
                     ((f = _TOLOWER( *(unsigned char *)first )) ==
                      (l = _TOLOWER( *(unsigned char *)last ))) )
                {
                    first = (char *)first + 1;
                    last = (char *)last + 1;
                }
                else
                    break;
            }
#if defined (_WIN32)
        }
        else {
            _lock_locale( local_lock_flag )
            while ( count-- )
                if ( (*(unsigned char *)first == *(unsigned char *)last) ||
                     ((f = _tolower_lk( *(unsigned char *)first )) ==
                      (l = _tolower_lk( *(unsigned char *)last ))) )
                {
                    first = (char *)first + 1;
                    last = (char *)last + 1;
                }
                else
                    break;
            _unlock_locale( local_lock_flag )
        }
#endif  /* defined (_WIN32) */

        return ( f - l );
}
