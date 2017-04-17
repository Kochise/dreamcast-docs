/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1998 Microsoft Corporation

Module Name:

    generic.h

Abstract:

    This file contains common color and dimension definitions.

Environment:

    Runs on Dreamcast under Windows CE.

-------------------------------------------------------------------*/


#ifndef GENERIC_H
#define GENERIC_H


#include "tchar.h"
#include "stdlib.h"
#include "winuser.h"

#ifndef UNDER_CE
#error \
This sample cannot be built for Win95.  If you are building this \
sample from within the DevStudio IDE, please select 'Win32 (WCE SH4)' \
from the WCE Configuration listbox, and then try building again.
#endif

        // Going from 888 RGB:
        //                    --------BBBBBBBBGGGGGGGGRRRRRRRR
        // to 565 RGB:
        //                    ----------------RRRRRGGGGGGBBBBB
#define COLORREF_TO_565(rgb)                \
            ((WORD) (                       \
            (((rgb) & 0x00f80000) >> 19) |  \
            (((rgb) & 0x0000fc00) >> 5) |   \
            (((rgb) & 0x000000f8) << 8)))   \

        // Going from 888 RGB:
        //                    --------BBBBBBBBGGGGGGGGRRRRRRRR
        // to 555 RGB:
        //                    -----------------RRRRRGGGGGBBBBB
#define COLORREF_TO_555(rgb)                \
            ((WORD) (                       \
            (((rgb) & 0x00f80000) >> 19) |  \
            (((rgb) & 0x0000f800) >> 6) |   \
            (((rgb) & 0x000000f8) << 7)))   \

#define g_fPrimarySurface555    0

#define COLORREF_TO_16BPP(rgb)              \
            (g_fPrimarySurface555 ?         \
            COLORREF_TO_555(rgb) :          \
            COLORREF_TO_565(rgb))

#define BLUE                            COLORREF_TO_16BPP(RGB(   0,   0, 255))
#define DARKBLUE                        COLORREF_TO_16BPP(RGB(   0,   0, 128))
#define RED                             COLORREF_TO_16BPP(RGB( 255,   0,   0))
#define DARKRED                         COLORREF_TO_16BPP(RGB( 128,   0,   0))
#define GREEN                           COLORREF_TO_16BPP(RGB(   0, 255,   0))
#define DARKGREEN                       COLORREF_TO_16BPP(RGB(   0, 128,   0))
#define BLACK                           COLORREF_TO_16BPP(RGB(   0,   0,   0))
#define DARKGRAY                        COLORREF_TO_16BPP(RGB(  80,  80,  80))
#define LIGHTGRAY                       COLORREF_TO_16BPP(RGB( 192, 192, 192))
#define WHITE                           COLORREF_TO_16BPP(RGB( 255, 255, 255))


// currently all of the windows use the same font
#define FONTFILENAME                TEXT("\\Windows\\msgot.ttf")
#define FONTFACENAME                TEXT("MS Gothic")
#define FONTDEFHEIGHT               24

#define KEY_SHADOW_THICKNESS        2
#define KEY_FILL_COLOR              LIGHTGRAY
#define KEY_SHADOW_LIGHT_COLOR      WHITE
#define KEY_SHADOW_DARK_COLOR       DARKGRAY
#define KEY_BORDER_COLOR            BLUE
#define KEY_TEXT_COLOR              RGB(0,0,0) // Black

#define MAX_CHARS_ON_KEY            80

// soft keyboard specs
// these specs go in generic.h because each window uses the same font, which 
// is based in part on the size of an SKB key.  all other window specs appear in 
// the main header file for each window.
#define SKB_BORDERTHICKNESS         4
#define SKB_COLWIDTH                (FONTDEFHEIGHT * 10 / 8)
#define SKB_ROWHEIGHT               (FONTDEFHEIGHT * 10 / 8)
#define SKB_COLUMNS                 18
#define SKB_ROWS                    6
#define SKB_WIDTH                   (SKB_COLWIDTH * SKB_COLUMNS + 2 * SKB_BORDERTHICKNESS)
#define SKB_HEIGHT                  (SKB_ROWHEIGHT * SKB_ROWS + 2 * SKB_BORDERTHICKNESS)
#define SKB_LEFTEDGE                45
#define SKB_TOPEDGE                 200
#define SKB_BKGNDCOLOR              BLACK

typedef enum _KBDLAYOUT
{
    HIRAGANA = 0,
    KATAKANA,
    ROMANJI
} KBDLAYOUT;

#endif
