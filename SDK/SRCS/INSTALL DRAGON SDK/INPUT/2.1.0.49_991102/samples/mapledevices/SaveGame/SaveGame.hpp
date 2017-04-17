/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999 Microsoft Corporation

Module Name:

    VMU_Flash.hpp

Abstract:

   Include file for VMU_Flash

-------------------------------------------------------------------*/

#ifndef VMU_FLASH_HPP
#define VMU_FLASH_HPP

// ++++ Include Files +++++++++++++++++++++++++++++++++++++++++++++++

#include <tchar.h>
#include <windows.h>
#include <dinput.h>
#include <maplusag.h>
#include <mapledev.h>
#include <ceddcdrm.h>	// For IOCTL_CDROM_BASE
#include <segagdrm.h>	// For SEGACD_DOOR_BEHAVIOR
#include <perstore.h>
#include <platutil.h>	// For ResetToFirmware
#include <dbt.h>		// For WM_DEVICECHANGE & DBT_DEVICEREMOVECOMPLETE
#include "CFlash.hpp"
#include "CController.hpp"


// ++++ Enumerated Types ++++++++++++++++++++++++++++++++++++++++++++

// Output types
enum toutputlevel { OUTPUT_ALL = 0, OUTPUT_FAILURESONLY };
typedef enum eCommand {ecmdDumpUsage, ecmdFormatFlash, ecmdDumpFlash, ecmdCopyFlash};

// ++++ Types +++++++++++++++++++++++++++++++++++++++++++++++++++++++

// Error type
typedef int terr;

// ++++ Defines +++++++++++++++++++++++++++++++++++++++++++++++++++++

// DIUtil.cpp defines
#define MAX_CONTROLLERS		4                            // Maximum number of controllers
#define MAX_DEVICE_EVENT	2

#define NEW_DEVICE			0
#define DEVICE_REMOVED		1

#define WM_FINISHED_WRITING WM_USER + 101
#define WM_INITVMU			WM_USER + 102
#define WM_CHOSSESAVESLOT	WM_USER + 104


// ++++ Global Variables ++++++++++++++++++++++++++++++++++++++++++++

// VMU_Flash.cpp variables
extern HINSTANCE			g_hinst;                     // HINSTANCE of the application
extern HANDLE				g_hDeviceEvent[MAX_DEVICE_EVENT];// NEW_DEVICE and DEVICE_ROMOVED
extern HWND					g_hwndApp;                                // HWND of the application
extern CFlash				*g_pFlash;


// Error.cpp variables
extern toutputlevel g_outputlevel;                      // Amount of detail in error messages
extern terr g_errLast;                                  // Error return code of last function

//DIUtil.cpp variables
extern LPDIRECTINPUT       g_pdi;                       // The DirectInput object
extern CController         *g_rgpcont[MAX_CONTROLLERS]; // The list of active input devices

// ++++ Global Functions ++++++++++++++++++++++++++++++++++++++++++++

// DIUtil.cpp functions
BOOL InitDirectInput();
void GetDeviceData();
void CheckNewDevices();

// SaveGame functions
BOOL InitVMU();
void Save( DWORD in_dwSlot );
void ChooseSaveSlot();
void ChangeRebootType(BOOL bReboot);


// Error.cpp functions
BOOL CheckError(TCHAR *tszErr);
void RetailOutput(TCHAR *tszErr, ...);
#ifdef DEBUG
void DebugOutput(TCHAR *tszErr, ...);
#else
__inline void DebugOutput(TCHAR *tszErr, ...) {};
#endif
#endif
