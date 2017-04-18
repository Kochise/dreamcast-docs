/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1998 Microsoft Corporation

Module Name:

    Optimal.cpp

Abstract:

    This sample demonstrates how to maximum polygon throughput on
    Dreamcast using the Dreamcast sdk.  It creates a set of spheres, each of 
    which is a single triangle strip, and rotates them on screen.  Each sphere
    uses a separate vertex pool, and the world matrix is changed between
    each sphere.  Each sphere is also lit by a single directional light
    source.  These demonstrate that the sample does basically the
    same thing as a game, and doesn't "cheat".

    There are several command line parameters created to allow testing
    other, less-optimal cases, such as using Triangle Lists or non-indexed
    strips.  Run 'Optimal -?' to see these command line params

    Note that although the vertex pools are unique to each strip, a
    single index list is used for all of the strips.  This has no effect
    on performance, and is simply done for clarity of the sample.

-------------------------------------------------------------------*/

// ++++ Include Files +++++++++++++++++++++++++++++++++++++++++++++++
#include "Optimal.hpp"

// ++++ Global Variables ++++++++++++++++++++++++++++++++++++++++++++
HWND      g_hwndApp;                                 // HWND of the application
HINSTANCE g_hinst;                                   // HINSTANCE of the application

// ++++ Local Variables +++++++++++++++++++++++++++++++++++++++++++++
TCHAR     g_tszAppName[] = TEXT("Optimal");          // The App's Name
D3DVERTEX **g_ppVerts;                               // List of strip vertices
D3DVERTEX **g_ppVerts2;                              // List of strip vertices (Used for DrawPrimitive)
WORD      *g_pIndices;                               // List of strip indices
int       g_nVerts, g_nIndices;                      // Number of strip indices and vertices
int       g_nPolys;                                  // Number of polygons per strip
LPDIRECT3DTEXTURE2 g_pTexture[10];                   // Pointer to the strip's texture
D3DTEXTUREHANDLE   g_hTexture[10];                   // Handle of the strip's texture


BOOL g_fIndexedPrims = false;    // Set to FALSE to use DrawPrimitive, TRUE for DrawIndexedPrimitive
BOOL g_fTriStrips    = true;     // Set to FALSE to use TriLists, TRUE for TriStrips
BOOL g_fPreLit       = false;    // Set to FALSE to use D3DVERTEX, TRUE for D3DLVERTEX
int  g_nUserLights   = 1;        // 0 == Prelit.
int  g_nEndFrame     = -1;       // -1 == 'infinite' (ie no end)
int  g_nOutputFrame  = 300;      // Output info every 300 frames.
BOOL g_fDone         = false;
BOOL g_fTextureMap   = true;     // TRUE == user texture mapping.

// These are the number of quads that appear in eachdimension; ie a width of 16 means
// that there are 32 tris in that dimension.
// Also: StripWidth and height MUST be evenly divisible by two!
int  g_nStripWidth   = 20;
int  g_nStripHeight  = 20;
int  g_nStrips       = 20;

static int g_cFramesDrawn = 0;

// ++++ Local Functions +++++++++++++++++++++++++++++++++++++++++++++
static BOOL RenderSceneToBackBuffer();
static BOOL AppInit(HINSTANCE hPrev,int nCmdShow);
static BOOL ParseCommandLine(LPTSTR lpCmdLine);
static void DumpInfo();

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
    if (g_nLights > 0)
    {
        for (int i = 0; i < g_nLights; i++)
            g_rglight[i]->Release();
    }

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

    // Deallocate the strip movement tracker
    if (g_ptrackerStrip)
        delete g_ptrackerStrip;
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
        g_fDone = true;
        DumpInfo();

        // Cleanup DirectX structures
        CleanUp();

        PostQuitMessage(0);
        return 0L;

    } // switch (message)

    return DefWindowProc (hWnd, uMessage, wParam, lParam);
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    CreateStrip

