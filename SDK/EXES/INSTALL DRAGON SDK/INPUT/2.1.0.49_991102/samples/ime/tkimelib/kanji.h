
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1998 Microsoft Corporation

Module Name:

    kanji.h

Abstract:

    This file contains definitions of kanji characters which appear on the keyboard.

Environment:

    Runs on Dreamcast under Windows CE.

-------------------------------------------------------------------*/

#ifndef _KANJI_H
#define _KANJI_H

//  The following characters are for the kanji strings which appear on the softkbd's "hot" keys
//      KANJI               UNICODE VALUE
//      ------------        ----------------------

// confirm/convert keys
#define KANJI_CONFIRM_0     0x78ba
#define KANJI_CONFIRM_1     0x5b9a
#define KANJI_CONFIRM       TEXT("\x78BA\x5B9A")
#define US_CONFIRM          TEXT("OK")

#define KANJI_CONVERT_0     0x5909
#define KANJI_CONVERT_1     0x63db
#define KANJI_CONVERT       TEXT("\x5909\x63DB")
#define US_CONVERT          TEXT("Conv")
//#define KANJI_NOCONVERT_0 0x7121
//#define KANJI_NOCONVERT_1 0x5909
//#define KANJI_NOCONVERT_2 0x63db

// escape key
#define KANJI_REJECT_0      0x53d6
#define KANJI_REJECT_1      0x6d88
#define KANJI_REJECT        TEXT("\x53D6\x6D88")
#define US_REJECT           TEXT("Esc")

// switch to/from half-height characters
#define KANJI_SMALL_0       0x5c0f
#define KANJI_SMALL_1       0x5b57
#define KANJI_SMALL         TEXT("\x5C0F\x5B57")
#define US_SMALL            TEXT("Small")

// delete key
#define KANJI_DELETE_0      0x524a
#define KANJI_DELETE_1      0x9664
#define KANJI_DELETE        TEXT("\x524A\x9664")
#define US_BACKSPACE        TEXT("<-- BkSp")

// pop up the special symbols panel
#define KANJI_SYMBOLS_0     0x8a18
#define KANJI_SYMBOLS_1     0x53f7
#define KANJI_SYMBOLS       TEXT("\x8A18\x53F7")
#define US_SYMBOLS          TEXT("Sym")

// close the soft keyboard
#define KANJI_CLOSE_0       0x6587
#define KANJI_CLOSE_1       0x5b57
#define KANJI_CLOSE_2       0x5165
#define KANJI_CLOSE_3       0x529b
#define KANJI_CLOSE_4       0x7d42
#define KANJI_CLOSE_5       0x308a
#define KANJI_CLOSE         TEXT("\x6587\x5B57\x5165\x529B\x7D42\x308A")
#define US_CLOSE            TEXT("Exit")

// switch to english keyboard
#define KANJI_ENGLISH_0     0x82f1
#define KANJI_ENGLISH_1     0x8a9e
#define KANJI_ENGLISH       TEXT("\x82F1\x8A9E")
#define US_ENGLISH          TEXT("ABC")

// switch to/from half-width characters
#define KANJI_HALF_0        0x5168  
#define KANJI_HALF_1        0x002f  
#define KANJI_HALF_2        0x534a  
#define KANJI_HALF_3        0x89d2
#define KANJI_HALF          TEXT("\x5168\x002F\x534A\x89D2")
#define US_HALF             TEXT("\xFF21/\x0041")

// space key
#define KANJI_SPACE_0       0x7a7a
#define KANJI_SPACE_1       0x767d
#define KANJI_SPACE         TEXT("\x7A7A\x767D")
#define US_SPACE            TEXT("Space")

// caps lock
#define KANJI_CAPSLOCK_0    0x5927
#define KANJI_CAPSLOCK_1    0x002f
#define KANJI_CAPSLOCK_2    0x5c0f
#define KANJI_CAPSLOCK_3    0x5b57
#define KANJI_CAPSLOCK      TEXT("\x5927\x002F\x5C0F\x5B57")
#define US_CAPSLOCK         TEXT("Caps Lock")

#define CMD_CONFIRM         KANJI_CONFIRM_0
#define CMD_CONVERT         KANJI_CONVERT_0
#define CMD_REJECT          KANJI_REJECT_0
#define CMD_SMALL           KANJI_SMALL_0
#define CMD_DELETE          KANJI_DELETE_0
#define CMD_SYMBOLS         KANJI_SYMBOLS_0
#define CMD_CLOSE           KANJI_CLOSE_0
#define CMD_ENGLISH         KANJI_ENGLISH_0
#define CMD_HALF            KANJI_HALF_0
#define CMD_SPACE           KANJI_SPACE_0
#define CMD_CAPSLOCK        KANJI_CAPSLOCK_0

#endif  // _KANJI_H
