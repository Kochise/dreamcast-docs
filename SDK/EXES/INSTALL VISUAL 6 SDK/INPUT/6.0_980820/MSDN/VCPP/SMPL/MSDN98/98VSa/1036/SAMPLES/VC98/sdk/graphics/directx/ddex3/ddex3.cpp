/*==========================================================================
 *
 *  Copyright (C) 1995-1997 Microsoft Corporation. All Rights Reserved.
 *
 *  File:       ddex3.cpp
 *  Content:    Direct Draw example program 3.  Adds functionality to 
 *              example program 2.  Creates two offscreen surfaces in 
 *              addition to the primary surface and back buffer.  Loads
 *              a bitmap file into each offscreen surface.  Uses BltFast
 *              to copy the contents of an offscreen surface to the back
 *              buffer and then flips the buffers and copies the next 
 *              offscreen surface to the back buffer.  Press F12 to exit
 *              the program.  This program requires at least 1.2 Megs of 
 *              video ram.
 *
 ***************************************************************************/

#define NAME "DDExample3"
#define TITLE "Direct Draw Example 3"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <windowsx.h>
#include <ddraw.h>
#include <stdlib.h>
#include <stdarg.h>
#include "resource.h"
#include "ddutil.h"         // DDLoadPalette, DDCopyBitmap

// Name of our bitmap resource.
char szBitmap[] = "DDEX3";

BOOL InitSurfaces( void );

#define TIMER_ID        1
#define TIMER_RATE      500

LPDIRECTDRAW            lpDD;           // DirectDraw object
LPDIRECTDRAWSURFACE     lpDDSPrimary;   // DirectDraw primary surface
LPDIRECTDRAWSURFACE     lpDDSBack;      // DirectDraw back surface
LPDIRECTDRAWSURFACE     lpDDSOne;       // Offscreen surface 1
LPDIRECTDRAWSURFACE     lpDDSTwo;       // Offscreen surface 2
LPDIRECTDRAWPALETTE     lpDDPal;        // DirectDraw palette
BOOL                    bActive;        // is application active?

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
	if( lpDDSTwo != NULL )
	{
	    lpDDSTwo->Release();
	    lpDDSTwo = NULL;
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
		InitSurfaces();
	    }
	}
    }
    return ddrval;

} /* restoreAll */

long FAR PASCAL WindowProc( HWND hWnd, UINT message, 
			    WPARAM wParam, LPARAM lParam )
{
    static  int phase = 0;
    RECT        rcRect;

    switch( message )
    {
    case WM_ACTIVATEAPP:
	bActive = wParam;
	break;

    case WM_CREATE:
	break;

    case WM_SETCURSOR:
	SetCursor(NULL);
	return TRUE;

    case WM_TIMER:
	if( bActive )
	{
	    HRESULT             ddrval;
	    LPDIRECTDRAWSURFACE pdds;

	    rcRect.left = 0;
	    rcRect.top = 0;
	    rcRect.right = 640;
	    rcRect.bottom = 480;
	    if(phase)
	    {
		pdds = lpDDSTwo;
		phase = 0;
	    }
	    else
	    {
		pdds = lpDDSOne;
		phase = 1;
	    }
	    while( 1 )
	    {
		ddrval = lpDDSBack->BltFast( 0, 0, pdds, &rcRect, FALSE );
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
    
	    // Flip surfaces
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
	}
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
 *                create the window, initialize data
 */
static BOOL doInit( HINSTANCE hInstance, int nCmdShow )
{
    HWND                hwnd;
    WNDCLASS            wc;
    DDSURFACEDESC       ddsd;
    DDSCAPS             ddscaps;
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

    // Create a offscreen bitmap.
    ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;
    ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;
    ddsd.dwHeight = 480;
    ddsd.dwWidth = 640;
    ddrval = lpDD->CreateSurface( &ddsd, &lpDDSOne, NULL );
    if( ddrval != DD_OK )
    {
	return initFail(hwnd);
    }

    // Create another offscreen bitmap.
    ddrval = lpDD->CreateSurface( &ddsd, &lpDDSTwo, NULL );
    if( ddrval != DD_OK )
    {
	return initFail(hwnd);
    }

    // Create a Direct Draw Palette and associate it with the front buffer
    lpDDPal = DDLoadPalette(lpDD, szBitmap);

    if (lpDDPal)
	lpDDSPrimary->SetPalette( lpDDPal );

    if( !InitSurfaces() )
    {
	return initFail(hwnd);
    }

    // Create a timer to flip the pages
    if( !SetTimer( hwnd, TIMER_ID, TIMER_RATE, NULL ) )
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

    lpCmdLine = lpCmdLine;
    hPrevInstance = hPrevInstance;

    if( !doInit( hInstance, nCmdShow ) )
    {
	return FALSE;
    }

    while( GetMessage( &msg, NULL, 0, 0 ) )
    {
	TranslateMessage(&msg);
	DispatchMessage(&msg);
    }

    return msg.wParam;

} /* WinMain */

/*
 * InitSurfaces - This function reads the bitmap file FRNTBACK.BMP
 * and stores half of it in offscreen surface 1 and the other half in 
 * offscreen surface 2.
 */
BOOL InitSurfaces( void )
{
    HBITMAP hbm;

    // Load our bitmap resource.
    hbm = (HBITMAP)LoadImage(GetModuleHandle(NULL), szBitmap, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);

    if (hbm == NULL)
	return FALSE;

    DDCopyBitmap(lpDDSOne, hbm, 0, 0,   640, 480);
    DDCopyBitmap(lpDDSTwo, hbm, 0, 480, 640, 480);
    DeleteObject(hbm);

    return TRUE;

} /* readBMPIntoSurfaces */
