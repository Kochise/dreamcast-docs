/*==========================================================================
 *
 *  Copyright (C) 1995-1997 Microsoft Corporation. All Rights Reserved.
 *
 *  File:       donut.cpp
 *
 *  This sample takes the ddraw donut sample from the DirectX SDK and
 *  adds an animating text string to it using DirectX Animation.  A
 *  direct draw primary surface is created in this file and passed to
 *  the DAView object for rendering.
 *
 ***************************************************************************/

#define NAME "Donut"
#define TITLE "Donut"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <windowsx.h>
#include <ddrawex.h>
#include "ddutil.h"
#include "dxa.h"

char szBitmap[] = "DONUT";

BOOL            gExclusive = FALSE;
BOOL            bPaused = FALSE;
HWND            hWndMain;

IDirectDrawFactory      *lpDDF;
LPDIRECTDRAW            lpDD;           // DirectDraw object
LPDIRECTDRAWSURFACE     lpDDSPrimary;   // DirectDraw primary surface
LPDIRECTDRAWSURFACE     lpDDSDA;        // Offscreen surface for DA
LPDIRECTDRAWSURFACE     lpDDSDonut;     // Offscreen surface for donut
LPDIRECTDRAWPALETTE     lpDDPal;        // DirectDraw palette
LPDIRECTDRAWCLIPPER     lpClipper;      // Clipper for the primary surface
BOOL                    bActive;        // is application active?
RECT                    windowRect;     // windows' client rectangle

/*
 * releaseSurfaces
 *
 * Release the global surfaces and clipper.
 */
void releaseSurfaces( void )
{
    if( lpDDSPrimary != NULL )
    {
        lpDDSPrimary->Release();
        lpDDSPrimary = NULL;
    }
    if( lpDDSDA != NULL )
    {
        lpDDSDA->Release();
        lpDDSDA = NULL;
    }
    if( lpDDSDonut != NULL )
    {
        lpDDSDonut->Release();
        lpDDSDonut = NULL;
    }
    if( lpClipper != NULL )
    {
        lpClipper->Release();
        lpClipper = NULL;
    }
} 

/*
 * finiObjects
 *
 * Finish with all objects we use; release them
 */
static void finiObjects( void )
{
    if( lpDD != NULL )
    {
        releaseSurfaces();
        if( lpDDPal != NULL )
        {
            lpDDPal->Release();
            lpDDPal = NULL;
        }
        lpDD->Release();
        lpDD = NULL;
    }

    // Clean up the screen on exit
    RedrawWindow( NULL, NULL, NULL, RDW_INVALIDATE | RDW_ERASE |
                     RDW_ALLCHILDREN );

} /* finiObjects */

/*
 * initFail
 *
 * This function is called if the initialization function fails
 */
BOOL initFail( HWND hWnd, LPCTSTR msg )
{
    finiObjects();
    MessageBox( hWnd, msg, TITLE, MB_OK );
    DestroyWindow( hWnd );
    return FALSE;

} /* initFail */

/*
 * createSurfaces
 *
 * Create the front and back buffers.
 */
BOOL createSurfaces( void )
{
    HRESULT             ddrval;
    DDSURFACEDESC       ddsd;
    
    // Create the primary surface
    ddsd.dwSize = sizeof( ddsd );
    ddsd.dwFlags = DDSD_CAPS;
    ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;

    ddrval = lpDD->CreateSurface( &ddsd, &lpDDSPrimary, NULL );
    if( ddrval != DD_OK )
        return false;

    if(!gExclusive)
    {
        //
        // now create a DirectDrawClipper object.
        //
        ddrval = lpDD->CreateClipper(0, &lpClipper, NULL);

        if( ddrval == DD_OK )
        {
            ddrval = lpClipper->SetHWnd(0, hWndMain);

            if( ddrval == DD_OK )
            {
                ddrval = lpDDSPrimary->SetClipper(lpClipper);
            }
        }
        if( ddrval != DD_OK )
            return false;
    }

    //
    // Create a DirectDrawSurface to hand to Direct Animation.
    //
    ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT |DDSD_WIDTH;
    ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;
    ddsd.dwWidth = WINDOW_WIDTH;
    ddsd.dwHeight = WINDOW_HEIGHT;

    ddrval = lpDD->CreateSurface(&ddsd, &lpDDSDA, NULL);
    if (ddrval != DD_OK)
        return false;

    lpDDPal = DDLoadPalette(lpDD, szBitmap);
    if (lpDDPal)
    {
        lpDDSPrimary->SetPalette(lpDDPal);
    }

    lpDDSDonut = DDLoadBitmap(lpDD, szBitmap, 0, 0);
    if( lpDDSDonut == NULL )
    {
        return false;
    }

    // set color key to black
    DDSetColorKey(lpDDSDonut, RGB(0,0,0));
    return true;
} /* createSurfaces */

/*
 * recreateSurfaces
 *
 * The screen resolution or bitdepth has changed, re-create
 * all surfaces.
 */
