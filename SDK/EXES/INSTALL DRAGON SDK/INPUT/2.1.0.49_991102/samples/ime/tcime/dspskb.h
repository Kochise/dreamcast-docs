/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1998 Microsoft Corporation

Module Name:

    dspskb.h

Abstract:

    This is the header file for dspskb.cpp, which displays the software
    keyboard (SKB).

Environment:

    Runs on Dreamcast under Windows CE.

-------------------------------------------------------------------*/


#ifndef _DISPLAY_SKB_H
#define _DISPLAY_SKB_H

BOOL SKBRender(void);

BOOL SKBRenderKey(LPDIRECTDRAWSURFACE pddsTarget,
                  SOFTKEY*            psk,
                  BOOL                fFocus,
                  TCHAR*              pszTextOverride);

#endif  // _DISPLAY_SKB_H
