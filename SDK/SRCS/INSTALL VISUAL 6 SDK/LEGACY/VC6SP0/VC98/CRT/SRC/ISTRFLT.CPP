/***
* istrflt.cpp - definitions for istream operator>>(float) member function
*
*       Copyright (c) 1991-1997, Microsoft Corporation.  All rights reserved.
*
*Purpose:
*       Definitions of operator>>(float) member function for istream class.
*       [AT&T C++]
*
*******************************************************************************/

#include <cruntime.h>
#include <internal.h>
#include <stdlib.h>
#include <float.h>
#include <iostream.h>
#pragma hdrstop

#pragma check_stack(on)         // large buffer(s)

#define MAXFLTSIZ       20

istream& istream::operator>>(float& n)
{
_WINSTATIC char ibuffer[MAXFLTSIZ];
    double d;
    char ** endptr = (char**)NULL;
    if (ipfx(0))
        {
        if (getdouble(ibuffer, MAXFLTSIZ)>0)
            {
            d = strtod(ibuffer, endptr);

            if (d > FLT_MAX)
                n = FLT_MAX;
            else if (d < -FLT_MAX)
                n =  -FLT_MAX;
            else if ((d>0) && (d< FLT_MIN))
                n = FLT_MIN;
            else if ((d<0) && (d> -FLT_MIN))
                n = - FLT_MIN;
            else
                n = (float) d;
            }
        isfx();
        }
return *this;
}
