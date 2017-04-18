/***
*fgets.c - get string from a file
*
*       Copyright (c) 1985-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       defines fgets() - read a string from a file
*
*******************************************************************************/

#include <cruntime.h>
#include <stdio.h>
#include <dbgint.h>
#include <file2.h>
#include <internal.h>
#include <mtdll.h>
#include <tchar.h>

/***
*char *fgets(string, count, stream) - input string from a stream
*
*Purpose:
*       get a string, up to count-1 chars or '\n', whichever comes first,
*       append '\0' and put the whole thing into string. the '\n' IS included
*       in the string. if count<=1 no input is requested. if EOF is found
*       immediately, return NULL. if EOF found after chars read, let EOF
*       finish the string as '\n' would.
*
*Entry:
*       char *string - pointer to place to store string
*       int count - max characters to place at string (include \0)
*       FILE *stream - stream to read from
*
*Exit:
*       returns string with text read from file in it.
*       if count <= 0 return NULL
*       if count == 1 put null string in string
*       returns NULL if error or end-of-file found immediately
*
*Exceptions:
*
*******************************************************************************/

#ifdef _UNICODE
wchar_t * __cdecl fgetws (
#else  /* _UNICODE */
char * __cdecl fgets (
#endif  /* _UNICODE */
        _TSCHAR *string,
        int count,
        FILE *str
        )
{
        REG1 FILE *stream;
        REG2 _TSCHAR *pointer = string;
        _TSCHAR *retval = string;
        int ch;

        _ASSERTE(string != NULL);
        _ASSERTE(str != NULL);

        if (count <= 0)
                return(NULL);

        /* Init stream pointer */
        stream = str;

        _lock_str(stream);

        while (--count)
        {
#ifdef _UNICODE
                if ((ch = _getwc_lk(stream)) == WEOF)
#else  /* _UNICODE */
                if ((ch = _getc_lk(stream)) == EOF)
#endif  /* _UNICODE */
                {
                        if (pointer == string) {
                                retval=NULL;
                                goto done;
                        }

                        break;
                }

                if ((*pointer++ = (_TSCHAR)ch) == _T('\n'))
                        break;
        }

        *pointer = _T('\0');

/* Common return */
done:
        _unlock_str(stream);
        return(retval);
}
