/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1998 Microsoft Corporation

Module Name:

    cmndefs.h

Abstract:

    The common defines for this program

Environment:

    Runs on WinCE/Dragon only, due to MAPLUSAG.

-------------------------------------------------------------------*/

#ifndef _COMMON_DEFS_H
#define _COMMON_DEFS_H

#define DEFAULT_CODEPAGE    950

#define FONT_FILENAME       TEXT("\\Windows\\msming.ttf")
#define FONT_FACENAME       TEXT("MS Ming")

#define DEFAULT_FONTSIZE    24


// Going from 888 RGB:
//                    --------BBBBBBBBGGGGGGGGRRRRRRRR
// to 565 RGB:
//                    ----------------RRRRRGGGGGGBBBBB
#define COLORREF_TO_565(rgb)        ((WORD) (                      \
                                    (((rgb) & 0x00f80000) >> 19) | \
                                    (((rgb) & 0x0000fc00) >> 5) |  \
                                    (((rgb) & 0x000000f8) << 8)))  \

// Going from 888 RGB:
//                    --------BBBBBBBBGGGGGGGGRRRRRRRR
// to 555 RGB:
//                    -----------------RRRRRGGGGGBBBBB
#define COLORREF_TO_555(rgb)        ((WORD) (                      \
                                    (((rgb) & 0x00f80000) >> 19) | \
                                    (((rgb) & 0x0000f800) >> 6) |  \
                                    (((rgb) & 0x000000f8) << 7)))  \

#define g_fPrimarySurface555        0

#define COLORREF_TO_16BPP(rgb)      (g_fPrimarySurface555 ?        \
                                    COLORREF_TO_555(rgb) :         \
                                    COLORREF_TO_565(rgb))

#define BLUE                        COLORREF_TO_16BPP(RGB(   0,   0, 255))
#define DARKBLUE                    COLORREF_TO_16BPP(RGB(   0,   0, 128))
#define RED                         COLORREF_TO_16BPP(RGB( 255,   0,   0))
#define DARKRED                     COLORREF_TO_16BPP(RGB( 128,   0,   0))
#define GREEN                       COLORREF_TO_16BPP(RGB(   0, 255,   0))
#define DARKGREEN                   COLORREF_TO_16BPP(RGB(   0, 128,   0))
#define BLACK                       COLORREF_TO_16BPP(RGB(   0,   0,   0))
#define DARKGRAY                    COLORREF_TO_16BPP(RGB(  80,  80,  80))
#define GRAY                        COLORREF_TO_16BPP(RGB( 128, 128, 128))
#define LIGHTGRAY                   COLORREF_TO_16BPP(RGB( 192, 192, 192))
#define WHITE                       COLORREF_TO_16BPP(RGB( 255, 255, 255))

#define KEY_SHADOW_THICKNESS        2
#define KEY_FILL_COLOR              LIGHTGRAY
#define KEY_SHADOW_LIGHT_COLOR      WHITE
#define KEY_SHADOW_DARK_COLOR       DARKGRAY
#define KEY_BORDER_COLOR            BLUE
#define KEY_TEXT_COLOR              RGB(0,0,0) // Black


#define MAX_CHARS_ON_KEY            8


typedef enum _KBDLAYOUT
{
    PHONETIC = 0,
    ROMANJI,
    SYMBOLS,
    HARDWARE
} KBDLAYOUT;


typedef struct _KeyboardState
{
    KBDLAYOUT   keyboard;
    BOOL        fIMEOn;
    BOOL        fCapsOn;        // For HARDWARE and ROMANJI only
    BOOL        fDoubleWidth;   // For HARDWARE and ROMANJI only
} KeyboardState;


typedef enum {LEFT_JUSTIFY, CENTER_JUSTIFY} JUSTIFY;


// software keyboard key
typedef struct _SOFTKEY
{
    BYTE        xGridLocation;
    BYTE        yGridLocation;
    BYTE        dxColumns;
    BYTE        dyRows;
    TCHAR       szKeyString[MAX_CHARS_ON_KEY + 1];
	UINT		vkCode;
} SOFTKEY;

// CWND key
typedef struct _CWNDKEY
{
    BYTE        xGridLocation;
    BYTE        yGridLocation;
    BYTE        dxColumns;
    BYTE        dyRows;
    TCHAR       szKeyString[MAX_CHARS_ON_KEY + 1];
} CWNDKEY;

#endif  // _COMMON_DEFS_H
