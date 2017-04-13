/*==========================================================================
 *
 *  Copyright (C) 1995 Microsoft Corporation. All Rights Reserved.
 *
 *  File:       ddmm.cpp
 *  Content:    Routines for using DirectDraw on a multimonitor system
 *
 ***************************************************************************/

#define WIN32_LEAN_AND_MEAN
#define WINVER 0x0400
#define _WIN32_WINDOWS 0x0400
#include <windows.h>
#include <windowsx.h>
#include <ddraw.h>
#include "ddmm.h"

#define COMPILE_MULTIMON_STUBS
#include "multimon.h"

/*
 *  OneMonitorCallback
 */
BOOL CALLBACK OneMonitorCallback(HMONITOR hMonitor, HDC hdc, LPRECT prc, LPARAM lParam)
{
    HMONITOR *phMonitorFound = (HMONITOR *)lParam;

    if (*phMonitorFound == 0)
        *phMonitorFound = hMonitor;
    else
        *phMonitorFound = INVALID_HANDLE_VALUE;

    return TRUE;
}

/*
 *  OneMonitorFromWindow
 *
 *  similar to the Win32 function MonitorFromWindow, except
 *  only returns a HMONITOR if a window is on a single monitor.
 *
 *  if the window handle is NULL, the primary monitor is returned
 *  if the window is not visible returns NULL
 *  if the window is on a single monitor returns its HMONITOR
 *  if the window is on more than on monitor returns INVALID_HANDLE_VALUE
 */
HMONITOR OneMonitorFromWindow(HWND hwnd)
{
    HMONITOR hMonitor = NULL;
    RECT rc;

    if (hwnd)
    {
        GetClientRect(hwnd, &rc);
        ClientToScreen(hwnd, (LPPOINT)&rc);
        ClientToScreen(hwnd, (LPPOINT)&rc+1);
    }
    else
    {
        //SetRect(&rc,0,0,1,1);
        SetRectEmpty(&rc);
    }

    EnumDisplayMonitors(NULL, &rc, OneMonitorCallback, (LPARAM)&hMonitor);
    return hMonitor;
}

/*
 * FindDeviceCallback
 */
typedef struct {
    LPSTR   szDevice;
    GUID*   lpGUID;
    GUID    GUID;
    BOOL    fFound;
}   FindDeviceData;

BOOL CALLBACK FindDeviceCallback(GUID* lpGUID, LPSTR szName, LPSTR szDevice, LPVOID lParam)
{
    FindDeviceData *p = (FindDeviceData*)lParam;

    if (lstrcmpi(p->szDevice, szDevice) == 0)
    {
	if (lpGUID)
	{
	    p->GUID = *lpGUID;
	    p->lpGUID = &p->GUID;
	}
	else
	{
	    p->lpGUID = NULL;
	}
	p->fFound = TRUE;
	return FALSE;
    }
    return TRUE;
}

/*
 * DirectDrawCreateFromDevice
 *
 * create a DirectDraw object for a particular device
 */
IDirectDraw * DirectDrawCreateFromDevice(LPSTR szDevice)
{
    IDirectDraw*    pdd = NULL;
    FindDeviceData  find;

    find.szDevice = szDevice;
    find.fFound   = FALSE;
    DirectDrawEnumerate(FindDeviceCallback, (LPVOID)&find);

    if (find.fFound)
    {
        DirectDrawCreate(find.lpGUID, &pdd, NULL);
    }

    return pdd;
}

/*
 * DirectDrawDeviceFromWindow
 *
 * find the direct draw device that should be used for a given window
 *
 * the return code is a "unique id" for the device, it should be used
 * to determine when your window moves from one device to another.
 *
 *      case WM_MOVE:
 *          if (MyDevice != DirectDrawDeviceFromWindow(hwnd,NULL,NULL))
 *          {
 *              // handle moving to a new device.
 *          }
 *
 */
int DirectDrawDeviceFromWindow(HWND hwnd, LPSTR szDevice, RECT *prc)
{
    HMONITOR hMonitor;

    if (GetSystemMetrics(SM_CMONITORS) <= 1)
    {
        if (prc) SetRect(prc,0,0,GetSystemMetrics(SM_CXSCREEN),GetSystemMetrics(SM_CYSCREEN));
        if (szDevice) lstrcpy(szDevice, "DISPLAY");
        return -1;
    }

    hMonitor = OneMonitorFromWindow(hwnd);

    if (hMonitor == NULL || hMonitor == INVALID_HANDLE_VALUE)
    {
	if (prc) SetRectEmpty(prc);
	if (szDevice) *szDevice=0;
        return 0;
    }
    else
    {
	if (prc != NULL || szDevice != NULL)
	{
	    MONITORINFOEX mi;
	    mi.cbSize = sizeof(mi);
	    GetMonitorInfo(hMonitor, &mi);
	    if (prc) *prc = mi.rcMonitor;
	    if (szDevice) lstrcpy(szDevice, mi.szDevice);
	}
        return (int)hMonitor;
    }
}

/*
 * DirectDrawCreateFromWindow
 */
IDirectDraw * DirectDrawCreateFromWindow(HWND hwnd)
{
    IDirectDraw *pdd;
    char szDevice[80];

    //
    // if there is only one monitor, just create a DD object!
    //
    if (GetSystemMetrics(SM_CMONITORS) <= 1)
    {
	DirectDrawCreate(NULL, &pdd, NULL);
        return pdd;
    }

    //
    // find the direct draw device that the window is on
    //
    if (DirectDrawDeviceFromWindow(hwnd, szDevice, NULL))
    {
	//
	// the window is only on one device,
	// do a create for only that device
	//
        return DirectDrawCreateFromDevice(szDevice);
    }
    else
    {
	//
	// the window is off the screen or spans two
	// monitors, do a DirectDrawCreate(NULL)
        //
        DirectDrawCreate(NULL, &pdd, NULL);
	return pdd;
    }
}
