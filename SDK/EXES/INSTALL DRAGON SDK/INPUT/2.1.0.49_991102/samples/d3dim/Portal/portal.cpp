/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999 Microsoft Corporation

Module Name:

    Portal.cpp

Abstract:

    Portal Application

-------------------------------------------------------------------*/

// ++++ Include Files +++++++++++++++++++++++++++++++++++++++++++++++
#include "Portal.hpp"

// ++++ Global Variables ++++++++++++++++++++++++++++++++++++++++++++
HWND      g_hwndApp;                                // HWND of the application
HINSTANCE g_hinst;                                  // HINSTANCE of the application

// ++++ Local Variables +++++++++++++++++++++++++++++++++++++++++++++
TCHAR                g_tszAppName[] = TEXT("Portal");  // The App's Name
LPDIRECT3DTEXTURE2   g_ptexFloor = NULL;
LPDIRECT3DTEXTURE2   g_ptexWall = NULL;
LPDIRECT3DTEXTURE2   g_ptexShade = NULL;
LPDIRECT3DTEXTURE2   g_ptexMirror = NULL;
LPDIRECTDRAWSURFACE4 g_pddsMirror = NULL;
D3DVERTEX            g_rgvertFloors[8];
D3DVERTEX            g_rgvertWalls[16];
WORD                 g_rgwFloorIndices[12];
WORD                 g_rgwWallIndices[24];
MLVERTEX             g_rgvertMirror[4];

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

    // Release the Mirror Surface
    if (g_pddsMirror)
        g_pddsMirror->Release();

    // Release the textures
    if (g_ptexWall)
        g_ptexWall->Release();

    if (g_ptexFloor)
        g_ptexFloor->Release();

    if (g_ptexShade)
        g_ptexShade->Release();

    if (g_ptexMirror)
        g_ptexMirror->Release();

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

    Renders the triangle to the back buffer using the Direct3D 
    DrawPrimitive method.

Arguments:
    
    None

Return Value:

    TRUE on success, FALSE on failure.

