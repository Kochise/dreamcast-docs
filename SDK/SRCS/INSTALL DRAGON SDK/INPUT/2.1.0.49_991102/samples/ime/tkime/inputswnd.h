
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1998 Microsoft Corporation

Module Name:

    inputswnd.h

Abstract:

    Header file for inputswnd.cxx, which manages the input to the 
    symbol window (SWND).

Environment:

    Runs on Dreamcast under Windows CE.

-------------------------------------------------------------------*/
#ifndef INPUTSWND_H
#define INPUTSWND_H

#include "input.h"
#include "swnd.h"

extern HWND                        g_hwndSWND;
extern LPDIRECTINPUTDEVICE2        g_pdidevice2JoystickSKB;



BOOL SWNDReadDirectInputDevices 
(
    WORD* iKeyTop
);
SWNDKEY* SWNDProcessXMovement 
(
    DIJOYSTATE dijoystate, 
    SWNDKEY* psk,
    WORD *iKeyTop,
    STEP_MOVEMENT bStep
);
SWNDKEY* SWNDProcessYMovement 
(
    DIJOYSTATE dijoystate, 
    SWNDKEY* psk,
    WORD* iKeyTop,
    STEP_MOVEMENT bStep
);



#endif