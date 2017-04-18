/*==========================================================================
 *
 *  Copyright (C) 1995-1997 Microsoft Corporation. All Rights Reserved.
 *
 *  File:	ddex5.cpp
 *  Content:	Direct Draw example program 5.	Adds functionality to
 *		example program 4.  Uses GetEntries() to read a palette,
 *		modifies the entries, and then uses SetEntries() to update
 *		the palette.  This program requires 1.2 Meg of video ram.
 *
 ***************************************************************************/

#define NAME "DDExample5"
#define TITLE "Direct Draw Example 5"

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
LPDIRECTDRAWPALETTE	lpDDPal;	// The primary surface palette
BOOL			bActive;	// is application active?

BYTE torusColors[256];	// Marks the colors used in the torus

/*
 * restoreAll
 *
 * restore all lost objects
 */
HRESULT restoreAll( void )
{
    HRESULT	ddrval;
    DDSURFACEDESC	ddsd;

    ddrval = lpDDSPrimary->Restore();
    if( ddrval == DD_OK )
    {
	ddrval = lpDDSOne->Restore();
	if( ddrval == DD_OK )
        {
            DDReLoadBitmap(lpDDSOne, szBitmap);
	}
    }

    //Loose the old palette
    lpDDPal->Release();
    // create and set the palette (restart cycling from the same place)
    lpDDPal = DDLoadPalette(lpDD, szBitmap);

    if (lpDDPal)
        lpDDSPrimary->SetPalette(lpDDPal);
    //
    // Mark the colors used in the torus frames
    //
    int i,x,y;

    // First, set all colors as unused
    for(i=0; i<256; i++)
    {
        torusColors[i] = 0;
    }

    // lock the surface and scan the lower part (the torus area)
    // and remember all the index's we find.
    ddsd.dwSize = sizeof(ddsd);
    while (lpDDSOne->Lock(NULL, &ddsd, 0, NULL) == DDERR_WASSTILLDRAWING)
        ;

    // Now search through the torus frames and mark used colors
    for( y=480; y<480+384; y++ )
    {
        for( x=0; x<640; x++ )
        {
            torusColors[((BYTE *)ddsd.lpSurface)[y*ddsd.lPitch+x]] = 1;
        }
    }

    lpDDSOne->Unlock(NULL);

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
    static DWORD	lastTickCount[4] = {0,0,0,0};
    static int		currentFrame[3] = {0,0,0};
    DWORD		thisTickCount;
    RECT		rcRect;
    DWORD		delay[4] = {50, 78, 13, 93};
    int			i;
    int			xpos[3] = {288, 190, 416};
    int			ypos[3] = {128, 300, 256};
    PALETTEENTRY	pe[256];
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
		currentFrame[i] = 0;
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

    for(i=0; i<3; i++)
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

    if( (thisTickCount - lastTickCount[3]) > delay[3] )
    {
	// Change the palette
	if(lpDDPal->GetEntries( 0, 0, 256, pe ) != DD_OK)
	{
	    return;
	}
	
	for(i=1; i<256; i++)
	{
	    if(!torusColors[i])
	    {
		continue;
	    }
	    pe[i].peRed = (pe[i].peRed+2) % 256;
	    pe[i].peGreen = (pe[i].peGreen+1) % 256;
	    pe[i].peBlue = (pe[i].peBlue+3) % 256;
	}
	if(lpDDPal->SetEntries( 0, 0, 256, pe) != DD_OK)
	{
	    return;
	}
    
	lastTickCount[3] = thisTickCount;
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
    SetFocus( hwnd );

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
    if(ddrval != DD_OK)
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

    // set the color key to black
    DDSetColorKey(lpDDSOne, RGB(0,0,0));

    //
    // Mark the colors used in the torus frames
    //
    int i,x,y;

    // First, set all colors as unused
    for(i=0; i<256; i++)
    {
        torusColors[i] = 0;
    }

    // lock the surface and scan the lower part (the torus area)
    // and remember all the index's we find.
    ddsd.dwSize = sizeof(ddsd);
    while (lpDDSOne->Lock(NULL, &ddsd, 0, NULL) == DDERR_WASSTILLDRAWING)
        ;

    // Now search through the torus frames and mark used colors
    for( y=480; y<480+384; y++ )
    {
        for( x=0; x<640; x++ )
        {
            torusColors[((BYTE *)ddsd.lpSurface)[y*ddsd.lPitch+x]] = 1;
        }
    }

    lpDDSOne->Unlock(NULL);

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
	    {
		return msg.wParam;
	    }
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
