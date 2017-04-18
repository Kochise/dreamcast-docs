/*
**-----------------------------------------------------------------------------
**  File:       WinProc.cpp
**  Purpose:    A sample windows proc for supporting D3D.
**  Notes:
**
**
**  Copyright (c) 1995 - 1997 by Microsoft, all rights reserved
**-----------------------------------------------------------------------------
*/

/*
**-----------------------------------------------------------------------------
**	Include Files
**-----------------------------------------------------------------------------
*/

#include "WinProc.h"
#include "WinMain.h"
#include "Debug.h"



/*
**-----------------------------------------------------------------------------
**	Local Typedefs
**-----------------------------------------------------------------------------
*/

typedef struct tagChangeDDInfo {
	DDDrvInfo  * lpDrvOrig;			// Original Driver
	DDDrvInfo  * lpDrvNew;			// New Driver (user choice)
	
	D3DDevInfo * lpDevOrig;			// Original D3D device
	D3DDevInfo * lpDevNew;			// New D3D device (user choice)

	DDModeInfo * lpModeOrig;		// Orignal Mode
	DDModeInfo * lpModeNew;			// New Mode (user choice)
} ChangeDDInfo;
typedef ChangeDDInfo * LPChangeDDInfo;



/*
**-----------------------------------------------------------------------------
**	Local Variables
**-----------------------------------------------------------------------------
*/

// Used for 3Dfx Voodoo driver detection below
const GUID guid3DfxVoodoo = {
	0x3A0CFD01,
	0x9320,
	0x11CF,
	0xAC,0xA1,0x00,0xA0,0x24,0x13,0xC2,0xE2
};



/*
**-----------------------------------------------------------------------------
**	Local function prototypes
**-----------------------------------------------------------------------------
*/

// About message proc
BOOL FAR PASCAL AboutBoxProc (HWND hWnd, UINT uiMsg,
							  WPARAM wParam, LPARAM lParam);


/*
**-----------------------------------------------------------------------------
**	Local function prototypes
**-----------------------------------------------------------------------------
*/

// Change Dialog
BOOL DlgDriversInit (HWND hDlg);
BOOL DlgDevicesInit (HWND hDlg);
BOOL DlgModesInit (HWND hDlg);

int _cdecl CompareModes (const void* element1, const void* element2);

LPDDDrvInfo  DlgGetDriver (HWND hDlg);
LPD3DDevInfo DlgGetDevice (HWND hDlg);
LPDDModeInfo DlgGetMode (HWND hDlg);

BOOL FAR PASCAL ChangeDriverProc (HWND hWnd, UINT uiMsg,
							      WPARAM wParam, LPARAM lParam);
void OnChangeDriver (HWND hWindow, int idDialog);



/*
**-----------------------------------------------------------------------------
**	Functions
**-----------------------------------------------------------------------------
*/

/*
**-----------------------------------------------------------------------------
**  Name:       D3DWindowProc
**  Purpose:    handles windows messages for D3DWindow's
**-----------------------------------------------------------------------------
*/

LRESULT CALLBACK D3DWindowProc (
    HWND    hWindow,
    UINT    uiMsg,
    WPARAM  wParam,
    LPARAM  lParam)
{
	LONG lResult;

    //
    // Windows messages
    //
    switch (uiMsg)
    {
	case WM_ACTIVATE:
		// Note:  Do we need to handle this ?!?
		break;

    case WM_ACTIVATEAPP:
        return OnActivateApp (hWindow, wParam, lParam);

	case WM_CLOSE:
		return OnClose (hWindow);

    case WM_COMMAND:
        return OnCommand (hWindow, wParam, lParam);

    case WM_CREATE:
		return OnCreate (hWindow);
			
    case WM_DESTROY:
		return OnDestroy (hWindow);

	case WM_DISPLAYCHANGE:
		return OnDisplayChange (hWindow);

    case WM_ERASEBKGND:
		return OnEraseBackground (hWindow, wParam, lParam);

    case WM_GETMINMAXINFO:
		return OnGetMinMaxInfo (hWindow, (LPMINMAXINFO) lParam);

    case WM_MOVE:
        return OnMove (hWindow, (INT)LOWORD(lParam), (INT)HIWORD(lParam));

    case WM_PAINT:
    {
        HDC         hdc;
        PAINTSTRUCT ps;

        hdc = BeginPaint (hWindow, &ps);            
        lResult = OnPaint (hWindow, hdc, &ps);
        EndPaint (hWindow, &ps);
    }
        return lResult;


	case WM_PALETTECHANGED:
		// Note:  We need to support this
		break;

	case WM_QUERYNEWPALETTE:
		// Note:  We need to support this
		break;

    case WM_SIZE:
        return OnSize (hWindow, (INT)LOWORD(lParam), (INT)HIWORD(lParam));
     
	 //
     // D3D Window messages
     //  
    case D3DWIN_GET_VALID:       // Get valid size
		{
		LPD3DWindow lpd3dWindow;
	
		//	Get D3DWindow pointer
		lpd3dWindow =  (LPD3DWindow)GetWindowLong (hWindow, GWL_USERDATA);
        if (! lpd3dWindow)
            return FALSE;
        return lpd3dWindow->isValid();
		}

    case D3DWIN_GET_POINTER:
		//	Get D3DWindow pointer
		return (LRESULT)GetWindowLong (hWindow, GWL_USERDATA);

    case D3DWIN_GET_SURFACE:
		{
		LPD3DWindow lpd3dWindow;
	
		//	Get D3DWindow pointer
		lpd3dWindow =  (LPD3DWindow)(void *)GetWindowLong (hWindow, GWL_USERDATA);
        if (! lpd3dWindow)
            return NULL;
        return (LPARAM)(lpd3dWindow->GetRender ());
		}

	case D3DWIN_INIT:
		return OnD3DInit (hWindow, (LPD3DWindow) lParam);

	case D3DWIN_FINI:
		return OnD3DFini (hWindow, (LPD3DWindow) lParam);

	case D3DWIN_CHANGED_DRIVER:
		return OnD3DChangeDriver (hWindow);

	case D3DWIN_CHANGED_DEVICE:
		return OnD3DChangeDevice (hWindow);

	case D3DWIN_CHANGED_MODE:
		return OnD3DChangeMode (hWindow);
    } // End Switch

   // Do Default window behavior
   return (DefWindowProc (hWindow, uiMsg, wParam, lParam));
} // End D3DWindowProc



