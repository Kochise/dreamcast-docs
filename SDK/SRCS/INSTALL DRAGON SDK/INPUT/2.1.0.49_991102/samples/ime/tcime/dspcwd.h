/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1998 Microsoft Corporation

Module Name:

    dspcwnd.h

Abstract:

    This is the header file for dspcwnd.cxx, which displays the candidate
    selection window (CWND).

Environment:

    Runs on Dreamcast under Windows CE.

-------------------------------------------------------------------*/


#ifndef _DISPLAYCWND_H
#define _DISPLAYCWND_H

#include <ddraw.h>
#include "tchar.h"
#include "candwnd.h"


// DSPCWND.CPP

BOOL CWNDRender(WORD iKeyTop);

BOOL CWNDRenderKey(LPDIRECTDRAWSURFACE pddsTarget,
                   WORD                iKey,
                   BOOL                fFocus,
                   WORD                iKeyTop);

#endif // _DISPLAYCWND_H
