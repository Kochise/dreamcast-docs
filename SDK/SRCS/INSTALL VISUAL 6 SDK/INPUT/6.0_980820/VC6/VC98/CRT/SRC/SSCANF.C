/***
*sscanf.c - read formatted data from string
*
*       Copyright (c) 1985-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       defines scanf() - reads formatted data from string
*
*******************************************************************************/

#include <cruntime.h>
#include <stdio.h>
#include <dbgint.h>
#include <stdarg.h>
#include <string.h>
#include <internal.h>
#include <mtdll.h>

/***
*int sscanf(string, format, ...) - read formatted data from string
*
*Purpose:
*       Reads formatted data from string into arguments.  _input does the real
*       work here.  Sets up a FILE so file i/o operations can be used, makes
*       string look like a huge buffer to it, but _filbuf will refuse to refill
*       it if it is exhausted.
*
*       Allocate the 'fake' _iob[] entryit statically instead of on
*       the stack so that other routines can assume that _iob[] entries are in
*       are in DGROUP and, thus, are near.
*
*       Multi-thread: (1) Since there is no stream, this routine must never try
*       to get the stream lock (i.e., there is no stream lock either).  (2)
*       Also, since there is only one staticly allocated 'fake' iob, we must
*       lock/unlock to prevent collisions.
*
*Entry:
*       char *string - string to read data from
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

int __cdecl sscanf (
        REG2 const char *string,
        const char *format,
        ...
        )
/*
 * 'S'tring 'SCAN', 'F'ormatted
 */
{
        va_list arglist;
        FILE str;
        REG1 FILE *infile = &str;
        REG2 int retval;

        va_start(arglist, format);

        _ASSERTE(string != NULL);
        _ASSERTE(format != NULL);

        infile->_flag = _IOREAD|_IOSTRG|_IOMYBUF;
        infile->_ptr = infile->_base = (char *) string;
        infile->_cnt = strlen(string);

        retval = (_input(infile,format,arglist));

        return(retval);
}
