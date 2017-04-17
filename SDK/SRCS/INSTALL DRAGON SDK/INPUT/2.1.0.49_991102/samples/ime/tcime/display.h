/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1998 Microsoft Corporation

Module Name:

    display.h

Abstract:

    This file contains prototypes for the DDraw-related functions
    exported by display.cxx.

Environment:

    Runs on Dreamcast under Windows CE.

-------------------------------------------------------------------*/


#ifndef _DISPLAY_H
#define _DISPLAY_H

BOOL DDrawFillRect(LPDIRECTDRAWSURFACE pdds,
                   DWORD               dwX,
                   DWORD               dwY,
                   DWORD               dwWidth,
                   DWORD               dwHeight,
                   DWORD               dwColor);

BOOL DDrawOutlineRect(LPDIRECTDRAWSURFACE pdds,
                      DWORD               dwX,
                      DWORD               dwY,
                      DWORD               dwWidth,
                      DWORD               dwHeight,
                      DWORD               dwColor);

BOOL RenderCharacters(LPDIRECTDRAWSURFACE pddsTarget,
                      TCHAR              *wc,
                      WORD                xKeyLeftEdge,
                      WORD                yKeyTopEdge,
                      WORD                dxKeyWidth,
                      WORD                dyKeyHeight,
                      JUSTIFY             eCenter,
                      HFONT               hfontSpecify);

BOOL RenderFocusRing(LPDIRECTDRAWSURFACE pddsTarget,
                     WORD                xKeyLeftEdge,
                     WORD                yKeyTopEdge,
                     WORD                dxKeyWidth,
                     WORD                dyKeyHeight,
                     WORD                dwKeyBorderColor);

BOOL RenderBlankKey(LPDIRECTDRAWSURFACE pddsTarget,
                    WORD                xLeftEdge,
                    WORD                yTopEdge,
                    WORD                dxWidth,
                    WORD                dyHeight);

#endif      // _DISPLAY_H