Description:

    Initializes the vertices and indices of the strip that will be
    drawn to the screen.

Arguments:

    None.

Return Value:

    None.

-------------------------------------------------------------------*/
void
CreateStrip()
{
    int i, j, iCurStrip, iCurIndex;

    // Allocate space for the list of strips
    g_ppVerts = new D3DVERTEX*[g_nStrips];

    // Seed the random number initializer with a known value for consistent results
    srand(0);

    for (iCurStrip = 0; iCurStrip < g_nStrips; iCurStrip++)
    {
        // Create the strip vertices.
        g_nVerts = (g_nStripWidth + 1) * (g_nStripHeight + 1);

#ifdef ALIGN_ALLOCS
        unsigned int puiTemp = (unsigned int)malloc((g_nVerts + 1)* sizeof(D3DVERTEX));
        g_ppVerts[iCurStrip] = (LPD3DVERTEX)(((unsigned int)(puiTemp + 31 ) & ~31));
#else
        g_ppVerts[iCurStrip] = new D3DVERTEX[g_nVerts];
#endif

        D3DVERTEX *pVertList = g_ppVerts[iCurStrip];
        float rXOffset, rYOffset, rZOffset;

        // We want to offset each strip to use maximum screen real estate
        rXOffset = -4.0f + (float)(rand()%100)/12.5f;
        rYOffset = -4.0f + (float)(rand()%100)/12.5f;
        rZOffset = -1.0f + (float)(rand()%100)/50.0f;

        // Set the movement tracker for this strip.
        g_ptrackerStrip[iCurStrip].Randomize(rXOffset, rYOffset, rZOffset);

        // Create the strip.
        for (j = 0; j <= g_nStripHeight; j++)
            {
            for (i = 0; i <= g_nStripWidth; i++)
            {
                int nVert = j * (g_nStripWidth + 1) + i;
                D3DVERTEX *pVert = &pVertList[nVert];

                float rX  = (float)i / (float)(g_nStripWidth);
                float rY  = (float)j / (float)(g_nStripHeight);
                float rXP = rX * 2.0f * PI;
                float rYP = rY * 2.0f * PI;

                pVert->x  = (float)(sin(rXP) * sin(rYP));
                pVert->y  = (float)(cos(rYP));
                pVert->z  = (float)(cos(rXP) * sin(rYP));

                if (g_fPreLit)
                {
                    // Prelit vertices - For now, we'll just drop a color in there.  Eventually
                    // this could be rewritten to fake a light source if so desired.
                    D3DLVERTEX *plvert = (D3DLVERTEX*)pVert;
                    plvert->color = 0xFF00FF00;     // Green
                    plvert->specular = 0x00000000;
                }
                else
                {
                    // Not prelit; use normals
                    pVert->nx = pVert->x;
                    pVert->ny = pVert->y;
                    pVert->nz = pVert->z;
                    // Normalize the normals of the vertex
                    NormalizeVector((D3DVECTOR*)(&pVert->nx));
                }

                pVert->tu = (float)i / (float)(g_nStripWidth) * 4.0f;
                pVert->tv = (float)j / (float)(g_nStripHeight) * 4.0f;

            }
        }
    }

    // Create the strip indices.  These are reused for all strips.
    int iIndex = 0;

    if (g_fTriStrips)
    {
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
    else
    {
        // Triangle lists
        g_nIndices = g_nStripWidth * g_nStripHeight * 6;

        g_pIndices = new WORD[g_nIndices];

        for (j = 0; j < g_nStripHeight; j++)
        {
            for (i = 0; i < g_nStripWidth; i++)
            {
                g_pIndices[iIndex++] =  i      + (j + 1) * g_nStripWidth;
                g_pIndices[iIndex++] =  i      +  j      * g_nStripWidth;
                g_pIndices[iIndex++] = (i + 1) + (j + 1) * g_nStripWidth;

                g_pIndices[iIndex++] =  i      +  j      * g_nStripWidth;
                g_pIndices[iIndex++] = (i + 1) +  j      * g_nStripWidth;
                g_pIndices[iIndex++] = (i + 1) + (j + 1) * g_nStripWidth;
            }
        }
        g_nPolys = g_nStripWidth * g_nStripHeight * 2;
    }

    // If the user wants non-indexed prims, then create the lists from the generated vertices above
    if (!g_fIndexedPrims)
    {
        g_nVerts = g_nIndices;

#ifdef ALIGN_ALLOCS
        g_ppVerts2 = (LPD3DVERTEX*) malloc(sizeof(LPD3DVERTEX) * (g_nVerts + 1));

        // TODO : When freeing, need to free UNALIGNED address!!!!
        g_ppVerts2 = (LPD3DVERTEX*)(((unsigned int)((unsigned int*)g_ppVerts2 + 31 ) & ~31));
#else
        g_ppVerts2 = new D3DVERTEX*[g_nVerts];
#endif

        for (iCurStrip = 0; iCurStrip < g_nStrips; iCurStrip++)
        {
#ifdef ALIGN_ALLOCS
            unsigned int puiTemp = (unsigned int)malloc((g_nVerts + 1)* sizeof(D3DVERTEX));
            g_ppVerts2[iCurStrip] = (LPD3DVERTEX)(((unsigned int)(puiTemp + 31 ) & ~31));
#else
            g_ppVerts2[iCurStrip] = new D3DVERTEX[g_nVerts];
#endif
            for (iCurIndex = 0; iCurIndex < g_nIndices; iCurIndex++)
            {
                g_ppVerts2[iCurStrip][iCurIndex] = g_ppVerts[iCurStrip][g_pIndices[iCurIndex]];
            }
        }
    }
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
    D3DMATRIX matTemp;

    // Clear the back buffer.
    g_errLast = g_pviewport->Clear(1, &s_d3drect, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER);
    if (CheckError(TEXT("Clear Back Buffer")))
        return FALSE;

    // Begin the scene
    g_errLast = g_p3ddevice->BeginScene();
    if (CheckError(TEXT("Begin Scene")))
        return FALSE;

    g_p3ddevice->GetTransform(D3DTRANSFORMSTATE_WORLD, &matTemp);

    // Set the strip texture
    if (g_fTextureMap)
        g_p3ddevice->SetRenderState(D3DRENDERSTATE_TEXTUREHANDLE, g_hTexture[0]);

    // Render the Strip(s).
    for (int i = 0; i < g_nStrips; i++)
    {
        // Move the strip
        g_ptrackerStrip[i].Move();

        // Draw the strip
        if (g_fIndexedPrims)
        {
            if (g_fTriStrips)
            {
                // Triangle strips, indexed primitive

                // NOTE: It would reduce cache-misses if we reused the source vertices each time, but
                // for better realism, we'll use redundant sets of vertices for each sphere.
                if (g_fPreLit)
                    g_p3ddevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, D3DVT_LVERTEX,
                                                      (LPVOID) g_ppVerts[i], g_nVerts, g_pIndices, g_nIndices,
                                                      D3DDP_DONOTUPDATEEXTENTS | D3DDP_DONOTCLIP);
                else
                    g_p3ddevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, D3DVT_VERTEX,
                                                      (LPVOID) g_ppVerts[i], g_nVerts, g_pIndices, g_nIndices,
                                                      D3DDP_DONOTUPDATEEXTENTS | D3DDP_DONOTCLIP);
            }
            else
            {
                // Triangle lists, indexed primitive
                if (g_fPreLit)
                    g_p3ddevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, D3DVT_LVERTEX,
                                                      (LPVOID) g_ppVerts[i], g_nVerts, g_pIndices, g_nIndices,
                                                      D3DDP_DONOTUPDATEEXTENTS | D3DDP_DONOTCLIP);
                else
                    g_p3ddevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, D3DVT_VERTEX,
                                                      (LPVOID) g_ppVerts[i], g_nVerts, g_pIndices, g_nIndices,
                                                      D3DDP_DONOTUPDATEEXTENTS | D3DDP_DONOTCLIP);
            }
        }
        else
        {
            if (g_fTriStrips)
            {
                // Triangle strips, nonindexed primitive
                if (g_fPreLit)
                    g_p3ddevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, D3DVT_LVERTEX,
                                               (LPVOID) g_ppVerts2[i], g_nVerts,
                                               D3DDP_DONOTUPDATEEXTENTS | D3DDP_DONOTCLIP);
                else
                    g_p3ddevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, D3DVT_VERTEX,
                                               (LPVOID) g_ppVerts2[i], g_nVerts,
                                               D3DDP_DONOTUPDATEEXTENTS | D3DDP_DONOTCLIP);
            }
            else
            {
                // Triangle lists, nonindexed primitves
                if (g_fPreLit)
                    g_p3ddevice->DrawPrimitive(D3DPT_TRIANGLELIST, D3DVT_LVERTEX,
                                               (LPVOID) g_ppVerts2[i], g_nVerts,
                                               D3DDP_DONOTUPDATEEXTENTS | D3DDP_DONOTCLIP);
                else
                    g_p3ddevice->DrawPrimitive(D3DPT_TRIANGLELIST, D3DVT_VERTEX,
                                               (LPVOID) g_ppVerts2[i], g_nVerts,
                                               D3DDP_DONOTUPDATEEXTENTS | D3DDP_DONOTCLIP);
            }
        }
    }
    g_p3ddevice->SetTransform(D3DTRANSFORMSTATE_WORLD, &matTemp);

    // Increment frame counter
    g_cFramesDrawn++;

    // Output framerate info to the console
    DumpInfo();

    // End the scene
    g_errLast = g_p3ddevice->EndScene();
    if (CheckError(TEXT("EndScene")))
        return FALSE;

    return TRUE;
}

