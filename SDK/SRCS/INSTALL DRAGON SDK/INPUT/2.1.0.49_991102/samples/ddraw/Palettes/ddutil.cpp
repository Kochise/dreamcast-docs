/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999 Microsoft Corporation

Module Name:

    DDUtil.cpp

Abstract:

   This file contains DirectDraw functionality for the Palettes sample.

-------------------------------------------------------------------*/

// ++++ Include Files +++++++++++++++++++++++++++++++++++++++++++++++
#include "Palettes.hpp"

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
    ddsd.ddsCaps.dwCaps    = DDSCAPS_PRIMARYSURFACE | DDSCAPS_FLIP | DDSCAPS_COMPLEX;
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

    LoadBitmapToPalettizedDDS

Description:

    Loads a bitmap from a file or resource, creates a new palettized
    DirectDraw surface, and copies the bitmap to that surface.  The bitmap
    being loaded must be an 8bpp bitmap.

    Order of operation:
        a. Load the bitmap from a file to a HBITMAP object
        c. Create a system memory surface
        d. Copy the HBITMAP to the system memory surface
        b. Create a twiddled palettized video memory surface
        e. Create the palette and attach it to the video memory surface
        f. BitBlt from the system memory surface to the video memory surface
        g. Delete the system memory surface
        h. Return the video memory surface

Arguments:

    LPTSTR szBitmap     -   Name of the texture to load
 
Return Value:

    LPDIRECTDRAWSURFACE -   A pointer to the loaded surface