BOOL recreateSurfaces( void )
{
    releaseSurfaces();

    if (createSurfaces())
    {
        return resetDXASurfaces(lpDDSDA);
    }
    return false;
} /* recreateSurfaces */

/*
 * restoreAll
 *
 * Restore all lost objects
 */
BOOL restoreAll( void )
{
    HRESULT     ddrval;

    ddrval = lpDDSPrimary->Restore();
    if (ddrval == DDERR_WRONGMODE)
    {
        if (recreateSurfaces())
            return true;

    }
    else if (ddrval == DD_OK)
    {
        ddrval = lpDDSDA->Restore();
        if( ddrval == DD_OK )
        {
            ddrval = lpDDSDonut->Restore();
            if( ddrval == DD_OK )
            {
                DDReLoadBitmap(lpDDSDonut, szBitmap);
                return true;
            }
        }
    }

    return initFail(hWndMain, "DirectDraw: Can't Recreate Surfaces");
} /* restoreAll */

/*
 * updateFrame
 * 
 * Decide what needs to be blitted next, wait for flip to complete,
 * then flip the buffers.
 */
void updateFrame( void )
{
    static DWORD        lastTickCount = 0;
    static int          currentFrame = 0;
    static BOOL         haveBackground = FALSE;
    DWORD               thisTickCount;
    DWORD               delay = 17;
    HRESULT             ddrval;

    thisTickCount = GetTickCount();
    if((thisTickCount - lastTickCount) <= delay)
    {
        return;
    }

    thisTickCount = GetTickCount();
    if((thisTickCount - lastTickCount) > delay)
    {
        // Move to next frame;
        lastTickCount = thisTickCount;
        currentFrame++;
        if(currentFrame > 59)
        {
            currentFrame = 0;
        }
    }

    // DA doesn't like lost surface.  We should restore lost surface
    // before asking DA to render.
    if (lpDDSDA && lpDDSDA->IsLost() == DDERR_SURFACELOST)
    {
        // This function will destroy the window if failed.        
        if (!restoreAll())
            return;
    }

    // Ask DA to render to the DA surface the next image/sound for view1.
    tick(view1);

    // The image in the DA model (defined in dxa.cpp) has a background
    // image, so we don't need to clear the background before we draw here.
    RECT  donutSrcRect;
    donutSrcRect.left   = currentFrame%10*64;
    donutSrcRect.top    = currentFrame/10*64;
    donutSrcRect.right  = currentFrame%10*64 + 64;
    donutSrcRect.bottom = currentFrame/10*64 + 64;

    // Blt the donut to the center of the DDSDonut surface.
    RECT donutDestRect;
    donutDestRect.left   = WINDOW_WIDTH/2-32;
    donutDestRect.top    = WINDOW_HEIGHT/2-32;
    donutDestRect.right  = donutDestRect.left + 64;
    donutDestRect.bottom = donutDestRect.top + 64;

    // Blit the donut for the next frame to the DA surface.
    while( 1 )
    {
        ddrval = lpDDSDA->Blt(&donutDestRect, lpDDSDonut,
            &donutSrcRect, DDBLT_WAIT|DDBLT_KEYSRC, NULL);

        if( ddrval == DD_OK )
        {
            break;
        }
        if( ddrval == DDERR_SURFACELOST )
        {
            ddrval = restoreAll();
            if( ddrval != DD_OK )
            {
                return;
            }
        }

        if( ddrval != DDERR_WASSTILLDRAWING )
        {
            return;
        }
    }

    // Ask DA to render to the DA surface the next image/sound for view2.
    tick(view2);

    // Blit from the DA surface to the screen.
    RECT daRect;
    daRect.left = 0;
    daRect.top = 0;
    daRect.right = WINDOW_WIDTH;
    daRect.bottom = WINDOW_HEIGHT;
    RECT screenRect;
    screenRect.left = windowRect.left;
    screenRect.top = windowRect.top;
    screenRect.right = windowRect.left + WINDOW_WIDTH;
    screenRect.bottom = windowRect.top + WINDOW_HEIGHT;
        
    while( 1 )
    {
        ddrval = lpDDSPrimary->Blt(&screenRect, lpDDSDA,
                                   &daRect, DDBLT_WAIT, NULL);

        if( ddrval == DD_OK )
        {
            break;
        }
        if( ddrval == DDERR_SURFACELOST )
        {
            ddrval = restoreAll();
            if( ddrval != DD_OK )
            {
                return;
            }
        }
        if( ddrval != DDERR_WASSTILLDRAWING )
        {
            return;
        }
    }

} /* updateFrame */