void
DumpInfo()
{
    static DWORD s_dwTimeLast  = GetTickCount();
    static DWORD s_dwTimeFirst = GetTickCount();
    static DWORD s_dwTimeExclude = 0;

    TCHAR tszBuf[256];

    // Output polycount info only on the first time
    if (g_cFramesDrawn == 1)
    {
        DWORD dwTime = GetTickCount();

        // Output the type of primitive and the primitive instruction used.
        wsprintf(tszBuf, TEXT("Drawing "));
        if (g_fPreLit)
            _tcscat(tszBuf, TEXT("Prelit "));
        else
            _tcscat(tszBuf, TEXT("Unlit "));

        if (g_fTriStrips)
            _tcscat(tszBuf, TEXT("Triangle Strips "));
        else
            _tcscat(tszBuf, TEXT("Triangle Lists "));

        if (g_fIndexedPrims)
            _tcscat(tszBuf, TEXT("using 'DrawIndexedPrimitive'.\r\n"));
        else
            _tcscat(tszBuf, TEXT("using 'DrawPrimitive'.\r\n"));

        OutputDebugString(tszBuf);

        wsprintf(tszBuf, TEXT("Totals: NumStrips: %d, Indices: %d  Vertices: %d  Polygons: %d\r\n"), g_nStrips,
                 g_nIndices * g_nStrips, g_nVerts * g_nStrips, g_nPolys * g_nStrips);

        OutputDebugString(tszBuf);
        s_dwTimeExclude += GetTickCount() - dwTime;
    }

    // Output framerate info every 'g_nOutputFrame' frames
    if (g_fDone || ((g_cFramesDrawn % g_nOutputFrame) == 0) && g_nOutputFrame != -1)
    {
        DWORD dwTime              = GetTickCount();
        DWORD dwTimeSinceStart    = dwTime - s_dwTimeFirst - s_dwTimeExclude;
        DWORD dwTimeSincePrevious = dwTime - s_dwTimeLast;

        // Output fps info
        wsprintf(tszBuf, TEXT("Total Frames Drawn: %d   Time: %d.%03ds   fps: %d  #Polys:%d   p/s:%d\r\n"),
                         g_cFramesDrawn,
                         dwTimeSinceStart/1000, dwTimeSinceStart%1000,
                         (g_cFramesDrawn * 1000) / dwTimeSinceStart,
                         g_nPolys * g_nStrips,
                         (int) ( ((float)g_nPolys * (float)g_nStrips * (float)g_cFramesDrawn * 1000.f) / (float)dwTimeSinceStart) );
        OutputDebugString(tszBuf);

        if (!g_fDone)
        {
            wsprintf(tszBuf, TEXT("     Last %d frames: Time: %d.%03ds   fps: %d  p/s:%d\r\n"),
                             g_nOutputFrame,
                             dwTimeSincePrevious/1000, dwTimeSincePrevious%1000, (g_nOutputFrame * 1000) / dwTimeSincePrevious,
                         (int) ( ((float)g_nPolys * (float)g_nStrips * (float)g_nOutputFrame * 1000.f) / (float)dwTimeSincePrevious) );
            OutputDebugString(tszBuf);
        }

        s_dwTimeLast = GetTickCount();
        s_dwTimeExclude += s_dwTimeLast - dwTime;
    }
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

    if (g_nEndFrame != -1 && g_cFramesDrawn >= g_nEndFrame)
    {
        // Last frame drawn!
        g_fDone = true;
        DumpInfo();
    }
}

