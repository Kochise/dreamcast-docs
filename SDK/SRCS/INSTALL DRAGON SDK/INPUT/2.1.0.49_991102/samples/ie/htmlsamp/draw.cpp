/********************************************************************
 * draw.cpp
 *
 * Description
 *     DDraw wrappers and helpers.
 *     Also has the "window manager" system. The application can have
 *     multiple "screens" which can each have multiple "windows". A
 *     screen is a set of windows; you can switch displaying screens
 *     easily without having to move around all of the windows. A
 *     window is a rectangle on the screen and does not have to have
 *     an HWND.
 *     Also has the "drawing manager" system. Windows are displayed
 *     in Z order by calling the windows' respective Draw routines.
 *     Also has the "cursor manager" system. Cursor position, type,
 *     visiblity can be set for each screen.
 *     Also has the "joystick manager" system. When joystick messages
 *     are received, the window manager sends the message to the 
 *     appropriate window(s).
 ********************************************************************/

/********************************************************************
 * Includes
 ********************************************************************/
#include "headers.h"            // common headers
#include "window.h"             // CWindow
#include <wdm.h>                // PHYSICAL_ADDRESS

/********************************************************************
 * Structures
 ********************************************************************/
typedef struct _GDISurfaceInfo
{
    int           width;        // width of GDI surface
    int           height;       // height of GDI surface
    int           stride;       // pitch (distance to start of next line)
    unsigned long physicalAddr; // address of surface
} GDISurfaceInfo, *PGDISurfaceInfo;

/********************************************************************
 * Defines
 ********************************************************************/
#define GETGDIINFO  6500        // driver escape ID for GDI memory stuff

/********************************************************************
 * Global variables
 ********************************************************************/
LPDIRECTDRAW        g_pDD            = NULL;    // Direct Draw object
LPDIRECTDRAWSURFACE g_pDDSPrimary    = NULL;    // main DDraw surface
LPDIRECTDRAWSURFACE g_pDDSBack       = NULL;    // back frame surface
LPDIRECTDRAWSURFACE g_pDDSCursor     = NULL;    // cursor bitmap surface
LPDIRECTDRAWSURFACE g_pDDSDesktop    = NULL;    // GDI surface
LPDIRECTDRAWSURFACE g_pDDSTexture    = NULL;    // GDI surface
LPVOID              g_pGDIBits       = NULL;    // mapped space
HWND                g_hwndMain       = NULL;    // main application window
BOOL                g_f555           = FALSE;   // color model type
SIZE                g_szScreen       = { GetSystemMetrics(SM_CXSCREEN), 
                                         GetSystemMetrics(SM_CYSCREEN) };
                                                // size of screen
RECT                g_rcActiveScreen = { X_MARGIN, Y_MARGIN, 
                                         g_szScreen.cx - X_MARGIN, 
                                         g_szScreen.cy - Y_MARGIN };
                                                // active area of screen

/********************************************************************
 * Internal function prototypes
 ********************************************************************/
void InitGDIDesktop(void);
void DestroyAllWindows(void);

/********************************************************************
 * CreateDirectDraw
 *
 * Description
 *    Creates and initializes Direct Draw. Creates the GDI surface.
 *
 * Parameters
 *    hwndMain     main application window
 * 
 * Returns
 *    None
 ********************************************************************/
void CreateDirectDraw(HWND hwndMain)
{
    if (g_pDD || !hwndMain)
    {
        return;
    }

    // store main application window
    g_hwndMain = hwndMain;

    DDSURFACEDESC  ddsd;
    DDSCAPS        ddscaps;
    HRESULT        ddrval;

    // create Direct Draw object
    ddrval = DirectDrawCreate(NULL, &g_pDD, NULL);
    if (ddrval == DD_OK)
    {   
        // set up Direct Draw object
    	ddrval = g_pDD->SetCooperativeLevel(g_hwndMain, 
                        DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN);
        if (ddrval == DD_OK)
        {
            ddrval = g_pDD->SetDisplayMode(g_szScreen.cx, g_szScreen.cy, 16);
            if (ddrval == DD_OK)
            {
                // set up back buffer
                ddsd.dwSize = sizeof(ddsd);
                ddsd.dwFlags = DDSD_CAPS | DDSD_BACKBUFFERCOUNT;
                ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE | DDSCAPS_FLIP | 
                                      DDSCAPS_COMPLEX;
                ddsd.dwBackBufferCount = 1;
                ddrval = g_pDD->CreateSurface(&ddsd, &g_pDDSPrimary, NULL);
                if (ddrval == DD_OK)
                {
                    ddscaps.dwCaps = DDSCAPS_BACKBUFFER;
                    ddrval = g_pDDSPrimary->GetAttachedSurface(&ddscaps, 
                                                               &g_pDDSBack);

                    // check the format of the primary surface.  This app only 
                    // supports 5-5-5 and 5-6-5 formats.
                    if (g_pDDSPrimary->GetSurfaceDesc(&ddsd) == DD_OK) 
                    {
                        // choose the appropriate bitmap resource depending on 
                        // the format of the primary surface.
                        if ((ddsd.ddpfPixelFormat.dwRBitMask == 0x7c00) &&
                            (ddsd.ddpfPixelFormat.dwGBitMask == 0x03e0) &&
                            (ddsd.ddpfPixelFormat.dwBBitMask == 0x001f)) 
                        {
                            // 5-5-5 primary surface.
                            g_f555 = TRUE;
                        } 
                        else if ((ddsd.ddpfPixelFormat.dwRBitMask == 0xf800) &&
                                 (ddsd.ddpfPixelFormat.dwGBitMask == 0x07e0) &&
                                 (ddsd.ddpfPixelFormat.dwBBitMask == 0x001f)) {
                                 // We have a 5-6-5 primary surface.
                                 g_f555 = FALSE;
                        }
                        else
                        {
                            OutputDebugString(TEXT("Error: surface not 555 or 565\n"));
                        }
                    }

                    // create cursor bitmap icon strip surface
                    g_pDDSCursor = CreateBitmapSurface(TEXT("Cursor"), 
                                   CURSOR_SIZE * CURSOR_FRAME * CURSOR_MAX, 
                                   CURSOR_SIZE, TRUE, RGB(0, 255, 0));
                }
            }
        }
    }

    // init GDI surface
    InitGDIDesktop();
}