/*
**-----------------------------------------------------------------------------
**  Name:       AboutBoxProc
**  Purpose:    handles messages for About Dialog box
**-----------------------------------------------------------------------------
*/
BOOL
FAR PASCAL AboutBoxProc (HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uiMsg)
	{
	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
			EndDialog (hWnd, TRUE);
		break;

    case WM_INITDIALOG:
		return TRUE;
	}
	return FALSE;
} // End AboutBoxProc 


  
/*
**-----------------------------------------------------------------------------
**  Name:       OnAbout
**  Purpose:    Display About Dialog
**-----------------------------------------------------------------------------
*/

LRESULT OnAbout (HWND hWindow)
{
	HINSTANCE hInstance;

	if ((! hWindow) || (! IsWindow (hWindow)))
		return 0L;

	hInstance = (HINSTANCE) GetWindowLong (hWindow, GWL_HINSTANCE);
	if (! hInstance)
		return 0L;

    // Pause App
    OnPause (hWindow, TRUE);

    // Do About Dialog here
    DialogBox (hInstance, MAKEINTRESOURCE (IDD_ABOUT), hWindow, (DLGPROC)AboutBoxProc);

    // UnPause app
    OnPause (hWindow, FALSE);

    return 0L;
} // End OnAbout


  
/*
**-----------------------------------------------------------------------------
**  Name:       OnActivateApp
**  Purpose:    ActivateApp
**  Note:
**		always let it fall through to Default window proc
**		to set up keyboard focus properly, etc.
**-----------------------------------------------------------------------------
*/

LRESULT OnActivateApp (HWND hWindow, WPARAM wParam, LPARAM lParam)
{
	BOOL fActive = (BOOL)wParam;

	// Get D3D Window pointer
	LPD3DWindow lpd3dWindow =  (LPD3DWindow)GetWindowLong (hWindow, GWL_USERDATA);

    if (fActive)
    {
		// Reactivating - Realize current palette
		if (lpd3dWindow)
		{
			lpd3dWindow->turnActiveOn ();
			lpd3dWindow->RealizePalette ();
		}
    }
    else
    {
        //
        //  If we have been deactivated invalidate
        //  to show the paused display.
        //
		if (lpd3dWindow)
		{
			lpd3dWindow->turnActiveOff ();
	        InvalidateRect (hWindow, NULL, FALSE);
		}

    }

    // Do default behavior
	return DefWindowProc (hWindow, WM_ACTIVATEAPP, wParam, lParam);
} // End OnActivateApp


  
/*
**-----------------------------------------------------------------------------
**  Name:       OnClose
**  Purpose:    Shut down app
**-----------------------------------------------------------------------------
*/

LRESULT OnClose (HWND hWindow)
{
	// Just Destroy the window for now
    DestroyWindow (hWindow);
	return 0L;
} // End OnClose

  

/*
**-----------------------------------------------------------------------------
**  Name:       OnCommand
**  Purpose:    Handle User commands
**-----------------------------------------------------------------------------
*/

LRESULT OnCommand (HWND hWindow, WPARAM wParam, LPARAM lParam)
{   
	HWND  hControl	= (HWND)lParam;
    DWORD dwNotify	= (DWORD)HIWORD(wParam);
    DWORD dwID      = (DWORD)LOWORD(wParam);

    if (hControl)
    {
		//
	    // Handle messages from controls here
        //
    }
    else 
	{
		// 
		// Handle Menu messages here
		//
		switch (dwID)
		{
		case IDM_EXIT:
			// Close down app
			SendMessage (hWindow, WM_CLOSE, 0, 0);
			return 0;

		case IDM_ABOUT:
			// Bring up About Dialog
			OnAbout (hWindow);
			break;

		case IDM_CHANGE_DRIVERS:
			// Bring up the "Change Driver" dialog
			OnChangeDriver (hWindow, IDD_CHANGE_DRIVER);
			break;

		default:
			// Unknown Menu Command
			break;
		}
	}

    // Let Default Window Proc handle it for us.
    return DefWindowProc (hWindow, WM_COMMAND, wParam, lParam);
} // End OnCommand



/*
**-----------------------------------------------------------------------------
**  Name:       OnCreate
**  Purpose:    Initialization of any Window objects
**-----------------------------------------------------------------------------
*/

LRESULT OnCreate (HWND hWindow)
{
    // Success
    return 0L;
} // End OnCreate


  
/*
**-----------------------------------------------------------------------------
**  Name:       OnDestroy
**  Purpose:    Cleanup and shut down app
**-----------------------------------------------------------------------------
*/

