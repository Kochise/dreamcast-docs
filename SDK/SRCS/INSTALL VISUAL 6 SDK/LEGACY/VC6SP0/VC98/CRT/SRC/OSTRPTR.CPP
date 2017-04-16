/***
* ostrptr.cpp - definitions for ostream operator<<(const void*) member function
*
*       Copyright (c) 1991-1997, Microsoft Corporation.  All rights reserved.
*
*Purpose:
*       Member function definition for ostream operator<<(const void*).
*
*******************************************************************************/

#include <cruntime.h>
#include <internal.h>
#include <stdio.h>
#include <iostream.h>
#pragma hdrstop

ostream& ostream::operator<<(const void * ptr)
{
_WINSTATIC char obuffer[12];
_WINSTATIC char fmt[4] = "%p";
_WINSTATIC char leader[4] = "0x";
    if (opfx())
        {
        if (ptr)
            {
            if (x_flags & uppercase)
                leader[1] = 'X';
            }
        sprintf(obuffer,fmt,ptr);
        writepad(leader,obuffer);
        osfx();
        }
    return *this;
}
