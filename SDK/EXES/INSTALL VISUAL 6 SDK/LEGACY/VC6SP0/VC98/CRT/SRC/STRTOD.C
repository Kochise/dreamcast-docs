/***
*strtod.c - convert string to floating point number
*
*       Copyright (c) 1985-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       Convert character string to floating point number
*
*******************************************************************************/

#include <cruntime.h>
#include <stdlib.h>
#include <fltintrn.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <math.h>

/***
*double strtod(nptr, endptr) - convert string to double
*
*Purpose:
*       strtod recognizes an optional string of tabs and spaces,
*       then an optional sign, then a string of digits optionally
*       containing a decimal point, then an optional e or E followed
*       by an optionally signed integer, and converts all this to
*       to a floating point number.  The first unrecognized
*       character ends the string, and is pointed to by endptr.
*
*Entry:
*       nptr - pointer to string to convert
*
*Exit:
*       returns value of character string
*       char **endptr - if not NULL, points to character which stopped
*                       the scan
*
*Exceptions:
*
*******************************************************************************/

double __cdecl strtod (
        const char *nptr,
        REG2 char **endptr
        )
{

#ifdef _MT
        struct _flt answerstruct;
#endif  /* _MT */

        FLT      answer;
        double       tmp;
        unsigned int flags;
        REG1 char *ptr = (char *) nptr;

        /* scan past leading space/tab characters */

        while ( isspace((int)(unsigned char)*ptr) )
                ptr++;

        /* let _fltin routine do the rest of the work */

#ifdef _MT
        /* ok to take address of stack variable here; fltin2 knows to use ss */
        answer = _fltin2( &answerstruct, ptr, strlen(ptr), 0, 0);
#else  /* _MT */
        answer = _fltin(ptr, strlen(ptr), 0, 0);
#endif  /* _MT */

        if ( endptr != NULL )
                *endptr = (char *) ptr + answer->nbytes;

        flags = answer->flags;
        if ( flags & (512 | 64)) {
                /* no digits found or invalid format:
                   ANSI says return 0.0, and *endptr = nptr */
                tmp = 0.0;
                if ( endptr != NULL )
                        *endptr = (char *) nptr;
        }
        else if ( flags & (128 | 1) ) {
                if ( *ptr == '-' )
                        tmp = -HUGE_VAL;        /* negative overflow */
                else
                        tmp = HUGE_VAL;         /* positive overflow */
                errno = ERANGE;
        }
        else if ( flags & 256 ) {
                tmp = 0.0;                      /* underflow */
                errno = ERANGE;
        }
        else
                tmp = answer->dval;

        return(tmp);
}