LRESULT OnDestroy (HWND hWindow)
{
    LPD3DWindow lpd3dWindow;
	
    //	Delete associated D3DWindow from this window
	lpd3dWindow =  (LPD3DWindow)GetWindowLong (hWindow, 0L);
	if (lpd3dWindow)
		lpd3dWindow->Fini ();
	SetWindowLong (hWindow, GWL_USERDATA, 0L);

    // Tell windows to QUIT!
    PostQuitMessage (0);
    return 0L;
} // End OnDestroy


  
/*
**-----------------------------------------------------------------------------
**  Name:       OnDisplayChange
**  Purpose:    Cleanup and shut down app
**-----------------------------------------------------------------------------
*/

LRESULT OnDisplayChange (HWND hWindow)
{
	HRESULT		hResult;
    LPD3DWindow lpd3dWindow;

	// Get D3D window pointer
	lpd3dWindow =  (LPD3DWindow)GetWindowLong (hWindow, GWL_USERDATA);
	if (! lpd3dWindow)
		return 0L;
	
	// Change Primary surface to new desktop
	hResult = lpd3dWindow->ChangeDesktop ();
	if (FAILED (hResult))
		return 0L;

	// Success
    return 0L;
} // End OnDestroy


  
/*
**-----------------------------------------------------------------------------
**  Name:       OnEraseBackground
**  Purpose:    Erase Window background
**  Notes:
**		1.  The only time we need to do this is when
**			the rendering surface is valid yet smaller than the client area
**			any other situation and we are re-painting the entire client area.
**			so we don't need to erase the background
**-----------------------------------------------------------------------------
*/

LRESULT OnEraseBackground (HWND hWindow, WPARAM wParam, LPARAM lParam)
{
    LPD3DWindow lpd3dWindow;
	RECT        rTemp, rSurf, rClient;

	// Get D3D window pointer
	lpd3dWindow =  (LPD3DWindow)GetWindowLong (hWindow, GWL_USERDATA);
	if (! lpd3dWindow)
		return 0L;

	if ((lpd3dWindow->isValid ()) && (! lpd3dWindow->isPaused ()))
	{
		GetClientRect (hWindow, &rClient);
		lpd3dWindow->GetSurfaceRect (rSurf);

		// Does surface rect contain the client rectangle?
		if (IntersectRect (&rTemp, &rClient, &rSurf))
		{
			if (! EqualRect (&rTemp, &rClient))
			{
				// No, then allow system to erase the background for us
				return DefWindowProc (hWindow, WM_ERASEBKGND, wParam, lParam);
			}
		}
	}

	// Success
	// Tell system we erased background, even though we didn't
    return 1L;
} // End OnEraseBackground
  

  
/*
**-----------------------------------------------------------------------------
**  Name:       OnGetMinMaxInfo
**  Purpose:    Set Minimum, Maximum Window sizes
**-----------------------------------------------------------------------------
*/

LRESULT OnGetMinMaxInfo (HWND hWindow, LPMINMAXINFO lpmmi)
{
	RECT		 rMin;
	DWORD		 dwStyle, dwStyleEx;
	HMENU		 hMenu;
	BOOL		 fMenu;
    LPD3DWindow  lpd3dWindow;

	// Get D3D window pointer
	lpd3dWindow =  (LPD3DWindow)GetWindowLong (hWindow, GWL_USERDATA);
	if (! lpd3dWindow)
		return 0L;

	// Get Window Style
	dwStyle   = GetWindowLong (hWindow, GWL_STYLE);
	dwStyleEx = GetWindowLong (hWindow, GWL_EXSTYLE);
	hMenu	  = GetMenu (hWindow);
	fMenu     = (hMenu ? TRUE : FALSE);

	rMin.left	= 0;
	rMin.top	= 0;
	rMin.right  = MIN_WIN_SIZE_X;
	rMin.bottom	= MIN_WIN_SIZE_Y;

	AdjustWindowRectEx (&rMin, dwStyle, fMenu, dwStyleEx);

 	lpmmi->ptMinTrackSize.x = rMin.right - rMin.left;
	lpmmi->ptMinTrackSize.y = rMin.bottom  - rMin.top;

	return 0L;
} // End OnGetMinMaxInfo



/*
**-----------------------------------------------------------------------------
**  Name:       OnIdle
**  Purpose:    Animate while system is idle
**-----------------------------------------------------------------------------
*/

void OnIdle (HWND hWindow)
{
    HRESULT hResult;
    LPD3DWindow  lpd3dWindow;

	// Get D3D window pointer
	lpd3dWindow =  (LPD3DWindow)GetWindowLong (hWindow, GWL_USERDATA);
	if (! lpd3dWindow)
		return;

    //
    // Only animate if we are the foreground app, we aren't suspended
    // and we have completed initialization.
    //
    //
    // Only animate if we are the foreground app, we aren't suspended
    // and we have completed initialization.
    //
	if (! lpd3dWindow->isActive () || 
		(lpd3dWindow->isPaused ()) ||
		(! lpd3dWindow->isValid ()))
		return;

	hResult = lpd3dWindow->DrawFrame ();
    if (FAILED (hResult))
		return;

    return;
} // End OnIdle



/*
**-----------------------------------------------------------------------------
**  Name:       OnMove
**  Purpose:    Move window
**-----------------------------------------------------------------------------
*/

LRESULT OnMove (HWND hWindow, INT nX, INT nY)
{
    HRESULT hResult;
    LPD3DWindow lpd3dWindow;

	// Get D3D Window pointer
	lpd3dWindow =  (LPD3DWindow)GetWindowLong (hWindow, GWL_USERDATA);
	if (! lpd3dWindow)
		return 0L;

    /*
     * No action if the device has not yet been created or if we are
     * suspended.
     */
    if (! lpd3dWindow->isPaused() || ! lpd3dWindow->isValid ())
    {
		// Keep the D3D info in synch with the change
		hResult = lpd3dWindow->Move (nX, nY);
        if (FAILED (hResult))
            return 0L;

        // Repaint the client area.
        hResult = lpd3dWindow->DrawFrame ();
        if (FAILED (hResult))
            return 0L;
    }

    // Success
    return 0L;
} // End OnMove

  

