/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999 Microsoft Corporation

Module Name:

    StreamingSound.cpp

Abstract:

    This application streams a sound file from the image.  It creates
    a separate thread to handle streaming the sound while the app 
    does it's own thing.  Essentially, it shows how to do background
    music while an app is running
    
-------------------------------------------------------------------*/

// ++++ Include Files +++++++++++++++++++++++++++++++++++++++++++++++
#include "StreamingSound.hpp"

// ++++ Global Variables ++++++++++++++++++++++++++++++++++++++++++++
HWND      g_hwndApp;                                // HWND of the application
HINSTANCE g_hinst;                                  // HINSTANCE of the application
volatile BOOL g_fPlayBackgroundSound = FALSE;       // TRUE if the background sound should be played
HANDLE    g_hSoundNotifyEvent = NULL;               // Notify Event for the background sound buffer
HANDLE    g_hSoundDoneEvent = NULL;                 // End-Of-Playing Event for the background sound buffer
HANDLE    g_hSoundFile = NULL;                      // Handle of the background sound file to play
IDirectSoundBuffer *g_pdsbBackground = NULL;        // The background sound buffer
BOOL      g_fExiting = FALSE;                       // TRUE if the app is exiting

// ++++ Local Variables +++++++++++++++++++++++++++++++++++++++++++++
TCHAR     g_tszAppName[] = TEXT("StreamingSound");  // The App's Name
HANDLE    g_hStreamThread;                          // Streaming sound thread

// ++++ Local Functions +++++++++++++++++++++++++++++++++++++++++++++
static BOOL AppInit(HINSTANCE hPrev,int nCmdShow);

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    WndProc

Description:

    Window message processing routine for the main application window.
    The main purpose of this function is to exit the app when the user
    presses <Escape> or <F12>.

Arguments:

    HWND hWnd           - Window handle

    UINT uMessage       - Message identifier
  
    WPARAM wParam       - First message parameter
    
    LPARAM lParam       - Second message parameter
  
Return Value:

    Zero if the message was processed.  The return value from 
    DefWindowProc otherwise.

-------------------------------------------------------------------*/
LRESULT CALLBACK
WndProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
    switch (uMessage)
    {
    case WM_KEYDOWN:
        switch (wParam)
        {
        case VK_ESCAPE:
        case VK_F12:
            g_fExiting = TRUE;
//            g_pdsbBackground->Stop();
            DestroyWindow(hWnd);
            return 0;
        } // switch (wParam)
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0L;

    } // switch (message)

    return DefWindowProc (hWnd, uMessage, wParam, lParam);
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    AppInit

Description:

    This function registers a window class, and creates a window for
    the application.

Arguments:

    hPrev               - Hinstance of another process running the program

    nCmdShow            - Whether the app should be shown (ignored)

Return Value:

    TRUE on success, FALSE on failure.

