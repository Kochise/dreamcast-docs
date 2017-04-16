/***
*strlwr.c - routine to map upper-case characters in a string to lower-case
*
*       Copyright (c) 1985-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       Converts all the upper case characters in a string to lower case,
*       in place.
*
*******************************************************************************/

#include <cruntime.h>
#include <string.h>

#ifdef _WIN32
#include <malloc.h>
#include <locale.h>
#include <setlocal.h>
#include <limits.h>     /* for INT_MAX */
#include <mtdll.h>
#include <awint.h>
#include <dbgint.h>
#endif  /* _WIN32 */

/***
*char *_strlwr(string) - map upper-case characters in a string to lower-case
*
*Purpose:
*       _strlwr() converts upper-case characters in a null-terminated string
*       to their lower-case equivalents.  Conversion is done in place and
*       characters other than upper-case letters are not modified.
*
*       In the C locale, this function modifies only 7-bit ASCII characters
*       in the range 0x41 through 0x5A ('A' through 'Z').
*
*       If the locale is not the 'C' locale, MapString() is used to do
*       the work.  Assumes enough space in the string to hold result.
*
*Entry:
*       char *string - string to change to lower case
*
*Exit:
*       input string address
*
*Exceptions:
*       The original string is returned unchanged on any error.
*
*******************************************************************************/

char * __cdecl _strlwr (
        char * string
        )
{
#if defined (_WIN32)

        int dstlen;                 /* len of dst string, with null  */
        unsigned char *dst = NULL;  /* destination string */
#if defined (_MT)
        int local_lock_flag;
#endif  /* defined (_MT) */

        if (__lc_handle[LC_CTYPE] == _CLOCALEHANDLE)
        {
        char *cp;               /* traverses string for C locale conversion */

                for (cp=string; *cp; ++cp)
                {
                        if ('A' <= *cp && *cp <= 'Z')
                                *cp += 'a' - 'A';
                }

                return(string);
        } /* C locale */

        _lock_locale( local_lock_flag )

#if defined (_MT)

        if (__lc_handle[LC_CTYPE] == _CLOCALEHANDLE)
        {
        char *cp;               /* traverses string for C locale conversion */
                _unlock_locale( local_lock_flag )

                for (cp=string; *cp; ++cp)
                {
                        if ('A' <= *cp && *cp <= 'Z')
                                *cp += 'a' - 'A';
                }

                return(string);
        } /* C locale */
#endif  /* defined (_MT) */

        /* Inquire size of dst string */
        if (0 == (dstlen = __crtLCMapStringA(__lc_handle[LC_CTYPE], LCMAP_LOWERCASE,
            string, -1, NULL, 0, 0, TRUE)))
                goto error_cleanup;

        /* Allocate space for dst */
        if (NULL == (dst = (unsigned char *) _malloc_crt(dstlen*sizeof(unsigned char))))
                goto error_cleanup;

        /* Map src string to dst string in alternate case */
        if (0 == __crtLCMapStringA(__lc_handle[LC_CTYPE], LCMAP_LOWERCASE,
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
                if ('A' <= *cp && *cp <= 'Z')
                        *cp += 'a' - 'A';
        }

        return(string);


#endif  /* defined (_WIN32) */
}
