/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999 Microsoft Corporation

Module Name:

    TxtrUtil.cpp

Abstract:

    Contains Direct3D Texture functionality.

-------------------------------------------------------------------*/

// ++++ Include Files +++++++++++++++++++++++++++++++++++++++++++++++
#include "RearViewMirror.hpp"

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
    DDSURFACEDESC2       ddsd;
    LPDIRECTDRAWSURFACE4 pddsBitmap,     pddsTexture;
    LPDIRECT3DTEXTURE2   pd3dtextureSrc, pd3dtextureDest;

    // Create a surface in system memory and load the bitmap file into it.
    pddsBitmap = LoadBitmapToDDS(tstrFileName);
    if (!pddsBitmap)
    {
        DebugOutput(TEXT("ERROR: Unable to load texture %s\r\n"), tstrFileName);
        return NULL;
    }

    // Query our source surface for a texture interface.  This is necessary for the 'Load()' command.
    g_errLast = pddsBitmap->QueryInterface(IID_IDirect3DTexture2, (LPVOID*)&pd3dtextureSrc);

    // Release the no-longer-necessary bitmap surface
    pddsBitmap->Release();

    if (CheckError(TEXT("Query D3D Texture interface")))
        return NULL;

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

    // Query our destination surface for a texture interface
    g_errLast = pddsTexture->QueryInterface(IID_IDirect3DTexture2,(LPVOID*)&pd3dtextureDest);

    // Release the no-longer-necessary texture surface
    pddsTexture->Release();

    if (CheckError(TEXT("Query D3D Texture Interface")))
        return NULL;

    // Load the source texture into the destination.  During this call, a
    // driver could compress or reformat the texture surface and put it in video memory.
    g_errLast = pd3dtextureDest->Load(pd3dtextureSrc);

    // Release no-longer-necessary system memory texture
    pd3dtextureSrc->Release();

    if (CheckError(TEXT("Load Source Texture into Destination Texture")))
        return NULL;

    return pd3dtextureDest;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    LoadAlphaTexture

Description:

    Creates a texture map surface and texture object and initializes
    it with alpha information based on the named bitmap file.  The bitmap
    is first loaded into a temporary surface.  Next a system memory texture
    is created and its alpha bits are initialized proportionally to the
    color information interpolated from the bitmap surface.  Finally a
    device memory texture is loaded from the system memory texture (as
    done by the LoadTexture function).

Arguments:

    TCHAR *tstrFileName  - Name of the texture to open

Return Value:

    LPDIRECT3DTEXTURE2   - Pointer to the loaded Texture (or NULL if failure)

