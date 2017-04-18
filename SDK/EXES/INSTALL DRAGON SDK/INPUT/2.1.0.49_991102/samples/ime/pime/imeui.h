
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1998 Microsoft Corporation

Module Name:

    imeui.h

Abstract:

    This file contains the prototypes of functions in imeui.cxx, which
    manages the input method editor (IME) user interface window.

Environment:

    Runs on Dreamcast under Windows CE.

-------------------------------------------------------------------*/

#ifndef IMEUI_H
#define IMEUI_H

#include "windows.h"
#include "ddraw.h"
#include "kwnd.h"
#include "tankanji.h"
#include "romanji.h"
#include "hiragana.h"
#include "katakana.h"

// name of tankanji dictionary, so that we can load the dictionary as a resource
#define TANKANJI_DICTIONARY_NAME    TEXT("TANKANJI_DICTIONARY")


// enum for return value of IMEProcessKana
typedef enum {HIRAGANA_STRING, OTHER_STRING, INVALID_STRING} KANA_STRING_TYPE;


// IME.CXX
BOOL
IMECreate
    (
    void
    );
void 
IMEProcessKey
    (
    TCHAR wcKey
    );
void 
IMEProcessVirtualKey
    (
    TCHAR wcKey,
    BOOL fCtrlKeyPressed
    );
void
IMEDestroy
    (
    void
    );
void
IMEUpdate
    (
    void
    );
void
IMEBlt
    (
    LPDIRECTDRAWSURFACE lpDDSBack
    );
KANA_STRING_TYPE
IMEProcessKana
(
    TCHAR *szKanaIn,
    TCHAR *szKanaOut
);
BOOL
IsKatakana(TCHAR *szIn);
BOOL
IsHiragana(TCHAR *szIn);
void
ConvertToHiragana
    (
    TCHAR*          szInput,
    TCHAR*          szHiragana
    );
TCHAR
DakutenValid(TCHAR wcKey);
TCHAR
HandakutenValid(TCHAR wcKey);

extern unsigned short		g_iKeyTop;				   // the top displayed row of the scrolling

#endif  // IMEUI_H
