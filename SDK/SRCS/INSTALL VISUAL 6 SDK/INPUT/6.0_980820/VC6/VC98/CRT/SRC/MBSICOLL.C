/***
*mbsicoll.c - Collate MBCS strings, ignoring case
*
*       Copyright (c) 1994-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       Collate MBCS strings, ignoring case
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
#include <mbstring.h>

/***
* _mbsicoll - Collate MBCS strings, ignoring case
*
*Purpose:
*       Collates two strings for lexical order.   Strings
*       are collated on a character basis, not a byte basis.
*
*Entry:
*       char *s1, *s2 = strings to collate
*
*Exit:
*       returns <0 if s1 < s2
*       returns  0 if s1 == s2
*       returns >0 if s1 > s2
*
*Exceptions:
*
*******************************************************************************/

int __cdecl _mbsicoll(
    const unsigned char *s1,
    const unsigned char *s2
    )
{
#if !defined (_WIN32)
        return _mbsicmp(s1, s2);
#else  /* !defined (_WIN32) */
        int ret;

        if (0 == (ret = __crtCompareStringA(__mblcid, NORM_IGNORECASE,
                s1, -1, s2, -1, __mbcodepage)))
            return _NLSCMPERROR;

        return ret - 2;

#endif  /* !defined (_WIN32) */
}

#endif  /* _MBCS */
