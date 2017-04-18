/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999 Microsoft Corporation

Module Name:

    DDraw.cpp

Abstract:

   This file contains DirectDraw functionality for the Desktop Compatibility program

-------------------------------------------------------------------*/

// ++++ Include Files +++++++++++++++++++++++++++++++++++++++++++++++
#include "DesktopCompat.hpp"

// ++++ Global Variables ++++++++++++++++++++++++++++++++++++++++++++
LPDIRECTDRAW        g_pdd;          // The DirectDraw object
LPDIRECTDRAWSURFACE g_pddsPrimary;  // Primary DirectDraw surface
LPDIRECTDRAWSURFACE g_pddsSecondary;  // secondary DirectDraw surface
LPDIRECTDRAWCLIPPER g_lpDDClipper;  //the clipper used to determine the usable area

// ++++ Local functions +++++++++++++++++++++++++++++++++++++++++++++
static BOOL CreateDirectDrawDevice();

int ImageWidth, ImageHeight;
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    InitDirectDraw

Description:

    Initializes the DirectDraw object and its surfaces.

Arguments:

    None

Return Value:

    TRUE on success, FALSE on failure.

-------------------------------------------------------------------*/
BOOL
InitDirectDraw()
{
	HRESULT gr;
	DDSURFACEDESC ddsd;         // DirectDraw Surface Descriptor
	    // Find and create the proper DDraw device for our purposes.
    if (!CreateDirectDrawDevice())
    {
        gr = -1;
        ErrorMessage(NULL, TEXT("Create Direct Draw Device"));
        return FALSE;
    }

    // if UNDER_CE not defined,  run in windowed mode.
	// Else,  run in full screen mode

#ifdef UNDER_CE    
	gr = g_pdd->SetCooperativeLevel(g_hwndApp, DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN);
	if(FAILED(gr)){
		ErrorMessage(NULL, TEXT("Setting of Cooperative Level"));
		return FALSE;
	}
	
	// create a primary surface with a backbuffer.


	ddsd.dwSize            = sizeof(ddsd);
    ddsd.dwFlags           = DDSD_CAPS | DDSD_BACKBUFFERCOUNT;
    ddsd.ddsCaps.dwCaps    = DDSCAPS_PRIMARYSURFACE | DDSCAPS_FLIP | DDSCAPS_COMPLEX;
    ddsd.dwBackBufferCount = 1;


	gr = g_pdd->CreateSurface(&ddsd, &g_pddsPrimary, NULL);
	if(FAILED(gr)){
		ErrorMessage(NULL, TEXT("Can not create primary surface"));
		return FALSE;
	}

	ddsd.ddsCaps.dwCaps = DDSCAPS_BACKBUFFER;
	gr = g_pddsPrimary->GetAttachedSurface(&ddsd.ddsCaps, &g_pddsSecondary);
	if(FAILED(gr)){
		ErrorMessage(NULL, TEXT("Can not create Secondary surface"));
		return FALSE;
	}

#else  //Desktop

	gr = g_pdd->SetCooperativeLevel(g_hwndApp, DDSCL_NORMAL) ;

	if(FAILED(gr)){
		ErrorMessage(NULL, TEXT("Setting of Cooperative Level"));
		return FALSE;
	}
    // Setup to create the primary surface with no back buffer
    ddsd.dwSize            = sizeof(ddsd);
    ddsd.dwFlags           = DDSD_CAPS ;
    ddsd.ddsCaps.dwCaps    = DDSCAPS_PRIMARYSURFACE ;

	// Create the primary surface
    gr = g_pdd->CreateSurface(&ddsd, &g_pddsPrimary, NULL);
    

	if(FAILED(gr)){
		ErrorMessage(NULL, TEXT("Creation of Primary DirectDraw Surface"));
        return FALSE;
	}
	
	ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT |DDSD_WIDTH;
	ddsd.ddsCaps.dwCaps    = DDSCAPS_OFFSCREENPLAIN;
	ddsd.dwWidth = WINWIDTH;
	ddsd.dwHeight = WINHEIGHT;
	
	gr = g_pdd->CreateSurface(&ddsd, &g_pddsSecondary, NULL);
    

	if(FAILED(gr)){
		ErrorMessage(NULL, TEXT("Could not create Secondary DirectDraw Surface"));
        return FALSE;
	}

    gr  = g_pdd->CreateClipper( 0, &g_lpDDClipper, NULL );
	if(FAILED(gr)){
		ErrorMessage(NULL, TEXT("Couldn't create the clipper.\n"));
		return false;
    }

    // Associate our clipper with our hwnd so it will be updated
    // by Windows.
    gr  =  g_lpDDClipper->SetHWnd( 0, g_hwndApp );
	if (FAILED(gr)){
		ErrorMessage(NULL, TEXT("Couldn't set the hwnd.\n"));
		return false;
	}
    
	// Associate our clipper with the primary surface, so Blt 
    // will use it. 

    gr  =  g_pddsPrimary->SetClipper( g_lpDDClipper);
	
	if (FAILED(gr)){
		ErrorMessage(NULL, TEXT("Couldn't set the clipper.\n"));
		return false;
	}
    
    g_lpDDClipper->Release();
	
	
#endif //UNDER_CE
	
	return TRUE;
}


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    CreateDirectDrawDevice