/*
**-----------------------------------------------------------------------------
**  Name:       OnPaint
**  Purpose:	Paint the window
**-----------------------------------------------------------------------------
*/

LRESULT OnPaint (HWND hWindow, HDC hdc, LPPAINTSTRUCT lpps)
{
    HRESULT hResult;
	LPD3DWindow lpd3dWindow;

	// Get D3D Window pointer
	lpd3dWindow =  (LPD3DWindow)GetWindowLong (hWindow, GWL_USERDATA);
	if (! lpd3dWindow)
	{
        PaintPaused (hWindow, hdc);
		return 0L;
	}

    if (lpd3dWindow->isActive () && 
		!lpd3dWindow->isPaused () && 
		lpd3dWindow->isValid())
    {
        //
        // NOTE: DrawFrame() re-renders the scene as well as blitting the
        // result to the primary. As all we really want to do here is
        // repaint the client area we don't really need to re-render -
        // just re-blit. For this simple sample this inefficiency
        // doesn't matter but for real applications not re-rendering
        // may be a useful optimization.
        //
        hResult = lpd3dWindow->DrawFrame ();
        if (FAILED (hResult))
            return 0L;
    }
    else
    {
        //
        // Show the suspended image if we are not active, 
        // or paused, or if we have not yet created the device.
        //
        PaintPaused (hWindow, hdc);
    }

    return 0L;
} // End OnPaint


  
/*
**-----------------------------------------------------------------------------
**  Name:		OnPause
**  Purpose:	Pause/Unpause app
**-----------------------------------------------------------------------------
*/

void OnPause (HWND hWindow, BOOL fPause)
{
	LPD3DWindow lpd3dWindow;

	// Get D3D Window pointer
	lpd3dWindow =  (LPD3DWindow)GetWindowLong (hWindow, GWL_USERDATA);
	if (! lpd3dWindow)
		return;

	lpd3dWindow->Pause (fPause);
} // End OnPause



/*
**-----------------------------------------------------------------------------
**  Name:       OnSize
**  Purpose:	Resize main window
**-----------------------------------------------------------------------------
*/

LRESULT OnSize (HWND hWindow, INT nW, INT nH)
{
    HRESULT       hResult;
    LPD3DWindow  lpd3dWindow;

	// Get D3D window pointer
	lpd3dWindow =  (LPD3DWindow)GetWindowLong (hWindow, GWL_USERDATA);
	if (! lpd3dWindow)
		return 0L;

    // Check if we are paused 
    if (! lpd3dWindow->isPaused ())
    {
		// Resize D3D surfaces
		hResult = lpd3dWindow->Resize (nW, nH);
        if (FAILED (hResult))
            return 0L;

        //
        // Render at the new size and show the results
        // in the main window's client area.
        //
        hResult = lpd3dWindow->DrawFrame ();
        if (FAILED (hResult))
            return 0L;
    }

    // Success
    return 0L;
} // End OnSize


  
/*
**-----------------------------------------------------------------------------
**  Name:       OnD3DInit
**  Purpose:	Notification that associated D3D Window object
**				has successfully initialized
**-----------------------------------------------------------------------------
*/

LRESULT OnD3DInit (HWND hWindow, LPD3DWindow lpd3dWindow)
{
	if ((! lpd3dWindow) || (! lpd3dWindow->isValid ()))
	{
		// Error, something went wrong
		return 0L;
	}

	// Save the pointer to the D3D Window object
	SetWindowLong (hWindow, GWL_USERDATA, (long)(void *)lpd3dWindow);

	// Make sure we are properly marked as active/inactive
	HWND hActive = GetActiveWindow ();
	if (hActive == hWindow)
		lpd3dWindow->turnActiveOn ();
	else
		lpd3dWindow->turnActiveOff ();

	// Success
	return 0L;
} // End OnD3DInit


  
/*
**-----------------------------------------------------------------------------
**  Name:       OnD3DFini
**  Purpose:	Notification that the D3D window object
**				is cleaning up.
**-----------------------------------------------------------------------------
*/

LRESULT OnD3DFini (HWND hWindow, LPD3DWindow lpd3dWindow)
{
	// Set our window pointer to NULL
	// so we don't attempt to misuse it later.
	SetWindowLong (hWindow, GWL_USERDATA, 0L);
	
	// Success
	return 0L;
} // End OnD3DFini



/*
**-----------------------------------------------------------------------------
**  Name:       OnD3DChangeDriver
**  Purpose:	Notification that our associated D3D Window object
**				has changed it's DD Driver.
**  Notes:		This is a good time to update our Menus
**-----------------------------------------------------------------------------
*/

LRESULT OnD3DChangeDriver (HWND hWindow)
{
	// Success
	return 0L;
} // End OnD3DChangeDriver

  

  
/*
**-----------------------------------------------------------------------------
**  Name:       OnD3DChangeMode
**  Purpose:	Notification that our associated D3D Window object
**				has changed it's mode.
**  Notes:		
**		1. This is probably caused by the user changing the Desktop mode
**		2. This is a good time to update our Menus
**-----------------------------------------------------------------------------
*/

LRESULT OnD3DChangeMode (HWND hWindow)
{
	// Success
	return 0L;
} // End OnD3DChangeMode


  
/*
**-----------------------------------------------------------------------------
**  Name:       OnD3DChangeDevice
**  Purpose:	Notification that our associated D3D Window object
**				has changed it's D3D device.
**  Notes:		This is a good time to update our Menus
**-----------------------------------------------------------------------------
*/

