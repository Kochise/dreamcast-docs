/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1998 Microsoft Corporation

Module Name:

    readwnd.h

Abstract:

    Header file for readwnd.cxx, which manages the reading string window (RWND).

Environment:

    Runs on Dreamcast under Windows CE.

-------------------------------------------------------------------*/

#ifndef _READWND_H
#define _READWND_H

#include <windows.h>
#include <ddraw.h>
#include "cmndefs.h"

#define RWND_MAXREADING             4

#define RWND_MARGIN                 3
#define RWND_WIDTH                  DEFAULT_FONTSIZE * RWND_MAXREADING + RWND_MARGIN * 2
#define RWND_HEIGHT                 DEFAULT_FONTSIZE + RWND_MARGIN * 2
#define RWND_TOPEDGE                EDITBOX_TOPEDGE + EDITBOX_HEIGHT + 2
#define RWND_BKGNDCOLOR             LIGHTGRAY
#define RWND_BKGNDINCORRECT         GRAY


extern BOOL                 g_bRWNDactive;
extern WORD                 g_wRWNDXCoord;
extern LPDIRECTDRAWSURFACE  g_lpddsRWND;

// READWND.CPP
BOOL RWNDCreate(void);

BOOL RWNDCreateWindow(void);

void RWNDDestroy(void);

void RWNDBlt(LPDIRECTDRAWSURFACE lpDDSBack);

void RWNDUpdateStr(void);

void RWNDCleanStr(void);

void RWNDIncorrectInput(void);


#endif  // _READWND_H
