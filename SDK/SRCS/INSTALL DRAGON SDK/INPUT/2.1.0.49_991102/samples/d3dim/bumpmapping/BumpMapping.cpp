/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999 Microsoft Corporation

Module Name:

    bumpmapping.cpp

Abstract:

    Bump Application

-------------------------------------------------------------------*/

// ++++ Include Files +++++++++++++++++++++++++++++++++++++++++++++++
#include "bumpmapping.hpp"

// ++++ Global Variables ++++++++++++++++++++++++++++++++++++++++++++
HWND      g_hwndApp;                                // HWND of the application
HINSTANCE g_hinst;                                  // HINSTANCE of the application
float	g_phase = 0.f;

// ++++ Local Variables +++++++++++++++++++++++++++++++++++++++++++++
TCHAR     g_tszAppName[] = TEXT("bumpmapping");   // The App's Name

D3DVERTEX *g_pvertSphere;                           // List of strip vertices
WORD      *g_pIndices;                              // List of strip indices
unsigned int g_puiSphereOrigin = NULL;              // Pointer to actual (possibly unaligned) alloc address.
int       g_nSphereVerts, g_nIndices;               // Number of strip indices and vertices
int       g_nPolys;                                 // Number of polygons per strip
#if 0
int       g_nStripWidth  = 8;                      // Dimensions of sphere
int       g_nStripHeight = 2;                      // Dimensions of sphere
#else
int       g_nStripWidth  = 30;                      // Dimensions of sphere
int       g_nStripHeight = 30;                      // Dimensions of sphere
#endif

LPDIRECT3DTEXTURE2 g_pd3dtex1;                       // The conventional texture
LPDIRECT3DTEXTURE2 g_pd3dtex2;                       // The conventional texture
LPDIRECT3DTEXTURE2 g_pd3dtexBump;                   // The bumpmapping map to overlay

D3DMATRIX           g_matWorld1   (1.0f, 0.0f, 0.0f, 0.0f,
                                  0.0f, 1.0f, 0.0f, 0.0f,
                                  0.0f, 0.0f, 1.0f, 0.0f,
                                  0.6f, 0.0f, 0.0f, 1.0f);
D3DMATRIX           g_matWorld2   (1.0f, 0.0f, 0.0f, 0.0f,
                                  0.0f, 1.0f, 0.0f, 0.0f,
                                  0.0f, 0.0f, 1.0f, 0.0f,
                                  -0.6f, 0.0f, 0.0f, 1.0f);




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

    g_phase += 3.14159f/100.f;
    D3DVECTOR light;

    // light in diagonal loop - also going behind plane
    light.x = (float)(cos(g_phase)/sqrt(2.f));
    light.y = light.x;
    light.z = (float)sin(g_phase);


    g_p3ddevice->SetLightState(D3DLIGHTSTATE_BUMPDIRECTION, (unsigned long)&light);

    g_p3ddevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE, TRUE );
    g_p3ddevice->SetRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_ONE );
    g_p3ddevice->SetRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_ZERO );

   // g_p3ddevice->SetRenderState(D3DRENDERSTATE_SPECULARENABLE, TRUE );

	// Set up the states to render an opaque bumpmapping-mapped object
    g_p3ddevice->SetTexture(0, g_pd3dtexBump);
    g_p3ddevice->SetTextureStageState(0, D3DTSS_TEXCOORDINDEX, 0);
    g_p3ddevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_BLENDTEXTUREALPHA);
    g_p3ddevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
    g_p3ddevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
    g_p3ddevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG2);
    g_p3ddevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
    g_p3ddevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

    g_p3ddevice->SetTexture(1, g_pd3dtex1);
    g_p3ddevice->SetTextureStageState(1, D3DTSS_TEXCOORDINDEX, 0);

    g_p3ddevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_MODULATE);
    g_p3ddevice->SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_TEXTURE);
    g_p3ddevice->SetTextureStageState(1, D3DTSS_COLORARG2, D3DTA_CURRENT);
    g_p3ddevice->SetTextureStageState(1, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
    g_p3ddevice->SetTextureStageState(1, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
    g_p3ddevice->SetTextureStageState(1, D3DTSS_ALPHAARG2, D3DTA_CURRENT);


    g_p3ddevice->SetTextureStageState(2, D3DTSS_COLOROP, D3DTOP_DISABLE);
    g_p3ddevice->SetTextureStageState(2, D3DTSS_ALPHAOP, D3DTOP_DISABLE);


    g_p3ddevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE, FALSE );


    g_errLast = g_p3ddevice->SetTransform(D3DTRANSFORMSTATE_WORLD, &g_matWorld1);
    if (CheckError(TEXT("Set World Matrix")))
        return FALSE;


    // Draw the sphere
    g_p3ddevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, D3DFVF_VERTEX,
                                      (LPVOID) g_pvertSphere, g_nSphereVerts, g_pIndices, g_nIndices,
                                      D3DDP_DONOTUPDATEEXTENTS | D3DDP_DONOTCLIP);

    g_p3ddevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE, TRUE );
    g_p3ddevice->SetRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_SRCALPHA );
    g_p3ddevice->SetRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_INVSRCALPHA );
    g_p3ddevice->SetTexture(1, g_pd3dtex2);

    g_errLast = g_p3ddevice->SetTransform(D3DTRANSFORMSTATE_WORLD, &g_matWorld2);
    if (CheckError(TEXT("Set World Matrix")))
        return FALSE;


    // Draw the sphere
    g_p3ddevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, D3DFVF_VERTEX,
                                      (LPVOID) g_pvertSphere, g_nSphereVerts, g_pIndices, g_nIndices,
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
    g_puiSphereOrigin = (unsigned int)malloc((g_nSphereVerts + 1)* sizeof(D3DVERTEX));
    g_pvertSphere = (LPD3DVERTEX)(((unsigned int)(g_puiSphereOrigin + 31 ) & ~31));

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
            float rYP = rY * 1.0f * PI;
            pVert->x  = (float)(sin(rXP) * sin(rYP));
            pVert->y  = (float)(cos(rYP));
            pVert->z  = -(float)(cos(rXP) * sin(rYP));
            // Not prelit; use normals
            pVert->nx = pVert->x;
            pVert->ny = pVert->y;
            pVert->nz = pVert->z;

            // Normalize the normals of the vertex
            NormalizeVector((D3DVECTOR*)(&pVert->nx));

            pVert->tu = (float)i / (float)(g_nStripWidth)  * 10.0f;
            pVert->tv = (float)j / (float)(g_nStripHeight) * 10.0f;
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

	RETAILMSG(1,(TEXT("AppInit\r\n")));

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

    // Load the two textures that are displayed inside and outside the modifier volume

	RETAILMSG(1,(TEXT("LoadTexture\r\n")));


    g_pd3dtex1 = LoadTexture(TEXT("TextrBmp1"));
    if (!g_pd3dtex1)
        return FALSE;

    g_pd3dtex2 = LoadTexture(TEXT("TextrBmp2"));
    if (!g_pd3dtex2)
        return FALSE;

	RETAILMSG(1,(TEXT("CreateBumpMapTexture\r\n")));

    g_pd3dtexBump = CreateBumpMapTexture();
    if (!g_pd3dtexBump)
        return FALSE;

