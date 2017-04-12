/***
*mbsicmp.c - Case-insensitive string comparision routine (MBCS)
*
*       Copyright (c) 1985-1997, Microsoft Corporation.  All rights reserved.
*
*Purpose:
*       Case-insensitive string comparision routine (MBCS)
*
*******************************************************************************/

#ifdef _MBCS

#if defined (_WIN32)
#include <awint.h>
#endif  /* defined (_WIN32) */

#include <mtdll.h>
#include <cruntime.h>
#include <mbdata.h>
#include <mbctype.h>
#include <string.h>
#include <mbstring.h>

/***
* _mbsicmp - Case-insensitive string comparision routine (MBCS)
*
*Purpose:
*       Compares two strings for lexical order without regard to case.
*       Strings are compared on a character basis, not a byte basis.
*
*Entry:
*       char *s1, *s2 = strings to compare
*
*Exit:
*       returns <0 if s1 < s2
*       returns  0 if s1 == s2
*       returns >0 if s1 > s2
*       returns _NLSCMPERROR if NLS error
*
*Exceptions:
*
*******************************************************************************/

int __cdecl _mbsicmp (const unsigned char *s1, const unsigned char *s2)
{
        unsigned short c1, c2;
#if defined (_WIN32)
        int    retval;
        unsigned char szResult[4];
#endif  /* defined (_WIN32) */

        if ( _ISNOTMBCP )
            return _stricmp(s1, s2);

        _mlock(_MB_CP_LOCK);

        for (;;)
        {
            c1 = *s1++;
            if (_ISLEADBYTE(c1))
            {
                if (*s1 == '\0')
                    c1 = 0;
                else
                {
#if defined (_WIN32)
                    retval = __crtLCMapStringA(__mblcid, LCMAP_UPPERCASE,
                                               s1 - 1, 2, szResult, 2,
                                               __mbcodepage, TRUE);
                    if (retval == 1)
                        c1 = szResult[0];
                    else if (retval == 2)
                        c1 = (szResult[0] << 8) + szResult[1];
                    else
                    {
                        _munlock(_MB_CP_LOCK);
                        return _NLSCMPERROR;
                    }
                    s1++;
#else  /* defined (_WIN32) */
                    c1 = ((c1 << 8) | *s1++);
                    if (c1 >= _MBUPPERLOW1 && c1 <= _MBUPPERHIGH1)
                        c1 += _MBCASEDIFF1;
                    else if (c1 >= _MBUPPERLOW2 && c1 <= _MBUPPERHIGH2)
                        c1 += _MBCASEDIFF2;
#endif  /* defined (_WIN32) */
                }
            }
            else
                c1 = _mbbtolower(c1);

            c2 = *s2++;
            if (_ISLEADBYTE(c2))
            {
                if (*s2 == '\0')
                    c2 = 0;
                else
                {
#if defined (_WIN32)
                    retval = __crtLCMapStringA(__mblcid, LCMAP_UPPERCASE,
                                               s2 - 1, 2, szResult, 2,
                                               __mbcodepage, TRUE);
                    if (retval == 1)
                        c2 = szResult[0];
                    else if (retval == 2)
                        c2 = (szResult[0] << 8) + szResult[1];
                    else
                    {
                        _munlock(_MB_CP_LOCK);
                        return _NLSCMPERROR;
                    }
                    s2++;
#else  /* defined (_WIN32) */
                    c2 = ((c2 << 8) | *s2++);
                    if (c2 >= _MBUPPERLOW1 && c2 <= _MBUPPERHIGH1)
                        c2 += _MBCASEDIFF1;
                    else if (c2 >= _MBUPPERLOW2 && c2 <= _MBUPPERHIGH2)
                        c2 += _MBCASEDIFF2;
#endif  /* defined (_WIN32) */
                }
            }
            else
                c2 = _mbbtolower(c2);

            if (c1 != c2)
            {
                _munlock(_MB_CP_LOCK);
                return( (c1 > c2) ? 1 : -1 );
            }

            if (c1 == 0)
            {
                _munlock(_MB_CP_LOCK);
                return(0);
            }
        }
}

#endif  /* _MBCS */
