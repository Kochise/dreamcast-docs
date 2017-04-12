/***
*ismblgl.c - Tests to see if a given character is a legal MBCS char.
*
*       Copyright (c) 1985-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       Tests to see if a given character is a legal MBCS character.
*
*******************************************************************************/

#ifdef _MBCS

#include <cruntime.h>
#include <mbdata.h>
#include <mbctype.h>
#include <mbstring.h>


/***
*int _ismbclegal(c) - tests for a valid MBCS character.
*
*Purpose:
*       Tests to see if a given character is a legal MBCS character.
*
*Entry:
*       unsigned int c - character to test
*
*Exit:
*       returns non-zero if Microsoft Kanji code, else 0
*
*Exceptions:
*
******************************************************************************/

int __cdecl _ismbclegal(c)
unsigned int c;
{
        return((_ISLEADBYTE(c>>8)) && (_ISTRAILBYTE(c&0377)));
}

#endif  /* _MBCS */
