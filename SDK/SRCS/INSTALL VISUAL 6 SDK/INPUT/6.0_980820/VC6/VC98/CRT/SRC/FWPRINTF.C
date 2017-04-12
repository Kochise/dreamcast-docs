/***
*fwprintf.c - print formatted data to stream
*
*       Copyright (c) 1992-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       defines fwprintf() - print formatted data to stream
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
*int fwprintf(stream, format, ...) - print formatted data
*
*Purpose:
*       Prints formatted data on the given using the format string to
*       format data and getting as many arguments as called for
*       _output does the real work here
*
*Entry:
*       FILE *stream - stream to print on
*       wchar_t *format - format string to control data format/number of arguments
*       followed by arguments to print, number and type controlled by
*       format string
*
*Exit:
*       returns number of wide characters printed
*
*Exceptions:
*
*******************************************************************************/

int __cdecl fwprintf (
        FILE *str,
        const wchar_t *format,
        ...
        )
/*
 * 'F'ile (stream) 'W'char_t 'PRINT', 'F'ormatted
 */
{
        va_list(arglist);
        REG1 FILE *stream;
        REG2 int buffing;
        int retval;

// UNDONE: make va_start work with wchar_t format string
        va_start(arglist, format);

        _ASSERTE(str != NULL);
        _ASSERTE(format != NULL);

        /* Init stream pointer */
        stream = str;

        _lock_str(stream);
        buffing = _stbuf(stream);
        retval = _woutput(stream,format,arglist);
        _ftbuf(buffing, stream);
        _unlock_str(stream);

        return(retval);
}

