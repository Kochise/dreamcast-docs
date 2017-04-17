/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999 Microsoft Corporation

Module Name:

    DShowUtil.cpp

Abstract:

    DirectShow support functions for the 'StreamingVideo' sample

-------------------------------------------------------------------*/

// ++++ Include Files +++++++++++++++++++++++++++++++++++++++++++++++
#include "StreamingVideo.hpp"

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

// Create a render target surface for the specified MultiMedia Stream
IDirectDrawSurface *
CreateMMSRenderTarget(IMultiMediaStream *pmmstream, IDirectDrawStreamSample **ppddssStream, HANDLE *phEndOfStream)
{
    DDSURFACEDESC ddsd;
    DWORD         dwFlags;     
    RECT          rcSrc = {0};
    IDirectDrawSurface      *pddsTarget  = NULL;
    IMediaStream            *pmsPrimary  = NULL;
    IDirectDrawMediaStream  *pddmstream  = NULL;

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
    g_errLast = pddmstream->GetFormat(&ddsd, NULL, NULL, &dwFlags);

    rcSrc.right  = ddsd.dwWidth;
    rcSrc.bottom = ddsd.dwHeight;

    // Create an MMS sample onto which the video will be streamed
    g_errLast = pddmstream->CreateSample(NULL, NULL, DDSFF_PROGRESSIVERENDER, ppddssStream);

    // Finally, create the direct draw surface that we will render to.
    g_errLast = (*ppddssStream)->GetSurface(&pddsTarget, &rcSrc);

done:
    pddmstream->Release();

    // Return the generated DDraw surface
    return pddsTarget;
}
