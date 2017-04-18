/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1998 Microsoft Corporation

Module Name:

    symbols.cxx

Abstract:

    This file initializes an array of special symbols keys for the
    special symbols window.

Environment:

    Runs on Dreamcast under Windows CE.

-------------------------------------------------------------------*/


#include "precomp.hxx"


#ifdef KANJI
// This array defines the layout for the Hiragana software keyboard.
// Keys must be listed in sorted order by location on keyboard, 
// left to right, and then top to bottom.  The binary search 
// is dependent on this sort order.
TCHAR g_rgcSpecialKeys[] = 
    {
//       Special Character UNICODE
//       ----------------------------------------------------------------------------------
    0x3012, 
    0x30fd, 
    0x30fe, 
    0x309d, 
    0x309e, 
    0x3005, 
    0x3003, 
    0x3006, 
    0x3007, 

    0xffe5, 
    0xff5e,     // tilda
    0x2192, 
    0x2190, 
    0x2191, 
    0x2193, 
    0x00a7, 
    0x00b0, 
    0x2032, 

    0x2033, 
    0x2642, 
    0x2640, 
    0x2103,     // degrees centigrade
    0xff04,     // dollar
    0xffe0,     // cent
    0xffe1,     
    0xff05,     // percent
    0xff03,     // pound

    0xff06,     // ampersand
    0xff0a,     // asterisk
    0xff20,     // at
    0x266f, 
    0x266d, 
    0x266a, 
    0x2020, 
    0x2021, 
    0x222b, 

    0x222c, 
    0x21d2, 
    0x21d4, 
    0x203b, 
    0x25c7, 
    0x25c6, 
    0x25a1, 
    0x25a0, 
    0x25cb,

    0x25cf, 
    0x2606, 
    0x2605, 
    0x25b3, 
    0x25b2, 
    0x25bd, 
    0x25bc, 
    0x25ce, 
    0xff0b, 

    0xff0d, 
    0x00b1, 
    0x00d7, 
    0x00f7, 
    0xff1d, 
    0x2260, 
    0x221e, 
    0xff1c, 
    0xff1e, 

    0xff0c, 
    0xff0e, 
    0xff1a, 
    0xff1b, 
    0xff1f, 
    0xff01, 
    0xff40, 
    0x00a8, 
    0xff3e, 

    0xffe3,     // long overline
    0xff3f,     // long underline
    0x30fc,     // long dash
    0x2015,     // long dash
    0x2010,     // short dash
    0xff0f,     // forward slash
    0xff3c,     // backslash
    0x2225,     // double vertical bar
    0xff5c,     // single vertical bar

    0x2026, 
    0x2025, 
    0x2018, 
    0x2019, 
    0x201c, 
    0x201d, 
    0xff08, 
    0xff09, 
    0x3014, 

    0x3015, 
    0xff3b, 
    0xff3d, 
    0x3010, 
    0x3011, 
    0xff5b, 
    0xff5d, 
    0x3008,     // left angle bracket
    0x3009,     // right angle bracket

    0x300a,     // outlined left angle bracket
    0x300b,     // outlined right angle bracket
    0x300e,     // japanese outlined left quote
    0x300f,     // japanese outlined right quote
    0x3090, 
    0x3091, 
    0x30cc, 
    0x30f0, 
    0x30f1, 

    0x30f2, 
    0x30f4, 
    0xff61, 
    0xff62, 
    0xff63, 
    0xff64, 
    0xff66, 
    0xff70, 
    0xff91, 

    0x4edd,
    0x00b6,
    0x00b4
};
WORD g_cSpecialKeys = sizeof(g_rgcSpecialKeys) / sizeof(TCHAR);  // number of symbols in window
#endif