//******************************************************************************
//
// Function:
//
//     SetDisplayValue
//
// Description:
//
//     Set the given registry key using the given value.
//
// Arguments:
//
//     LPCWSTR szName           - Name of the registry key to set
//
//     DWORD dwValue            - Value to set the key with
//
//     LPDWORD pdwOldValue      - Contains the old value of the registry key
//                                on return
//
// Return Value:
//
//     true on success, false on failure.
//
//******************************************************************************
bool SetDisplayValue(LPCWSTR szName, DWORD dwValue, LPDWORD pdwOldValue) {

    HKEY  hKey;
    DWORD dwType;
    DWORD dwSize;
    bool  bRet = false;

    if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, L"DisplaySettings", 0, 0, &hKey)
                                                        == ERROR_SUCCESS)
    {
        if (pdwOldValue) {
            DWORD dwOldValue;
            dwSize = sizeof(DWORD);
            if (RegQueryValueEx(hKey, szName, NULL, &dwType,
                                (LPBYTE)&dwOldValue, &dwSize) == ERROR_SUCCESS)
            {
                *pdwOldValue = dwOldValue;
            }
        }

        if (RegSetValueEx(hKey, szName, 0, REG_DWORD, (LPBYTE)&dwValue,
                            sizeof(DWORD)) == ERROR_SUCCESS)
        {
            bRet = true;
        }

        RegCloseKey(hKey);
    }

    return bRet;
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

    g_hwndApp = CreateWindowEx (0, g_tszAppName, g_tszAppName, WS_VISIBLE,
                                0, 0, 640, 480, NULL, NULL, g_hinst, NULL);

