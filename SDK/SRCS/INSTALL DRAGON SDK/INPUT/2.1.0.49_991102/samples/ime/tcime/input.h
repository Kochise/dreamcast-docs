/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1998 Microsoft Corporation

Module Name:

    input.h

Abstract:

    This file contains prototypes for the DInput-related functions
    exported by input.cxx.

Environment:

    Runs on Dreamcast under Windows CE.

-------------------------------------------------------------------*/


#ifndef _INPUT_H
#define _INPUT_H

#include <maplusag.h>

// in direct input, a button has value 0x80 if it is pressed
#define BUTTON_ON                   0x80


#define LOWER_JOYSTICK_THRESHOLD    15
#define UPPER_JOYSTICK_THRESHOLD    100
#define SLOW_REPEAT_RATE            1000
#define FAST_REPEAT_RATE            50


// Macros to make referencing joystick buttons a little more convenient.
#define JOYSTICKMAXBUTTONS      (USAGE_LAST_BUTTON - USAGE_FIRST_BUTTON + 1)
#define JOYSTICKRANGE           100
#define JOYSTICK_A              (USAGE_A_BUTTON - USAGE_FIRST_BUTTON)
#define JOYSTICK_B              (USAGE_B_BUTTON - USAGE_FIRST_BUTTON)
#define JOYSTICK_START          (USAGE_START_BUTTON - USAGE_FIRST_BUTTON)
#define JOYSTICK_LA             (USAGE_LA_BUTTON - USAGE_FIRST_BUTTON)
#define JOYSTICK_RA             (USAGE_RA_BUTTON - USAGE_FIRST_BUTTON)
#define JOYSTICK_DA             (USAGE_DA_BUTTON - USAGE_FIRST_BUTTON)
#define JOYSTICK_UA             (USAGE_UA_BUTTON - USAGE_FIRST_BUTTON)
#define JOYSTICK_X              (USAGE_X_BUTTON - USAGE_FIRST_BUTTON)
#define JOYSTICK_Y              (USAGE_Y_BUTTON - USAGE_FIRST_BUTTON)
#define JOYSTICK_D              (USAGE_D_BUTTON - USAGE_FIRST_BUTTON)
#define JOYSTICK_LB             (USAGE_LB_BUTTON - USAGE_FIRST_BUTTON)
#define JOYSTICK_RB             (USAGE_RB_BUTTON - USAGE_FIRST_BUTTON)
#define JOYSTICK_DB             (USAGE_DB_BUTTON - USAGE_FIRST_BUTTON)
#define JOYSTICK_UB             (USAGE_UB_BUTTON - USAGE_FIRST_BUTTON)
#define JOYSTICK_LTRIG          (USAGE_LTRIG_BUTTON - USAGE_FIRST_BUTTON)
#define JOYSTICK_RTRIG          (USAGE_RTRIG_BUTTON - USAGE_FIRST_BUTTON)
#define INVALID_INDEX           0xff


// Array of joystick button indices, arranged by usage.
extern BYTE                     g_rgiButtons[JOYSTICKMAXBUTTONS];
// Array of previous joystick button states
extern BYTE                     g_rgiPrevButtons[JOYSTICKMAXBUTTONS];

// Array to map joystick buttons to SKB keys (WM_KEYDOWN messages).
extern WPARAM                   g_rgwparamButtons[JOYSTICKMAXBUTTONS];

// Global DirectInput objects
extern LPDIRECTINPUT            g_pdinput;
extern HWND                     g_hwndDirectInput;

// is the CWND active? if so, then the SKB is not active
extern BOOL                     g_bCWNDactive;

// is the RWND active? if so, then the SKB is not active
extern BOOL                     g_bRWNDactive;

extern BOOL                     g_fHardwareKeyboardPresent;

// this flag allows the IME to communicate to the softkbd that it should reacquire the joystick
extern BOOL                     g_bSKBReacquireJoystick;

extern BOOL                     g_fAnalogJoystick;

// enum for moving forward, back, or don't move
typedef enum {BACK, NONE, FORWARD} STEP_MOVEMENT;


// INPUT.CXX

void SendKeyEvents(UINT uVK, UINT uCharNum, UINT uChars);

BOOL CreateDirectInput(HINSTANCE hinstApp, HWND hwndApp,
                       LPDIRECTINPUTDEVICE2 *pdidevice2Joystick);

BOOL  AcquireJoystick(LPDIRECTINPUTDEVICE2 *pdidevice2Joystick);

void DestroyDirectInput(void);

void FillPrevButtons(DIJOYSTATE dijoystate);

void InitializePrevButtons(void);

BOOL CheckForHardwareKeyboard(void);

#endif  // #ifndef _INPUT_H
