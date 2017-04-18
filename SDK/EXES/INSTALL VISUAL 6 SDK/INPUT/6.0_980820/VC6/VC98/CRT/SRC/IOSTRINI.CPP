/***
*iostrini.cpp - definition and initialization for predefined stream cout.
*
*       Copyright (c) 1991-1997, Microsoft Corporation.  All rights reserved.
*
*Purpose:
*       Definition and initialization of and predefined iostream cout.
*
*******************************************************************************/
#include <cruntime.h>
#include <internal.h>
#include <iostream.h>
#include <fstream.h>
#include <dbgint.h>
#pragma hdrstop

// put contructors in special MS-specific XIFM segment
#pragma warning(disable:4074)   // disable init_seg warning
#pragma init_seg(compiler)

ostream_withassign cout(_new_crt filebuf(1));

static Iostream_init  __InitCout(cout,-1);


/***
*Iostream_init::Iostream_init() - initialize predefined streams
*
*Purpose:
*        For compatibility only.  Not used.
*Entry:
*
*Exit:
*
*Exceptions:
*
*******************************************************************************/
        Iostream_init::Iostream_init() { }      // do nothing

/***
*Iostream_init::Iostream_init() - initialize predefined streams
*
*Purpose:
*        Initializes predefined streams: cin, cout, cerr, clog;
*Entry:
*       pstrm = cin, cout, cerr, or clog
*       sflg =  1 if cerr (unit buffered)
*       sflg = -1 if cout
*
*Exit:
*
*Exceptions:
*
*******************************************************************************/
        Iostream_init::Iostream_init(ios& pstrm, int sflg)
{
        pstrm.delbuf(1);
        if (sflg>=0)    // make sure not cout
                pstrm.tie(&cout);
        if (sflg>0)
                pstrm.setf(ios::unitbuf);
}

/***
*Iostream_init::~Iostream_init() - destroy predefined streams on exit
*
*Purpose:
*        Destroy predefined streams: cin, cout, cerr, clog;
*Entry:
*
*Exit:
*
*Exceptions:
*
*******************************************************************************/
        Iostream_init::~Iostream_init() { }     // do nothing

