/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999 Microsoft Corporation

Module Name:

    ShadowVolumes.cpp

Abstract:

    ShadowVolumes Application

-------------------------------------------------------------------*/

// ++++ Include Files +++++++++++++++++++++++++++++++++++++++++++++++
#include "ShadowVolumes.hpp"

// ++++ Global Variables ++++++++++++++++++++++++++++++++++++++++++++
HWND      g_hwndApp;                                // HWND of the application
HINSTANCE g_hinst;                                  // HINSTANCE of the application

// ++++ Local Variables +++++++++++++++++++++++++++++++++++++++++++++
TCHAR     g_tszAppName[] = TEXT("ShadowVolumes");   // The App's Name

D3DVERTEX g_rgvertTri[3];                           // "Modifier Volume Top" polygon
D3DVERTEX g_rgvertModVol[6];                        // Modifier volume vertices
int       g_nModVolVerts = 6;                       // Number of vertices in the modifier volume
WORD      g_pwModVolIndices[24] = {0,1,2,           // List of modifier volume indices
                                   3,4,5,
                                   0,1,4,
                                   0,4,3,
                                   1,2,5,
                                   1,4,5,
                                   0,2,5,
                                   0,3,5};
int       g_nModVolIndices = 24;                    // Number of indicies in the modifier volume
D3DVERTEX *g_pvertSphere;                           // List of strip vertices
WORD      *g_pIndices;                              // List of strip indices
int       g_nSphereVerts, g_nIndices;               // Number of strip indices and vertices
int       g_nPolys;                                 // Number of polygons per strip
int       g_nStripWidth  = 20;                      // Dimensions of sphere
int       g_nStripHeight = 20;                      // Dimensions of sphere
int       g_nShadowIntensity;                       // Amount that the shadow volume affects the scene
unsigned int *g_puiSphereOrigin = NULL;             // Pointer to actual (possibly unaligned) alloc address.

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
    // Release the sphere
    if (g_puiSphereOrigin)
        free(g_puiSphereOrigin);

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

    // Set the upcoming modifier volume to be an "include" modifier volume.
    // NOTE: After setting this renderstate, the next DrawPrimitive (or other related function)
    //       called will be used to define the modifier volume.
    g_p3ddevice->SetRenderState(D3DRENDERSTATE_FILLMODE, D3DFILL_INCLUDE);
    g_p3ddevice->SetRenderState(D3DRENDERSTATE_CULLMODE, D3DCULL_NONE );

    g_p3ddevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, D3DVT_VERTEX,
                                      (LPVOID) g_rgvertModVol, g_nModVolVerts,
                                      g_pwModVolIndices, g_nModVolIndices,
                                      D3DDP_DONOTUPDATEEXTENTS | D3DDP_DONOTCLIP);

    // Revert to solid-fill mode
    g_p3ddevice->SetRenderState(D3DRENDERSTATE_FILLMODE, D3DFILL_SOLID);
    g_p3ddevice->SetRenderState(D3DRENDERSTATE_CULLMODE, D3DCULL_CCW);


    // Set intensity of shadow Volume (0 == totally dark, 255 == totally unaffected)
    g_p3ddevice->SetRenderState(D3DRENDERSTATE_SHADOWLEVEL, g_nShadowIntensity);

    // Draw the sphere
    g_p3ddevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, D3DVT_VERTEX,
                                      (LPVOID) g_pvertSphere, g_nSphereVerts, g_pIndices, g_nIndices,
                                      D3DDP_DONOTUPDATEEXTENTS | D3DDP_DONOTCLIP);

    // Draw the "modifier volume top" triangle
    g_p3ddevice->DrawPrimitive(D3DPT_TRIANGLELIST, D3DVT_VERTEX, (LPVOID) g_rgvertTri, 3,
                               D3DDP_DONOTUPDATEEXTENTS | D3DDP_DONOTCLIP);

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
    
    None

Return Value:

    None.

