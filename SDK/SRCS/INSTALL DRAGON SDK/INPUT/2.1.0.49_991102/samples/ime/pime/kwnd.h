/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1998 Microsoft Corporation

Module Name:

    kwnd.h

Abstract:

    Header file for kwnd.cxx, which manages the kanji selection window (KWND).

Environment:

    Runs on Dreamcast under Windows CE.

-------------------------------------------------------------------*/

#ifndef KWND_H
#define KWND_H

#include "windows.h"
#include "ddraw.h"
#include "displaykwnd.h"
#include "inputkwnd.h"
#include "romanji.h"
#include "kanji.h"
#include "symbols.h"

#define KWND_FONTHEIGHT             28

#define MAX_KANJI                   180
#define KWND_ROWS                   9
#define KWND_COLUMNS                1
#define MAX_KANJI_DISPLAYED         (KWND_ROWS * KWND_COLUMNS)
#define SPECIAL_KWND_KEYS           2
#define TOTAL_KWND_KEYS             (MAX_KANJI + SPECIAL_KWND_KEYS)
#define KWND_COLWIDTH               50
#define KWND_ROWHEIGHT              (KWND_FONTHEIGHT * 10 / 8)
#define KWND_LEFTEDGE               300
#define KWND_TOPEDGE                130
#define KWND_SCROLLBARWIDTH         15
#define KWND_WIDTH                  (KWND_COLWIDTH * KWND_COLUMNS + KWND_SCROLLBARWIDTH)
#define KWND_KEYS_HEIGHT            (KWND_ROWHEIGHT * KWND_ROWS)
#define KWND_BORDER_HEIGHT          0
#define KWND_HEIGHT                 (KWND_KEYS_HEIGHT + 2 * KWND_BORDER_HEIGHT)
#define KWND_BKGNDCOLOR             LIGHTGRAY
#define KWND_BORDER_COLOR           DARKGRAY

#define KWNDKEY_SHADOW_THICKNESS            2
#define KWNDKEY_FILL_COLOR                  LIGHTGRAY
#define KWNDKEY_SHADOW_LIGHT_COLOR          WHITE
#define KWNDKEY_SHADOW_DARK_COLOR           DARKGRAY
#define KWNDKEY_BORDER_COLOR                BLACK
#define KWNDKEY_TEXT_COLOR                  RGB(0,0,0) // Black


// KWND.CXX
BOOL
KWNDCreate
    (
    void
    );
void
KWNDUpdateFocusRect
    (
    WORD                    iKeyTop,
    WORD                    iKWNDNewFocus
    );
BOOL 
KWNDCreateWindow 
    (
    void
    );
void
KWNDDestroy
    (
    void
    );
WORD
KWNDFindKeyUnderCursor
    (
    void
    );
void
KWNDBlt
    (
    LPDIRECTDRAWSURFACE lpDDSBack
    );


extern KWNDKEY              g_pskCurrentKWND[TOTAL_KWND_KEYS];
extern WORD                 g_cCurrentKWNDKeys;
extern WORD                 g_xKWNDCursor;
extern WORD                 g_yKWNDCursor;
extern HFONT                g_hfontKWND;
extern WORD                 g_iKWNDFocus;
extern LPDIRECTDRAWSURFACE  g_lpddsKWND;
extern WORD                 g_cCurrentKWNDKeys;

#endif  // KWND_H
