/***
*vswprint.c - print formatted data into a string from var arg list
*
*       Copyright (c) 1985-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       defines vswprintf() and _vsnwprintf() - print formatted output to
*       a string, get the data from an argument ptr instead of explicit
*       arguments.
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
*int vswprintf(string, format, ap) - print formatted data to string from arg ptr
*else
*int _vsnwprintf(string, format, ap) - print formatted data to string from arg ptr
*endif
*
*Purpose:
*       Prints formatted data, but to a string and gets data from an argument
*       pointer.
*       Sets up a FILE so file i/o operations can be used, make string look
*       like a huge buffer to it, but _flsbuf will refuse to flush it if it
*       fills up. Appends '\0' to make it a true string.
*
*       Allocate the 'fake' _iob[] entryit statically instead of on
*       the stack so that other routines can assume that _iob[] entries are in
*       are in DGROUP and, thus, are near.
*
*ifdef _COUNT_
*       The _vsnwprintf() flavor takes a count argument that is
*       the max number of bytes that should be written to the
*       user's buffer.
*endif
*
*       Multi-thread: (1) Since there is no stream, this routine must never try
*       to get the stream lock (i.e., there is no stream lock either).  (2)
*       Also, since there is only one staticly allocated 'fake' iob, we must
*       lock/unlock to prevent collisions.
*
*Entry:
*       wchar_t *string - place to put destination string
*ifdef _COUNT_
*       size_t count - max number of bytes to put in buffer
*endif
*       wchar_t *format - format string, describes format of data
*       va_list ap - varargs argument pointer
*
*Exit:
*       returns number of wide characters in string
*
*Exceptions:
*
*******************************************************************************/

#ifndef _COUNT_

int __cdecl vswprintf (
        wchar_t *string,
        const wchar_t *format,
        va_list ap
        )
#else  /* _COUNT_ */

int __cdecl _vsnwprintf (
        wchar_t *string,
        size_t count,
        const wchar_t *format,
        va_list ap
        )
#endif  /* _COUNT_ */

{
        FILE str;
        REG1 FILE *outfile = &str;
        REG2 int retval;

        _ASSERTE(string != NULL);
        _ASSERTE(format != NULL);

        outfile->_flag = _IOWRT|_IOSTRG;
        outfile->_ptr = outfile->_base = (char *) string;
#ifndef _COUNT_
        outfile->_cnt = MAXSTR;
#else  /* _COUNT_ */
        outfile->_cnt = count*sizeof(wchar_t);
#endif  /* _COUNT_ */

        retval = _woutput(outfile,format,ap );
        _putc_lk('\0',outfile);     /* no-lock version */
        _putc_lk('\0',outfile);     /* 2nd byte for wide char version */

        return(retval);
}

