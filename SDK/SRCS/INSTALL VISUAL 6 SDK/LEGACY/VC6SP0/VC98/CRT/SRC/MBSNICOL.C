/***
*mbsnicol.c - Collate n characters of strings, ignoring case (MBCS)
*
*       Copyright (c) 1994-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       Collate n characters of strings, ignoring case (MBCS)
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
* _mbsnicoll - Collate n characters of strings, ignoring case (MBCS)
*
*Purpose:
*       Collates up to n charcters of two strings for lexical order.
*       Strings are collated on a character basis, not a byte basis.
*       Case of characters is not considered.
*
*Entry:
*       unsigned char *s1, *s2 = strings to collate
*       size_t n = maximum number of characters to collate
*
*Exit:
*       returns <0 if s1 < s2
*       returns  0 if s1 == s2
*       returns >0 if s1 > s2
*
*Exceptions:
*
*******************************************************************************/

int __cdecl _mbsnicoll(
    const unsigned char *s1,
    const unsigned char *s2,
    size_t n
    )
{
#if !defined (_WIN32)
        return _mbsnicmp(s1, s2, n);
#else  /* !defined (_WIN32) */
        int ret;
        size_t bcnt1, bcnt2;

        if (n == 0)
            return 0;

        bcnt1 = _mbsnbcnt(s1, n);
        bcnt2 = _mbsnbcnt(s2, n);

        if (0 == (ret = __crtCompareStringA(__mblcid, NORM_IGNORECASE,
                s1, bcnt1, s2, bcnt2, __mbcodepage)))
            return _NLSCMPERROR;

        return ret - 2;

#endif  /* !defined (_WIN32) */
}

#endif  /* _MBCS */
