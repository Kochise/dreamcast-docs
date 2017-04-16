/***
*mbsupr.c - Convert string upper case (MBCS)
*
*       Copyright (c) 1985-1997, Microsoft Corporation.  All rights reserved.
*
*Purpose:
*       Convert string upper case (MBCS)
*
*******************************************************************************/

#ifdef _MBCS

#if defined (_WIN32)
#include <awint.h>
#endif  /* defined (_WIN32) */

#include <mtdll.h>
#include <cruntime.h>
#include <ctype.h>
#include <mbdata.h>
#include <mbstring.h>
#include <mbctype.h>


/***
* _mbsupr - Convert string upper case (MBCS)
*
*Purpose:
*       Converts all the lower case characters in a string
*       to upper case in place.   Handles MBCS chars correctly.
*
*Entry:
*       unsigned char *string = pointer to string
*
*Exit:
*       Returns a pointer to the input string; no error return.
*
*Exceptions:
*
*******************************************************************************/

unsigned char * __cdecl _mbsupr(
    unsigned char *string
    )
{
        unsigned char *cp;

        _mlock(_MB_CP_LOCK);

        for (cp=string; *cp; cp++)
        {
            if (_ISLEADBYTE(*cp))
            {

#if defined (_WIN32)

                int retval;
                unsigned char ret[4];

                if ((retval = __crtLCMapStringA(__mblcid,
                                                LCMAP_UPPERCASE,
                                                cp,
                                                2,
                                                ret,
                                                2,
                                                __mbcodepage,
                                                TRUE)) == 0)
                {
                    _munlock(_MB_CP_LOCK);
                    return NULL;
                }

                *cp = ret[0];

                if (retval > 1)
                    *(++cp) = ret[1];

#else  /* defined (_WIN32) */

                int mbval = ((*cp) << 8) + *(cp+1);

                cp++;
                if (     mbval >= _MBLOWERLOW1
                    &&   mbval <= _MBLOWERHIGH1 )
                    *cp -= _MBCASEDIFF1;

                else if (mbval >= _MBLOWERLOW2
                    &&   mbval <= _MBLOWERHIGH2 )
                    *cp -= _MBCASEDIFF2;

#endif  /* defined (_WIN32) */

            }
            else
                /* single byte, macro version */
                *cp = (unsigned char) _mbbtoupper(*cp);
        }

        _munlock(_MB_CP_LOCK);
        return string ;
}

#endif  /* _MBCS */