#ifdef UNDER_CE
    // Set bumpmapping mapping information
    D3DVECTOR vect(0.0f, 0.0f, +1.0f);
    float rIntensity = 0.8f;
//    float rIntensity = 1.f;
    float rAmbient   = 0.f;
    g_p3ddevice->SetLightState(D3DLIGHTSTATE_BUMPINTENSITY, *(unsigned long *)&rIntensity);
    g_p3ddevice->SetLightState(D3DLIGHTSTATE_BUMPAMBIENT,   *(unsigned long *)&rAmbient);
    g_p3ddevice->SetLightState(D3DLIGHTSTATE_BUMPDIRECTION, (unsigned long)&vect);
#endif


    // Initialize the vertices of a sphere
	RETAILMSG(1,(TEXT("InitSphere\r\n")));
    InitSphere();

    // Add a white light
	RETAILMSG(1,(TEXT("AddLight\r\n")));
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
        if (PeekMessage (&msg, NULL, 0, 0, PM_NOREMOVE))
        {
            // There's a message waiting in the queue for us.  Retrieve
            // it and dispatch it, unless it's a WM_QUIT.
            if (!GetMessage (&msg, NULL, 0, 0))
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

#if 0
void CTracker::Randomize(float rX, float rY, float rZ)
{
	// Randomize translation and rotation info
    m_matRotAndTrans = m_matOrientation =  g_matIdent;
    m_matOrientation._41 = rX;
    m_matOrientation._42 = rY;
    m_matOrientation._43 = rZ;

    m_rXRot = (-1.0f + (float)(rand()%100)/50.0f)/4.0f;
    m_rYRot = (-1.0f + (float)(rand()%100)/50.0f)/4.0f;
    m_rZRot = (-1.0f + (float)(rand()%100)/50.0f)/4.0f;

    m_rXTrans = (-1.0f + (float)(rand()%100)/50.0f)/4.0f;
    m_rYTrans = (-1.0f + (float)(rand()%100)/50.0f)/4.0f;
    SetMatrix();
}

void CTracker::SetMatrix()
{
    D3DMATRIX matRotate;

    D3DVECTOR vAxisX(1.0f, 0.0f, 0.0f);
    D3DVECTOR vAxisY(0.0f, 1.0f, 0.0f);
    D3DVECTOR vAxisZ(0.0f, 0.0f, 1.0f);

    SetMatrixAxisRotation(&matRotate, &vAxisX, m_rXRot);
    m_matRotAndTrans = matRotate;
    SetMatrixAxisRotation(&matRotate, &vAxisY, m_rYRot);
    matprod(&m_matRotAndTrans, &m_matRotAndTrans, &matRotate);
    SetMatrixAxisRotation(&matRotate, &vAxisZ, m_rZRot);
    matprod(&m_matRotAndTrans, &m_matRotAndTrans, &matRotate);
}

void CTracker::Move()
{
    matprod(&m_matOrientation, &m_matRotAndTrans, &m_matOrientation);
    g_p3ddevice->SetTransform(D3DTRANSFORMSTATE_WORLD, &m_matOrientation);
}

void
matprod(D3DMATRIX *pmatDest, D3DMATRIX *pmatSource1, D3DMATRIX *pmatSource2)
{
    // TODO: This will eventually use Quadword-moves for better speed
    __asm (
            "fmov.s fr8,  @-r15\n"
            "fmov.s fr9,  @-r15\n"
            "fmov.s fr10, @-r15\n"
            "fmov.s fr11, @-r15\n"
            "fmov.s fr12, @-r15\n"
            "fmov.s fr13, @-r15\n"
            "fmov.s fr14, @-r15\n"
            "fmov.s fr15, @-r15\n"

           "fmov.s @r6+, fr0\n"
           "fmov.s @r6+, fr1\n"
           "fmov.s @r6+, fr2\n"
           "fmov.s @r6+, fr3\n"
           "fmov.s @r6+, fr4\n"
           "fmov.s @r6+, fr5\n"
           "fmov.s @r6+, fr6\n"
           "fmov.s @r6+, fr7\n"
           "fmov.s @r6+, fr8\n"
           "fmov.s @r6+, fr9\n"
           "fmov.s @r6+, fr10\n"
           "fmov.s @r6+, fr11\n"
           "fmov.s @r6+, fr12\n"
           "fmov.s @r6+, fr13\n"
           "fmov.s @r6+, fr14\n"
           "fmov.s @r6+, fr15\n"


            "; Swap the floating point bank register bit so that we're writing into the other set of FP registers.\n"
            "frchg\n"

            "; Now move the second matrix into the floating point registers\n"
            "fmov.s @r5+, fr0\n"
            "fmov.s @r5+, fr1\n"
            "fmov.s @r5+, fr2\n"
            "fmov.s @r5+, fr3\n"
            "fmov.s @r5+, fr4\n"
            "fmov.s @r5+, fr5\n"
            "fmov.s @r5+, fr6\n"
            "fmov.s @r5+, fr7\n"
            "fmov.s @r5+, fr8\n"
            "fmov.s @r5+, fr9\n"
            "fmov.s @r5+, fr10\n"
            "fmov.s @r5+, fr11\n"
            "fmov.s @r5+, fr12\n"
            "fmov.s @r5+, fr13\n"
            "fmov.s @r5+, fr14\n"
            "fmov.s @r5,  fr15\n"

	        "; Do the actual vector multiplications\n"
	        "ftrv xmtrx, fv0\n"
	        "ftrv xmtrx, fv4\n"
	        "ftrv xmtrx, fv8\n"
	        "ftrv xmtrx, fv12\n"

	        "; Finally copy the results out to the destination matrix.\n"

	        "; Pre-increment the destination address so we can pre-decrement r4 inline\n"
	        "add #60, r4\n"

            "fmov.s fr15, @r4\n"
            "fmov.s fr14, @-r4\n"
            "fmov.s fr13, @-r4\n"
            "fmov.s fr12, @-r4\n"
            "fmov.s fr11, @-r4\n"
            "fmov.s fr10, @-r4\n"
            "fmov.s fr9, @-r4\n"
            "fmov.s fr8, @-r4\n"
            "fmov.s fr7, @-r4\n"
            "fmov.s fr6, @-r4\n"
            "fmov.s fr5, @-r4\n"
            "fmov.s fr4, @-r4\n"
            "fmov.s fr3, @-r4\n"
            "fmov.s fr2, @-r4\n"
            "fmov.s fr1, @-r4\n"
            "fmov.s fr0, @-r4\n"

            "; Swap the floating point bank register bit back to it's original value.\n"
            "frchg   ; todo - move to after the 'rts' to avoid pipeline stall\n"

            "fmov.s @r15+, fr15\n"
            "fmov.s @r15+, fr14\n"
            "fmov.s @r15+, fr13\n"
            "fmov.s @r15+, fr12\n"
            "fmov.s @r15+, fr11\n"
            "fmov.s @r15+, fr10\n"
            "fmov.s @r15+, fr9\n"
            "fmov.s @r15+, fr8\n"


           ,pmatDest, pmatSource1, pmatSource2);

}
#endif