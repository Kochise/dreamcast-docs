/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1998 Microsoft Corporation

Module Name:

    displayskb.h

Abstract:

    This is the header file for displayskb.cxx, which displays the software
    keyboard (SKB).

Environment:

    Runs on Dreamcast under Windows CE.

-------------------------------------------------------------------*/


#ifndef DISPLAYSKB_H
#define DISPLAYSKB_H

#include "tchar.h"
#include "display.h"
#include "softkbd.h"
#include <ddraw.h>
#include "ddutil.h"


// DISPLAYKBD.CXX
BOOL 
SKBRender
    (
    void
    );
BOOL
SKBRenderKey
    (
    LPDIRECTDRAWSURFACE        pddsTarget,
    SOFTKEY*                    psk,
    BOOL                        fFocus,
	TCHAR*                      pszTextOverride
    );


#endif        // DISPLAYSKB_H
