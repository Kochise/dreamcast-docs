/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1998 Microsoft Corporation

Module Name:

    candwnd.h

Abstract:

    Header file for kwnd.cxx, which manages the candidate selection window (CWND).

Environment:

    Runs on Dreamcast under Windows CE.

-------------------------------------------------------------------*/

#ifndef _CANDWND_H
#define _CANDWND_H

#include <windows.h>
#include <ddraw.h>
#include "cmndefs.h"
#include "dspcwd.h"
#include "inputcwd.h"

#define CWND_FONTSIZE               28

#define CWND_BORDER_THICKNESS       2
#define CWND_GAP                    3

#define MAX_CAND                    180
#define CWND_ROWS                   9
#define CWND_COLUMNS                1
#define MAX_CAND_DISPLAYED          (CWND_ROWS * CWND_COLUMNS)
#define TOTAL_CWND_KEYS             (MAX_CAND + 1)

#define CWND_COLWIDTH               80
#define CWND_ROW_HEIGHT             CWND_FONTSIZE * 10 / 8
#define CWND_TOPEDGE                EDITBOX_TOPEDGE + EDITBOX_HEIGHT + 2
#define CWND_KEYS_WIDTH             CWND_COLWIDTH * CWND_COLUMNS
#define CWND_KEYS_HEIGHT            CWND_ROW_HEIGHT * CWND_ROWS
#define CWND_SCROLL_WIDTH           15
#define CWND_SCROLL_HEIGHT          CWND_KEYS_HEIGHT
#define CWND_WIDTH                  (CWND_KEYS_WIDTH + CWND_SCROLL_WIDTH + 2 * CWND_BORDER_THICKNESS)
#define CWND_HEIGHT                 (CWND_KEYS_HEIGHT + 2 * CWND_BORDER_THICKNESS)
#define CWND_KEYS_BKGNDCOLOR        LIGHTGRAY
#define CWND_SCROLL_BKGNDCOLOR      GRAY
#define CWND_BORDER_COLOR           BLACK


extern HFONT                g_hfontCWND;
extern CWNDKEY              g_pskCurrentCWND[TOTAL_CWND_KEYS];
extern WORD                 g_cCurrentCWNDKeys;
extern WORD                 g_uFocusCWNDKey;
extern WORD                 g_uTopCWNDKey;
extern WORD                 g_xCWNDCursor;
extern WORD                 g_yCWNDCursor;
extern BOOL                 g_bCWNDactive;
extern LPDIRECTDRAWSURFACE  g_lpddsCWND;


// CANDWND.CPP
BOOL CWNDCreate(void);

void CWNDUpdateFocusRect(WORD iKeyTop, WORD iCWNDNewFocus);

BOOL CWNDCreateWindow(void);

void CWNDDestroy(void);

WORD CWNDFindKeyUnderCursor(void);

BOOL CWNDGetData(void);

void CWNDGetChange(void);

void CWNDUpdate(void);

void CWNDBlt(LPDIRECTDRAWSURFACE lpDDSBack);

#endif  // _CANDWND_H
