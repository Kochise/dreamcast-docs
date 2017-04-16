// COPYRIGHT:
//
//   (C) Copyright Microsoft Corp. 1993.  All rights reserved.
//
//   You have a royalty-free right to use, modify, reproduce and
//   distribute the Sample Files (and/or any modified version) in
//   any way you find useful, provided that you agree that
//   Microsoft has no warranty obligations or liability for any
//   Sample Application Files which are modified.

#include "zusammen.h"
/*
This file contains the non-Zusammen specific message handlers.
It contains the Client_WndProc Entry point.
*/

LRESULT ENTRY Client_WndProc (HWND hwnd, UINT msg, 
										WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
        HANDLE_MSG(hwnd, WM_CREATE, zu_OnCreate);

        HANDLE_MSG(hwnd, WM_PAINT, zu_OnPaint);
        HANDLE_MSG(hwnd, WM_ERASEBKGND, Client_OnEraseBkgnd);

        HANDLE_MSG(hwnd, WM_COMMAND, zu_OnCommand);
		  
		  HANDLE_MSG(hwnd, WM_HSCROLL, zu_OnHScroll);
  		  HANDLE_MSG(hwnd, WM_VSCROLL, zu_OnVScroll);
		  
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
}

BOOL GLOBAL Client_OnEraseBkgnd (HWND hwnd, HDC hdc)
{
    // Let DefWindowProc erase the background
    //
    return FORWARD_WM_ERASEBKGND(hwnd, hdc, DefWindowProc);
}
