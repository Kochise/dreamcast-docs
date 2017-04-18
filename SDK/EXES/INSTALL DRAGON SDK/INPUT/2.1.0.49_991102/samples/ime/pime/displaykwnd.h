/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1998 Microsoft Corporation

Module Name:

    displaykwnd.h

Abstract:

    This is the header file for displaykwnd.cxx, which displays the kanji
    selection window (KWND).

Environment:

    Runs on Dreamcast under Windows CE.

-------------------------------------------------------------------*/


#ifndef DISPLAYKWND_H
#define DISPLAYKWND_H

#include "tchar.h"
#include "display.h"
#include "kwnd.h"
#include <ddraw.h>
#include "ddutil.h"


// DISPLAYKWND.CXX

BOOL
KWNDRender
    (
    WORD iKeyTop
    );

BOOL
KWNDRenderKey
    (
    LPDIRECTDRAWSURFACE         pddsTarget,
    WORD                        xKeyboardLeftEdge,
    WORD                        yKeyboardTopEdge,
    WORD                        iKey,
    BOOL                        fFocus,
    WORD                        iKeyTop
    );


#endif        // DISPLAYKWND_H
