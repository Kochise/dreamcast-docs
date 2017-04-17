/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999 Microsoft Corporation

Module Name:

    DDUtil.cpp

Abstract:

   This file contains DirectDraw functionality for the VQSurfaces sample.

-------------------------------------------------------------------*/

// ++++ Include Files +++++++++++++++++++++++++++++++++++++++++++++++
#include "VQSurfaces.hpp"

// ++++ Preprocessor definitions ++++++++++++++++++++++++++++++++++++
#define VQ_TEXTURE              0x00000300
#define VQ_MIPMAP               0x00000400
#define VQ_RGBA_5551            0x00000000
#define VQ_RGBA_5650            0x00000001
#define VQ_RGBA_4444            0x00000002

// ++++ Global Variables ++++++++++++++++++++++++++++++++++++++++++++
LPDIRECTDRAW        g_pdd;          // The DirectDraw object
LPDIRECTDRAWSURFACE g_pddsPrimary;  // Primary DirectDraw surface
LPDIRECTDRAWSURFACE g_pddsBack;     // Backbuffer DirectDraw surface

// ++++ Local functions +++++++++++++++++++++++++++++++++++++++++++++
static BOOL CreateDirectDrawDevice();
static inline void CopyWORD(LPVOID pvDst, LPVOID pvSrc, DWORD dwSize);

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

    LoadVQToDDS

Description:

    Loads a VQ compressed image from a file or resource, creates a 
	new compressed DirectDraw surface, and copies the image to that 
	surface.

Arguments:

    LPTSTR tszVQImage   -   Name of the image to load
 
Return Value:

    LPDIRECTDRAWSURFACE -   A pointer to the loaded surface

