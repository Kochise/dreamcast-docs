/***
*strset.c - sets all characters of string to given character
*
*       Copyright (c) 1985-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       defines _strset() - sets all of the characters in a string (except
*       the '\0') equal to a given character.
*
*******************************************************************************/

#include <cruntime.h>
#include <string.h>

#if defined (_M_ALPHA) || defined (_M_MRX000) || defined (_M_PPC) || defined (_M_MPPC)
#pragma function(_strset)
#endif  /* defined (_M_ALPHA) || defined (_M_MRX000) || defined (_M_PPC) || defined (_M_MPPC) */

/***
*char *_strset(string, val) - sets all of string to val
*
*Purpose:
*       Sets all of characters in string (except the terminating '/0'
*       character) equal to val.
*
*
*Entry:
*       char *string - string to modify
*       char val - value to fill string with
*
*Exit:
*       returns string -- now filled with val's
*
*Uses:
*
*Exceptions:
*
*******************************************************************************/

char * __cdecl _strset (
        char * string,
        int val
        )
{
        char *start = string;

        while (*string)
                *string++ = (char)val;

        return(start);
}