-------------------------------------------------------------------*/
LPDIRECTDRAWSURFACE
LoadBitmapToPalettizedDDS(LPTSTR tszBitmap)
{
    HBITMAP             hbitmap;    // Bitmap handle
    BITMAP              bitmap;     // Bitmap information
    DDSURFACEDESC       ddsd;       // Surface Descriptor
    LPDIRECTDRAWPALETTE pddp;
    LPDIRECTDRAWSURFACE pddsSystemMemory;
    LPDIRECTDRAWSURFACE pddsVideoMemory;
    PALETTEENTRY        ppe[256];
    LPBYTE              pfile;
    int                 i;

    // Load the bitmap from the resource file
    hbitmap = (HBITMAP)LoadImage (g_hinst, tszBitmap, IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR);
    if (hbitmap== NULL)
    {
        // Failed to load the bitmap
        return NULL;
    }

    // Get the width, height and other info about the bitmap.
    GetObject (hbitmap, sizeof(BITMAP), &bitmap);

    // Create the palettized system memory ddraw surface.  Note - this assume 8bpp; use
    // "DDPF_PALETTEINDEXED4" for 4bpp surface
    memset(&ddsd, 0, sizeof(ddsd));
    ddsd.dwSize         = sizeof(DDSURFACEDESC);
    ddsd.dwFlags        = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH | DDSD_PIXELFORMAT;
    ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_SYSTEMMEMORY;
    ddsd.dwWidth        = bitmap.bmWidth;
    ddsd.dwHeight       = bitmap.bmHeight;
    ddsd.ddpfPixelFormat.dwSize        = sizeof(DDPIXELFORMAT);
    ddsd.ddpfPixelFormat.dwFlags       = DDPF_RGB | DDPF_PALETTEINDEXED8;
    ddsd.ddpfPixelFormat.dwRGBBitCount = 8;

    g_errLast = g_pdd->CreateSurface(&ddsd, &pddsSystemMemory, NULL);
    if (CheckError(TEXT("Create DDTexture surface")))
        return NULL;

    // Create a palette from the color table in the bitmap

    // Clear all palette entries
    memset(&ppe, 0, sizeof(PALETTEENTRY) * 256);

    // Copy the palette information from the source bitmap - this code
    // assumes the bitmap is in the app's resource file.
    HGLOBAL           hg;
    HRSRC             hrsrc;
    UNALIGNED RGBQUAD *prgbq;

    if (!(hrsrc = FindResource(g_hinst, tszBitmap, RT_BITMAP))) 
    {
        RetailOutput(TEXT("FindResource failed to find %s"), tszBitmap);
        return NULL;
    }

    if (!(hg = LoadResource(g_hinst, hrsrc)))
    {
        RetailOutput(TEXT("LoadResource failed to load %s"), tszBitmap);
        return NULL;
    }

    pfile = (LPBYTE)LockResource(hg);
    if (!pfile)
    {
        RetailOutput(TEXT("LockResource failed to lock %s"), tszBitmap);
        return NULL;
    }

    prgbq = (RGBQUAD*)(pfile + sizeof(BITMAPINFOHEADER));

    // Copy the entries from the bitmap palette
    for (i = 0; i < (UINT)256; i++)
    {
        ppe[i].peRed = prgbq[i].rgbRed;
        ppe[i].peGreen = prgbq[i].rgbGreen;
        ppe[i].peBlue = prgbq[i].rgbBlue;
    }

    // Create the palette
    g_errLast = g_pdd->CreatePalette(DDPCAPS_8BIT, ppe, &pddp, NULL);
    if (CheckError(TEXT("IDirectDraw::CreatePalette")))
        return NULL;

    // Attach the palette to the texture surface
    g_errLast = pddsSystemMemory->SetPalette(pddp);

    // Release a reference on the palette
    pddp->Release();

    if (CheckError(TEXT("IDirectDrawSurface::SetPalette")))
        return NULL;

    // Create an offscreen DC for the bitmap
    HDC hdcSrc = CreateCompatibleDC(NULL);
    HDC hdcDst;
    if (!hdcSrc)
    {
        RetailOutput(TEXT("CreateCompatibleDC failed for %s"), tszBitmap);
        return NULL;
    }

    SelectObject(hdcSrc, hbitmap);

    // Get a DC on the texture surface
    g_errLast = pddsSystemMemory->GetDC(&hdcDst);
    if (CheckError(TEXT("IDirectDrawSurface::GetDC")))
        return NULL;

    // Copy the bitmap into the texture
    if (!BitBlt(hdcDst, 0, 0, bitmap.bmWidth, bitmap.bmHeight, hdcSrc, 0, 0, SRCCOPY)) 
    {
        RetailOutput(TEXT("BitBlt failed for %s"), tszBitmap);
        return NULL;
    }

    // Release the DC
    pddsSystemMemory->ReleaseDC(hdcDst);

    // Create the (twiddled) video memory surface that we will load the palettized surface into.
    memset(&ddsd, 0, sizeof(ddsd));
    ddsd.dwSize = sizeof(ddsd);
    g_errLast = pddsSystemMemory->GetSurfaceDesc(&ddsd);
    if (CheckError(TEXT("GetSurfaceDesc")))
        return NULL;

    ddsd.ddsCaps.dwCaps &= ~DDSCAPS_SYSTEMMEMORY;   // Don't specify a memory location
    ddsd.ddsCaps.dwCaps |= DDSCAPS_ALLOCONLOAD;

    g_errLast = g_pdd->CreateSurface(&ddsd, &pddsVideoMemory, NULL);
    if (CheckError(TEXT("IDirectDraw::CreateSurface")))
        return NULL;

    // Attach the palette to the device memory surface
    g_errLast = pddsVideoMemory->SetPalette(pddp);
    if (CheckError(TEXT("SetPalette")))
        return NULL;

    // BitBlt from the system memory surface to the video memory surface - this will twiddle the
    // bitmap, which is required for hardware-memory palettized surfaces (this is a requirement of
    // the hardware).
    pddsVideoMemory->Blt(NULL, pddsSystemMemory, NULL, 0, NULL);

    // No longer need the system memory surface
    pddsSystemMemory->Release();
    return pddsVideoMemory;
}

