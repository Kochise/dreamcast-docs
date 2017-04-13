/*
**-----------------------------------------------------------------------------
**  Name:       D3DWin.cpp
**  Purpose:    Shows how to set up a windowed D3D framework
**  Notes:
**
**	Basic Initialization proceeds as follows:
**
**	1.  Enumerate all Driver, modes, D3D devices (see DrvMgr.cpp for details)
**	2.  Choose a starting driver, mode, D3D device
**			- default driver = primary display driver (lpGuidDD = NULL)
**			- default mode   = current desktop
**			- default device = D3D device compatible with desktop mode
**	3.  Validate driver, mode, D3D device
**	4.  Create interfaces (from DD driver)
**  5.  Set window (from associated window handle)
**  6.  Create DD/D3D interfaces (lpDD, lpDD2, lpD3D)
**  7.  Create Primary surface (primary palette, if necessary)
**			- Attach a clipper to primary surface
**  8.  Create Render surface 
**			- Render surface (and associated Z-buffer)
**			- D3D Device 
**			- D3D Viewport
**
**  After initialization is complete, we have the
**	following objects necessary for rendering:
**
**		lpDD2 - DirectDraw interface, used for creating texture surfaces
**		lpD3D - Direct3D interface, used for creating materials, lights, viewports
**		lpD3DDevice - D3D device (current material, current viewport, etc.)
**		lpViewport - current viewport
**		lpPrimary  - front buffer
**		lpRender   - render target
**
**  Copyright (c) 1995 - 1997 by Microsoft, all rights reserved
**-----------------------------------------------------------------------------
*/

/*
**-----------------------------------------------------------------------------
** Includes
**-----------------------------------------------------------------------------
*/

#include "D3DWin.h"
#include "WinProc.h"
#include "D3DScene.h"
#include "Debug.h"



/*
**-----------------------------------------------------------------------------
**	D3DWindow Methods
**-----------------------------------------------------------------------------
*/

/*
**-----------------------------------------------------------------------------
** Name:    D3DWindow::D3DWindow
** Purpose: Default Constructor
**-----------------------------------------------------------------------------
*/

D3DWindow::D3DWindow (void)
{
    ZeroMemory (this, sizeof(D3DWindow));
    this->dwSize = sizeof(D3DWindow);

	// Default to creating a z-buffer
	createZBufferOn ();	
} // End D3DWindow::D3DWindow ()


  
/*
**-----------------------------------------------------------------------------
** Name:    D3DWindow::~D3DWindow
** Purpose: Destructor
**-----------------------------------------------------------------------------
*/

D3DWindow::~D3DWindow (void)
{
	// Destroy all objects
    Fini ();

	// Mark all other pointers as invalid
	// In case user tries to reuse this object incorrectly
	lpCurrDriver = NULL;
	lpCurrMode	 = NULL;
	lpCurrDevice = NULL;
	hWindow		 = NULL;
	lpd3dScene	 = NULL;

} // End D3DWindow::~D3DWindow



/*
**-----------------------------------------------------------------------------
** Name:    D3DWindow::Create
** Purpose: Creates a D3DWindow 
**
** Basic Algorithm:
**	- Validate parameters
**	- Choose (and validate choices) for driver, mode, device
**	- Create Interfaces
**	- Set Window
**	- Create Primary surface (and palette)
**	- Create Render surface (and D3D device)
**-----------------------------------------------------------------------------
*/

HRESULT D3DWindow::Create (
	HWND   hWnd,		/* In:  Window */
	LPGUID lpGuidDD,	/* In:  Requested DirectDraw Device */
	DWORD  dwW,			/* In:	Requested Mode */
	DWORD  dwH,			
	DWORD  dwBPP,
	DWORD  dwRefresh,
	LPGUID lpGuidD3D,	/* In:  Requested D3D device */
	BOOL   fUseZBuffer, /* In:	Create Z-buffer */
	LPRECT lprSurf)		/* In:  requested surface size (NULL => use client area) */
{
    HRESULT         hResult;

    // Check parameters
	if ((! hWnd) || (! IsWindow (hWnd)))
	{
		REPORTERR (DDERR_INVALIDPARAMS);
		return DDERR_INVALIDPARAMS;
	}

	// Set Current Window
	hWindow = hWnd;

    // Set Use Z-Buffer On/Off
    if (fUseZBuffer)
        createZBufferOn ();
    else
        createZBufferOff ();

    // Choose Default Driver, Mode, device 
    hResult = ChooseDriverDefaults (lpGuidDD,
									dwW, dwH, dwBPP, dwRefresh,
									lpGuidD3D,
									FALSE,
									&lpCurrDriver,
									&lpCurrMode,
									&lpCurrDevice);
    if (FAILED (hResult))
        return hResult;
    
    // Create DD/D3D Interface objects
    hResult = InitInterfaces ();
    if (FAILED (hResult))
        return hResult;

	// Attach window to DD interface
	hResult = InitWindow ();
	if (FAILED (hResult))
		goto lblCLEANUP;

    // Create Primary Surface (and palette)
    hResult = InitPrimary ();
    if (FAILED (hResult))
        goto lblCLEANUP;

	// Get initial surface size
	if (lprSurf)
		rSurf = *lprSurf;
	else
		GetClientRect (hWindow, &rSurf);

	// Create the Render Surface (and D3D Device)
    hResult = InitRender ();
    if (FAILED (hResult))
        goto lblCLEANUP;

	// Notify the window of a successful initialization
	SendMessage (hWindow, D3DWIN_INIT, 0, (LPARAM)(void *)this);

    // Success
    return DD_OK;

lblCLEANUP:
    // Cleanup
    Fini ();

    return hResult;
} // End D3DWindow::Create



/*
**-----------------------------------------------------------------------------
** Name:    D3DWindow::Init
** Purpose: 
**
** Basic Algorithm:
**	- Validate driver, mode, device
**	- Create Interfaces
**	- Attach Window
**	- Create Primary surface (and palette)
**	- Create Render surface (and D3D device)
**
** Notes:
**		1.  Assumes that a valid window handle has already
**			been associated with this D3DWindow
**		2.  Assumes that driver, mode, device already choosen
**			- however if not, reasonable defaults will be choosen
**-----------------------------------------------------------------------------
*/

HRESULT D3DWindow::Init (void)
{
    HRESULT         hResult;

    // Check parameters
	if ((! hWindow) || (! IsWindow (hWindow)))
	{
		// Error, we absolutely need a valid window
		REPORTERR (DDERR_INVALIDPARAMS);
		return DDERR_INVALIDPARAMS;
	}

    // Validate Curr Driver, mode, device
	hResult = ValidateDefaults ();
	if (FAILED (hResult))
		return hResult;

    // Create DD/D3D Interface objects
    hResult = InitInterfaces ();
    if (FAILED (hResult))
		goto lblCLEANUP;

	// Attach the window to the DD interface
	hResult = InitWindow ();
	if (FAILED (hResult))
		goto lblCLEANUP;

    // Create Primary Surface (and palette)
    hResult = InitPrimary ();
    if (FAILED (hResult))
        goto lblCLEANUP;

	// Create Render surface (and D3D device)
    hResult = InitRender ();
    if (FAILED (hResult))
        goto lblCLEANUP;

	// Notify the window of a successful initialization
	SendMessage (hWindow, D3DWIN_INIT, 0, (LPARAM)(void *)this);

    // Success
    return DD_OK;

lblCLEANUP:
    // Cleanup
    Fini ();
    return hResult;
} // End D3DWindow::Init



/*
**-----------------------------------------------------------------------------
** Name:    D3DWindow::Fini
** Purpose: Destroys a D3DWindow
**-----------------------------------------------------------------------------
*/

HRESULT D3DWindow::Fini (void)
{
	// Notify the window that we are cleaning up
	SendMessage (hWindow, D3DWIN_FINI, 0, (LPARAM)(void *)this);

	// Cleanup
    FiniRender ();
    FiniPrimary ();
//	FiniWindow ();
    FiniInterfaces ();

	// Success
	return DD_OK;
} // End D3DWindow::Fini


  
  
