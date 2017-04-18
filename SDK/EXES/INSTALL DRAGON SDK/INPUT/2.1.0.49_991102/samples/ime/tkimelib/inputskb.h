
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
#ifndef INPUTSKB_H
#define INPUTSKB_H

#include "input.h"
#include "softkbd.h"

extern HWND                        g_hwndSKB;
extern LPDIRECTINPUTDEVICE2        g_pdidevice2JoystickSKB;


void SKBReadDirectInputDevices 
(
    void
);
SOFTKEY* SKBProcessXMovement 
(
    DIJOYSTATE dijoystate, 
    SOFTKEY* psk,
    STEP_MOVEMENT bStep
);
SOFTKEY* SKBProcessYMovement 
(
    DIJOYSTATE dijoystate, 
    SOFTKEY* psk,
    STEP_MOVEMENT bStep
);
TCHAR 
SKBConvertHiraganaKey
(
    TCHAR wcCharacter
);
void 
SKBProcessHiraganaKey
(
    TCHAR wcCharacter
);
TCHAR 
SKBConvertKatakanaKey
(
    TCHAR wcCharacter
);
void 
SKBProcessKatakanaKey
(
    TCHAR wcCharacter
);
TCHAR 
SKBConvertRomanjiKey
(
    TCHAR wcCharacter
);
void
SKBProcessRomanjiKey
(
    TCHAR wcCharacter
);

#endif