/********************************************************************
 * InitGDIDesktop
 *
 * Description
 *    Creates and initializes the GDI surface and GDI texture surface.
 *
 * Parameters
 *    None
 * 
 * Returns
 *    None
 ********************************************************************/
void InitGDIDesktop(void)
{
    DDSURFACEDESC ddsd;
    HRESULT       ddrval;
    LPDIRECTDRAWSURFACE3 pDDS3Desktop = NULL;
    PHYSICAL_ADDRESS     sPhysicalAddress;
		
    memset(&ddsd, 0, sizeof(ddsd));
    ddsd.dwSize = sizeof(ddsd);

    // create GDI surface
    ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;
    ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_SYSTEMMEMORY;
    ddsd.dwWidth  = g_szScreen.cx;
    ddsd.dwHeight = g_szScreen.cy;
    ddrval = g_pDD->CreateSurface(&ddsd, &g_pDDSDesktop, NULL);

    if (ddrval == DD_OK)
    {		
        ddrval = g_pDDSDesktop->QueryInterface(IID_IDirectDrawSurface3, 
                                               (LPVOID *) &pDDS3Desktop);
    }

    // get GDI info
    GDISurfaceInfo info;
    if (ddrval == DD_OK)
    {
        ExtEscape(GetDC(HWND_DESKTOP), GETGDIINFO, 0, 0, sizeof(GDISurfaceInfo), 
                  ((LPSTR)&info));
    }

    // map GDI address into process space
    if ((ddrval == DD_OK) && (info.width == g_szScreen.cx) && 
        (info.height == g_szScreen.cy))
    {

        sPhysicalAddress.HighPart = 0;
        sPhysicalAddress.LowPart = info.physicalAddr;
        g_pGDIBits = MmMapIoSpace(sPhysicalAddress, info.height * info.stride, TRUE);
		
        memset(&ddsd, 0, sizeof(ddsd));
        ddsd.dwSize=sizeof(ddsd);
        ddsd.dwFlags = DDSD_HEIGHT | DDSD_WIDTH | DDSD_LPSURFACE | DDSD_PITCH;
        ddsd.dwWidth = info.width;
        ddsd.dwHeight = info.height;
        ddsd.lPitch = info.stride;
        ddsd.lpSurface = g_pGDIBits;

        ddrval = pDDS3Desktop->SetSurfaceDesc(&ddsd, 0);
    }

    // done with the IDirectDrawSurface3 interface
    if (pDDS3Desktop)
    {
        pDDS3Desktop->Release ();
    }

    // create texture surface for GDI
    if (ddrval == DD_OK)
    {
        memset(&ddsd, 0, sizeof(ddsd));
        ddsd.dwSize=sizeof(ddsd);
        ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;
        ddsd.ddsCaps.dwCaps = DDSCAPS_VIDEOMEMORY | DDSCAPS_TEXTURE;
        ddsd.dwWidth = g_szScreen.cx;
        ddsd.dwHeight = g_szScreen.cy;
        ddrval = g_pDD->CreateSurface(&ddsd, &g_pDDSTexture, NULL);
    }

    // clean up on failure
    if (ddrval != DD_OK)
    {
        OutputDebugString(TEXT("GDI Surface failed"));

        if (g_pDDSTexture)
        {
            g_pDDSTexture->Release();
            g_pDDSTexture = NULL;
        }

        if (g_pDDSDesktop)
        {
            if (g_pGDIBits)
            {
                MmUnmapIoSpace((void *)g_pGDIBits, g_szScreen.cx*g_szScreen.cy*2);
                g_pGDIBits = NULL;
            }
       
            g_pDDSDesktop->Release();
            g_pDDSDesktop = NULL;
        }
    }
}

/********************************************************************
 * DestroyDirectDraw
 *
 * Description
 *    Destroys the Direct Direct object and all of the other DDraw
 *    objects.
 *
 * Parameters
 *    None
 * 
 * Returns
 *    None
 ********************************************************************/