#define VERTEX_BUFFER_SIZE 0x001E0000
#define POLYGON_BUFFER_SIZE 0x0030000
    DWORD dwVertexBufferSize;
    DWORD dwPolygonBufferSize;
        SetDisplayValue(L"CommandVertexBufferSize", VERTEX_BUFFER_SIZE,
                        &dwVertexBufferSize);
        SetDisplayValue(L"CommandPolygonBufferSize", POLYGON_BUFFER_SIZE,
                        &dwPolygonBufferSize);

    // Initialize DirectDraw
    if (!InitDirectDraw())
        return FALSE;

    // Initializes the Direct3D object, viewport, and sets the rendering state.
    if (!InitDirect3D())
        return FALSE;

    // Allocate the strip movement tracker
    g_ptrackerStrip = new CTracker[g_nStrips];

    // Initialize the Strip's vertices and indices.
    CreateStrip();

    // Load the texture for the Strip.
    g_pTexture[0] = LoadTexture(TEXT("TEXTURE0"));
    g_pTexture[0]->GetHandle(g_p3ddevice, &g_hTexture[0]);

    return TRUE;
}

int
GetNumber(TCHAR **ppCmdLine)
{
    int nValue = 0;
    int nNeg = 1;

    while (**ppCmdLine == TEXT(' ') && **ppCmdLine)
        (*ppCmdLine)++;

    if (**ppCmdLine == TEXT('-'))
    {
        nNeg = -1;
        (*ppCmdLine)++;
    }

    while (**ppCmdLine >= TEXT('0') && **ppCmdLine <= TEXT('9') && *ppCmdLine)
    {
        nValue = nValue * 10 + (**ppCmdLine - '0');
        (*ppCmdLine)++;
    }

    return nValue * nNeg;
}

