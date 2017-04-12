/***
*fprintf.c - print formatted data to stream
*
*       Copyright (c) 1985-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       defines fprintf() - print formatted data to stream
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
*int fprintf(stream, format, ...) - print formatted data
*
*Purpose:
*       Prints formatted data on the given using the format string to
*       format data and getting as many arguments as called for
*       _output does the real work here
*
*Entry:
*       FILE *stream - stream to print on
*       char *format - format string to control data format/number of arguments
*       followed by arguments to print, number and type controlled by
*       format string
*
*Exit:
*       returns number of characters printed
*
*Exceptions:
*
*******************************************************************************/

int __cdecl fprintf (
        FILE *str,
        const char *format,
        ...
        )
/*
 * 'F'ile (stream) 'PRINT', 'F'ormatted
 */
{
        va_list(arglist);
        REG1 FILE *stream;
        REG2 int buffing;
        int retval;

        va_start(arglist, format);

        _ASSERTE(str != NULL);
        _ASSERTE(format != NULL);

        /* Init stream pointer */
        stream = str;

        _lock_str(stream);
        buffing = _stbuf(stream);
        retval = _output(stream,format,arglist);
        _ftbuf(buffing, stream);
        _unlock_str(stream);

        return(retval);
}
