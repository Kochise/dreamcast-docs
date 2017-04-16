/*==========================================================================
 *
 *  Copyright (C) 1995 Microsoft Corporation. All Rights Reserved.
 *
 *  File:       draw.h
 *  Content:    Include file for draw.cpp -- DirectDraw routines
 *
 ***************************************************************************/

#include <ddraw.h>

IDirectDrawPalette * DDLoadPalette(IDirectDraw *pdd, LPCSTR szBitmap);
IDirectDrawSurface * DDLoadBitmap(IDirectDraw *pdd, LPCSTR szBitmap, int dx, int dy);
HRESULT              DDReLoadBitmap(IDirectDrawSurface *pdds, LPCSTR szBitmap);
HRESULT              DDCopyBitmap(IDirectDrawSurface *pdds, HBITMAP hbm, int x, int y, int dx, int dy);
DWORD                DDColorMatch(IDirectDrawSurface *pdds, COLORREF rgb);
HRESULT              DDSetColorKey(IDirectDrawSurface *pdds, COLORREF rgb);
BOOL     InitGraphics(HWND hwnd);
void     CleanupGraphics(void);
BOOL     UpdateScreen(HWND hwnd);
HRESULT  PutSprite(int, int, int);
void     EraseSprite(int, int);
void     EraseAllSprites(void);


#define BM_AHAB    0
#define BM_MOBY    1
#define BM_SPOUT   2
#define BM_WAKE    3
#define NUMSPRITES BM_WAKE + 1

#define SPRITE_HT      20        // height of sprites in pixels
#define SPRITE_WD      32        // width of sprites in pixels