void
DumpUsageInfo()
{
    RetailOutput(TEXT("\r\nOptimal performance application.\r\n"));
    RetailOutput(TEXT("Usage: Optimal [options]\r\n\r\n"));
    RetailOutput(TEXT("-?               This output\r\n"));
    RetailOutput(TEXT("-notex           Disable texture mapping  (default = texture mapping ON)\r\n"));
    RetailOutput(TEXT("-dip             Use DrawIndexedPrimitive (default = use DrawPrimitive)\r\n"));
    RetailOutput(TEXT("-list            use Triangle Lists       (default = use Triangle Strips)\r\n"));
    RetailOutput(TEXT("-light #         Number of lights to display.  Must be 0, 1, 2, or 3.\r\n"));
    RetailOutput(TEXT("                     Use '0' to use PreLit vertices  (default = 1)\r\n"));
    RetailOutput(TEXT("-frames #        Number of frames to run before exiting.\r\n"));
    RetailOutput(TEXT("                     Use '-1' for Infinite run (default == -1)\r\n"));
    RetailOutput(TEXT("-output #        Number of frames to run between outputting information\r\n"));
    RetailOutput(TEXT("                     use '-1' for no during-run output (default = -1)\r\n"));
    RetailOutput(TEXT("-stripsize # #   Specify size of strip (Width, Height).  Numbers must be\r\n"));
    RetailOutput(TEXT("                     divisible by two! technically, this is the number of \r\n"));
    RetailOutput(TEXT("                     vertices in each dimension.  The number of polygons\r\n"));
    RetailOutput(TEXT("                     displayed will be roughly (2 * Width * Height), since\r\n"));
    RetailOutput(TEXT("                     each 'square' in the strip is 2 polygons (the number \r\n"));
    RetailOutput(TEXT("                     of polygons is 'roughly' that because there are also \r\n"));
    RetailOutput(TEXT("                     extra polygons at the end of each row to allow us to \r\n"));
    RetailOutput(TEXT("                     use a single strip for each sphere.  Look at the output \r\n"));
    RetailOutput(TEXT("                     of the program for the exact number of polygons displayed).\r\n"));
    RetailOutput(TEXT("                     (Default; width = 20, height = 20)\r\n"));
    RetailOutput(TEXT("-stripnum #      Number of strips to display (default = 20)\r\n\r\n"));
}

TCHAR *
GetNextCommand(TCHAR **ppCmdLine)
{
    TCHAR *ptsz = *ppCmdLine;

    // Skip command (ie go until whitespace is hit)
    while (**ppCmdLine != TEXT(' ') && **ppCmdLine)
        (*ppCmdLine)++;

    return ptsz;
}