LRESULT OnD3DChangeDevice (HWND hWindow)
{
	// Success
	return 0L;
} // End OnD3DChangeDevice


  
/*
**-----------------------------------------------------------------------------
**  Name:       PaintPaused
**  Purpose:	Paint the window as Paused
**  Notes:      
**
**  1.  We show the paused state by drawing a text string
**      in the client area of the window.
**
**-----------------------------------------------------------------------------
*/

void PaintPaused (HWND hWindow, HDC hdc)
{
    HPEN     hOldPen;
    HBRUSH   hOldBrush;
    COLORREF crOldTextColor;
    INT      oldMode;
    INT      x;
    INT      y;
    SIZE     size;
    RECT     rect;
    INT      nStrLen;

    //
    // Black background.
    //
    hOldPen   = (HPEN)SelectObject (hdc, GetStockObject (NULL_PEN));
    hOldBrush = (HBRUSH)SelectObject (hdc, GetStockObject (BLACK_BRUSH));

    //
    // White text.
    //
    oldMode = SetBkMode (hdc, TRANSPARENT);
    crOldTextColor = SetTextColor (hdc, RGB(255, 255, 255));

    // 
    GetClientRect (hWindow, &rect);

    //
    // Clear the client area.
    //
    Rectangle (hdc, rect.left, rect.top, rect.right + 1, rect.bottom + 1);

    //
    // Draw the string centered in the client area.
    //
    nStrLen = strlen (g_szPaused);
    GetTextExtentPoint32 (hdc, g_szPaused, nStrLen, &size);
    x = (rect.right  - size.cx) / 2;
    y = (rect.bottom - size.cy) / 2;
    TextOut (hdc, x, y, g_szPaused, nStrLen);

    // Cleanup
    SetTextColor (hdc, crOldTextColor);
    SetBkMode (hdc, oldMode);

    SelectObject (hdc, hOldBrush);
    SelectObject (hdc, hOldPen);
} // End PaintPaused



  
/*
**-----------------------------------------------------------------------------
**	Dialog Functions
**-----------------------------------------------------------------------------
*/

/*
**-----------------------------------------------------------------------------
**  Name:       DlgDriversInit
**  Purpose:    Set up Drivers for dialog 
**  Notes:		Shows list of current Drivers
**-----------------------------------------------------------------------------
*/

BOOL DlgDriversInit (HWND hDlg)
{
	LPChangeDDInfo	lpChange;
	LPDDDrvInfo		lpDriver;
	LPDDDrvInfo		lpCurr, lpNext;
	DWORD			dwIndex;
	LPGUID			lpGuidDD;

	// Check Parameters
	lpChange = (LPChangeDDInfo)(void *)GetWindowLong (hDlg, DWL_USER);
	if (! lpChange)
		return FALSE;

	lpDriver = lpChange->lpDrvNew;

	// Validate Driver
	if (! lpDriver)
		lpGuidDD = NULL;
	else
		lpGuidDD = lpDriver->GetGuid ();
	lpDriver = ValidateDriver (lpGuidDD);
	if (! lpDriver)
		return FALSE;
	
	// Dump Driver list to Combo Box
	dwIndex = 0;
	lpCurr = DDDrvMgr::g_lpDriverRoot;
	while (lpCurr)
	{
		TCHAR szBuff[80];
		DWORD dwNew;
		LPGUID lpGuidDD;

		lpNext = lpCurr->lpNext;

		// Hack: Do a Quick check for the 3Dfx Voodoo driver
		//		 which doesn't support windowed mode
		lpGuidDD = lpCurr->GetGuid ();
		if (lpGuidDD)
		{
			if (*lpGuidDD == guid3DfxVoodoo)
			{
				// Don't add 3Dfx Voodoo driver.
				// This is a windowed app and it isn't supported
				lpCurr = lpNext;
				continue;
			}
		}

		if (lpCurr->isPrimary ())
			wsprintf (szBuff, TEXT("%s (Primary)"), lpCurr->szName);
		else
			wsprintf (szBuff, TEXT("%s"), lpCurr->szName);

		// Add String to Combo Box
		dwNew = SendDlgItemMessage (hDlg, IDC_DRIVERS, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)szBuff);

		// Set up pointer to driver for this item
		SendDlgItemMessage (hDlg, IDC_DRIVERS, CB_SETITEMDATA, (WPARAM)dwNew, (LPARAM)(void *)lpCurr);

		// Is it the current Driver
		if (lpDriver == lpCurr)
		{
			// Set as our current selection
			SendDlgItemMessage (hDlg, IDC_DRIVERS, CB_SETCURSEL, (WPARAM)dwNew, 0L);
		}

		lpCurr = lpNext;
	}

	// Success
	return TRUE;
} // End DlgDriversInit
    


/*
**-----------------------------------------------------------------------------
**  Name:       DlgDevicesInit
**  Purpose:    Set up Devices for dialog 
**  Notes:		Shows list of current Devices
**-----------------------------------------------------------------------------
*/

