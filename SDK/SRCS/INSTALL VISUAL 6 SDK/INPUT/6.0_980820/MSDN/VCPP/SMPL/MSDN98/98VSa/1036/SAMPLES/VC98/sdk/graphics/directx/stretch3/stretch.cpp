/*==========================================================================
 *
 *  Copyright (C) 1995-1997 Microsoft Corporation. All Rights Reserved.
 *
 *  File:       stretch.cpp
 *
 *  stretch with multimonitor support
 *
 ***************************************************************************/

#define NAME "Stretch"
#define TITLE "Stretch"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <windowsx.h>
#include <ddraw.h>
#include "resource.h"
#include "ddutil2.h"
#include "ddmm.h"

#define SIZEX	64
#define SIZEY	64
char *szBitmap = "DONUT";

HWND		hwnd1;
HWND		hwnd2;
DWORD           UpdateDelay = 100;

LPDIRECTDRAW2		lpDDArtWork;		// DirectDraw object
LPDIRECTDRAWSURFACE3	lpDDSArtWorkOriginal;	
LPDIRECTDRAWSURFACE3	lpDDSArtWork;	
LPDIRECTDRAWPALETTE	lpDDPal = 0;	// DirectDraw palette

LPDIRECTDRAW2		lpDD1;		// DirectDraw object
LPDIRECTDRAWSURFACE3	lpDDSPrimary1;	// DirectDraw primary surface
LPDIRECTDRAWSURFACE3	lpDDSOne1;	// Offscreen surface 1
LPDIRECTDRAWCLIPPER     lpClipper1;      // clipper for primary
DWORD			ThdId1;

LPDIRECTDRAW2		lpDD2;		// DirectDraw object
LPDIRECTDRAWSURFACE3	lpDDSPrimary2;	// DirectDraw primary surface
LPDIRECTDRAWSURFACE3	lpDDSOne2;	// Offscreen surface 1
LPDIRECTDRAWCLIPPER     lpClipper2;      // clipper for primary
DWORD			ThdId2;

volatile int 			SpinLock = 0;
BOOL                    bActive;        // is application active?
VOID *                  lpArtWork;      // shared art work

/* multimon stuff
*/
int     MyDevice1;
char    MyDeviceName1[128];
RECT    MyDeviceRect1;
int     MyDevice2;
char    MyDeviceName2[128];
RECT    MyDeviceRect2;

typedef struct
{
    HINSTANCE hInstance;
    int nCmdShow;
}Thread_Info;

Thread_Info ThdInfo;

BOOL ddInit(HWND);
BOOL ddInit1(HWND);

/*
 * restoreAll
 *
 * restore all lost objects
 */
BOOL restoreAll( void )
{
    return (
           lpDDSPrimary1->Restore() &&
           lpDDSPrimary2->Restore() &&
           lpDDSOne1->Restore() &&
           lpDDSOne2->Restore() 
		   );
} /* restoreAll */

/*
 * updateFrame
 * 
 * Decide what needs to be blitted next, wait for flip to complete,
 * then flip the buffers.
 */