-------------------------------------------------------------------*/
BOOL 
RenderSceneToBackBuffer()
{
    D3DRECT d3drect;
    D3DMATRIX matWorld, matView, matProj, matRotate = g_matIdent;
    UINT uPass;
    static D3DVALUE fAngle = 0.0f;

    // Get the world matrix
    g_errLast = g_p3ddevice->GetTransform(D3DTRANSFORMSTATE_WORLD, &matWorld);
    if (CheckError(TEXT("Get Transform")))
        return FALSE;

    // Rotate the camera about the y axis
    g_cam.vectPosition.x = -10.0f * D3DVAL(sin(fAngle));
    g_cam.vectPosition.z = 10.0f * D3DVAL(cos(fAngle));
    SetView(&g_cam);
    fAngle += 0.005236f;
    if (fAngle > TWOPI) {
        fAngle -= TWOPI;
    }

    // Rotate the mirror about the y axis
    matRotate._11 = (float)cos(0.02f);
    matRotate._13 = (float)-sin(0.02f);
    matRotate._31 = (float)sin(0.02f);
    matRotate._33 = (float)cos(0.02f);

    for (uPass = 0; uPass < 2; uPass++) 
    {
        // Set up the rendering target and viewing matrices
        if (!uPass) 
        {
            // Set the texture as the new rendering target for the device
            if (!ReplaceRenderTarget(g_pddsMirror, &g_pddsBack, &d3drect))
                return FALSE;

            // Save the current view matrix
            g_errLast = g_p3ddevice->GetTransform(D3DTRANSFORMSTATE_VIEW, &matView);
            if (CheckError(TEXT("Get Transform")))
                return FALSE;

            // Move the camera to the portal's point of view
            if (!SetPortalView(&g_cam, g_rgvertMirror, &matWorld))
                return FALSE;
        }
        else 
        {
            // Restore the back buffer as the rendering target for the scene
            if (!ReplaceRenderTarget(g_pddsBack, &g_pddsMirror, &d3drect))
                return FALSE;

            // Restore the view matrix
            g_errLast = g_p3ddevice->SetTransform(D3DTRANSFORMSTATE_VIEW, &matView);
            if (CheckError(TEXT("Set Transform")))
                return FALSE;

            // Restore the projection matrix
            SetProjectionMatrix(&matProj, g_cam.rNearPlane, g_cam.rFarPlane,
                                g_cam.rFieldOfView, D3DVAL(d3drect.y2) / 
                                D3DVAL(d3drect.x2));

            g_errLast = g_p3ddevice->SetTransform(D3DTRANSFORMSTATE_PROJECTION, &matProj);
            if (CheckError(TEXT("Set Projection Matrix")))
                return FALSE;
        }

        // Clear the rendering target.
        g_errLast = g_pviewport->Clear(1, &d3drect, D3DCLEAR_TARGET);
        if (CheckError(TEXT("Clear Rendering Target")))
            return FALSE;

        // Begin the scene
        g_errLast = g_p3ddevice->BeginScene();
        if (CheckError(TEXT("Begin Scene")))
            return FALSE;

        // Set the world matrix to the identity matrix
        g_errLast = g_p3ddevice->SetTransform(D3DTRANSFORMSTATE_WORLD, &g_matIdent);
        if (CheckError(TEXT("Set Transform")))
            return FALSE;

        // Set the floor texture
        g_errLast = g_p3ddevice->SetTexture(0, g_ptexFloor);
        if (CheckError(TEXT("Set Texture")))
            return FALSE;

        // Draw the floor and ceiling
        g_errLast = g_p3ddevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, D3DFVF_VERTEX, 
                g_rgvertFloors, 8, g_rgwFloorIndices, 12, D3DDP_DONOTUPDATEEXTENTS);
        if (CheckError(TEXT("Draw Floor")))
            return FALSE;

        // Set the wall texture
        g_errLast = g_p3ddevice->SetTexture(0, g_ptexWall);
        if (CheckError(TEXT("Set Texture")))
            return FALSE;

        // Draw the walls
        g_errLast = g_p3ddevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, D3DFVF_VERTEX, 
                g_rgvertWalls, 16, g_rgwWallIndices, 24, D3DDP_DONOTUPDATEEXTENTS);
        if (CheckError(TEXT("Draw Floor")))
            return FALSE;

        g_errLast = g_p3ddevice->SetTransform(D3DTRANSFORMSTATE_WORLD, &matWorld);
        if (CheckError(TEXT("Set Transform")))
            return FALSE;

        // Render the mirror
        if (uPass) 
        {
            // Disable perspective correct texture mapping since the perspective
            // of the mirror's reflection was already set on the first rendering pass
            g_errLast = g_p3ddevice->SetRenderState(D3DRENDERSTATE_TEXTUREPERSPECTIVE, (DWORD)FALSE);
            if (CheckError(TEXT("Disable perspective correction")))
                return FALSE;

            // Set the mirror's textures
            g_errLast = g_p3ddevice->SetTexture(0, g_ptexMirror);
            if (CheckError(TEXT("Set Texture")))
                return FALSE;

            g_errLast = g_p3ddevice->SetTexture(1, g_ptexShade);
            if (CheckError(TEXT("Set Texture")))
                return FALSE;

            // Use color and alpha information from the texture for the first stage
            SetColorStage(0, D3DTA_TEXTURE, D3DTA_DIFFUSE, D3DTOP_SELECTARG1);
            SetAlphaStage(0, D3DTA_TEXTURE, D3DTA_DIFFUSE, D3DTOP_SELECTARG1);

            // Modulate the color and alpha information with the alpha texture for the second stage
            SetColorStage(1, D3DTA_TEXTURE, D3DTA_CURRENT, D3DTOP_MODULATE);
            SetAlphaStage(1, D3DTA_TEXTURE, D3DTA_CURRENT, D3DTOP_MODULATE);

            // Enable blending
            g_p3ddevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE, TRUE);

            // Disable back face culling
            g_p3ddevice->SetRenderState(D3DRENDERSTATE_CULLMODE, (DWORD)D3DCULL_NONE);

            // Draw the mirror
            g_errLast = g_p3ddevice->DrawPrimitive(D3DPT_TRIANGLEFAN, FVF_MLVERTEX, 
                    g_rgvertMirror, 4, D3DDP_DONOTUPDATEEXTENTS);
            if (CheckError(TEXT("Draw Mirror")))
                return FALSE;

            // Enable counterclockwise back face culling
            g_p3ddevice->SetRenderState(D3DRENDERSTATE_CULLMODE, (DWORD)D3DCULL_CCW);

            // Disable blending
            g_p3ddevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE, FALSE);

            // Modulate color and select texture alpha for the first stage
            SetColorStage(0, D3DTA_TEXTURE, D3DTA_DIFFUSE, D3DTOP_MODULATE);
            SetAlphaStage(0, D3DTA_TEXTURE, D3DTA_DIFFUSE, D3DTOP_SELECTARG1);

            // Disable texture and blend operations for the second stage
            g_p3ddevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_DISABLE);
            g_p3ddevice->SetTextureStageState(1, D3DTSS_ALPHAOP, D3DTOP_DISABLE);
            g_p3ddevice->SetTexture(1, NULL);

            // Update the rotation
            g_errLast = g_p3ddevice->MultiplyTransform(D3DTRANSFORMSTATE_WORLD, &matRotate);
            if (CheckError(TEXT("Multiply Transform")))
                return FALSE;

            // Restore perspective correct texture mapping
            g_errLast = g_p3ddevice->SetRenderState(D3DRENDERSTATE_TEXTUREPERSPECTIVE, (DWORD)TRUE);
            if (CheckError(TEXT("Enable perspective correction")))
                return FALSE;
        }

        // End the scene
        g_errLast = g_p3ddevice->EndScene();
        if (CheckError(TEXT("EndScene")))
            return FALSE;
    }

    return TRUE;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    UpdateFrame

