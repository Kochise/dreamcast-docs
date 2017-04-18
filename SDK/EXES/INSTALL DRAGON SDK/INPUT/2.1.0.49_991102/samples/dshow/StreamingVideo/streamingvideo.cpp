/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999 Microsoft Corporation

Module Name:

    StreamingVideo.cpp

Abstract:

    StreamingVideo Application

-------------------------------------------------------------------*/

// ++++ Include Files +++++++++++++++++++++++++++++++++++++++++++++++
#include "StreamingVideo.hpp"

// ++++ Global Variables ++++++++++++++++++++++++++++++++++++++++++++
HWND      g_hwndApp;                                // HWND of the application
HINSTANCE g_hinst;                                  // HINSTANCE of the application

// ++++ Local Variables +++++++++++++++++++++++++++++++++++++++++++++
TCHAR     g_tszAppName[] = TEXT("StreamingVideo");  // The App's Name
IDirectDrawSurface *g_pddsOffScreenStream;          // The offscreen surface to which the media 
                                                    // is automatically rendered.

// ++++ Local Functions +++++++++++++++++++++++++++++++++++++++++++++
static BOOL RenderSceneToBackBuffer();
static BOOL AppInit(HINSTANCE hPrev,int nCmdShow);


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
    // Release back buffer
    if (g_pddsBack)           
        g_pddsBack->Release();

    // Release the primary surface.
    if (g_pddsPrimary)        
        g_pddsPrimary->Release();

    // Release the DD object
    if (g_pdd)                
        g_pdd->Release();  
    
}

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

    RenderSceneToBackBuffer

Description:

    Render the bitmap to the back buffer

Arguments:
    
    None

Return Value:

    TRUE on success, FALSE on failure.

-------------------------------------------------------------------*/
BOOL 
RenderSceneToBackBuffer()
{
    // Blt video onto screen before text if offscreen surface doesn't support GetDC
    g_pddsBack->Blt(NULL, g_pddsOffScreenStream, NULL, DDBLT_WAIT, NULL);

    // Draw text          

    HDC hdc;
    g_pddsBack->GetDC(&hdc);

    SetBkMode(hdc, TRANSPARENT);
    SetTextColor(hdc, RGB(255,255,255));
    ExtTextOut(hdc, 260, 230, 0, NULL, TEXT("Hello World"), 11, NULL);
    g_pddsBack->ReleaseDC(hdc);

    return TRUE;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    UpdateFrame

Description:

    This function is called whenever the CPU is idle.  The application
    should update it's state and rerender to the screen if appropriate.

Arguments:

    None.

Return Value:

    None.

-------------------------------------------------------------------*/
void 
UpdateFrame ()
{
    // Render the scene
    if (!RenderSceneToBackBuffer())
        return;
    
    // Flip the buffers
    FlipBuffers();
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
AppInit(HINSTANCE hPrev, int nCmdShow)
{
    WNDCLASS  cls;          

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

    // Initialize DirectDraw
    if (!InitDirectDraw())
        return FALSE;

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
    MSG               msg;
    IMultiMediaStream *pmmsMovie;                     // The media to display
    HANDLE            hEndOfStream;                   // Event that stream has ended
    IDirectDrawStreamSample *g_pddssStream;
    TCHAR szFile[MAX_PATH];
    DWORD dwAttributes;

    // Store Instance handle for use later...
    g_hinst = hInstance;

    if (*lpCmdLine == NULL)
    {
        // The user must specify a filename
        RetailOutput(TEXT("Error: filename not specified.  File must either be specified with full path\r\n"));
        RetailOutput(TEXT("name, or must reside in your Release\\<retail/debug>\\Samples directory\r\n"));
        RetailOutput(TEXT("Usage: StreamingVideo [filename]\r\n"));
        return 1;
    }

    // Get the desired filename from the command line
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
            RetailOutput(TEXT("specified media file (%s) not found\r\n"), lpCmdLine);
            RetailOutput(TEXT("File must either be specified with full path name, or must reside in\r\n"));
            RetailOutput(TEXT("your Release\\<retail/debug>\\Samples directory\r\n"));
            RetailOutput(TEXT("Usage: StreamingVideo [filename]\r\n"));
            return 1;
        }
    }

    // Call initialization procedure
    if (!AppInit(hPrevInstance,nCmdShow))
        return 1;

    // Load the media file
    pmmsMovie = OpenMMStream(szFile);
    if (!pmmsMovie)
    {
        CleanUp();
        return 1;
    }

    // Create a rendering surface target for the streaming media object.
    g_pddsOffScreenStream = CreateMMSRenderTarget(pmmsMovie, &g_pddssStream, &hEndOfStream);

    // Start the media file playing.  This will automatically render itself to the
    // surface created above.
    g_errLast = pmmsMovie->SetState(STREAMSTATE_RUN);
    if (CheckError(TEXT("Start Movie Playing")))
    {
        CleanUp();
        return 1;
    }

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
            // If no messages pending, then update the frame.

            // Check to see if the media has finished playing.
            if (g_pddssStream->Update(0, NULL, NULL, 0) != S_OK)
            {
                // The media has finished playing - send a message to ourselves
                // telling us to quit
                SendMessage(g_hwndApp, WM_KEYDOWN, VK_ESCAPE, 0L);
            }
            else
            {
                // Render the frame - this consists of Blting the rendering media
                // from it's offscreen surface to the screen.
                UpdateFrame();
            }
        }
    }

    // We want to wait until the audio has finished; otherwise the app
    // ends with the last sound infinitely repeating.
    if (hEndOfStream)
        WaitForSingleObject(hEndOfStream, INFINITE);

    // Tell the stream to stop playing
    pmmsMovie->SetState(STREAMSTATE_STOP);

    // Delete the media's offscreen surface
    g_pddsOffScreenStream->Release();

    // Delete the media object
    pmmsMovie->Release();

    g_pddssStream->Release();

    // Cleanup DirectX structures
    CleanUp();

    RetailOutput(TEXT("\r\nApp exited...\r\n"));

    // And return our error code
    return msg.wParam;
}