void DestroyDirectDraw(void)
{
    // all windows should be destroyed at this point, but lets make sure
    DestroyAllWindows();

    // release all DDraw objects
    if (g_pDD)
    {
        if (g_pDDSDesktop)
        {
            if (g_pGDIBits)
            {
                MmUnmapIoSpace((void *)g_pGDIBits, g_szScreen.cx*g_szScreen.cy*2);
                g_pGDIBits = NULL;
            }

            g_pDDSDesktop->Release();
            g_pDDSDesktop = NULL;
        }

        if (g_pDDSTexture)
        {
            g_pDDSTexture->Release();
            g_pDDSTexture = NULL;
        }

        if (g_pDDSBack)
        {
            g_pDDSBack->Release();
            g_pDDSBack = NULL;
        }

        if (g_pDDSPrimary)
        {
            g_pDDSPrimary->Release();
            g_pDDSPrimary = NULL;
        }

        if (g_pDDSCursor)
        {
            g_pDDSCursor->Release();
            g_pDDSCursor = NULL;
        }

        g_pDD->Release();
        g_pDD = NULL;
        g_pDDSBack = NULL;
    }
}

/********************************************************************
 * LoadImage
 *
 * Description
 *    Load an image from the resources into a DDraw surface.
 *
 * Parameters
 *    pDDS     DDraw surface into which to load bitmap
 *    szImage  resource ID of image to load into surface
 * 
 * Returns
 *    TRUE     sucessfully loaded bitmap into surface
 ********************************************************************/
BOOL LoadImage(LPDIRECTDRAWSURFACE pDDS, LPCTSTR szImage)
{
    BOOL            bReturn  = FALSE;
    HBITMAP         hbm      = NULL;
    HDC             hdcImage = NULL;
    HDC             hdcSurf  = NULL;
    DDSURFACEDESC   ddsd;

    memset(&ddsd, 0, sizeof(ddsd));
    ddsd.dwSize = sizeof(ddsd);

    if (FAILED(pDDS->GetSurfaceDesc(&ddsd)))
    {
        goto Exit;
    }

    // if the pixel format isn't some flavor of RGB, we can't handle it
    if ((ddsd.ddpfPixelFormat.dwFlags != DDPF_RGB) ||
        (ddsd.ddpfPixelFormat.dwRGBBitCount < 16))
    {
        OutputDebugString(TEXT("Non-palettized RGB mode required.\n"));
        goto Exit;        
    }

    // try loading the image
    hbm = LoadBitmap(g_hInstance, szImage);

    if (hbm == NULL) 
    {
        OutputDebugString(TEXT("Couldn't find the resource.\n"));
        goto Exit;
    }

    // create a DC and select the image into it
    hdcImage = CreateCompatibleDC(NULL);
    SelectObject(hdcImage, hbm);
   
    // Get a DC for the surface.
    if (FAILED(pDDS->GetDC(&hdcSurf)))
    {
        OutputDebugString(TEXT("Couldn't get a DC.\n"));
        goto Exit;
    }
    
    // BitBlt will perform format conversion as necessary.
    if (BitBlt(hdcSurf, 0, 0, ddsd.dwWidth, ddsd.dwHeight, hdcImage, 0, 0, SRCCOPY) == FALSE) 
    {
        OutputDebugString(TEXT("Blt failed.\n"));
        goto Exit;
    }

    // Success.
    bReturn = TRUE;
    
Exit:
    // clean up everything
    if (hdcSurf)
    {
        pDDS->ReleaseDC(hdcSurf);
    }
    if (hdcImage)
    {
        DeleteDC(hdcImage);
    }
    if (hbm)
    {
        DeleteObject(hbm);
    }

    return bReturn;
}

/********************************************************************
 * CreateBitmapSurface
 *
 * Description
 *    Creates a DDraw surface the size of a bitmap and loads that 
 *    bitmap into the surface.
 *
 * Parameters
 *    pszResource  resource ID of image to create surface
 *    nWidth       width of bitmap
 *    nHeight      height of bitmap
 *    bTransparent if TRUE, crTransColor describes transparent color
 *                 in bitmap; if FALSE, crTransColor is ignored
 *    crTransColor RGB value of transparent color in bitmap
 * 
 * Returns
 *    LPDIRECTDRAWSURFACE       new surface with bitmap loaded
 ********************************************************************/
LPDIRECTDRAWSURFACE CreateBitmapSurface(LPCTSTR pszResource, WORD nWidth, WORD nHeight, 
                                        BOOL bTransparent, COLORREF crTransColor)
{
    // verify Direct Draw object
    if (!g_pDD)
    {
        return NULL;
    }

    // get transparent color as 16 bit color
    WORD wTransColor = COLORREF_TO_16BPP(crTransColor);

    // create direct draw surface for bitmap
    DDSURFACEDESC  ddsd;
    memset(&ddsd, 0, sizeof(ddsd));

    ddsd.dwSize = sizeof(ddsd);
    ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;
    ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;
    ddsd.dwWidth  = nWidth; 
    ddsd.dwHeight = nHeight;
    if (bTransparent)
    {
        ddsd.dwFlags |= DDSD_CKSRCBLT;
        ddsd.ddckCKSrcBlt.dwColorSpaceLowValue  = wTransColor;
        ddsd.ddckCKSrcBlt.dwColorSpaceHighValue = wTransColor;
    }

    LPDIRECTDRAWSURFACE pDDS = NULL;
    if (FAILED(g_pDD->CreateSurface(&ddsd, &pDDS, NULL)))
    {
        return NULL;
    }

    // load bitmap to surface
    if (!LoadImage(pDDS, pszResource))
    {
        pDDS->Release();
        return NULL;
    }

    // return new surface
    return pDDS;
}

