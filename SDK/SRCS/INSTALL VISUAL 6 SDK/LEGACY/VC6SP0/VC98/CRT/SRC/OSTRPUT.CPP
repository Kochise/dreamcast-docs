/***
* ostrput.cpp - definitions for ostream classes put() and write() functions
*
*       Copyright (c) 1991-1997, Microsoft Corporation.  All rights reserved.
*
*Purpose:
*       Contains the member function definitions for ostream put() and write().
*
*******************************************************************************/

#include <cruntime.h>
#include <internal.h>
#include <iostream.h>
#pragma hdrstop

// note: called inline by char and signed char versions:
ostream& ostream::put(unsigned char c)
{
    if (opfx())
        {
        if (bp->sputc((int)c)==EOF)
            state |= (failbit|badbit);
        osfx();
        }
    return(*this);
}

// note: called inline by unsigned char * and signed char * versions:
ostream& ostream::write(const char * s, int n)
{
    if (opfx())
        {
// Note: 'n' treated as unsigned
        if (bp->sputn(s,n)!=n)
            state |= (failbit|badbit);
        osfx();
        }
    return(*this);
}
