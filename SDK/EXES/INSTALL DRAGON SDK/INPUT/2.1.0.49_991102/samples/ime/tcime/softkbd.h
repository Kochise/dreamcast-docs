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

#ifndef _SOFTKBD_H
#define _SOFTKBD_H


// soft keyboard specs
// these specs go in generic.h because each window uses the same font, which 
// is based in part on the size of an SKB key.  all other window specs appear in 
// the main header file for each window.
#define SKB_BORDER_THICKNESS    4
#define SKB_BKGNDCOLOR          BLACK

#define SKB_COLWIDTH            (DEFAULT_FONTSIZE * 10 / 8)
#define SKB_ROWHEIGHT           (DEFAULT_FONTSIZE * 10 / 8)

#define SKB_PHON_COLUMNS        15
#define SKB_PHON_ROWS           5
#define SKB_PHON_WIDTH          (SKB_COLWIDTH * SKB_PHON_COLUMNS + 2 * SKB_BORDER_THICKNESS)
#define SKB_PHON_HEIGHT         (SKB_ROWHEIGHT* SKB_PHON_ROWS + 2 * SKB_BORDER_THICKNESS)
#define SKB_PHON_LEFTEDGE       ((640 - SKB_PHON_WIDTH) / 2)
#define SKB_PHON_TOPEDGE        260

#define SKB_ENG_COLUMNS         18
#define SKB_ENG_ROWS            5
#define SKB_ENG_WIDTH           (SKB_COLWIDTH * SKB_ENG_COLUMNS + 2 * SKB_BORDER_THICKNESS)
#define SKB_ENG_HEIGHT          (SKB_ROWHEIGHT* SKB_ENG_ROWS + 2 * SKB_BORDER_THICKNESS)
#define SKB_ENG_LEFTEDGE        ((640 - SKB_ENG_WIDTH) / 2)
#define SKB_ENG_TOPEDGE         260

#define SKB_SYM_COLUMNS         17
#define SKB_SYM_ROWS            5
#define SKB_SYM_WIDTH           (SKB_COLWIDTH * SKB_SYM_COLUMNS + 2 * SKB_BORDER_THICKNESS)
#define SKB_SYM_HEIGHT          (SKB_ROWHEIGHT * SKB_SYM_ROWS + 2 * SKB_BORDER_THICKNESS)
#define SKB_SYM_LEFTEDGE        ((640 - SKB_SYM_WIDTH) / 2)
#define SKB_SYM_TOPEDGE         260

#define SKB_WIDTH               max(max(SKB_PHON_WIDTH, SKB_ENG_WIDTH), SKB_SYM_WIDTH)
#define SKB_HEIGHT              max(max(SKB_PHON_HEIGHT, SKB_ENG_HEIGHT), SKB_SYM_HEIGHT)


extern HWND                 g_hwndSKB;
extern RECT                 g_rcSKB;
extern WORD                 g_uSKBColumns;
extern WORD                 g_uSKBRows;
extern SOFTKEY*             g_pskCurrentSKB;
extern WORD                 g_cCurrentSKBKeys;
extern WORD                 g_uFocusSKBKey;
extern WORD                 g_xSKBCursor;
extern WORD                 g_ySKBCursor;
extern LPDIRECTDRAWSURFACE  g_lpddsSKB;


// SOFTKBD.CPP
BOOL SKBCreate(KBDLAYOUT kbdInitial);

BOOL SKBCreateWindow(void);

void SKBDestroy(void);

void SKBSetLayout(KBDLAYOUT);

void SKBUpdate(void);

WORD SKBFindKeyUnderCursor(void);

void SKBUpdateFocusRect(void);

void SKBBlt(LPDIRECTDRAWSURFACE lpDDSBack);

#endif  // _SOFTKBD_H