BOOL DlgDevicesInit (HWND hDlg)
{
	LPChangeDDInfo	lpChange;
	LPDDDrvInfo		lpDriver;
	LPD3DDevInfo	lpDevice;
	LPD3DDevInfo	lpCurr, lpNext;
	DWORD			dwIndex;
	LPGUID			lpGuidD3D;

	// Check Parameters
	lpChange = (LPChangeDDInfo)(void *)GetWindowLong (hDlg, DWL_USER);
	if (! lpChange)
		return FALSE;

	lpDriver = lpChange->lpDrvNew;
	if (! lpDriver)
		return FALSE;

	lpDevice = lpChange->lpDevNew;

	// Validate Device
	if (! lpDevice)
		lpGuidD3D = NULL;
	else
		lpGuidD3D = &(lpDevice->guid);
	lpDevice = ValidateDevice (lpDriver, lpGuidD3D, NULL);
	if (! lpDevice)
		return FALSE;
	
	// Dump Device list to Combo Box
	dwIndex = 0;
	lpCurr = lpDriver->lpDeviceRoot;
	while (lpCurr)
	{
		TCHAR szBuff[80];
		DWORD dwNew;

		lpNext = lpCurr->lpNext;

		// Get Device String
		wsprintf (szBuff, TEXT("%s"), lpCurr->szName);

		// Add String to Combo Box
		dwNew = SendDlgItemMessage (hDlg, IDC_DEVICES, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)szBuff);

		// Set up pointer to device for this item
		SendDlgItemMessage (hDlg, IDC_DEVICES, CB_SETITEMDATA, (WPARAM)dwNew, (LPARAM)(void *)lpCurr);

		// Is it the current device
		if (lpDevice == lpCurr)
		{
			// Set as our current selection
			SendDlgItemMessage (hDlg, IDC_DEVICES, CB_SETCURSEL, (WPARAM)dwNew, 0L);
		}

		lpCurr = lpNext;
	}

	// Success
	return TRUE;
} // End DlgDevicesInit



/*
**-----------------------------------------------------------------------------
**  Name:       CompareModes
**  Purpose:    Comparision function used with Quick sort 
**				to get sorted list of modes
**-----------------------------------------------------------------------------
*/

int _cdecl CompareModes (const void * element1, const void * element2) 
{
	LPDDModeInfo lpMode1;
	LPDDModeInfo lpMode2;
	DWORD w1, h1, bpp1, refresh1;
	DWORD w2, h2, bpp2, refresh2;
	int   iCompare = 0;

    lpMode1 = *((LPDDModeInfo *)element1);
    lpMode2 = *((LPDDModeInfo *)element2);

	// Handle Null pointers
	if ((! lpMode1) && (! lpMode2))
		return 0;
	if ((lpMode1) && (! lpMode2))
		return -1;
	if ((! lpMode2) && (lpMode2))
		return 1;

	// Get Mode Data
	lpMode1->GetMode (w1, h1, bpp1, refresh1);
	lpMode2->GetMode (w2, h2, bpp2, refresh2);

	// Sort first on BPP then width then height
    if (bpp1 < bpp2)
		iCompare = -1;
    else if (bpp1 > bpp2)
		iCompare = 1;
    else if (w1 < w2)
		iCompare = -1;
    else if (w1 > w2)
		iCompare = 1;
    else if (h1 < h2)
		iCompare = -1;
    else if (h1 > h2)
		iCompare = 1;

	// Equality
    return iCompare;
} // End CompareModes


  
/*
**-----------------------------------------------------------------------------
**  Name:       DlgModesInit
**  Purpose:    Set up Modes for dialog 
**  Notes:		Shows list of current modes, compatible with the current 
**				device.  This list is displayed in sorted order (bpp, w, h)
**-----------------------------------------------------------------------------
*/

BOOL DlgModesInit (HWND hDlg)
{
	LPChangeDDInfo	lpChange;
	LPDDDrvInfo		lpDriver;
	LPD3DDevInfo	lpDevice;
	LPDDModeInfo	lpModeCurr, lpModeRoot, lpCurr, lpNext;
	DWORD			cModes;
	DWORD			cbSize;
	DWORD			dwIndex;
	LPDDModeInfo *	lpModes;

	// Check Parameters
	lpChange = (LPChangeDDInfo)(void *)GetWindowLong (hDlg, DWL_USER);
	if (! lpChange)
		return FALSE;

	lpDriver   = lpChange->lpDrvNew;
	lpDevice   = lpChange->lpDevNew;
	lpModeCurr = lpChange->lpModeNew;

	if (! lpDriver)
		return FALSE;

	if (! lpDevice)
	{
		lpDevice = ValidateDevice (lpDriver, NULL, NULL);
		if (! lpDevice)
			return FALSE;
	}

	lpModeRoot = lpDriver->lpModeRoot;
	if (! lpModeRoot)
		return FALSE;

	cModes = lpDriver->countModes ();
	if (! cModes)
		return FALSE;
	
	if (! lpModeCurr)
	{
		lpModeCurr = ValidateMode (lpDriver, 640, 480, 16, 0, lpDevice);
	}

	// Get memory for Mode list
	cbSize = cModes * sizeof (LPDDModeInfo);
	lpModes = (LPDDModeInfo *) malloc (cbSize);
	if (! lpModes)
		return FALSE;

	// Create Mode List
	dwIndex = 0;
	lpCurr = lpModeRoot;
	while (lpCurr)
	{
		lpNext = lpCurr->lpNext;

		lpModes[dwIndex] = lpCurr;

		dwIndex++;

		lpCurr = lpNext;
	}

	// Sort Mode list
    qsort ((void *)lpModes, (size_t)cModes, sizeof(LPDDModeInfo), CompareModes);

	// Dump Mode list to Combo Box
	for (dwIndex = 0; dwIndex < cModes; dwIndex++)
	{
		// Make sure mode is supported by D3D device
		if ((lpModes[dwIndex]) && 
			(lpModes[dwIndex]->ModeSupported (lpDevice)))
		{
			TCHAR szBuff[80];
			DWORD w, h, bpp, refresh;
			DWORD dwNew;

			lpModes[dwIndex]->GetMode (w, h, bpp, refresh);
			
			// Set up Mode String
			if (refresh)
				wsprintf (szBuff, TEXT("%4d x %4d x %4d (%4d Hz)"), 
					      w, h, bpp, refresh);
			else
				wsprintf (szBuff, TEXT("%4d x %4d x %4d"), 
					      w, h, bpp);

			// Add String to Combo Box
			dwNew = SendDlgItemMessage (hDlg, IDC_MODES, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)szBuff);

			// Set up pointer to Mode Info for this item
			SendDlgItemMessage (hDlg, IDC_MODES, CB_SETITEMDATA, (WPARAM)dwNew, (LPARAM)(void *)lpModes[dwIndex]);

			// Is it the current Mode 
			if (lpModeCurr == lpModes[dwIndex])
			{
				// Set as our current selection
				SendDlgItemMessage (hDlg, IDC_MODES, CB_SETCURSEL, (WPARAM)dwNew, 0L);
			}
		}
	}	

	// Cleanup Memory
	free (lpModes);
	lpModes = NULL;

	// Success
	return TRUE;
} // End DlgModesInit



  
/*
**-----------------------------------------------------------------------------
**  Name:       DlgGetDriver
**  Purpose:    Get current driver selection
**-----------------------------------------------------------------------------
*/

