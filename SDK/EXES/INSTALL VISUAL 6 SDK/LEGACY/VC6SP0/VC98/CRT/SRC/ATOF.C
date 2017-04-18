/***
*atof.c - convert char string to floating point number
*
*       Copyright (c) 1985-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       Converts a character string into a floating point number.
*
*******************************************************************************/

#include <stdlib.h>
#include <math.h>
#include <cruntime.h>
#include <fltintrn.h>
#include <string.h>
#include <ctype.h>

/***
*double atof(nptr) - convert string to floating point number
*
*Purpose:
*       atof recognizes an optional string of whitespace, then
*       an optional sign, then a string of digits optionally
*       containing a decimal point, then an optional e or E followed
*       by an optionally signed integer, and converts all this to
*       to a floating point number.  The first unrecognized
*       character ends the string.
*
*Entry:
*       nptr - pointer to string to convert
*
*Exit:
*       returns floating point value of character representation
*
*Exceptions:
*
*******************************************************************************/

double __cdecl atof(
        REG1 const char *nptr
        )
{

#ifdef _MT
        struct _flt fltstruct;      /* temporary structure */
#endif  /* _MT */

        /* scan past leading space/tab characters */

        while ( isspace((int)(unsigned char)*nptr) )
                nptr++;

        /* let _fltin routine do the rest of the work */

#ifdef _MT
        return( *(double *)&(_fltin2( &fltstruct, nptr, strlen(nptr), 0, 0 )->
        dval) );
#else  /* _MT */
        return( *(double *)&(_fltin( nptr, strlen(nptr), 0, 0 )->dval) );
#endif  /* _MT */
}
