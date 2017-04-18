/***
*w_cmp.c - W versions of CompareString.
*
*       Copyright (c) 1993-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       Use either CompareStringA or CompareStringW depending on which is
*       available
*
*******************************************************************************/

#include <cruntime.h>
#include <internal.h>
#include <dbgint.h>
#include <stdlib.h>
#include <setlocal.h>
#include <awint.h>
#include <dbgint.h>

#define USE_W   1
#define USE_A   2

/***
*int __cdecl wcsncnt - count wide characters in a string, up to n.
*
*Purpose:
*       Internal local support function. Counts characters in string before NULL.
*       If NULL not found in n chars, then return n.
*
*Entry:
*       const wchar_t *string   - start of string
*       int n                   - byte count
*
*Exit:
*       returns number of wide characaters from start of string to
*       NULL (exclusive), up to n.
*
*Exceptions:
*
*******************************************************************************/

static int __cdecl wcsncnt (
        const wchar_t *string,
        int cnt
        )
{
        int n = cnt;
        wchar_t *cp = (wchar_t *)string;

        while (n-- && *cp)
            cp++;

        if (!*cp)
            return cp - string;
        return cnt;
}

/***
*int __cdecl __crtCompareStringW - Get type information about a wide string.
*
*Purpose:
*  Internal support function. Assumes info in wide string format. Tries
*  to use NLS API call CompareStringW if available and uses CompareStringA
*  if it must. If neither are available it fails and returns 0.
*
*Entry:
*  LCID     Locale      - locale context for the comparison.
*  DWORD    dwCmpFlags  - see NT\Chicago docs
*  LPCWSTR  lpStringn   - wide string to be compared
*  int      cchCountn   - wide char (word) count (NOT including NULL)
*                       (-1 if NULL terminated)
*  int      code_page   - for MB/WC conversion. If 0, use __lc_codepage
*
*Exit:
*  Success: 1 - if lpString1 <  lpString2
*           2 - if lpString1 == lpString2
*           3 - if lpString1 >  lpString2
*  Failure: 0
*
*Exceptions:
*
*******************************************************************************/

int __cdecl __crtCompareStringW(
        LCID     Locale,
        DWORD    dwCmpFlags,
        LPCWSTR  lpString1,
        int      cchCount1,
        LPCWSTR  lpString2,
        int      cchCount2,
        int      code_page
        )
{
        static int f_use = 0;

        /*
         * Look for unstubbed 'preferred' flavor. Otherwise use available flavor.
         * Must actually call the function to ensure it's not a stub.
         */

        if (0 == f_use)
        {
            if (0 != CompareStringW(0, 0, L"\0", 1, L"\0", 1))
                f_use = USE_W;

            else if (0 != CompareStringA(0, 0, "\0", 1, "\0", 1))
                f_use = USE_A;

            else
                return 0;
        }

        /*
         * CompareString will compare past NULL. Must find NULL if in string
         * before cchCountn wide characters.
         */

        if (cchCount1 > 0)
            cchCount1= wcsncnt(lpString1, cchCount1);
        if (cchCount2 > 0)
            cchCount2= wcsncnt(lpString2, cchCount2);

        if (!cchCount1 || !cchCount2)
            return (cchCount1 - cchCount2 == 0) ? 2 :
                   (cchCount1 - cchCount2 < 0) ? 1 : 3;

        /* Use "W" version */

        if (USE_W == f_use)
        {
            return CompareStringW( Locale,
                                   dwCmpFlags,
                                   lpString1,
                                   cchCount1,
                                   lpString2,
                                   cchCount2 );
        }

        /* Use "A" version */

        if (USE_A == f_use)
        {
            int buff_size1;
            int buff_size2;
            unsigned char *buffer1;
            unsigned char *buffer2;

            /*
             * Use __lc_codepage for conversion if code_page not specified
             */

            if (0 == code_page)
                code_page = __lc_codepage;

            /*
             * Convert strings and return the requested information.
             */

            /* find out how big a buffer we need (includes NULL if any) */
            if ( 0 == (buff_size1 = WideCharToMultiByte( code_page,
                                                         WC_COMPOSITECHECK |
                                                            WC_SEPCHARS,
                                                         lpString1,
                                                         cchCount1,
                                                         NULL,
                                                         0,
                                                         NULL,
                                                         NULL )) )
                return 0;

            /* allocate enough space for chars */
            __try {
                buffer1 = (unsigned char *)_alloca( buff_size1 * sizeof(char) );
            }
            __except( EXCEPTION_EXECUTE_HANDLER ) {
                buffer1 = NULL;
            }

            if ( buffer1 == NULL )
                return 0;

            /* do the conversion */
            if ( 0 == WideCharToMultiByte( code_page,
                                           WC_COMPOSITECHECK | WC_SEPCHARS,
                                           lpString1,
                                           cchCount1,
                                           buffer1,
                                           buff_size1,
                                           NULL,
                                           NULL ) )
                return 0;

            /* find out how big a buffer we need (includes NULL if any) */
            if ( 0 == (buff_size2 = WideCharToMultiByte( code_page,
                                                         WC_COMPOSITECHECK |
                                                            WC_SEPCHARS,
                                                         lpString2,
                                                         cchCount2,
                                                         NULL,
                                                         0,
                                                         NULL,
                                                         NULL )) )
                return 0;

            /* allocate enough space for chars */
            __try {
                buffer2 = (unsigned char *)_alloca( buff_size2 * sizeof(char) );
            }
            __except( EXCEPTION_EXECUTE_HANDLER ) {
                buffer2 = NULL;
            }

            if ( buffer2 == NULL )
                return 0;

            /* do the conversion */
            if ( 0 == WideCharToMultiByte( code_page,
                                           WC_COMPOSITECHECK | WC_SEPCHARS,
                                           lpString2,
                                           cchCount2,
                                           buffer2,
                                           buff_size2,
                                           NULL,
                                           NULL ) )
                return 0;

            return CompareStringA( Locale,
                                   dwCmpFlags,
                                   buffer1,
                                   buff_size1,
                                   buffer2,
                                   buff_size2 );
        }
        else   /* f_use is neither USE_A nor USE_W */
            return 0;
}