/********************************************************************
 * Defines
 ********************************************************************/
#define MAX_SCREEN      2       // maximum number of screens
#define MAX_WINDOW      20      // maximum number of windows per scrn

/********************************************************************
 * Structure
 ********************************************************************/
struct SCREEN_INFO              // information for screen
{
    CWindow * _apWindow[MAX_WINDOW];    // all windows on screen
    CWindow * _pCaptureWindow;          // window with cursor capture
    WORD      _nWindow;                 // number of windows on screen
    WORD      _nCursor;                 // cursor type for screen
    WORD      _nCursorState;            // cursor state (frame)
    WORD      _nCursorHide;             // cursor hide count
    POINT     _ptCursor;                // cursor position
    POINT     _ptCursorOffset;          // cursor hot spot

    SCREEN_INFO(void) 
    { 
        // initialize cursor type and position
        memset(this, 0, sizeof(*this)); 
        _ptCursorOffset.x = CURSOR_GAME_OFFSET_X; 
        _ptCursorOffset.y = CURSOR_GAME_OFFSET_Y; 
        _ptCursor.x = GetSystemMetrics(SM_CXSCREEN) / 2;
        _ptCursor.y = GetSystemMetrics(SM_CYSCREEN) / 2;
    }
};

/********************************************************************
 * SetActiveDisplay
 *
 * Description
 *    Sets the extents of the viewable screen area (the TV screen is
 *    rounded, so parts of the total screen are cut off).
 *
 * Parameters
 *    x        left margin of viewable area
 *    y        top margin of viewable area
 *    w        width of viewable area
 *    h        height of viewable area
 * 
 * Returns
 *    None
 ********************************************************************/
void SetActiveDisplay(WORD x, WORD y, WORD w, WORD h)
{
    // set active screen rectangle
    g_rcActiveScreen.left   = x;
    g_rcActiveScreen.right  = x + w;
    g_rcActiveScreen.top    = y;
    g_rcActiveScreen.bottom = y + h;
}

/********************************************************************
 * Global variables
 ********************************************************************/
BOOL g_bLockScreen = FALSE;     // screen lock for external drawing

/********************************************************************
 * DrawWaitScreen
 *
 * Description
 *    Draws a bitmap on the screen for use by procedures that will 
 *    take a while to complete. Does not create a window.
 *
 * Parameters
 *    x        left position of where to display bitmap
 *    y        top position of where to display bitmap
 *    w        width of bitmap to display
 *    h        height of bitmap to display
 * 
 * Returns
 *    None
 ********************************************************************/
void DrawWaitScreen(WORD x, WORD y, WORD w, WORD h, LPDIRECTDRAWSURFACE pDDSBitmap)
{
    // validate back surface
    if (!g_pDDSBack)
    {
        return;
    }

    // clear back buffer
    RECT rc = { 0, 0, g_szScreen.cx, g_szScreen.cy };
    DDBLTFX ddbltfx;
    memset(&ddbltfx, 0, sizeof(ddbltfx));
    ddbltfx.dwSize = sizeof(DDBLTFX);
    ddbltfx.dwFillColor = COLORREF_TO_16BPP(RGB(0xC0, 0xC0, 0xC0));
    g_pDDSBack->Blt(&rc, NULL, NULL, DDBLT_COLORFILL | DDBLT_WAIT, &ddbltfx);

    // draw wait screen bitmap
    rc.right  = w;
    rc.bottom = h;
    g_pDDSBack->BltFast(x, y, pDDSBitmap, &rc, 0);

    // flip back buffer to primary and wait to finish flip
    while (TRUE)
    {
        HRESULT ddrval = g_pDDSPrimary->Flip(NULL, 0);

        if (ddrval == DD_OK)
        {
            break;
        }

        if (ddrval == DDERR_SURFACELOST)
        {
            ddrval = g_pDDSPrimary->Restore();
            if (ddrval != DD_OK)
            {
                break;
            }
        }

        if (ddrval != DDERR_WASSTILLDRAWING)
        {
            break;
        }
    }
}

/********************************************************************
 * LockScreen
 *
 * Description
 *    Locks the drawing of the screens for use when external procedures
 *    need to take over drawing (such as the IME).
 *
 * Parameters
 *    None
 * 
 * Returns
 *    None
 ********************************************************************/
void LockScreen(void)
{
    // set lock status
    g_bLockScreen = TRUE;
}

/********************************************************************
 * UnlockScreen
 *
 * Description
 *    Unlocks the drawing of the screens. The next time it is time to
 *    redraw the screen, the regular screen drawing routines will take
 *    effect again.
 *
 * Parameters
 *    None
 * 
 * Returns
 *    None
 ********************************************************************/
void UnlockScreen(void)
{
    // set lock status
    g_bLockScreen = FALSE;
}

/********************************************************************
 * IsScreenLocked
 *
 * Description
 *    Returns whether the screen is locked to allow external procedure
 *    to take over drawing.
 *
 * Parameters
 *    None
 * 
 * Returns
 *    TRUE     screen is locked 
 *    FALSE    screen is not locked
 ********************************************************************/
BOOL IsScreenLocked(void)
{
    // return lock status
    return g_bLockScreen;
}

/********************************************************************
 * Global variables
 ********************************************************************/
