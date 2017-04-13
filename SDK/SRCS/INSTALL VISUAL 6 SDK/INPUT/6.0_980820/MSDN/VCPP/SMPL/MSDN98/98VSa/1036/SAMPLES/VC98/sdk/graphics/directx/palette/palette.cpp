/*==========================================================================
 *
 *  Copyright (C) 1995-1997 Microsoft Corporation. All Rights Reserved.
 *
 *  File:	palette.cpp
 *  Content:	Does some basic palette manipulation
 *
 ***************************************************************************/
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <windowsx.h>
#include <ddraw.h>
#include "resource.h"
#include "lbprintf.h"

static char	szClass[32]="DDTest1Class";
static char	szCaption[32]="DirectDraw Palette Test";

/*
 * DirectDraw objects we will use
 */
#define MAX_PALETTES	4
LPDIRECTDRAW		lpDD;
LPDIRECTDRAWSURFACE	lpDDPSurf;
LPDIRECTDRAWPALETTE	lpDDPal[MAX_PALETTES];
LPDIRECTDRAWPALETTE	lpDDPalCurr;

HWND			hWndMain;

BOOL			bIsExclusive = TRUE;
BOOL			bActive;


/*
 * doAttach
 *
 * attach palette to the primary surface
 */
static void doAttach( int index )
{
    HRESULT	ddrval;

    ddrval = lpDDPSurf->SetPalette( lpDDPal[index] );
    if( ddrval == DDERR_SURFACELOST )
    {
        lpDDPSurf->Restore();
        ddrval = lpDDPSurf->SetPalette( lpDDPal[index] );
    }
    if (!FAILED(ddrval))
    {
       LBPrintfDDRC( ddrval, "doAttach1: SetPalette" );
       lpDDPalCurr = lpDDPal[index];
    }
    else
    {
	LBPrintf( "Could not attach palette" );
	lpDDPalCurr = NULL;
    }

} /* doAttach */

/*
 * doDetach
 *
 * detach the current palette from the primary surface
 */
static void doDetach( void )
{
    HRESULT	ddrval;

    ddrval = lpDDPSurf->SetPalette( NULL );
    if( ddrval == DDERR_SURFACELOST )
    {
        lpDDPSurf->Restore();
        ddrval = lpDDPSurf->SetPalette( NULL );
    }
    LBPrintfDDRC( ddrval, "doDetach: SetPalette" );
    lpDDPalCurr = NULL;

} /* doDetach */

/*
 * doCycle
 *
 * cycle the current palette's red entries by 10
 */
static void doCycle( void )
{
    if( lpDDPalCurr != NULL )
    {
	#define ENTRIES 10
	#define BASE 0
	PALETTEENTRY	pe[ENTRIES];
	HRESULT		ddrval;
	int		i;

	/*
	 * display the original entries
	 */
	ddrval = lpDDPalCurr->GetEntries( 0, BASE, ENTRIES, pe );
	if( ddrval == DDERR_SURFACELOST )
	{
            lpDDPSurf->Restore();
	    ddrval = lpDDPalCurr->GetEntries( 0, BASE, ENTRIES, pe );
	}
	LBPrintfDDRC( ddrval, "GetEntries" );
	LBPrintf( "Old Entries" );
	for( i=0;i<ENTRIES;i++ )
	{
	    LBPrintf( "    pe[%d] (r,g,b) = (%d,%d,%d)", i, pe[i].peRed,
			pe[i].peGreen, pe[i].peBlue );
	}

	/*
	 * cycle the red values
	 */
	for( i=0;i<ENTRIES;i++ )
	{
	    pe[i].peRed = (BYTE) (((int)pe[i].peRed + 50) % 256);
	}
	ddrval = lpDDPalCurr->SetEntries( 0, BASE, ENTRIES, pe );
	if( ddrval == DDERR_SURFACELOST )
	{
            lpDDPSurf->Restore();
	    ddrval = lpDDPalCurr->SetEntries( 0, BASE, ENTRIES, pe );
	}
	LBPrintfDDRC( ddrval, "SetEntries" );

	/*
	 * display the new values
	 */
	ddrval = lpDDPalCurr->GetEntries( 0, BASE, ENTRIES, pe );
	if( ddrval == DDERR_SURFACELOST )
	{
            lpDDPSurf->Restore();
	    ddrval = lpDDPalCurr->GetEntries( 0, BASE, ENTRIES, pe );
	}
	LBPrintfDDRC( ddrval, "GetEntries" );
	LBPrintf( "New Entries" );
	for( i=0;i<ENTRIES;i++ )
	{
	    LBPrintf( "    pe[%d] (r,g,b) = (%d,%d,%d)", i, pe[i].peRed,
			pe[i].peGreen, pe[i].peBlue );
	}
    }
    else
    {
	LBPrintf( "No palette attached" );
    }

} /* doCycle */

