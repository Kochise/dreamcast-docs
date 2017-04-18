/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999 Microsoft Corporation

Module Name:

    PlaySound.cpp

Abstract:

    PlaySound Application

-------------------------------------------------------------------*/

// ++++ Include Files +++++++++++++++++++++++++++++++++++++++++++++++
#include "PlaySound.hpp"

// ++++ Global Variables ++++++++++++++++++++++++++++++++++++++++++++
HWND      g_hwndApp;                                // HWND of the application
HINSTANCE g_hinst;                                  // HINSTANCE of the application

// ++++ Local Variables +++++++++++++++++++++++++++++++++++++++++++++
LPDIRECTSOUNDBUFFER g_pdsbToPlay;

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
    if (g_pdsbToPlay)
        g_pdsbToPlay->Release();

    if (g_pds)
        g_pds->Release();
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    WinMain

Description:

    This is the entrypoint for this sample app.  Load the specified
    sound file and play it.

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
    TCHAR szFile[MAX_PATH];
    DWORD dwAttributes;
    ULONG fPlaying;

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
        return 1;
    }

    // Get the desired filename from the command line
    if (*lpCmdLine == NULL)
    {
        // The user must specify a filename
        RetailOutput(TEXT("Error:  Filename not specified.\r\n"));
        RetailOutput(TEXT("File must either be specified with full path, or must reside in\r\n"));
        RetailOutput(TEXT("your <WCEDreamcastSDK>\\release\\(retail,debug)\\Samples directory.\r\n\r\n"));

        RetailOutput(TEXT("Usage:   s PlaySound <WAV filename>\r\n\r\n"));

        RetailOutput(TEXT("Example: s PlaySound jump.wav\r\n"));
        RetailOutput(TEXT("Example: s PlaySound \\PC\\Samples\\jump.wav\r\n"));
        goto done;
    }
    
    lstrcpy(szFile, lpCmdLine);

    // Check to see if the file is specified using the full path (ie "\windows\test.mpg")
    dwAttributes = GetFileAttributes(szFile);
    if (dwAttributes == 0xFFFFFFFF || dwAttributes & FILE_ATTRIBUTE_DIRECTORY)
    {
        // The file was not specifies using the full path; check to see if the filename
        // specified exists in the Flat Release directory
        lstrcpy(szFile, TEXT("\\PC\\Samples\\"));
        lstrcat(szFile, lpCmdLine);
        dwAttributes = GetFileAttributes(szFile);
        if (dwAttributes == 0xFFFFFFFF || dwAttributes & FILE_ATTRIBUTE_DIRECTORY)
        {
            // The file wasn't there either - this sample doesn't support loading from other
            // default directories, so report usage and exit
            RetailOutput(TEXT("Error:  Specified media file (%s) not found\r\n"), szFile);
            RetailOutput(TEXT("File must either be specified with full path, or must reside in\r\n"));
            RetailOutput(TEXT("your <WCEDreamcastSDK>\\release\\(retail,debug)\\Samples directory.\r\n\r\n"));

            RetailOutput(TEXT("Usage:   s PlaySound <WAV filename>\r\n\r\n"));

            RetailOutput(TEXT("Example: s PlaySound jump.wav\r\n"));
            RetailOutput(TEXT("Example: s PlaySound \\PC\\Samples\\jump.wav\r\n"));
            goto done;
        }
    }    

    // Load the specified sound
    g_pdsbToPlay = LoadSoundBuffer(szFile);
    if (!g_pdsbToPlay)
    {
        RetailOutput(TEXT("Unable to load wave file\r\n"));
        return 1;
    }

    // Rewind the test sound (necessary?)
    g_pdsbToPlay->SetCurrentPosition(0);

    // Play the test sound
    g_errLast = g_pdsbToPlay->Play(0, 0, 0);
    if (CheckError(TEXT("Play Sound")))
        return 1;

    // Busy wait for the sound to finish playing
    while (TRUE)
    {
        g_pdsbToPlay->GetStatus(&fPlaying);
        if (!fPlaying)
            break;
    }

done:

    // Release objects that we created.
    CleanUp();

    RetailOutput(TEXT("\r\nApp exited...\r\n"));

    return 0;
}
