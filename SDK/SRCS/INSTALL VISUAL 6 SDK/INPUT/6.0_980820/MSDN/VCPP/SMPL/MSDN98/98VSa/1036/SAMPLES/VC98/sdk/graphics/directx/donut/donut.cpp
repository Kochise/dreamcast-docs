/*==========================================================================
 *
 *  Copyright (C) 1995-1997 Microsoft Corporation. All Rights Reserved.
 *
 *  File:       donut.cpp
 *
 ***************************************************************************/

#define NAME "Donut"
#define TITLE "Donut"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <windowsx.h>
#include <ddraw.h>
#include "resource.h"
#include "ddutil.h"

char szBitmap[] = "DONUT";

int             gPos = 0;
BOOL            gExclusive = FALSE;
int             gMode = 0;
HWND            hwnd;

LPDIRECTDRAW            lpDD;           // DirectDraw object
LPDIRECTDRAWSURFACE     lpDDSPrimary;   // DirectDraw primary surface
LPDIRECTDRAWSURFACE     lpDDSOne;       // Offscreen surface 1
LPDIRECTDRAWSURFACE     lpDDSTwo;       // Offscreen surface 2
LPDIRECTDRAWPALETTE     lpDDPal;        // DirectDraw palette
BOOL                    bActive;        // is application active?

/*
 * restoreAll
 *
 * restore all lost objects
 */
