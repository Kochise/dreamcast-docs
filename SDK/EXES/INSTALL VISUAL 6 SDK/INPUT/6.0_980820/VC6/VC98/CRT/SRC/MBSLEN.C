/***
*mbslen.c - Find length of MBCS string
*
*       Copyright (c) 1985-1997, Microsoft Corporation.  All rights reserved.
*
*Purpose:
*       Find length of MBCS string
*
*******************************************************************************/

#ifdef _MBCS

#include <mtdll.h>
#include <cruntime.h>
#include <string.h>
#include <mbdata.h>
#include <mbctype.h>
#include <mbstring.h>


/***
* _mbslen - Find length of MBCS string
*
*Purpose:
*       Find the length of the MBCS string (in characters).
*
*Entry:
*       unsigned char *s = string
*
*Exit:
*       Returns the number of MBCS chars in the string
*
*Exceptions:
*
*******************************************************************************/

size_t __cdecl _mbslen(
        const unsigned char *s
        )
{
        int n;

        if ( _ISNOTMBCP )
            return strlen(s);

        _mlock(_MB_CP_LOCK);

        for (n = 0; *s; n++, s++) {
                if (_ISLEADBYTE(*s)) {
                        if (*++s == '\0')
                                break;
                }
        }

        _munlock(_MB_CP_LOCK);
        return(n);
}

#endif  /* _MBCS */