/*
 * resetExclusiveAndPalettes
 *
 * Sets exclusive mode to the desired value, and the rebuilds
 * the palettes.
 *
 * Palettes in exclusive mode bypass GDI and go directly to the display
 * driver, so the performance is much higher.
 */
static BOOL resetExclusiveAndPalettes( BOOL excl )
{
    LPPALETTEENTRY	ppe;
    int			i;
    HRESULT		ddrval;

    /*
     * create palette entries
     */
    ppe = (LPPALETTEENTRY) LocalAlloc( LPTR, sizeof( PALETTEENTRY ) * 256 );
    if( ppe == NULL )
    {
	return FALSE;
    }

    /*
     * release existing palettes
     */
    for( i=0;i<MAX_PALETTES;i++ )
    {
	if( lpDDPal[i] != NULL )
	{
	    ddrval = lpDDPal[i]->Release();
	    LBPrintfDDRC( ddrval, "Release" );
	    lpDDPal[i] = NULL;
	}
    }

    /*
     * No current palette any more.
     */
    lpDDPalCurr = NULL;

    if( excl )
    {
	ddrval = lpDD->SetCooperativeLevel( hWndMain, DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN );
    }
    else
    {
	ddrval = lpDD->SetCooperativeLevel( hWndMain, DDSCL_NORMAL );
    }
        
    LBPrintfDDRC( ddrval, "SetCooperativeLevel" );

    /*
     * set up 4 palettes
     */
    ppe[0].peRed = 0;
    ppe[0].peGreen = 0;
    ppe[0].peBlue = 0;
    ppe[255].peRed = 255;
    ppe[255].peGreen = 255;
    ppe[255].peBlue = 255;

    for( i=1;i<255;i++ )
    {
	ppe[i].peRed = 0;
	ppe[i].peGreen = 0;
	ppe[i].peBlue = 0;
    }
    ddrval = lpDD->CreatePalette( DDPCAPS_8BIT, ppe, &lpDDPal[0], NULL );
    LBPrintfDDRC( ddrval, "CreatePalette" );

    for( i=1;i<255;i++ )
    {
	ppe[i].peRed = 0;
	ppe[i].peGreen = 255;
	ppe[i].peBlue = 255;
    }
    ddrval = lpDD->CreatePalette( DDPCAPS_8BIT, ppe, &lpDDPal[1], NULL );
    LBPrintfDDRC( ddrval, "CreatePalette" );

    for( i=1;i<255;i++ )
    {
	ppe[i].peRed = 255;
	ppe[i].peGreen = 255;
	ppe[i].peBlue = 0;
    }
    ddrval = lpDD->CreatePalette( DDPCAPS_8BIT, ppe, &lpDDPal[2], NULL );
    LBPrintfDDRC( ddrval, "CreatePalette" );

    for( i=1;i<255;i++ )
    {
	ppe[i].peRed = 255;
	ppe[i].peGreen = 0;
	ppe[i].peBlue = 255;
    }
    ddrval = lpDD->CreatePalette( DDPCAPS_8BIT, ppe, &lpDDPal[3], NULL );
    LBPrintfDDRC( ddrval, "CreatePalette" );
    LocalFree( ppe );

    for( i=0;i<MAX_PALETTES;i++ )
    {
	LBPrintf( "lpDDPal %d = %08lx", i+1, lpDDPal[i] );
    }
    return TRUE;

} /* resetExclusiveAndPalettes */

/*
 * WindowProc
 *
 * Messages for our window are handled here
 */