-------------------------------------------------------------------*/
BOOL 
AppInit(HINSTANCE hPrev, int nCmdShow, LPTSTR lpCmdLine)
{
    WAVEFORMATEX *pwfx;
    WNDCLASS cls;          
    DWORD    dwThreadId, dwSize;
    ULONG    nBytes1, nBytes2, cbRead;
    BYTE     byTemp[256], *pbyBlock1, *pbyBlock2, *pbyData;
    TCHAR    szFile[MAX_PATH];
    DWORD    dwAttributes;

    if (!hPrev)
    {
        //  Register a class for the main application window
        cls.hCursor        = NULL;
        cls.hIcon          = NULL;
        cls.lpszMenuName   = NULL;
        cls.hbrBackground  = NULL;
        cls.hInstance      = g_hinst;
        cls.lpszClassName  = g_tszAppName;
        cls.lpfnWndProc    = (WNDPROC)WndProc;
        cls.style          = 0;
        cls.cbWndExtra     = 0;
        cls.cbClsExtra     = 0;

        if (!RegisterClass(&cls))
            return FALSE;
    }

    g_hwndApp = CreateWindowEx (0, g_tszAppName, g_tszAppName, WS_VISIBLE, 0, 0, 640, 480, NULL, NULL, g_hinst, NULL);

    // Initialize DirectSound
    if (!InitDirectSound())
        return FALSE;

    // Load the wav file that we want to stream in the background.

    // Get the desired filename from the command line
    if (*lpCmdLine == NULL)
    {
        // The user must specify a filename
        RetailOutput(TEXT("Error:  Filename not specified.\r\n"));
        RetailOutput(TEXT("File must either be specified with full path, or must reside in\r\n"));
        RetailOutput(TEXT("your <WCEDreamcastSDK>\\release\\(retail,debug)\\Samples directory.\r\n\r\n"));

        RetailOutput(TEXT("Usage:   s StreamingSound <WAV filename>\r\n\r\n"));

        RetailOutput(TEXT("Example: s StreamingSound longtest.wav\r\n"));
        RetailOutput(TEXT("Example: s StreamingSound \\PC\\Samples\\longtest.wav\r\n"));
        return FALSE;
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
            RetailOutput(TEXT("Error:  Specified media file (%s) not found.\r\n"), szFile);
            RetailOutput(TEXT("File must either be specified with full path, or must reside in\r\n"));
            RetailOutput(TEXT("your <WCEDreamcastSDK>\\release\\(retail,debug)\\Samples directory.\r\n\r\n"));

            RetailOutput(TEXT("Usage:   s StreamingSound <WAV filename>\r\n\r\n"));

            RetailOutput(TEXT("Example: s StreamingSound longtest.wav\r\n"));
            RetailOutput(TEXT("Example: s StreamingSound \\PC\\Samples\\longtest.wav\r\n"));
            return FALSE;
        }
    }

    // Open the test file
    g_hSoundFile = CreateFile(szFile, GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);
    if (g_hSoundFile == (HANDLE)0xFFFFFFFF)
    {
        g_pds->Release();
        return FALSE;
    }

    // Read the first 256 bytes to get file header
    ReadFile(g_hSoundFile, byTemp, 256, &cbRead, NULL);

    // Parse the header information to get information.
    ParseWaveFile((void*)byTemp, &pwfx, &pbyData, &dwSize);
    
    // Set file pointer to point to start of data
    SetFilePointer(g_hSoundFile, (int)(pbyData - byTemp), NULL, FILE_BEGIN);

    // Create the sound buffer
    g_pdsbBackground = CreateSoundBuffer(pwfx->nSamplesPerSec, pwfx->wBitsPerSample, BUFFERSIZE);
    if (!g_pdsbBackground)
        return FALSE;

    // Prepare the wav file for streaming (set up event notifications)
    if (!PrepareForStreaming(g_pdsbBackground, BUFFERSIZE, &g_hSoundNotifyEvent, &g_hSoundDoneEvent))
        return FALSE;

    // Fill the sound buffer with the start of the wav file.
    g_pdsbBackground->Lock(0, BUFFERSIZE, (void **)&pbyBlock1, &nBytes1, (void **)&pbyBlock2, &nBytes2, 0);
    ReadFile(g_hSoundFile, pbyBlock1, nBytes1, &cbRead, NULL);
    g_pdsbBackground->Unlock(pbyBlock1, nBytes1, pbyBlock2, nBytes2);

    // Create a separate thread which will handling streaming the sound
    g_hStreamThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)StreamThread, NULL, 0, &dwThreadId);
    if (!g_hStreamThread)
    {
        RetailOutput(TEXT("Error calling CreateThread\r\n"));
        return FALSE;
    }

    // Start the sound playing
    g_pdsbBackground->Play(0, 0, DSBPLAY_LOOPING);

    g_fPlayBackgroundSound = TRUE;
    return TRUE;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    WinMain

Description:

    This is the entrypoint for this sample app.  It creates an app
    window and then enters a message loop.

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
    MSG msg;

    // Store Instance handle for use later...
    g_hinst = hInstance;

    // Call initialization procedure
    if (!AppInit(hPrevInstance,nCmdShow, lpCmdLine))
        goto done;

    // Main Message loop
    while (TRUE)
    {
        if (PeekMessage (&msg, NULL, 0, 0, PM_REMOVE))
        {
            // There's a message waiting in the queue for us.  Retrieve
            // it and dispatch it, unless it's a WM_QUIT.
            if (msg.message == WM_QUIT)
                break;

            TranslateMessage(&msg); 
            DispatchMessage(&msg);
        }
        else
        {
            // Do normal game processing here.  we will emulate this by sleeping for a while...
            Sleep(12);

            if (g_fDonePlaying)
            {
                // Sound has finished
                SendMessage(g_hwndApp, WM_KEYDOWN, VK_ESCAPE, 0L);
            }
        }
    }

    // Wait until we're sure the background sound is done streaming
    WaitUntilSoundDone();

    // Wait to ensure that the streaming thread has exited
    Sleep(100);

done:

    // When done, delete the Threads and events
    if (g_hSoundNotifyEvent)
        CloseHandle(g_hSoundNotifyEvent);

    if (g_hSoundDoneEvent)
        CloseHandle(g_hSoundDoneEvent);

    if (g_hStreamThread)
        CloseHandle(g_hStreamThread);

    if (g_hSoundFile)
        CloseHandle(g_hSoundFile);

    if (g_pdsbBackground)
        g_pdsbBackground->Release();

    if (g_pds)
        g_pds->Release();

    RetailOutput(TEXT("\r\nApp exited...\r\n"));

    return msg.wParam;
}