/*
**-----------------------------------------------------------------------------
** Name:    D3DWindow::ValidateDefaults
** Purpose: Verify's current driver, mode, and device
** Notes:   
**
**	1.  Rather than fail completely, this will pick new defaults
**      if the current defaults don't work.
**
**-----------------------------------------------------------------------------
*/

HRESULT D3DWindow::ValidateDefaults (void)
{
	LPGUID			lpGuidDD, lpGuidD3D;
	HRESULT			hResult;
    LPDDDrvInfo		lpDrvNew;
	LPDDModeInfo	lpModeNew;
	LPD3DDevInfo	lpDevNew;

	// Initialize Driver Manager, if necessary
	if (! DDDrvMgr::isInitialized ())
	{
		hResult = DDDrvMgr::Init ();
		if (FAILED (hResult))
			return DDERR_INVALIDPARAMS;
	}
    
    // Get DD Guid
	if (lpCurrDriver)
		lpGuidDD = lpCurrDriver->GetGuid ();
	else
		lpGuidDD = NULL;

	// Get D3D Guid
	if (lpCurrDevice)
		lpGuidD3D = &(lpCurrDevice->guid);
	else
		lpGuidD3D = NULL;

	// Get Driver corresponding to DD Guid
    lpDrvNew = ValidateDriver (lpGuidDD);
	if (! lpDrvNew)
    {
        // Error, invalid DD Guid
		REPORTERR (DDERR_INVALIDPARAMS);
        return DDERR_INVALIDPARAMS;
    }

	// Get Desktop mode and compatible D3D device
	if (! GetDesktopMode (lpDrvNew, lpGuidD3D, &lpModeNew, &lpDevNew))
	{
		REPORTERR (DDERR_GENERIC);
		return DDERR_GENERIC;
	}

	// Note:  Instead of complaining let's go ahead
	//		  and use the new defaults
	// Save new defaults
	lpCurrDriver = lpDrvNew;
	lpCurrMode	 = lpModeNew;
	lpCurrDevice = lpDevNew;

    // Success
    return DD_OK;
} // End D3DWindow::ValidateDefaults


  
/*
**-----------------------------------------------------------------------------
** Name:    D3DWindow::CreateInterfaces
** Purpose: Creates DD/D3D interfaces from specified Guid
**-----------------------------------------------------------------------------
*/

HRESULT D3DWindow::CreateInterfaces (LPGUID lpDDGuid)
{
	LPDDDrvInfo lpDrvNew;
	HRESULT		hResult;

	// Verify Guid
	lpDrvNew = ValidateDriver (lpDDGuid);
	if (! lpDrvNew)
	{
		REPORTERR (DDERR_GENERIC);
		return DDERR_GENERIC;
	}

	lpCurrDriver = lpDrvNew;

	hResult = D3DWindow::InitInterfaces ();
	if (FAILED (hResult))
		return hResult;

	// Success
	return DD_OK;
} // End D3DWindow::CreateInterfaces

  

/*
**-----------------------------------------------------------------------------
** Name:    D3DWindow::InitInterfaces
** Purpose: Creates DD/D3D interfaces
**-----------------------------------------------------------------------------
*/

HRESULT D3DWindow::InitInterfaces (void)
{
    HRESULT         hResult;
    LPGUID          lpGuid;

    // Do we have a current DD Driver
    if (! lpCurrDriver)
    {
		// Try to grab the Primary DD driver instead
		lpCurrDriver = ValidateDriver (NULL);
		if (! lpCurrDriver)
		{
			REPORTERR (DDERR_GENERIC);
			return DDERR_GENERIC;
		}
    }

    // Get DD Guid
    lpGuid = lpCurrDriver->GetGuid ();
    
    // Create DD interface
    hResult = DirectDrawCreate (lpGuid, &lpDD, NULL);
    if (FAILED (hResult))
    {
        // Error
		REPORTERR (hResult);
		goto lblERROR;
    }

    // Get DD2 interface
    hResult = lpDD->QueryInterface ((REFIID)IID_IDirectDraw2, (void **)&lpDD2);
    if (FAILED (hResult))
    {
        // Error
		REPORTERR (hResult);
        goto lblERROR;
    }

    // Get D3D interface
    hResult = lpDD2->QueryInterface ((REFIID)IID_IDirect3D2, (void **)&lpD3D);
    if (FAILED (hResult))
    {
        // Error
		REPORTERR (hResult);
        goto lblERROR;
    }

	// Mark this stage as done
	turnValidInterfaceOn ();

    // Success
    return DD_OK;

lblERROR:
    // Failure
    FiniInterfaces ();

    return hResult;
} // End InitInterfaces



  
/*
**-----------------------------------------------------------------------------
** Name:    D3DWindow::FiniInterfaces
** Purpose: Destroys DD/D3D interfaces
**-----------------------------------------------------------------------------
*/

HRESULT D3DWindow::FiniInterfaces (void)
{
	// Mark this stage as invalid
	turnValidInterfaceOff ();

    // Release Direct3D Interface
    if (lpD3D)
    {
        lpD3D->Release ();
        lpD3D = NULL;
    }

    // Release DirectDraw2 Interface
    if (lpDD2)
    {
        lpDD2->Release ();
        lpDD2 = NULL;
    }

    // Release DirectDraw Interface
    if (lpDD)
    {
        lpDD->Release ();
        lpDD = NULL;
    }

	// Success
	return DD_OK;
} // End D3DWindow::FiniInterfaces



/*
**-----------------------------------------------------------------------------
**	Name:		D3DWindow::InitWindow
**	Purpose:	Attaches Window to Direct Draw Interface
**	Notes:		Assumes window handle already associated with this D3DWindow.
**-----------------------------------------------------------------------------
*/

HRESULT D3DWindow::InitWindow (void)
{
	HRESULT hResult;
	DWORD	dwFlags;

	// Check Initialization
	if ((! hWindow) || (! IsWindow (hWindow)))
	{
		// Error, we have to have an associated window to continue
		REPORTERR (DDERR_GENERIC);
		return DDERR_GENERIC;
	}

    // Get Cooperative Flags
    dwFlags = DDSCL_NORMAL;

    // Set Cooperative Level
    hResult = lpDD2->SetCooperativeLevel (hWindow, dwFlags);
    if (FAILED (hResult))
    {
        // Error
        REPORTERR (hResult);
		return hResult;
    }

	// Success
	return DD_OK;
} // End D3DWindow::InitWindow


  
/*
**-----------------------------------------------------------------------------
** Name:    D3DWindow::FiniWindow
** Purpose: Cleanups window
**-----------------------------------------------------------------------------
*/

HRESULT D3DWindow::FiniWindow (void)
{
	// Currently does nothing

	// Success
	return DD_OK;
} // End D3DWindow::FiniWindow


  
/*
**-----------------------------------------------------------------------------
**	Name:    D3DWindow::InitPrimary
**	Purpose: Creates a primary surface
**
**	Basic Algorithm:
**		1.  Create primary surface (from desktop mode)
**		2.  Create and attach a clipper object
**		3.  Create and attach a palette object, if desktop is palettized
**-----------------------------------------------------------------------------
*/