LPDDDrvInfo DlgGetDriver (HWND hDlg)
{
	DWORD dwIndex = SendDlgItemMessage (hDlg, IDC_DRIVERS, CB_GETCURSEL, 0, 0);
	if (dwIndex != CB_ERR)
	{
		// Get pointer to driver
		LPDDDrvInfo lpDriver = (LPDDDrvInfo) SendDlgItemMessage (hDlg, 
							  								     IDC_DRIVERS, 
																 CB_GETITEMDATA, 
																 (WPARAM)dwIndex, 
																 (LPARAM)0);
		return lpDriver;
	}			

	// Failure
	return NULL;
} // End DlgGetDriver


  
/*
**-----------------------------------------------------------------------------
**  Name:       DlgGetDevice
**  Purpose:    Get current device selection
**-----------------------------------------------------------------------------
*/

LPD3DDevInfo DlgGetDevice (HWND hDlg)
{
	DWORD dwIndex = SendDlgItemMessage (hDlg, IDC_DEVICES, CB_GETCURSEL, 0, 0);
	if (dwIndex != CB_ERR)
	{
		// Get pointer to device
		LPD3DDevInfo lpDevice = (LPD3DDevInfo) SendDlgItemMessage (hDlg, 
							  								       IDC_DEVICES, 
																   CB_GETITEMDATA, 
																   (WPARAM)dwIndex, 
																   (LPARAM)0);
		return lpDevice;
	}			

	// Failure
	return NULL;
} // End DlgGetDevice


  
/*
**-----------------------------------------------------------------------------
**  Name:       DlgGetMode
**  Purpose:    Get current mode selection
**-----------------------------------------------------------------------------
*/

LPDDModeInfo DlgGetMode (HWND hDlg)
{
	DWORD dwIndex = SendDlgItemMessage (hDlg, IDC_MODES, CB_GETCURSEL, 0, 0);
	if (dwIndex != CB_ERR)
	{
		// Get pointer to device
		LPDDModeInfo lpMode = (LPDDModeInfo) SendDlgItemMessage (hDlg, 
						    								     IDC_MODES, 
																 CB_GETITEMDATA, 
																 (WPARAM)dwIndex, 
																 (LPARAM)0);
		return lpMode;
	}			

	// Failure
	return NULL;
} // End DlgGetMode

  


  
/*
**-----------------------------------------------------------------------------
**  Name:       OnChangeDriver
**  Purpose:    Allows user to choose a new Driver from dialog
**	Notes:		User can also choose a new device and mode
**-----------------------------------------------------------------------------
*/

void OnChangeDriver (HWND hWindow, int idDialog)
{
	HINSTANCE		hInstance;
	int				fResult;
	ChangeDDInfo	changeInfo;
	LPD3DWindow		lpd3dWindow;

	// Get application instance
	hInstance = (HINSTANCE) GetWindowLong (hWindow, GWL_HINSTANCE);
	if (! hInstance)
		return;

	// Get D3D Window pointer
	lpd3dWindow =  (LPD3DWindow)GetWindowLong (hWindow, GWL_USERDATA);
	if (! lpd3dWindow)
		return;

	// Setup Change info
	changeInfo.lpDrvOrig	= lpd3dWindow->GetDriverInfo ();
	changeInfo.lpDrvNew		= changeInfo.lpDrvOrig;

	changeInfo.lpDevOrig	= lpd3dWindow->GetDeviceInfo ();
	changeInfo.lpDevNew		= changeInfo.lpDevOrig;

	changeInfo.lpModeOrig	= lpd3dWindow->GetModeInfo ();
	changeInfo.lpModeNew	= changeInfo.lpModeOrig;


    // Pause App
    OnPause (hWindow, TRUE);

    // Do Change Mode Dialog here
    fResult = DialogBoxParam (hInstance, MAKEINTRESOURCE (idDialog), 
							  hWindow, (DLGPROC)ChangeDriverProc,
							  (LPARAM)(void *)&changeInfo);

    // UnPause app
    OnPause (hWindow, FALSE);

	// Did user request a change ?!?
	if (fResult == TRUE)
	{
		LPGUID lpGuidDD, lpGuidD3D;

		if (changeInfo.lpDrvOrig != changeInfo.lpDrvNew)
		{
			if (changeInfo.lpDrvNew)
				lpGuidDD = changeInfo.lpDrvNew->GetGuid ();
			else
				lpGuidDD = NULL;

			lpd3dWindow->ChangeDriver (lpGuidDD, changeInfo.lpDevNew);
		}
		else if (changeInfo.lpDevOrig != changeInfo.lpDevNew)
		{
			if (changeInfo.lpDevNew)
				lpGuidD3D = &(changeInfo.lpDevNew->guid);
			else
				lpGuidD3D = NULL;

			lpd3dWindow->ChangeDevice (lpGuidD3D);
		}
	}
} // End OnChangeDriver
  