SCREEN_INFO  g_aScreenInfo[MAX_SCREEN];         // all screen data
SCREEN_INFO *g_pScreenInfo = g_aScreenInfo;	// current screen data

/********************************************************************
 * DrawCurrentScreen
 *
 * Description
 *    Draws all of the windows on the current screen. Windows that are
 *    doing device context drawing must do that drawing last.
 *
 * Parameters
 *    None
 * 
 * Returns
 *    None
 ********************************************************************/
void DrawCurrentScreen(void)
{
    // do not do anything if screen is locked or no back surface
    if (g_bLockScreen)
    {
        return;
    }

    if (!g_pDDSBack)
    {
        return;
    }

    WORD i;
    HDC hdc;

    // load the base GDI information to the texture
    RECT rc   = { 0, 0, g_szScreen.cx, g_szScreen.cy };
    g_pDDSTexture->BltFast(0, 0, g_pDDSDesktop, &rc, 0);

    DDBLTFX ddbltfx;
    memset(&ddbltfx, 0, sizeof(ddbltfx));
    ddbltfx.dwSize = sizeof(DDBLTFX);
    ddbltfx.dwFillColor = COLORREF_TO_16BPP(RGB(0xC0, 0xC0, 0xC0));

    // clear the back buffer
    g_pDDSBack->Blt(&rc, NULL, NULL, DDBLT_COLORFILL | DDBLT_WAIT, &ddbltfx);

    // draw all of the ddraw elements (GDI and ddraw CAN'T be mixed!!!!)
    for (i = 0; i < g_pScreenInfo->_nWindow; i++)
    {
        if (g_pScreenInfo->_apWindow[i]->IsVisible())
        {
            g_pScreenInfo->_apWindow[i]->Draw(g_pDDSBack);
            g_pScreenInfo->_apWindow[i]->Draw(g_pDDSBack, g_pDDSTexture);
        }
    }

    // draw all of the GDI elements
    if (g_pDDSBack->GetDC(&hdc) == DD_OK)
    {
        for (i = 0; i < g_pScreenInfo->_nWindow; i++)
        {
            if (g_pScreenInfo->_apWindow[i]->IsVisible())
            {
                g_pScreenInfo->_apWindow[i]->Draw(hdc);
            }
        }

        g_pDDSBack->ReleaseDC(hdc);
    }

    // Check for whether GDI cursor is active (i.e., user is navigating within 
    // server-side image map). Since there is no mouse installed, the GDI cursor
    // count starts at -1. If the image map is not active, ShowCursor will 
    // increment the GDI cursor count to 0, and thus the drawing of the GDI cursor
    // will be skipped. If the image map is active, ShowCursor will increment
    // the GDI cursor count > 0 (because the server-side image map element will
    // already have incremented it), and thus the GDI cursor will be drawn.
    if (ShowCursor(TRUE))
    {
        // show the arrow cursor when inside server-side image maps
        POINT ptGDICursor;
        GetCursorPos(&ptGDICursor);
        RECT rcCursor;
        SetRect(&rcCursor,
                (CURSOR_POINTER * CURSOR_FRAME) * CURSOR_SIZE,
                0,
                (CURSOR_POINTER * CURSOR_FRAME + 1) * CURSOR_SIZE,
                CURSOR_SIZE);

        g_pDDSBack->BltFast(ptGDICursor.x - CURSOR_POINTER_OFFSET_X,
                            ptGDICursor.y - CURSOR_POINTER_OFFSET_Y,
                            g_pDDSCursor, &rcCursor, DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY);
    }
    else
    {
        // draw cursor at ptCursor
        if (!g_pScreenInfo->_nCursorHide)
        {
            static DWORD dwTick = GetTickCount();
            RECT rcCursor;
 
            // see if time to animate cursor to next frame
            if ((GetTickCount() - dwTick) > CURSOR_RATE)
            {
                g_pScreenInfo->_nCursorState = 
                    (g_pScreenInfo->_nCursorState + 1) % CURSOR_FRAME;
                dwTick = GetTickCount();
            }

            SetRect(&rcCursor,
                    (g_pScreenInfo->_nCursor * CURSOR_FRAME + g_pScreenInfo->_nCursorState) * CURSOR_SIZE,
                    0,
                    (g_pScreenInfo->_nCursor * CURSOR_FRAME + g_pScreenInfo->_nCursorState + 1) * CURSOR_SIZE,
                    CURSOR_SIZE);

            // draw cursor frame
            if (g_pDDSCursor)
            {
                g_pDDSBack->BltFast(g_pScreenInfo->_ptCursor.x - g_pScreenInfo->_ptCursorOffset.x,
                                    g_pScreenInfo->_ptCursor.y - g_pScreenInfo->_ptCursorOffset.y,
                                    g_pDDSCursor, &rcCursor, DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY);
            }
        }
    }

    ShowCursor(FALSE);

    // flip back buffer to primary and wait to finish flip
    while (TRUE)
    {
        HRESULT ddrval = g_pDDSPrimary->Flip(NULL, 0);

        if (ddrval == DD_OK)
        {
            break;
        }

        if (ddrval == DDERR_SURFACELOST)
        {
            ddrval = g_pDDSPrimary->Restore();
            if (ddrval != DD_OK)
            {
                break;
            }
        }

        if (ddrval != DDERR_WASSTILLDRAWING)
        {
            break;
        }
    }
}

