
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

//  The following characters are for the special symbols on the keyboard.

//      SYMBOL                           UNICODE VALUE
//      ------------                ----------------------

// Chinese symbols
#define SYMBOL_IDEO_COMMA                   0x3001
#define SYMBOL_IDEO_FULLSTOP                0x3002
#define SYMBOL_FW_COMMA                     0xff0c
#define SYMBOL_FW_FULLSTOP                  0xff0e
#define SYMBOL_FW_QUESTION                  0xff1f
#define SYMBOL_LOWLINE                      0xff3f
#define SYMBOL_REFERENCE                    0x203b
#define SYMBOL_WHITE_CIRCLE                 0x25cb
#define SYMBOL_BLACK_CIRCLE                 0x25cf
#define SYMBOL_FW_EXCLAMATION               0xff01
#define SYMBOL_FW_COLON                     0xff1a
#define SYMBOL_FW_SEMICOLON                 0xff1b
#define SYMBOL_BULLSEYE                     0x25ce
#define SYMBOL_SECTION                      0x00a7
#define SYMBOL_FW_REVERSE_SOLIDUS           0xff3c

#define SYMBOL_WHITE_STAR                   0x2606
#define SYMBOL_BLACK_STAR                   0x2605

#define SYMBOL_LESS_OVER_EQUAL              0x2266
#define SYMBOL_GREATER_OVER_EQUAL           0x2267
#define SYMBOL_NOT_EQUAL                    0x2260

#define SYMBOL_LEFT_SINGLE_QUOT             0x2018
#define SYMBOL_RIGHT_SINGLE_QUOT            0x2019
#define SYMBOL_LEFT_DOUBLE_QUOT             0x201c
#define SYMBOL_RIGHT_DOUBLE_QUOT            0x201d
#define SYMBOL_LEFT_DB_PRIME_QUOT           0x301d
#define SYMBOL_RIGHT_DB_PRIME_QUOT          0x301e

#define SYMBOL_LEFT_CORNER_BRACKET          0x300c
#define SYMBOL_RIGHT_CORNER_BRACKET         0x300d
#define SYMBOL_LEFT_WT_CORNER_BRACKET       0x300e
#define SYMBOL_RIGHT_WT_CORNER_BRACKET      0x300f

#define SYMBOL_LEFT_ANGLE_BRACKET           0x3008
#define SYMBOL_RIGHT_ANGLE_BRACKET          0x3009
#define SYMBOL_LEFT_DB_ANGLE_BRACKET        0x300a
#define SYMBOL_RIGHT_DB_ANGLE_BRACKET       0x300b

#define SYMBOL_LEFT_BK_LENTIC_BRACKET       0x3010
#define SYMBOL_RIGHT_BK_LENTIC_BRACKET      0x3011

#define SYMBOL_LEFT_TORT_SHELL_BRACKET      0x3014
#define SYMBOL_RIGHT_TORT_SHELL_BRACKET     0x3015

// box drawings
#define SYMBOL_BD_HORZONTAL                 0x2500
#define SYMBOL_BD_VERTICAL                  0x2502
#define SYMBOL_BD_DOWN_RIGHT                0x250c
#define SYMBOL_BD_DOWN_LEFT                 0x2510
#define SYMBOL_BD_UP_RIGHT                  0x2514
#define SYMBOL_BD_UP_LEFT                   0x2518
#define SYMBOL_BD_VERT_LEFT                 0x2524
#define SYMBOL_BD_DOWN_HORZ                 0x252c
#define SYMBOL_BD_UP_HORZ                   0x2534
#define SYMBOL_BD_VERT_HORZ                 0x253c
#define SYMBOL_BD_VERT_RIGHT                0x251c

// arrows
#define SYMBOL_LEFT_ARROW                   0x2190
#define SYMBOL_UP_ARROW                     0x2191
#define SYMBOL_RIGHT_ARROW                  0x2192
#define SYMBOL_DOWN_ARROW                   0x2193

// special signals
#define OUTWND_CLEAR                        0x9998


extern SOFTKEY  g_rgskSymbol[];
extern WORD     g_cSymbolKeys;

#endif  // _SYMBOLS_H
