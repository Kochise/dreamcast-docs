/***
*strcoll.c - Collate locale strings
*
*       Copyright (c) 1988-1998, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       Compare two strings using the locale LC_COLLATE information.
*
*******************************************************************************/

#include <cruntime.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
#include <stdlib.h>
#include <malloc.h>
#include <locale.h>
#include <setlocal.h>
#include <mtdll.h>
#include <errno.h>
#include <awint.h>
#endif  /* _WIN32 */

/***
*int strcoll() - Collate locale strings
*
*Purpose:
*       Compare two strings using the locale LC_COLLATE information.
*       [ANSI].
*
*       Non-C locale support available under _INTL switch.
*       In the C locale, strcoll() simply resolves to strcmp().
*Entry:
*       const char *s1 = pointer to the first string
*       const char *s2 = pointer to the second string
*
*Exit:
*       Less than 0    = first string less than second string
*       0              = strings are equal
*       Greater than 0 = first string greater than second string
*
*Exceptions:
*       _NLSCMPERROR    = error
*       errno = EINVAL
*
*******************************************************************************/

int __cdecl strcoll (
        const char *_string1,
        const char *_string2
        )
{
#if defined (_WIN32)

        int ret;
#if defined (_MT)
        int local_lock_flag;
#endif  /* defined (_MT) */

        if (__lc_handle[LC_COLLATE] == _CLOCALEHANDLE) {
                return strcmp(_string1, _string2);
        }

        _lock_locale( local_lock_flag )

#if defined (_MT)
        if (__lc_handle[LC_COLLATE] == _CLOCALEHANDLE) {
                _unlock_locale( local_lock_flag )
                return strcmp(_string1, _string2);
        }
#endif  /* defined (_MT) */

        if ( 0 == (ret = __crtCompareStringA( __lc_handle[LC_COLLATE],
                                              SORT_STRINGSORT,
                                              _string1,
                                              -1,
                                              _string2,
                                              -1,
                                              __lc_collate_cp )) )
            goto error_cleanup;

        _unlock_locale( local_lock_flag )
        return (ret - 2);

error_cleanup:

        _unlock_locale( local_lock_flag )
        errno = EINVAL;
        return _NLSCMPERROR;

#else  /* defined (_WIN32) */

        return strcmp(_string1,_string2);

#endif  /* defined (_WIN32) */
}
