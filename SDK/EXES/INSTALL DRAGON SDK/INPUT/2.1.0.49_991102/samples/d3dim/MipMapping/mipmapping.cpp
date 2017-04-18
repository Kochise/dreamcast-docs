/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999 Microsoft Corporation

Module Name:

    MipMapping.cpp

Abstract:

    MipMapping Application

-------------------------------------------------------------------*/

// ++++ Include Files +++++++++++++++++++++++++++++++++++++++++++++++
#include "MipMapping.hpp"

// ++++ Global Variables ++++++++++++++++++++++++++++++++++++++++++++
HWND      g_hwndApp;                                // HWND of the application
HINSTANCE g_hinst;                                  // HINSTANCE of the application

// ++++ Local Variables +++++++++++++++++++++++++++++++++++++++++++++
TCHAR     g_tszAppName[] = TEXT("MipMapping");      // The App's Name
D3DTEXTUREHANDLE   g_hMipMap;                       // The MipMap texture handle
LPDIRECT3DTEXTURE2 g_pd3dtexMipMap;
D3DTEXTUREHANDLE   g_hBrick;
LPDIRECT3DTEXTURE2 g_pd3dtexBrick;
WORD      g_rgwTestIndices[6];
D3DVERTEX g_rgvertTest[4];
WORD      g_rgwTestIndices2[6];
D3DVERTEX g_rgvertTest2[4];

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

    Renders the scene to the back buffer

Arguments:
    
    None

Return Value:

    TRUE on success, FALSE on failure.

-------------------------------------------------------------------*/
BOOL 
RenderSceneToBackBuffer()
{
    static D3DRECT s_d3drect = {0, 0, 640, 480};
    D3DMATRIX matRotate = g_matIdent;   // Used to rotate the cube

    // Clear the back buffer.
    g_errLast = g_pviewport->Clear(1, &s_d3drect, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER);
    if (CheckError(TEXT("Clear Back Buffer")))
        return FALSE;

    // Begin the scene
    g_errLast = g_p3ddevice->BeginScene();
    if (CheckError(TEXT("Begin Scene")))
        return FALSE;

    // Use mipmapping
    g_p3ddevice->SetRenderState(D3DRENDERSTATE_TEXTUREHANDLE, g_hMipMap);
    g_p3ddevice->SetRenderState(D3DRENDERSTATE_TEXTUREMIN, (DWORD)(D3DFILTER_MIPLINEAR));
    g_p3ddevice->SetRenderState(D3DRENDERSTATE_TEXTUREMAG, (DWORD)(D3DFILTER_MIPLINEAR));

    // Draw the mipmapped rectangle
    g_errLast = g_p3ddevice->DrawIndexedPrimitive( D3DPT_TRIANGLELIST,  D3DVT_VERTEX, 
                    (LPVOID) g_rgvertTest,  4, g_rgwTestIndices, 6, D3DDP_WAIT);
    if (CheckError(TEXT("Draw test primitive")))
        return FALSE;

    // Don't use mipmapping
    g_p3ddevice->SetRenderState(D3DRENDERSTATE_TEXTUREHANDLE, g_hBrick);
    g_p3ddevice->SetRenderState(D3DRENDERSTATE_TEXTUREMIN, (DWORD)(D3DFILTER_LINEAR));
    g_p3ddevice->SetRenderState(D3DRENDERSTATE_TEXTUREMAG, (DWORD)(D3DFILTER_LINEAR));

    // Draw the mipmapped rectangle
    g_errLast = g_p3ddevice->DrawIndexedPrimitive( D3DPT_TRIANGLELIST,  D3DVT_VERTEX, 
                    (LPVOID) g_rgvertTest2,  4, g_rgwTestIndices2, 6, D3DDP_WAIT);
    if (CheckError(TEXT("Draw test primitive")))
        return FALSE;

    // End the scene
    g_errLast = g_p3ddevice->EndScene();
    if (CheckError(TEXT("EndScene")))
        return FALSE;

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
    static D3DMATRIX s_d3dmatxBackwards(1, 0, 0, 0,
                                        0, 1, 0, 0,
                                        0, 0, 1, 0,
                                        0, 0, -0.2f, 1);

    static D3DMATRIX s_d3dmatxForwards(1, 0, 0, 0,
                                       0, 1, 0, 0,
                                       0, 0, 1, 0,
                                       0, 0, 0.2f, 1);
    static int s_iFrame = 0;

    // Render the scene
    if (!RenderSceneToBackBuffer())
        return;
    
    // Move the viewport back and forth so that we can see the effect of the Mipmapping
    if ((s_iFrame % 400) < 200)
        g_p3ddevice->MultiplyTransform(D3DTRANSFORMSTATE_VIEW, &s_d3dmatxBackwards);
    else
        g_p3ddevice->MultiplyTransform(D3DTRANSFORMSTATE_VIEW, &s_d3dmatxForwards);
    s_iFrame++;

    // Flip the buffers
    FlipBuffers();
}


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    InitVertices

Description:

    Initialize the Triangles' vertices.

Arguments:

    None

Return Value:

    None

