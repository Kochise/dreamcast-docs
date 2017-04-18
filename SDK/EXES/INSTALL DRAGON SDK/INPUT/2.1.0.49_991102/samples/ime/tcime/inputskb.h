
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1998 Microsoft Corporation

Module Name:

    inputskb.h

Abstract:

    Header file for inputskb.cxx, which manages the input to the 
    soft keyboard window.

Environment:

    Runs on Dreamcast under Windows CE.

-------------------------------------------------------------------*/
#ifndef _INPUTSKB_H
#define _INPUTSKB_H


extern HWND                    g_hwndSKB;
extern LPDIRECTINPUTDEVICE2    g_pdidevice2JoystickSKB;


void SKBReadDirectInputDevices(void);

TCHAR SKBConvertPhoneticKey(TCHAR wcCharacter);

void SKBProcessPhoneticKey(TCHAR wcCharacter);

TCHAR SKBConvertRomanjiKey(TCHAR wcCharacter);

void SKBProcessRomanjiKey(TCHAR wcCharacter);

TCHAR SKBConvertSymbolKey(TCHAR wcCharacter);

void SKBProcessSymbolKey(TCHAR wcCharacter);

#endif  // _INPUTSKB_H