HRESULT D3DWindow::InitPrimary (void)
{
    HRESULT				hResult;
    DDSURFACEDESC		ddsd;
    LPDIRECTDRAWCLIPPER lpddcClipper = NULL;    

    // Check Initialization
    if ((! lpCurrMode) || (! lpDD2))
    {
        // Error
		REPORTERR (DDERR_GENERIC);
        return DDERR_GENERIC;
    }

	// 
	// Step 1.  Create Primary Surface
	//

	// Note:  No need to fill in width, height, etc.
	//        They system knows how to do it automatically
	//		  for a primary surface
    ddsd.dwSize         = sizeof(ddsd);
    ddsd.dwFlags        = DDSD_CAPS;
    ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;

	// Create Primary surface
    hResult = lpDD2->CreateSurface (&ddsd, &lpddsPrimary, NULL);
    if (FAILED (hResult))
    {
        // Error
        REPORTERR (hResult);
        return hResult;
    }


	// 
	// Step 2.   Create and attach clipper
	//
	// Note:	This needs to be done to prevent drawing outside
	//			of the windows current client area

	// Create Clipper object
    hResult = DirectDrawCreateClipper (0L, &lpddcClipper, 0);
    if (FAILED (hResult))
    {
        // Error
        REPORTERR (hResult);
		goto lblCLEANUP;
    }
    
	// Attach window to clipper
    hResult = lpddcClipper->SetHWnd (0L, hWindow);
    if (FAILED (hResult))
    {
        // Error
        REPORTERR (hResult);
		goto lblCLEANUP;
    }

	// Attach clipper to primary surface
    hResult = lpddsPrimary->SetClipper (lpddcClipper);
    if (FAILED (hResult))
    {
        // Error
        REPORTERR (hResult);
		goto lblCLEANUP;
    }

    // Go ahead and release the clipper interface, 
    // we don't need it anymore and it will be
    // destroyed automatically with the surface
    lpddcClipper->Release ();

	// Create and attach palette, if necessary
	hResult = InitPalette ();
	if (FAILED (hResult))
		goto lblCLEANUP;

	// Mark as Valid
	turnValidPrimaryOn ();

    // Success
    return DD_OK;

lblCLEANUP:
	// Failure

	// Cleanup before leaving
	if (lpddcClipper)
		lpddcClipper->Release ();
	
	FiniPrimary ();

	return hResult;
} // End D3DWindow::InitPrimary



/*
**-----------------------------------------------------------------------------
** Name:    D3DWindow::FiniPrimary
** Purpose: Destroys the Primary Surface
**-----------------------------------------------------------------------------
*/

HRESULT D3DWindow::FiniPrimary (void)
{
	// Mark as Invalid
	turnValidPrimaryOff ();

	// Cleanup palette
	FiniPalette ();

    // Release Primary Surface Object
    if (lpddsPrimary)
    {
        lpddsPrimary->Release ();
        lpddsPrimary = NULL;
    }

	// Success
	return DD_OK;
} // End D3DWindow::FiniPrimary



/*
**-----------------------------------------------------------------------------
** Name:    D3DWindow::InitPalette
** Purpose: Creates a primary palette if necessary
**-----------------------------------------------------------------------------
*/

HRESULT D3DWindow::InitPalette ()
{
    HRESULT             hResult;
    HDC                 hdc;
    DWORD               ii;
    PALETTEENTRY        pePalette[256];
    DWORD               cPal;
    DWORD               cbSize;
    DWORD               dwFlags;
    DDSURFACEDESC       ddsd;

    // Destroy old palette
    FiniPalette ();

    // Make sure we are properly intialized 
    // for this to work
    if ((! lpDD2) || (! lpddsPrimary))
    {
        // Error
		REPORTERR (DDERR_GENERIC);
        return DDERR_GENERIC;
    }

    // Get primary surface caps
    ZeroMemory(&ddsd, sizeof(ddsd));
    ddsd.dwSize = sizeof(ddsd);
    hResult = lpddsPrimary->GetSurfaceDesc(&ddsd);
    if (FAILED (hResult))
    {
        // Error
        REPORTERR (hResult);
        return hResult;
    }

    // Make sure it is a palettized surface
    if (! isPalettized (&(ddsd.ddpfPixelFormat)))
    {
        // Success, primary isn't palettized
		// So we don't need to create a palette
        return DD_OK;
    }

    // Create and save System palette
    hdc = GetDC (NULL);
    cPal = GetDeviceCaps (hdc, SIZEPALETTE);
    if (cPal)
    {
        if (cPal > 256)
            cPal = 256;

        // Get memory for palette entries
        lppePalette = new PALETTEENTRY[cPal];
        if (! lppePalette)
        {
            // Error, not enough memory
			ReleaseDC (NULL, hdc);

			hResult = DDERR_OUTOFMEMORY;
			REPORTERR (hResult);
			goto lblCLEANUP;
        }

        // Save system palette
        GetSystemPaletteEntries (hdc, 0, cPal, lppePalette);

        // Copy system palette to temporary values
        cbSize = cPal * sizeof (PALETTEENTRY);
        CopyMemory (pePalette, lppePalette, cbSize);
    }
	ReleaseDC (NULL, hdc);

    if (ddsd.ddpfPixelFormat.dwFlags & DDPF_PALETTEINDEXED1)
    {
        dwFlags = DDPCAPS_1BIT;

        // Only 2 palette entries, we need them all
        for (ii = 0; ii < 2; ii++)
            pePalette[ii].peFlags = D3DPAL_FREE | PC_RESERVED;

    }
    else if (ddsd.ddpfPixelFormat.dwFlags & DDPF_PALETTEINDEXED2)
    {
        // Only 4 palette entries, we need them all
        for (ii = 0; ii < 4; ii++)
            pePalette[ii].peFlags = D3DPAL_FREE | PC_RESERVED;

        dwFlags = DDPCAPS_2BIT;
    }
    else if (ddsd.ddpfPixelFormat.dwFlags & DDPF_PALETTEINDEXED4)
    {
        // Only 16 palette entries, we will save black and white
        // and keep the rest for ourselves.

        pePalette[0].peFlags = D3DPAL_READONLY;
        pePalette[15].peFlags = D3DPAL_READONLY;

        for (ii = 1; ii < 15; ii++)
            pePalette[ii].peFlags = D3DPAL_FREE | PC_RESERVED;

        dwFlags = DDPCAPS_4BIT;
    }
    else if (ddsd.ddpfPixelFormat.dwFlags & DDPF_PALETTEINDEXED8)
    {
        // 256 palette entries, we can afford to be nice
        // and save the first 10 and last 10 palette entries
        // for system use 
        for (ii = 0; ii < 10; ii++)
        {
            pePalette[ii].peFlags = D3DPAL_READONLY;
            pePalette[246+ii].peFlags = D3DPAL_READONLY;
        }

        for (ii = 10; ii < 246; ii++)
            pePalette[ii].peFlags = D3DPAL_FREE | PC_RESERVED;

        dwFlags = DDPCAPS_8BIT;        
    }
    else
    {
        // Error, programming (unknown palette type)
		hResult = DDERR_GENERIC;
		REPORTERR (hResult);
		goto lblCLEANUP;
    }

    // Create Primary Palette
    hResult = lpDD2->CreatePalette (dwFlags,
                                    pePalette,
                                    &lpddpPalette,
                                    NULL);
    if (FAILED (hResult))
    {
        // Error
        REPORTERR (hResult);
        goto lblCLEANUP;
    }

    // Attach palette to primary surface
    hResult = lpddsPrimary->SetPalette (lpddpPalette);
    if (FAILED (hResult))
    {
        // Error
        REPORTERR (hResult);
        goto lblCLEANUP;
    }

    // Success
    return DD_OK;

lblCLEANUP:
	// Cleanup before leaving
    FiniPalette ();

	// Failure
	return hResult;
} // D3DWindow::InitPalette



/*
**-----------------------------------------------------------------------------
** Name:    D3DWindow::FiniPalette
** Purpose: Destroys primary palette
**-----------------------------------------------------------------------------
*/

HRESULT D3DWindow::FiniPalette (void)
{
    // Note:  Should we Detach Palette object from surfaces
    // No way to do this that I know of...
    
    // Cleanup up DD Palette object
    if (lpddpPalette)
    {
        lpddpPalette->Release ();
        lpddpPalette = NULL;
    }

    // Cleanup System Palette
    if (lppePalette)
    {
        // Note:  Should we try and restore system palette here ?!?

        // Destroy system palette
        delete [] lppePalette;
        lppePalette = NULL;
    }

	// Success
	return DD_OK;
} // End FiniPalette



