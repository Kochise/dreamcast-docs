/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999 Microsoft Corporation

Module Name:

    AlphaBlt.cpp

Abstract:

    AlphaBlt Application

-------------------------------------------------------------------*/

// ++++ Include Files +++++++++++++++++++++++++++++++++++++++++++++++
#include "AlphaBlt.hpp"

// ++++ Global Variables ++++++++++++++++++++++++++++++++++++++++++++
HWND      g_hwndApp;                                // HWND of the application
HINSTANCE g_hinst;                                  // HINSTANCE of the application

// ++++ Local Variables +++++++++++++++++++++++++++++++++++++++++++++
TCHAR     g_tszAppName[] = TEXT("AlphaBlt");        // The App's Name
CAlphaSurface *g_pas1;                              // Alpha surface to blt to screen
CAlphaSurface *g_pas2;                              // Alpha surface to blt to screen
float         g_fFade = 0.5f;                       // Current 'fade' value

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
    // Delete the Alpha Surfaces
    if (g_pas1)
        delete g_pas1;

    if (g_pas2)
        delete g_pas2;

    // Release global light
    for (int i = 0; i < g_cLights; i++)
        g_rglight[i]->Release();
    
    // Release global materials
    if (g_pmatWhite)  
        g_pmatWhite->Release();
    if (g_pmatBlack)  
        g_pmatBlack->Release();

    // Release the Viewport
    if (g_pviewport)       
        g_pviewport->Release();

    // Release the 3D Device
    if (g_p3ddevice)         
        g_p3ddevice->Release();
    
    // Release the global Z Buffer
    // Release back buffer
    if (g_pddsBack)           
        g_pddsBack->Release();

    // Release the primary surface.
    if (g_pddsPrimary)        
        g_pddsPrimary->Release();

    // Release the D3D object
    if (g_pd3d)               
        g_pd3d->Release();

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
        // Cleanup DirectX structures
        CleanUp();

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
    D3DRECT d3drect;
    static fUp = false;

    // Clear the back buffer.
    d3drect.x1 = 0;
    d3drect.y1 = 0;
    d3drect.x2 = 640;
    d3drect.y2 = 480;
    g_errLast = g_pviewport->Clear(1, &d3drect, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER);
    if (CheckError(TEXT("Clear Back Buffer")))
        return FALSE;

    // Begin the scene
    g_errLast = g_p3ddevice->BeginScene();
    if (CheckError(TEXT("Begin Scene")))
        return FALSE;

//    g_p3ddevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, D3DVT_LVERTEX, 
//                                      (LPVOID) g_pVerts, g_cVerts, g_pIndices, g_cIndices, 
//                                      D3DDP_DONOTUPDATEEXTENTS | D3DDP_DONOTCLIP);

    // End the scene
    g_errLast = g_p3ddevice->EndScene();
    if (CheckError(TEXT("EndScene")))
        return FALSE;

    // Blt the alpha surfaces to the back buffer
    RECT rcDest1 = {100, 100, 300, 300};
    RECT rcDest2 = {225, 200, 375, 350};
    RECT rcSrc   = {0, 0, 128, 128};
    
    // Both surfaces were attached to the back buffer at surface creation time (no need to specify destination).
    g_pas1->Blt(&rcDest1, NULL, g_fFade);
    g_pas2->Blt(&rcDest2, &rcSrc, 1.0f - g_fFade); // <- rcSrc = NULL == full source rect

    if (fUp)
    {
        g_fFade += .005f;
        if (g_fFade >= 1.0f)
        {
            g_fFade = 1.0f;
            fUp = ~fUp;
        }
    }
    else
    {
        g_fFade -= .005f;
        if (g_fFade <= .0f)
        {
            g_fFade = .0f;
            fUp = ~fUp;
        }
    }
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

    // Initializes the Direct3D object, viewport, and sets the rendering state.
    if (!InitDirect3D())
        return FALSE;

    // Create and load the test alpha surfaces.  Pass in the global 3d device (which was created off of the back buffer).
    g_pas1 = new CAlphaSurface(g_p3ddevice);
    g_pas2 = new CAlphaSurface(g_p3ddevice);

    g_pas1->LoadBitmap(TEXT("BitmapB"));
    g_pas2->LoadBitmap(TEXT("BitmapA"));

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
    if (!AppInit(hPrevInstance,nCmdShow))
        return 0L;

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

            // Do game-related calculations (physics, AI, etc).

            // ...

            // Render the frame
            UpdateFrame();
        }
    }

    RetailOutput(TEXT("\r\nApp exited...\r\n"));
    return msg.wParam;
}
