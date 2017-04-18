/*==========================================================================
 *
 *  Copyright (C) 1995-1997 Microsoft Corporation. All Rights Reserved.
 *
 *  File:       gfx.c
 *  Content:    DirectDraw related code.
 *
 *
 ***************************************************************************/
#include "gfx.h"
#include "input.h"
#include "ddutil.h"

/*
 * Externals
 */
extern BOOL             gbUseEmulation;     // user DDHEL or DDHAL ?
extern BOOL				gbFullscreen;		// window or fullscreen mode ?
extern HWND				ghWndMain;			// main window
extern DWORD			gdwKeys;				
extern int              gnProgramState;     // current state of program (rest, splash, active, etc.)
extern RECT				grcWindow;          // client window rectangle
extern BOOL				gbFullscreen;		// fullscreen or window mode ?
extern HINSTANCE		ghinst;				// application instance handle
extern TCHAR			gtszClassName[];	// Duel's class name


/*
 * Globals
 */
LPDIRECTDRAWSURFACE     glpFrontBuffer;			// primary surface
LPDIRECTDRAWSURFACE     glpBackBuffer;			// back buffer for animation
LPDIRECTDRAWSURFACE		glpSplash;				// splash screen
LPDIRECTDRAWSURFACE     glpShip0;				// ship bitmaps
LPDIRECTDRAWSURFACE     glpShip1;
LPDIRECTDRAWSURFACE     glpShip2;
LPDIRECTDRAWSURFACE     glpShip3;
LPDIRECTDRAWSURFACE     glpNum;					// Numbers bitmap
LPDIRECTDRAW            glpDD;					// DirectDraw interface
LPDIRECTDRAWPALETTE     glpArtPalette=NULL;		// Game screen palette
LPDIRECTDRAWPALETTE     glpSplashPalette=NULL;	// Splash screen palette
LPDIRECTDRAWCLIPPER		glpClipper=NULL;		// Clipper for front buffer
DWORD                   gdwFillColor;
int						gnGameBPP;				// primary surface bit depth
#ifdef DEBUG
BOOL                    gbHELBlt = FALSE;
#endif