/********************************************************************
 * SwitchScreen
 *
 * Description
 *    Switch display to another set of windows. You can have multiple
 *    "screens" with a number of windows on each screen and quickly 
 *    switch between these sets of windows.
 *
 * Parameters
 *    nScreen  the screen ID of screen to display
 * 
 * Returns
 *    None
 ********************************************************************/
void SwitchScreen(WORD nScreen)
{
    // validate parameters
    if (nScreen < MAX_SCREEN)
    {
        // switch to new screen
        g_pScreenInfo = g_aScreenInfo + nScreen;
    }
}

/********************************************************************
 * AddWindow
 *
 * Description
 *    Add a window to the requested screen.
 *
 * Parameters
 *    pWindow  window to add to screen
 *    nScreen  the screen ID to which to add window
 * 
 * Returns
 *    None
 ********************************************************************/
void AddWindow(CWindow *pWindow, WORD nScreen)
{
    // validate parameters and enough room for a new window
    if ((nScreen < MAX_SCREEN) && ((g_aScreenInfo[nScreen]._nWindow + 1) < MAX_WINDOW))
    {
        // add window to screen array
        g_aScreenInfo[nScreen]._apWindow[g_aScreenInfo[nScreen]._nWindow] = pWindow;
        g_aScreenInfo[nScreen]._nWindow++;
    }
}

/********************************************************************
 * RemoveWindow
 *
 * Description
 *    Remove a window from the requested screen.
 *
 * Parameters
 *    pWindow  window to remove from screen
 *    nScreen  the screen ID for which to remove window
 * 
 * Returns
 *    None
 ********************************************************************/
void RemoveWindow(CWindow *pWindow, WORD nScreen)
{
    // validate parameters
    if (nScreen < MAX_SCREEN)
    {
        WORD i;
        for (i = 0; i < g_aScreenInfo[nScreen]._nWindow; i++)
        {
            // find window to delete
            if (g_aScreenInfo[nScreen]._apWindow[i] == pWindow)
            {
                // decrement window count
                g_aScreenInfo[nScreen]._nWindow--;

                // shift all windows after removed one up
                if (g_aScreenInfo[nScreen]._nWindow - i)
                {
                    memcpy(g_aScreenInfo[nScreen]._apWindow + i, 
                           g_aScreenInfo[nScreen]._apWindow + i + 1, 
                           sizeof(CWindow *) * (g_aScreenInfo[nScreen]._nWindow - i));
                }

                // release capture if window is captured
                if (g_aScreenInfo[nScreen]._pCaptureWindow == pWindow)
                {
                    ReleaseCursorCapture(pWindow, nScreen);
                }
                break;
            }
        }
    }
}

/********************************************************************
 * DestroyAllWindows
 *
 * Description
 *    Destroys any windows still left on any screen.
 *
 * Parameters
 *    None
 * 
 * Returns
 *    None
 ********************************************************************/
void DestroyAllWindows(void)
{
    WORD j;
    WORD i;
    // destroy each screen
    for (j = 0; j < MAX_SCREEN; j++)
    {
        // destroy each window on screen
        for (i = 0; i < g_aScreenInfo[j]._nWindow; i++)
        {
            delete g_aScreenInfo[j]._apWindow[i];
        }
        g_aScreenInfo[j]._nWindow = 0;
    }
}

/********************************************************************
 * EnableModal
 *
 * Description
 *    Brings the window to the top of the Z order and captures the 
 *    cursor for the window.
 *
 * Parameters
 *    pWindow  window to make modal
 *    nScreen  the screen ID for which to set modal window
 * 
 * Returns
 *    None
 ********************************************************************/
void EnableModal(CWindow *pWindow, WORD nScreen)
{
    // validate parameters
    if (nScreen < MAX_SCREEN)
    {
        // put window at top of Z order
        if (g_aScreenInfo[nScreen]._apWindow[g_aScreenInfo[nScreen]._nWindow - 1] != pWindow)
        {
            RemoveWindow(pWindow, nScreen);
            AddWindow(pWindow, nScreen);
        }

        // capture the cursor for the window
        SetCursorCapture(pWindow, nScreen);
    }
}

/********************************************************************
 * DisableModal
 *
 * Description
 *    Release capture on modal window.
 *
 * Parameters
 *    pWindow  window to no longer be modal
 *    nScreen  the screen ID for which to release modal window
 * 
 * Returns
 *    None
 ********************************************************************/
void DisableModal(CWindow *pWindow, WORD nScreen)
{
    // just release cursor capture
    ReleaseCursorCapture(pWindow, nScreen);
}

/********************************************************************
 * MoveAllWindows
 *
 * Description
 *    Move all the windows on the requested screen by a delta 
 *    horizontally and vertically.
 *
 * Parameters
 *    xDelta   amount to move all windows horizontally
 *    yDelta   amount to move all windows vertically
 *    nScreen  the screen ID for which to move all windows
 * 
 * Returns
 *    None
 ********************************************************************/
void MoveAllWindows(short xDelta, short yDelta, WORD nScreen)
{
    // validate parameters
    if (nScreen < MAX_SCREEN)
    {
        // adjust all windows' positions
        WORD i;
        for (i = 0; i < g_aScreenInfo[nScreen]._nWindow; i++)
        {
            g_aScreenInfo[nScreen]._apWindow[i]->MoveRelative(xDelta, yDelta);
        }
    }
}

