
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1998 Microsoft Corporation

Module Name:

    symbols.h

Abstract:

    This file contains definitions of symbols which appear on the keyboard.

Environment:

    Runs on Dreamcast under Windows CE.

-------------------------------------------------------------------*/

#ifndef _SYMBOLS_H
#define _SYMBOLS_H

#include <tchar.h>

extern WORD g_cSpecialKeys;
extern TCHAR g_rgcSpecialKeys[];

//  The following characters are for the special symbols on the keyboard.

//      SYMBOL                           UNICODE VALUE
//      ------------                ----------------------

#define SYMBOLS_YEN_HW                      0x005c
#define SYMBOLS_YEN                         0xffe5

// grammatical symbols
#define SYMBOLS_JAPANESE_LEFT_PAREN_HW      0xff62
#define SYMBOLS_JAPANESE_LEFT_PAREN         0x300c
#define SYMBOLS_JAPANESE_RIGHT_PAREN_HW     0xff63
#define SYMBOLS_JAPANESE_RIGHT_PAREN        0x300d
#define SYMBOLS_AMPERSAND                   0x0026
#define SYMBOLS_DAKUTEN                     0x309b
#define SYMBOLS_HANDAKUTEN                  0x309c
#define SYMBOLS_HW_DAKUTEN                  0xff9e
#define SYMBOLS_HW_HANDAKUTEN               0xff9f
#define SYMBOLS_IDEO_COMMA_HW               0xff64
#define SYMBOLS_IDEO_COMMA                  0x3001
#define SYMBOLS_IDEO_PERIOD_HW              0xff61
#define SYMBOLS_IDEO_PERIOD                 0x3002
#define SYMBOLS_ROMAN_LEFT_PAREN            0x0028
#define SYMBOLS_ROMAN_RIGHT_PAREN           0x0029
#define SYMBOLS_EXCLAMATION                 0x0021
#define SYMBOLS_QUESTION                    0x003f  
#define SYMBOLS_LOWLINE                     0xff3f
#define SYMBOLS_EMDASH                      0x002d
#define SYMBOLS_PERCENT                     0x0025
#define SYMBOLS_JAPANESE_DASH               0x30fc
#define SYMBOLS_FW_PERIOD                   0xff0e
#define SYMBOLS_FW_COMMA                    0xff0c
#define SYMBOLS_FW_DASH                     0xff0d
#define SYMBOLS_FW_BACKSLASH                0xff3c

// symbols from roman keyboard
#define SYMBOLS_DOLLAR_SIGN                 0x0024
#define SYMBOLS_CIRCUMFLEX                  0x005e
#define SYMBOLS_ASTERISK                    0x002a
#define SYMBOLS_SEMICOLON                   0x003b
#define SYMBOLS_SINGLE_QUOTE                0x0027
#define SYMBOLS_DOUBLE_QUOTE                0x0022
#define SYMBOLS_LESSTHAN                    0x003c
#define SYMBOLS_GREATERTHAN                 0x003e
#define SYMBOLS_VERTICAL_LINE               0x007c
#define SYMBOLS_LEFT_CURLY                  0x007b
#define SYMBOLS_RIGHT_CURLY                 0x007d
#define SYMBOLS_AT                          0x0040
#define SYMBOLS_LEFT_BRACKET                0x005b
#define SYMBOLS_RIGHT_BRACKET               0x005d
#define SYMBOLS_ROMAN_COMMA                 0x002c
#define SYMBOLS_ROMAN_PERIOD                0x002e
#define SYMBOLS_GRAVE_ACCENT                0x0060
    

// arrows
#define SYMBOLS_LEFT                        0x2190
#define SYMBOLS_UP                          0x2191
#define SYMBOLS_RIGHT                       0x2192
#define SYMBOLS_DOWN                        0x2193

// special signals
// #define REJECT                              0x9999
#define OUTWND_CLEAR                        0x9998



#endif  // _SYMBOLS_H