BOOL InitGraphics( void )
{
    DDCAPS          ddcaps;
    HRESULT         ddrval;
    DDSURFACEDESC   ddsd;
    DDSCAPS         ddscaps;
	TCHAR			tszTitle[MAX_WINDOWTITLE];

	LoadString(ghinst, IDS_DUEL_TITLE, tszTitle, MAX_WINDOWTITLE);

	// Create a window
    ghWndMain = CreateWindowEx(
		WS_EX_APPWINDOW,  // WS_EX_TOPMOST,
        gtszClassName,
        tszTitle,
					 // don't show the window yet 
        WS_POPUP |   // non-app window POPUP
        WS_SYSMENU,  // so we get an icon in the tray
        0,
        0,
        GetSystemMetrics(SM_CXSCREEN),
        GetSystemMetrics(SM_CYSCREEN),
        NULL,
        NULL,
        ghinst,
        NULL );

    if( !ghWndMain )
    {
        return FALSE;
    }

    UpdateWindow( ghWndMain );
    SetFocus( ghWndMain );

	// ddraw stuff begins here
    if( gbUseEmulation )
        ddrval = DirectDrawCreate( (LPVOID) DDCREATE_EMULATIONONLY, &glpDD, NULL );
    else
        ddrval = DirectDrawCreate( NULL, &glpDD, NULL );

    if( ddrval != DD_OK )
        return ShowError(IDS_DDRAW_ERROR_DDC);

	// set access mode based on fullscreen/window
	if (gbFullscreen) 
	{
		ddrval = glpDD->lpVtbl->SetCooperativeLevel( glpDD, ghWndMain,
                            DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN );
	}
	else
	{
		ddrval = glpDD->lpVtbl->SetCooperativeLevel( glpDD, ghWndMain,
                            DDSCL_NORMAL);
	}

    if( ddrval != DD_OK )
        return ShowError(IDS_DDRAW_ERROR_SCL);

	if (gbFullscreen)
	{
	    // set the mode to 640 by 480 by 8
		ddrval = glpDD->lpVtbl->SetDisplayMode( glpDD, 640, 480, 8 );
	    
		if( ddrval != DD_OK )
		    return ShowError(IDS_DDRAW_ERROR_SDM);
	}
	else
	{
		RECT rcWork;
		RECT rc;
		HDC hdc;
		DWORD dwStyle;

		//
		//  when in rome (I mean when in windows) we should use the
		//  current mode
		//
		hdc = GetDC(NULL);
		gnGameBPP = GetDeviceCaps(hdc, PLANES) * GetDeviceCaps(hdc, BITSPIXEL);
		ReleaseDC(NULL, hdc);

		//
		// if we are still a WS_POPUP window we should convert to a
		// normal app window so we look like a windows app.
		//
		dwStyle = GetWindowStyle(ghWndMain);
		dwStyle &= ~WS_POPUP;
		dwStyle |= WS_OVERLAPPED | WS_CAPTION | WS_THICKFRAME | WS_MINIMIZEBOX;
		SetWindowLong(ghWndMain, GWL_STYLE, dwStyle);

		// set window size
		SetRect(&rc, 0, 0, MAX_DEFWIN_X, MAX_DEFWIN_Y);

		AdjustWindowRectEx(&rc,
			GetWindowStyle(ghWndMain),
			GetMenu(ghWndMain) != NULL,
			GetWindowExStyle(ghWndMain));

		SetWindowPos(ghWndMain, NULL, 0, 0, rc.right-rc.left, rc.bottom-rc.top,
			SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);

		SetWindowPos(ghWndMain, HWND_NOTOPMOST, 0, 0, 0, 0,
			SWP_NOSIZE | SWP_NOMOVE | SWP_NOACTIVATE);

		//
		//  make sure our window does not hang outside of the work area
		//  this will make people who have the tray on the top or left
		//  happy.
		//
		SystemParametersInfo(SPI_GETWORKAREA, 0, &rcWork, 0);
		GetWindowRect(ghWndMain, &rc);
		if (rc.left < rcWork.left) rc.left = rcWork.left;
		if (rc.top  < rcWork.top)  rc.top  = rcWork.top;
		SetWindowPos(ghWndMain, NULL, rc.left, rc.top, 0, 0,
			SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
	}

    // check the color key hardware capabilities
    ddcaps.dwSize = sizeof( ddcaps );

	memset( &ddsd, 0, sizeof( ddsd ) );
	ddsd.dwSize = sizeof( ddsd );

	if (gbFullscreen)
	{
		// Create surfaces
		ddsd.dwFlags = DDSD_CAPS | DDSD_BACKBUFFERCOUNT;
		ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE |
							  DDSCAPS_FLIP |
							  DDSCAPS_COMPLEX;
		ddsd.dwBackBufferCount = 1;
		ddrval = glpDD->lpVtbl->CreateSurface( glpDD, &ddsd, &glpFrontBuffer, NULL );
		if( ddrval != DD_OK )
			return ShowError(IDS_DDRAW_ERROR_CSFB);

		// get a pointer to the back buffer
		ddscaps.dwCaps = DDSCAPS_BACKBUFFER;
		ddrval = glpFrontBuffer->lpVtbl->GetAttachedSurface(
					glpFrontBuffer,
					&ddscaps,
					&glpBackBuffer );
		if( ddrval != DD_OK )
			return ShowError(IDS_DDRAW_ERROR_GAS);
	}
	else
	{
		// window case, create the primary surface
		// and create a backbuffer in offscreen memory
		ddsd.dwFlags = DDSD_CAPS;
		ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;

		ddrval = glpDD->lpVtbl->CreateSurface( glpDD, &ddsd, &glpFrontBuffer, NULL );
		if( ddrval != DD_OK )
			return ShowError(IDS_DDRAW_ERROR_CSFB);

		ddsd.dwFlags = DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT;	
		ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;

		ddsd.dwWidth = MAX_DEFWIN_X;
		ddsd.dwHeight = MAX_DEFWIN_Y;
		ddrval = glpDD->lpVtbl->CreateSurface( glpDD, &ddsd, &glpBackBuffer, NULL );
		if( ddrval != DD_OK )
			return ShowError(IDS_DDRAW_ERROR_CSBB);

		ddrval = glpDD->lpVtbl->CreateClipper(glpDD, 0, &glpClipper, NULL);
		if( ddrval != DD_OK )
			return ShowError(IDS_DDRAW_ERROR_CC);

		ddrval = glpClipper->lpVtbl->SetHWnd(glpClipper, 0, ghWndMain);
		if( ddrval != DD_OK )
			return ShowError(IDS_DDRAW_ERROR_SH);

		ddrval = glpFrontBuffer->lpVtbl->SetClipper(glpFrontBuffer, glpClipper);
		if( ddrval != DD_OK )
			return ShowError(IDS_DDRAW_ERROR_SC);
	}

    ddsd.dwFlags = DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT;	
    ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;
#ifdef DEBUG
    if( gbHELBlt )
        ddsd.ddsCaps.dwCaps |= DDSCAPS_SYSTEMMEMORY;
#endif

    ddsd.dwWidth = 320;
    ddsd.dwHeight = 128;
    ddrval = glpDD->lpVtbl->CreateSurface( glpDD, &ddsd, &glpShip0, NULL );
    if( ddrval != DD_OK )
	return ShowError(IDS_DDRAW_ERROR_CSS0);

    ddsd.dwWidth = 320;
    ddsd.dwHeight = 128;
    ddrval = glpDD->lpVtbl->CreateSurface( glpDD, &ddsd, &glpShip1, NULL );
    if( ddrval != DD_OK )
	return ShowError(IDS_DDRAW_ERROR_CSS1);

    ddsd.dwWidth = 320;
    ddsd.dwHeight = 128;
    ddrval = glpDD->lpVtbl->CreateSurface( glpDD, &ddsd, &glpShip2, NULL );
    if( ddrval != DD_OK )
	return ShowError(IDS_DDRAW_ERROR_CSS2);

    ddsd.dwWidth = 320;
    ddsd.dwHeight = 128;
    ddrval = glpDD->lpVtbl->CreateSurface( glpDD, &ddsd, &glpShip3, NULL );
    if( ddrval != DD_OK )
	return ShowError(IDS_DDRAW_ERROR_CSS3);

    ddsd.dwHeight = 16;
    ddrval = glpDD->lpVtbl->CreateSurface( glpDD, &ddsd, &glpNum, NULL );
    if( ddrval != DD_OK )
	return ShowError(IDS_DDRAW_ERROR_CSN);

    if( !RestoreSurfaces() )
        return ShowError(IDS_DDRAW_ERROR_RS);
	
    gdwKeys = 0;
	ShowWindow(ghWndMain, SW_SHOW);
    return TRUE;
}

void CleanupGraphics(void)
{
    if( glpShip0 != NULL )
	glpShip0->lpVtbl->Release( glpShip0 );
	
    if( glpShip1 != NULL )
	glpShip1->lpVtbl->Release( glpShip1 );
	
    if( glpShip2 != NULL )
	glpShip2->lpVtbl->Release( glpShip2 );
	
    if( glpShip3 != NULL )
	glpShip3->lpVtbl->Release( glpShip3 );
	
    if( glpNum != NULL )
	glpNum->lpVtbl->Release( glpNum );
		
	if (!gbFullscreen && glpClipper)
	glpClipper->lpVtbl->Release( glpClipper );

    if( glpFrontBuffer != NULL )
	glpFrontBuffer->lpVtbl->Release( glpFrontBuffer );
	
     if( glpArtPalette != NULL )
	glpArtPalette->lpVtbl->Release( glpArtPalette );
	
    if( glpSplashPalette != NULL )
	glpSplashPalette->lpVtbl->Release( glpSplashPalette );

   if( !gbFullscreen && (glpBackBuffer != NULL ))
	glpBackBuffer->lpVtbl->Release( glpBackBuffer );

    if( glpDD != NULL )
        glpDD->lpVtbl->Release( glpDD );
}

void bltSplash( LPRECT rc)
{
    HRESULT     ddrval;
    HBITMAP     hbm;

    if( ( glpFrontBuffer == NULL ) ||
        ( glpSplashPalette == NULL ) ||
	( glpBackBuffer == NULL ) )
    {
        return;
    }

    // set the palette before loading the splash screen
	glpFrontBuffer->lpVtbl->SetPalette( glpFrontBuffer, glpSplashPalette );

    hbm = (HBITMAP)LoadImage( GetModuleHandle( NULL ), TEXT("SPLASH"), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION );
    if ( NULL == hbm )
	return;
	
    // if the surface is lost, DDCopyBitmap will fail and the surface will
    // be restored below.
    ddrval = DDCopyBitmap( glpBackBuffer, hbm, 0, 0, 0, 0 );

    DeleteObject( hbm );

    while( 1 )
    {
        if( NULL == rc)
		{
				ddrval = glpFrontBuffer->lpVtbl->Blt( glpFrontBuffer, 
				&grcWindow, glpBackBuffer, NULL, DDBLT_WAIT, NULL);
		}
		else
		{
				ddrval = glpFrontBuffer->lpVtbl->Blt( glpFrontBuffer, 
				&grcWindow, glpBackBuffer, rc, DDBLT_WAIT, NULL);
		}

        if( ddrval == DD_OK )
	    return;
        if( ddrval == DDERR_SURFACELOST )
            if( !RestoreSurfaces() )
                return;
        if( ddrval != DDERR_WASSTILLDRAWING )
            return;
    }
}

void bltScore( char *num, int x, int y )
{
    char *c;
    RECT    src;
    int     i;

    for(c=num; *c != '\0'; c++)
    {
        i = *c - '0';
        src.left = i*16;
        src.top = 0;
        src.right = src.left + 16;
        src.bottom = src.top + 16;
	bltObject( x, y, glpNum, &src, DDBLTFAST_SRCCOLORKEY );
        x += 16;
    }
}

void bltObject( int x, int y, LPDIRECTDRAWSURFACE surf, LPRECT src, DWORD flags )
{
    HRESULT ddrval;

    while( 1 )
    {
        ddrval = glpBackBuffer->lpVtbl->BltFast( glpBackBuffer, x, y, surf, src, flags );
        if( ddrval == DD_OK )
	    return;
        if( ddrval == DDERR_SURFACELOST )
            if( !RestoreSurfaces() )
                return;
        if( ddrval != DDERR_WASSTILLDRAWING )
            return;
    }
}

void EraseScreen( void )
{
    DDBLTFX     ddbltfx;
    HRESULT     ddrval;

    // Erase the background
    ddbltfx.dwSize = sizeof( ddbltfx );
    ddbltfx.dwFillColor = gdwFillColor;
    while( 1 )
    {
        ddrval = glpBackBuffer->lpVtbl->Blt( glpBackBuffer, NULL, NULL,
                 NULL, DDBLT_COLORFILL, &ddbltfx );

        if( ddrval == DD_OK )
        {
            break;
        }
        if( ddrval == DDERR_SURFACELOST )
        {
            if( !RestoreSurfaces() )
                return;
        }
        if( ddrval != DDERR_WASSTILLDRAWING )
        {
            return;
        }
    }
}

void FlipScreen( void )
{
    HRESULT     ddrval;

    // Flip the surfaces
	if (gbFullscreen)
	{
		while( 1 )
		{
			ddrval = glpFrontBuffer->lpVtbl->Flip( glpFrontBuffer, NULL, 0 );
			if( ddrval == DD_OK )
			{
				break;
			}
			if( ddrval == DDERR_SURFACELOST )
			{
				if( !RestoreSurfaces() )
				{
					return;
				}
			}
			if( ddrval != DDERR_WASSTILLDRAWING )
			{
				break;
			}
		}
    }
	else
	{
	    ddrval = IDirectDrawSurface_Blt(
                    glpFrontBuffer,          // dest surface
                    &grcWindow,              // dest rect
                    glpBackBuffer,           // src surface
                    NULL,                   // src rect (all of it)
                    DDBLT_WAIT,
                    NULL);
	}
}

BOOL RestoreSurfaces( void )
{
    HRESULT	ddrval;
    HBITMAP     hbm;

    ddrval = glpFrontBuffer->lpVtbl->Restore(glpFrontBuffer);
    if( ddrval != DD_OK )
        return FALSE;
	ddrval = glpBackBuffer->lpVtbl->Restore(glpBackBuffer);
	if( ddrval != DD_OK )
		return FALSE;
    ddrval = glpShip0->lpVtbl->Restore(glpShip0);
    if( ddrval != DD_OK )
        return FALSE;
    ddrval = glpShip1->lpVtbl->Restore(glpShip1);
    if( ddrval != DD_OK )
        return FALSE;
    ddrval = glpShip2->lpVtbl->Restore(glpShip2);
    if( ddrval != DD_OK )
        return FALSE;
    ddrval = glpShip3->lpVtbl->Restore(glpShip3);
    if( ddrval != DD_OK )
        return FALSE;
    ddrval = glpNum->lpVtbl->Restore(glpNum);
    if( ddrval != DD_OK )
        return FALSE;

    // Create and set the palette for the splash bitmap
    glpSplashPalette = DDLoadPalette( glpDD, TEXT("SPLASH") );
    if( NULL == glpSplashPalette )
	return FALSE;

    // Create and set the palette for the art bitmap
    glpArtPalette = DDLoadPalette( glpDD, TEXT("Duel8") );
    if( NULL == glpArtPalette )
	return FALSE;

    // set the palette before loading the art
    glpFrontBuffer->lpVtbl->SetPalette( glpFrontBuffer, glpArtPalette );

    hbm = (HBITMAP)LoadImage(GetModuleHandle(NULL), TEXT("Duel8"), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION );

    if( NULL == hbm )
        return FALSE;

    ddrval = DDCopyBitmap( glpShip0, hbm, 0, 0, 320, 128 );
    if( ddrval != DD_OK )
    {
        DeleteObject( hbm );
	return FALSE;
    }

    ddrval = DDCopyBitmap( glpShip1, hbm, 0, 128, 320, 128 );
    if( ddrval != DD_OK )
    {
        DeleteObject( hbm );
	return FALSE;
    }

    ddrval = DDCopyBitmap( glpShip2, hbm, 0, 256, 320, 128 );
    if( ddrval != DD_OK )
    {
        DeleteObject( hbm );
	return FALSE;
    }

    ddrval = DDCopyBitmap( glpShip3, hbm, 0, 384, 320, 128 );
    if( ddrval != DD_OK )
    {
        DeleteObject( hbm );
	return FALSE;
    }

    ddrval = DDCopyBitmap( glpNum, hbm, 0, 512, 320, 16 );
    if( ddrval != DD_OK )
    {
        DeleteObject( hbm );
	return FALSE;
    }

    DeleteObject( hbm );

    // set colorfill colors and color gdwKeys according to bitmap contents
    gdwFillColor = DDColorMatch( glpShip0, CLR_INVALID );
    
    DDSetColorKey( glpShip0, CLR_INVALID );
    DDSetColorKey( glpShip1, CLR_INVALID );
    DDSetColorKey( glpShip2, CLR_INVALID );
    DDSetColorKey( glpShip3, CLR_INVALID );
    DDSetColorKey( glpNum, CLR_INVALID );

    return TRUE;
}

void SetGamePalette(void)
{
	if (glpFrontBuffer)
		glpFrontBuffer->lpVtbl->SetPalette( glpFrontBuffer, glpArtPalette );
}

void FlipToGDI(void)
{
	if (glpDD) 
		glpDD->lpVtbl->FlipToGDISurface( glpDD );
}


