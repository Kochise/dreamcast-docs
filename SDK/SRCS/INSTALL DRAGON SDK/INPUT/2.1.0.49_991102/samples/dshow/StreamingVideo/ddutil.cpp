/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999 Microsoft Corporation

Module Name:

    DDUtil.cpp

Abstract:

   This file contains DirectDraw functionality for the StreamingVideo sample.

-------------------------------------------------------------------*/

// ++++ Include Files +++++++++++++++++++++++++++++++++++++++++++++++
#include "StreamingVideo.hpp"

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

