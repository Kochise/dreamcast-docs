/***
* istrusht.cpp - definitions for istream class operator>>(unsigned short) funct
*
*       Copyright (c) 1991-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       Definitions of operator>>(unsigned short) member function for istream
*       class.
*       [AT&T C++]
*
*******************************************************************************/

#include <cruntime.h>
#include <internal.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>
#include <iostream.h>
#pragma hdrstop

/***
*istream& istream::operator>>(unsigned short& n) - extract unsigned short
*
*Purpose:
*       Extract unsigned short value from stream
*       Valid range is SHRT_MIN to USHRT_MAX.
*
*Entry:
*       n = value to update
*
*Exit:
*       n updated, or ios::failbit and n=USHRT_MAX if error
*
*Exceptions:
*       Stream error on entry or value out of range
*
*******************************************************************************/
istream& istream::operator>>(unsigned short& n)
{
_WINSTATIC char ibuffer[MAXLONGSIZ];
    unsigned long value;
    char ** endptr = (char**)NULL;
    if (ipfx(0))
        {
        value = strtoul(ibuffer, endptr, getint(ibuffer));

        if (((value>USHRT_MAX) && (value<=(ULONG_MAX-(-SHRT_MIN))))
                || ((value==ULONG_MAX) && (errno==ERANGE)))
            {
            n = USHRT_MAX;
            state |= ios::failbit;
            }
        else
            n = (unsigned short) value;

        isfx();
        }
return *this;
}
