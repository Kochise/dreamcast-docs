/***
*printf.c - print formatted
*
*       Copyright (c) 1985-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       defines printf() - print formatted data
*
*******************************************************************************/

#include <cruntime.h>
#include <stdio.h>
#include <dbgint.h>
#include <stdarg.h>
#include <file2.h>
#include <internal.h>
#include <mtdll.h>

/***
*int printf(format, ...) - print formatted data
*
*Purpose:
*       Prints formatted data on stdout using the format string to
*       format data and getting as many arguments as called for
*       Uses temporary buffering to improve efficiency.
*       _output does the real work here
*
*Entry:
*       char *format - format string to control data format/number of arguments
*       followed by list of arguments, number and type controlled by
*       format string
*
*Exit:
*       returns number of characters printed
*
*Exceptions:
*
*******************************************************************************/

int __cdecl printf (
        const char *format,
        ...
        )
/*
 * stdout 'PRINT', 'F'ormatted
 */
{
        va_list arglist;
        int buffing;
        int retval;

        va_start(arglist, format);

        _ASSERTE(format != NULL);

        _lock_str2(1, stdout);

        buffing = _stbuf(stdout);

        retval = _output(stdout,format,arglist);

        _ftbuf(buffing, stdout);

        _unlock_str2(1, stdout);

        return(retval);
}
