
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1998 Microsoft Corporation

Module Name:

    inputkwnd.h

Abstract:

    Header file for inputcwd.cpp, which manages the input to the 
    candidate selection window (CWND).

Environment:

    Runs on Dreamcast under Windows CE.

-------------------------------------------------------------------*/
#ifndef _INPUTCWND_H
#define _INPUTCWND_H

#include "input.h"
#include "candwnd.h"

extern HWND                 g_hwndCWND;
extern LPDIRECTINPUTDEVICE2 g_pdidevice2JoystickCWND;

BOOL CWNDReadDirectInputDevices(WORD* iKeyTop);

CWNDKEY* CWNDProcessYMovement(DIJOYSTATE    dijoystate,
                              CWNDKEY*      psk,
                              WORD*         iKeyTop,
                              STEP_MOVEMENT bStep);

CWNDKEY* CWNDProcessXMovement(DIJOYSTATE    dijoystate,
                              CWNDKEY*      psk,
                              WORD*         iKeyTop,
                              STEP_MOVEMENT bStep);

#endif