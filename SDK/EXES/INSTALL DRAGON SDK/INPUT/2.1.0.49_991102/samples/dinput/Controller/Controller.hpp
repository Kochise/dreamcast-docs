/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999 Microsoft Corporation

Module Name:

    Controller.hpp

Abstract:

   Include file for Controller sample

-------------------------------------------------------------------*/

// ++++ Include Files +++++++++++++++++++++++++++++++++++++++++++++++

#include <tchar.h>
#include <windows.h>
#include <ddraw.h>
#include <dinput.h>
#include <maplusag.h>
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

// Controller.cpp variables
extern HWND                g_hwndApp;             // HWND of the application
extern HINSTANCE           g_hinst;               // HINSTANCE of the application
extern LPDIRECTDRAWSURFACE g_pddsButtons;         // Contains button bitmaps 

// Error.cpp variables
extern toutputlevel g_outputlevel;                      // Amount of detail in error messages
extern terr g_errLast;                                  // Error return code of last function

// DDUtil.cpp variables
extern LPDIRECTDRAW        g_pdd;                    // The DirectDraw object
extern LPDIRECTDRAWSURFACE g_pddsPrimary;            // Primary directdraw surface
extern LPDIRECTDRAWSURFACE g_pddsBack;               // Back buffer directdraw surface

// DIUtil.cpp variables
extern LPDIRECTINPUT       g_pdi;                    // The DirectInput object
extern CController         *g_rgpcont[MAX_CONTROLLERS]; // The list of active input devices

// ++++ Global Functions ++++++++++++++++++++++++++++++++++++++++++++

// DDUtil.cpp functions
void FlipBuffers();
BOOL InitDirectDraw();

// DIUtil.cpp functions
BOOL InitDirectInput();
void PollDevices();
void GetDeviceData();
void CheckNewDevices();
LPDIRECTDRAWSURFACE LoadBitmapToDDS(LPTSTR tszBitmap);

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