/*
**-----------------------------------------------------------------------------
** Name:    D3DWindow::ValidateSize
** Purpose: Validate Surface Size
**-----------------------------------------------------------------------------
*/

HRESULT D3DWindow::ValidateSize (void)
{
	long x, y, w,h;
    long wwMax, whMax;  // maximum windows width, height
    long wwMin, whMin;  // minimum windows width, height

	// Get Min, max window sizes
    wwMax = GetSystemMetrics (SM_CXMAXTRACK);
    whMax = GetSystemMetrics (SM_CYMAXTRACK);
    wwMin = GetSystemMetrics (SM_CXMIN);
    whMin = GetSystemMetrics (SM_CYMIN);

	// Null Size => use client area of window for size
	w = abs (rSurf.right - rSurf.left);
	h = abs (rSurf.bottom - rSurf.top);
	if ((w == 0) || (h == 0))
	{
		if ((! hWindow) || (! IsWindow (hWindow)))
			return DDERR_GENERIC;

		GetClientRect (hWindow, &rSurf);
	}

	// Get canonical pos, size
	if (rSurf.right < rSurf.left)
	{
		x = rSurf.right;
		w = rSurf.left - rSurf.right;
	}
	else
	{
		x = rSurf.left;
		w = rSurf.right - rSurf.left;
	}
	
	if (rSurf.bottom < rSurf.top)
	{
		y = rSurf.bottom;
		h = rSurf.top - rSurf.bottom;
	}
	else
	{
		y = rSurf.top;
		h = rSurf.bottom - rSurf.top;
	}


	// Clamp to min,max sizes
	if (w < D3DWIN_MIN_SIZE)
		w = D3DWIN_MIN_SIZE;
	if (w < wwMin)
		w = wwMin;
	if (w > wwMax)
		w = wwMax;

	if (h < D3DWIN_MIN_SIZE)
		h = D3DWIN_MIN_SIZE;
	if (h < whMin)
		h = whMin;
	if (h > whMax)
		h = whMax;

	// Save validated surface
	rSurf.left   = x;
	rSurf.right  = x + w;
	rSurf.top    = y;
	rSurf.bottom = y + h;

	// Success
	return DD_OK;
} // End D3DWindow::ValidateSize


    
/*
**-----------------------------------------------------------------------------
** Name:    D3DWindow::CreateRender
** Purpose: Creates the rendering surface from requested device and 
**			surface size
**-----------------------------------------------------------------------------
*/

HRESULT D3DWindow::CreateRender (LPGUID lpD3DGuid, LPRECT lprSurf)
{
	HRESULT		 hResult;
	LPD3DDevInfo lpDevNew;

	// Check Initialization
	if ((! lpCurrDriver) || (! lpCurrMode))
	{
		REPORTERR (DDERR_GENERIC);
		return DDERR_GENERIC;
	}

	// Make sure this D3D device works with this mode
	lpDevNew = ValidateDevice (lpCurrDriver, lpD3DGuid, lpCurrMode);
	if (! lpDevNew)
	{
		REPORTERR (DDERR_INVALIDPARAMS);
		return DDERR_INVALIDPARAMS;
	}
	// Save new D3D device
	lpCurrDevice = lpDevNew;


	// Get Surface Size
	if (! lprSurf)
		GetClientRect (hWindow, &rSurf);
	else
		rSurf = *lprSurf;

	// Cleanup old render surface
	FiniRender ();

	// Create new Render surface (using new Device)
	hResult = InitRender ();
	if (FAILED (hResult))
		return hResult;

	// Success
	return DD_OK;
}



/*
**-----------------------------------------------------------------------------
** Name:    D3DWindow::InitRender
** Purpose: Creates the rendering surface and D3D device
** Notes:
**
**	1. The main problem here is a catch 22 situation.  In order to create the
**	   D3D device you need a valid render surface.   However, in order to create
**     a render surface properly, you need to know some D3D device caps 
**			- Does the device support Z-buffers
**			- Video vs. System memory
**			- etc.
**
**	   Fortunately, our Driver Manager already has all that information.
**	   So we can break the catch 22.  Without having to resort to some extra
**     complexity in the code here.
**		
** 
** Basic Algorithm:
**
**  1. Validate Device
**  2. Validate Surface size
**  3. Setup Surface Desc (width, height, bpp)
**	4. Create Render Surface (from surface desc)
**  5. Create Z-buffer (optional)
**	6. Create D3D Device
**	7. Create Viewport
**	8. InitScene (optional)
**
**-----------------------------------------------------------------------------
*/

HRESULT D3DWindow::InitRender (void)
{
    HRESULT         hResult;
    DWORD           dwMemType;
    LPD3DDEVICEDESC lpDeviceDesc;
    DDSURFACEDESC   ddsd;
    DWORD           dwWidth, dwHeight, dwBPP;
	LPGUID			lpGuidD3D;
	LPD3DDevInfo	lpDevNew;

	// Check Initialization
    if ((! hWindow) || (! IsWindow (hWindow)) ||
		(! lpCurrDevice) || (! lpCurrMode) || 
		(! lpDD2) || (! lpD3D) || (! lpddsPrimary))
    {
        // Error, Not initialized properly
		REPORTERR (DDERR_GENERIC);
        return DDERR_GENERIC;
    }

	
	//
	// Step 1.  Validate Device
	//
	if (lpCurrDevice)
		lpGuidD3D = &(lpCurrDevice->guid);
	else
		lpGuidD3D = NULL;

	lpDevNew = ValidateDevice (lpCurrDriver, lpGuidD3D, lpCurrMode);
	if (! lpDevNew)
	{
		REPORTERR (DDERR_GENERIC);
		return DDERR_GENERIC;
	}

	// Save new D3D device
	lpCurrDevice = lpDevNew;


	// 
	// Step 2. Validate Surface size
	//
	hResult = ValidateSize ();
	if (FAILED (hResult))
		return hResult;

	dwWidth	 = rSurf.right - rSurf.left;
	dwHeight = rSurf.bottom - rSurf.top;


    //
	// Step 3.  Setup DD surface desc (width, height, BPP)
	//

	// Get Memory Type
	if (lpCurrDevice->isHardware ())
	{
		// Hardware device
		dwMemType = DDSCAPS_VIDEOMEMORY;
		lpDeviceDesc = &(lpCurrDevice->d3dHalDesc);
	}
	else
	{
		// Software device 
		// Note:  It doesn't have to be in system memory but
		//        it makes debugging a lot easier 
		//		  (Win16locks don't get in the way)
		dwMemType = DDSCAPS_SYSTEMMEMORY;
		lpDeviceDesc = &(lpCurrDevice->d3dHelDesc);
	}

    // Get primary surface caps
    ZeroMemory(&ddsd, sizeof(ddsd));
    ddsd.dwSize = sizeof (DDSURFACEDESC);
    hResult = lpddsPrimary->GetSurfaceDesc (&ddsd);
    if (FAILED (hResult))
    {
      // Error
      REPORTERR (hResult);
      return hResult;
    }

    // Create device surface
	// Note: We don't need to specify the pixel format, it will
	//       automatically default to same format as primary
    ddsd.dwSize         = sizeof(ddsd);
    ddsd.dwFlags        = DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT;// | DDSD_PIXELFORMAT;
    ddsd.dwWidth        = dwWidth;
    ddsd.dwHeight       = dwHeight;
    ddsd.ddsCaps.dwCaps = DDSCAPS_3DDEVICE | DDSCAPS_OFFSCREENPLAIN | dwMemType;


	// 
	// Step 2.  Create Rendering Surface (from dd surface desc)
	//
	hResult = lpDD2->CreateSurface (&ddsd, &lpddsRender, NULL);
	if (FAILED(hResult))
	{
		REPORTERR (hResult);
		return hResult;
	}

	// Attach palette, if any
	if (NULL != lpddpPalette)
	{
		hResult = lpddsRender->SetPalette (lpddpPalette);
		if (FAILED (hResult))
		{
			// Error
			REPORTERR (hResult);
			return hResult;
		}
	}


	//
	// Step 3.	Create and attach Z-buffer (optional)
	//
    if ((isCreateZBuffer ()) && 
        (0L != lpDeviceDesc->dwDeviceZBufferBitDepth))
    {
        dwBPP = FlagsToBitDepth (lpDeviceDesc->dwDeviceZBufferBitDepth);

        // Create the z-buffer.
        ZeroMemory (&ddsd, sizeof(ddsd));
        ddsd.dwSize            = sizeof(ddsd);
        ddsd.dwFlags           = DDSD_CAPS   |
                                 DDSD_WIDTH  |
                                 DDSD_HEIGHT |
                                 DDSD_ZBUFFERBITDEPTH;
        ddsd.ddsCaps.dwCaps    = DDSCAPS_ZBUFFER | dwMemType;
        ddsd.dwWidth           = dwWidth;
        ddsd.dwHeight          = dwHeight;
        ddsd.dwZBufferBitDepth = dwBPP;
        hResult = lpDD2->CreateSurface (&ddsd, &lpddsZBuff, NULL);
        if (FAILED(hResult))
        {
            // Note: we may be able to continue without a z buffer
            REPORTERR (hResult);
        }
		else
		{
			// Attach Z-buffer to rendering surface
			hResult = lpddsRender->AddAttachedSurface (lpddsZBuff);
			if (FAILED (hResult))
			{
				// Note: we may be able to continue without a z buffer
				REPORTERR (hResult);
				if (lpddsZBuff)
				{
					lpddsZBuff->Release ();
					lpddsZBuff = NULL;
				}
			}
		}
    }


    //
    // Step 4.  Create the D3D device interface
	//
	hResult = lpD3D->CreateDevice (lpCurrDevice->guid,
				 				   lpddsRender, 
							 	   &lpd3dDevice);
    if (FAILED (hResult))
    {
        REPORTERR (hResult);
        return hResult;
    }


	//
	// Step 5.  Create the viewport
	//
	hResult = InitViewport ();
	if (FAILED (hResult))
		return hResult;

	// Mark as valid
	turnValidRenderOn ();
	turnCalcRectsOn ();

	
	// 
	// Step 6.	Initialize Scene (if attached)
	//
	if (lpd3dScene)
	{
		hResult = lpd3dScene->Init (this);
		if (FAILED (hResult))
			return hResult;
	}

    // Success
    return DD_OK;
} // End D3DWindow::InitRender



