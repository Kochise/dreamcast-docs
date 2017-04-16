/***
*ismbalnm - Test if character is alpha numeric (MBCS)
*
*       Copyright (c) 1985-1997, Microsoft Corporation.  All rights reserved.
*
*Purpose:
*       Test if character is alpha numeric (MBCS)
*
*******************************************************************************/

#ifdef _MBCS

#if defined (_WIN32)
#include <windows.h>
#include <awint.h>
#endif  /* defined (_WIN32) */

#include <cruntime.h>
#include <ctype.h>
#include <mbdata.h>
#include <mbctype.h>
#include <mbstring.h>


/***
* _ismbcalnum - Test if character is alpha numeric (MBCS)
*
*Purpose:
*       Test if the supplied character is alpha numeric or not.
*       Handles MBCS characters correctly.
*
*       Note:  Use test against 0x00FF instead of _ISLEADBYTE
*       to ensure that we don't call SBCS routine with a two-byte
*       value.
*
*Entry:
*       unsigned int c = character to test
*
*Exit:
*       Returns TRUE if c is an alpha numeric character; else FALSE
*
*Exceptions:
*
*******************************************************************************/

int __cdecl _ismbcalnum(
        unsigned int c
        )
{
        if (c > 0x00FF)
        {

#if defined (_WIN32)

            char buf[2];
            unsigned short ctype[2] = {0};

            buf[0] = (c >> 8) & 0xFF;
            buf[1] = c & 0xFF;

            /* return FALSE if not in supported MB code page */
            if ( _ISNOTMBCP )
                return 0;

            /*
            * Since 'c' could be two one-byte MB chars, we need room in the
            * ctype return array to handle this. In this case, the
            * second word in the return array will be non-zero.
            */

            if (__crtGetStringTypeA (CT_CTYPE1, buf,
                    2, ctype, __mbcodepage, __mblcid, TRUE) == 0)
                return 0;

            /* ensure single MB character and test for type */
            return (ctype[1] == 0 && ctype[0] & (_ALPHA|_DIGIT));

#else  /* defined (_WIN32) */

            return ((c >= _MBDIGITLOW && c <= _MBDIGITHIGH) || _ismbcalpha(c));

#endif  /* defined (_WIN32) */

        } else

            return _ismbbalnum(c);
}

#endif  /* _MBCS */