/********************************************************************
 * SetCursorCapture
 *
 * Description
 *    Send all subsequent controller (joystick) messages to the given
 *    window.
 *
 * Parameters
 *    pWindow  window to receive controller messages
 *    nScreen  the screen ID for which to set captured window
 * 
 * Returns
 *    None
 ********************************************************************/
void SetCursorCapture(CWindow *pWindow, WORD nScreen)
{
    // validate parameters
    if ((nScreen < MAX_SCREEN) && (pWindow != g_aScreenInfo[nScreen]._pCaptureWindow))
    {
        // release previous window's capture
        if (g_aScreenInfo[nScreen]._pCaptureWindow)
        {
            // send previous captured window a joystick message that
            // is off the screen, so it will clean up correctly
            POINT ptCursor = g_aScreenInfo[nScreen]._ptCursor;
            g_aScreenInfo[nScreen]._ptCursor.x = 0xffff;
            g_aScreenInfo[nScreen]._ptCursor.y = 0xffff;
            g_pScreenInfo->_pCaptureWindow->Joystick(0, 0, 
                (WORD)g_pScreenInfo->_ptCursor.x, (WORD)g_pScreenInfo->_ptCursor.y);
            g_aScreenInfo[nScreen]._ptCursor = ptCursor;
        }

        // set captured window and send it joystick message, so that
        // it will set up correctly
        g_aScreenInfo[nScreen]._pCaptureWindow = pWindow;
        g_pScreenInfo->_pCaptureWindow->Joystick(0, 0, 
            (WORD)g_pScreenInfo->_ptCursor.x, (WORD)g_pScreenInfo->_ptCursor.y);
    }
}

/********************************************************************
 * ReleaseCursorCapture
 *
 * Description
 *    Do not send all subsequent controller (joystick) messages to 
 *    previously captured window.
 *
 * Parameters
 *    pWindow  window to no longer receive controller messages
 *    nScreen  the screen ID for which to release captured window
 * 
 * Returns
 *    None
 ********************************************************************/
void ReleaseCursorCapture(CWindow *pWindow, WORD nScreen)
{
    // validate parameters
    if (nScreen < MAX_SCREEN)
    {
        // make sure window being released is the one that has
        // capture
        if (g_aScreenInfo[nScreen]._pCaptureWindow == pWindow)
        {
            // clear capture window
            g_aScreenInfo[nScreen]._pCaptureWindow = NULL;
            DWORD adwButtons[2] = { 0, 0 };
            POINT ptCursor = g_aScreenInfo[nScreen]._ptCursor;
            // allow other window to grab capture 
            SendCurrentScreenJoystick((WPARAM)adwButtons, 
                MAKELPARAM((WORD)ptCursor.x, ptCursor.y));
        }
    }
}

/********************************************************************
 * HideCursor
 *
 * Description
 *    Hides cusor on requested screen. Must be balanced with 
 *    ShowCursor.
 *
 * Parameters
 *    nScreen  the screen ID for which to hide cursor
 * 
 * Returns
 *    None
 ********************************************************************/
void HideCursor(WORD nScreen)
{
    // validate parameters
    if (nScreen < MAX_SCREEN)
    {
        // increment hide count
        g_aScreenInfo[nScreen]._nCursorHide++;
    }
}

/********************************************************************
 * ShowCursor
 *
 * Description
 *    Shows cusor on requested screen if hide count is down to zero.
 *
 * Parameters
 *    nScreen  the screen ID for which to show cursor
 * 
 * Returns
 *    None
 ********************************************************************/
void ShowCursor(WORD nScreen)
{
    // validate parameters
    if (nScreen < MAX_SCREEN)
    {
        // decrement hide count
        g_aScreenInfo[nScreen]._nCursorHide--;
    }
}

/********************************************************************
 * SetCursorOffset
 *
 * Description
 *    Sets the requested screen's cursor offset (hot spot).
 *
 * Parameters
 *    x        horizontal offset 
 *    y        vertical offset
 *    nScreen  the screen ID for which to set cursor offset
 * 
 * Returns
 *    None
 ********************************************************************/
void SetCursorOffset(WORD x, WORD y, WORD nScreen)
{
    // validate parameters
    if (nScreen < MAX_SCREEN)
    {
        // set cursor offset
        g_aScreenInfo[nScreen]._ptCursorOffset.x = x;
        g_aScreenInfo[nScreen]._ptCursorOffset.y = y;
    }
}

/********************************************************************
 * SetCursorType
 *
 * Description
 *    Sets requested screen's cursor type to the given type.
 *
 * Parameters
 *    nCursor  type of cursor to display
 *    nScreen  the screen ID for which to set cursor type
 * 
 * Returns
 *    None
 ********************************************************************/
void SetCursorType(WORD nCursor, WORD nScreen)
{
    // validate parameters
    if (nScreen < MAX_SCREEN)
    {
        // set cursor type
        g_aScreenInfo[nScreen]._nCursor = nCursor;

        // set appropriate cursor offset (hot spot)
        if (nCursor == CURSOR_GAME)
        {
            SetCursorOffset(CURSOR_GAME_OFFSET_X, CURSOR_GAME_OFFSET_Y, nScreen);
        }
        else if (nCursor == CURSOR_HTML)
        {
            SetCursorOffset(CURSOR_HTML_OFFSET_X, CURSOR_HTML_OFFSET_Y, nScreen);
        }
        else if (nCursor == CURSOR_POINTER)
        {
            SetCursorOffset(CURSOR_POINTER_OFFSET_X, CURSOR_POINTER_OFFSET_Y, nScreen);
        }
    }
}