HRESULT restoreAll( void )
{
    HRESULT     ddrval;

    ddrval = lpDDSPrimary->Restore();
    if( ddrval == DD_OK )
    {
	ddrval = lpDDSOne->Restore();
	if( ddrval == DD_OK )
	{
	    ddrval = lpDDSTwo->Restore();
	    if( ddrval == DD_OK )
	    {
		DDReLoadBitmap(lpDDSOne, szBitmap);
	    }
	}
    }
    return ddrval;

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
    RECT                rcRect;
    DWORD               delay = 17;
    HRESULT             ddrval;
    int                 pos;

    thisTickCount = GetTickCount();
    if((thisTickCount - lastTickCount) <= delay)
    {
	return;
    }

    switch( gPos )
    {
	case 0: pos = 0; break;
	case 1: pos = 64; break;
	case 2: pos = 128; break;
    }
    rcRect.left = 0;
    rcRect.top = 0;
    rcRect.right = 64;
    rcRect.bottom = 64;

    // restore a previously saved patch
    while( haveBackground )
    {
	ddrval = lpDDSPrimary->BltFast( pos, 0, lpDDSTwo, &rcRect, FALSE );
	if( ddrval == DD_OK )
	{
	    haveBackground = TRUE;
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

    rcRect.left = pos;
    rcRect.right = pos+64;
    // Save the current primary surface that we are about to overwrite
    while( 1 )
    {
	haveBackground = FALSE;
	ddrval = lpDDSTwo->BltFast( 0, 0, lpDDSPrimary,
	    &rcRect, DDBLTFAST_NOCOLORKEY);

	if( ddrval == DD_OK )
	{
	    haveBackground = TRUE;
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

    // Blit the stuff for the next frame
    rcRect.left   = currentFrame%10*64;
    rcRect.top    = currentFrame/10*64;
    rcRect.right  = currentFrame%10*64 + 64;
    rcRect.bottom = currentFrame/10*64 + 64;

    while( 1 )
    {
	ddrval = lpDDSPrimary->BltFast( pos, 0, lpDDSOne,
	    &rcRect, DDBLTFAST_SRCCOLORKEY);

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
    if(ddrval != DD_OK)
    {
	return;
    }
} /* updateFrame */


/*
 * finiObjects
 *
 * finished with all objects we use; release them
 */
static void finiObjects( void )
{
    if( lpDD != NULL )
    {
	if( lpDDSPrimary != NULL )
	{
	    lpDDSPrimary->Release();
	    lpDDSPrimary = NULL;
	}
	if( lpDDSOne != NULL )
	{
	    lpDDSOne->Release();
	    lpDDSOne = NULL;
	}
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

long FAR PASCAL WindowProc( HWND hWnd, UINT message, 
			    WPARAM wParam, LPARAM lParam )
{
    hwnd = hWnd;
    switch( message )
    {
    case WM_ACTIVATEAPP:
	bActive = wParam;
	break;

    case WM_SETCURSOR:
	SetCursor(NULL);
	return TRUE;

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
	DDReLoadBitmap(lpDDSOne, szBitmap);
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
 * This function is called if the initialization function fails
 */
BOOL initFail( HWND hwnd )
{
    finiObjects();
    MessageBox( hwnd, "DirectDraw Init FAILED", TITLE, MB_OK );
    DestroyWindow( hwnd );
    return FALSE;

} /* initFail */

/*
 * doInit - do work required for every instance of the application:
 *                create the window, initialize data
 */
static BOOL doInit( HINSTANCE hInstance, int nCmdShow )
{
    HWND                hwnd;
    WNDCLASS            wc;
    DDSURFACEDESC       ddsd;
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
    hwnd = CreateWindowEx(
	0,
	NAME,
	TITLE,
	WS_POPUP,
	0,
	0,
	1,
	1,
	NULL,
	NULL,
	hInstance,
	NULL );

    if( !hwnd )
    {
	return FALSE;
    }

    ShowWindow( hwnd, nCmdShow );
    UpdateWindow( hwnd );

    /*
     * create the main DirectDraw object
     */
    ddrval = DirectDrawCreate( NULL, &lpDD, NULL );
    if( ddrval != DD_OK )
    {
	return initFail(hwnd);
    }

    // Get exclusive mode if requested
    if(gExclusive)
    {
	ddrval = lpDD->SetCooperativeLevel( hwnd, DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN );
    }
    else
    {
	ddrval = lpDD->SetCooperativeLevel( hwnd, DDSCL_NORMAL );
    }
    if( ddrval != DD_OK )
    {
	return initFail(hwnd);
    }

    // Set the video mode to 640x480x8
    switch( gMode )
    {
	case 1:  ddrval = lpDD->SetDisplayMode( 640, 480, 8); break;
	case 2:  ddrval = lpDD->SetDisplayMode( 800, 600, 8); break;
	case 3:  ddrval = lpDD->SetDisplayMode( 1024, 768, 8); break;
	case 4:  ddrval = lpDD->SetDisplayMode( 1280, 1024, 8); break;
    }
    if( ddrval != DD_OK )
    {
	return initFail(hwnd);
    }

    // Create the primary surface
    ddsd.dwSize = sizeof( ddsd );
    ddsd.dwFlags = DDSD_CAPS;
    ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;

    ddrval = lpDD->CreateSurface( &ddsd, &lpDDSPrimary, NULL );
    if( ddrval != DD_OK )
    {
	return initFail(hwnd);
    }

    lpDDPal = DDLoadPalette(lpDD, szBitmap);

    if (lpDDPal)
    {
	lpDDSPrimary->SetPalette(lpDDPal);
    }

    lpDDSOne = DDLoadBitmap(lpDD, szBitmap, 0, 0);
    if( lpDDSOne == NULL )
    {
	return initFail(hwnd);
    }

    // set color key to black
    DDSetColorKey(lpDDSOne, RGB(0,0,0));

    ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;
    ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;
    ddsd.dwHeight = 64;
    ddsd.dwWidth = 64;
    ddrval = lpDD->CreateSurface( &ddsd, &lpDDSTwo, NULL );
    if( ddrval != DD_OK )
    {
	return initFail(hwnd);
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
	    case '0': gPos = 0; break;
	    case '1': gPos = 1; break;
	    case '2': gPos = 2; break;
	    case 'X': gExclusive = TRUE; break;
	    case 'A': gExclusive = TRUE; gMode = 1; break;
	    case 'B': gExclusive = TRUE; gMode = 2; break;
	    case 'C': gExclusive = TRUE; gMode = 3; break;
	    case 'D': gExclusive = TRUE; gMode = 4; break;
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
	else if( !gExclusive || bActive )
	{
	    updateFrame();
	}
	else
	{
	    WaitMessage();
	}
    }
} /* WinMain */
