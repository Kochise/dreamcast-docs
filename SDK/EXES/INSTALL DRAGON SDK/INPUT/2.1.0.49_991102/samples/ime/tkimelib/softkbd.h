/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1998 Microsoft Corporation

Module Name:

    softkbd.h

Abstract:

    This file is the header file for softkbd.cxx, which manages the soft 
    keyboard window (SKB).

Environment:

    Runs on Dreamcast under Windows CE.

-------------------------------------------------------------------*/

#ifndef SOFTKBD_H
#define SOFTKBD_H

#include "windows.h"
#include "ddraw.h"
#include "displayskb.h"
#include "inputskb.h"
#include "swnd.h"
#include "hiragana.h"
#include "katakana.h"
#include "romanji.h"
#include "symbols.h"


// SOFTKBD.CXX
BOOL
SKBCreate
    (
    KBDLAYOUT               kbdInitial
    );
BOOL 
SKBCreateWindow 
    (
    void
    );
void
SKBDestroy
    (
    void
    );
void
SKBUpdate
    (
    void
    );
WORD
SKBFindKeyUnderCursor
    (
    void
    );
void
SKBUpdateFocusRect
    (
    void
    );
void SKBBlt
    (
    LPDIRECTDRAWSURFACE lpDDSBack
    );

extern SOFTKEY*             g_pskCurrentSKB;
extern WORD                 g_cCurrentSKBKeys;
extern WORD                 g_xCursor;
extern WORD                 g_yCursor;
extern WORD                 g_iKeyFocus;
extern LPDIRECTDRAWSURFACE g_lpddsSKB;
extern WORD                 g_iSWNDKeyTop;

#endif  // SOFTKBD_H
