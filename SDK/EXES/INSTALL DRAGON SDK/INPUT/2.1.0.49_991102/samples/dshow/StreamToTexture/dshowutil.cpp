/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999 Microsoft Corporation

Module Name:

    DShowUtil.cpp

Abstract:

    DirectShow support functions for the 'StreamToTexture' sample

-------------------------------------------------------------------*/

// ++++ Include Files +++++++++++++++++++++++++++++++++++++++++++++++
#include "StreamToTexture.hpp"

float g_rX = 1.0f, g_rY = 1.0f;

// Create a MultiMediaStream and open the specified media file
IMultiMediaStream *
OpenMMStream(TCHAR *tszFileName)
{
     IAMMultiMediaStream *pammmstream;

     g_errLast = CoCreateInstance(CLSID_AMMultiMediaStream, NULL, CLSCTX_INPROC_SERVER, IID_IAMMultiMediaStream, (void **)&pammmstream);
     if (CheckError(TEXT("CoCreateInstance on MultiMediaStream")))
         return NULL;

     g_errLast = pammmstream->Initialize(STREAMTYPE_READ, 0, NULL);
     if (CheckError(TEXT("Initialize MultiMediaStream")))
     {
         pammmstream->Release();
         return NULL;
     }

     g_errLast = pammmstream->AddMediaStream(g_pdd, &MSPID_PrimaryVideo, 0, NULL);
     if (CheckError(TEXT("Add Primary Video stream")))
     {
         pammmstream->Release();
         return NULL;
     }

     g_errLast = pammmstream->AddMediaStream(NULL, &MSPID_PrimaryAudio, AMMSF_ADDDEFAULTRENDERER, NULL);
     if (CheckError(TEXT("Add Primary Audio stream")))
     {
         pammmstream->Release();
         return NULL;
     }
     
     g_errLast = pammmstream->OpenFile(tszFileName, 0);
     if (CheckError(TEXT("Open File")))
     {
         pammmstream->Release();
         return NULL;
     }
     
     return pammmstream;
}

// Create a 3D render target texture for the specified MultiMedia Stream
LPDIRECT3DTEXTURE2 
Create3DMMSRenderTarget(IMultiMediaStream *pmmstream, IDirectDrawStreamSample **ppddssStream, HANDLE *phEndOfStream)
{
    DDSURFACEDESC ddsd;
    RECT          rcSample = {0};
    IDirectDrawSurface      *pddsTarget = NULL;
    LPDIRECT3DTEXTURE2       pddtTarget = NULL;
    IMediaStream            *pmsPrimary = NULL;
    IDirectDrawMediaStream  *pddmstream = NULL;
    D3DTEXTUREHANDLE        d3dthStream;

    // Get a handle to the "End of Stream" event so the caller can wait until
    // Audio is done streaming if so desired.
    pmmstream->GetEndOfStreamEventHandle(phEndOfStream);
     
    // Get the primary Media Stream object
    g_errLast = pmmstream->GetMediaStream(MSPID_PrimaryVideo, &pmsPrimary);
    if (CheckError(TEXT("GetMediaStream")))
        goto done;

    // Query the Media Stream for an interface that works with DirectDraw
    g_errLast = pmsPrimary->QueryInterface(IID_IDirectDrawMediaStream, (void **)&pddmstream);
    if (CheckError(TEXT("QueryInterface for DirectDrawMediaStream")))
        goto done;

    // At this point, we no longer need the regular Media Stream interface, so release it
    pmsPrimary->Release();

    // get the dimensions of the video stream
    memset(&ddsd, 0, sizeof(DDSURFACEDESC));
    ddsd.dwSize = sizeof(DDSURFACEDESC);
    g_errLast = pddmstream->GetFormat(&ddsd, NULL, NULL, NULL);
    if (CheckError(TEXT("Get MediaStream Format")))
        goto done;

    rcSample.right  = ddsd.dwWidth;
    rcSample.bottom = ddsd.dwHeight;

    // Create a Texture in video memory
    ddsd.ddsCaps.dwCaps = DDSCAPS_TEXTURE | DDSCAPS_VIDEOMEMORY;

    // We'll need a texture whose dimensions are at least as big as the video 
    // stream while still being a power of two.
    ddsd.dwWidth = (int)pow(2.0f, (float)(((int)(log10((float)ddsd.dwWidth - 1.0f) / log10(2.0f))) + 1.0f));
    ddsd.dwHeight = (int)pow(2.0f, (float)(((int)(log10((float)ddsd.dwHeight - 1.0f) / log10(2.0f))) + 1.0f));

    // Ensure the texture is square for compatibility
    if (ddsd.dwWidth > ddsd.dwHeight)
        ddsd.dwHeight = ddsd.dwWidth;
    else
        ddsd.dwWidth = ddsd.dwHeight;

    // Store the ratio of stream to texture sizes so that we display the correct texture coordinates
    g_rX = (float) rcSample.right / (float) ddsd.dwWidth;
    g_rY = (float) rcSample.bottom / (float) ddsd.dwHeight;

    // Create the DDraw surface
    g_errLast = g_pdd->CreateSurface(&ddsd, &pddsTarget, NULL);
    if (CheckError(TEXT("Create Target DDraw surface for MMS")))
        goto done;

    // Query for the texture interface
    g_errLast = pddsTarget->QueryInterface(IID_IDirect3DTexture2, (LPVOID*)&pddtTarget);
    if (CheckError(TEXT("QueryInterface for Texture Interface for MMS")))
        goto done;

    // Get the handle of the video stream texture
    g_errLast = pddtTarget->GetHandle(g_p3ddevice, &d3dthStream);
    if (CheckError(TEXT("Get Handle to Texture")))
        goto done;

    // Set the texture of the video stream
    g_errLast = g_p3ddevice->SetRenderState(D3DRENDERSTATE_TEXTUREHANDLE, (DWORD)d3dthStream);
    if (CheckError(TEXT("SetRenderState to created texture")))
        goto done;
    
    // Create an MMS sample onto which the video will be streamed
    g_errLast = pddmstream->CreateSample(pddsTarget, &rcSample, DDSFF_PROGRESSIVERENDER, ppddssStream);
    if (CheckError(TEXT("CreateSample for MMS")))
        goto done;

done:

    pddmstream->Release();
    pddsTarget->Release();

    // Return the generated 3D texture
    return pddtTarget;
}
