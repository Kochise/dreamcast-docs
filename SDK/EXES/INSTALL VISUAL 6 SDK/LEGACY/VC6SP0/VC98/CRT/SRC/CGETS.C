/***
*cgets.c - buffered keyboard input
*
*       Copyright (c) 1989-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       defines _cgets() - read a string directly from console
*
*******************************************************************************/

#include <cruntime.h>
#include <oscalls.h>
#include <mtdll.h>
#include <conio.h>
#include <stdlib.h>
#include <internal.h>

/*
 * mask to clear the bits required to be 0 in the handle state passed to
 * DOSSETFHSTATE.
 */
#define FHSTATEMASK 0xffd07888

/*
 * declaration for console handle
 */

extern int _coninpfh;


/***
*char *_cgets(string) - read string from console
*
*Purpose:
*       Reads a string from the console via ReadConsole on a cooked console
*       handle.  string[0] must contain the maximum length of the
*       string.  Returns pointer to str[2].
*
*       NOTE: _cgets() does NOT check the pushback character buffer (i.e.,
*       _chbuf).  Thus, _cgets() will not return any character that is
*       pushed back by the _ungetch() call.
*
*Entry:
*       char *string - place to store read string, str[0] = max length.
*
*Exit:
*       returns pointer to str[2], where the string starts.
*       returns NULL if error occurs
*
*Exceptions:
*
*******************************************************************************/

char * __cdecl _cgets (
        char *string
        )
{
        ULONG oldstate;
        ULONG num_read;
        char *result;

        _mlock(_CONIO_LOCK);            /* lock the console */

        string[1] = 0;                  /* no chars read yet */
        result = &string[2];

        /*
         * _coninpfh, the handle to the console input, is created the first
         * time that either _getch() or _cgets() or _kbhit() is called.
         */

        if ( _coninpfh == -2 )
            __initconin();

        if ( _coninpfh == -1 ) {
            _munlock(_CONIO_LOCK);      /* unlock the console */
            return(NULL);               /* return failure */
        }

        GetConsoleMode( (HANDLE)_coninpfh, &oldstate );
        SetConsoleMode( (HANDLE)_coninpfh, ENABLE_LINE_INPUT | ENABLE_PROCESSED_INPUT |
                                         ENABLE_ECHO_INPUT );

        if ( !ReadConsole( (HANDLE)_coninpfh,
                           (LPVOID)result,
                           (unsigned char)string[0],
                           &num_read,
                           NULL )
           )
            result = NULL;

        if ( result != NULL ) {

            /* set length of string and null terminate it */

            if (string[num_read] == '\r') {
                string[1] = (char)(num_read - 2);
                string[num_read] = '\0';
            } else if ( (num_read == (ULONG)(unsigned char)string[0]) &&
                        (string[num_read + 1] == '\r') ) {
                /* special case 1 - \r\n straddles the boundary */
                string[1] = (char)(num_read -1);
                string[1 + num_read] = '\0';
            } else if ( (num_read == 1) && (string[2] == '\n') ) {
                /* special case 2 - read a single '\n'*/
                string[1] = string[2] = '\0';
            } else {
                string[1] = (char)num_read;
                string[2 + num_read] = '\0';
            }
        }

        SetConsoleMode( (HANDLE)_coninpfh, oldstate );

        _munlock(_CONIO_LOCK);          /* unlock the console */

        return result;
}