/********************************************************************
 * SetCursorPosition
 *
 * Description
 *    Sets requested screen's cursor position to the given point.
 *
 * Parameters
 *    x        new cursor horizontal position
 *    y        new cursor vertical positon
 *    nScreen  the screen ID for which to set cursor position
 * 
 * Returns
 *    None
 ********************************************************************/
void SetCursorPosition(WORD x, WORD y, WORD nScreen)
{
    if (nScreen < MAX_SCREEN)
    {
        g_aScreenInfo[nScreen]._ptCursor.x = x;
        g_aScreenInfo[nScreen]._ptCursor.y = y;
    }
}

/********************************************************************
 * QueryCursorPosition
 *
 * Description
 *    Returns requested screen's current cursor position.
 *
 * Parameters
 *    nScreen  the screen ID for which to retrieve cursor position
 * 
 * Returns
 *    POINT    the current position
 ********************************************************************/
POINT QueryCursorPosition(WORD nScreen)
{
    // validate parameters
    if (nScreen < MAX_SCREEN)
    {
        // return cursor position
        return g_aScreenInfo[nScreen]._ptCursor;
    }

    POINT pt = { 0, 0 };
    return pt;
}

/********************************************************************
 * SetCurrentScreenCursorPos
 *
 * Description
 *    Sets current screen's cursor position to the given point.
 *
 * Parameters
 *    x        new cursor horizontal position
 *    y        new cursor vertical positon
 * 
 * Returns
 *    None
 ********************************************************************/
void SetCurrentScreenCursorPos(WORD x, WORD y)
{
    g_pScreenInfo->_ptCursor.x = x;
    g_pScreenInfo->_ptCursor.y = y;
}

/********************************************************************
 * QueryCurrentCursorPos
 *
 * Description
 *    Returns current screen's current cursor position.
 *
 * Parameters
 *    None
 * 
 * Returns
 *    POINT        the current position
 ********************************************************************/
POINT QueryCurrentScreenCursorPos(void)
{
    // return cursor position
    return g_pScreenInfo->_ptCursor;
}

/********************************************************************
 * QueryCurrentScreenCursorOffet
 *
 * Description
 *    Returns current screen's current cursor hot spot offset.
 *
 * Parameters
 *    None
 * 
 * Returns
 *    POINT        the hot spot offset
 ********************************************************************/
POINT QueryCurrentScreenCursorOffset(void)
{
    // return cursor offset
    return g_pScreenInfo->_ptCursorOffset;
}

/********************************************************************
 * Global variables
 ********************************************************************/
extern BOOL g_bBusy;            // allow only one joystick msg at a time

/********************************************************************
 * SendCurrentScreenJoystick
 *
 * Description
 *    Send controller (joystick) message to captured window and/or
 *    other windows stopping when one of these windows does handle 
 *    the message.
 *
 * Parameters
 *    wParam    pointer to array of buttons info (buttons pressed and
 *              buttons held flags)
 *    lParam    low word is x position of cursor, high word is y 
 *              positon of cursor.
 * 
 * Returns
 *    None
 ********************************************************************/
void SendCurrentScreenJoystick(WPARAM wParam, LPARAM lParam)
{
    SCREEN_INFO *pScreenInfo = g_pScreenInfo;

    // allow other controller message to process
    g_bBusy = FALSE;

    // validate parameters
    if (!wParam)
    {
        return;
    }

    // set cursor position to joystick position
    SetCurrentScreenCursorPos(LOWORD(lParam), HIWORD(lParam));

    BOOL    bHandledButtons = FALSE;
    LPDWORD pdwButtons = (LPDWORD)wParam;

    // send joystick message to any window that has captured cursor
    if (g_pScreenInfo->_pCaptureWindow)
    {
        g_pScreenInfo->_pCaptureWindow->Joystick(pdwButtons[0], pdwButtons[1], 
                                        LOWORD(lParam), HIWORD(lParam));

        // in case the window released capture and we need to send on the
        // new joystick position to a new window, wipe out the buttons so
        // the new window does not process them
        pdwButtons[0] = 0;
        pdwButtons[1] = 0;
    }

    // send joystick message to other windows (in z-order) until one of 
    // windows handles it
    if (!g_pScreenInfo->_pCaptureWindow)
    {
        WORD i;
        WORD x = LOWORD(lParam);
        WORD y = HIWORD(lParam);

        for (i = g_pScreenInfo->_nWindow; i; i--)
        {
            // don't bother the window if the cursor is not in the window
            // or if the window is not visible
            if ((g_pScreenInfo == pScreenInfo) && 
                g_pScreenInfo->_apWindow[i-1]->IsVisible() && 
                g_pScreenInfo->_apWindow[i-1]->PointInWindow(x, y))
            {
                if (S_OK == g_pScreenInfo->_apWindow[i-1]->Joystick(pdwButtons[0], 
                                                           pdwButtons[1], x, y))
                {
                    // as soon as one window handles the message, we don't need
                    // to inform any other windows
                    break;
                }
            }
        }
    }
}