Description:

    There is only one device on Dreamcast - create it using the NULL
    GUID and return.

Arguments:

    None

Return Value:

    TRUE on success, FALSE on failure.


-------------------------------------------------------------------*/
static BOOL
CreateDirectDrawDevice()
{
	HRESULT gr;
	IDirectDraw *pdd;

    gr = DirectDrawCreate(NULL, &pdd, NULL);
    
	if (FAILED(gr)){
		ErrorMessage(NULL, TEXT("Creation of DirectDraw Object"));
        return FALSE;
	}
	g_pdd = pdd;
    return TRUE;
}


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    LoadBitmapToDDS

Description:

    Loads a bitmap from a file or resource, creates a new DirectDraw
    surface, and copies the bitmap to that surface.

Arguments:

    LPTSTR szBitmap     -   Name of the texture to load
 
Return Value:

    LPDIRECTDRAWSURFACE -   A pointer to the loaded texture

-------------------------------------------------------------------*/
LPDIRECTDRAWSURFACE
LoadBitmapToDDS(LPTSTR tszBitmap)
{
    HBITMAP             hbitmap;    // Bitmap handle
    BITMAP              bitmap;     // Bitmap information
    DDSURFACEDESC       ddsd;       // Surface Descriptor
    LPDIRECTDRAWSURFACE pdds;       // Pointer to a DirectDraw surface
    HDC                 hdcBitmap;  // DC for bitmap
    HDC                 hdcSurface; // DC for DDraw surface
	HRESULT gr;

    // Try to Load the bitmap as a resource or a file
    hbitmap = (HBITMAP)LoadImage (g_hinst, tszBitmap, IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR );//| LR_LOADFROMFILE);
    if (hbitmap== NULL)
    {
		ErrorMessage(NULL, TEXT("FAILED"));	
        // FAILED to load the bitmap
        return NULL;
    }
	
    // Get the width, height and other info about the bitmap.
	
    GetObject (hbitmap, sizeof(BITMAP), &bitmap);

    // Create a DirectDrawSurface for this texture
    memset(&ddsd, 0, sizeof(ddsd));
    ddsd.dwSize         = sizeof(DDSURFACEDESC);
    ddsd.dwFlags        = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;
    ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;
	ImageWidth = ddsd.dwWidth   = bitmap.bmWidth;
    ImageHeight= ddsd.dwHeight  = bitmap.bmHeight;
    
	gr = g_pdd->CreateSurface(&ddsd, &pdds, NULL);
    if (FAILED(gr)){
		ErrorMessage(NULL, TEXT("Can not Create DDTexture surface"));
        return FALSE;
	}
	
    // Create an offscreen DC, and load the bitmap into it.
    hdcBitmap = CreateCompatibleDC (NULL);
    SelectObject (hdcBitmap, hbitmap);

    // Get a DC onto the DDraw surface.
    gr = pdds->GetDC (&hdcSurface);
    if (FAILED(gr)){
		ErrorMessage(NULL, TEXT("Can not Get DDraw DC"));
        return FALSE;
	}

    // Copy the bits from the bitmap to the DDraw surface.
    BitBlt (hdcSurface, 0, 0, bitmap.bmWidth, bitmap.bmHeight, hdcBitmap, 0, 0, SRCCOPY);

    // Clean up after ourselves.
    pdds->ReleaseDC (hdcSurface);
    DeleteDC (hdcBitmap);
    DeleteObject (hbitmap);

    return pdds;
}