/*
**-----------------------------------------------------------------------------
** Name:    D3DWindow::FiniRender
** Purpose: Destroys the Rendering surface
**-----------------------------------------------------------------------------
*/

HRESULT D3DWindow::FiniRender (void)
{
	// Mark as invalid
	turnValidRenderOff ();

	// Cleanup Associated Scene
	if (lpd3dScene)
	{
		lpd3dScene->Fini ();
	}

	// Cleanup viewport
	FiniViewport ();

    // Release D3D Device
    if (lpd3dDevice)
    {
        lpd3dDevice->Release ();
        lpd3dDevice = NULL;
    }

    // Release Z Buffer
    if (lpddsZBuff)
    {
        // Detach Z-Buffer from back buffer
        if (lpddsRender)
            lpddsRender->DeleteAttachedSurface (0L, lpddsZBuff);
        lpddsZBuff->Release ();
        lpddsZBuff = NULL;
    }

    // Release rendering surface
    if (lpddsRender)
    {
        lpddsRender->Release ();
        lpddsRender = NULL;
    }

	// Success
	return DD_OK;
} // End D3DWindow::FiniRender



/*
**-----------------------------------------------------------------------------
**  Name:       D3DWindow::InitViewport
**  Purpose:    
**-----------------------------------------------------------------------------
*/

HRESULT D3DWindow::InitViewport (void)
{
	HRESULT hResult;

	// Check Initialization
	if ((! lpD3D) || (! lpd3dDevice))
	{
        REPORTERR (DDERR_GENERIC);
        return DDERR_GENERIC;
	}

	// Create Viewport
    hResult = lpD3D->CreateViewport (&lpd3dViewport, NULL);
    if (FAILED (hResult))
    {
        REPORTERR (hResult);
        return hResult;
    }

	// Attach viewport to D3D device
    hResult = lpd3dDevice->AddViewport (lpd3dViewport);
    if (FAILED (hResult))
    {
        REPORTERR (hResult);
        return hResult;
    }

	// Set up Initial Viewport parameters
	hResult = UpdateViewport ();
    if (FAILED (hResult))
        return hResult;

	/// Success
	return DD_OK;
} // End D3DWindow::InitViewport
  


/*
**-----------------------------------------------------------------------------
**  Name:       D3DWindow::FiniViewport
**  Purpose:    Cleanup viewport
**-----------------------------------------------------------------------------
*/

HRESULT D3DWindow::FiniViewport (void)
{
	// Release D3D viewport
    if (lpd3dViewport)
    {
        lpd3dViewport->Release ();
        lpd3dViewport  = NULL;
    }

	// Success
	return DD_OK;
} // End D3DWindow::FiniViewport

  

/*
**-----------------------------------------------------------------------------
**  Name:       D3DWindow::UpdateViewport
**  Purpose:    Keeps viewport updated with current window size
**  Notes:		
**
**	1. The viewport construction here assumes that you are rendering 
**		Triangles using the D3DVERTEX and D3DIM is doing Transform,
**		lighting, and rasterization for you.
**
**	2. If you are rendering triangles using D3DTLVERTEX and doing your
**	   own transform and lighting then you need to setup the viewport
**	   differently.   As follows:
**
**      // Replace the following values below:
**		dvClipX			= 0.0f;
**		dvClipY			= 0.0f;
**		dvClipWidth		= dwSurfW;
**		dvClipHeight	= dvSurfH;
**
**  3. This perserves the aspect ratio.  If you don't need or want to
**     perserve the aspect ratio then set inv_aspect = 1.0 below and
**     work this constant through the rest of the viewport setup.
**
**-----------------------------------------------------------------------------
*/

HRESULT D3DWindow::UpdateViewport (void)
{
    HRESULT			hResult;
    D3DVIEWPORT2	d3dViewport;
	DWORD			dwSurfW, dwSurfH;

    // Check Parameters
	if ((! lpd3dDevice) || (! lpd3dViewport))
	{
		// Not properly initialized.
		REPORTERR (DDERR_GENERIC);
		return DDERR_GENERIC;
	}

	// Get Surface Width and Height
	dwSurfW = abs (rSurf.right - rSurf.left);
	dwSurfH = abs (rSurf.bottom - rSurf.top);

	float inv_aspect;
	
	if (dwSurfW)
		inv_aspect = (float)dwSurfH/(float)dwSurfW;
	else
                inv_aspect = 1.0f;

    // Update Viewport
    ZeroMemory (&d3dViewport, sizeof(d3dViewport));
    d3dViewport.dwSize		= sizeof(d3dViewport);     // Always set size of structure!!!
    d3dViewport.dwX			= 0UL;
    d3dViewport.dwY			= 0UL;
    d3dViewport.dwWidth		= dwSurfW;
    d3dViewport.dwHeight	= dwSurfH;
    d3dViewport.dvClipX		= -1.0f;
    d3dViewport.dvClipY		= inv_aspect;
    d3dViewport.dvClipWidth	= 2.0f;
    d3dViewport.dvClipHeight = 2.0f * inv_aspect;
    d3dViewport.dvMinZ		= 0.0f;
    d3dViewport.dvMaxZ		= 1.0f;

	// Update Viewport
    hResult = lpd3dViewport->SetViewport2 (&d3dViewport);
    if (FAILED (hResult))
    {
        REPORTERR (hResult);
        return hResult;
    }

	// Update D3D device to use this viewport
    hResult = lpd3dDevice->SetCurrentViewport (lpd3dViewport);
    if (FAILED (hResult))
    {
        REPORTERR (hResult);
        return hResult;
    }

    // Success
    return DD_OK;
} // End D3DWindow::UpdateViewport

  