BOOL
ParseCommandLine(LPTSTR lpCmdLine)
{
    TCHAR tszBuf[256];
    TCHAR *ptszCommand;

    while ((lpCmdLine[0] == TEXT('-')) || (lpCmdLine[0] == TEXT('/')))
    {
        lpCmdLine++;

        ptszCommand = GetNextCommand(&lpCmdLine);

        if (!_tcsnicmp(ptszCommand, TEXT("?"), 1))
        {
            // Dump Usage info
            DumpUsageInfo();
            return false;
        }
        else if (!_tcsnicmp(ptszCommand, TEXT("dip"), 3))
        {
            // User wants to use DrawIndexedPrimitive
            g_fIndexedPrims = true;
        }
        else if (!_tcsnicmp(ptszCommand, TEXT("light"), 5))
        {
            // User wants to specify the number of lights to use
            // Get the number
            g_nUserLights = GetNumber(&lpCmdLine);
            if (g_nUserLights == 0)
                g_fPreLit = true;
            if (g_nUserLights > 3)
            {
                // Invalid number of lights!
                wsprintf(tszBuf, TEXT("\r\nERROR: Invalid number of lights! Must be between 0, 1, 2, or 3.\r\nRun 'Optimal -?' for usage info.\r\n"));
                OutputDebugString(tszBuf);
                return false;
            }
        }
        else if (!_tcsnicmp(ptszCommand, TEXT("list"), 4))
        {
            // User wants to use Triangle lists instead of Triangle Strips
            g_fTriStrips = false;

        }
        else if (!_tcsnicmp(ptszCommand, TEXT("Frames"), 6))
        {
            // User wants to specify the number of frames to run before ending.
            g_nEndFrame = GetNumber(&lpCmdLine);
        }
        else if (!_tcsnicmp(ptszCommand, TEXT("Output"), 6))
        {
            // User wants to specify the number of frames to run between info output
            g_nOutputFrame = GetNumber(&lpCmdLine);
        }
        else if (!_tcsnicmp(ptszCommand, TEXT("stripsize"), 9))
        {
            // User wants to specify the strip size
            g_nStripWidth  = GetNumber(&lpCmdLine);
            g_nStripHeight = GetNumber(&lpCmdLine);
            if ((g_nStripWidth%2) || (g_nStripHeight%2))
            {
                // Invalid size
                wsprintf(tszBuf, TEXT("\r\nERROR: Invalid Strip size specified - width and height *must* be divisible by two\r\nRun 'Optimal -?' for usage info.\r\n"));
                OutputDebugString(tszBuf);
                return false;
            }
            if ((g_nStripWidth<4) || (g_nStripHeight<4))
            {
                // Invalid size
                wsprintf(tszBuf, TEXT("\r\nERROR: Invalid Strip size specified - width and height *must* be greater than two\r\nRun 'Optimal -?' for usage info.\r\n"));
                OutputDebugString(tszBuf);
                return false;
            }
        }
        else if (!_tcsnicmp(ptszCommand, TEXT("stripnum"), 8))
        {
            // User wants to specify the number of strips
            g_nStrips      = GetNumber(&lpCmdLine);
        }
        else if (!_tcsnicmp(ptszCommand, TEXT("notex"), 5))
        {
            // User doesn't want textures
            g_fTextureMap = false;
        }
        else
        {
            // Unknown command
            wsprintf(tszBuf, TEXT("\r\nERROR: Invalid Command line param '%s' specified - run 'Optimal -?' for usage info.\r\n"), ptszCommand);
            OutputDebugString(tszBuf);
            return false;
        }

        // Advance to the next command line parameter, or the NULL
        // terminator at the end of the string.
        while (*lpCmdLine == TEXT(' '))
            lpCmdLine++;
    }

    return true;
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

    // Check the command line
    if (!ParseCommandLine(lpCmdLine))
        return 0L;

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
            UpdateFrame();
            if (g_fDone)
            {
                // Not the correct exit strategy - should send a message to the WndProc and let it deal with this...
                CleanUp();
                return 0L;
            }
        }
    }

    RetailOutput(TEXT("\r\nApp exited...\r\n"));
    return msg.wParam;
}
