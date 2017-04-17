/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999 Microsoft Corporation

Module Name:

    MipUtil.cpp

Abstract:

   This file contains MipMapping functions for the MipMapping sample.

-------------------------------------------------------------------*/

#include "MipMapping.hpp"

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    LoadMipMap

Description:

    Loads a MipMap chain and returns a IDirect3DTexture texture interface.
    The levels are ordered with the nearest bitmap (the largest) first, and
    the farthest bitmap (the smallest) last surface, and copies the bitmap
    to that surface.  This function does not do automatic size reduction for
    automatically generated MipMaps - it assumes that the bitmap chain has
    been created by the application already.  This function also does not
    support palettized MipMaps; it is easy enough to add if your application
    requires it - simply call GetPalette on the system memory surface, and then
    SetPalette on the video memory surface with the returned palette.

Arguments:

    int    nLevels              - Number of levels to load

    TCHAR  *rgtszBitmapName[]   - Array of bitmap names, ordered nearest to farthest.
 
Return Value:

    LPDIRECTDRAWTEXTURE2        - Texture interface to the MipMap chain

-------------------------------------------------------------------*/
LPDIRECT3DTEXTURE2
LoadMipMap(int nLevels, TCHAR *rgtszBitmapName[])
{
    DDSURFACEDESC      ddsd;
    DDSCAPS            ddscaps;
    IDirectDrawSurface *pdds                = NULL;
    IDirectDrawSurface *pddsNextSystemMemory= NULL;
    IDirectDrawSurface *pddsSystemMemory    = NULL;
    IDirectDrawSurface *pddsVideoMemory     = NULL;
    LPDIRECT3DTEXTURE2 pd3dtexSystemMemory  = NULL;
    LPDIRECT3DTEXTURE2 pd3dtexVideoMemory   = NULL;
    BOOL               fFailed              = TRUE;
    int                i;

    // Load the top level bitmap
    pdds = LoadBitmapToDDS(rgtszBitmapName[0]);

    GetSurfaceDesc(&ddsd, pdds);

    // Create the system memory texture surface
    ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH | DDSD_PIXELFORMAT;
    ddsd.ddsCaps.dwCaps = DDSCAPS_TEXTURE | DDSCAPS_SYSTEMMEMORY | DDSCAPS_MIPMAP | DDSCAPS_COMPLEX;
    ddsd.ddpfPixelFormat.dwSize = sizeof(DDPIXELFORMAT);
    g_errLast = g_pdd->CreateSurface(&ddsd, &pddsSystemMemory, NULL);
    if (CheckError(TEXT("CreateSurface for video memory MipMap texture (level %d)"), i))
        goto done;

    // Copy the bitmap onto the system memory texture surface
    g_errLast = pddsSystemMemory->Blt(NULL, pdds, NULL, 0, NULL);
    if (CheckError(TEXT("Blt bitmap to surface memory mipmap texture")))
        goto done;

    // We no longer need the bitmap itself
    pdds->Release();

    ddscaps.dwCaps = DDSCAPS_TEXTURE | DDSCAPS_MIPMAP;

    // Copy the other levels of the mipmap into the system memory surfaces
    g_errLast = pddsSystemMemory->GetAttachedSurface(&ddscaps, &pddsNextSystemMemory);
        if (CheckError(TEXT("Get Attached Surface")))
            goto done;

    for (i = 1; i < nLevels; i++)
    {
        IDirectDrawSurface *pddsTemp;
        pdds = LoadBitmapToDDS(rgtszBitmapName[i]);

        g_errLast = pddsNextSystemMemory->Blt(NULL, pdds, NULL, 0, NULL);
        if (CheckError(TEXT("Blt to lower level MipMap")))
            goto done;

        g_errLast = pddsNextSystemMemory->GetAttachedSurface(&ddscaps, &pddsTemp);
        if (CheckError(TEXT("Get Attached Surface")))
            goto done;

        pddsNextSystemMemory->Release();
        pdds->Release();

        pddsNextSystemMemory = pddsTemp;
    }

    // Query for the texture interface
    g_errLast = pddsSystemMemory->QueryInterface(IID_IDirect3DTexture2, (LPVOID*)&pd3dtexSystemMemory);
    if (CheckError(TEXT("QueryInterface for Texture Interface")))
        goto done;

    // Create a video memory texture
    ddsd.ddsCaps.dwCaps &= ~DDSCAPS_SYSTEMMEMORY;   // Don't specify a memory location
    ddsd.ddsCaps.dwCaps |= DDSCAPS_ALLOCONLOAD;

    g_errLast = g_pdd->CreateSurface(&ddsd, &pddsVideoMemory, NULL);
    if (CheckError(TEXT("QueryInterface for Texture Interface")))
        goto done;

    g_errLast = pddsVideoMemory->QueryInterface(IID_IDirect3DTexture2, (LPVOID*)&pd3dtexVideoMemory);
    if (CheckError(TEXT("QueryInterface for Texture Interface")))
        goto done;

    // Load the source texture into the destination.
    g_errLast = pd3dtexVideoMemory->Load(pd3dtexSystemMemory);
    if (CheckError(TEXT("Load source into destination")))
        goto done;


    // If we got here, then everything went just fine.
    fFailed = FALSE;

done:

    // Release any interfaces which remain.
    if (pddsNextSystemMemory)
        pddsNextSystemMemory->Release();

    if (pd3dtexSystemMemory)
        pd3dtexSystemMemory->Release();

    // If we failed during the last 'Load' call, we need to release the video memory texture
    // interfaces as well.
    if (fFailed && pd3dtexVideoMemory)
        pd3dtexVideoMemory->Release();

    if (pddsVideoMemory)
        pddsVideoMemory->Release();

    if (pddsSystemMemory)
        pddsSystemMemory->Release();

    return pd3dtexVideoMemory;
}
