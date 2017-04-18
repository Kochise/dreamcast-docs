/***
*strtok.c - tokenize a string with given delimiters
*
*       Copyright (c) 1989-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       defines strtok() - breaks string into series of token
*       via repeated calls.
*
*******************************************************************************/

#include <cruntime.h>
#include <string.h>
#ifdef _MT
#include <mtdll.h>
#endif  /* _MT */

/***
*char *strtok(string, control) - tokenize string with delimiter in control
*
*Purpose:
*       strtok considers the string to consist of a sequence of zero or more
*       text tokens separated by spans of one or more control chars. the first
*       call, with string specified, returns a pointer to the first char of the
*       first token, and will write a null char into string immediately
*       following the returned token. subsequent calls with zero for the first
*       argument (string) will work thru the string until no tokens remain. the
*       control string may be different from call to call. when no tokens remain
*       in string a NULL pointer is returned. remember the control chars with a
*       bit map, one bit per ascii char. the null char is always a control char.
*
*Entry:
*       char *string - string to tokenize, or NULL to get next token
*       char *control - string of characters to use as delimiters
*
*Exit:
*       returns pointer to first token in string, or if string
*       was NULL, to next token
*       returns NULL when no more tokens remain.
*
*Uses:
*
*Exceptions:
*
*******************************************************************************/

char * __cdecl strtok (
        char * string,
        const char * control
        )
{
        unsigned char *str;
        const unsigned char *ctrl = control;

        unsigned char map[32];
        int count;

#ifdef _MT
        _ptiddata ptd = _getptd();
#else  /* _MT */
        static char *nextoken;
#endif  /* _MT */

        /* Clear control map */
        for (count = 0; count < 32; count++)
                map[count] = 0;

        /* Set bits in delimiter table */
        do {
                map[*ctrl >> 3] |= (1 << (*ctrl & 7));
        } while (*ctrl++);

        /* Initialize str. If string is NULL, set str to the saved
         * pointer (i.e., continue breaking tokens out of the string
         * from the last strtok call) */
        if (string)
                str = string;
        else
#ifdef _MT
                str = ptd->_token;
#else  /* _MT */
                str = nextoken;
#endif  /* _MT */

        /* Find beginning of token (skip over leading delimiters). Note that
         * there is no token iff this loop sets str to point to the terminal
         * null (*str == '\0') */
        while ( (map[*str >> 3] & (1 << (*str & 7))) && *str )
                str++;

        string = str;

        /* Find the end of the token. If it is not the end of the string,
         * put a null there. */
        for ( ; *str ; str++ )
                if ( map[*str >> 3] & (1 << (*str & 7)) ) {
                        *str++ = '\0';
                        break;
                }

        /* Update nextoken (or the corresponding field in the per-thread data
         * structure */
#ifdef _MT
        ptd->_token = str;
#else  /* _MT */
        nextoken = str;
#endif  /* _MT */

        /* Determine if a token has been found. */
        if ( string == str )
                return NULL;
        else
                return string;
}
