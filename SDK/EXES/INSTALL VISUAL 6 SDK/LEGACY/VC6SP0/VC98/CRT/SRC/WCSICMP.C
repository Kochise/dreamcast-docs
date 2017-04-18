/***
*wcsicmp.c - contains case-insensitive wide string comp routine _wcsicmp
*
*       Copyright (c) 1985-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       contains _wcsicmp()
*
*******************************************************************************/


#include <cruntime.h>
#include <setlocal.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>
#include <setlocal.h>
#include <mtdll.h>

/***
*int _wcsicmp(dst, src) - compare wide-character strings, ignore case
*
*Purpose:
*       _wcsicmp perform a case-insensitive wchar_t string comparision.
*       _wcsicmp is independent of locale.
*
*Entry:
*       wchar_t *dst, *src - strings to compare
*
*Return:
*       <0 if dst < src
*        0 if dst = src
*       >0 if dst > src
*       This range of return values may differ from other *cmp/*coll functions.
*
*Exceptions:
*
*******************************************************************************/

int __cdecl _wcsicmp (
        const wchar_t * dst,
        const wchar_t * src
        )
{
        wchar_t f,l;
#if defined (_MT)
        int local_lock_flag;
#endif  /* defined (_MT) */

        if ( __lc_handle[LC_CTYPE] == _CLOCALEHANDLE ) {
            do  {
                f = ((*dst <= L'Z') && (*dst >= L'A'))
                    ? *dst + L'a' - L'A'
                    : *dst;
                l = ((*src <= L'Z') && (*src >= L'A'))
                    ? *src + L'a' - L'A'
                    : *src;
                dst++;
                src++;
            } while ( (f) && (f == l) );
        }
        else {
            _lock_locale( local_lock_flag );
            do  {
                f = _towlower_lk( (unsigned short)(*(dst++)) );
                l = _towlower_lk( (unsigned short)(*(src++)) );
            } while ( (f) && (f == l) );
            _unlock_locale( local_lock_flag )
        }

        return (int)(f - l);
}

