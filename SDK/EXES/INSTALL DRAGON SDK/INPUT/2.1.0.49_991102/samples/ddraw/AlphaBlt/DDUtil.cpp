/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999 Microsoft Corporation

Module Name:

    DDUtil.cpp

Abstract:

   This file contains DirectDraw functionality for the AlphaBlt sample.

-------------------------------------------------------------------*/

// ++++ Include Files +++++++++++++++++++++++++++++++++++++++++++++++
#include "AlphaBlt.hpp"

// ++++ Global Variables ++++++++++++++++++++++++++++++++++++++++++++
LPDIRECTDRAW        g_pdd;          // The DirectDraw object
LPDIRECTDRAWSURFACE g_pddsPrimary;  // Primary DirectDraw surface
LPDIRECTDRAWSURFACE g_pddsBack;     // Backbuffer DirectDraw surface

// ++++ Local functions +++++++++++++++++++++++++++++++++++++++++++++
static BOOL CreateDirectDrawDevice();

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
    DDSURFACEDESC ddsd;         // DirectDraw Surface Descriptor

    // Find and create the proper DDraw device for our purposes.
    if (!CreateDirectDrawDevice())
    {
        g_errLast = -1;
        CheckError(TEXT("Create Direct Draw Device"));
        return FALSE;
    }

    // Get exclusive mode.  Full-screen mode requires 'DDSCL_EXCLUSIVE'.
    g_errLast = g_pdd->SetCooperativeLevel(g_hwndApp, DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN);
    if (CheckError(TEXT("Setting of Cooperative Level")))
        return FALSE;

    // Set Display Mode
    g_errLast = g_pdd->SetDisplayMode(640, 480, 16);
    if (CheckError(TEXT("Setting of Display Mode")))
        return FALSE;

    // Setup to create the primary surface with 1 back buffer
    ddsd.dwSize            = sizeof(ddsd);
    ddsd.dwFlags           = DDSD_CAPS | DDSD_BACKBUFFERCOUNT;

    // NOTICE: Addition of 'DDSCAPS_3DDEVICE' to primary surface description.  This 
    // is so d3d can render our 3D alphablended surface to the display.
    ddsd.ddsCaps.dwCaps    = DDSCAPS_PRIMARYSURFACE | DDSCAPS_FLIP | DDSCAPS_COMPLEX | DDSCAPS_3DDEVICE;
    ddsd.dwBackBufferCount = 1;

    // Create the primary surface
    g_errLast = g_pdd->CreateSurface(&ddsd, &g_pddsPrimary, NULL);
    if (CheckError(TEXT("Creation of Primary DirectDraw Surface")))
        return FALSE;

    // Get a pointer to the back buffer
    ddsd.ddsCaps.dwCaps = DDSCAPS_BACKBUFFER;
    g_errLast = g_pddsPrimary->GetAttachedSurface(&ddsd.ddsCaps, &g_pddsBack);
    if (CheckError(TEXT("Obtaining of Back Buffer pointer")))
        return FALSE;

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
    g_errLast = DirectDrawCreate(NULL, &g_pdd, NULL);
    if (CheckError(TEXT("Creation of DirectDraw Object")))
        return FALSE;


    return TRUE;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    FlipBuffers

Description:

    If 'USE_WINDOW' is defined, then Blt the back buffer to the front.
    If 'USE_WINDOW' is not defined, then flip the back and front buffers.

Arguments:

    None

Return Value:

    None

-------------------------------------------------------------------*/
void
FlipBuffers()
{

    // Flip the Back Buffer to the Front Buffer
    g_errLast = g_pddsPrimary->Flip(NULL, DDFLIP_WAIT);
    CheckError(TEXT("Flipping of Buffers"));
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    GetSurfaceDesc

Description:

    Gets the surface information for the passed-in surface

Arguments:

    LPDDSURFACEDESC     pddsurfdesc   - Structure filled with information

    LPDIRECTDRAWSURFACE pddsurf       - Surface to get the information from.
 
Return Value:

    HRESULT                           - Result of function

-------------------------------------------------------------------*/
HRESULT
GetSurfaceDesc(LPDDSURFACEDESC pddsurfdesc, LPDIRECTDRAWSURFACE pddsurf)
{
    memset(pddsurfdesc, 0, sizeof(DDSURFACEDESC));
    pddsurfdesc->dwSize = sizeof(DDSURFACEDESC);
    
    return pddsurf->GetSurfaceDesc(pddsurfdesc);
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

    // Try to Load the bitmap as a resource or a file
    hbitmap = (HBITMAP)LoadImage (g_hinst, tszBitmap, IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR);
    if (hbitmap== NULL)
    {
        // Failed to load the bitmap
        return NULL;
    }

    // Get the width, height and other info about the bitmap.
    GetObject (hbitmap, sizeof(BITMAP), &bitmap);

    // Create a DirectDrawSurface for this texture
    memset(&ddsd, 0, sizeof(ddsd));
    GetSurfaceDesc(&ddsd, g_pddsBack);  

    ddsd.dwSize         = sizeof(DDSURFACEDESC);
    ddsd.dwFlags        = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;
    ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;

    ddsd.dwWidth        = bitmap.bmWidth;
    ddsd.dwHeight       = bitmap.bmHeight;
    g_errLast = g_pdd->CreateSurface(&ddsd, &pdds, NULL);
    if (CheckError(TEXT("Create DDTexture surface")))
        return NULL;

    // Create an offscreen DC, and load the bitmap into it.
    hdcBitmap = CreateCompatibleDC (NULL);
    SelectObject (hdcBitmap, hbitmap);

    // Get a DC onto the DDraw surface.
    g_errLast = pdds->GetDC (&hdcSurface);
    if (CheckError(TEXT("Get DDraw DC")))
        return NULL;

    // Copy the bits from the bitmap to the DDraw surface.
    BitBlt (hdcSurface, 0, 0, bitmap.bmWidth, bitmap.bmHeight, hdcBitmap, 0, 0, SRCCOPY);

    // Clean up after ourselves.
    pdds->ReleaseDC (hdcSurface);
    DeleteDC (hdcBitmap);
    DeleteObject (hbitmap);

    return pdds;
}
