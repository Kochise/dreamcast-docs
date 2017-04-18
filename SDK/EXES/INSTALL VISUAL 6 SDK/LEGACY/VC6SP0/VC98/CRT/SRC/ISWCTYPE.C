/***
*iswctype.c - support isw* wctype functions/macros for wide characters
*
*       Copyright (c) 1991-1998, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       Defines iswctype - support isw* wctype functions/macros for
*       wide characters (esp. > 255).
*
*******************************************************************************/

#include <cruntime.h>
#include <ctype.h>
#include <stdio.h>
#include <locale.h>
#include <setlocal.h>
#include <awint.h>

/*
 *  Use GetStringTypeW() API so check that character type masks agree between
 *  ctype.h and winnls.h
 */
#if _UPPER != C1_UPPER  || \
        _LOWER != C1_LOWER  || \
        _DIGIT != C1_DIGIT  || \
        _SPACE != C1_SPACE  || \
        _PUNCT != C1_PUNCT  || \
        _CONTROL != C1_CNTRL
#error Character type masks do not agree in ctype and winnls
#endif  /* _UPPER != C1_UPPER  || \ */

/***
*iswctype - support isw* wctype functions/macros.
*
*Purpose:
*       This function is called by the isw* wctype functions/macros
*       (e.g. iswalpha()) when their argument is a wide character > 255.
*       It is also a standard ITSCJ (proposed) ISO routine and can be called
*       by the user, even for characters < 256.
*       Returns true or false depending on whether the argument satisfies
*       the character class property encoded by the mask.  Returns 0 if the
*       argument is WEOF.
*
*       NOTE: The isw* functions are neither locale nor codepage dependent.
*
*Entry:
*       wchar_t c    - the wide character whose type is to be tested
*       wchar_t mask - the mask used by the isw* functions/macros
*                       corresponding to each character class property
*
*Exit:
*       Returns non-zero if c is of the character class.
*       Returns 0 if c is not of the character class.
*
*Exceptions:
*       Returns 0 on any error.
*
*******************************************************************************/

int __cdecl iswctype (
        wchar_t c,
        wctype_t mask
        )
{
        wint_t d;

        if (c == WEOF)
            return 0;

        if (c < 256)
            d = _pwctype[c];
        else
        {
            if ( __crtGetStringTypeW(CT_CTYPE1, &c, 1, &d, 0, 0) == 0 )
                return 0;
        }

        return (int)(d & mask);
}


/***
*is_wctype - support obsolete name
*
*Purpose:
*       Name changed from is_wctype to iswctype. is_wctype must be supported.
*
*Entry:
*       wchar_t c    - the wide character whose type is to be tested
*       wchar_t mask - the mask used by the isw* functions/macros
*                       corresponding to each character class property
*
*Exit:
*       Returns non-zero if c is of the character class.
*       Returns 0 if c is not of the character class.
*
*Exceptions:
*       Returns 0 on any error.
*
*******************************************************************************/
int __cdecl is_wctype (
        wchar_t c,
        wctype_t mask
        )
{
        return iswctype(c, mask);
}
