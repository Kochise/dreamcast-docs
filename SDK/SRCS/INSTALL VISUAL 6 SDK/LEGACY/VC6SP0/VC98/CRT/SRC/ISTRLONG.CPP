/***
* istrlong.cpp - definitions for istream class operator>>(long) member function
*
*       Copyright (c) 1991-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       Definitions of operator>>(long) member function(s) for istream class.
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
*istream& istream::operator>>(long& n) - extract long
*
*Purpose:
*       Extract long value from stream
*
*Entry:
*       n = value to update
*
*Exit:
*       n updated, or ios::failbit & n=LONG_MAX/LONG_MIN on overflow/underflow
*
*Exceptions:
*       Stream error on entry or value out of range
*
*******************************************************************************/
istream& istream::operator>>(long& n)
{
_WINSTATIC char ibuffer[MAXLONGSIZ];
    char ** endptr = (char**)NULL;
    if (ipfx(0)) {
        n = strtol(ibuffer, endptr, getint(ibuffer));
        if (errno==ERANGE)
            {
            state |= ios::failbit;
            }

        isfx();
    }
return *this;
}
