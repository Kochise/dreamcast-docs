/***
*a_map.c - A version of LCMapString.
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
*int __cdecl strncnt - count characters in a string, up to n.
*
*Purpose:
*       Internal local support function. Counts characters in string before
*       null. If null is not found in n chars, then return n.
*
*Entry:
*       const char *string   - start of string
*       int n                - byte count
*
*Exit:
*       returns number of bytes from start of string to
*       null (exclusive), up to n.
*
*Exceptions:
*
*******************************************************************************/

static int __cdecl strncnt (
        const char *string,
        int cnt
        )
{
        int n = cnt;
        char *cp = (char *)string;

        while (n-- && *cp)
            cp++;

        if (!*cp)
            return cp - string;
        return cnt;
}


/***
*int __cdecl __crtLCMapStringA - Get type information about an ANSI string.
*
*Purpose:
*       Internal support function. Assumes info in ANSI string format. Tries
*       to use NLS API call LCMapStringA if available and uses LCMapStringW
*       if it must. If neither are available it fails and returns 0.
*
*Entry:
*       LCID     Locale      - locale context for the comparison.
*       DWORD    dwMapFlags  - see NT\Chicago docs
*       LPCSTR   lpSrcStr    - pointer to string to be mapped
*       int      cchSrc      - wide char (word) count of input string
*                              (including NULL if any)
*                              (-1 if NULL terminated)
*       LPSTR    lpDestStr   - pointer to memory to store mapping
*       int      cchDest     - char (byte) count of buffer (including NULL)
*       int      code_page   - for MB/WC conversion. If 0, use __lc_codepage
*       BOOL     bError      - TRUE if MB_ERR_INVALID_CHARS set on call to
*                              MultiByteToWideChar when GetStringTypeW used.
*
*Exit:
*       Success: number of chars written to lpDestStr (including NULL)
*       Failure: 0
*
*Exceptions:
*
*******************************************************************************/

int __cdecl __crtLCMapStringA(
        LCID     Locale,
        DWORD    dwMapFlags,
        LPCSTR   lpSrcStr,
        int      cchSrc,
        LPSTR    lpDestStr,
        int      cchDest,
        int      code_page,
        BOOL     bError
        )
{
        static int f_use = 0;

        /*
         * Look for unstubbed 'preferred' flavor. Otherwise use available flavor.
         * Must actually call the function to ensure it's not a stub.
         * (Always try wide version first so WinNT can process codepage correctly.)
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
         * before cchSrc characters.
         */
        if (cchSrc > 0)
            cchSrc = strncnt(lpSrcStr, cchSrc);

        /* Use "A" version */

        if (USE_A == f_use) {
            return LCMapStringA( Locale, dwMapFlags, lpSrcStr, cchSrc,
                                 lpDestStr, cchDest );
        }

        /* Use "W" version */

        if (USE_W == f_use)
        {
            int retval;
            int inbuff_size;
            int outbuff_size;
            wchar_t *inwbuffer;
            wchar_t *outwbuffer;

            /*
             * Convert string and return the requested information. Note that
             * we are converting to a wide string so there is not a
             * one-to-one correspondence between number of wide chars in the
             * input string and the number of *bytes* in the buffer. However,
             * there had *better be* a one-to-one correspondence between the
             * number of wide characters and the number of multibyte characters
             * or the resulting mapped string will be worthless to the user.
             */

            /*
             * Use __lc_codepage for conversion if code_page not specified
             */

            if (0 == code_page)
                code_page = __lc_codepage;

            /* find out how big a buffer we need (includes NULL if any) */
            if ( 0 == (inbuff_size =
                       MultiByteToWideChar( code_page,
                                            bError ? MB_PRECOMPOSED |
                                                MB_ERR_INVALID_CHARS :
                                                MB_PRECOMPOSED,
                                            lpSrcStr,
                                            cchSrc,
                                            NULL,
                                            0 )) )
                return 0;

            /* allocate enough space for wide chars */
            __try {
                inwbuffer = (wchar_t *)_alloca( inbuff_size * sizeof(wchar_t) );
            }
            __except(EXCEPTION_EXECUTE_HANDLER) {
                inwbuffer = NULL;
            }

            if ( inwbuffer == NULL )
                return 0;

            /* do the conversion */
            if ( 0 == MultiByteToWideChar( code_page,
                                           MB_PRECOMPOSED,
                                           lpSrcStr,
                                           cchSrc,
                                           inwbuffer,
                                           inbuff_size) )
                return 0;

            /* get size required for string mapping */
            if ( 0 == (retval = LCMapStringW( Locale,
                                              dwMapFlags,
                                              inwbuffer,
                                              inbuff_size,
                                              NULL,
                                              0 )) )
                return 0;

            if (dwMapFlags & LCMAP_SORTKEY) {
                /* retval is size in BYTES */

                if (0 != cchDest) {

                    if (retval > cchDest)
                        return 0;

                    /* do string mapping */
                    if ( 0 == LCMapStringW( Locale,
                                            dwMapFlags,
                                            inwbuffer,
                                            inbuff_size,
                                            (LPWSTR)lpDestStr,
                                            cchDest ) )
                        return 0;
                }
            }
            else {
                /* retval is size in wide chars */

                outbuff_size = retval;

                /* allocate enough space for wide chars (includes NULL if any) */
                __try {
                    outwbuffer = (wchar_t *)_alloca( outbuff_size * sizeof(wchar_t) );
                }
                __except(EXCEPTION_EXECUTE_HANDLER) {
                    outwbuffer = NULL;
                }

                if ( outwbuffer == NULL )
                    return 0;

                /* do string mapping */
                if ( 0 == LCMapStringW( Locale,
                                        dwMapFlags,
                                        inwbuffer,
                                        inbuff_size,
                                        outwbuffer,
                                        outbuff_size ) )
                    return 0;

                if (0 == cchDest) {
                    /* get size required */
                    if ( 0 == (retval =
                               WideCharToMultiByte( code_page,
                                                    WC_COMPOSITECHECK |
                                                        WC_SEPCHARS,
                                                    outwbuffer,
                                                    outbuff_size,
                                                    NULL,
                                                    0,
                                                    NULL,
                                                    NULL )) )
                        return 0;
                }
                else {
                    /* convert mapping */
                    if ( 0 == (retval =
                               WideCharToMultiByte( code_page,
                                                    WC_COMPOSITECHECK |
                                                        WC_SEPCHARS,
                                                    outwbuffer,
                                                    outbuff_size,
                                                    lpDestStr,
                                                    cchDest,
                                                    NULL,
                                                    NULL )) )
                        return 0;
                }
            }

            return retval;
        }
        else   /* f_use is neither USE_A nor USE_W */
            return 0;
}
