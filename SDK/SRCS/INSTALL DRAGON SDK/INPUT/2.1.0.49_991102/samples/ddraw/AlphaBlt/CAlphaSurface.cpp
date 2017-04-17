/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1998 Microsoft Corporation

Module Name:

    CAlphaSurface.cpp

Abstract:

    Alpha Blting Surface class definition

Notes:

    This sample does not support multiple different global DirectDraw
    objects.

-------------------------------------------------------------------*/

// ++++ Include Files +++++++++++++++++++++++++++++++++++++++++++++++
#define D3D_OVERLOADS
#include "AlphaBlt.hpp"

// ++++ Local Variables +++++++++++++++++++++++++++++++++++++++++++++

float g_z = 0.001f;                               // Used to ensure Blts appear in correct order
WORD  g_wPowerOfTwo[4097];                          // Used to round up texture size to a power of two.

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    CAlphaSurface::CAlphaSurface

Description:

    Initialization function for CAlphaSurface object

Arguments:

    LPDIRECT3DDEVICE2 p3ddevice - The 3D device to which this surface is attached.
  
Return Value:

    None

-------------------------------------------------------------------*/
CAlphaSurface::CAlphaSurface(LPDIRECT3DDEVICE2 p3ddevice)
{
    // This function assumes the app has already created and initialized the 3ddevice that this alpha surface
    // will be blt to.
    m_p3ddevice = p3ddevice;
    m_ptexture  = NULL;
    m_hTexture  = NULL;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    CAlphaSurface::~CAlphaSurface

Description:

    Destructor function for CAlphaSurface object

Arguments:

    None
  
Return Value:

    None

-------------------------------------------------------------------*/
CAlphaSurface::~CAlphaSurface()
{
    if (m_ptexture)
        m_ptexture->Release();
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    InitPowerOfTwo

Description:

    Helper function to generate a power-of-two table.  This is used to
    round the size of textures up to a power of two.

Arguments:

    None
  
Return Value:

    None

-------------------------------------------------------------------*/
void
InitPowerOfTwo()
{
    int i = 0, n = 1;
    g_wPowerOfTwo[0] = 0;
    while (i < 4096)
    {
        for (;i < n;i++)
            g_wPowerOfTwo[i+1] = n;
        n = n * 2;
    }
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    CAlphaSurface::LoadBitmapToDDS

Description:

    Internal helper function to load a bitmap from a resource to a  DirectDraw surface.
    The size of the surface is rounded up to a power of two.  This function is called
    by the 'CAlphaSurface::LoadBitmap' function.

Arguments:

    LPTSTR tszBitmap            - Name of the bitmap to load
  
Return Value:

    LPDIRECTDRAWSURFACE         - A pointer to the loaded bitmap

-------------------------------------------------------------------*/
LPDIRECTDRAWSURFACE
CAlphaSurface::LoadBitmapToDDS(LPTSTR tszBitmap)
{
    HBITMAP             hbitmap;    // Bitmap handle
    BITMAP              bitmap;     // Bitmap information
    DDSURFACEDESC       ddsd;       // Surface Descriptor
    LPDIRECTDRAWSURFACE pdds;       // Pointer to a DirectDraw surface
    HDC                 hdcBitmap;  // DC for bitmap
    HDC                 hdcSurface; // DC for DDraw surface

    // TODO: make this a predeclared table, rather than creating it here.
    static BOOL fInited = FALSE;
    if (!fInited)
    {
        InitPowerOfTwo();
        fInited = TRUE;
    }

    // Try to Load the bitmap as a resource
    hbitmap = (HBITMAP)LoadImage (g_hinst, tszBitmap, IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR);
    if (hbitmap== NULL)
    {
        // Failed to load the bitmap
        return NULL;
    }

    // Get the width, height and other info about the bitmap.
    GetObject (hbitmap, sizeof(BITMAP), &bitmap);

    // create a DirectDrawSurface for this texture
    memset(&ddsd, 0, sizeof(ddsd));
    GetSurfaceDesc(&ddsd, g_pddsBack);  

    ddsd.dwSize         = sizeof(DDSURFACEDESC);
    ddsd.dwFlags        = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;
    ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;

    // Bump up the size to be power of 2
    m_fOrigWidth  = (float)bitmap.bmWidth;
    m_fOrigHeight = (float)bitmap.bmHeight;
    m_fInvOrigWidth = 1.0f/m_fOrigWidth;
    m_fInvOrigHeight= 1.0f/m_fOrigHeight;

    // Don't try to create bitmaps with dimensions greater than 4096, or this will fail!
    ddsd.dwWidth  = (DWORD)g_wPowerOfTwo[(int)m_fOrigWidth];
    ddsd.dwHeight = (DWORD)g_wPowerOfTwo[(int)m_fOrigHeight];
    m_fInvWidth  = 1.f/(float)ddsd.dwWidth;
    m_fInvHeight = 1.f/(float)ddsd.dwHeight;

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

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    CAlphaSurface::LoadBitmap

Description:

    Loads the specified bitmap onto an Alphablending surface.  It generates
    a 3D texture that is used when the surface is Blt'ed to the screen via
    the 'CAlphaSurface::Blt' function.

Arguments:

    LPTSTR tszBitmap            - Name of the bitmap to load
  
Return Value:

    TRUE on success, FALSE on failure

-------------------------------------------------------------------*/
bool
CAlphaSurface::LoadBitmap(LPTSTR tszBitmap)
{
    // First, the hard part - load the texture.  We do this separately from the normal 
    // LoadTexture routine (in ddutil.cxx) because we may need to bump the size of the 
    // surface up to be a power of 2.
    DDSURFACEDESC       ddsd;
    LPDIRECTDRAWSURFACE pddsBitmap,     pddsTexture;
    LPDIRECT3DTEXTURE2  pd3dtextureSrc;

    // Create a surface in system memory and load the bitmap file into it.  The function
    // automatically bumps up the size of the bitmap to be a power of 2, since that's what
    // Dreamcast supports.
    pddsBitmap = LoadBitmapToDDS(tszBitmap);
    if (!pddsBitmap)
    {
        DebugOutput(TEXT("ERROR: Unable to load texture %s\r\n"), tszBitmap);
        return NULL;
    }

    GetSurfaceDesc(&ddsd, pddsBitmap);
    ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH | DDSD_PIXELFORMAT;
    ddsd.ddsCaps.dwCaps = DDSCAPS_TEXTURE | DDSCAPS_ALLOCONLOAD | DDSCAPS_VIDEOMEMORY;

    g_errLast = g_pdd->CreateSurface(&ddsd, &pddsTexture, NULL);
    if (CheckError(TEXT("Create Destination Texture Surface")))
        return NULL;

    // Query our source surface for a texture interface.  This is necessary for the 'Load()' command.
    g_errLast = pddsBitmap->QueryInterface(IID_IDirect3DTexture2, (LPVOID*)&pd3dtextureSrc);
    if (CheckError(TEXT("Query D3D Texture interface")))
        return NULL;

    // Query our destination surface for a texture interface
    g_errLast = pddsTexture->QueryInterface(IID_IDirect3DTexture2,(LPVOID*)&m_ptexture);
    if (CheckError(TEXT("Query D3D Texture Interface")))
        return NULL;

    // Load the source texture into the destination.  During this call, a
    // driver could compress or reformat the texture surface and put it in video memory.
    g_errLast = m_ptexture->Load(pd3dtextureSrc);
    if (CheckError(TEXT("Load Source Texture into Destination Texture")))
        return NULL;

    // Release no-longer-necessary surfaces
    pd3dtextureSrc->Release();
    pddsBitmap->Release();


    m_ptexture->GetHandle(m_p3ddevice, &m_hTexture);

    return TRUE;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    CAlphaSurface::Blt

Description:

    Draws this surface to the screen with the specified transparency.

    NOTE: This function is not guaranteed to be thread-safe.
    NOTE: This is a considerable amount of work to be doing each blt, but it is here 
          because this sample needs to be generic - it is possible to extract portions of this
          on an app-by-app basis (for instance, if your app batches large numbers of Alphablts,
          then all of the render states can be pulled out of Blt and just done once before and
          once after.

Arguments:

    LPRECT prcDest            - Destination rectangle to which to Blt this surface

    LPRECT prcSrc             - Source rectangle of this Bitmap to Blt.  use 'NULL' to 
                                Blt the entire surface.

    BOOL   fFade              - Alpha value;  0.0 == totally black; 1.0 == totally visible
  
Return Value:

    None

-------------------------------------------------------------------*/

void
CAlphaSurface::Blt(LPRECT prcDest, LPRECT prcSrc, float fFade)
{
    D3DTLVERTEX rgverts[4];
    DWORD dwOldZFunc, dwBlendSrc, dwBlendDest, dwTextureMapBlend;
    BOOL fAlphaEnable;
    float fTU1, fTU2, fTV1, fTV2;

    // Fill the vertices with the appropriate values.
    if (prcSrc)
    {
        fTU1 = prcSrc->left   * m_fInvWidth;
        fTU2 = prcSrc->right  * m_fInvWidth;
        fTV1 = prcSrc->top    * m_fInvHeight;
        fTV2 = prcSrc->bottom * m_fInvHeight;
    }
    else
    {
        fTU1 = 0.0f;
        fTU2 = 1.0f;
        fTV1 = 0.0f;
        fTV2 = 1.0f;
    }

    if (m_fInvWidth != m_fOrigWidth)
    {
        fTU1 *= m_fOrigWidth * m_fInvWidth;
        fTU2 *= m_fOrigWidth * m_fInvWidth;
    }
    if (m_fInvHeight != m_fOrigHeight)
    {
        fTV1 *= m_fOrigHeight * m_fInvHeight;
        fTV2 *= m_fOrigHeight * m_fInvHeight;
    }

    D3DCOLOR cColor = D3DRGBA(1,1,1, fFade);

    // Optimization: make these class members to avoid recreating every single time.
    rgverts[0] = D3DTLVERTEX( D3DVECTOR( (float)prcDest->left,  (float)prcDest->top,    g_z ), 1.f/g_z, cColor, D3DRGBA(0,0,0,0), fTU1, fTV1 );
    rgverts[1] = D3DTLVERTEX( D3DVECTOR( (float)prcDest->right, (float)prcDest->top,    g_z ), 1.f/g_z, cColor, D3DRGBA(0,0,0,0), fTU2, fTV1 );
    rgverts[2] = D3DTLVERTEX( D3DVECTOR( (float)prcDest->left,  (float)prcDest->bottom, g_z ), 1.f/g_z, cColor, D3DRGBA(0,0,0,0), fTU1, fTV2 );
    rgverts[3] = D3DTLVERTEX( D3DVECTOR( (float)prcDest->right, (float)prcDest->bottom, g_z ), 1.f/g_z, cColor, D3DRGBA(0,0,0,0), fTU2, fTV2 );

    // Alpha blts are always done on top of the screen
    m_p3ddevice->GetRenderState(D3DRENDERSTATE_ZFUNC, &dwOldZFunc);
    m_p3ddevice->SetRenderState(D3DRENDERSTATE_ZFUNC, D3DCMP_ALWAYS );

    // Save/Set the texture map blend mode
    m_p3ddevice->GetRenderState(D3DRENDERSTATE_TEXTUREMAPBLEND,   &dwTextureMapBlend);
    m_p3ddevice->SetRenderState(D3DRENDERSTATE_TEXTUREMAPBLEND,   D3DTBLEND_MODULATEALPHA);

    // Get/Set the alpha blending state
    m_p3ddevice->GetRenderState(D3DRENDERSTATE_SRCBLEND,  &dwBlendSrc);
    m_p3ddevice->GetRenderState(D3DRENDERSTATE_DESTBLEND, &dwBlendDest);
    m_p3ddevice->GetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE, (ULONG*)&fAlphaEnable );

    m_p3ddevice->SetRenderState(D3DRENDERSTATE_SRCBLEND,  D3DBLEND_SRCALPHA);
    m_p3ddevice->SetRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_INVSRCALPHA);
    m_p3ddevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE, TRUE );

    // Set the current texture to be the Surfaces' texture.
    // NOTE: This function doesn't restore the previous texture handle; some apps may
    // care about this, and need to restore it after the call to DrawPrimitive.
    m_p3ddevice->SetRenderState(D3DRENDERSTATE_TEXTUREHANDLE, m_hTexture);

    // Blow away these states - the app should restore these if it cares.
    m_p3ddevice->SetRenderState(D3DRENDERSTATE_SPECULARENABLE,   FALSE);
    m_p3ddevice->SetRenderState(D3DRENDERSTATE_CULLMODE,         D3DCULL_CCW);
    m_p3ddevice->SetRenderState(D3DRENDERSTATE_ZENABLE, TRUE);
    m_p3ddevice->SetRenderState(D3DRENDERSTATE_ZWRITEENABLE, TRUE);

    // Draw the surface to the screen via DrawPrimitive.
    m_p3ddevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, D3DVT_TLVERTEX, rgverts, 4, NULL);

    // Restore the alpha blending state
    m_p3ddevice->SetRenderState(D3DRENDERSTATE_SRCBLEND,  dwBlendSrc);
    m_p3ddevice->SetRenderState(D3DRENDERSTATE_DESTBLEND, dwBlendDest);
    m_p3ddevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE, fAlphaEnable );

    // Restore the texture map blend mode
    m_p3ddevice->SetRenderState(D3DRENDERSTATE_TEXTUREMAPBLEND, dwTextureMapBlend);

    // Restore the old ZFunc
    m_p3ddevice->SetRenderState( D3DRENDERSTATE_ZFUNC, dwOldZFunc);
}