/*
**-----------------------------------------------------------------------------
**  Name:       ChangeDriverProc
**  Purpose:    handles messages for Change Driver,
**				D3D device, and mode dialog boxes
**-----------------------------------------------------------------------------
*/

BOOL CALLBACK ChangeDriverProc(
    HWND hDlg,		// handle to dialog box
    UINT uiMsg,		// message
    WPARAM wParam,	// first message parameter
    LPARAM lParam) 	// second message parameter
{
	BOOL			fChanged;
	LPChangeDDInfo  lpChange;
	LPDDDrvInfo		lpDriver;
	LPDDModeInfo	lpMode;
	LPD3DDevInfo	lpDevice;

	switch (uiMsg)
	{
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
			// Get Change Info
			lpChange = (LPChangeDDInfo) GetWindowLong (hDlg, DWL_USER);
			if (! lpChange)
				EndDialog (hDlg, FALSE);

			fChanged = FALSE;

			// Get New Driver
			lpDriver = DlgGetDriver (hDlg);
			if ((lpDriver) && (lpDriver != lpChange->lpDrvOrig))
			{
				fChanged = TRUE;
				lpChange->lpDrvNew = lpDriver;
			}
			else
				lpChange->lpDrvNew = lpChange->lpDrvOrig;

			// Get New Device
			lpDevice = DlgGetDevice (hDlg);
			if ((lpDevice) && (lpDevice != lpChange->lpDevOrig))
			{
				fChanged = TRUE;
				lpChange->lpDevNew = lpDevice;
			}
			else
				lpChange->lpDevNew = lpChange->lpDevOrig;
			
			// Get New Mode
			lpMode = DlgGetMode (hDlg);
			if ((lpMode) && (lpMode != lpChange->lpModeOrig))
			{
				fChanged = TRUE;
				lpChange->lpModeNew = lpMode;
			}
			else
				lpChange->lpModeNew = lpChange->lpModeOrig;

			// Return success/failure
			EndDialog (hDlg, fChanged);
			break;

		case IDCANCEL:
			EndDialog (hDlg, FALSE);
			break;

		case IDC_DRIVERS:
			switch (HIWORD (wParam))
			{
			case CBN_SELENDOK:
				// User has changed the current driver
				lpChange = (LPChangeDDInfo) GetWindowLong (hDlg, DWL_USER);
			
				// Check if user has changed the Driver
				lpDriver = DlgGetDriver (hDlg);
				if ((lpDriver) && (lpDriver != lpChange->lpDrvNew))
				{
					lpChange->lpDrvNew = lpDriver;
					lpChange->lpDevNew = NULL;	// Pick a new device
					lpChange->lpModeNew = NULL;	// Pick a new mode
					
					// Update the Device list
					SendDlgItemMessage (hDlg, IDC_DEVICES, CB_RESETCONTENT, 0, 0);
					DlgDevicesInit (hDlg);

					// Update the Mode list
					SendDlgItemMessage (hDlg, IDC_MODES, CB_RESETCONTENT, 0, 0);
					DlgModesInit (hDlg);
				}
				break;
			}
			break;

		case IDC_DEVICES:
			switch (HIWORD (wParam))
			{
			case CBN_SELENDOK:
				// User has changed the current device
				lpChange = (LPChangeDDInfo) GetWindowLong (hDlg, DWL_USER);
				
				// Check if user has changed the device
				lpDevice = DlgGetDevice (hDlg);
				if ((lpDevice) && (lpDevice != lpChange->lpDevNew))
				{
					lpChange->lpDevNew = lpDevice;
					
					// Update the Mode list
					SendDlgItemMessage (hDlg, IDC_MODES, CB_RESETCONTENT, 0, 0);
					DlgModesInit (hDlg);
				}
				break;
			}
			break;

		case IDC_MODES:
			switch (HIWORD (wParam))
			{
			case CBN_SELENDOK:
				// User has changed the current mode
				lpChange = (LPChangeDDInfo) GetWindowLong (hDlg, DWL_USER);
				
				// Check if user has changed the Mode
				lpMode = DlgGetMode (hDlg);
				if ((lpMode) && (lpMode != lpChange->lpModeNew))
				{
					lpChange->lpModeNew = lpMode;
				}
				break;
			}
			break;
		}
		break;

    case WM_INITDIALOG:
		// Save pointer to ChangeInfo
		SetWindowLong (hDlg, DWL_USER, (long)lParam);

		// Set up the current driver, device, and mode lists
		if (GetDlgItem (hDlg, IDC_DRIVERS))
			if (! DlgDriversInit (hDlg))	
				return FALSE;

		if (GetDlgItem (hDlg, IDC_DEVICES))
			if (! DlgDevicesInit (hDlg))
				return FALSE;

		if (GetDlgItem (hDlg, IDC_MODES))
			if (! DlgModesInit (hDlg))
				return FALSE;

		// Successful init
		return TRUE;
	}
	return FALSE;
} // End ChangeDriverProc 


/*
**-----------------------------------------------------------------------------
**  End of File
**-----------------------------------------------------------------------------
*/