-------------------------------------------------------------------*/
LPDIRECT3DTEXTURE2 
LoadAlphaTexture(TCHAR *tstrFileName)
{
    DDSURFACEDESC2       ddsdSrc,        ddsdDst;
    LPDIRECTDRAWSURFACE4 pddsBitmap,     
                         pddsTextureSrc, pddsTextureDst;
    LPDIRECT3DTEXTURE2   pd3dTextureSrc, pd3dTextureDst;
    D3DVALUE             rAlpha;
    WORD                 wAlpha;
    LPWORD               pwPixelSrc,     pwPixelDst;
    DWORD                dwPitchSrc,     dwPitchDst,
                         dwRMask, dwGMask, dwBMask;
    UINT                 i, j;

    // Create a temporary surface in system memory and load the bitmap file into it.
    pddsBitmap = LoadBitmapToDDS(tstrFileName);
    if (!pddsBitmap)
    {
        DebugOutput(TEXT("ERROR: Unable to load texture %s\r\n"), tstrFileName);
        return NULL;
    }

    GetSurfaceDesc(&ddsdSrc, pddsBitmap);

    // Create a system memory texture with alpha information.  An RGBA 4444
    // pixel format will be used.
    memset(&ddsdDst, 0, sizeof(DDSURFACEDESC2));
    ddsdDst.dwSize         = sizeof(DDSURFACEDESC2);
    ddsdDst.dwFlags        = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH | DDSD_PIXELFORMAT;
    ddsdDst.ddsCaps.dwCaps = DDSCAPS_TEXTURE | DDSCAPS_SYSTEMMEMORY;
    ddsdDst.dwWidth        = ddsdSrc.dwWidth;
    ddsdDst.dwHeight       = ddsdSrc.dwHeight;

    ddsdDst.ddpfPixelFormat.dwSize            = sizeof(DDPIXELFORMAT);
    ddsdDst.ddpfPixelFormat.dwFlags           = DDPF_RGB | DDPF_ALPHAPIXELS;
    ddsdDst.ddpfPixelFormat.dwRGBBitCount     = 16;
    ddsdDst.ddpfPixelFormat.dwRBitMask        = 0x0F00;
    ddsdDst.ddpfPixelFormat.dwGBitMask        = 0x00F0;
    ddsdDst.ddpfPixelFormat.dwBBitMask        = 0x000F;
    ddsdDst.ddpfPixelFormat.dwRGBAlphaBitMask = 0xF000;

    g_errLast = g_pdd->CreateSurface(&ddsdDst, &pddsTextureSrc, NULL);
    if (CheckError(TEXT("Create Texture Surface")))
    {
        pddsBitmap->Release();
        return NULL;
    }

    // Lock the bitmap surface
    memset(&ddsdSrc, 0, sizeof(DDSURFACEDESC2));
    ddsdSrc.dwSize = sizeof(DDSURFACEDESC2);
    g_errLast = pddsBitmap->Lock(NULL, &ddsdSrc, DDLOCK_SURFACEMEMORYPTR | DDLOCK_WAIT, NULL);
    if (CheckError(TEXT("Lock Bitmap Surface")))
    {
        pddsTextureSrc->Release();
        pddsBitmap->Release();
        return NULL;
    }

    // Lock the texture surface
    memset(&ddsdDst, 0, sizeof(DDSURFACEDESC2));
    ddsdDst.dwSize = sizeof(DDSURFACEDESC2);
    g_errLast = pddsTextureSrc->Lock(NULL, &ddsdDst, DDLOCK_SURFACEMEMORYPTR | DDLOCK_WAIT, NULL);
    if (CheckError(TEXT("Lock Bitmap Surface")))
    {
        pddsTextureSrc->Release();
        pddsBitmap->Release();
        return NULL;
    }

    // Initialize the alpha bits of the system memory surface proportionally to the
    // color information contained in the bitmap surface
    pwPixelSrc = (LPWORD)ddsdSrc.lpSurface;
    pwPixelDst = (LPWORD)ddsdDst.lpSurface;
    dwPitchSrc = ddsdSrc.lPitch / (sizeof(WORD) / sizeof(BYTE));
    dwPitchDst = ddsdDst.lPitch / (sizeof(WORD) / sizeof(BYTE));
    dwRMask = ddsdSrc.ddpfPixelFormat.dwRBitMask;
    dwGMask = ddsdSrc.ddpfPixelFormat.dwRBitMask;
    dwBMask = ddsdSrc.ddpfPixelFormat.dwRBitMask;

    for (i = 0; i < ddsdSrc.dwHeight; i++) 
    {
        for (j = 0; j < ddsdSrc.dwWidth; j++) 
        {
            // Interpolate the red, green, and blue components of the source bitmap
            // into an intensity value between 0.0 and 1.0
            rAlpha = (D3DVAL(*(pwPixelSrc + j) & dwRMask) / D3DVAL(dwRMask) +
                      D3DVAL(*(pwPixelSrc + j) & dwGMask) / D3DVAL(dwGMask) +
                      D3DVAL(*(pwPixelSrc + j) & dwBMask) / D3DVAL(dwBMask)) / 3.0f;

            // Initialize the alpha bits according to the intensity value
            wAlpha = (UINT)(D3DVAL(ddsdDst.ddpfPixelFormat.dwRGBAlphaBitMask) * rAlpha) 
                            & ddsdDst.ddpfPixelFormat.dwRGBAlphaBitMask;

            // Set the alpha bits in the destination pixel
            *(pwPixelDst + j) = wAlpha | (~(WORD)ddsdDst.ddpfPixelFormat.dwRGBAlphaBitMask 
                                        & 0xFFFF);
        }

        pwPixelSrc += dwPitchSrc;
        pwPixelDst += dwPitchDst;
    }

    // Unlock the texture surface
    pddsTextureSrc->Unlock(NULL);

    // Unlock and release the bitmap surface
    pddsBitmap->Unlock(NULL);
    pddsBitmap->Release();

    // Create an empty texture surface to load the source texture into.
    // The DDSCAPS_ALLOCONLOAD flag allows the DD driver to wait until the
    // load call to allocate the texture in memory because at this point,
    // we may not know how much memory the texture will take up (e.g. it
    // could be compressed to an unknown size in video memory).
    GetSurfaceDesc(&ddsdDst, pddsTextureSrc);

    ddsdDst.ddsCaps.dwCaps &= ~DDSCAPS_SYSTEMMEMORY;
    ddsdDst.ddsCaps.dwCaps |= DDSCAPS_ALLOCONLOAD;

    g_errLast = g_pdd->CreateSurface(&ddsdDst, &pddsTextureDst, NULL);
    if (CheckError(TEXT("Create Destination Texture Surface")))
    {
        pddsTextureSrc->Release();
        return NULL;
    }

    // Query our source surface for a texture interface.  This is necessary for the 'Load()' command.
    g_errLast = pddsTextureSrc->QueryInterface(IID_IDirect3DTexture2, (LPVOID*)&pd3dTextureSrc);

    // Release the surface interface
    pddsTextureSrc->Release();

    if (CheckError(TEXT("Query D3D Texture interface"))) 
    {
        pddsTextureDst->Release();
        return NULL;
    }

    // Query our destination surface for a texture interface
    g_errLast = pddsTextureDst->QueryInterface(IID_IDirect3DTexture2,(LPVOID*)&pd3dTextureDst);

    // Release the surface interface
    pddsTextureDst->Release();

    if (CheckError(TEXT("Query D3D Texture Interface"))) 
    {
        pd3dTextureSrc->Release();
        return NULL;
    }

    // Load the source texture into the destination.  During this call, a
    // driver could compress or reformat the texture surface and put it in video memory.
    g_errLast = pd3dTextureDst->Load(pd3dTextureSrc);

    // Release no-longer-necessary surfaces
    pd3dTextureSrc->Release();

    if (CheckError(TEXT("Load Source Texture into Destination Texture")))
        return NULL;

    return pd3dTextureDst;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    CreateTargetTexture

Description:

    Creates a rendering-capable texture map surface and texture object 
    with the given dimensions in video memory.

Arguments:

    DWORD dwWidth        - Width of the texture

    DWORD dwHeight       - Height of the texture

Return Value:

    LPDIRECT3DTEXTURE2   - Pointer to the created Texture (or NULL if failure)

-------------------------------------------------------------------*/
LPDIRECT3DTEXTURE2 
CreateTargetTexture(DWORD dwWidth, DWORD dwHeight)
{
    DDSURFACEDESC2       ddsd;
    LPDIRECTDRAWSURFACE4 pdds;
    LPDIRECT3DTEXTURE2   pd3dtexture;

    // Create a texture surface in video memory using the given 
    // dimensions.  The DDSCAPS_3DDEVICE flag allows
    // the texture to be used as a rendering target.
    memset(&ddsd, 0, sizeof(DDSURFACEDESC2));
    ddsd.dwSize         = sizeof(DDSURFACEDESC2);
    ddsd.dwFlags        = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;
    ddsd.ddsCaps.dwCaps = DDSCAPS_TEXTURE | DDSCAPS_VIDEOMEMORY | DDSCAPS_3DDEVICE;
    ddsd.dwWidth        = dwWidth;
    ddsd.dwHeight       = dwHeight;

    g_errLast = g_pdd->CreateSurface(&ddsd, &pdds, NULL);
    if (CheckError(TEXT("Create Texture Surface")))
        return NULL;

    // Query our surface for a texture interface
    g_errLast = pdds->QueryInterface(IID_IDirect3DTexture2,(LPVOID*)&pd3dtexture);

    // Release no-longer-necessary surfaces
    pdds->Release();

    if (CheckError(TEXT("Query D3D Texture Interface")))
        return NULL;

    return pd3dtexture;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    SetColorStage

Description:

    Simplifies the setting of a color texture stage.  The function
    will make three calls to SetTextureStageState to set the color
    blending operation and arguments for the given stage.

Arguments:

    DWORD dwStage        - Color stage to set

    DWORD dwArg1         - The first color argument for the stage
                           (corresponding to the D3DTSS_COLORARG1
                           texture stage type)

    DWORD dwArg2         - The second color argument for the stage
                           (corresponding to the D3DTSS_COLORARG2
                           texture stage type)

    D3DTEXTUREOP d3dtop  - The color blending operation to apply 
                           to the stage (corresponding to the 
                           D3DTSS_COLOROP texture stage type)

Return Value:

    HRESULT              - D3D_OK on success or the error returned by
                           SetTextureStageState on failure

-------------------------------------------------------------------*/
HRESULT SetColorStage(DWORD dwStage, DWORD dwArg1, DWORD dwArg2, D3DTEXTUREOP d3dtop)
{
    HRESULT hr;
    hr = g_p3ddevice->SetTextureStageState(dwStage, D3DTSS_COLOROP, d3dtop);
    if (FAILED(hr)) 
        return hr;
    hr = g_p3ddevice->SetTextureStageState(dwStage, D3DTSS_COLORARG1, dwArg1);
    if (FAILED(hr)) 
        return hr;
    hr = g_p3ddevice->SetTextureStageState(dwStage, D3DTSS_COLORARG2, dwArg2);
    return hr;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    SetAlphaStage

Description:

    Simplifies the setting of an alpha texture stage.  The function
    will make three calls to SetTextureStageState to set the alpha
    blending operation and arguments for the given stage.

Arguments:

    DWORD dwStage        - Alpha stage to set

    DWORD dwArg1         - The first alpha argument for the stage
                           (corresponding to the D3DTSS_ALPHAARG1
                           texture stage type)

    DWORD dwArg2         - The second alpha argument for the stage
                           (corresponding to the D3DTSS_ALPHAARG2
                           texture stage type)

    D3DTEXTUREOP d3dtop  - The alpha blending operation to apply 
                           to the stage (corresponding to the 
                           D3DTSS_ALPHAOP texture stage type)

Return Value:

    HRESULT              - D3D_OK on success or the error returned by
                           SetTextureStageState on failure

-------------------------------------------------------------------*/
HRESULT SetAlphaStage(DWORD dwStage, DWORD dwArg1, DWORD dwArg2, D3DTEXTUREOP d3dtop)
{
    HRESULT hr;
    hr = g_p3ddevice->SetTextureStageState(dwStage, D3DTSS_ALPHAOP, d3dtop);
    if (FAILED(hr)) 
        return hr;
    hr = g_p3ddevice->SetTextureStageState(dwStage, D3DTSS_ALPHAARG1, dwArg1);
    if (FAILED(hr)) 
        return hr;
    hr = g_p3ddevice->SetTextureStageState(dwStage, D3DTSS_ALPHAARG2, dwArg2);
    return hr;
}
