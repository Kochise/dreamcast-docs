#ifndef WINPROC_H
#define WINPROC_H
/*
**-----------------------------------------------------------------------------
**  File:       WinProc.h
**  Purpose:    Sample Window Procedure code
**  Notes:
**
**  Copyright (c) 1995 - 1997 by Microsoft, all rights reserved
**-----------------------------------------------------------------------------
*/

/*
**-----------------------------------------------------------------------------
**  Include files
**-----------------------------------------------------------------------------
*/

#include "Common.h"
#include "D3DWin.h"


/*
**-----------------------------------------------------------------------------
**  Function Prototypes
**-----------------------------------------------------------------------------
*/

// Windows routines
LRESULT CALLBACK D3DWindowProc (HWND hWindow, UINT uiMessage,
                                WPARAM wParam, LPARAM lParam);


// Window Message helper routines
LRESULT OnAbout (HWND hWindow);
LRESULT OnActivateApp (HWND hWindow, WPARAM wParam, LPARAM lParam);
LRESULT OnClose (HWND hWindow);
LRESULT OnCommand (HWND hWindow, WPARAM wParam, LPARAM lParam);
LRESULT OnCreate (HWND hWindow);
LRESULT OnDestroy (HWND hWindow);
LRESULT OnDisplayChange (HWND hWindow);
LRESULT OnEraseBackground (HWND hWindow, WPARAM wParam, LPARAM lParam);
LRESULT OnGetMinMaxInfo (HWND hWindow, LPMINMAXINFO lpmmi);
void    OnIdle (HWND hWindow);
LRESULT OnMove (HWND hWindow, INT nX, INT nY);
void    OnPause (HWND hWindow, BOOL fPause);
LRESULT OnPaint (HWND hWindow, HDC hdc, LPPAINTSTRUCT lpps);
LRESULT OnSize (HWND hWindow, INT nW, INT nH);

// D3D Notification routines
LRESULT	OnD3DInit (HWND hWindow, LPD3DWindow lpd3dWindow);
LRESULT	OnD3DFini (HWND hWindow, LPD3DWindow lpd3dWindow);
LRESULT	OnD3DChangeDriver (HWND hWindow);
LRESULT	OnD3DChangeMode (HWND hWindow);
LRESULT	OnD3DChangeDevice (HWND hWindow);

// Misc Routines
void    PaintPaused (HWND hWindow, HDC hdc);



/*
**-----------------------------------------------------------------------------
**  End of File
**-----------------------------------------------------------------------------
*/
#endif // End WINPROC_H


