/***
*strupr.c - routine to map lower-case characters in a string to upper-case
*
*   Copyright (c) 1985-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*   Converts all the lower case characters in string to upper case
*   in place.
*
*******************************************************************************/

#include <cruntime.h>
#include <string.h>

#ifdef _WIN32
#include <malloc.h>
#include <locale.h>
#include <setlocal.h>
#include <limits.h> /* for INT_MAX */
#include <mtdll.h>
#include <awint.h>
#include <dbgint.h>
#endif  /* _WIN32 */

/***
*char *_strupr(string) - map lower-case characters in a string to upper-case
*
*Purpose:
*   _strupr() converts lower-case characters in a null-terminated string
*   to their upper-case equivalents.  Conversion is done in place and
*   characters other than lower-case letters are not modified.
*
*   In the C locale, this function modifies only 7-bit ASCII characters
*   in the range 0x61 through 0x7A ('a' through 'z').
*
*   If the locale is not the 'C' locale, MapStringW() is used to do
*   the work.  Assumes enough space in the string to hold result.
*
*Entry:
*   char *string - string to change to upper case
*
*Exit:
*   input string address
*
*Exceptions:
*   The original string is returned unchanged on any error.
*
*******************************************************************************/

char * __cdecl _strupr (
    char * string
    )
{
#if defined (_WIN32)

    int dstlen;                 /* len of dst string, with null  */
    unsigned char *dst = NULL;  /* wide version of string in alternate case */
#if defined (_MT)
    int local_lock_flag;
#endif  /* defined (_MT) */

    if (__lc_handle[LC_CTYPE] == _CLOCALEHANDLE)
    {
        char *cp;       /* traverses string for C locale conversion */
        for (cp = string; *cp; ++cp)
        {
            if ('a' <= *cp && *cp <= 'z')
                *cp += 'A' - 'a';
        }
        return(string);
    } /* C locale */

    _lock_locale( local_lock_flag )

#if defined (_MT)
    if (__lc_handle[LC_CTYPE] == _CLOCALEHANDLE)
    {
        char *cp;       /* traverses string for C locale conversion */
        _unlock_locale( local_lock_flag )

        for (cp=string; *cp; ++cp)
        {
            if ('a' <= *cp && *cp <= 'z')
                *cp += 'A' - 'a';
        }

        return(string);
    } /* C locale */
#endif  /* defined (_MT) */

    if (0 == (dstlen =__crtLCMapStringA(__lc_handle[LC_CTYPE],
                                       LCMAP_UPPERCASE, string, -1,
                                       NULL, 0, 0, TRUE)))
        goto error_cleanup;

    /* Allocate space for dst */
    if (NULL == (dst = (unsigned char *)
                             _malloc_crt(dstlen * sizeof(unsigned char))))
        goto error_cleanup;

    /* Map src string to dst string in alternate case */
    if (0 == __crtLCMapStringA(__lc_handle[LC_CTYPE], LCMAP_UPPERCASE,
            string, -1, dst, dstlen, 0, TRUE))
        goto error_cleanup;

    /* copy dst string to return string */
    strcpy(string, dst);

error_cleanup:
    _unlock_locale( local_lock_flag )
    _free_crt (dst);
    return (string);

#else  /* defined (_WIN32) */

    char * cp;

    for (cp=string; *cp; ++cp)
    {
        if ('a' <= *cp && *cp <= 'z')
            *cp += 'A' - 'a';
    }

    return(string);

#endif  /* defined (_WIN32) */
}
