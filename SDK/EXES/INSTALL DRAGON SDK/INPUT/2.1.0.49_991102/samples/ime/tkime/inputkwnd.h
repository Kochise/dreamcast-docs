
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1998 Microsoft Corporation

Module Name:

    inputkwnd.h

Abstract:

    Header file for inputkwnd.cxx, which manages the input to the 
    kanji selection window (KWND).

Environment:

    Runs on Dreamcast under Windows CE.

-------------------------------------------------------------------*/
#ifndef INPUTKWND_H
#define INPUTKWND_H

#include "input.h"
#include "kwnd.h"

extern HWND                        g_hwndKWND;
extern LPDIRECTINPUTDEVICE2        g_pdidevice2JoystickIME;

BOOL KWNDReadDirectInputDevices 
(
    WORD* iKeyTop
);
KWNDKEY* KWNDProcessYMovement 
(
    DIJOYSTATE dijoystate, 
    KWNDKEY* psk,
    WORD *iKeyTop,
    STEP_MOVEMENT bStep
);
KWNDKEY* KWNDProcessXMovement 
(
    DIJOYSTATE dijoystate, 
    KWNDKEY* psk,
    WORD* iKeyTop,
    STEP_MOVEMENT bStep
);



#endif