/***
*wscanf.c - read formatted data from stdin
*
*       Copyright (c) 1985-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       defines wscanf() - reads formatted data from stdin
*
*******************************************************************************/


#include <cruntime.h>
#include <stdio.h>
#include <wchar.h>
#include <dbgint.h>
#include <stdarg.h>
#include <file2.h>
#include <internal.h>
#include <mtdll.h>

/***
*int wscanf(format, ...) - read formatted data from stdin
*
*Purpose:
*       Reads formatted data from stdin into arguments.  _input does the real
*       work here.
*
*Entry:
*       char *format - format string
*       followed by list of pointers to storage for the data read.  The number
*       and type are controlled by the format string.
*
*Exit:
*       returns number of fields read and assigned
*
*Exceptions:
*
*******************************************************************************/

int __cdecl wscanf (
        const wchar_t *format,
        ...
        )
/*
 * stdin 'W'char_t 'SCAN', 'F'ormatted
 */
{
        int retval;

        va_list arglist;

// UNDONE: make va_start work with wchar_t format string
        va_start(arglist, format);

        _ASSERTE(format != NULL);

        _lock_str2(0, stdin);

        retval = (_winput(stdin,format,arglist));

        _unlock_str2(0, stdin);

        return(retval);
}