-------------------------------------------------------------------*/
void 
UpdateFrame ()
{
    static float s_rPoint = 0.0f;

    // Rotate the modifier volume's top
    g_rgvertTri[0].x = (float)sin(s_rPoint) / 2.0f;
    g_rgvertTri[0].z = (float)cos(s_rPoint) / 2.0f;
    g_rgvertTri[1].x = (float)sin(s_rPoint + 4.0f * PI / 3.0f) / 2.0f;
    g_rgvertTri[1].z = (float)cos(s_rPoint + 4.0f * PI / 3.0f) / 2.0f;
    g_rgvertTri[2].x = (float)sin(s_rPoint + 2.0f * PI / 3.0f) / 2.0f;
    g_rgvertTri[2].z = (float)cos(s_rPoint + 2.0f * PI / 3.0f) / 2.0f;

    // Update the modifier volume's volume (tri top, slightly flared tri bottom)
    g_rgvertModVol[0].x = g_rgvertTri[0].x;
    g_rgvertModVol[0].z = g_rgvertTri[0].z;
    g_rgvertModVol[1].x = g_rgvertTri[1].x;
    g_rgvertModVol[1].z = g_rgvertTri[1].z;
    g_rgvertModVol[2].x = g_rgvertTri[2].x;
    g_rgvertModVol[2].z = g_rgvertTri[2].z;
    g_rgvertModVol[3].x = (float)sin(s_rPoint) / 1.5f;
    g_rgvertModVol[3].z = (float)cos(s_rPoint) / 1.5f;
    g_rgvertModVol[4].x = (float)sin(s_rPoint + 4.0f * PI / 3.0f) / 1.5f;
    g_rgvertModVol[4].z = (float)cos(s_rPoint + 4.0f * PI / 3.0f) / 1.5f;
    g_rgvertModVol[5].x = (float)sin(s_rPoint + 2.0f * PI / 3.0f) / 1.5f;
    g_rgvertModVol[5].z = (float)cos(s_rPoint + 2.0f * PI / 3.0f) / 1.5f;

    // Rotate the shadow's intensity between 0 and 255
    g_nShadowIntensity = ( (int)(((float)sin(s_rPoint)) * 128.0f) + 128 ) % 256;
    s_rPoint += 0.05f;

    // Render the scene
    if (!RenderSceneToBackBuffer())
        return;
    
    // Flip the buffers
    FlipBuffers();
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    InitSphere

Description:

    Generates the vertices for a sphere.

Arguments:
    
    None

Return Value:

    None.

-------------------------------------------------------------------*/
void
InitSphere()
{
    int i,j;

    // Create the strip vertices.
    g_nSphereVerts = (g_nStripWidth + 1) * (g_nStripHeight + 1);

    // Allocate the strip on an aligned boundary - this is VERY important for performance.
    g_puiSphereOrigin = (unsigned int*)malloc((g_nSphereVerts + 1)* sizeof(D3DVERTEX));
    g_pvertSphere = (LPD3DVERTEX)(((unsigned int)((char*)g_puiSphereOrigin + 31 ) & ~31));
    
    // Create the strip.
    for (j = 0; j <= g_nStripHeight; j++)
    {
        for (i = 0; i <= g_nStripWidth; i++)
        {
            int nVert = j * (g_nStripWidth + 1) + i;
            D3DVERTEX *pVert = &g_pvertSphere[nVert];

            float rX  = (float)i / (float)(g_nStripWidth);
            float rY  = (float)j / (float)(g_nStripHeight);
            float rXP = rX * 2.0f * PI;
            float rYP = rY * 2.0f * PI;

            pVert->x  = (float)(sin(rXP) * sin(rYP));
            pVert->y  = (float)(cos(rYP));
            pVert->z  = (float)(cos(rXP) * sin(rYP));

            // Not prelit; use normals
            pVert->nx = pVert->x;
            pVert->ny = pVert->y;
            pVert->nz = pVert->z;

            // Move the sphere down a little
            pVert->y -= 1.75f;

            // Normalize the normals of the vertex
            NormalizeVector((D3DVECTOR*)(&pVert->nx));

            pVert->tu = (float)i / (float)(g_nStripWidth)  * 4.0f;
            pVert->tv = (float)j / (float)(g_nStripHeight) * 4.0f;
        }
    }

    // Create the strip indices.
    int iIndex = 0;

    int nIndexWidth = (g_nStripWidth + 1) * 2;

    g_nIndices = (nIndexWidth+1) * g_nStripHeight;

    g_pIndices = new WORD[g_nIndices];
    for (j = 0; j < g_nStripHeight/2; j++)
    {
        for (i=nIndexWidth/2; i < nIndexWidth; i++)
        {
            g_pIndices[iIndex++] = i + j * nIndexWidth;
            g_pIndices[iIndex++] = i - (nIndexWidth/2) + j * nIndexWidth;
        }

        g_pIndices[iIndex++] = nIndexWidth * (j + 1) - 1;
        g_pIndices[iIndex++] = nIndexWidth * (j + 1) - 1;

        for (i = nIndexWidth - 1; i >= (nIndexWidth/2); i--)
        {
            g_pIndices[iIndex++] = i + j * nIndexWidth;
            g_pIndices[iIndex++] = i - (nIndexWidth / 2) + (j + 1) * nIndexWidth;
        }
    }

    // Calculate the number of polygons in the strip
    g_nPolys = (g_nIndices * 2 / g_nStripHeight - 3) * g_nStripHeight / 2;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    InitModifierVolume

Description:

    Generates the vertices for the modifier volume

Arguments:
    
    None

Return Value:

    None.

-------------------------------------------------------------------*/
void
InitModifierVolume()
{
    // x & z are set in UpdateFrame - just set the others here
    g_rgvertTri[0].y  = 1.0f;
    g_rgvertTri[0].nx = 0.0f;
    g_rgvertTri[0].ny = -1.0f;
    g_rgvertTri[0].nz = 0.0f;

    g_rgvertTri[2].y  = 1.0f;
    g_rgvertTri[2].nx = 0.0f;
    g_rgvertTri[2].ny = -1.0f;
    g_rgvertTri[2].nz = 0.0f;

    g_rgvertTri[1].y  = 1.0f;
    g_rgvertTri[1].nx = 0.0f;
    g_rgvertTri[1].ny = -1.0f;
    g_rgvertTri[1].nz = 0.0f;

    g_rgvertModVol[0].y = 1.0f;
    g_rgvertModVol[1].y = 1.0f;
    g_rgvertModVol[2].y = 1.0f;
    g_rgvertModVol[3].y = -1.0f;
    g_rgvertModVol[4].y = -1.0f;
    g_rgvertModVol[5].y = -1.0f;
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

    // Initialize the vertices of a sphere
    InitSphere();

    // Add a white light
    AddLight(1.0f, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f);

    // Add a triangle which will act as the "top" of the modifier volume.  Note that this
    // is not necessary for the modifier volume to work - it is included merely to make it clear where
    // the modifier volume is visually.
    InitModifierVolume();

    // Enable shadow mode (Only needs to be done once unless some objects aren't shadowed)
    g_p3ddevice->SetRenderState(D3DRENDERSTATE_SHADOWENABLE, TRUE);

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
