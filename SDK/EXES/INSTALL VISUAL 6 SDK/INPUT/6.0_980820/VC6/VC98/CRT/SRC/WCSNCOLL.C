/***
*wcsncoll.c - Collate wide-character locale strings
*
*       Copyright (c) 1994-1998, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       Compare two wchar_t strings using the locale LC_COLLATE information.
*       Compares at most n characters of two strings.
*
*******************************************************************************/


#include <cruntime.h>
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <setlocal.h>
#include <mtdll.h>
#include <errno.h>
#include <awint.h>

/***
*int _wcsncoll() - Collate wide-character locale strings
*
*Purpose:
*       Compare two wchar_t strings using the locale LC_COLLATE information
*       Compares at most n characters of two strings.
*       In the C locale, _wcsncmp() is used to make the comparison.
*
*Entry:
*       const wchar_t *s1 = pointer to the first string
*       const wchar_t *s2 = pointer to the second string
*       size_t count - maximum number of characters to compare
*
*Exit:
*       -1 = first string less than second string
*        0 = strings are equal
*        1 = first string greater than second string
*       This range of return values may differ from other *cmp/*coll functions.
*
*Exceptions:
*       _NLSCMPERROR    = error
*       errno = EINVAL
*
*******************************************************************************/

int __cdecl _wcsncoll (
        const wchar_t *_string1,
        const wchar_t *_string2,
        size_t count
        )
{

        int ret;
#if defined (_MT)
        int local_lock_flag;
#endif  /* defined (_MT) */

        if (!count)
            return 0;

        if (__lc_handle[LC_COLLATE] == _CLOCALEHANDLE) {
                return wcsncmp(_string1, _string2, count);
        }

        _lock_locale( local_lock_flag )

#if defined (_MT)
        if (__lc_handle[LC_COLLATE] == _CLOCALEHANDLE) {
                _unlock_locale( local_lock_flag )
                return wcsncmp(_string1, _string2, count);
        }
#endif  /* defined (_MT) */

        if ( 0 == (ret = __crtCompareStringW( __lc_handle[LC_COLLATE],
                                              SORT_STRINGSORT,
                                              _string1,
                                              count,
                                              _string2,
                                              count,
                                              __lc_collate_cp )) )
        {
                _unlock_locale( local_lock_flag )
                errno = EINVAL;
                return _NLSCMPERROR;
        }

        _unlock_locale( local_lock_flag )
        return (ret - 2);

}

