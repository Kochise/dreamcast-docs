/*==========================================================================
 *
 *  Copyright (C) 1995-1997 Microsoft Corporation. All Rights Reserved.
 *
 *  File:	ddex4.cpp
 *  Content:	Direct Draw example program 4.	Adds functionality to 
 *		example program 3.  Creates a flipping surface and loads
 *		a bitmap image into an offscreen surface.  Uses BltFast to
 *		copy portions of the offscreen surface to the back buffer
 *		to generate an animation.  Illustrates watching return
 *		code from BltFast to prevent image tearing.  This program
 *		requires 1.2 Meg of video ram.
 *
 ***************************************************************************/

#define NAME "DDExample4"
#define TITLE "Direct Draw Example 4"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <windowsx.h>
#include <ddraw.h>
#include "resource.h"
#include "ddutil.h"

char szBitmap[] = "ALL";

LPDIRECTDRAW		lpDD;		// DirectDraw object
LPDIRECTDRAWSURFACE	lpDDSPrimary;	// DirectDraw primary surface
LPDIRECTDRAWSURFACE	lpDDSBack;	// DirectDraw back surface
LPDIRECTDRAWSURFACE	lpDDSOne;	// Offscreen surface 1
LPDIRECTDRAWPALETTE	lpDDPal;	// DirectDraw palette
BOOL			bActive;	// is application active?

/*
 * restoreAll
 *
 * restore all lost objects
 */
HRESULT restoreAll( void )
{
    HRESULT	ddrval;

    ddrval = lpDDSPrimary->Restore();
    if( ddrval == DD_OK )
    {
	ddrval = lpDDSOne->Restore();
	if( ddrval == DD_OK )
	{
            DDReLoadBitmap(lpDDSOne, szBitmap);
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
    static DWORD	lastTickCount[3] = {0,0,0};
    static int		currentFrame[3] = {0,0,0};
    DWORD		thisTickCount;
    RECT		rcRect;
    DWORD		delay[3] = {50, 78, 13};
    int			i;
    int			xpos[3] = {288, 190, 416};
    int			ypos[3] = {128, 300, 256};
    HRESULT		ddrval;

    // Decide which frame will be blitted next
    thisTickCount = GetTickCount();
    for(i=0; i<3; i++)
    {
	if((thisTickCount - lastTickCount[i]) > delay[i])
	{
	    // Move to next frame;
	    lastTickCount[i] = thisTickCount;
	    currentFrame[i]++;
	    if(currentFrame[i] > 59)
	    {
		currentFrame[i] = 0;
	    }
	}
    }

    // Blit the stuff for the next frame
    rcRect.left = 0;
    rcRect.top = 0;
    rcRect.right = 640;
    rcRect.bottom = 480;
    while( 1 )
    {
        ddrval = lpDDSBack->BltFast( 0, 0, lpDDSOne,
            &rcRect, DDBLTFAST_NOCOLORKEY );

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

    for( i=0; i<3; i++ )
    {
        rcRect.left   = currentFrame[i]%10*64;
        rcRect.top    = currentFrame[i]/10*64 + 480;
        rcRect.right  = currentFrame[i]%10*64 + 64;
        rcRect.bottom = currentFrame[i]/10*64 + 64 + 480;

	while( 1 )
	{
	    ddrval = lpDDSBack->BltFast( xpos[i], ypos[i], lpDDSOne,
                                 &rcRect, DDBLTFAST_SRCCOLORKEY );
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
    }

    // Flip the surfaces
    while( 1 )
    {
	ddrval = lpDDSPrimary->Flip( NULL, 0 );
	if( ddrval == DD_OK )
	{
	    break;
	}
	if( ddrval == DDERR_SURFACELOST )
	{
	    ddrval = restoreAll();
	    if( ddrval != DD_OK )
	    {
		break;
	    }
	}
	if( ddrval != DDERR_WASSTILLDRAWING )
	{
	    break;
	}
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
} /* finiObjects */

long FAR PASCAL WindowProc( HWND hWnd, UINT message, 
			    WPARAM wParam, LPARAM lParam )
{
    switch( message )
    {
    case WM_ACTIVATEAPP:
    	bActive = wParam;
	break;

    case WM_SETCURSOR:
        SetCursor(NULL);
        return TRUE;

    case WM_CREATE:
	break;

    case WM_KEYDOWN:
	switch( wParam )
	{
	case VK_ESCAPE:
        case VK_F12:
            PostMessage(hWnd, WM_CLOSE, 0, 0);
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
 *		  create the window, initialize data
 */
static BOOL doInit( HINSTANCE hInstance, int nCmdShow )
{
    HWND		hwnd;
    WNDCLASS		wc;
    DDSURFACEDESC	ddsd;
    DDSCAPS		ddscaps;
    HRESULT		ddrval;

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
    wc.hbrBackground = GetStockBrush(BLACK_BRUSH);
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
        GetSystemMetrics(SM_CXSCREEN),
        GetSystemMetrics(SM_CYSCREEN),
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

    // Get exclusive mode
    ddrval = lpDD->SetCooperativeLevel( hwnd, DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN );
    if( ddrval != DD_OK )
    {
	return initFail(hwnd);
    }

    // Set the video mode to 640x480x8
    ddrval = lpDD->SetDisplayMode( 640, 480, 8);
    if( ddrval != DD_OK )
    {
	return initFail(hwnd);
    }

    // Create the primary surface with 1 back buffer
    ddsd.dwSize = sizeof( ddsd );
    ddsd.dwFlags = DDSD_CAPS | DDSD_BACKBUFFERCOUNT;
    ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE |
			  DDSCAPS_FLIP |
			  DDSCAPS_COMPLEX;
    ddsd.dwBackBufferCount = 1;
    ddrval = lpDD->CreateSurface( &ddsd, &lpDDSPrimary, NULL );
    if( ddrval != DD_OK )
    {
	return initFail(hwnd);
    }

    ddscaps.dwCaps = DDSCAPS_BACKBUFFER;
    ddrval = lpDDSPrimary->GetAttachedSurface(&ddscaps, &lpDDSBack);
    if( ddrval != DD_OK )
    {
	return initFail(hwnd);
    }

    // create and set the palette
    lpDDPal = DDLoadPalette(lpDD, szBitmap);

    if (lpDDPal)
        lpDDSPrimary->SetPalette(lpDDPal);

    // Create the offscreen surface, by loading our bitmap.
    lpDDSOne = DDLoadBitmap(lpDD, szBitmap, 0, 0);

    if( lpDDSOne == NULL )
    {
	return initFail(hwnd);
    }

    // Set the color key for this bitmap (black)
    DDSetColorKey(lpDDSOne, RGB(0,0,0));

    return TRUE;
} /* doInit */

/*
 * WinMain - initialization, message loop
 */
int PASCAL WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
			LPSTR lpCmdLine, int nCmdShow)
{
    MSG		msg;

    lpCmdLine = lpCmdLine;
    hPrevInstance = hPrevInstance;

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
	else if( bActive )
	{
	    updateFrame();
        }
        else
        {
            // make sure we go to sleep if we have nothing else to do
            WaitMessage();
        }
    }
} /* WinMain */
