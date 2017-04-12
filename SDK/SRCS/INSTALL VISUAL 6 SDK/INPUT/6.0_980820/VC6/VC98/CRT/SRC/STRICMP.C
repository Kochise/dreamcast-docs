/***
*stricmp.c - contains case-insensitive string comp routine _stricmp/_strcmpi
*
*       Copyright (c) 1985-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       contains _stricmp(), also known as _strcmpi()
*
*******************************************************************************/

#include <cruntime.h>
#include <string.h>

#ifdef _WIN32
#include <mtdll.h>
#include <setlocal.h>
#include <ctype.h>
#include <locale.h>
#endif  /* _WIN32 */

/***
*int _stricmp(dst, src), _strcmpi(dst, src) - compare strings, ignore case
*
*Purpose:
*       _stricmp/_strcmpi perform a case-insensitive string comparision.
*       For differences, upper case letters are mapped to lower case.
*       Thus, "abc_" < "ABCD" since "_" < "d".
*
*Entry:
*       char *dst, *src - strings to compare
*
*Return:
*       <0 if dst < src
*        0 if dst = src
*       >0 if dst > src
*
*Exceptions:
*
*******************************************************************************/

int __cdecl _stricmp (
        const char * dst,
        const char * src
        )
{
        return( _strcmpi(dst,src) );
}


int __cdecl _strcmpi(const char * dst, const char * src)
{
        int f,l;
#ifdef _MT
        int local_lock_flag;
#endif  /* _MT */

#if defined (_WIN32)
        if ( __lc_handle[LC_CTYPE] == _CLOCALEHANDLE ) {
#endif  /* defined (_WIN32) */
            do {
                if ( ((f = (unsigned char)(*(dst++))) >= 'A') && (f <= 'Z') )
                    f -= ('A' - 'a');

                if ( ((l = (unsigned char)(*(src++))) >= 'A') && (l <= 'Z') )
                    l -= ('A' - 'a');
            } while ( f && (f == l) );
#if defined (_WIN32)
        }
        else {
            _lock_locale( local_lock_flag )
            do {
                f = _tolower_lk( (unsigned char)(*(dst++)) );
                l = _tolower_lk( (unsigned char)(*(src++)) );
            } while ( f && (f == l) );
            _unlock_locale( local_lock_flag )
        }
#endif  /* defined (_WIN32) */

        return(f - l);
}
