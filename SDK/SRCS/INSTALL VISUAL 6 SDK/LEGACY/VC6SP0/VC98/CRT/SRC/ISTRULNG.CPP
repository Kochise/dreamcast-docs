/***
* istrulng.cpp - definitions for istream class operator>>(unsigned long) funct
*
*       Copyright (c) 1991-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       Definitions of operator>>(unsigned long) member function(s) for istream
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
*istream& istream::operator>>(unsigned long& n) - extract unsigned long
*
*Purpose:
*       Extract unsigned long value from stream
*
*Entry:
*       n = value to update
*
*Exit:
*       n updated, or ios::failbit and n=ULONG_MAX if error
*
*Exceptions:
*       Stream error on entry or value out of range
*
*******************************************************************************/
istream& istream::operator>>(unsigned long& n)
{
_WINSTATIC char ibuffer[MAXLONGSIZ];
    char ** endptr = (char**)NULL;
    if (ipfx(0)) {
        n = strtoul(ibuffer, endptr, getint(ibuffer));
        if ((n==ULONG_MAX) && (errno==ERANGE))
            {
            state |= ios::failbit;
            }

        isfx();
        }
return *this;
}
