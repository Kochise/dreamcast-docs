/***
*mbtolwr.c - Convert character to lower case (MBCS).
*
*   Copyright (c) 1985-1997, Microsoft Corporation.  All rights reserved.
*
*Purpose:
*   Convert character to lower case (MBCS).
*
*******************************************************************************/

#ifdef _MBCS

#if defined (_WIN32)
#include <awint.h>
#endif  /* defined (_WIN32) */

#include <cruntime.h>
#include <ctype.h>
#include <mbdata.h>
#include <mbctype.h>
#include <mbstring.h>


/***
* _mbctolower - Convert character to lower case (MBCS)
*
*Purpose:
*   If the given character is upper case, convert it to lower case.
*   Handles MBCS characters correctly.
*
*   Note:  Use test against 0x00FF instead of _ISLEADBYTE
*   to ensure that we don't call SBCS routine with a two-byte
*   value.
*
*Entry:
*   unsigned int c = character to convert
*
*Exit:
*   Returns converted character
*
*Exceptions:
*
*******************************************************************************/

unsigned int __cdecl _mbctolower (unsigned int c)
{
    unsigned char val[2];
#if defined (_WIN32)
    unsigned char ret[4];
#endif  /* defined (_WIN32) */

    if (c > 0x00FF)
    {
        val[0] = (c >> 8) & 0xFF;
        val[1] = c & 0xFF;

        if (!_ismbblead(val[0]))
            return c;

#if defined (_WIN32)

        if (__crtLCMapStringA(__mblcid, LCMAP_LOWERCASE, val, 2,
                              ret, 2, __mbcodepage, TRUE) == 0)
            return c;

        c = ret[1];
        c += ret[0] << 8;

        return c;

#else  /* defined (_WIN32) */

        if (c >= _MBUPPERLOW1 && c <= _MBUPPERHIGH1)
            c += _MBCASEDIFF1;
        else if (c >= _MBUPPERLOW2 && c <= _MBUPPERHIGH2)
            c += _MBCASEDIFF2;

        return c;

#endif  /* defined (_WIN32) */

    }
    else
            return (unsigned int)_mbbtolower((int)c);
}

#endif  /* _MBCS */