/*
**-----------------------------------------------------------------------------
** Name:    D3DWindow::DrawFrame
** Purpose: Paints current surface to window
**-----------------------------------------------------------------------------
*/

HRESULT D3DWindow::DrawFrame (void)
{
    HRESULT hResult = DD_OK;

	// Check Initialization
    if (! isValid ())
    {
        // Error, not properly initialized
        return DDERR_GENERIC;
    }

    if (isPaused ())
    {
        // Don't draw, if paused
        return DD_OK;
    }

    // Double check parameters
    if ((! lpddsPrimary) || (! lpddsRender))
    {
        // Error, not properly initialized
        return DDERR_GENERIC;
    }
    
    // Get current src, dest rectangles
    CalcRects ();

    if (! checkPaint ())
    {
        // Nothing to draw, so return immediately
        return DD_OK;
    }

    // Paint until we truly succeed or error out
    while (TRUE)
    {
		// Render D3D Scene
		if (lpd3dScene)
			hResult = lpd3dScene->Render ();

		if (SUCCEEDED (hResult))
		{
			// Blt Rendering surface onto primary surface
			hResult = lpddsPrimary->Blt (&rDrawDest,	// Dest Rect
					                     lpddsRender,   // Src Surface
						                 &rDrawSrc,     // Src Rect
							             DDBLT_WAIT,    // Wait
								         NULL);         // Blt Special Effects (none)

			// Did it work ?!?  
			if (SUCCEEDED (hResult))
			{
				// Success, exit
				return hResult;
			}
		}

        // Check if busy or drawing
        if ((DDERR_SURFACEBUSY == hResult) ||
            (DDERR_WASSTILLDRAWING == hResult))
        {
            // Try again
            continue;
        }

        // Check for lost surfaces
        while (DDERR_SURFACELOST == hResult)
        {
            // Restore surfaces
            hResult = Restore ();
        }

        // Check for real error
        if (FAILED (hResult))
        {
            // Error,
            REPORTERR (hResult);
            return hResult;
        }
    }

    // Success
    return DD_OK;
} // End D3DWindow::DrawFrame



/*
**-----------------------------------------------------------------------------
** Name:    D3DWindow::Move
** Purpose: Move window to new coordinates
** Notes:   This used to be simpler. (See CalcRects)
**-----------------------------------------------------------------------------
*/

HRESULT D3DWindow::Move (long x, long y)
{
    // Need to recalculate src, dest rectangles
    turnCalcRectsOn ();

    // Success
    return DD_OK;
} // D3DWindow::Move



/*
**-----------------------------------------------------------------------------
** Name:    D3DWindow::Resize
** Purpose: Resizes the Window
** Notes:
**		We need to resize the render surface to stay in sync
**		with the new window size
**-----------------------------------------------------------------------------
*/

HRESULT D3DWindow::Resize (DWORD dwWidth, DWORD dwHeight)
{
	HRESULT				hResult;
	RECT				rSurfOld;

    // Need to recalculate src, dest rectangles 
    turnCalcRectsOn ();

	// Save old Surface coordinates
	rSurfOld = rSurf;

	// Update the surface rectangle
	rSurf.left   = 0;
	rSurf.top    = 0;
	rSurf.right  = dwWidth;
	rSurf.bottom = dwHeight;

	// Check if properly initialized
	if (! isValid ())
	{
		// Try to re-initialize
		Fini ();
		hResult = Init ();
		if (FAILED (hResult))
			return hResult;

		// Successful re-initialization
		return DD_OK;
	}

    // Cleanup Render Surface (and D3D Device)
    FiniRender ();

	// Re-create Render Surface (at new size)
	hResult = InitRender ();
	if (FAILED (hResult))
	{
		if ((hResult == DDERR_OUTOFMEMORY) || 
			(hResult == DDERR_OUTOFVIDEOMEMORY))
		{
			// Try to restore old surface size
			rSurf = rSurfOld;

			FiniRender ();
			hResult = InitRender ();
			if (FAILED (hResult))
				return hResult;

			// Successfully returned to previous size
			return DD_OK;
		}

		return hResult;
	}

	// Success
	return DD_OK;
} // End D3DWindow::Resize 



/*
**-----------------------------------------------------------------------------
**  Name:       D3DWindow::RealizePalette
**  Purpose:    
**-----------------------------------------------------------------------------
*/

HRESULT D3DWindow::RealizePalette (void)
{
	HRESULT hResult;

	//
    // Realizing the palette using DirectDraw is quite different
    // from GDI. To realize the palette we call SetPalette()
    // each time our application is activated.
    //
    // NOTE: DirectDraw spots the fact that the new palette is the
    // same as the old one and so does not increase the reference
    // count of the palette.
    //

	if ((lpddsPrimary) && (lpddpPalette))
	{
		hResult = lpddsPrimary->SetPalette (lpddpPalette);
		if (FAILED (hResult))
        {
            REPORTERR (hResult);
            return hResult;
        }
	}

	// Success
	return DD_OK;
} // End D3DWindow::RealizePalette



/*
**-----------------------------------------------------------------------------
** Name:    D3DWindow::Pause
** Purpose: Pause any work on DD/D3D resources
**-----------------------------------------------------------------------------
*/

HRESULT D3DWindow::Pause (BOOL fPause)
{
    // Turning pausing on/off ?!?
    if (fPause)
    {
        if (dwPaused == 0L)
        {
			// Very first time paused, do anything special here...

			// Force screen redraw
			if (hWindow)
				InvalidateRect (hWindow, NULL, FALSE);
        }
        dwPaused++;
    }
    else
    {
        if (dwPaused == 0L)
        {
            // Programmer Error, already paused
			REPORTERR (DDERR_GENERIC);
            return DDERR_GENERIC;
        }

        // Decrement semaphore
        dwPaused--;
        if (dwPaused == 0L)
        {
			// Very last time unpaused, do anything special here...

			// Force screen redraw
			if (hWindow)
				InvalidateRect (hWindow, NULL, FALSE);
        }
    }

    // Success
    return DD_OK;
} // D3DWindow::Pause



/*
**-----------------------------------------------------------------------------
** Name:    D3DWindow::AttachScene
** Purpose: 
**-----------------------------------------------------------------------------
*/

HRESULT D3DWindow::AttachScene (LPD3DScene lpNewScene)
{
	// Check parameters
	if (! lpNewScene)
	{
		return DDERR_INVALIDPARAMS;
	}

	DetachScene ();

	// Save Scene pointer
	lpd3dScene = lpNewScene;

	// Initialize Scene ?!?
	if (isValid ())
	{
		lpd3dScene->Init (this);
	}

	// Success
	return DD_OK;
} // End D3DWindow::AttachScene



/*
**-----------------------------------------------------------------------------
** Name:    D3DWindow::DetachScene
** Purpose: 
**-----------------------------------------------------------------------------
*/

HRESULT D3DWindow::DetachScene (void)
{
	// Cleanup Scene
	if (lpd3dScene)
	{
		lpd3dScene->Fini ();
		lpd3dScene = NULL;
	}

	// Success
	return DD_OK;
} // End D3DWindow::DetachScene


  
/*
**-----------------------------------------------------------------------------
** Name:    D3DWindow::CalcRects
** Purpose: Recalculate src,dest rectangles
**
** Notes:	Without this protection we get a GPF when we drag the window
**			off the edge of the screen.  This is because we are trying to
**			write pixels to a non-existent location.   The clipper object
**			attached to the primary protects the primary surface from 
**			stray pixels outside of the window's client area.  However, it
**			doesn't stop us from trying to write outside the primary.  So
**			we need to protect ourselves.
** 
** Basic Algorithm:   
**
**     - Get Client rectangle
**     - Get Render Surface rectangle
**     - Intersect client with surface to get initial src rect
**
**     - Get Primary surface rectangle
**     - Map Src rect to primary surface coordinates
**
**     - Intersect primary with src to get dest rect.
**     - Map dest rect back into surface coordinates to get final src rect.
**
**-----------------------------------------------------------------------------
*/

