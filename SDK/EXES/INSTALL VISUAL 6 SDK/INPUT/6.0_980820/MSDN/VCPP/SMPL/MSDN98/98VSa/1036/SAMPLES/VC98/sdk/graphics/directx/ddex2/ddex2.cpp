/*==========================================================================
 *
 *  Copyright (C) 1995-1997 Microsoft Corporation. All Rights Reserved.
 *
 *  File:       ddex2.cpp
 *  Content:    Direct Draw example program 2.  Adds functionality to 
 *              example program 1.  Changes the video mode to 640x480x8.
 *              Reads a bitmap file from disk and copies it into the 
 *              back buffer and then slowly flips between the primary
 *              surface and the back buffer.  Press F12 to exit the program.
 *
 ***************************************************************************/

#define NAME "DDExample2"
#define TITLE "Direct Draw Example 2"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <windowsx.h>
#include <ddraw.h>
#include <stdlib.h>
#include <stdarg.h>
#include "resource.h"
#include "ddutil.h"

#define TIMER_ID        1
#define TIMER_RATE      250

LPDIRECTDRAW            lpDD;           // DirectDraw object
LPDIRECTDRAWSURFACE     lpDDSPrimary;   // DirectDraw primary surface
LPDIRECTDRAWSURFACE     lpDDSBack;      // DirectDraw back surface
LPDIRECTDRAWPALETTE     lpDDPal;        // DirectDraw palette
BOOL                    bActive;        // is application active?

char szBackground[] = "BACK";

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
	if( lpDDPal != NULL )
	{
	    lpDDPal->Release();
	    lpDDPal = NULL;
	}
	lpDD->Release();
	lpDD = NULL;
    }

} /* finiObjects */

char szFrontMsg[] = "Front buffer (F12 to quit)";
char szBackMsg[] = "Back buffer (F12 to quit)";

long FAR PASCAL WindowProc( HWND hWnd, UINT message, 
			    WPARAM wParam, LPARAM lParam )
{
    static BYTE phase = 0;
    HDC         hdc;

    switch( message )
    {
    case WM_ACTIVATEAPP:
	bActive = wParam;
	break;

    case WM_CREATE:
	break;

    case WM_TIMER:
	// Flip surfaces
	if( bActive )
	{
	    if (lpDDSBack->GetDC(&hdc) == DD_OK)
	    {
		SetBkColor( hdc, RGB( 0, 0, 255 ) );
		SetTextColor( hdc, RGB( 255, 255, 0 ) );
		if( phase )
		{
		    TextOut( hdc, 0, 0, szFrontMsg, lstrlen(szFrontMsg) );
		    phase = 0;
		}
		else
		{
		    TextOut( hdc, 0, 0, szBackMsg, lstrlen(szBackMsg) );
		    phase = 1;
		}
		lpDDSBack->ReleaseDC(hdc);
	    }
	    while( 1 )
	    {
		HRESULT ddrval;
		ddrval = lpDDSPrimary->Flip( NULL, 0 );
		if( ddrval == DD_OK )
		{
		    break;
		}
		if( ddrval == DDERR_SURFACELOST )
		{
		    ddrval = lpDDSPrimary->Restore();

		    if( ddrval != DD_OK )
		    {
			break;
		    }

		    ddrval = DDReLoadBitmap(lpDDSBack, szBackground);

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
 
    case WM_SETCURSOR:
	SetCursor(NULL);
	return TRUE;

    case WM_KEYDOWN:
	switch( wParam )
	{
	case VK_ESCAPE:
	case VK_F12:
	    DestroyWindow( hWnd );
	    return 0;
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
    wc.hbrBackground = NULL;
    wc.lpszMenuName = NAME;
    wc.lpszClassName = NAME;
    RegisterClass( &wc );
    
    /*
     * create a window
     */
    hwnd = CreateWindowEx(
	WS_EX_TOPMOST,
	NAME,
	TITLE,
	WS_POPUP,
	0,
	0,
	GetSystemMetrics( SM_CXSCREEN ),
	GetSystemMetrics( SM_CYSCREEN ),
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
	goto error;

    // Get exclusive mode
    ddrval = lpDD->SetCooperativeLevel( hwnd,
			    DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN );
    if(ddrval != DD_OK )
	goto error;

    // Set the video mode to 640x480x8
    ddrval = lpDD->SetDisplayMode( 640, 480, 8);
    if(ddrval != DD_OK)
	goto error;

    // Create the primary surface with 1 back buffer
    ddsd.dwSize = sizeof( ddsd );
    ddsd.dwFlags = DDSD_CAPS | DDSD_BACKBUFFERCOUNT;
    ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE |
			  DDSCAPS_FLIP |
			  DDSCAPS_COMPLEX;
    ddsd.dwBackBufferCount = 1;
    ddrval = lpDD->CreateSurface( &ddsd, &lpDDSPrimary, NULL );
    if( ddrval != DD_OK )
	goto error;

    ddscaps.dwCaps = DDSCAPS_BACKBUFFER;
    ddrval = lpDDSPrimary->GetAttachedSurface(&ddscaps, &lpDDSBack);

    if( ddrval != DD_OK )
	goto error;

    lpDDPal = DDLoadPalette(lpDD, szBackground);

    if (lpDDPal == NULL)
	goto error;

    ddrval = lpDDSPrimary->SetPalette(lpDDPal);

    if( ddrval != DD_OK )
	goto error;

    // load a bitmap into the back buffer.
    ddrval = DDReLoadBitmap(lpDDSBack, szBackground);

    if( ddrval != DD_OK )
	goto error;

    // Create a timer to flip the pages
    if( !SetTimer( hwnd, TIMER_ID, TIMER_RATE, NULL ) )
	goto error;

    return TRUE;

error:
    finiObjects();
    MessageBox( hwnd, "DirectDraw Init FAILED", TITLE, MB_OK );
    DestroyWindow( hwnd );
    return FALSE;
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

    while(GetMessage(&msg, NULL, 0, 0))
    {
	TranslateMessage(&msg);
	DispatchMessage(&msg);
    }

    return msg.wParam;

} /* WinMain */
