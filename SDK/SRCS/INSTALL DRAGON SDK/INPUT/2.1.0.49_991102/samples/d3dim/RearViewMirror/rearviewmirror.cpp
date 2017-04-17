/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999 Microsoft Corporation

Module Name:

    RearViewMirror.cpp

Abstract:

    RearViewMirror Application

-------------------------------------------------------------------*/

// ++++ Include Files +++++++++++++++++++++++++++++++++++++++++++++++
#include "RearViewMirror.hpp"

// ++++ Global Variables ++++++++++++++++++++++++++++++++++++++++++++
HWND      g_hwndApp;                                // HWND of the application
HINSTANCE g_hinst;                                  // HINSTANCE of the application

// ++++ Local Variables +++++++++++++++++++++++++++++++++++++++++++++
TCHAR                g_tszAppName[] = TEXT("RearViewMirror");  // The App's Name
LPDIRECT3DTEXTURE2   g_ptexTrench = NULL;
LPDIRECT3DTEXTURE2   g_ptexShade = NULL;
LPDIRECT3DTEXTURE2   g_ptexMirror = NULL;
LPDIRECTDRAWSURFACE4 g_pddsMirror = NULL;
MLVERTEX             g_rgvertMirror[4];
D3DVERTEX            g_rgvertTrench[12];
WORD				 g_rgwTrenchIndices[18];
D3DVERTEX            g_rgvertCube[8];
WORD                 g_rgwCubeIndices[36];
LPDIRECT3DMATERIAL3  g_pmatCube[5] = {NULL};
D3DMATERIALHANDLE    g_hmatCube[5];

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
    int i;

    // Release global light
    for (i = 0; i < g_cLights; i++)
        g_rglight[i]->Release();
    
    // Release global materials
    for (i = 0; i < 5; i++) 
    {
        if (g_pmatCube[i]) 
        {
            g_pmatCube[i]->Release();
        }
    }
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
    if (g_ptexTrench)
        g_ptexTrench->Release();

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
    D3DRECT         d3drect;
    D3DMATRIX       matView, matProj, matMirror, matCube = g_matIdent;
    static D3DVALUE rAngle = 0.0f;
    int             i;
    UINT            uPass;

    // Translate the view along the z axis 
    g_cam.vectPosition.z += 2.0f;
    g_cam.vectInterest.z += 2.0f;
    if (g_cam.vectPosition.z >= 1000.0f) 
    {
        g_cam.vectPosition.z = -1000.0f;
        g_cam.vectInterest.z = -950.0f;
    }
    SetView(&g_cam);

    // Set the mirror's world matrix to keep it positioned in front of the camera
    matMirror = g_matIdent;
    matMirror._43 = g_cam.vectPosition.z;

    // Rotate the cube about the y axis
    matCube._11 = (float)cos(rAngle);
    matCube._13 = (float)-sin(rAngle);
    matCube._31 = (float)sin(rAngle);
    matCube._33 = (float)cos(rAngle);
    matCube._42 = -5.0f;

    rAngle += 0.07f;
    if (rAngle > TWOPI)
    {
        rAngle -= TWOPI;
    }

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

            // Move the camera to the mirror's point of view
            if (!SetReflectedView(&g_cam, g_rgvertMirror, &matMirror))
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

        // Set the trench texture
        g_errLast = g_p3ddevice->SetTexture(0, g_ptexTrench);
        if (CheckError(TEXT("Set Texture")))
            return FALSE;

        // Set the world matrix for the trench
        g_errLast = g_p3ddevice->SetTransform(D3DTRANSFORMSTATE_WORLD, &g_matIdent);
        if (CheckError(TEXT("Set Transform")))
            return FALSE;

        // Draw the trench
        g_errLast = g_p3ddevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, D3DFVF_VERTEX, 
                g_rgvertTrench, 12, g_rgwTrenchIndices, 18, D3DDP_DONOTUPDATEEXTENTS);
        if (CheckError(TEXT("Draw Trench")))
            return FALSE;

        // Clear the trench texture
        g_errLast = g_p3ddevice->SetTexture(0, NULL);
        if (CheckError(TEXT("Set Texture")))
            return FALSE;

        // Draw a series of cubes evenly spaced along the trench
        for (i = 0; i < 5; i++) {

            // Set a material for the cube
            g_p3ddevice->SetLightState(D3DLIGHTSTATE_MATERIAL, g_hmatCube[i]);

            for (matCube._43 = 2000.0f + 200.0f * D3DVAL(i); 
                 matCube._43 > -2000.0f; matCube._43 -= 1000.0f) 
            {
                // Set the world matrix for the cube
                g_errLast = g_p3ddevice->SetTransform(D3DTRANSFORMSTATE_WORLD, &matCube);
                if (CheckError(TEXT("Set Transform")))
                    return FALSE;

                // Draw the cube
                g_errLast = g_p3ddevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, D3DFVF_VERTEX, 
                                g_rgvertCube, 8, g_rgwCubeIndices, 36, D3DDP_DONOTUPDATEEXTENTS);
                if (CheckError(TEXT("Draw Primitive")))
                    return FALSE;
            }
        }

        // Restore the default material
        g_p3ddevice->SetLightState(D3DLIGHTSTATE_MATERIAL, g_hmatWhite);

        // Set the world matrix for the mirror
        g_errLast = g_p3ddevice->SetTransform(D3DTRANSFORMSTATE_WORLD, &matMirror);
        if (CheckError(TEXT("Set Transform")))
            return FALSE;

        // Render the mirror
        if (!uPass) 
        {
            // Set the texture coordinates of the mirror in such a way as to
            // clip the scene rendered in the first pass to the mirror's boundaries
            g_errLast = SetReflectionTextureCoords(g_rgvertMirror, 4);
            if (CheckError(TEXT("Set Reflection Texture Coordinates")))
                return FALSE;
        }
        else 
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

            SetColorStage(0, D3DTA_TEXTURE, D3DTA_DIFFUSE, D3DTOP_SELECTARG1);
            SetAlphaStage(0, D3DTA_TEXTURE, D3DTA_DIFFUSE, D3DTOP_SELECTARG1);
            SetColorStage(1, D3DTA_TEXTURE, D3DTA_CURRENT, D3DTOP_MODULATE);
            SetAlphaStage(1, D3DTA_TEXTURE, D3DTA_CURRENT, D3DTOP_MODULATE);

            g_p3ddevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE, TRUE);

            // Draw the mirror
            g_errLast = g_p3ddevice->DrawPrimitive(D3DPT_TRIANGLEFAN, FVF_MLVERTEX, 
                    g_rgvertMirror, 4, D3DDP_DONOTUPDATEEXTENTS);
            if (CheckError(TEXT("Draw Mirror")))
                return FALSE;

            g_p3ddevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE, FALSE);

            SetColorStage(0, D3DTA_TEXTURE, D3DTA_DIFFUSE, D3DTOP_MODULATE);
            SetAlphaStage(0, D3DTA_TEXTURE, D3DTA_DIFFUSE, D3DTOP_SELECTARG1);
            g_p3ddevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_DISABLE);
            g_p3ddevice->SetTextureStageState(1, D3DTSS_ALPHAOP, D3DTOP_DISABLE);
            g_p3ddevice->SetTexture(1, NULL);

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

    CreateTrench

