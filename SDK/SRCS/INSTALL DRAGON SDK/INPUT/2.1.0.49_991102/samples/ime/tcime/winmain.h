
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1998 Microsoft Corporation

Module Name:

    winmain.h

Abstract:

    The main header file for gtest.exe.

Environment:

    Runs on WinCE/Dragon only, due to MAPLUSAG.

-------------------------------------------------------------------*/


#ifndef _WINMAIN_H
#define _WINMAIN_H

extern HINSTANCE            g_hInstance;
extern HWND                 g_hwndAPP;
extern RECT                 g_rcDesktop;
extern HFONT                g_hfontDefault;
extern LPDIRECTDRAW         g_lpdd;

extern LPDIRECTINPUTDEVICE2 g_pdidevice2JoystickApp;

HFONT CreateChineseFont(LONG lFontHeight);

#endif  // _WINMAIN_H
