// setupdd.h - Public definitions for users of SETUPDD.DLL
//
//

#ifndef _SETUPDD_H_
#define _SETUPDD_H_

// NMInstallNTDisplayDriver
//
// The public entry point of SETUPDD.DLL.  Installs the NetMeeting display
// driver for Windows NT. 
// 
// Parameters:
//	HWND - Handle of the parent window used by the setup engine when 
//		displaying dialogs).
//
// Returns:
//	TRUE if the driver was successfully installed.  In this event,
//		the caller should prompt the user to restart the system for
//		the changes to take effect.
//  FALSE if this version of the OS does not support this driver
//		(NT 4.0 SP 3 or later, or NT 4.x, x > 0, is required) or if
//		an error occurs during installation.
//
// Limitations:
//	NetMeeting must already be installed on the system for this function
//		to work.
//	This function does not detect if the display driver is already
//		installed and enabled.

BOOL DECLSPEC_IMPORT WINAPI NMInstallNTDisplayDriver(HWND hWnd);

#endif // _SETUPDD_H_
