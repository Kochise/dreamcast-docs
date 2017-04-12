/***
*fputc.c - write a character to an output stream
*
*       Copyright (c) 1985-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       defines fputc() - writes a character to a stream
*       defines fputwc() - writes a wide character to a stream
*
*******************************************************************************/

#include <cruntime.h>
#include <stdio.h>
#include <dbgint.h>
#include <file2.h>
#include <internal.h>
#include <mtdll.h>

/***
*int fputc(ch, stream) - write a character to a stream
*
*Purpose:
*       Writes a character to a stream.  Function version of putc().
*
*Entry:
*       int ch - character to write
*       FILE *stream - stream to write to
*
*Exit:
*       returns the character if successful
*       returns EOF if fails
*
*Exceptions:
*
*******************************************************************************/

int __cdecl fputc (
        int ch,
        FILE *str
        )
{
        REG1 FILE *stream;
        REG2 int retval;

        _ASSERTE(str != NULL);

        /* Init stream pointer */
        stream = str;

        _lock_str(stream);
        retval = _putc_lk(ch,stream);
        _unlock_str(stream);

        return(retval);
}

#undef putc

int __cdecl putc (
        int ch,
        FILE *str
        )
{
        return fputc(ch, str);
}
