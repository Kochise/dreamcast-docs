/***
*mbsinc.c - Move MBCS string pointer ahead one charcter.
*
*       Copyright (c) 1991-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       Move MBCS string pointer ahead one character.
*
*******************************************************************************/

#ifdef _MBCS

#include <cruntime.h>
#include <mbdata.h>
#include <mbstring.h>
#include <mbctype.h>
#include <stddef.h>

/***
*_mbsinc - Move MBCS string pointer ahead one charcter.
*
*Purpose:
*       Move the supplied string pointer ahead by one
*       character.  MBCS characters are handled correctly.
*
*Entry:
*       const unsigned char *current = current char pointer (legal MBCS boundary)
*
*Exit:
*       Returns pointer after moving it.
*
*Exceptions:
*
*******************************************************************************/

unsigned char * __cdecl _mbsinc(
    const unsigned char *current
    )
{
    if (_ISLEADBYTE(*(current++)))
        current++;
    return (unsigned char *)current;
}

#endif  /* _MBCS */
