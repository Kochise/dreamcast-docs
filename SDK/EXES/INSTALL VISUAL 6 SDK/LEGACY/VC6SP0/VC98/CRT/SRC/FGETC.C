/***
*fgetc.c - get a character from a stream
*
*       Copyright (c) 1985-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       defines fgetc() and getc() - read  a character from a stream
*
*******************************************************************************/

#include <cruntime.h>
#include <stdio.h>
#include <dbgint.h>
#include <file2.h>
#include <internal.h>
#include <mtdll.h>

/***
*int fgetc(stream), getc(stream) - read a character from a stream
*
*Purpose:
*       reads a character from the given stream
*
*Entry:
*       FILE *stream - stream to read character from
*
*Exit:
*       returns the character read
*       returns EOF if at end of file or error occurred
*
*Exceptions:
*
*******************************************************************************/

int __cdecl fgetc (
        REG1 FILE *stream
        )
{
        int retval;

        _ASSERTE(stream != NULL);

        _lock_str(stream);
        retval = _getc_lk(stream);
        _unlock_str(stream);

        return(retval);
}

#undef getc

int __cdecl getc (
        FILE *stream
        )
{
        return fgetc(stream);
}