-------------------------------------------------------------------*/
LPDIRECTDRAWSURFACE
LoadVQToDDS(LPTSTR tszVQImage)
{
    DDSURFACEDESC       ddsd;       // Surface Descriptor
    LPDIRECTDRAWSURFACE pdds;       // Pointer to a DirectDraw surface
    HANDLE              hFile;
    PBYTE               pdata;      // Pointer to the VQ image data
    DWORD               dwFormat;   // Pixel format of the VQ image
    DWORD               dwSize;
    WORD                wWidth,
                        wHeight;

    // Attempt to open the VQ image as a file
    hFile = CreateFile(tszVQImage, GENERIC_READ, FILE_SHARE_READ, NULL, 
                       OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile != INVALID_HANDLE_VALUE) 
    {
        DWORD dwRead;

        // Get the size of the file
        dwSize = GetFileSize(hFile, NULL);
        if (dwSize == 0xFFFFFFFF) 
        {
            CloseHandle(hFile);
            return NULL;
        }

        // Allocate a buffer for the file data
        pdata = new BYTE[dwSize];
        if (!pdata) 
        {
            CloseHandle(hFile);
            return NULL;
        }                

        // Read the file into the buffer
        if (!ReadFile(hFile, pdata, dwSize, &dwRead, NULL)
            || dwSize != dwRead)
        {
            delete [] pdata;
            CloseHandle(hFile);
            return NULL;
        }

        // Close the file
        CloseHandle(hFile);
    }
    else 
    {
        HGLOBAL hg;
        HRSRC   hrsrc;

        // Attempt to open th eVQ image as a resource
        if (!(hrsrc = FindResource(g_hinst, tszVQImage, RT_RCDATA))) 
        {
            DebugOutput(TEXT("FindResource failed to find the texture resource %s"), 
                                                                    tszVQImage);
            return NULL;
        }

        if (!(hg = LoadResource(g_hinst, hrsrc))) 
        {
            DebugOutput(TEXT("LoadResource failed to load the texture resource %s"), 
                                                                    tszVQImage);
            return NULL;
        }

        if (!(pdata = (LPBYTE)LockResource(hg))) 
        {
            DebugOutput(TEXT("LockResource failed to lock the texture resource %s"), 
                                                                    tszVQImage);
            return NULL;
        }
    }

    // Check the first four bytes of the header to see if the given image
    // is a VQ compressed image
    if (strncmp((char*)pdata, "PVRT", 4)) 
    {
        DebugOutput(TEXT("%s is not a valid VQ image"), tszVQImage);
        if (hFile != INVALID_HANDLE_VALUE) 
            delete [] pdata;
        return NULL;
    }

    // Get the size of the image data
    memcpy(&dwSize, (((LPDWORD)pdata) + 1), sizeof(DWORD));
    dwSize -= 8;

    // Get the dimensions of the image
    memcpy(&wWidth, (((LPWORD)pdata) + 6), sizeof(WORD));
    memcpy(&wHeight, (((LPWORD)pdata) + 7), sizeof(WORD));

    // Get the pixel format of the image
    dwFormat = *(((LPDWORD)pdata) + 2);

    // Fail if the image is a mipmapped texture
    if (dwFormat & VQ_MIPMAP) 
    {
        if (hFile != INVALID_HANDLE_VALUE) 
            delete [] pdata;
        return NULL;
    }

    // Create a DirectDrawSurface for the image
    GetSurfaceDesc(&ddsd, g_pddsBack);  

    ddsd.dwSize                  = sizeof(DDSURFACEDESC);
    ddsd.dwFlags                 = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH | DDSD_PIXELFORMAT;
    ddsd.ddsCaps.dwCaps          = DDSCAPS_OFFSCREENPLAIN;

    ddsd.dwWidth                 = wWidth;
    ddsd.dwHeight                = wHeight;

    ddsd.ddpfPixelFormat.dwSize  = sizeof(DDPIXELFORMAT);
    ddsd.ddpfPixelFormat.dwFlags = DDPF_RGB | DDPF_COMPRESSED;

    switch (dwFormat & 0x000000FF) 
    {
        case VQ_RGBA_5650:
            ddsd.ddpfPixelFormat.dwRGBBitCount = 16;
            ddsd.ddpfPixelFormat.dwRBitMask = 0xF800;
            ddsd.ddpfPixelFormat.dwGBitMask = 0x07E0;
            ddsd.ddpfPixelFormat.dwBBitMask = 0x001F;
            break;

        case VQ_RGBA_5551:
            ddsd.ddpfPixelFormat.dwFlags |= DDPF_ALPHAPIXELS;
            ddsd.ddpfPixelFormat.dwRGBBitCount = 16;
            ddsd.ddpfPixelFormat.dwRBitMask = 0x7C00;
            ddsd.ddpfPixelFormat.dwGBitMask = 0x03E0;
            ddsd.ddpfPixelFormat.dwBBitMask = 0x001F;
            ddsd.ddpfPixelFormat.dwRGBAlphaBitMask = 0x8000;
            break;

        case VQ_RGBA_4444:
            ddsd.ddpfPixelFormat.dwFlags |= DDPF_ALPHAPIXELS;
            ddsd.ddpfPixelFormat.dwRGBBitCount = 16;
            ddsd.ddpfPixelFormat.dwRBitMask = 0x0F00;
            ddsd.ddpfPixelFormat.dwGBitMask = 0x00F0;
            ddsd.ddpfPixelFormat.dwBBitMask = 0x000F;
            ddsd.ddpfPixelFormat.dwRGBAlphaBitMask = 0xF000;
            break;

        default:
            // Unsupported format
            if (hFile != INVALID_HANDLE_VALUE) 
                delete [] pdata;
            return NULL;
    }

    g_errLast = g_pdd->CreateSurface(&ddsd, &pdds, NULL);
    if (CheckError(TEXT("Create DirectDraw surface")))
    {
        if (hFile != INVALID_HANDLE_VALUE) 
            delete [] pdata;
        return NULL;
    }

    // Lock the surface
    g_errLast = pdds->Lock(NULL, &ddsd, DDLOCK_SURFACEMEMORYPTR |
                    DDLOCK_WAIT | DDLOCK_COMPRESSED, NULL);
    if (CheckError(TEXT("Lock DirectDraw surface")))
    {
        if (hFile != INVALID_HANDLE_VALUE) 
            delete [] pdata;
        pdds->Release();
        return NULL;
    }

    // Copy the image data into the surface.  The copy operation
    // must be done word by word since the hardware does not support
    // byte access to video memory
    // REVIEW: Will memcpy do the right thing when dealing with video
    // memory (i.e. can we substitute it?)
    CopyWORD(ddsd.lpSurface, ((LPDWORD)pdata) + 4, dwSize / 2);

    // Unlock the surface
    g_errLast = pdds->Unlock(ddsd.lpSurface);
    if (CheckError(TEXT("Unlock DirectDraw surface")))
    {
        if (hFile != INVALID_HANDLE_VALUE) 
            delete [] pdata;
        pdds->Release();
        return NULL;
    }

    // Clean up after ourselves.
    if (hFile != INVALID_HANDLE_VALUE) 
        delete [] pdata;

    return pdds;
}

//******************************************************************************
inline void CopyWORD(LPVOID pvDst, LPVOID pvSrc, DWORD dwSize) {

    UINT   i;
    LPWORD pwDst = (LPWORD)pvDst;
    LPWORD pwSrc = (LPWORD)pvSrc;
    for (i = 0; i < dwSize; i++) {
        pwDst[i] = pwSrc[i];
    }
}