Description:

    Initialize the trench's vertices.

Arguments:

    None

Return Value:

    None

-------------------------------------------------------------------*/
void 
CreateTrench()
{
    // Initialize the trench's vertices

    // Floor
    g_rgvertTrench[0] = D3DVERTEX(D3DVECTOR(-10.0f,-10.0f,-3000.0f), 
                                 D3DVECTOR(0.0f, 1.0f, 0.0f), 0.0f, 300.0f);
    g_rgvertTrench[1] = D3DVERTEX(D3DVECTOR(-10.0f,-10.0f, 3000.0f), 
                                 D3DVECTOR(0.0f, 1.0f, 0.0f), 0.0f, 0.0f);
    g_rgvertTrench[2] = D3DVERTEX(D3DVECTOR( 10.0f,-10.0f, 3000.0f), 
                                 D3DVECTOR(0.0f, 1.0f, 0.0f), 5.0f, 0.0f);
    g_rgvertTrench[3] = D3DVERTEX(D3DVECTOR( 10.0f,-10.0f,-3000.0f), 
                                 D3DVECTOR(0.0f, 1.0f, 0.0f), 5.0f, 300.0f);
    // Left wall
    g_rgvertTrench[4] = D3DVERTEX(D3DVECTOR(-10.0f,-10.0f,-3000.0f), 
                                 D3DVECTOR(1.0f, 0.0f, 0.0f), 0.0f, 5.0f);
    g_rgvertTrench[5] = D3DVERTEX(D3DVECTOR(-10.0f, 10.0f,-3000.0f), 
                                 D3DVECTOR(1.0f, 0.0f, 0.0f), 0.0f, 0.0f);
    g_rgvertTrench[6] = D3DVERTEX(D3DVECTOR(-10.0f, 10.0f, 3000.0f), 
                                 D3DVECTOR(1.0f, 0.0f, 0.0f), 300.0f, 0.0f);
    g_rgvertTrench[7] = D3DVERTEX(D3DVECTOR(-10.0f,-10.0f, 3000.0f), 
                                 D3DVECTOR(1.0f, 0.0f, 0.0f), 300.0f, 5.0f);

    // Right wall
    g_rgvertTrench[8]  = D3DVERTEX(D3DVECTOR(10.0f,-10.0f, 3000.0f), 
                                 D3DVECTOR(-1.0f, 0.0f, 0.0f), 0.0f, 5.0f);
    g_rgvertTrench[9]  = D3DVERTEX(D3DVECTOR(10.0f, 10.0f, 3000.0f), 
                                 D3DVECTOR(-1.0f, 0.0f, 0.0f), 0.0f, 0.0f);
    g_rgvertTrench[10] = D3DVERTEX(D3DVECTOR(10.0f, 10.0f,-3000.0f), 
                                 D3DVECTOR(-1.0f, 0.0f, 0.0f), 300.0f, 0.0f);
    g_rgvertTrench[11] = D3DVERTEX(D3DVECTOR(10.0f,-10.0f,-3000.0f), 
                                 D3DVECTOR(-1.0f, 0.0f, 0.0f), 300.0f, 5.0f);

    // Initialize the trench's indices

    // Floor
    g_rgwTrenchIndices[0]  = 0;
    g_rgwTrenchIndices[1]  = 1;
    g_rgwTrenchIndices[2]  = 2;
    g_rgwTrenchIndices[3]  = 0;
    g_rgwTrenchIndices[4]  = 2;
    g_rgwTrenchIndices[5]  = 3;

    // Left wall
    g_rgwTrenchIndices[6]  = 4;
    g_rgwTrenchIndices[7]  = 5;
    g_rgwTrenchIndices[8]  = 6;
    g_rgwTrenchIndices[9]  = 4;
    g_rgwTrenchIndices[10] = 6;
    g_rgwTrenchIndices[11] = 7;

    // Right wall
    g_rgwTrenchIndices[12] = 8;
    g_rgwTrenchIndices[13] = 9;
    g_rgwTrenchIndices[14] = 10;
    g_rgwTrenchIndices[15] = 8;
    g_rgwTrenchIndices[16] = 10;
    g_rgwTrenchIndices[17] = 11;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    CreateMirror

Description:

    Initialize the mirror's vertices.

Arguments:

    None

Return Value:

    None

-------------------------------------------------------------------*/
void 
CreateMirror()
{
    // Initialize the vertices for the mirror.  The vertices are lit
    // so the mirror isn't affected by the lighting in the scene
    // on the second rendering pass.  The two texture coordinate sets
    // are used for multistage texturing.
    g_rgvertMirror[0].vectPosition = D3DVECTOR(-1.5f, -4.5f, 5.0f);
    g_rgvertMirror[0].u0 = g_rgvertMirror[0].u1 = 0.0f;
    g_rgvertMirror[0].v0 = g_rgvertMirror[0].v1 = 1.0f;

    g_rgvertMirror[1].vectPosition = D3DVECTOR(-1.5f, -3.7f, 4.925f);
    g_rgvertMirror[1].u0 = g_rgvertMirror[1].u1 = 0.0f;
    g_rgvertMirror[1].v0 = g_rgvertMirror[1].v1 = 0.0f;

    g_rgvertMirror[2].vectPosition = D3DVECTOR( 1.5f, -3.7f, 4.925f);
    g_rgvertMirror[2].u0 = g_rgvertMirror[2].u1 = 1.0f;
    g_rgvertMirror[2].v0 = g_rgvertMirror[2].v1 = 0.0f;

    g_rgvertMirror[3].vectPosition = D3DVECTOR( 1.5f, -4.5f, 5.0f);
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
    int       i;   

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

    // Load the trench texture
    g_ptexTrench = LoadTexture(TEXT("Trench"));
    if (!g_ptexTrench)
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
    g_ptexMirror = CreateTargetTexture(512, 512);
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
    CreateCube();
    CreateTrench();
    CreateMirror();

    // Create materials to color the cubes
    g_pmatCube[0] = CreateMaterial(1.0f, 0.0f, 0.0f, 1.0f, 20.0f, 0.5f, 0.0f, 0.0f, 0.75f, 0.0f, 0.0f);
    g_pmatCube[1] = CreateMaterial(0.0f, 1.0f, 0.0f, 1.0f, 20.0f, 0.0f, 0.5f, 0.0f, 0.0f, 0.75f, 0.0f);
    g_pmatCube[2] = CreateMaterial(0.0f, 0.0f, 1.0f, 1.0f, 20.0f, 0.0f, 0.0f, 0.5f, 0.0f, 0.0f, 0.75f);
    g_pmatCube[3] = CreateMaterial(1.0f, 1.0f, 0.0f, 1.0f, 20.0f, 0.5f, 5.0f, 0.0f, 0.75f, 0.75f, 0.0f);
    g_pmatCube[4] = CreateMaterial(1.0f, 0.0f, 1.0f, 1.0f, 20.0f, 0.5f, 0.0f, 0.5f, 0.75f, 0.0f, 0.75f);

    // Get the material handles
    for (i = 0; i < 5; i++) 
    {
        g_errLast = g_pmatCube[i]->GetHandle(g_p3ddevice, &g_hmatCube[i]);
        if (CheckError(TEXT("Get cube material handle")))
            return FALSE;
    }

    // Add a white light
    AddLight(1.0f, 1.0f, 1.0f, -0.5f, -1.0f, -1.0f);

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