void updateFrame( void )
{
    static DWORD	lastTickCount = 0;
    static int		currentFrame = 0;
    static BOOL         haveBackground = FALSE;
    DWORD		thisTickCount;
    RECT		rcRect;
    RECT		destRect;
    HRESULT		ddrval;
    POINT               pt;

    thisTickCount = GetTickCount();
    if((thisTickCount - lastTickCount) <= UpdateDelay)
    {
	return;
    }

    // Move to next frame;
    lastTickCount = thisTickCount;
    currentFrame++;
    if(currentFrame > 59)
    {
        currentFrame = 0;
    }

    // Blit the stuff for the next frame
    rcRect.left   = currentFrame%10*64;
    rcRect.top    = currentFrame/10*64;
    rcRect.right  = currentFrame%10*64 + 64;
    rcRect.bottom = currentFrame/10*64 + 64;

    GetClientRect( hwnd1, &destRect );
    if (destRect.right  < 64) destRect.right = 64;
    if (destRect.bottom < 64)  destRect.bottom = 64;

    pt.x = pt.y = 0;
    ClientToScreen( hwnd1, &pt );
    pt.x -= MyDeviceRect1.left;
    pt.y -= MyDeviceRect1.top;
    OffsetRect(&destRect, pt.x, pt.y);


    while( 1 )
    {
        ddrval = lpDDSPrimary1->Blt( &destRect, lpDDSOne1, &rcRect, 0, NULL );

        if( ddrval == DD_OK )
        {
            break;
        }
        if( ddrval == DDERR_SURFACELOST )
        {
            if(!restoreAll())
            {
                return;
            }
     	}
        if( ddrval != DDERR_WASSTILLDRAWING )
        {
            return;
        }
    };
    if(ddrval != DD_OK)
    {
        return;
    }
} /* updateFrame */

/*
 * updateFrame1
 * 
 * Decide what needs to be blitted next, wait for flip to complete,
 * then flip the buffers.
 */
