/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999 Microsoft Corporation

Module Name:

    VibrationPack.hpp

Abstract:

   Include file for VibrationPack

-------------------------------------------------------------------*/

// ++++ Include Files +++++++++++++++++++++++++++++++++++++++++++++++

#include <tchar.h>
#include <windows.h>
#include <dinput.h>
#include <maplusag.h>
#include <mapledev.h>
#include <vib.h>
#include "CVibPack.hpp"
#include "CController.hpp"

// ++++ Enumerated Types ++++++++++++++++++++++++++++++++++++++++++++

// Output types
enum toutputlevel { OUTPUT_ALL = 0, OUTPUT_FAILURESONLY };

// ++++ Types +++++++++++++++++++++++++++++++++++++++++++++++++++++++

// Error type
typedef int terr;

// ++++ Defines +++++++++++++++++++++++++++++++++++++++++++++++++++++

// DIUtil.cpp defines
#define MAX_CONTROLLERS    4                            // Maximum number of controllers

// ++++ Global Variables ++++++++++++++++++++++++++++++++++++++++++++

// VibrationPack.cpp variables
extern HWND                g_hwndApp;                   // HWND of the application
extern HINSTANCE           g_hinst;                     // HINSTANCE of the application

// Error.cpp variables
extern toutputlevel g_outputlevel;                      // Amount of detail in error messages
extern terr g_errLast;                                  // Error return code of last function

//DIUtil.cpp variables
extern LPDIRECTINPUT       g_pdi;                       // The DirectInput object
extern CController         *g_rgpcont[MAX_CONTROLLERS]; // The list of active input devices

// ++++ Global Functions ++++++++++++++++++++++++++++++++++++++++++++

// DIUtil.cpp functions
BOOL InitDirectInput();
void PollDevices();
void GetDeviceData();
void CheckNewDevices();

// OutputState.cpp functions
void OutputControllerState(int iPort, CController *pcont);

// Error.cpp functions
BOOL CheckError(TCHAR *tszErr);
void RetailOutput(TCHAR *tszErr, ...);
#ifdef DEBUG
void DebugOutput(TCHAR *tszErr, ...);
#else
__inline void DebugOutput(TCHAR *tszErr, ...) {};
#endif
