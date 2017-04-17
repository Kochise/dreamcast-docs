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

// escape key
#define KANJI_REJECT_0      0x53d6
#define KANJI_REJECT_1      0x6d88

// delete key
#define KANJI_DELETE_0      0x524a
#define KANJI_DELETE_1      0x9664

// close the soft keyboard
#define KANJI_CLOSE_0       0x7d50
#define KANJI_CLOSE_1       0x675f

// switch to phonetic keyboard
#define KANJI_PHONETIC_0    0x6ce8
#define KANJI_PHONETIC_1    0x97f3

// switch to english keyboard
#define KANJI_ENGLISH_0     0x82f1
#define KANJI_ENGLISH_1     0x6587

// switch to symbol keyboard
#define KANJI_SYMBOLS_0     0x7b26
#define KANJI_SYMBOLS_1     0x865f

// switch to/from half-width characters
#define KANJI_HALF_0        0x5168  
#define KANJI_HALF_1        0x002f  
#define KANJI_HALF_2        0x534a  
#define KANJI_HALF_3        0x5f62  

// space key
#define KANJI_SPACE_0       0x7a7a
#define KANJI_SPACE_1       0x767d

// caps lock
#define KANJI_CAPSLOCK_0    0x5927
#define KANJI_CAPSLOCK_1    0x002f
#define KANJI_CAPSLOCK_2    0x5c0f
#define KANJI_CAPSLOCK_3    0x5b57

#endif  // _KANJI_H