HRESULT D3DWindow::CalcRects (void)
{
    // Do we need to recalculate the rectangles
	// I.E. Can we avoid doing work
    if (checkCalcRects ())
    {
        HRESULT       hResult;
        DDSURFACEDESC ddsd;         // Surface desc.
        POINT         pnt;
        RECT          rClient;
        RECT          rSrc;
        RECT          rDest;
        RECT          rTemp;
        
        if (! isValid ())
        {
            // Error, not properly initialized
            return DDERR_GENERIC;
        }

        // Assume we are going to paint
        turnPaintOn ();

        // Get Client rectangle pos/size
        GetClientRect (hWindow, &rClient);

        // Get Surface rectangle size
        ddsd.dwSize = sizeof (DDSURFACEDESC);
        hResult = lpddsRender->GetSurfaceDesc (&ddsd);
        if (FAILED (hResult))
        {
            // Error
            REPORTERR (hResult);
            return hResult;
        }
        rSurf.right     = rSurf.left + ddsd.dwWidth;
        rSurf.bottom    = rSurf.top + ddsd.dwHeight;

        // Intersect client with surface to get initial Src Rect
        if (! IntersectRect (&rSrc, &rClient, &rSurf))
        {
            // No intersection, means nothing to draw
            turnPaintOff ();
            rSrc.left   = 0;
            rSrc.top    = 0;
            rSrc.right  = 0;
            rSrc.bottom = 0;
        }

        // Get Primary Rectangle
        ZeroMemory (&ddsd, sizeof(ddsd));
        ddsd.dwSize = sizeof (DDSURFACEDESC);
        hResult = lpddsPrimary->GetSurfaceDesc (&ddsd);
        if (FAILED (hResult))
        {
            // Error
            return hResult;
        }

        rPrim.left      = 0;
        rPrim.top       = 0;
        rPrim.right     = rPrim.left + ddsd.dwWidth;
        rPrim.bottom    = rPrim.top + ddsd.dwHeight;

        // Map src rectangle in surface coordinates to 
		// primary surface coordinates
        pnt.x = rSrc.left;
        pnt.y = rSrc.top;
        ClientToScreen (hWindow, &pnt);

        rTemp.left   = pnt.x;
        rTemp.top    = pnt.y;
        rTemp.right  = rTemp.left + (rSrc.right - rSrc.left);
        rTemp.bottom = rTemp.top + (rSrc.bottom - rSrc.top);

        // Intersect temp with primary to get dest Rect
        if (! IntersectRect (&rDest, &rPrim, &rTemp))
        {
            // No intersection, means nothing to draw
            turnPaintOff ();
            rDest.left   = 0;
            rDest.top    = 0;
            rDest.right  = 0;
            rDest.bottom = 0;
        }

        // Now we have to map the dest rectangle back into
        // surface space to to get the final src rectangle
        rSrc.left   = rSrc.left + (rDest.left - pnt.x);
        rSrc.top    = rSrc.top + (rDest.top - pnt.y);
        rSrc.right  = rSrc.left + (rDest.right - rDest.left);
        rSrc.bottom = rSrc.top + (rDest.bottom - rDest.top);

        // Save src and dest rectangles
        rDrawDest.left   = rDest.left;
        rDrawDest.top    = rDest.top;
        rDrawDest.right  = rDest.right;
        rDrawDest.bottom = rDest.bottom;

        rDrawSrc.left   = rSrc.left;
        rDrawSrc.top    = rSrc.top;
        rDrawSrc.right  = rSrc.right;
        rDrawSrc.bottom = rSrc.bottom;

        // No longer need to calculate rects
        turnCalcRectsOff ();
    }

    // Success
    return DD_OK;
} // End D3DWindow::CalcRects



/*
**-----------------------------------------------------------------------------
** Name:    D3DWindow::Restore
** Purpose: Restores lost surfaces
** Note:    Eventually we should inform the user somehow that
**          they need to redraw the surface but for now punt
**-----------------------------------------------------------------------------
*/

HRESULT D3DWindow::Restore (void)
{
    HRESULT hResult;

	// Check Initialization
    if (! isValid ())
        return DDERR_GENERIC;

    // Restore Primary Surface
    if (lpddsPrimary)
    {
        hResult = lpddsPrimary->Restore ();
        if (FAILED (hResult))
            return hResult;
    }

    // Restore Z Buffer
    if (lpddsZBuff)
    {
        hResult = lpddsZBuff->Restore ();
        if (FAILED (hResult))
            return hResult;
    }

    // Restore Rendering surface
    if (lpddsRender)
    {
        hResult = lpddsRender->Restore ();
        if (FAILED (hResult))
            return hResult;
    }

	// Allow D3D Scene to restore any surfaces
	if (lpd3dScene)
	{
		hResult = lpd3dScene->Restore ();
		if (FAILED (hResult))
			return hResult;
	}

    // Success
    return DD_OK;
} // End D3DWindow::Restore


  
/*
**-----------------------------------------------------------------------------
** Name:    D3DWindow::GetSurfaceRect
** Purpose: Get bounding rectangle of surface
**-----------------------------------------------------------------------------
*/

HRESULT D3DWindow::GetSurfaceRect (RECT & rSurface)
{
    HRESULT hResult;

    if (! isValid ())
    {
        // Error
        return DDERR_GENERIC;
    }

    // Force update of rectangle coordinates
    hResult = CalcRects ();
    if (FAILED (hResult))
        return hResult;

    // Return Surface rectangle
    rSurface = rSurf;

    // Success
    return DD_OK;
} // D3DWindow::GetSurfaceRect



/*
**-----------------------------------------------------------------------------
** Name:    D3DWindow::GetPrimaryRect
** Purpose: Get bounding rectangle of primary surface
**-----------------------------------------------------------------------------
*/

HRESULT D3DWindow::GetPrimaryRect (RECT & rPrimary)
{
    HRESULT hResult;

    if (! isValid ())
    {
        // Error
        return DDERR_GENERIC;
    }

    // Force update of rectangle coordinates
    hResult = CalcRects ();
    if (FAILED (hResult))
    {
        // Error
        REPORTERR (hResult);
        return hResult;
    }

    // Return Primary rectangle
    rPrimary = rPrim;

    // Success
    return DD_OK;
} // GetPrimaryRect
  

  
/*
**-----------------------------------------------------------------------------
** Name:    D3DWindow::GetSrcRect
** Purpose: Get current Src Rectangle
**-----------------------------------------------------------------------------
*/

HRESULT D3DWindow::GetSrcRect (RECT & rSrc)
{
    HRESULT hResult;

    if (! isValid ())
    {
        // Error
        return DDERR_GENERIC;
    }

    // Force update of rectangle coordinates
    hResult = CalcRects ();
    if (FAILED (hResult))
        return hResult;

    // Return Surface rectangle
    rSrc = rDrawSrc;

    // Success
    return DD_OK;
} // D3DWindow::GetSrcRect


  
/*
**-----------------------------------------------------------------------------
** Name:    D3DWindow::GetDestRect
** Purpose: Get current Dest Rectangle
**-----------------------------------------------------------------------------
*/

HRESULT D3DWindow::GetDestRect (RECT & rDest)
{
    HRESULT hResult;

    if (! isValid ())
    {
        // Error
        return DDERR_GENERIC;
    }

    // Force update of rectangle coordinates
    hResult = CalcRects ();
    if (FAILED (hResult))
        return hResult;

    // Return Surface rectangle
    rDest = rDrawDest;

    // Success
    return DD_OK;
} // D3DWindow::GetDestRect
  

