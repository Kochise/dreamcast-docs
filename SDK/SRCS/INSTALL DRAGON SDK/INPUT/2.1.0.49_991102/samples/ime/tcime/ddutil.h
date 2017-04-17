/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1996-1997 Microsoft Corporation

Module Name:

    ddutil.h

Abstract:

    This contains declarations of helper routines for loading bitmaps 
    and palettes from resources.  The functions are implemented in
    ddutil.cxx

Environment:

    Dragon emulation under Windows 95.

-------------------------------------------------------------------*/

#ifndef _DDUTIL_H
#define _DDUTIL_H

#ifdef __cplusplus
extern "C" {
#endif // #ifdef __cplusplus

extern LPDIRECTDRAWSURFACE DDUtilLoadBitmap (HINSTANCE hinstApp, 
    LPDIRECTDRAW pdd, LPCTSTR szBitmap);

extern BOOL DDUtilCopyBitmap (HINSTANCE hinstApp, LPDIRECTDRAWSURFACE pddsDest, 
    LPCTSTR szBitmap, unsigned int xSrc, unsigned int ySrc, 
    unsigned int dxWidth, unsigned int dyHeight);

extern LPDIRECTDRAWPALETTE DDUtilLoadPalette (HINSTANCE hinstApp, 
    LPDIRECTDRAW pdd, LPCTSTR szBitmap);

#ifdef __cplusplus
}
#endif // #ifdef __cplusplus

#endif // _DDUTIL_H