-------------------------------------------------------------------*/
void 
InitVertices()
{
    g_rgvertTest[0].x  = 0.0f;
    g_rgvertTest[0].y  = 0.0f;
    g_rgvertTest[0].z  = 0.0f;
    g_rgvertTest[0].nx = 0.0f;
    g_rgvertTest[0].ny = 0.0f;
    g_rgvertTest[0].nz = 1.0f;
    g_rgvertTest[0].tu = 1.0f;
    g_rgvertTest[0].tv = 1.0f;

    g_rgvertTest[1].x  = 1.0f;
    g_rgvertTest[1].y  = 0.0f;
    g_rgvertTest[1].z  = 0.0f;
    g_rgvertTest[1].nx = 0.0f;
    g_rgvertTest[1].ny = 0.0f;
    g_rgvertTest[1].nz = 1.0f;
    g_rgvertTest[1].tu = 0.0f;
    g_rgvertTest[1].tv = 1.0f;

    g_rgvertTest[2].x  = 0.0f;
    g_rgvertTest[2].y  = 1.0f;
    g_rgvertTest[2].z  = 0.0f;
    g_rgvertTest[2].nx = 0.0f;
    g_rgvertTest[2].ny = 0.0f;
    g_rgvertTest[2].nz = 1.0f;
    g_rgvertTest[2].tu = 1.0f;
    g_rgvertTest[2].tv = 0.0f;

    g_rgvertTest[3].x  = 1.0f;
    g_rgvertTest[3].y  = 1.0f;
    g_rgvertTest[3].z  = 0.0f;
    g_rgvertTest[3].nx = 0.0f;
    g_rgvertTest[3].ny = 0.0f;
    g_rgvertTest[3].nz = 1.0f;
    g_rgvertTest[3].tu = 0.0f;
    g_rgvertTest[3].tv = 0.0f;

    g_rgwTestIndices[0] = 0; g_rgwTestIndices[1] = 1; g_rgwTestIndices[2] = 2;
    g_rgwTestIndices[3] = 1; g_rgwTestIndices[4] = 3; g_rgwTestIndices[5] = 2;

    g_rgvertTest2[0].x  = -1.1f;
    g_rgvertTest2[0].y  = 0.0f;
    g_rgvertTest2[0].z  = 0.0f;
    g_rgvertTest2[0].nx = 0.0f;
    g_rgvertTest2[0].ny = 0.0f;
    g_rgvertTest2[0].nz = 1.0f;
    g_rgvertTest2[0].tu = 1.0f;
    g_rgvertTest2[0].tv = 1.0f;

    g_rgvertTest2[1].x  = -0.1f;
    g_rgvertTest2[1].y  = 0.0f;
    g_rgvertTest2[1].z  = 0.0f;
    g_rgvertTest2[1].nx = 0.0f;
    g_rgvertTest2[1].ny = 0.0f;
    g_rgvertTest2[1].nz = 1.0f;
    g_rgvertTest2[1].tu = 0.0f;
    g_rgvertTest2[1].tv = 1.0f;

    g_rgvertTest2[2].x  = -1.1f;
    g_rgvertTest2[2].y  = 1.0f;
    g_rgvertTest2[2].z  = 0.0f;
    g_rgvertTest2[2].nx = 0.0f;
    g_rgvertTest2[2].ny = 0.0f;
    g_rgvertTest2[2].nz = 1.0f;
    g_rgvertTest2[2].tu = 1.0f;
    g_rgvertTest2[2].tv = 0.0f;

    g_rgvertTest2[3].x  = -0.1f;
    g_rgvertTest2[3].y  = 1.0f;
    g_rgvertTest2[3].z  = 0.0f;
    g_rgvertTest2[3].nx = 0.0f;
    g_rgvertTest2[3].ny = 0.0f;
    g_rgvertTest2[3].nz = 1.0f;
    g_rgvertTest2[3].tu = 0.0f;
    g_rgvertTest2[3].tv = 0.0f;

    g_rgwTestIndices2[0] = 0; g_rgwTestIndices2[1] = 1; g_rgwTestIndices2[2] = 2;
    g_rgwTestIndices2[3] = 1; g_rgwTestIndices2[4] = 3; g_rgwTestIndices2[5] = 2;
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
    WNDCLASS           cls;
    TCHAR              *tszMipNames[] = {TEXT("L0Bitmap"), TEXT("L1Bitmap"), 
                       TEXT("L2Bitmap"), TEXT("L3Bitmap"), TEXT("L4Bitmap")};

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

    // Load the mipmap
    g_pd3dtexMipMap = LoadMipMap(5, tszMipNames);
    if (!g_pd3dtexMipMap)
        return FALSE;

    // Get a texture handle to the mipmap
    g_errLast = g_pd3dtexMipMap->GetHandle(g_p3ddevice, &g_hMipMap);
    if (CheckError(TEXT("Get texture handle")))
        return FALSE;

    // Load the regular brick texture
    g_pd3dtexBrick = LoadTexture(TEXT("Brick"));
    if (!g_pd3dtexBrick)
        return FALSE;

    // Get a texture handle to the brick texture
    g_errLast = g_pd3dtexBrick->GetHandle(g_p3ddevice, &g_hBrick);
    if (CheckError(TEXT("Get texture handle")))
        return FALSE;

    // Create a rectangular polygon pair that will display the mipmap
    InitVertices();

    // Add a white light
    AddLight(1.0f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f);

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
