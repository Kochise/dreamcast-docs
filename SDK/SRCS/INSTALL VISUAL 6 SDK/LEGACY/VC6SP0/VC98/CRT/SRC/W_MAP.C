/***
*w_map.c - W version of LCMapString.
*
*       Copyright (c) 1993-1997, Microsoft Corporation.  All rights reserved.
*
*Purpose:
*       Use either LCMapStringA or LCMapStringW depending on which is available
*
*******************************************************************************/

#include <cruntime.h>
#include <internal.h>
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
*       Internal local support function. Counts characters in string before
*       null. If null not found in n chars, then return n.
*
*Entry:
*       const wchar_t *string   - start of string
*       int n                - byte count
*
*Exit:
*       returns number of wide characaters from start of string to
*       null (exclusive), up to n.
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
*int __cdecl __crtLCMapStringW - Get type information about a wide string.
*
*Purpose:
*       Internal support function. Assumes info in wide string format. Tries
*       to use NLS API call LCMapStringW if available and uses LCMapStringA
*       if it must. If neither are available it fails and returns 0.
*
*Entry:
*       LCID     Locale      - locale context for the comparison.
*       DWORD    dwMapFlags  - see NT\Chicago docs
*       LPCWSTR  lpSrcStr    - pointer to string to be mapped
*       int      cchSrc      - wide char (word) count of input string
*                              (including NULL if any)
*                              (-1 if NULL terminated)
*       LPWSTR   lpDestStr   - pointer to memory to store mapping
*       int      cchDest     - wide char (word) count of buffer (including NULL)
*       int      code_page   - for MB/WC conversion. If 0, use __lc_codepage
*
*       NOTE:    if LCMAP_SORTKEY is specified, then cchDest refers to number
*                of BYTES, not number of wide chars. The return string will be
*                a series of bytes with a NULL byte terminator.
*
*Exit:
*       Success: if LCMAP_SORKEY:
*                   number of bytes written to lpDestStr (including NULL byte
*                   terminator)
*               else
*                   number of wide characters written to lpDestStr (including
*                   NULL)
*       Failure: 0
*
*Exceptions:
*
*******************************************************************************/

int __cdecl __crtLCMapStringW(
        LCID     Locale,
        DWORD    dwMapFlags,
        LPCWSTR  lpSrcStr,
        int      cchSrc,
        LPWSTR   lpDestStr,
        int      cchDest,
        int      code_page
        )
{
        static int f_use = 0;

        /*
         * Look for unstubbed 'preferred' flavor. Otherwise use available flavor.
         * Must actually call the function to ensure it's not a stub.
         */

        if (0 == f_use) {
            if (0 != LCMapStringW(0, LCMAP_LOWERCASE, L"\0", 1, NULL, 0))
                f_use = USE_W;
            else if (0 != LCMapStringA(0, LCMAP_LOWERCASE, "\0", 1, NULL, 0))
                f_use = USE_A;
            else
                return 0;
        }

        /*
         * LCMapString will map past NULL. Must find NULL if in string
         * before cchSrc wide characters.
         */
        if (cchSrc > 0)
            cchSrc = wcsncnt(lpSrcStr, cchSrc);

        /* Use "W" version */

        if (USE_W == f_use) {
            return LCMapStringW( Locale, dwMapFlags, lpSrcStr, cchSrc,
                                 lpDestStr, cchDest );
        }

        /* Use "A" version */

        if (USE_A == f_use) {

            int retval;
            int inbuff_size;
            int outbuff_size;
            unsigned char *inbuffer;
            unsigned char *outbuffer;

            /*
             * Convert string and return the requested information. Note that
             * we are converting to a multibyte string so there is not a
             * one-to-one correspondence between number of wide chars in the
             * input string and the number of *bytes* in the buffer. However,
             * there had *better be* a one-to-one correspondence between the
             * number of wide characters and the number of multibyte characters
             * (enforced by WC_SEPCHARS) in the buffer or the resulting mapped
             * string will be worthless to the user.
             *
             */

            /*
             * Use __lc_codepage for conversion if code_page not specified
             */

            if (0 == code_page)
                code_page = __lc_codepage;

            /* find out how big a buffer we need (includes NULL if any) */
            if ( 0 == (inbuff_size = WideCharToMultiByte( code_page,
                                                          WC_COMPOSITECHECK |
                                                            WC_SEPCHARS,
                                                          lpSrcStr,
                                                          cchSrc,
                                                          NULL,
                                                          0,
                                                          NULL,
                                                          NULL )) )
                return 0;

            /* allocate enough space for chars */
            __try {
                inbuffer = (unsigned char *)_alloca( inbuff_size * sizeof(char) );
            }
            __except(EXCEPTION_EXECUTE_HANDLER) {
                inbuffer = NULL;
            }

            if ( inbuffer == NULL )
                return 0;

            /* do the conversion */
            if ( 0 ==  WideCharToMultiByte( code_page,
                                            WC_COMPOSITECHECK | WC_SEPCHARS,
                                            lpSrcStr,
                                            cchSrc,
                                            inbuffer,
                                            inbuff_size,
                                            NULL,
                                            NULL ) )
                return 0;

            /* get size required for string mapping */
            if ( 0 == (outbuff_size = LCMapStringA( Locale,
                                                    dwMapFlags,
                                                    inbuffer,
                                                    inbuff_size,
                                                    NULL,
                                                    0 )) )
                return 0;

            /* allocate enough space for chars and NULL */
            __try {
                outbuffer = (unsigned char *)_alloca( outbuff_size * sizeof(char) );
            }
            __except(EXCEPTION_EXECUTE_HANDLER) {
                outbuffer = NULL;
            }

            if ( outbuffer == NULL )
                return 0;

            /* do string mapping */
            if ( 0 == LCMapStringA( Locale,
                                    dwMapFlags,
                                    inbuffer,
                                    inbuff_size,
                                    outbuffer,
                                    outbuff_size ) )
                return 0;

            if (dwMapFlags & LCMAP_SORTKEY) {

                /* outbuff_size > cchDest is allowed */
                retval = outbuff_size;

                if (0 != cchDest)
                    /* SORTKEY returns BYTES, just copy */
                    strncpy( (char *)lpDestStr,
                             (char *)outbuffer,
                             cchDest < outbuff_size ? cchDest : outbuff_size );
            }
            else {
                if (0 == cchDest) {
                    /* get size required */
                    if ( 0 == (retval = MultiByteToWideChar( code_page,
                                                             MB_PRECOMPOSED,
                                                             outbuffer,
                                                             outbuff_size,
                                                             NULL,
                                                             0 )) )
                        return 0;
                }
                else {
                    /* convert mapping */
                    if ( 0 == (retval = MultiByteToWideChar( code_page,
                                                             MB_PRECOMPOSED,
                                                             outbuffer,
                                                             outbuff_size,
                                                             lpDestStr,
                                                             cchDest )) )
                        return 0;
                }
            }

            return retval;
        }
        else   /* f_use is neither USE_A nor USE_W */
            return 0;
}
