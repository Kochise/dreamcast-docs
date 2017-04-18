/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999 Microsoft Corporation

Module Name:

    BasicD3DIM.cpp

Abstract:

    BasicD3DIM Application

-------------------------------------------------------------------*/

// ++++ Include Files +++++++++++++++++++++++++++++++++++++++++++++++
#include "BasicD3DIM.hpp"

// ++++ Global Variables ++++++++++++++++++++++++++++++++++++++++++++
HWND      g_hwndApp;                                // HWND of the application
HINSTANCE g_hinst;                                  // HINSTANCE of the application

// ++++ Local Variables +++++++++++++++++++++++++++++++++++++++++++++
TCHAR     g_tszAppName[] = TEXT("BasicD3DIM");        // The App's Name
D3DVERTEX           g_rgvertCube[8];                // Global Triangle Vertices
WORD                g_rgwCubeIndices[36];           // Global Triangle Indices

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

    // Move the viewpoint (around the x axis)
    matRotate._22 = (float)cos(0.1f);
    matRotate._23 = (float)sin(0.1f);
    matRotate._32 = (float)-sin(0.1f);
    matRotate._33 = (float)cos(0.1f);
    g_errLast = g_p3ddevice->MultiplyTransform(D3DTRANSFORMSTATE_WORLD, &matRotate);
    if (CheckError(TEXT("Object Transform")))
        return FALSE;

    // Render the cube
    g_errLast = g_p3ddevice->DrawIndexedPrimitive( D3DPT_TRIANGLELIST,  D3DVT_VERTEX, 
                    (LPVOID) g_rgvertCube,  8, g_rgwCubeIndices, 36, D3DDP_WAIT);
    if (CheckError(TEXT("Draw Primitive")))
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
    // Render the scene
    if (!RenderSceneToBackBuffer())
        return;
    
    // Flip the buffers
    FlipBuffers();
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    CreateCube

Description:

    Initializes the vertices and indices of the cube.

Arguments:

    None.

Return Value:

    None.

-------------------------------------------------------------------*/
void 
CreateCube()
{
    // Initalize the vertices

    // Vertex 0
    g_rgvertCube[0].x  = 0.5f;
    g_rgvertCube[0].y  = 0.5f;
    g_rgvertCube[0].z  = 0.5f;
    g_rgvertCube[0].nx = 0.5f;
    g_rgvertCube[0].ny = 0.5f;
    g_rgvertCube[0].nz = 0.5f;

    // Vertex 1
    g_rgvertCube[1].x  = 0.5f;
    g_rgvertCube[1].y  = 0.5f;
    g_rgvertCube[1].z  = -0.5f;
    g_rgvertCube[1].nx = 0.5f;
    g_rgvertCube[1].ny = 0.5f;
    g_rgvertCube[1].nz = -0.5f;

    // Vertex 2
    g_rgvertCube[2].x  = -0.5f;
    g_rgvertCube[2].y  = 0.5f;
    g_rgvertCube[2].z  = -0.5f;
    g_rgvertCube[2].nx = -0.5f;
    g_rgvertCube[2].ny = 0.5f;
    g_rgvertCube[2].nz = -0.5f;

    // Vertex 3
    g_rgvertCube[3].x  = -0.5f;
    g_rgvertCube[3].y  = 0.5f;
    g_rgvertCube[3].z  = 0.5f;
    g_rgvertCube[3].nx = -0.5f;
    g_rgvertCube[3].ny = 0.5f;
    g_rgvertCube[3].nz = 0.5f;

    // Vertex 4
    g_rgvertCube[4].x  = 0.5f;
    g_rgvertCube[4].y  = -0.5f;
    g_rgvertCube[4].z  = 0.5f;
    g_rgvertCube[4].nx = 0.5f;
    g_rgvertCube[4].ny = -0.5f;
    g_rgvertCube[4].nz = 0.5f;

    // Vertex 5
    g_rgvertCube[5].x  = 0.5f;
    g_rgvertCube[5].y  = -0.5f;
    g_rgvertCube[5].z  = -0.5f;
    g_rgvertCube[5].nx = 0.5f;
    g_rgvertCube[5].ny = -0.5f;
    g_rgvertCube[5].nz = -0.5f;

    // Vertex 6
    g_rgvertCube[6].x  = -0.5f;
    g_rgvertCube[6].y  = -0.5f;
    g_rgvertCube[6].z  = -0.5f;
    g_rgvertCube[6].nx = -0.5f;
    g_rgvertCube[6].ny = -0.5f;
    g_rgvertCube[6].nz = -0.5f;

    // Vertex 7
    g_rgvertCube[7].x  = -0.5f;
    g_rgvertCube[7].y  = -0.5f;
    g_rgvertCube[7].z  = 0.5f;
    g_rgvertCube[7].nx = -0.5f;
    g_rgvertCube[7].ny = -0.5f;
    g_rgvertCube[7].nz = 0.5f;

    // Initialize the indices

    // top face
    g_rgwCubeIndices[0]  = 0;
    g_rgwCubeIndices[1]  = 1;
    g_rgwCubeIndices[2]  = 2;
    g_rgwCubeIndices[3]  = 0;
    g_rgwCubeIndices[4]  = 2;
    g_rgwCubeIndices[5]  = 3;

    //bottom face
    g_rgwCubeIndices[6]  = 5;
    g_rgwCubeIndices[7]  = 4;
    g_rgwCubeIndices[8]  = 7;
    g_rgwCubeIndices[9]  = 5;
    g_rgwCubeIndices[10] = 7;
    g_rgwCubeIndices[11] = 6;

    //front face
    g_rgwCubeIndices[12] = 1;
    g_rgwCubeIndices[13] = 5;
    g_rgwCubeIndices[14] = 6;
    g_rgwCubeIndices[15] = 1;
    g_rgwCubeIndices[16] = 6;
    g_rgwCubeIndices[17] = 2;

    //back face
    g_rgwCubeIndices[18] = 3;
    g_rgwCubeIndices[19] = 7;
    g_rgwCubeIndices[20] = 4;
    g_rgwCubeIndices[21] = 3;
    g_rgwCubeIndices[22] = 4;
    g_rgwCubeIndices[23] = 0;

    //left face
    g_rgwCubeIndices[24] = 2;
    g_rgwCubeIndices[25] = 6;
    g_rgwCubeIndices[26] = 7;
    g_rgwCubeIndices[27] = 2;
    g_rgwCubeIndices[28] = 7;
    g_rgwCubeIndices[29] = 3;

    //right face
    g_rgwCubeIndices[30] = 0;
    g_rgwCubeIndices[31] = 4;
    g_rgwCubeIndices[32] = 5;
    g_rgwCubeIndices[33] = 0;
    g_rgwCubeIndices[34] = 5;
    g_rgwCubeIndices[35] = 1;
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

    // Initialize the sample 3D Cube's vertices and indices
    CreateCube();

    // Add a white light
    AddLight(1.0f, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f);

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
