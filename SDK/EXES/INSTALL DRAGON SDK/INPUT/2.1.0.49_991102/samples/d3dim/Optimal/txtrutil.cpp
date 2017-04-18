/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999 Microsoft Corporation

Module Name:

    TxtrUtil.cpp

Abstract:

    Contains Direct3D Texture functionality.

-------------------------------------------------------------------*/

// ++++ Include Files +++++++++++++++++++++++++++++++++++++++++++++++
#include "Optimal.hpp"

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    LoadTexture

Description:

    Creates a texture map surface and texture object from the named 
    bitmap file.  This is done in a two step process.  A source 
    DirectDraw surface and bitmap are created in system memory.  A second,
    initially empty, texture surface is created (in video memory if hardware
    is present).  The source bitmap is loaded into the destination texture
    surface and then discarded. This process allows a device to compress or
    reformat a texture map as it enters video memory during the Load call.

Arguments:

    TCHAR *tstrFileName  - Name of the texture to open

Return Value:

    LPDIRECT3DTEXTURE2   - Pointer to the loaded Texture (or NULL if failure)

-------------------------------------------------------------------*/
LPDIRECT3DTEXTURE2 
LoadTexture(TCHAR *tstrFileName)
{
    DDSURFACEDESC       ddsd;
    LPDIRECTDRAWSURFACE pddsBitmap,     pddsTexture;
    LPDIRECT3DTEXTURE2  pd3dtextureSrc, pd3dtextureDest;

    // Create a surface in system memory and load the bitmap file into it.
    pddsBitmap = LoadBitmapToDDS(tstrFileName);
    if (!pddsBitmap)
    {
        DebugOutput(TEXT("ERROR: Unable to load texture %s\r\n"), tstrFileName);
        return NULL;
    }

    // Create an empty texture surface to load the source texture into.
    // The DDSCAPS_ALLOCONLOAD flag allows the DD driver to wait until the
    // load call to allocate the texture in memory because at this point,
    // we may not know how much memory the texture will take up (e.g. it
    // could be compressed to an unknown size in video memory).
    GetSurfaceDesc(&ddsd, pddsBitmap);

    ddsd.dwFlags        = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;
    ddsd.ddsCaps.dwCaps = DDSCAPS_TEXTURE | DDSCAPS_ALLOCONLOAD | DDSCAPS_VIDEOMEMORY;

    g_errLast = g_pdd->CreateSurface(&ddsd, &pddsTexture, NULL);
    if (CheckError(TEXT("Create Destination Texture Surface")))
        return NULL;

    // Query our source surface for a texture interface.  This is necessary for the 'Load()' command.
    g_errLast = pddsBitmap->QueryInterface(IID_IDirect3DTexture2, (LPVOID*)&pd3dtextureSrc);
    if (CheckError(TEXT("Query D3D Texture interface")))
        return NULL;

    // Query our destination surface for a texture interface
    g_errLast = pddsTexture->QueryInterface(IID_IDirect3DTexture2,(LPVOID*)&pd3dtextureDest);
    if (CheckError(TEXT("Query D3D Texture Interface")))
        return NULL;

    // Load the source texture into the destination.  During this call, a
    // driver could compress or reformat the texture surface and put it in video memory.
    g_errLast = pd3dtextureDest->Load(pd3dtextureSrc);
    if (CheckError(TEXT("Load Source Texture into Destination Texture")))
        return NULL;

    // Release no-longer-necessary surfaces
    pd3dtextureSrc->Release();
    pddsBitmap->Release();

    return pd3dtextureDest;
}
