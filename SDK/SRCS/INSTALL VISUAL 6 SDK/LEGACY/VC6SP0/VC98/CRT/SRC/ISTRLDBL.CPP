/***
* istrldbl.cpp - definitions for istream class operator>>(long double) funct
*
*       Copyright (c) 1991-1997, Microsoft Corporation.  All rights reserved.
*
*Purpose:
*       Definitions of operator>>(long double) member function for istream
*       class.
*       [AT&T C++]
*
*******************************************************************************/

#include <cruntime.h>
#include <internal.h>
#include <stdlib.h>
#include <iostream.h>
#pragma hdrstop

#pragma check_stack(on)         // large buffer(s)

#define MAXLDBLSIZ      32

istream& istream::operator>>(long double& n)
{
_WINSTATIC char ibuffer[MAXLDBLSIZ];
    char ** endptr = (char**)NULL;
    if (ipfx(0))
        {
        if (getdouble(ibuffer, MAXLDBLSIZ)>0)
            {
            n = (long double)strtod(ibuffer, endptr);
            }
        isfx();
        }
return *this;
}