/*
**-----------------------------------------------------------------------------
**  Name:       D3DWindow::ChangeDesktop
**  Purpose:    The Primary Desktop has changed Modes, so we need
**				to update our current mode to stay in sync
**-----------------------------------------------------------------------------
*/

HRESULT D3DWindow::ChangeDesktop (void)
{
	HRESULT		 hResult;
	LPDDDrvInfo  lpDrvOld;
	LPDDModeInfo lpModeOld, lpModeNew;
	LPD3DDevInfo lpDevOld, lpDevNew;
	LPGUID		 lpGuidD3D;

	// Check Initialization
	if ((! hWindow) || (! IsWindow (hWindow)))
	{
		REPORTERR (DDERR_INVALIDPARAMS);
		return DDERR_INVALIDPARAMS;
	}

	lpDrvOld  = lpCurrDriver;
	lpModeOld = lpCurrMode;
	lpDevOld  = lpCurrDevice;

	if (! lpDrvOld)
	{
		REPORTERR (DDERR_GENERIC);
		return DDERR_GENERIC;
	}


	//
	// Step 1. Get New Mode (and new device)
	//

	// Get D3D Guid
	if (lpDevOld)
		lpGuidD3D = &(lpDevOld->guid);
	else
		lpGuidD3D = NULL;

	// Get New Mode and Device corresponding to current desktop
	if (! GetDesktopMode (lpDrvOld, lpGuidD3D, &lpModeNew, &lpDevNew))
	{
		REPORTERR (DDERR_GENERIC);
		return DDERR_GENERIC;
	}

	// Do they match
	if (lpModeOld == lpModeNew)
	{
		// Nothing to do
		return DD_OK;
	}

	// 
	// Step 2.	Destroy current Mode
	//
	FiniRender ();
	FiniPrimary ();
//  FiniMode ();		// Don't do this => unnecessary mode switch

	//
	// Step 3.  Create new mode
	//
	lpCurrMode = lpModeNew;
	if (lpDevNew)
		lpCurrDevice = lpDevNew;

	// Create Primary Surface
	hResult = InitPrimary ();
	if (FAILED (hResult))
	{
		// Error, no point in trying to restore old defaults
		// they are out of sync with the current desktop
		return hResult;
	}


	// Create Render surface
	hResult = InitRender ();
	if (FAILED (hResult))
	{
		// Error, no point in trying to restore old defaults
		// they are out of sync with the current desktop
		return hResult;
	}

	// Notify the window of a successful change in Mode
	SendMessage (hWindow, D3DWIN_CHANGED_MODE, 0, 0);

	// Success
    return DD_OK;
} // D3DInfo::ChangeDesktop
  


  
/*
**-----------------------------------------------------------------------------
** Name:    D3DWindow::ChangeDriver
** Purpose: 
**-----------------------------------------------------------------------------
*/

HRESULT D3DWindow::ChangeDriver (LPGUID lpGuidDD, LPD3DDevInfo lpDevHint)
{
	HRESULT		 hResult;
    LPGUID       lpGuidD3D;
	LPDDDrvInfo  lpDrvNew,  lpDrvOld;
	LPDDModeInfo lpModeNew, lpModeOld;
	LPD3DDevInfo lpDevNew, lpDevOld;

	// Get New Driver
	lpDrvNew = ValidateDriver (lpGuidDD);
	if (! lpDrvNew)
	{
		return DDERR_GENERIC;
	}

	// Are we already using the requested driver
	if ((isValid ()) && (lpDrvNew == lpCurrDriver))
		return DD_OK;

	// Get reasonable defaults for Mode and D3D device
	if (lpDevHint)
		lpGuidD3D = &(lpDevHint->guid);
	else if (lpCurrDevice)
		lpGuidD3D = &(lpCurrDevice->guid);
	else
		lpGuidD3D = NULL;

	if (! GetDesktopMode (lpDrvNew, lpGuidD3D, &lpModeNew, &lpDevNew))
	{
		return DDERR_GENERIC;
	}
	
	// Save old defaults
	lpDrvOld	= lpCurrDriver;
	lpModeOld	= lpCurrMode;
	lpDevOld	= lpCurrDevice;

	// Destroy almost everything
	Fini ();

	// Set new defaults
	lpCurrDriver = lpDrvNew;
	lpCurrMode   = lpModeNew;
	lpCurrDevice = lpDevNew;

	// Re-create almost everything based on new driver
	hResult = Init ();
	if (FAILED (hResult))
	{
		// Try to restore old defaults
		Fini ();

		lpCurrDriver = lpDrvOld;
		lpCurrMode   = lpModeOld;
		lpCurrDevice = lpDevOld;

		Init ();
		return hResult;
	}

	// Notify the window of a successful change in Driver
	SendMessage (hWindow, D3DWIN_CHANGED_DRIVER, 0, 0);

	// Success
    return DD_OK;
} // End D3DWindow::ChangeDriver


  
/*
**-----------------------------------------------------------------------------
** Name:    D3DWindow::ChangeDevice
** Purpose: Change to a new D3D device (RAMP, RGB, Hardware, etc.)
** Notes:
**
**  Algorithm:
**		- Destroy the current D3D Device (and associated surfaces)
**		- Recreate a new D3D device from the new GUID
**
**  1.	The new D3D Device may not be supported by the current DD Device.
**
**  2.  The new D3D Device may not be compatible with the current Mode
**		- If we are windowed, then punt (we shouldn't change the desktop)
**		- If we are full-screen then pick a new mode that is compatible
**			- This means destroy the current mode and recreate it.
**
**-----------------------------------------------------------------------------
*/

HRESULT D3DWindow::ChangeDevice (LPGUID lpD3DGuid)
{
    HRESULT         hResult;
	LPDDDrvInfo		lpDrvOld;
	LPDDModeInfo    lpModeOld;
	LPD3DDevInfo	lpDevNew, lpDevOld;

	// Check Parameters
	if (! lpD3DGuid)
	{
		REPORTERR (DDERR_INVALIDPARAMS);
        return DDERR_INVALIDPARAMS;
	}
	
	// Check Initialization
    if (! isValid () || (! lpddsRender))
	{
		REPORTERR (DDERR_GENERIC);
        return DDERR_GENERIC;
	}

	// Save Original State
	lpDrvOld	= lpCurrDriver;
	lpModeOld   = lpCurrMode;
	lpDevOld	= lpCurrDevice;

	// Verify new D3D device belongs to current DD driver
	lpDevNew = lpDrvOld->FindDevice (lpD3DGuid, NULL);
	if (! lpDevNew)
	{
		REPORTERR (DDERR_INVALIDPARAMS);
        return DDERR_INVALIDPARAMS;
	}

	//
	//	Step 1. Verify new D3D device is supported with current mode
	//
	if (! lpModeOld->ModeSupported (lpDevNew))
	{
		// We can't change the mode
		// as we shouldn't be changing the desktop
		REPORTERR (DDERR_INVALIDPARAMS);
		return DDERR_INVALIDPARAMS;
	}


	//
	//	Step 2.  Destroy Old D3D Device
	//
	FiniRender ();

	//
	//	Step 3. Create new D3D Device
	//

	// Set new D3D device (and mode)
	lpCurrDevice = lpDevNew;

	// Create new D3D Device
	hResult = InitRender ();
	if (FAILED (hResult))
	{
		// Try to restore original device
		lpCurrDevice = lpDevOld;		
		InitRender ();

		// Return Error
		REPORTERR (hResult);
		return hResult;
	}

	// Notify the window of a successful change in device
	SendMessage (hWindow, D3DWIN_CHANGED_DEVICE, 0, 0);

    // Success
    return DD_OK;
} // End D3DWindow::ChangeDevice



/*
**-----------------------------------------------------------------------------
** End of File
**-----------------------------------------------------------------------------
*/
