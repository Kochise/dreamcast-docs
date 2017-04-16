/***
*cputs.c - direct console output
*
*       Copyright (c) 1989-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       defines _cputs() - write string directly to console
*
*******************************************************************************/

#include <cruntime.h>
#include <oscalls.h>
#include <internal.h>
#include <mtdll.h>
#include <conio.h>
#include <stdio.h>
#include <string.h>

/*
 * declaration for console handle
 */
extern int _confh;

/***
*int _cputs(string) - put a string to the console
*
*Purpose:
*       Writes the string directly to the console.  No newline
*       is appended.
*
*Entry:
*       char *string - string to write
*
*Exit:
*       Good return = 0
*       Error return = !0
*
*Exceptions:
*
*******************************************************************************/

int __cdecl _cputs (
        const char *string
        )
{
        ULONG num_written;
        int error = 0;                   /* error occurred? */

        _mlock(_CONIO_LOCK);             /* acquire console lock */

        /*
         * _confh, the handle to the console output, is created the
         * first time that either _putch() or _cputs() is called.
         */

        if (_confh == -2)
            __initconout();

        /* write string to console file handle */

        if ( (_confh == -1) || !WriteConsole( (HANDLE)_confh,
                                              (LPVOID)string,
                                              strlen(string),
                                              &num_written,
                                              NULL )
           )
                /* return error indicator */
                error = -1;

        _munlock(_CONIO_LOCK);          /* release console lock */

        return error;
}
