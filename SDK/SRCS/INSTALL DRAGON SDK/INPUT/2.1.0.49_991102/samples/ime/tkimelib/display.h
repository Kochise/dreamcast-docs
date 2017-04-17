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


#ifndef DISPLAY_H
#define DISPLAY_H

#include "tchar.h"
#include "windows.h"
#include "ddraw.h"
#include "generic.h"

typedef enum {LEFT_JUSTIFY, CENTER_JUSTIFY} JUSTIFY;

// in direct input, a button has value 0x80 if it is pressed
#define BUTTON_ON   0x80

extern      HFONT               g_hfontKana;

// software keyboard key
typedef struct _SOFTKEY
{
    BYTE            xGridLocation;
    BYTE            yGridLocation;
    BYTE            dxColumns;
    BYTE            dyRows;
    TCHAR           szKeyString[MAX_CHARS_ON_KEY + 1];
	UINT			vkCode;
} SOFTKEY;

// IME key
typedef struct _IMEKEY
{
    BYTE            xGridLocation;
    BYTE            yGridLocation;
    BYTE            dxColumns;
    BYTE            dyRows;
    TCHAR           szKeyString[MAX_CHARS_ON_KEY + 1];
} IMEKEY;

// KWND key
typedef struct _KWNDKEY
{
    BYTE            xGridLocation;
    BYTE            yGridLocation;
    BYTE            dxColumns;
    BYTE            dyRows;
    TCHAR           szKeyString[MAX_CHARS_ON_KEY + 1];
} KWNDKEY;

// SWND key
typedef struct _SWNDKEY
{
    BYTE            xGridLocation;
    BYTE            yGridLocation;
    BYTE            dxColumns;
    BYTE            dyRows;
    TCHAR           szKeyString[MAX_CHARS_ON_KEY + 1];
} SWNDKEY;

// DISPLAY.CXX
BOOL
DDrawFillRect (
    LPDIRECTDRAWSURFACE    pdds,
    DWORD                   dwX,
    DWORD                   dwY,
    DWORD                   dwWidth,
    DWORD                   dwHeight,
    DWORD                   dwColor
    );

BOOL
DDrawOutlineRect (
    LPDIRECTDRAWSURFACE    pdds,
    DWORD                   dwX,
    DWORD                   dwY,
    DWORD                   dwWidth,
    DWORD                   dwHeight,
    DWORD                   dwColor
    );

BOOL
RenderCharacters 
    (
    LPDIRECTDRAWSURFACE        pddsTarget,
    TCHAR                       *wc,
    WORD                        xKeyLeftEdge, 
    WORD                        yKeyTopEdge, 
    WORD                        dxKeyWidth,
    WORD                        dyKeyHeight,
    JUSTIFY                     eCenter,
    HFONT                       hfontSpecify
    );

BOOL
RenderFocusRing
    (
    LPDIRECTDRAWSURFACE        pddsTarget,
    WORD                        xKeyLeftEdge, 
    WORD                        yKeyTopEdge, 
    WORD                        dxKeyWidth,
    WORD                        dyKeyHeight,
    WORD                        dwKeyBorderColor
    );

BOOL
RenderBlankKey
    (
    LPDIRECTDRAWSURFACE        pddsTarget,
    WORD                        xLeftEdge,
    WORD                        yTopEdge,
    WORD                        dxWidth,
    WORD                        dyHeight
    );

BOOL
CreateKanaFont
    (
    void
    );
void
DestroyKanaFont
    (
    void
    );

#endif      // DISPLAY_H
