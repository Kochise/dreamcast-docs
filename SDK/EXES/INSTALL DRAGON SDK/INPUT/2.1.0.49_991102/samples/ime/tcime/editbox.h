
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1998 Microsoft Corporation

Module Name:

    editbox.h

Abstract:

    The header file for edit box

Environment:

    Runs on WinCE/Dragon only, due to MAPLUSAG.

-------------------------------------------------------------------*/

#ifndef _EDITBOX_H
#define _EDITBOX_H


#define EDITBOX_MAXCHARS        255
#define EDITBOX_BLOCKCHARS      10
#define EDITBOX_FONTSIZE        28
#define EDITBOX_MARGIN          5

#define EDITBOX_LEFTEDGE        40
#define EDITBOX_TOPEDGE         INDICATOR_TOPEDGE + INDICATOR_HEIGHT + 8
#define EDITBOX_WIDTH           560
#define EDITBOX_HEIGHT          EDITBOX_FONTSIZE + EDITBOX_MARGIN * 2
#define EDITBOX_CLIENTWIDTH     EDITBOX_WIDTH - EDITBOX_MARGIN * 2
#define EDITBOX_BKGNDCOLOR      LIGHTGRAY

#define CARET_WIDTH             2


extern HWND                     g_hwndEditBox;
extern WORD                     g_wCaretXCoord;


void EditBoxCreate(void);
void EditBoxDestroy(void);
void EditBoxBlt(LPDIRECTDRAWSURFACE lpDDSBack);

void CaretBlt(LPDIRECTDRAWSURFACE lpDDSBack);

#endif  // _EDITBOX_H
