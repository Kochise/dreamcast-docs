/***
*perror.c - print system error message
*
*       Copyright (c) 1985-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       defines perror() - print system error message
*       System error message are indexed by errno; conforms to XENIX
*       standard, with much compatability with 1983 uniforum draft standard.
*
*******************************************************************************/

#include <cruntime.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <syserr.h>
#include <mtdll.h>
#include <io.h>

#if defined (_M_M68K) || defined (_M_MPPC)
#include <fcntl.h>
#include <share.h>
#endif  /* defined (_M_M68K) || defined (_M_MPPC) */

/***
*void perror(message) - print system error message
*
*Purpose:
*       prints user's error message, then follows it with ": ", then the system
*       error message, then a newline.  All output goes to stderr.  If user's
*       message is NULL or a null string, only the system error message is
*       printer.  If errno is weird, prints "Unknown error".
*
*Entry:
*       const char *message - users message to prefix system error message
*
*Exit:
*       Prints message; no return value.
*
*Exceptions:
*
*******************************************************************************/

void __cdecl perror (
        REG1 const char *message
        )
{

#if defined (_WIN32)
        REG2 int fh = 2;

        _lock_fh(fh);       /* acquire file handle lock */
#endif  /* defined (_WIN32) */

        if (message && *message)
        {

#if defined (_WIN32)
            _write_lk(fh,(char *)message,strlen(message));
            _write_lk(fh,": ",2);
#else  /* defined (_WIN32) */
            fprintf(stderr,"%s", (char *)message);
            fprintf(stderr,": ");
#endif  /* defined (_WIN32) */
        }

        message = _sys_err_msg( errno );

#if defined (_WIN32)
        _write_lk(fh,(char *)message,strlen(message));
        _write_lk(fh,"\n",1);

        _unlock_fh(fh);     /* release file handle lock */
#else  /* defined (_WIN32) */
        fprintf(stderr,"%s\n", (char *)message);
#endif  /* defined (_WIN32) */
}
