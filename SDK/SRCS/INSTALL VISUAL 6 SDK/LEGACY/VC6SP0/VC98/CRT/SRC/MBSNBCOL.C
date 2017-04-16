/***
*mbsnbcol.c - Collate n bytes of two MBCS strings
*
*       Copyright (c) 1994-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       Collate n bytes of two MBCS strings
*
*******************************************************************************/

#ifdef _MBCS

#if defined (_WIN32)
#include <awint.h>
#include <mtdll.h>
#endif  /* defined (_WIN32) */

#include <cruntime.h>
#include <internal.h>
#include <mbdata.h>
#include <mbctype.h>
#include <string.h>
#include <mbstring.h>


/***
* _mbsnbcoll(s1, s2, n) - Collate n bytes of two MBCS strings
*
*Purpose:
*       Collates up to n bytes of two strings for lexical order.
*
*Entry:
*       unsigned char *s1, *s2 = strings to collate
*       size_t n = maximum number of bytes to collate
*
*Exit:
*       returns <0 if s1 < s2
*       returns  0 if s1 == s2
*       returns >0 if s1 > s2
*
*Exceptions:
*
*******************************************************************************/

int __cdecl _mbsnbcoll(
    const unsigned char *s1,
    const unsigned char *s2,
    size_t n
    )
{
#if !defined (_WIN32)
        return _mbsnbcmp(s1, s2, n);
#else  /* !defined (_WIN32) */
        int ret;

        if (n == 0)
            return 0;

        if (0 == (ret = __crtCompareStringA(__mblcid, 0,
                s1, n, s2, n, __mbcodepage)))
            return _NLSCMPERROR;

        return ret - 2;

#endif  /* !defined (_WIN32) */
}

#endif  /* _MBCS */