LRESULT CALLBACK WindowProc( HWND hWnd, unsigned uMsg, WPARAM wParam, LPARAM lParam )
{

    switch( uMsg )
    {
    case WM_COMMAND:
	switch( LOWORD( wParam ) )
	{
	case IDM_EXCLUSIVE:
	    bIsExclusive = !bIsExclusive;
	    resetExclusiveAndPalettes( bIsExclusive );
	    break;
	case IDM_ATTACH1:
	case IDM_ATTACH2:
	case IDM_ATTACH3:
	case IDM_ATTACH4:
	    doAttach( LOWORD( wParam ) - IDM_ATTACH1 );
	    break;
	case IDM_DETACH:
	    doDetach();
	    break;
	case IDM_CYCLE:
	    doCycle();
	    break;
	case IDM_CLEAR:
	    LBClear();
	    break;
	case IDM_EXIT:
	    DestroyWindow( hWnd );
	    break;
	}
	break;

    case WM_PAINT:
    {
	PAINTSTRUCT	ps;

	BeginPaint( hWnd, &ps );
	EndPaint( hWnd, &ps );
	break;
    }

    case WM_INITMENU:
	CheckMenuItem( (HMENU) wParam, IDM_EXCLUSIVE, MF_BYCOMMAND |
			(bIsExclusive ? MF_CHECKED:MF_UNCHECKED) );
	break;

    case WM_SIZE:
	/*
	 * resize our message listbox
	 */
	LBSize( LOWORD( lParam ), HIWORD( lParam ) );
	break;

    case WM_DESTROY:
	/*
	 * free all DirectDraw objects
	 */
	if( lpDD != NULL )
	{
	    int i;

	    for( i=0;i<MAX_PALETTES;i++ )
	    {
		if( lpDDPal[i] != NULL )
		{
		    lpDDPal[i]->Release();
		    lpDDPal[i] = NULL;
		}
	    }

	    if( lpDDPSurf != NULL )
	    {
		lpDDPSurf->Release();
		lpDDPSurf = NULL;
	    }
	    lpDD->Release();
	    lpDD = NULL;
	}
	PostQuitMessage( 0 );
	break;

    default:
	return DefWindowProc( hWnd, uMsg, wParam, lParam );
    }
    return 0L;

} /* WindowProc */

/*
 * doInit - do work required for every instance of the application:
 *		  create the window, initialize data
 */
static BOOL doInit( HINSTANCE hInstance, int nCmdShow )
{
    WNDCLASS		wc;
    HRESULT		ddrval;
    DDSURFACEDESC	ddsd;

    /*
     * set up and register window class
     */
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = (WNDPROC) WindowProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = sizeof( DWORD );
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon( hInstance, IDI_APPLICATION );
    wc.hCursor = LoadCursor( NULL, IDC_ARROW );
    wc.hbrBackground = (HBRUSH)GetStockObject( WHITE_BRUSH );
    wc.lpszMenuName = MAKEINTRESOURCE( IDR_MENU );
    wc.lpszClassName = szClass;
    if( !RegisterClass( &wc ) )
    {
	return FALSE;
    }
    
    /*
     * create a window
     */
    hWndMain = CreateWindow(
	szClass,		// class
	szCaption,		// caption
	WS_OVERLAPPEDWINDOW,	// style 
	CW_USEDEFAULT,		// x pos
	CW_USEDEFAULT,		// y pos
	CW_USEDEFAULT,		// width
	CW_USEDEFAULT,		// height
	NULL,			// parent window
	NULL,			// menu 
	hInstance,		// instance
	NULL			// parms
	);
		    
    if( !hWndMain )
    {
	return FALSE;
    }

    LBCreate( hWndMain, 100 );

    ShowWindow( hWndMain, nCmdShow );
    UpdateWindow( hWndMain );

    /*
     * create the main DirectDraw object
     */
    ddrval = DirectDrawCreate( NULL, &lpDD, NULL );
    LBPrintfDDRC( ddrval, "DirectDrawCreate" );
    if( ddrval != DD_OK )
    {
	DestroyWindow( hWndMain );
	return FALSE;
    }

    ddrval = lpDD->SetCooperativeLevel( hWndMain, DDSCL_NORMAL );

    /*
     * create the primary surface
     */
    ddsd.dwSize = sizeof( ddsd );
    ddsd.dwFlags = DDSD_CAPS;
    ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;
    ddrval = lpDD->CreateSurface( &ddsd, &lpDDPSurf, NULL );
    LBPrintfDDRC( ddrval, "CreateSurface" );
    if( ddrval != DD_OK )
    {
	lpDD->Release();
	DestroyWindow( hWndMain );
	return FALSE;
    }

    /*
     * set up palettes
     */
    if( !resetExclusiveAndPalettes( bIsExclusive ) )
    {
	lpDDPSurf->Release();
	lpDD->Release();
	DestroyWindow( hWndMain );
	return FALSE;
    }
    
    return TRUE;
			
} /* doInit */

/*
 * WinMain - initialization, message loop
 */
int PASCAL WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
			LPSTR lpCmdLine, int nCmdShow)
{
    MSG		msg;

    hPrevInstance = hPrevInstance;
    lpCmdLine = lpCmdLine;

    if( !doInit( hInstance, nCmdShow ) )
    {
	return FALSE;
    }

    while( GetMessage( &msg, NULL, NULL, NULL ) )
    {
	TranslateMessage( &msg );
	DispatchMessage( &msg );
    }

    return( msg.wParam );

} /* WinMain */