void updateFrame1( void )
{
    static DWORD	lastTickCount = 0;
    static int		currentFrame = 0;
    static BOOL         haveBackground = FALSE;
    DWORD		thisTickCount;
    RECT		rcRect;
    RECT		destRect;
    HRESULT		ddrval;
    POINT               pt;

    thisTickCount = GetTickCount();
    if((thisTickCount - lastTickCount) <= UpdateDelay)
    {
	return;
    }

    // Move to next frame;
    lastTickCount = thisTickCount;
    currentFrame++;
    if(currentFrame > 59)
    {
        currentFrame = 0;
    }

    // Blit the stuff for the next frame
    rcRect.left   = currentFrame%10*64;
    rcRect.top    = currentFrame/10*64;
    rcRect.right  = currentFrame%10*64 + 64;
    rcRect.bottom = currentFrame/10*64 + 64;

    GetClientRect( hwnd2, &destRect );
    if (destRect.right  < 64) destRect.right = 64;
    if (destRect.bottom < 64)  destRect.bottom = 64;

    pt.x = pt.y = 0;
    ClientToScreen( hwnd2, &pt );
    pt.x -= MyDeviceRect2.left;
    pt.y -= MyDeviceRect2.top;
    OffsetRect(&destRect, pt.x, pt.y);


    while( 1 )
    {
        ddrval = lpDDSPrimary2->Blt( &destRect, lpDDSOne2, &rcRect, 0, NULL );

        if( ddrval == DD_OK )
        {
            break;
        }
        if( ddrval == DDERR_SURFACELOST )
        {
            if(!restoreAll())
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
} /* updateFrame1 */


/*
 * finiObjects
 *
 * finished with all objects we use; release them
 */
static void finiObjects( BOOL fKillDD )
{
    if( lpDDSPrimary1 != NULL )
    {
        lpDDSPrimary1->Release();
        lpDDSPrimary1 = NULL;
    }
    if( lpDDSOne1 != NULL )
    {
        lpDDSOne1->Release();
        lpDDSOne1 = NULL;
    }
    if( lpDDPal != NULL )
    {
        lpDDPal->Release();
        lpDDPal = NULL;
    }
    if( fKillDD && lpDD1 != NULL )
    {
        lpDD1->Release();
        lpDD1 = NULL;
    }
} /* finiObjects */
static void finiObjects1( BOOL fKillDD )
{
    if( lpDDSPrimary2 != NULL )
    {
        lpDDSPrimary2->Release();
        lpDDSPrimary2 = NULL;
    }
    if( lpDDSOne2 != NULL )
    {
        lpDDSOne2->Release();
        lpDDSOne2 = NULL;
    }
    if( lpDDPal != NULL )
    {
        lpDDPal->Release();
        lpDDPal = NULL;
    }
    if( fKillDD && lpDD2 != NULL )
    {
        lpDD2->Release();
        lpDD2 = NULL;
    }
} /* finiObjects1 */

long FAR PASCAL WindowProc( HWND hWnd, UINT message, 
			    WPARAM wParam, LPARAM lParam )
{
    RECT  rc;

    switch( message )
    {
    case WM_ACTIVATEAPP:
    	bActive = wParam;
	break;

    case WM_SIZE:
    case WM_MOVE:
        if(hWnd == hwnd1)
        {
            if (MyDevice1 != DirectDrawDeviceFromWindow(hWnd,NULL,NULL))
            {
                ddInit(hwnd1);
            }
        }
        if(hWnd == hwnd2)
        {
            if (MyDevice2 != DirectDrawDeviceFromWindow(hWnd,NULL,NULL))
            {
                ddInit1(hwnd2);
            }
        }
        break;

    case WM_PALETTECHANGED:
        if ((HWND)wParam == hWnd)
            break;
        // fall through to WM_QUERYNEWPALETTE
    case WM_QUERYNEWPALETTE:
/*--------------------------------------------------------**
**  Er um, truth is this app is broken on palette change  **
**  see ddInitArtWork to understand why.                  **
**--------------------------------------------------------*/
        break;

    case WM_CREATE:
        break;

    case WM_GETMINMAXINFO:
        ((MINMAXINFO*)lParam)->ptMinTrackSize.x = SIZEX;
        ((MINMAXINFO*)lParam)->ptMinTrackSize.y = SIZEY;
        return 0;

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
        if(hWnd == hwnd1)
        {
            finiObjects(TRUE);
	    }
        if(hWnd == hwnd2)
        {
            finiObjects1(TRUE);
		}
	PostQuitMessage( 0 );
        break;

    case WM_KEYUP:
        if (wParam >= '1' && wParam <= '9')
        {
            SetRect(&rc, 0, 0, SIZEX*(wParam-'0'), SIZEY*(wParam-'0'));
            goto size_me;
        }
        break;

    case WM_COMMAND: 
    	switch(LOWORD(wParam))
	{
	    case ID_ROTATION_STOP:	    
		UpdateDelay = 0x7fffffff;
		break;
	    case ID_ROTATION_SLOW:	    
		UpdateDelay = 200;
		break;
	    case ID_ROTATION_FAST:	    
                UpdateDelay = 100;
		break;
	    case ID_FILE_EXIT:	    
                PostMessage( hWnd, WM_CLOSE, 0, 0L );
	        break;
		    
            case ID_SIZE_1X1: SetRect(&rc, 0, 0, SIZEX*1, SIZEY*1); goto size_me;
            case ID_SIZE_2X1: SetRect(&rc, 0, 0, SIZEX*2, SIZEY*1); goto size_me;
            case ID_SIZE_3X1: SetRect(&rc, 0, 0, SIZEX*3, SIZEY*1); goto size_me;
            case ID_SIZE_1X2: SetRect(&rc, 0, 0, SIZEX*1, SIZEY*2); goto size_me;
            case ID_SIZE_2X2: SetRect(&rc, 0, 0, SIZEX*2, SIZEY*2); goto size_me;
            case ID_SIZE_3X2: SetRect(&rc, 0, 0, SIZEX*3, SIZEY*2); goto size_me;
            case ID_SIZE_1X3: SetRect(&rc, 0, 0, SIZEX*1, SIZEY*3); goto size_me;
            case ID_SIZE_2X3: SetRect(&rc, 0, 0, SIZEX*2, SIZEY*3); goto size_me;
	    case ID_SIZE_3X3: SetRect(&rc, 0, 0, SIZEX*3, SIZEY*3); goto size_me;
size_me:
                AdjustWindowRectEx(&rc, GetWindowLong(hWnd, GWL_STYLE),
		    GetMenu(hWnd) != NULL, GetWindowLong(hWnd, GWL_EXSTYLE));
		SetWindowPos(hWnd, NULL, 0, 0, rc.right-rc.left, rc.bottom-rc.top,
                    SWP_NOZORDER|SWP_NOMOVE|SWP_NOACTIVATE);
		break;
	    } 
	    break;
    }

    return DefWindowProc(hWnd, message, wParam, lParam);

} /* WindowProc */

/*
 * This function is called if the initialization function fails
 */
BOOL initFail( HWND hwnd )
{
    finiObjects(TRUE);
    finiObjects1(TRUE);
    MessageBox( hwnd, "DirectDraw Init FAILED", TITLE, MB_OK );
    DestroyWindow( hwnd );
    return FALSE;

} /* initFail */

/*
 * ddInit
 */
BOOL ddInit( HWND hwnd )
{
    DDSURFACEDESC	ddsd;
    HRESULT             ddrval;
    char                ach[128];

    /*
     * clean up our mess
     */
    finiObjects(TRUE);

    MyDevice1 = DirectDrawDeviceFromWindow(hwnd,MyDeviceName1,&MyDeviceRect1);

    if (MyDeviceName1[0] == 0) lstrcpy(MyDeviceName1, "(none)");
    wsprintf(ach, "%s - %s", TITLE, MyDeviceName1);
    SetWindowText(hwnd1, ach);

    /*
     * create the main DirectDraw object
     */
    LPDIRECTDRAW lpDDT;
    lpDDT = DirectDrawCreateFromWindow(hwnd);
    if( lpDDT == NULL )
    {
	    return initFail(hwnd);
    }
    ddrval = lpDDT->QueryInterface(IID_IDirectDraw2, (void**)&lpDD1);

    if( lpDD1 == NULL )
    {
	    return initFail(hwnd);
    }
    lpDDT->Release();
    
    ddrval = lpDD1->SetCooperativeLevel( hwnd, DDSCL_NORMAL );

    // Create the primary surface
    ddsd.dwSize = sizeof( ddsd );
    ddsd.dwFlags = DDSD_CAPS;
    ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;

    LPDIRECTDRAWSURFACE lpDDSTemp;
    ddrval = lpDD1->CreateSurface( &ddsd, &lpDDSTemp, NULL );
    if( ddrval != DD_OK )
    {
        return initFail(hwnd);
    }
    ddrval = lpDDSTemp->QueryInterface(IID_IDirectDrawSurface3, (void**)&lpDDSPrimary1);
    if( ddrval != DD_OK )
    {
        return initFail(hwnd);
    }
    lpDDSTemp->Release();

    // create a clipper for the primary surface
    ddrval = lpDD1->CreateClipper( 0, &lpClipper1, NULL );
    if( ddrval != DD_OK )
    {
        return initFail(hwnd);
    }

    ddrval = lpClipper1->SetHWnd( 0, hwnd );
    if( ddrval != DD_OK )
    {
        return initFail(hwnd);
    }

    ddrval = lpDDSPrimary1->SetClipper( lpClipper1 );
    if( ddrval != DD_OK )
    {
        return initFail(hwnd);
    }

     // load our palette                                     
     lpDDPal = DDLoadPalette2(lpDD1, szBitmap);              
                                                             
     // make sure to set the palette before loading bitmaps. 
     if (lpDDPal)                                            
        lpDDSPrimary1->SetPalette(lpDDPal);                    

    // load our bitmap
    ZeroMemory(&ddsd, sizeof(ddsd));
    ddsd.dwSize = sizeof(ddsd);
    ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT |DDSD_WIDTH;
    ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_SYSTEMMEMORY;
    ddsd.dwWidth = 2;
    ddsd.dwHeight = 2;

    if (lpDD1->CreateSurface(&ddsd, &lpDDSTemp, NULL) != DD_OK)
    {
        OutputDebugString("CreateSurf failed");
        return initFail(hwnd);
    }
    //CreateSurface must set SurfaceMemory Flag
    ZeroMemory(&ddsd, sizeof(ddsd));
    ddsd.dwSize = sizeof(ddsd);
    ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT |DDSD_WIDTH;
    ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_SYSTEMMEMORY;
    ddsd.dwWidth = 2;  // It's going away anyway
    ddsd.dwHeight = 2;
    if (lpDD1->CreateSurface(&ddsd, &lpDDSTemp, NULL) != DD_OK)
    {
        OutputDebugString("CreateSurf failed");
        return initFail(hwnd);
    };

    if (lpDDSTemp->QueryInterface(IID_IDirectDrawSurface3,(void**)&lpDDSOne1) != DD_OK)
    {
        OutputDebugString("QueryInterface failed");
        return initFail(hwnd);
    }
    lpDDSTemp->Release();

    if( lpDDSOne1 == NULL )
    {
	    return initFail(hwnd);
    }

    //Get the size of the surface
    DDSURFACEDESC DDSDesc;
    memset(&DDSDesc,0,sizeof(DDSURFACEDESC));
    DDSDesc.dwSize = sizeof(DDSURFACEDESC);
    DDSDesc.dwFlags =  DDSD_WIDTH | DDSD_HEIGHT | DDSD_PITCH;
    ddrval = lpDDSArtWork->GetSurfaceDesc(&DDSDesc);
    if( ddrval != DD_OK )
    {
        return initFail(hwnd);
    }

    //Set the memory into the surface
    DDSDesc.dwFlags =  DDSD_LPSURFACE | DDSD_WIDTH | DDSD_HEIGHT | DDSD_PITCH;
    DDSDesc.lpSurface = lpArtWork;    
    
    ddrval = lpDDSOne1->SetSurfaceDesc(&DDSDesc,0);
    if( ddrval != DD_OK )
    {
        return initFail(hwnd);
    }


    return TRUE;
} /* doInit */


/*
 * ddInit1
 */
BOOL ddInit1( HWND hwnd )
{
    DDSURFACEDESC	ddsd;
    HRESULT             ddrval;
    char                ach[128];

    /*
     * clean up our mess
     */
    finiObjects1(TRUE);

    MyDevice2 = DirectDrawDeviceFromWindow(hwnd,MyDeviceName2,&MyDeviceRect2);

    if (MyDeviceName2[0] == 0) lstrcpy(MyDeviceName2, "(none)");
    wsprintf(ach, "%s - %s", TITLE, MyDeviceName2);
    SetWindowText(hwnd, ach);

    /*
     * create the main DirectDraw object
     */
    LPDIRECTDRAW lpDDT;
    lpDDT = DirectDrawCreateFromWindow(hwnd);
    if( lpDDT == NULL )
    {
	    return initFail(hwnd);
    }
    ddrval = lpDDT->QueryInterface(IID_IDirectDraw2, (void**)&lpDD2);

    if( lpDD2 == NULL )
    {
	    return initFail(hwnd);
    }
    lpDDT->Release();
    ddrval = lpDD2->SetCooperativeLevel( hwnd, DDSCL_NORMAL );

    // Create the primary surface
    ddsd.dwSize = sizeof( ddsd );
    ddsd.dwFlags = DDSD_CAPS;
    ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;

    LPDIRECTDRAWSURFACE lpDDSTemp;
    ddrval = lpDD2->CreateSurface( &ddsd, &lpDDSTemp, NULL );
    if( ddrval != DD_OK )
    {
        return initFail(hwnd);
    }
    ddrval = lpDDSTemp->QueryInterface(IID_IDirectDrawSurface3, (void**)&lpDDSPrimary2);
    if( ddrval != DD_OK )
    {
        return initFail(hwnd);
    }
    lpDDSTemp->Release();

    // create a clipper for the primary surface
    ddrval = lpDD2->CreateClipper( 0, &lpClipper2, NULL );
    if( ddrval != DD_OK )
    {
        return initFail(hwnd);
    }

    ddrval = lpClipper2->SetHWnd( 0, hwnd );
    if( ddrval != DD_OK )
    {
        return initFail(hwnd);
    }

    ddrval = lpDDSPrimary2->SetClipper( lpClipper2 );
    if( ddrval != DD_OK )
    {
        return initFail(hwnd);
    }

    // load our palette                                     
    lpDDPal = DDLoadPalette2(lpDD2, szBitmap);              
                                                             
    // make sure to set the palette before loading bitmaps. 
    if (lpDDPal)                                            
        lpDDSPrimary2->SetPalette(lpDDPal);                    
                                                             

    //CreateSurface must set SurfaceMemory Flag
    ZeroMemory(&ddsd, sizeof(ddsd));
    ddsd.dwSize = sizeof(ddsd);
    ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT |DDSD_WIDTH;
    ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_SYSTEMMEMORY;
    ddsd.dwWidth = 2;  // It's going away anyway
    ddsd.dwHeight = 2;
    if (lpDD2->CreateSurface(&ddsd, &lpDDSTemp, NULL) != DD_OK)
    {
        OutputDebugString("CreateSurf failed");
        return initFail(hwnd);
    };

    if (lpDDSTemp->QueryInterface(IID_IDirectDrawSurface3,(void**)&lpDDSOne2) != DD_OK)
    {
        OutputDebugString("QueryInterface failed");
        return initFail(hwnd);
    }
    lpDDSTemp->Release();

    if( lpDDSOne2 == NULL )
    {
	    return initFail(hwnd);
    }

    //Get the size of the surface
    DDSURFACEDESC DDSDesc;
    memset(&DDSDesc,0,sizeof(DDSURFACEDESC));
    DDSDesc.dwSize = sizeof(DDSURFACEDESC);
    DDSDesc.dwFlags =  DDSD_WIDTH | DDSD_HEIGHT | DDSD_PITCH;
    ddrval = lpDDSArtWork->GetSurfaceDesc(&DDSDesc);
    if( ddrval != DD_OK )
    {
        return initFail(hwnd);
    }

    //Set the memory into the surface
    DDSDesc.dwFlags =  DDSD_LPSURFACE | DDSD_WIDTH | DDSD_HEIGHT | DDSD_PITCH;
    DDSDesc.lpSurface = lpArtWork;    
    
    ddrval = lpDDSOne2->SetSurfaceDesc(&DDSDesc,0);
    if( ddrval != DD_OK )
    {
        return initFail(hwnd);
    }

    return TRUE;
} /* doInit1 */



/*-------------------------------------------------------**
** This code assumes that if more than one monitor exist **
** that they have the same color depth, else sharing     **
** artwork doesn't make sense                            **
**-------------------------------------------------------*/
BOOL ddInitArtWork(void )
{
    DDSURFACEDESC	ddsd;
    HRESULT             ddrval;

    /*
     * create the main DirectDraw object
     */
    LPDIRECTDRAW lpDDT;
    ddrval = DirectDrawCreate(NULL,&lpDDT,0);
    if( ddrval != DD_OK )
    {
	    return initFail(NULL);
    }
    ddrval = lpDDT->QueryInterface(IID_IDirectDraw2, (void**)&lpDDArtWork);
    if( ddrval != DD_OK )
    {
	    return initFail(NULL);
    }

    lpDDT->Release();
    ddrval = lpDDArtWork->SetCooperativeLevel( NULL, DDSCL_NORMAL );

    //CreateSurface must set SurfaceMemory Flag
    LPDIRECTDRAWSURFACE lpDDSTemp;
    ZeroMemory(&ddsd, sizeof(ddsd));
    ddsd.dwSize = sizeof(ddsd);
    ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT |DDSD_WIDTH;
    ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_SYSTEMMEMORY;
    ddsd.dwWidth = 2;  // It's going away anyway
    ddsd.dwHeight = 2;
    if (lpDDArtWork->CreateSurface(&ddsd, &lpDDSTemp, NULL) != DD_OK)
    {
        OutputDebugString("CreateSurf failed");
        return initFail(NULL);
    };

    if (lpDDSTemp->QueryInterface(IID_IDirectDrawSurface3,(void**)&lpDDSArtWork) != DD_OK)
    {
        OutputDebugString("QueryInterface failed");
        return initFail(NULL);
    }
    lpDDSTemp->Release();

    if( lpDDSArtWork == NULL )
    {
	    return initFail(NULL);
    }

    // load our palette
    lpDDPal = DDLoadPalette2(lpDDArtWork, szBitmap);

    //copy the preconverted bits to the surface
    lpDDSArtWorkOriginal = DDLoadBitmap2(lpDDArtWork, szBitmap, 0, 0);
    // make sure to set the palette before loading bitmaps.
    if (lpDDPal != 0)
	lpDDSArtWorkOriginal->SetPalette(lpDDPal);
    //Get the size of the surface
    DDSURFACEDESC DDSDesc;
    memset(&DDSDesc,0,sizeof(DDSURFACEDESC));
    DDSDesc.dwSize = sizeof(DDSURFACEDESC);
    DDSDesc.dwFlags =  DDSD_WIDTH | DDSD_HEIGHT | DDSD_PITCH;
    ddrval = lpDDSArtWorkOriginal->GetSurfaceDesc(&DDSDesc);
    if( ddrval != DD_OK )
    {
        return initFail(NULL);
    }

    //Alloc a surface.  The pitch must always be an integral number
    // of DWORDs, so we compute the theoretical pitch and then round it up.
    DDSDesc.lPitch =  DDSDesc.dwWidth*DDSDesc.ddpfPixelFormat.dwRGBBitCount/8;
    DDSDesc.lPitch = (DDSDesc.lPitch + 3) & ~3;

    lpArtWork = GlobalAlloc(GPTR, DDSDesc.lPitch * DDSDesc.dwHeight);

    //Set the memory into the surface
    DDSDesc.dwFlags =  DDSD_LPSURFACE | DDSD_WIDTH | DDSD_HEIGHT | DDSD_PITCH;
    DDSDesc.lpSurface = lpArtWork;    
    
    ddrval = lpDDSArtWork->SetSurfaceDesc(&DDSDesc,0);
    if( ddrval != DD_OK )
    {
        return initFail(NULL);
    }

    //copy the preconverted bits to the surface
    ddrval = lpDDSArtWork->Blt(NULL,lpDDSArtWorkOriginal,NULL,DDBLT_WAIT,NULL);
    if( ddrval != DD_OK )
    {
        return initFail(NULL);
    }
    return TRUE;
} /* doInitArt */


/*
 * doInit - do work required for every instance of the application:
 *		  create the window, initialize data
 */
static BOOL doInit( Thread_Info *thd)
//HINSTANCE hInstance, int nCmdShow )
{
    WNDCLASS		wc;
    MSG         msg;

    /*
     * set up and register window class
     */
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WindowProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = thd->hInstance;
    wc.hIcon = LoadIcon( thd->hInstance, IDI_APPLICATION );
    wc.hCursor = LoadCursor( NULL, IDC_ARROW );
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wc.lpszMenuName = NULL; // MAKEINTRESOURCE(IDR_MENU);
    wc.lpszClassName = NAME;
    RegisterClass( &wc );
    
    /*
     * create a window
     */
    hwnd1 = CreateWindowEx(
	0,
	NAME,
	TITLE,
        WS_POPUP | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME,
	CW_USEDEFAULT,
	CW_USEDEFAULT,
	128,
	128,
	NULL,
	NULL,
	thd->hInstance,
	NULL );

    if( !hwnd1 )
    {
	return FALSE;
    }

    PostMessage(hwnd1, WM_COMMAND, ID_SIZE_3X3, 0);

    ShowWindow( hwnd1, thd->nCmdShow );
    UpdateWindow( hwnd1 );

    /*
     * create the direct draw objects
     */
    ddInit(hwnd1);

    // Wait for both window to get ready
    SpinLock ++;
	while(SpinLock <2);

    while( 1 )
    {
		if( PeekMessage( &msg, NULL, 0, 0, PM_NOREMOVE ) )
		{
		    if( !GetMessage( &msg, NULL, 0, 0 ) )
			return msg.wParam;
		    TranslateMessage(&msg); 
		    DispatchMessage(&msg);
		}
	        else
		{
		    updateFrame();
		}
    }
}

static BOOL doInit1(Thread_Info *thd)
//HINSTANCE hInstance, int nCmdShow )
{
    WNDCLASS		wc;
    MSG         msg;

    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WindowProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = thd->hInstance;
    wc.hIcon = LoadIcon( thd->hInstance, IDI_APPLICATION );
    wc.hCursor = LoadCursor( NULL, IDC_ARROW );
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wc.lpszMenuName = NULL; // MAKEINTRESOURCE(IDR_MENU);
    wc.lpszClassName = NAME;
    RegisterClass( &wc );


    /*
     * create the direct draw objects
     */


    hwnd2 = CreateWindowEx(
	0,
	NAME,
	TITLE,
        WS_POPUP | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME,
	CW_USEDEFAULT,
	CW_USEDEFAULT,
	128,
	128,
	NULL,
	NULL,
	thd->hInstance,
	NULL );

    if( !hwnd2 )
    {
	return FALSE;
    }

    PostMessage(hwnd2, WM_COMMAND, ID_SIZE_3X3, 0);

    ShowWindow( hwnd2, thd->nCmdShow );
    UpdateWindow( hwnd2 );

    /*
     * create the direct draw objects
     */
    ddInit1(hwnd2);

    // Wait for both window to get ready
    SpinLock ++;
	while(SpinLock <2);

    while( 1 )
    {
		if( PeekMessage( &msg, NULL, 0, 0, PM_NOREMOVE ) )
		{
		    if( !GetMessage( &msg, NULL, 0, 0 ) )
			return msg.wParam;
		    TranslateMessage(&msg); 
		    DispatchMessage(&msg);
		}
	        else
		{
		    updateFrame1();
		}
    }

} /* doInit */

/*
 * WinMain - initialization, message loop
 */
int PASCAL WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
			LPSTR lpCmdLine, int nCmdShow)
{
//    MSG         msg;
    HANDLE ThdHnd[2];

    ddInitArtWork();

    ThdInfo.hInstance = hInstance;
    ThdInfo.nCmdShow = nCmdShow;

    ThdHnd[0] = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)doInit,&ThdInfo,0,&ThdId1);
    ThdHnd[1] = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)doInit1,&ThdInfo,0,&ThdId2);

    WaitForMultipleObjects((DWORD)2,ThdHnd,TRUE,(DWORD)-1);
    if( lpDDSArtWork != NULL )
    {
        lpDDSArtWork->Release();
        lpDDSArtWork = NULL;
    }
    if( lpDDSArtWorkOriginal != NULL )
    {
        lpDDSArtWorkOriginal->Release();
        lpDDSArtWorkOriginal = NULL;
    }
    if( lpDDPal != NULL )
    {
        lpDDPal->Release();
        lpDDPal = NULL;
    }
    if( lpDDArtWork != NULL )
    {
        lpDDArtWork->Release();
        lpDDArtWork = NULL;
    }
   // ExitThread(0);
    return TRUE;
} /* WinMain */
