
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1998 Microsoft Corporation

Module Name:

    romanji.h

Abstract:

    This file contains definitions of Roman characters which appear
    on the keyboard.


Environment:

    Runs on Dreamcast under Windows CE.

-------------------------------------------------------------------*/

#ifndef _ROMANJI_H
#define _ROMANJI_H


#include "symbols.h"
#include "kanji.h"
#include "display.h"



//      ROMAN                   UNICODE VALUE
//      ------------            ----------------------

// symbols from the keypad
#define ROMAN_EXCLAMATION       0x0021
#define ROMAN_DOUBLE_QUOTE      0x0022
#define ROMAN_NUMBER            0x0023
#define ROMAN_DOLLAR_SIGN       0x0024
#define ROMAN_PERCENT           0x0025
#define ROMAN_AMPERSAND         0x0026
#define ROMAN_SINGLE_QUOTE      0x0027
#define ROMAN_LEFT_PAREN        0x0028
#define ROMAN_RIGHT_PAREN       0x0029
#define ROMAN_ASTERISK          0x002a
#define ROMAN_PLUS              0x002b
#define ROMAN_COMMA             0x002c
#define ROMAN_MINUS             0x002d
#define ROMAN_PERIOD            0x002e
#define ROMAN_SOLIDUS           0x002f

#define ROMAN_COLON             0x003a
#define ROMAN_SEMICOLON         0x003b
#define ROMAN_LESSTHAN          0x003c
#define ROMAN_EQUALS            0x003d
#define ROMAN_GREATERTHAN       0x003e
#define ROMAN_QUESTION          0x003f

#define ROMAN_AT                0x0040

#define ROMAN_LEFT_BRACKET      0x005b
#define ROMAN_RIGHT_BRACKET     0x005d
#define ROMAN_REVERSE_SOLIDUS   0x005c
#define ROMAN_CIRCUMFLEX        0x005e
#define ROMAN_LOWLINE           0x005f

#define ROMAN_GRAVE_ACCENT      0x0060

#define ROMAN_LEFT_CURLY        0x007b
#define ROMAN_RIGHT_CURLY       0x007d
#define ROMAN_VERTICAL_LINE     0x007c
#define ROMAN_TILDE             0x007e

// digits
#define ROMAN_ONE               0x0031
#define ROMAN_TWO               0x0032
#define ROMAN_THREE             0x0033
#define ROMAN_FOUR              0x0034
#define ROMAN_FIVE              0x0035
#define ROMAN_SIX               0x0036
#define ROMAN_SEVEN             0x0037
#define ROMAN_EIGHT             0x0038
#define ROMAN_NINE              0x0039
#define ROMAN_ZERO              0x0030

// alphabet
#define ROMAN_A                 0x0041
#define ROMAN_B                 0x0042
#define ROMAN_C                 0x0043
#define ROMAN_D                 0x0044
#define ROMAN_E                 0x0045
#define ROMAN_F                 0x0046
#define ROMAN_G                 0x0047
#define ROMAN_H                 0x0048
#define ROMAN_I                 0x0049
#define ROMAN_J                 0x004a
#define ROMAN_K                 0x004b
#define ROMAN_L                 0x004c
#define ROMAN_M                 0x004d
#define ROMAN_N                 0x004e
#define ROMAN_O                 0x004f
#define ROMAN_P                 0x0050
#define ROMAN_Q                 0x0051
#define ROMAN_R                 0x0052
#define ROMAN_S                 0x0053
#define ROMAN_T                 0x0054
#define ROMAN_U                 0x0055
#define ROMAN_V                 0x0056
#define ROMAN_W                 0x0057
#define ROMAN_X                 0x0058
#define ROMAN_Y                 0x0059
#define ROMAN_Z                 0x005a

#define ROMAN_SPACE             0x0020
#define ROMAN_NULL              '\0'

#define ROMAN_START             0x0021
#define ROMAN_END               0x007e

#define ROMAN_DOUBLEWIDTH_OFFSET    0xfee0

// the difference between upper case A and lower case A in UNICODE
#define ROMAN_ALPHABET_GAP      0x0020


extern SOFTKEY  g_rgskRomanji[];
extern WORD     g_cRomanjiKeys;

#endif  // _ROMANJI_H
