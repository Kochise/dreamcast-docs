/***
*gets.c - read a line from stdin
*
*       Copyright (c) 1985-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       defines gets() and getws() - read a line from stdin into buffer
*
*******************************************************************************/

#include <cruntime.h>
#include <stdio.h>
#include <dbgint.h>
#include <file2.h>
#include <mtdll.h>
#include <tchar.h>

/***
*char *gets(string) - read a line from stdin
*
*Purpose:
*       Gets a string from stdin terminated by '\n' or EOF; don't include '\n';
*       append '\0'.
*
*Entry:
*       char *string - place to store read string, assumes enough room.
*
*Exit:
*       returns string, filled in with the line of input
*       null string if \n found immediately
*       NULL if EOF found immediately
*
*Exceptions:
*
*******************************************************************************/

_TCHAR * __cdecl _getts (
        _TCHAR *string
        )
{
        int ch;
        _TCHAR *pointer = string;
        _TCHAR *retval = string;

        _ASSERTE(string != NULL);

        _lock_str2(0, stdin);

#ifdef _UNICODE
        while ((ch = _getwchar_lk()) != L'\n')
#else  /* _UNICODE */
        while ((ch = _getchar_lk()) != '\n')
#endif  /* _UNICODE */
        {
                if (ch == _TEOF)
                {
                        if (pointer == string)
                        {
                                retval = NULL;
                                goto done;
                        }

                        break;
                }

                *pointer++ = (_TCHAR)ch;
        }

        *pointer = _T('\0');

/* Common return */
done:
        _unlock_str2(0, stdin);
        return(retval);
}
