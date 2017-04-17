/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1998 Microsoft Corporation

Module Name:

    displayswnd.h

Abstract:

    This is the header file for displayswnd.cxx, which displays the symbol
    window (SWND).

Environment:

    Runs on Dreamcast under Windows CE.

-------------------------------------------------------------------*/


#ifndef DISPLAYSWND_H
#define DISPLAYSWND_H

#include "tchar.h"
#include "display.h"
#include "swnd.h"
#include <ddraw.h>
#include "ddutil.h"


extern LPDIRECTDRAWSURFACE    g_lpddsSWNDDownArrow;
extern LPDIRECTDRAWSURFACE    g_lpddsSWNDUpArrow;

// DISPLAYSWND.CXX

BOOL
SWNDRender
    (
    WORD iKeyTop
    );

BOOL
SWNDRenderKey
    (
    LPDIRECTDRAWSURFACE         pddsTarget,
    WORD                        xKeyboardLeftEdge,
    WORD                        yKeyboardTopEdge,
    SWNDKEY*                    psk,
    BOOL                        fFocus,
    WORD                        iKeyTop
    );



#endif        // DISPLAYSWND_H