long FAR PASCAL WindowProc( HWND hWnd, UINT message, 
                            WPARAM wParam, LPARAM lParam )
{
    switch( message )
    {
    case WM_SIZE:
    case WM_MOVE:
        if (IsIconic(hWnd))
        {
            bPaused = true;
        }

        if (!gExclusive) 
        {
            GetClientRect(hWnd, &windowRect);
            ClientToScreen(hWnd, (LPPOINT)&windowRect);
            ClientToScreen(hWnd, (LPPOINT)&windowRect+1);
        } else {
            SetRect(&windowRect, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
        }
        break;

    case WM_ACTIVATEAPP:
        bActive = wParam && GetForegroundWindow() == hWnd;

        // Unpause when we're no longer iconic.
        if (bPaused && bActive)
        {
            bPaused = false;
        }
        break;

    case WM_SETCURSOR:
        if (gExclusive && bActive)
        {
            SetCursor(NULL);
            return TRUE;
        }
        break;

    case WM_PALETTECHANGED:
        if ((HWND)wParam == hWnd)
            break;
        // fall through to WM_QUERYNEWPALETTE
    case WM_QUERYNEWPALETTE:
        // install our palette here
        if (lpDDPal)
        {
            lpDDSPrimary->SetPalette(lpDDPal);
        }
        DDReLoadBitmap(lpDDSDonut, szBitmap);
        break;
        
    case WM_CREATE:
        break;

    case WM_KEYDOWN:
        switch( wParam )
        {
        case VK_ESCAPE:
        case VK_F12:
            PostMessage(hWnd,WM_CLOSE,0,0);
            break;
        }
        break;

    case WM_DESTROY:
        finiObjects();
        PostQuitMessage( 0 );
        break;
    }

    return DefWindowProc(hWnd, message, wParam, lParam);

} /* WindowProc */

/*
 * doInit - do work required for every instance of the application:
 *                create the window, initialize data
 */
static BOOL doInit( HINSTANCE hInstance, int nCmdShow )
{
    WNDCLASS            wc;
    HRESULT             ddrval;

    /*
     * set up and register window class
     */
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WindowProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon( hInstance, IDI_APPLICATION );
    wc.hCursor = LoadCursor( NULL, IDC_ARROW );
    wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wc.lpszMenuName = NAME;
    wc.lpszClassName = NAME;
    RegisterClass( &wc );
    
    /*
     * create a window
     */
    DWORD wndStyle = WS_OVERLAPPEDWINDOW;
    if( gExclusive)
        wndStyle = WS_POPUP;

    hWndMain = CreateWindowEx(
        WS_EX_APPWINDOW,
        NAME,
        TITLE,
        wndStyle,
        0,
        0,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        NULL,
        NULL,
        hInstance,
        NULL );

    if( !hWndMain )
    {
        return FALSE;
    }

    ShowWindow( hWndMain, nCmdShow );
    UpdateWindow( hWndMain );

    /*
     * create the main DirectDraw object
     */
    
    ddrval = CoCreateInstance(CLSID_DirectDrawFactory,
                              NULL, CLSCTX_INPROC_SERVER,
                              IID_IDirectDrawFactory,
                              (void **) & lpDDF);

    char strDDFailed[] = "DirectDraw Init Failed";
    if( ddrval != DD_OK )
    {
        return initFail(hWndMain, strDDFailed);
    }

    ddrval = lpDDF->CreateDirectDraw(NULL, hWndMain, DDSCL_NORMAL, 0, NULL, &lpDD);
    if( ddrval != DD_OK )
    {
        return initFail(hWndMain, strDDFailed);
    }

    // Get exclusive mode if requested
    if(gExclusive)
    {
        ddrval = lpDD->SetCooperativeLevel( hWndMain, DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN );
    }
    else
    {
        ddrval = lpDD->SetCooperativeLevel( hWndMain, DDSCL_NORMAL );
    }
    if( ddrval != DD_OK )
    {
        return initFail(hWndMain, strDDFailed);
    }

    if (!createSurfaces())
    {
        return initFail(hWndMain, strDDFailed);
    }

    // Create a DAView object and construct the model.
    if (!initDXAViewObj(lpDDSDA))
    {
        return initFail(hWndMain, "DirectX Animation Init FAILED");
    }

    return TRUE;
} /* doInit */

/*
 * WinMain - initialization, message loop
 */
int PASCAL WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
                        LPSTR lpCmdLine, int nCmdShow)
{
    MSG         msg;
    LPSTR       c;

    for(c=lpCmdLine; *c != '\0'; c++)
    {
        switch( *c )
        {
            case 'X': gExclusive = TRUE; break;
        }
    }
    
    if( !doInit( hInstance, nCmdShow ) )
    {
        return FALSE;
    }

    while( 1 )
    {
        if( PeekMessage( &msg, NULL, 0, 0, PM_NOREMOVE ) )
        {
            if( !GetMessage( &msg, NULL, 0, 0 ) )
                return msg.wParam;
            TranslateMessage(&msg); 
            DispatchMessage(&msg);
        }
        else if (!bPaused && (bActive || !gExclusive))
        {
            updateFrame();
        }
        else
        {
            WaitMessage();
        }
    }
} /* WinMain */
