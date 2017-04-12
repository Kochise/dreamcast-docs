/***
*mbtokata.c - Converts character to katakana.
*
*       Copyright (c) 1985-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       Converts a character from hiragana to katakana.
*
*******************************************************************************/

#ifdef _MBCS

#include <cruntime.h>
#include <mbdata.h>
#include <mbstring.h>
#include <mbctype.h>


/***
*unsigned short _mbctokata(c) - Converts character to katakana.
*
*Purpose:
*       If the character c is hiragana, convert to katakana.
*
*Entry:
*       unsigned int c - Character to convert.
*
*Exit:
*       Returns converted character.
*
*Exceptions:
*
*******************************************************************************/

unsigned int __cdecl _mbctokata(
    unsigned int c
    )
{
        if (_ismbchira(c)) {
                c += 0xa1;
                if (c >= 0x837f)
                        c++;
        }
        return(c);
}

#endif  /* _MBCS */
