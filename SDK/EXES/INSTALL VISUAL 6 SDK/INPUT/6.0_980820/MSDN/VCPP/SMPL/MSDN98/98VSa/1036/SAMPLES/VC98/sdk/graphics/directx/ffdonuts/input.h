/*==========================================================================
 *
 *  Copyright (C) 1995-1996 Microsoft Corporation. All Rights Reserved.
 *
 *  File:       input.h
 *  Content:    input functionality include file
 *
 *
 ***************************************************************************/

#ifndef _INPUT_H
#define _INPUT_H

#ifdef __cplusplus
extern "C" {            /* Assume C declarations for C++ */
#endif	/* __cplusplus */

//---------------------------------------------------------------------------

#include <dinput.h>

// prototypes
BOOL            inputInitDirectInput(HINSTANCE hInst, HWND hWnd);
void            inputCleanupDirectInput(void);
BOOL CALLBACK   inputEnumDeviceProc(LPDIDEVICEINSTANCE pdidi, LPVOID pv);
BOOL CALLBACK   inputEnumEffectTypeProc(LPCDIEFFECTINFO pei, LPVOID pv);
BOOL            inputAcquireDevices(void);
BOOL            inputCreateEffect(DWORD dwEffectFlags);
DWORD           inputProcessDeviceInput(void);
BOOL            inputPrepareDevice(void);
BOOL            inputPlayEffect(DWORD dwEffectFlags, LONG lDirection);
BOOL CALLBACK   inputForceLevelDlgProc(HWND hWnd, UINT uMsg, WPARAM wParam,
                                       LPARAM lParam);

// constants used for scaling the input device
#define DEADZONE        2500            // 25% of the axis range
#define RANGE_MAX       1000            // maximum positive axis value
#define RANGE_MIN       -1000           // minimum negative axis value
#define FF_CHILD        5000            // "Child"          gain == 50%
#define FF_ADULT        7500            // "Adult"          gain == 75%
#define FF_BODYBUILDER  10000           // "Bodybuilder"    gain == 100%

// "effect flags" - these are internal identifiers and in no way map to DirectInput
#define EF_BOUNCE   0x00000001l
#define EF_EXPLODE  0x00000002l
#define EF_FIRE     0x00000004l

// "keyboard" commands - moved from original .h file
#define KEY_STOP    0x00000001l
#define KEY_DOWN    0x00000002l
#define KEY_LEFT    0x00000004l
#define KEY_RIGHT   0x00000008l
#define KEY_UP      0x00000010l
#define KEY_FIRE    0x00000020l
#define KEY_THROW   0x00000040l
#define KEY_SHIELD  0x00000080l

//---------------------------------------------------------------------------

#endif _INPUT_H