Description:

    This function is called whenever the CPU is idle.  The application
    should update it's state and rerender to the screen if appropriate.

Return Value:

    None.

-------------------------------------------------------------------*/
void 
UpdateFrame ()
{
    // Render the cube
    if (!RenderSceneToBackBuffer())
        return;
    
    // Flip the buffers
    FlipBuffers();
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    InitVertices

Description:

    Initialize the scene's vertices.

Arguments:

    None

Return Value:

    None

-------------------------------------------------------------------*/
void 
InitVertices()
{
    // Initialize the floor and ceiling vertices
    g_rgvertFloors[0] = D3DVERTEX(D3DVECTOR(-10.0f,-10.0f,-10.0f), 
                                 D3DVECTOR(0.0f, 1.0f, 0.0f), 0.0f, 1.0f);
    g_rgvertFloors[1] = D3DVERTEX(D3DVECTOR(-10.0f,-10.0f, 10.0f), 
                                 D3DVECTOR(0.0f, 1.0f, 0.0f), 0.0f, 0.0f);
    g_rgvertFloors[2] = D3DVERTEX(D3DVECTOR( 10.0f,-10.0f, 10.0f), 
                                 D3DVECTOR(0.0f, 1.0f, 0.0f), 1.0f, 0.0f);
    g_rgvertFloors[3] = D3DVERTEX(D3DVECTOR( 10.0f,-10.0f,-10.0f), 
                                 D3DVECTOR(0.0f, 1.0f, 0.0f), 1.0f, 1.0f);

    g_rgvertFloors[4] = D3DVERTEX(D3DVECTOR(-10.0f, 10.0f, 10.0f), 
                                 D3DVECTOR(0.0f, -1.0f, 0.0f), 0.0f, 1.0f);
    g_rgvertFloors[5] = D3DVERTEX(D3DVECTOR(-10.0f, 10.0f,-10.0f), 
                                 D3DVECTOR(0.0f, -1.0f, 0.0f), 0.0f, 0.0f);
    g_rgvertFloors[6] = D3DVERTEX(D3DVECTOR( 10.0f, 10.0f,-10.0f), 
                                 D3DVECTOR(0.0f, -1.0f, 0.0f), 1.0f, 0.0f);
    g_rgvertFloors[7] = D3DVERTEX(D3DVECTOR( 10.0f, 10.0f, 10.0f), 
                                 D3DVECTOR(0.0f, -1.0f, 0.0f), 1.0f, 1.0f);

    // Initialize the wall vertices
    g_rgvertWalls[0] = D3DVERTEX(D3DVECTOR(-10.0f,-10.0f,-10.0f), 
                                 D3DVECTOR(1.0f, 0.0f, 0.0f), 0.0f, 1.0f);
    g_rgvertWalls[1] = D3DVERTEX(D3DVECTOR(-10.0f, 10.0f,-10.0f), 
                                 D3DVECTOR(1.0f, 0.0f, 0.0f), 0.0f, 0.0f);
    g_rgvertWalls[2] = D3DVERTEX(D3DVECTOR(-10.0f, 10.0f, 10.0f), 
                                 D3DVECTOR(1.0f, 0.0f, 0.0f), 1.0f, 0.0f);
    g_rgvertWalls[3] = D3DVERTEX(D3DVECTOR(-10.0f,-10.0f, 10.0f), 
                                 D3DVECTOR(1.0f, 0.0f, 0.0f), 1.0f, 1.0f);

    g_rgvertWalls[4] = D3DVERTEX(D3DVECTOR(10.0f,-10.0f, 10.0f), 
                                 D3DVECTOR(-1.0f, 0.0f, 0.0f), 0.0f, 1.0f);
    g_rgvertWalls[5] = D3DVERTEX(D3DVECTOR(10.0f, 10.0f, 10.0f), 
                                 D3DVECTOR(-1.0f, 0.0f, 0.0f), 0.0f, 0.0f);
    g_rgvertWalls[6] = D3DVERTEX(D3DVECTOR(10.0f, 10.0f,-10.0f), 
                                 D3DVECTOR(-1.0f, 0.0f, 0.0f), 1.0f, 0.0f);
    g_rgvertWalls[7] = D3DVERTEX(D3DVECTOR(10.0f,-10.0f,-10.0f), 
                                 D3DVECTOR(-1.0f, 0.0f, 0.0f), 1.0f, 1.0f);

    g_rgvertWalls[8] = D3DVERTEX(D3DVECTOR(-10.0f,-10.0f, 10.0f), 
                                 D3DVECTOR(0.0f, 0.0f, -1.0f), 0.0f, 1.0f);
    g_rgvertWalls[9] = D3DVERTEX(D3DVECTOR(-10.0f, 10.0f, 10.0f), 
                                 D3DVECTOR(0.0f, 0.0f, -1.0f), 0.0f, 0.0f);
    g_rgvertWalls[10] = D3DVERTEX(D3DVECTOR(10.0f, 10.0f, 10.0f), 
                                 D3DVECTOR(0.0f, 0.0f, -1.0f), 1.0f, 0.0f);
    g_rgvertWalls[11] = D3DVERTEX(D3DVECTOR(10.0f,-10.0f, 10.0f), 
                                 D3DVECTOR(0.0f, 0.0f, -1.0f), 1.0f, 1.0f);

    g_rgvertWalls[12] = D3DVERTEX(D3DVECTOR(10.0f,-10.0f,-10.0f), 
                                 D3DVECTOR(0.0f, 0.0f, 1.0f), 0.0f, 1.0f);
    g_rgvertWalls[13] = D3DVERTEX(D3DVECTOR(10.0f, 10.0f,-10.0f), 
                                 D3DVECTOR(0.0f, 0.0f, 1.0f), 0.0f, 0.0f);
    g_rgvertWalls[14] = D3DVERTEX(D3DVECTOR(-10.0f, 10.0f,-10.0f), 
                                 D3DVECTOR(0.0f, 0.0f, 1.0f), 1.0f, 0.0f);
    g_rgvertWalls[15] = D3DVERTEX(D3DVECTOR(-10.0f,-10.0f,-10.0f), 
                                 D3DVECTOR(0.0f, 0.0f, 1.0f), 1.0f, 1.0f);

    // Initialize the floor and ceiling indices
    g_rgwFloorIndices[0]  = 0;
    g_rgwFloorIndices[1]  = 1;
    g_rgwFloorIndices[2]  = 2;
    g_rgwFloorIndices[3]  = 0;
    g_rgwFloorIndices[4]  = 2;
    g_rgwFloorIndices[5]  = 3;

    g_rgwFloorIndices[6]  = 4;
    g_rgwFloorIndices[7]  = 5;
    g_rgwFloorIndices[8]  = 6;
    g_rgwFloorIndices[9]  = 4;
    g_rgwFloorIndices[10] = 6;
    g_rgwFloorIndices[11] = 7;

    // Initialize the wall indices
    g_rgwWallIndices[0]  = 0;
    g_rgwWallIndices[1]  = 1;
    g_rgwWallIndices[2]  = 2;
    g_rgwWallIndices[3]  = 0;
    g_rgwWallIndices[4]  = 2;
    g_rgwWallIndices[5]  = 3;

    g_rgwWallIndices[6]  = 4;
    g_rgwWallIndices[7]  = 5;
    g_rgwWallIndices[8]  = 6;
    g_rgwWallIndices[9]  = 4;
    g_rgwWallIndices[10] = 6;
    g_rgwWallIndices[11] = 7;

    g_rgwWallIndices[12] = 8;
    g_rgwWallIndices[13] = 9;
    g_rgwWallIndices[14] = 10;
    g_rgwWallIndices[15] = 8;
    g_rgwWallIndices[16] = 10;
    g_rgwWallIndices[17] = 11;

    g_rgwWallIndices[18] = 12;
    g_rgwWallIndices[19] = 13;
    g_rgwWallIndices[20] = 14;
    g_rgwWallIndices[21] = 12;
    g_rgwWallIndices[22] = 14;
    g_rgwWallIndices[23] = 15;

    // Initialize the vertices for the mirror.  The vertices are lit
    // so the mirror isn't affected by the lighting in the scene
    // on the second rendering pass.  The two texture coordinate sets
    // are used for multistage texturing.
    g_rgvertMirror[0].vectPosition = D3DVECTOR(-4.0f, -4.0f, 2.0f);
    g_rgvertMirror[0].u0 = g_rgvertMirror[0].u1 = 0.0f;
    g_rgvertMirror[0].v0 = g_rgvertMirror[0].v1 = 1.0f;

    g_rgvertMirror[1].vectPosition = D3DVECTOR(-4.0f, 4.0f, 0.0f);
    g_rgvertMirror[1].u0 = g_rgvertMirror[1].u1 = 0.0f;
    g_rgvertMirror[1].v0 = g_rgvertMirror[1].v1 = 0.0f;

    g_rgvertMirror[2].vectPosition = D3DVECTOR( 4.0f, 4.0f, 0.0f);
    g_rgvertMirror[2].u0 = g_rgvertMirror[2].u1 = 1.0f;
    g_rgvertMirror[2].v0 = g_rgvertMirror[2].v1 = 0.0f;

    g_rgvertMirror[3].vectPosition = D3DVECTOR( 4.0f, -4.0f, 2.0f);
    g_rgvertMirror[3].u0 = g_rgvertMirror[3].u1 = 1.0f;
    g_rgvertMirror[3].v0 = g_rgvertMirror[3].v1 = 1.0f;
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

    // Load the floor texture
    g_ptexFloor = LoadTexture(TEXT("Floor"));
    if (!g_ptexFloor)
    {
        RetailOutput(TEXT("Error: Failed to load texture\r\n"));
        return FALSE;
    }

    // Load the wall texture
    g_ptexWall = LoadTexture(TEXT("Wall"));
    if (!g_ptexWall)
    {
        RetailOutput(TEXT("Error: Failed to load texture\r\n"));
        return FALSE;
    }

    // Load the alpha texture to blend with the mirror
    g_ptexShade = LoadAlphaTexture(TEXT("Shade"));
    if (!g_ptexShade)
    {
        RetailOutput(TEXT("Error: Failed to load texture\r\n"));
        return FALSE;
    }

    // Create the mirror texture as a rendering target
    g_ptexMirror = CreateTargetTexture(256, 256);
    if (!g_ptexMirror)
        return FALSE;

    // Query the texture for its surface interface
    g_errLast = g_ptexMirror->QueryInterface(IID_IDirectDrawSurface4, (LPVOID*)&g_pddsMirror);
    if (CheckError(TEXT("Query Surface Interface")))
        return FALSE;

    // Note that on the desktop the rendering device could have
    // an associated z buffer.  In this case we would have
    // to also create a z buffer for the texture target.

    // Initialize the vertices that we will draw
    InitVertices();

    // Add a white light
    AddLight(1.0f, 1.0f, 1.0f, 0.0f, -1.0f, -1.0f);

    // Initialize texture coordinates to their appropriate stages
	g_p3ddevice->SetTextureStageState(0, D3DTSS_TEXCOORDINDEX, 0);
	g_p3ddevice->SetTextureStageState(1, D3DTSS_TEXCOORDINDEX, 1);

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
_tWinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
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
                return msg.wParam;

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

    return msg.wParam;
}
