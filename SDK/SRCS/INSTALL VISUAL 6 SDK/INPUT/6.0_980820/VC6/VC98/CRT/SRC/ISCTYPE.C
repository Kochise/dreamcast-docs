/***
*isctype.c - support is* ctype functions/macros for two-byte multibyte chars
*
*       Copyright (c) 1991-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       Defines _isctype.c - support is* ctype functions/macros for
*       two-byte multibyte chars.
*
*******************************************************************************/

#ifndef _MAC
#include <stdio.h>
#include <cruntime.h>
#include <ctype.h>
#include <locale.h>
#include <setlocal.h>
#include <mtdll.h>
#include <awint.h>
#endif  /* _MAC */

#if !defined (_MAC)

/*
 *  Use GetCharType() API so check that character type masks agree between
 *  ctype.h and winnls.h
 */
#if _UPPER   != C1_UPPER || \
        _LOWER   != C1_LOWER || \
        _DIGIT   != C1_DIGIT || \
        _SPACE   != C1_SPACE || \
        _PUNCT   != C1_PUNCT || \
        _CONTROL != C1_CNTRL
#error Character type masks do not agree in ctype and winnls
#endif  /* _UPPER   != C1_UPPER || \ */

/***
*_isctype - support is* ctype functions/macros for two-byte multibyte chars
*
*Purpose:
*       This function is called by the is* ctype functions/macros
*       (e.g. isalpha()) when their argument is a two-byte multibyte char.
*       Returns true or false depending on whether the argument satisfies
*       the character class property encoded by the mask.
*
*Entry:
*       int c - the multibyte character whose type is to be tested
*       unsigned int mask - the mask used by the is* functions/macros
*                  corresponding to each character class property
*
*       The leadbyte and the trailbyte should be packed into the int c as:
*
*       H.......|.......|.......|.......L
*           0       0   leadbyte trailbyte
*
*Exit:
*       Returns non-zero if c is of the character class.
*       Returns 0 if c is not of the character class.
*
*Exceptions:
*       Returns 0 on any error.
*
*******************************************************************************/

int __cdecl _isctype (
        int c,
        int mask
        )
{
        int size;
        unsigned short chartype;
        char buffer[3];

        /* c valid between -1 and 255 */
        if (((unsigned)(c + 1)) <= 256)
            return _pctype[c] & mask;

        if (isleadbyte(c >> 8 & 0xff))
        {
            buffer[0] = (c >> 8 & 0xff); /* put lead-byte at start of str */
            buffer[1] = (char)c;
            buffer[2] = 0;
            size = 2;
        } else {
            buffer[0] = (char)c;
            buffer[1] = 0;
            size = 1;
        }

        if (0 == __crtGetStringTypeA(CT_CTYPE1, buffer, size, &chartype, 0, 0, TRUE))
        {
            return 0;
        }

        return (int)(chartype & mask);
}

#else  /* !defined (_MAC) */

int __cdecl _isctype (
        int c,
        int mask
        )
{
        return 0;
}

#endif  /* !defined (_MAC) */
