/***
*swprintf.c - print formatted to string
*
*       Copyright (c) 1985-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       defines swprintf() and _snwprintf() - print formatted data to string
*
*******************************************************************************/


#include <cruntime.h>
#include <stdio.h>
#include <wchar.h>
#include <dbgint.h>
#include <stdarg.h>
#include <internal.h>
#include <limits.h>
#include <mtdll.h>

#define MAXSTR INT_MAX


/***
*ifndef _COUNT_
*int swprintf(string, format, ...) - print formatted data to string
*else
*int _snwprintf(string, cnt, format, ...) - print formatted data to string
*endif
*
*Purpose:
*       Prints formatted data to the using the format string to
*       format data and getting as many arguments as called for
*       Sets up a FILE so file i/o operations can be used, make
*       string look like a huge buffer to it, but _flsbuf will
*       refuse to flush it if it fills up.  Appends '\0' to make
*       it a true string. _output does the real work here
*
*       Allocate the 'fake' _iob[] entry statically instead of on
*       the stack so that other routines can assume that _iob[]
*       entries are in are in DGROUP and, thus, are near.
*
*ifdef _COUNT_
*       The _snwprintf() flavor takes a count argument that is
*       the max number of wide characters that should be written to the
*       user's buffer.
*endif
*
*       Multi-thread: (1) Since there is no stream, this routine must
*       never try to get the stream lock (i.e., there is no stream
*       lock either). (2) Also, since there is only one statically
*       allocated 'fake' iob, we must lock/unlock to prevent collisions.
*
*Entry:
*       wchar_t *string - pointer to place to put output
*ifdef _COUNT_
*       size_t count - max number of wide characters to put in buffer
*endif
*       wchar_t *format - format string to control data format/number
*       of arguments followed by list of arguments, number and type
*       controlled by format string
*
*Exit:
*       returns number of wide characters printed
*
*Exceptions:
*
*******************************************************************************/

#ifndef _COUNT_

int __cdecl swprintf (
        wchar_t *string,
        const wchar_t *format,
        ...
        )
#else  /* _COUNT_ */

int __cdecl _snwprintf (
        wchar_t *string,
        size_t count,
        const wchar_t *format,
        ...
        )
#endif  /* _COUNT_ */

{
        FILE str;
        REG1 FILE *outfile = &str;
        va_list arglist;
        REG2 int retval;

        va_start(arglist, format);

        _ASSERTE(string != NULL);
        _ASSERTE(format != NULL);

        outfile->_flag = _IOWRT|_IOSTRG;
        outfile->_ptr = outfile->_base = (char *) string;
#ifndef _COUNT_
        outfile->_cnt = MAXSTR;
#else  /* _COUNT_ */
        outfile->_cnt = count*sizeof(wchar_t);
#endif  /* _COUNT_ */

        retval = _woutput(outfile,format,arglist);

        _putc_lk('\0',outfile); /* no-lock version */
        _putc_lk('\0',outfile); /* 2nd null byte for wchar_t version */

        return(retval);
}

