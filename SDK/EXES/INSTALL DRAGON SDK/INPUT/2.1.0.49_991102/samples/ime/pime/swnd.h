
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1998 Microsoft Corporation

Module Name:

    swnd.h

Abstract:

    Header file for swnd.cxx, which manages the symbol window (SWND).

Environment:

    Runs on Dreamcast under Windows CE.

-------------------------------------------------------------------*/

#ifndef SWND_H
#define SWND_H


#include "windows.h"
#include "ddraw.h"
#include "symbols.h"
#include "displayswnd.h"
#include "inputswnd.h"
#include "kanji.h"
#include "romanji.h"

#define SWND_ROWS                   8
#define SWND_COLUMNS                9
// one special key: the reject button
#define SWND_SPECIAL_KEYS           1
#define MAX_SWND_DISPLAYED          SWND_ROWS * SWND_COLUMNS
#define SWND_COLWIDTH               (FONTDEFHEIGHT * 10 / 8 * 2)
#define SWND_ROWHEIGHT              (FONTDEFHEIGHT * 10 / 8)
#define SWND_LEFTEDGE               52
#define SWND_TOPEDGE                153
#define SWND_WIDTH                  SWND_COLWIDTH * SWND_COLUMNS
#define SWND_KEYS_HEIGHT            SWND_ROWHEIGHT * SWND_ROWS
#define SWND_BORDER_HEIGHT          25
#define SWND_HEIGHT                 SWND_KEYS_HEIGHT + 2 * SWND_BORDER_HEIGHT
#define SWND_BKGNDCOLOR             LIGHTGRAY
#define SWND_BORDER_COLOR           DARKGRAY

// SWND arrow bitmaps
#define SWND_UPBITMAP_NAME          TEXT("SWND_UPBITMAP")
#define SWND_DOWNBITMAP_NAME        TEXT("SWND_DOWNBITMAP")
#define SWND_BITMAP_WIDTH           SWND_WIDTH
#define SWND_BITMAP_HEIGHT          SWND_BORDER_HEIGHT

#define SWNDKEY_SHADOW_THICKNESS    2
#define SWNDKEY_FILL_COLOR          LIGHTGRAY
#define SWNDKEY_SHADOW_LIGHT_COLOR  WHITE
#define SWNDKEY_SHADOW_DARK_COLOR   DARKGRAY
#define SWNDKEY_BORDER_COLOR        BLACK
#define SWNDKEY_TEXT_COLOR          RGB(0,0,0) // Black


// SWND.CXX
BOOL
SWNDCreate
    (
    void
    );
void
SWNDUpdateFocusRect
    (
    WORD                    iKeyTop
    );
BOOL 
SWNDCreateWindow 
    (
    void
    );
void
SWNDDestroy
    (
    void
    );
WORD
SWNDFindKeyUnderCursor
    (
    void
    );
void
SWNDBlt
    (
    LPDIRECTDRAWSURFACE lpDDSBack
    );


extern SWNDKEY              *g_pskCurrentSWND;
extern WORD                 g_cCurrentSWNDKeys;
extern WORD                 g_xSWNDCursor;
extern WORD                 g_ySWNDCursor;
extern WORD                 g_iSWNDFocus;
extern LPDIRECTDRAWSURFACE  g_lpddsSWND;
extern WORD                 g_cCurrentSWNDKeys;


#endif  // SWND_H
