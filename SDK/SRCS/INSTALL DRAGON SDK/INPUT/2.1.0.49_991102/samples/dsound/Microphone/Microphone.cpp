/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999 Microsoft Corporation

Module Name:

    Microphone.cpp

Abstract:

    Microphone Application

-------------------------------------------------------------------*/

// ++++ Include Files +++++++++++++++++++++++++++++++++++++++++++++++
#include "Microphone.hpp"

// ++++ global Variables ++++++++++++++++++++++++++++++++++++++++++++
HINSTANCE   g_hinst;                        // Instance of the application
HWND        g_hwndApp;                      // Handle to the App's window
                                            // [Used by InitDirectSound()]

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    CleanUp

Description:

    Cleans up after the application is done.  Frees allocated memory

Arguments:

    None
  
Return Value:

    None

-------------------------------------------------------------------*/
void
CleanUp()
{
    int iPort;

    // Release the device objects that we created
    for (iPort = 0; iPort < g_nPorts; iPort++)
        if (g_rgpcont[iPort])
            delete g_rgpcont[iPort];

    // Release the DI object
    if (g_pdi)
        g_pdi->Release();
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    WinMain

Description:

    This is the entrypoint for this sample app.

Arguments:

    hInstance           - HInstance of the process

    hPrev               - HInstance of another process running the program

    LPTSTR lpCmdLine    - Pointer to command line string

    nCmdShow            - Whether the app should be shown (ignored)

Return Value:

    We normally return the wParam value from the WM_QUIT message.  If
    there's a failure upon initialization, we just return 0.

-------------------------------------------------------------------*/
extern "C" int APIENTRY 
WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
    UINT        nCount;
    CMicrophone *pmicrophone;

    // Store Instance handle for use later...
    g_hinst = hInstance;

    // Set g_hwndApp to NULL so that we can properly set the DirectSound
    // CooperativeLevel in InitDirectSound.  A normal application would
    // set g_hwndApp to the HWND of the window that the app renders into
    g_hwndApp = NULL;

    // Initialize DirectSound
    if (!InitDirectSound())
    {
        RetailOutput(TEXT("Unable to Initialize DirectSound\r\n"));
        goto done;
    }

    // Initialize DirectInput
    if (!InitDirectInput())
    {
        RetailOutput(TEXT("Unable to Initialize DirectInput\r\n"));
        goto done;
    }

    // This sample cheats and assumes there's a microphone in the controller on port 0
    if (g_rgpcont[0] == NULL)
    {
        RetailOutput(TEXT("There must be a controller with a microphone plugged into port 0 for this sample to work.\r\n"));
        goto done;
    }

    pmicrophone = g_rgpcont[0]->GetMicrophone();
    if (!pmicrophone)
    {
        RetailOutput(TEXT("There needs to be a microphone plugged into the controller in port 0 for this sample to work.\r\n"));
        goto done;
    }
    
    // This code records and plays back sound from the specified microphone for 100 seconds

    // Create a playback buffer for this microphone device
    pmicrophone->m_pdsb = CreateSoundBuffer(11025, 16, 16 * 1024);
    if (!pmicrophone->m_pdsb)
    {
        RetailOutput(TEXT("Unable to create DSound buffer\r\n"));
        goto done;
    }

    // DSound works by playing half of a buffer while it is in the process of writing to the 
    // other half.  When it sees that it's hit the mid/end point, it switches to playing the
    // other buffer while writing to the opposite buffer.  The recording is going on at the 
    // same time here; while DSound is playing from one half of the buffer, DSound is also 
    // recording into the DirectSoundCapture buffer; once it notices that it's hit the end
    // of the current half of the DSound Buffer, the loop copies the newly recording information
    // into DSound and begins to play that.

    // Start the DirectSoundCapture loop recording
    g_errLast = pmicrophone->m_pdscb->Start(DSCBSTART_LOOPING);
    if (CheckError(TEXT("Start Looping")))
    {
        RetailOutput(TEXT("Microphone unplugged\r\n"));
        goto done;
    }

    // Clear out the sound buffer (to silence)
    ClearSoundBuffer(pmicrophone->m_pdsb);

    // Start the sound buffer playing (this will play silence for the first half second)
    g_errLast = pmicrophone->m_pdsb->Play(0, 0, DSBPLAY_LOOPING);
    if (CheckError(TEXT("Play DSound Buffer")))
        goto done;

    // Loop the recording
    nCount = 0;
    while (nCount++ < 100)
    {
        // Wait until we're finished recording a half second's worth of sound (after the
        // first time through this loop, the second half of the buffer will be playing at
        // the same time).
        WaitForSingleObject(pmicrophone->m_rgdsbposnotify[0].hEventNotify, INFINITE);

        // Copy the first half second into the DSound buffer (which will automatically
        // begin playing it)
        if (!CopyInputToOutput(pmicrophone->m_pdscb, pmicrophone->m_pdsb, 0))
            goto done;

        // Wait until we're finished recording the second half's 500ms of sound (the
        // first half will be playing during this).
        WaitForSingleObject(pmicrophone->m_rgdsbposnotify[1].hEventNotify, INFINITE);

        // Copy the second half second into the DSound buffer
        if (!CopyInputToOutput(pmicrophone->m_pdscb, pmicrophone->m_pdsb, 1))
            goto done;
    }

    // When done, stop the microphone from recording
    g_errLast = pmicrophone->m_pdscb->Stop();
    if (CheckError(TEXT("Stop Microphone")))
    {
        RetailOutput(TEXT("Microphone unplugged\r\n"));
        goto done;
    }

    // Stop the DSound buffer from playing
    g_errLast = pmicrophone->m_pdsb->Stop();
    if (CheckError(TEXT("Stop Microphone")))
        goto done;

    // Wait until we're notified that the microphone stopped capturing.
    WaitForSingleObject(pmicrophone->m_rgdsbposnotify[2].hEventNotify, INFINITE);

    // Release objects that we created.
    CleanUp();

done:
    delete pmicrophone;
    g_pds->Release();

    RetailOutput(TEXT("\r\nApp exited...\r\n"));

    return 0;
}
