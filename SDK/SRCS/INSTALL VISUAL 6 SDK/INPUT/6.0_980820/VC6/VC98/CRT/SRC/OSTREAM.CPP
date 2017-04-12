/***
* ostream.cpp - definitions for ostream and ostream_withassign classes
*
*       Copyright (c) 1991-1997, Microsoft Corporation.  All rights reserved.
*
*Purpose:
*       Contains the core member function definitions for ostream and
*       ostream_withassign classes.
*
*******************************************************************************/

#include <cruntime.h>
#include <internal.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream.h>
#include <dbgint.h>
#pragma hdrstop

int ostream::opfx()
{
    lock();
    if (state)
        {
        state |= ios::failbit;
        unlock();
        return 0;
        }
    if (x_tie)
        {
        x_tie->flush();
        }
    lockbuf();
    return(1);  // return non-zero
}

void ostream::osfx()
{
    x_width = 0;
    if (x_flags & unitbuf)
        {
        if (bp->sync()==EOF)
            state = failbit | badbit;
        }
    if (x_flags & ios::stdio)
        {
        if (fflush(stdout)==EOF)
            state |= failbit;
        if (fflush(stderr)==EOF)
            state |= failbit;
        }
    unlockbuf();
    unlock();
}

// note: called inline by unsigned char * and signed char * versions:
ostream& ostream::operator<<(const char * s)
{
    if (opfx()) {
        writepad("",s);
        osfx();
    }
    return *this;
}

ostream& ostream::flush()
{
    lock();
    lockbuf();
    if (bp->sync()==EOF)
        state |= ios::failbit;
    unlockbuf();
    unlock();
    return(*this);
}

        ostream::ostream()
// : ios()
{
        x_floatused = 0;
}

        ostream::ostream(streambuf* _inistbf)
// : ios()
{
        init(_inistbf);

        x_floatused = 0;
}

        ostream::ostream(const ostream& _ostrm)
// : ios()
{
        init(_ostrm.rdbuf());

        x_floatused = 0;
}

        ostream::~ostream()
// : ~ios()
{
}

// used in ios::sync_with_stdio()
ostream& ostream::operator=(streambuf * _sbuf)
{

        if (delbuf() && rdbuf())
            delete rdbuf();

        bp = 0;

        this->ios::operator=(ios());    // initialize ios members
        delbuf(0);                      // important!
        init(_sbuf);

        return *this;
}


        ostream_withassign::ostream_withassign()
: ostream()
{
}

        ostream_withassign::ostream_withassign(streambuf* _os)
: ostream(_os)
{
}

        ostream_withassign::~ostream_withassign()
// : ~ostream()
{
}

ostream& ostream::writepad(const char * leader, const char * value)

        {
unsigned int len, leadlen;
long padlen;
        leadlen = strlen(leader);
        len = strlen(value);
        padlen = (((unsigned)x_width) > (len+leadlen)) ? ((unsigned)x_width) - (len + leadlen) : 0;
        if (!(x_flags & (left|internal)))  // default is right-adjustment
            {
            while (padlen-- >0)
                {
                if (bp->sputc((unsigned char)x_fill)==EOF)
                    state |= (ios::failbit|ios::badbit);
                }
            }
        if (leadlen)
            {
            if ((unsigned)bp->sputn(leader,leadlen)!=leadlen)
                state |= (failbit|badbit);
            }
        if (x_flags & internal)
            {
            while (padlen-- >0)
                {
                if (bp->sputc((unsigned char)x_fill)==EOF)
                    state |= (ios::failbit|ios::badbit);
                }
            }
        if ((unsigned)bp->sputn(value,len)!=len)
            state |= (failbit|badbit);
        if (x_flags & left)
            {
            while ((padlen--)>0)        // left-adjust if necessary
                {
                if (bp->sputc((unsigned char)x_fill)==EOF)
                    state |= (ios::failbit|ios::badbit);
                }
            }
        return (*this);
        }
