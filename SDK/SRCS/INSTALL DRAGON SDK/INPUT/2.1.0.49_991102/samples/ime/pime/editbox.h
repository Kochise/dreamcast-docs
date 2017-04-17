/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1998 Microsoft Corporation

Module Name:

    editbox.h

Abstract:

    This file contains the prototypes of functions in editbox.cxx, which
    manages the output window.

Environment:

    Runs on Dreamcast under Windows CE.

-------------------------------------------------------------------*/

#ifndef EDITBOX_H
#define EDITBOX_H


#include "windows.h"
#include "ddraw.h"
#include "symbols.h"


#define EDITBOX_FONTHEIGHT              28
 
#define EDITBOX_MARGIN                  (EDITBOX_FONTHEIGHT / 8 + 3)
#define EDITBOX_LEFTEDGE                40
#define EDITBOX_TOPEDGE                 85
#define EDITBOX_WIDTH                   560
#define EDITBOX_HEIGHT                  (EDITBOX_FONTHEIGHT + 2 * EDITBOX_MARGIN)
#define EDITBOX_BKGNDCOLOR              LIGHTGRAY
#define EDITBOX_MAXCHARS                160

#define OUTWNDKEY_SHADOW_THICKNESS      2
#define OUTWNDKEY_FILL_COLOR            LIGHTGRAY
#define OUTWNDKEY_SHADOW_LIGHT_COLOR    WHITE
#define OUTWNDKEY_SHADOW_DARK_COLOR     DARKGRAY
#define OUTWNDKEY_BORDER_COLOR          BLACK
#define OUTWNDKEY_TEXT_COLOR            RGB(0,0,0) // Black


// EDITBOX.CXX
BOOL
EditBoxCreate
    (
    );
void
AddNonConvertedCharacter 
    (
    WPARAM          wParam
    );
LRESULT CALLBACK 
EditBoxWindowProc
    (
    HWND            hwnd,       // handle to window
    UINT            uMsg,       // message identifier
    WPARAM          wParam,     // first message parameter
    LPARAM          lParam      // second message parameter
    );
BOOL 
EditBoxCreateWindow 
    (
    void
    );
void 
EditBoxProcessKey
    (
    TCHAR wcKey
    );
void
EditBoxDestroy
    (
    void
    );
void
EditBoxBlt
    (
    LPDIRECTDRAWSURFACE lpDDSBack
    );
void
CaretBlt
    (
    LPDIRECTDRAWSURFACE lpDDSBack
    );
BOOL
EditBoxRender
    (
    void
    );


extern LPDIRECTDRAWSURFACE g_lpddsEditBox;                      // editbox's offscreen surface
extern HWND                g_hwndEditBox;                       // editbox's window handle
extern WCHAR               g_wszConverted[EDITBOX_MAXCHARS + 1];
extern WCHAR               g_wszNonConverted[EDITBOX_MAXCHARS + 1];
extern BOOL                g_fConverting;
extern WORD                g_xCandidateList;
extern WORD                g_dxCandidateListWidth;
extern WORD                g_caretpos;
extern WORD                g_caretxcoord;


#endif  // EDITBOX_H
