/**************************************************************************

    FLIPCUBE.CPP - A spinning cube demo for DirectDraw

    basic page fliping app, just render to the back buffer and flip
    that is all I do.

 **************************************************************************/
/**************************************************************************

    (C) Copyright 1995-1997 Microsoft Corp.  All rights reserved.

    You have a royalty-free right to use, modify, reproduce and
    distribute the Sample Files (and/or any modified version) in
    any way you find useful, provided that you agree that
    Microsoft has no warranty obligations or liability for any
    Sample Application Files which are modified.

 **************************************************************************/

#define INITGUID

#include <windows.h>
#include <windowsx.h>
#include <mmsystem.h>
#include <ddraw.h>
#include <dinput.h>
#include <math.h>

#include "flipcube.h"
#include "dumb3d.h"

// code is in tri.cpp
extern void Triangle8(BYTE *p, int next_scan, POINT P0, POINT P1, POINT P2, DWORD c);

/**************************************************************************
  Global Variables
 **************************************************************************/

static char szAppName[]="DirectDraw Spinning Cube";

static HINSTANCE  hInstApp;
static BOOL       fAppActive;
static BOOL       fAppPaused;
static HWND       hwndApp;
static HACCEL     hAccelApp;
static HFONT      AppFont;
static SIZE       ScreenSize;
static BOOL       fDrawWithGDI;

/**************************************************************************
  DirectDraw Globals
 **************************************************************************/

IDirectDraw            *dd;
IDirectDrawSurface     *FrontBuffer;
IDirectDrawSurface     *BackBuffer;
IDirectDrawPalette     *Palette;

/**************************************************************************
  DirectInput Globals
 **************************************************************************/
LPDIRECTINPUT			lpdi;
LPDIRECTINPUTDEVICE             lpdiZoom;       // Used for zooming
LPDIRECTINPUTDEVICE             lpdiRot;        // Use for rotation
BOOL                            fMouseAcquired = FALSE; // Acquired for rot'n

/**************************************************************************
  dumb 3D Globals
 **************************************************************************/

//*** Cube vertices, normals, shades, and modeling transform
static point_4 CubeVertices[8] =
{
  point_4( -10,  10, -10 ),
  point_4( -10,  10,  10 ),
  point_4(  10,  10,  10 ),
  point_4(  10,  10, -10 ),
  point_4(  10, -10, -10 ),
  point_4(  10, -10,  10 ),
  point_4( -10, -10,  10 ),
  point_4( -10, -10, -10 )
};
static vector_4   CubeSurfaceNormals[6];
static real       CubeSurfaceShades[6];
static matrix_4x4 CubeTransform;

//*** Cube edges - ordered indices into the vertex array
const int CubeFaces[6][4] =
{
  0, 1, 2, 3,
  2, 1, 6, 5,
  3, 2, 5, 4,
  0, 3, 4, 7,
  1, 0, 7, 6,
  4, 5, 6, 7
};

//*** Cube colors - one RGB color per surface
const unsigned char CubeColors[6][3] =
{
  240,  20,  20,    // Unsaturated Red
   20, 240,  20,    // Unsaturated Green
   20,  20, 240,    // Unsaturated Blue
  128,  64,   0,    // Brown
  240,  20, 240,    // Unsaturated Magenta
  240, 240,  20     // Unsaturated Yellow
};

//*** Lighting
vector_4   LightSourceDirection;
const real AmbientLight = 0.2;

//*** Viewing and perspective
static matrix_4x4  ViewPerspective;
static point_4     Viewpoint(60, 60, 60);
static vector_4    Up(0, 1, 0);
static point_4     Origin;

/**************************************************************************
   Internal function declarations
 **************************************************************************/

LONG  CALLBACK AppWndProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam);
BOOL  InitDInput(void);
BOOL  AppIdle(void);
void  RenderFrame(void);

void  TransformCube(matrix_4x4 const &Transform);
BOOL  ProjectAndDrawCube(HDC hdc, int XOffset, int YOffset);
BOOL  ProjectAndDrawCube(IDirectDrawSurface *pdds, int XOffset, int YOffset);

/**************************************************************************
  AppAbout

  Description:
    This function handles messages belonging to the "About" dialog box.
  The only message that it looks for is WM_COMMAND, indicating the user
  has pressed the "OK" button.
 **************************************************************************/

BOOL FAR PASCAL AppAbout(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
  switch (msg)
  {
    case WM_COMMAND:
      if (LOWORD(wParam) == IDOK)
        EndDialog(hwnd, TRUE);
      break;

    case WM_INITDIALOG:
      return TRUE;
  }
  return FALSE;
}

/**************************************************************************
  DDInit

  Description:
    initialize all the DirectDraw specific stuff
 **************************************************************************/

BOOL DDInit()
{
    HRESULT err;

    err = DirectDrawCreate(NULL, &dd, NULL);

    if (err != DD_OK)
        return FALSE;

    err = dd->SetCooperativeLevel(hwndApp,
        DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN | DDSCL_ALLOWMODEX);

    if (err != DD_OK)
        return FALSE;

	// NEWNEW init DirectInput iff DDraw inits ok
	if(!InitDInput())
		return FALSE;

    return TRUE;
}

/**************************************************************************
  CreateMouse
 **************************************************************************/

BOOL CreateMouse(GUID &guid, LPDIRECTINPUTDEVICE& lpdiMouse, DWORD dwAccess)
{
    HRESULT err;

    err = lpdi->CreateDevice(guid, &lpdiMouse, NULL);

    if(err != DI_OK)
    {
            MessageBox(NULL, "Unable to Create DirectInput Mouse Device",
                    "DirectDraw Spinning Cube", MB_OK);
            goto fail;
    }

    // Tell DirectInput that we want to receive data in mouse format
    err = lpdiMouse->SetDataFormat(&c_dfDIMouse);

    if(err != DI_OK)
    {
            MessageBox(NULL, "Unable to Access DirectInput Device as a mouse",
                    "DirectDraw Spinning Cube", MB_OK);
            goto fail;
    }

    // set desired access mode
    err = lpdiMouse->SetCooperativeLevel(hwndApp, dwAccess);
    if(err != DI_OK)
    {
        // Don't complain if asking for DISCL_NONEXCLUSIVE since
        // not all systems support it.  (The caller will gracefully
        // degrade.)
        if (dwAccess & DISCL_EXCLUSIVE) {
            MessageBox(NULL, "Unable to set cooperativity level",
                    "DirectDraw Spinning Cube", MB_OK);
        }
        goto fail;
    }

    return TRUE;

fail:;
    if (lpdiMouse)      lpdiMouse->Release(),       lpdiMouse = 0;
    return FALSE;
}

/**************************************************************************
  InitDInput
 **************************************************************************/
BOOL InitDInput(void)
{
	HRESULT		err;
	GUID     guid = GUID_SysMouse;
    // Need DirectX 3 or better
    err = DirectInputCreate(hInstApp, 0x0300, &lpdi, NULL);

	if(err != DI_OK)
	{
		MessageBox(NULL, "Unable to Create DirectInput Object",
			"DirectDraw Spinning Cube", MB_OK);
		return FALSE;
	}

        // Create a mouse for zooming.  Zooming is done non-exclusively.
        if (!CreateMouse(guid, lpdiZoom, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND))
        {
                /* Note!  This is not a fatal error */
        } else {

            if (fAppActive) lpdiZoom->Acquire();

        }

        // Create a mouse for rotation.  Rotation is done exclusively.
        if (!CreateMouse(guid, lpdiRot, DISCL_EXCLUSIVE | DISCL_FOREGROUND))
        {
                goto fail;
        }

        // if we get here, all DirectInput objects were created ok
	return TRUE;

fail:
        if (lpdiZoom)  lpdiZoom->Release(), lpdiZoom = NULL;
        if (lpdiRot)   lpdiRot ->Release(), lpdiRot  = NULL;
        if (lpdi)      lpdi    ->Release(), lpdi     = NULL;
        return FALSE;

}


/**************************************************************************
  DDSetMode
 **************************************************************************/

BOOL DDSetMode(int width, int height, int bpp)
{
    HRESULT err;

    err = dd->SetDisplayMode(width, height, bpp);

    if (err != DD_OK)
        return FALSE;

    ScreenSize.cx = width;
    ScreenSize.cy = height;

    // get rid of any previous surfaces.
    if (BackBuffer)  BackBuffer->Release(),     BackBuffer = NULL;
    if (FrontBuffer) FrontBuffer->Release(),    FrontBuffer = NULL;
    if (Palette)     Palette->Release(),        Palette = NULL;

    //
    // Create surfaces
    //
    // what we want is a tripple buffered surface in video memory
    // so we try to create this first.
    //
    // if we cant get a triple buffered surface, we try again
    // for a double buffered surface (still must be in video memory)
    //
    // if we cant get a double buffered surface, we try for a double
    // buffered surface not being specific about video memory, we will
    // get back a main-memory surface, that work use HW page flipping
    // but at least we run.
    //
    // NOTE you need to recreate the surfaces for a new display mode
    // they wont work when/if the mode is changed.
    //
    DDSURFACEDESC ddsd;

    ZeroMemory(&ddsd, sizeof(ddsd));
    ddsd.dwSize = sizeof(ddsd);
    ddsd.dwFlags = DDSD_CAPS | DDSD_BACKBUFFERCOUNT;
    ddsd.dwBackBufferCount = 2;
    ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE |
                          DDSCAPS_FLIP |
                          DDSCAPS_COMPLEX |
                          DDSCAPS_VIDEOMEMORY;

    // try to get a triple buffered video memory surface.
    err = dd->CreateSurface(&ddsd, &FrontBuffer, NULL);

    if (err != DD_OK)
    {
        // try to get a double buffered video memory surface.
        ddsd.dwBackBufferCount = 1;
        err = dd->CreateSurface(&ddsd, &FrontBuffer, NULL);
    }

    if (err != DD_OK)
    {
        // settle for a main memory surface.
        ddsd.ddsCaps.dwCaps &= ~DDSCAPS_VIDEOMEMORY;
        err = dd->CreateSurface(&ddsd, &FrontBuffer, NULL);
    }

    if (err != DD_OK)
        return FALSE;

    // get a pointer to the back buffer
    DDSCAPS caps;
    caps.dwCaps = DDSCAPS_BACKBUFFER;
    err = FrontBuffer->GetAttachedSurface(&caps, &BackBuffer);

    if (err != DD_OK)
        return FALSE;

    // create a palette if we are in a paletized display mode.
    //
    // NOTE because we want to be able to show dialog boxs and
    // use our menu, we leave the windows reserved colors as is
    // so things dont look ugly.
    //
    // palette is setup like so:
    //
    //      10      windows system colors
    //      64      red wash
    //      64      grn wash
    //      64      blu wash
    //
    PALETTEENTRY ape[256];
    HDC hdc = GetDC(NULL);
    if (GetDeviceCaps(hdc, RASTERCAPS) & RC_PALETTE)
    {
        // get the current windows colors.
        GetSystemPaletteEntries(hdc, 0, 256, ape);

        // make a red, grn, and blu wash for our cube.
        for (int i=0; i<64; i++)
        {
            ape[10+64*0+i].peRed   = i * 255/63;
            ape[10+64*0+i].peGreen = 0;
            ape[10+64*0+i].peBlue  = 0;

            ape[10+64*1+i].peRed   = 0;
            ape[10+64*1+i].peGreen = i * 255/63;
            ape[10+64*1+i].peBlue  = 0;

            ape[10+64*2+i].peRed   = 0;
            ape[10+64*2+i].peGreen = 0;
            ape[10+64*2+i].peBlue  = i * 255/63;
        }

        // create the palette.
        err = dd->CreatePalette(DDPCAPS_8BIT, ape, &Palette, NULL);

        if (err == DD_OK)
        {
            FrontBuffer->SetPalette(Palette);
        }
    }
    ReleaseDC(NULL, hdc);

    if (AppFont)
        DeleteObject(AppFont);

    AppFont = CreateFont(width < 640 ? 24 : 48,
        0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
        ANSI_CHARSET,
        OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS,
        NONANTIALIASED_QUALITY,
        VARIABLE_PITCH,
        "Comic Sans MS");

    return TRUE;
}


/**************************************************************************
  DDTerm
 **************************************************************************/

void DDTerm()
{
    if (BackBuffer)  BackBuffer->Release(),     BackBuffer = NULL;
    if (FrontBuffer) FrontBuffer->Release(),    FrontBuffer = NULL;
    if (Palette)     Palette->Release(),        Palette = NULL;
    if (dd)          dd->Release(),             dd = NULL;
    if (lpdi)        lpdi->Release(),           lpdi = NULL;
}

/**************************************************************************
  ModeCallback
 **************************************************************************/

#define MAKEMENUITEMDATA(width, height, bpp) \
        (width) | ((height) << 12) | ((bpp) << 24)

HRESULT CALLBACK ModeCallback(LPDDSURFACEDESC pdds, LPVOID lParam)
{
    HMENU hmenu = (HMENU)lParam;
    char ach[80];
    int n;
    int width  = pdds->dwWidth;
    int height = pdds->dwHeight;
    int bpp    = pdds->ddpfPixelFormat.dwRGBBitCount;

    n = GetMenuItemCount(hmenu);
    wsprintf(ach,"%dx%dx%d",width,height,bpp);
    AppendMenu(hmenu,MF_STRING,MENU_MODE+n,ach);

    MENUITEMINFO mii;

    // pack the mode info into a DWORD and set the extra item data.
    mii.cbSize = sizeof(mii);
    mii.fMask = MIIM_DATA;
    mii.dwItemData = MAKEMENUITEMDATA(width, height, bpp);
    SetMenuItemInfo(hmenu, MENU_MODE+n, MF_BYCOMMAND, &mii);

    //return S_TRUE to stop enuming modes, S_FALSE to continue
    return S_FALSE;
}

/**************************************************************************
  AppInit

  Description:
    This is called when the application is first loaded. It initializes
  all variables, registers the window class, and creates the main app
  window.
 **************************************************************************/

BOOL AppInit(HINSTANCE hInst,HINSTANCE hPrev,int sw,LPSTR szCmdLine)
{
  WNDCLASS cls;

  /* Save instance handle for DialogBoxes */
  hInstApp = hInst;

  if (!hPrev)
  {
    //***  Register a class for the main application window
    cls.hCursor        = LoadCursor(0,IDC_ARROW);

    //*** Just for fun, we'll draw our own spinning cube icon.
    cls.hIcon          = LoadIcon(hInst, "AppIcon");
    cls.lpszMenuName   = "AppMenu";
    cls.lpszClassName  = szAppName;
    cls.hbrBackground  = (HBRUSH)GetStockObject(BLACK_BRUSH);
    cls.hInstance      = hInst;
    cls.style          = CS_VREDRAW | CS_HREDRAW;
    cls.lpfnWndProc    = (WNDPROC)AppWndProc;
    cls.cbClsExtra     = 0;
    cls.cbWndExtra     = 0;

    if (!RegisterClass(&cls))
      return FALSE;
  }

  hAccelApp = LoadAccelerators(hInst, "AppAccel");

  //*** Set and normalize the light source
  LightSourceDirection = vector_4(50, 30, -15);
  LightSourceDirection.Normalize();

  //*** Distance to view plane:
  ViewPerspective.SetElement(3, 2, 1/300.0);
  ViewPerspective.SetElement(3, 3, 0);

  //*** Viewport scaling - some arbitrary number like 3.5 will do
  ViewPerspective.SetElement(0, 0, 3.5);
  ViewPerspective.SetElement(1, 1, 3.5);

  //*** Calculate the initial normals and shades
  TransformCube(CubeTransform);

  //*** Then generate an interesting rotation for the spin
  CubeTransform.ConcatenateYRotation(6.0);
  CubeTransform.ConcatenateXRotation(3.5);
  CubeTransform.ConcatenateZRotation(2.0);

  hwndApp = CreateWindowEx(
                  WS_EX_APPWINDOW,
                  szAppName,           // Class name
                  szAppName,           // Caption
                  WS_POPUP |
                  WS_SYSMENU |
                  WS_CAPTION,
		  0, 0, 	       // Position
		  640,480,	       // Size
                  0,                   // Parent window (no parent)
                  0,                   // use class menu
                  hInst,               // handle to window instance
                  0                    // no params to pass on
                  );
  ShowWindow(hwndApp,sw);
  UpdateWindow(hwndApp);

  if (!DDInit())
    return FALSE;

  // Enumerate all posible display modes, and stick them in our menu.
  // we use the extra item DWORD of a menu item to store the mode info
  HMENU hmenu = CreatePopupMenu();
  dd->EnumDisplayModes(0,NULL,(LPVOID)hmenu,ModeCallback);
  AppendMenu(GetMenu(hwndApp),MF_POPUP,(UINT)hmenu,"&Modes");

  if (!DDSetMode(640,480,8) &&
      !DDSetMode(640,480,16))
    return FALSE;

  return TRUE;
}

/**************************************************************************
  WinMain

  Description:
    The main procedure for the App.  After initializing, it just goes
  into a message-processing loop until it gets a WM_QUIT message.
 **************************************************************************/

int PASCAL WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR szCmdLine, int sw)
{
  MSG     msg;

  //*** Call initialization procedure
  if (!AppInit(hInst,hPrev,sw,szCmdLine))
    return FALSE;

    //*** Polling messages from event queue until quit
  for (;;)
  {
    if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
    {
      if (msg.message == WM_QUIT)
        break;

      if (!hwndApp || !TranslateAccelerator(hwndApp, hAccelApp, &msg))
      {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
      }
    }
    else
    {
      if (AppIdle())
        WaitMessage();
    }
  }

  DDTerm();
  return msg.wParam;
}

/**************************************************************************
  AppPause

 **************************************************************************/

void AppPause(BOOL f)
{
    if (f)
    {
        DDSCAPS caps;
        FrontBuffer->GetCaps(&caps);

        // if we are in ModeX go back to a windows mode
        // so we can see the menu or dialog box.

        if (caps.dwCaps & DDSCAPS_MODEX)
        {
            DDSetMode(640,480,8);
        }

        // turn off rotation while paused
        if (lpdiRot) lpdiRot->Unacquire();
        fMouseAcquired = FALSE;

        fAppPaused = TRUE;
        dd->FlipToGDISurface();
        DrawMenuBar(hwndApp);
        RedrawWindow(hwndApp, NULL, NULL, RDW_FRAME);
    }
    else
    {
        fAppPaused = FALSE;

    }
}

/**************************************************************************
  MagnifyCube

  Description:
    Magnify the cube the indicated number of times.  A negative number
    makes it smaller.
 **************************************************************************/

void MagnifyCube(double times)
{
    matrix_4x4 m;
    double factor = pow(1.5, times);
    m.SetElement(0,0,factor);
    m.SetElement(1,1,factor);
    m.SetElement(2,2,factor);
    TransformCube(m);
}

/**************************************************************************
  AppIdle

  return TRUE if the app is idle
  return FALSE if the app is not idle.

  Description:
 **************************************************************************/

BOOL AppIdle()
{
  DIMOUSESTATE dims;

  //*** Spin while the app is active, lbutton is up, and spinning is on.

  //*** Spin while the app is iconized.
  if (fAppActive && !fAppPaused)
  {
    //*** If the app is active, spin the cube and redraw

    // See if any zooming needs to be done.
    if(lpdiZoom &&
       lpdiZoom->GetDeviceState(sizeof(DIMOUSESTATE), &dims) == DI_OK) {
        // 240 units of motion in the Z-axis equals one unit of
        // magnification / shrinkage.
        if(dims.lZ) {
           MagnifyCube(dims.lZ / 240.0);
        }
    }

    if(fMouseAcquired)
	 {
		//** If we have the mouse acquired...

		// user spins cube if GetDeviceState succeeds and if the left button (button 0) is held
                if(lpdiRot->GetDeviceState(sizeof(DIMOUSESTATE), &dims) == DI_OK)
		{
         if(dims.rgbButtons[0] & 0x80)
         {
            if(dims.lX || dims.lY)
            {
               matrix_4x4 Movement;
               Movement.ConcatenateYRotation(dims.lX);
               Movement.ConcatenateXRotation(dims.lY);
               TransformCube(Movement);
            }

         }
         else
		   {
			   // unacquire the mouse
                           lpdiRot->Unacquire();
			   fMouseAcquired = FALSE;
		   }
      }
    }
    else
    {
         TransformCube(CubeTransform);
    }
    RenderFrame();
    return FALSE;
  }
  else
  {
    //*** Don't do anything when not the active app
    return TRUE;
  }
}

/**************************************************************************
  RenderFrame

  render the frame into the back buffer and do a page flip.

  things to NOTE:

    we use the blter to clear the backbuffer, this usualy is a big
    win blters are real fast.

    we use GDI to draw the frame rate, and info text

    we either use GDI to draw the faces of the cube, or our own code
    based on the fDrawWithGDI global variable.

 **************************************************************************/

int FrameRate;
int FrameCount;
int FrameCount0;
DWORD FrameTime;
DWORD FrameTime0;

void RenderFrame()
{
  HDC hdc;

  //*** always need to handle DDERR_SURFACELOST, this will happen
  //*** when we get switched away from.

  if (FrontBuffer->IsLost() == DDERR_SURFACELOST)
    FrontBuffer->Restore();

  //*** use the blter to do a color fill to clear the back buffer

  DDBLTFX ddbltfx;
  ddbltfx.dwSize = sizeof(ddbltfx);
  ddbltfx.dwFillColor = 0;
  BackBuffer->Blt(NULL,NULL,NULL,DDBLT_COLORFILL | DDBLT_WAIT,&ddbltfx);

  //*** based on the fDrawWithGDI global variable, we either
  //*** render the polygons ourself or let GDI do it

  BOOL fGDI = fDrawWithGDI;

  //*** render the cube with our own code.
  //*** we need to do this outside of the GetDC, because we cant
  //*** lock a buffer while we have a DC on it.
  //*** if ProjectAndDrawCube returns FALSE it did not want to
  //*** draw for some reason, so go ahead and use GDI

  if (!fGDI)
     fGDI = !ProjectAndDrawCube(BackBuffer, ScreenSize.cx/2, ScreenSize.cy/2);

  if (BackBuffer->GetDC(&hdc) == DD_OK)
  {
    //*** use GDI to draw the cube.
    if (fGDI)
      ProjectAndDrawCube(hdc, ScreenSize.cx/2, ScreenSize.cy/2);

    //*** draw stats, like frame number and frame rate

    char ach[128];
    int len;
    static char szHelp[] = "F10=Menu F7=Smaller F8=Larger";

    SetBkMode(hdc, TRANSPARENT);
    SelectObject(hdc, AppFont);

    len = wsprintf(ach, "FPS %02d Frame %05d", FrameRate, FrameCount);

    SetTextColor(hdc, RGB(255, 255, 0));
    TextOut(hdc, 0, 0, ach, len);
    TextOut(hdc, 0, ScreenSize.cy-(ScreenSize.cx<640 ? 24:48),szHelp,sizeof(szHelp)-1);

    BackBuffer->ReleaseDC(hdc);
  }

  //*** we have rendered the backbuffer, call flip so we can see it
  FrontBuffer->Flip(NULL, DDFLIP_WAIT);

  FrameCount++;
  FrameTime = timeGetTime();

  if (FrameTime - FrameTime0 > 1000)
  {
    FrameRate = (FrameCount - FrameCount0) * 1000 / (FrameTime - FrameTime0);
    FrameTime0 = FrameTime;
    FrameCount0 = FrameCount;
  }
}

/**************************************************************************
  AppInitMenuPopup

    If it's the Cube menu, then check or uncheck the GDI item accordingly.

    If it's the mode list popup, then add a MENUBARBREAK as necessary.

 **************************************************************************/

void AppInitMenuPopup(HWND hwnd, HMENU hmenuPopup, UINT uPos, BOOL fSys)
{
    if (fSys) return;       /* Don't mess with the sysmenu */

    switch (uPos) {
    case 0:                 /* Cube menu */
        CheckMenuItem(hmenuPopup, MENU_GDI,
                      fDrawWithGDI ? MF_CHECKED : MF_UNCHECKED);
        break;

    case 1:                 /* Mode menu */
        /*
         *  Compute how many menu items fit on the screen.
         *
         *  Note that we use ScreenSize instead of SM_CYSCREEN.
         *  This allows us to do the right thing in the face of
         *  multiple monitors.  (ScreenSize is the size of our
         *  monitor.)
         */
        int cmi;

        cmi = GetMenuItemCount(hmenuPopup);
        if (cmi) {

            RECT rcClient;
            GetClientRect(hwnd, &rcClient);

            RECT rc;
            GetMenuItemRect(hwnd, hmenuPopup, 0, &rc);

            int dyMenuItem = rc.bottom - rc.top;

            /*
             *  Aargh.  If the menu has never appeared yet, USER
             *  returns an empty rectangle.  DON'T DIVIDE BY ZERO!
             *
             *  In such case, we use the height of the menu bar.
             *  Not perfect, but close enough.  And it happens only
             *  once.
             */
            if (dyMenuItem == 0) {
                dyMenuItem = GetSystemMetrics(SM_CYMENU);
            }

            /*
             *  Aargh.  You can't change MF_MENUBARBREAK without
             *  also changing the text, so we have to get the
             *  old text and set it back.
             *
             *  While we're here, we may as well put a check-box
             *  next to the item that matches our current screen res.
             */

            HDC hdc = GetDC(0);

            DWORD dwItemDataMatch = MAKEMENUITEMDATA(
                            GetDeviceCaps(hdc, HORZRES),
                            GetDeviceCaps(hdc, VERTRES),
                            GetDeviceCaps(hdc, BITSPIXEL) *
                            GetDeviceCaps(hdc, PLANES));
            ReleaseDC(0, hdc);


            MENUITEMINFO mii;
            TCHAR tsz[80];

            mii.cbSize = sizeof(mii);
            mii.fMask = MIIM_TYPE | MIIM_DATA | MIIM_STATE;
            mii.dwTypeData = tsz;

            /*
             *  Compute the number of MI's that fit in our client area.
             *  Note: Client area, not screen size.  This ensures that
             *  the menu pops in a reasonable location.
             */

            int cmiScreen = rcClient.bottom / dyMenuItem;
 BOOL bModeMatch = FALSE;
            for (int imi = 0; imi < cmi; imi++) {
                mii.cch = sizeof(tsz) / sizeof(tsz[0]);
                if (GetMenuItemInfo(hmenuPopup, imi, MF_BYPOSITION, &mii)) {
                    if (imi > 0 && imi % cmiScreen == 0) {
                        mii.fType |= MFT_MENUBARBREAK;
                    } else {
                        mii.fType &= ~MFT_MENUBARBREAK;
                    }

                    if (mii.dwItemData == dwItemDataMatch) {
                        mii.fState |= MFS_CHECKED;
bModeMatch = TRUE;
                    } else {
                        mii.fState &= ~MFS_CHECKED;
                    }

                    SetMenuItemInfo(hmenuPopup, imi, MF_BYPOSITION, &mii);
                }
            }
if(bModeMatch == FALSE) _asm int 3

        }
        break;
    }

}

/**************************************************************************
  AppWndProc

  Description:
    Main window proc. Standard Windows fare.
 **************************************************************************/

LONG CALLBACK AppWndProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
  RECT Rect;

  switch (msg)
  {
    case WM_CREATE:
      break;

    case WM_ACTIVATEAPP:
      //*** Keep track of whether or not the app is in the foreground
      fAppActive = (BOOL)wParam;
          // re-acquire the zooming controller when we are activated
          if (fAppActive) {
                if (lpdiZoom) lpdiZoom->Acquire();
          } else{           // unacquire everything if app is not active
                if (lpdiZoom) lpdiZoom->Unacquire();
                if (lpdiRot) lpdiRot->Unacquire();
		fMouseAcquired = FALSE;
	  }
      break;

    case WM_SETCURSOR:
      if (fAppActive && !fAppPaused)
      {
        SetCursor(NULL);
        return 1;
      }
      break;

    case WM_ENTERMENULOOP:
      AppPause(TRUE);
      break;

    case WM_EXITMENULOOP:
      AppPause(FALSE);
      break;

    case WM_INITMENUPOPUP:
        AppInitMenuPopup(hwnd, (HMENU)wParam,
                         (UINT)LOWORD(lParam), (BOOL)HIWORD(lParam));
        break;

    case WM_COMMAND:
      switch(LOWORD(wParam))
      {
        case MENU_ABOUT:
          AppPause(TRUE);
          DialogBox(hInstApp, "AppAbout", hwnd, (DLGPROC)AppAbout);
          AppPause(FALSE);
          break;

        case MENU_EXIT:
          PostMessage(hwnd, WM_CLOSE, 0, 0L);
          break;

        case MENU_LARGER:
          MagnifyCube(+1.0);
          break;

        case MENU_SMALLER:
          MagnifyCube(-1.0);
          break;

        case MENU_GDI:
          fDrawWithGDI = !fDrawWithGDI;
          break;
      }
      if (LOWORD(wParam) >= MENU_MODE && LOWORD(wParam) < MENU_MODE+100)
      {
        MENUITEMINFO mii;

        mii.cbSize = sizeof(mii);
        mii.fMask = MIIM_DATA;
        GetMenuItemInfo(GetMenu(hwnd), LOWORD(wParam), MF_BYCOMMAND, &mii);

        DDSetMode(
            (mii.dwItemData >> 0)  & 0xFFF,
            (mii.dwItemData >> 12) & 0xFFF,
            (mii.dwItemData >> 24) & 0x0FF);
      }
      return 0L;

    case WM_DESTROY:
	  // clean up DirectInput objects
          if (fMouseAcquired) lpdiRot->Unacquire();
          if (lpdiZoom)  lpdiZoom->Release(), lpdiZoom = NULL;
          if (lpdiRot)   lpdiRot ->Release(), lpdiRot  = NULL;
          if (lpdi)      lpdi    ->Release(), lpdi     = NULL;

      hwndApp = NULL;
      PostQuitMessage(0);
      break;

    case WM_PAINT:
      break;

    case WM_MOVE:
    case WM_SIZE:
    case WM_DISPLAYCHANGE:
      if (fAppActive && !IsIconic(hwnd))
      {
        SetRect(&Rect, 0, GetSystemMetrics(SM_CYCAPTION), GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
        AdjustWindowRectEx(&Rect, WS_POPUP | WS_CAPTION, FALSE, 0);
        SetWindowPos(hwnd, NULL, Rect.left, Rect.top, Rect.right-Rect.left, Rect.bottom-Rect.top, SWP_NOACTIVATE | SWP_NOZORDER);
      }
      break;

    case WM_LBUTTONDOWN:
    case WM_RBUTTONDOWN:
    case WM_MBUTTONDOWN:
          if(lpdiRot->Acquire() == DI_OK)
     {
        fMouseAcquired = TRUE;
     }
	  else
	  {
		// not acquired, mouse will not do anything
	  }
      break;

  }

  return DefWindowProc(hwnd,msg,wParam,lParam);
}

/**************************************************************************
  TransformCube

  Description:
    Transforms the cube vertices by the current rotation matrix.
    Recalculates normals and flat shade values for the
  directional light source.
 **************************************************************************/

void TransformCube(matrix_4x4 const &Transform)
{
  int i;

  //*** Transform the cube by the matrix
  for (i = 0; i < 8; ++i)
    CubeVertices[i] = Transform * CubeVertices[i];

  //*** Recalculate normals and shades
  for (i = 0; i < 6; ++i)
  {
    //*** Normals are perpendicular to two edges of the cube
    vector_4 Edge1, Edge2;
    Edge1 = CubeVertices[CubeFaces[i][1]] - CubeVertices[CubeFaces[i][0]];
    Edge2 = CubeVertices[CubeFaces[i][3]] - CubeVertices[CubeFaces[i][0]];
    CubeSurfaceNormals[i] = CrossProduct(Edge1, Edge2);
    CubeSurfaceNormals[i].Normalize();

    //*** Cosine shading based on the surface normal, clamped to [0, 1]
    real Shade = DotProduct(CubeSurfaceNormals[i], LightSourceDirection);
    Shade = Shade + AmbientLight;
    if (Shade < 0) Shade = 0;
    else if (Shade > 1.0) Shade = 1.0;
    CubeSurfaceShades[i] = Shade;
  }
}

/**************************************************************************
  ProjectAndDrawCube

  Description:
    Projects the cube vertices for the current viewpoint then culls
  in screen space and draws into the DC via GDI.
 **************************************************************************/

BOOL ProjectAndDrawCube(HDC hdc, int XOffset, int YOffset)
{
  //*** Create a viewing transform for the current eye position
  vector_4 ViewDirection = Origin - Viewpoint;
  ViewDirection.Normalize();
  view_transform View(Viewpoint, ViewDirection, Up);

  //*** Transform and project the vertices into screen space
  int i;
  POINT aScreenVertices[8];
  for (i = 0; i < 8; ++i)
  {
    point_4 Temp = View * CubeVertices[i];
    Temp = ViewPerspective * Temp;
    Temp.Homogenize();

    aScreenVertices[i].x = (int)Temp.GetX() + XOffset;
    aScreenVertices[i].y = (int)Temp.GetY() + YOffset;
  }

  SelectPen(hdc, GetStockPen(NULL_PEN));

  for (i = 0; i < 6; ++i)
  {
    //*** Standard culling operation based on the z value of the
    //*** cross product of the edges: are the vertices oriented in the
    //*** counterclockwise or clockwise direction?
    real v1 = aScreenVertices[ CubeFaces[i][2] ].x -
      aScreenVertices[ CubeFaces[i][1] ].x;
    real w1 = aScreenVertices[ CubeFaces[i][0] ].x -
      aScreenVertices[ CubeFaces[i][1] ].x;
    real v2 = aScreenVertices[ CubeFaces[i][2] ].y -
      aScreenVertices[ CubeFaces[i][1] ].y;
    real w2 = aScreenVertices[ CubeFaces[i][0] ].y -
      aScreenVertices[ CubeFaces[i][1] ].y;
    if ((v1*w2 - v2*w1) <= 0)
      continue;

    //*** Create a brush for the shaded face color using the selected dither

    HBRUSH hbr;

    //*** Get the shading colors

    int Red, Green, Blue;

    Red   = (int)(CubeColors[i][0] * CubeSurfaceShades[i]);
    Green = (int)(CubeColors[i][1] * CubeSurfaceShades[i]);
    Blue  = (int)(CubeColors[i][2] * CubeSurfaceShades[i]);

    //*** Create the dithered or PALETTERGB brush

    COLORREF cr;

    cr = RGB(Red, Green, Blue);
    hbr = CreateSolidBrush(cr);

    //*** Collect the correct points in an array
    POINT aQuadVertices[4];
    for (int j = 0; j < 4; ++j)
      aQuadVertices[j] = aScreenVertices[ CubeFaces[i][j] ];

    //*** Use GDI to draw the face
    hbr = SelectBrush(hdc, hbr);
    Polygon(hdc, aQuadVertices, 4);
    hbr = SelectBrush(hdc, hbr);
    DeleteObject(hbr);
  }

  return TRUE;
}

/**************************************************************************
  ProjectAndDrawCube

  Description:
    Projects the cube vertices for the current viewpoint then culls
  in screen space and draws them into a DirectDrawSurface via custom code
 **************************************************************************/

BOOL ProjectAndDrawCube(IDirectDrawSurface *pdds, int XOffset, int YOffset)
{
  //*** Lock the DirectDraw surface
  DDSURFACEDESC ddsd;
  ddsd.dwSize = sizeof(ddsd);

  if (pdds->Lock(NULL, &ddsd, DDLOCK_WAIT, NULL) != DD_OK)
    return FALSE;

  //*** This code only works for 8bpp
  if (ddsd.ddpfPixelFormat.dwRGBBitCount != 8)
  {
    pdds->Unlock(NULL);
    return FALSE;
  }

  //*** Create a viewing transform for the current eye position
  vector_4 ViewDirection = Origin - Viewpoint;
  ViewDirection.Normalize();
  view_transform View(Viewpoint, ViewDirection, Up);

  //*** Transform and project the vertices into screen space
  int i;
  POINT aScreenVertices[8];
  for (i = 0; i < 8; ++i)
  {
    point_4 Temp = View * CubeVertices[i];
    Temp = ViewPerspective * Temp;
    Temp.Homogenize();

    aScreenVertices[i].x = (int)Temp.GetX() + XOffset;
    aScreenVertices[i].y = (int)Temp.GetY() + YOffset;

    //*** !!! OUR CODE DOES NOT CLIP, SO FAIL IF WE NEED CLIPPING
    if (aScreenVertices[i].x < 0 || aScreenVertices[i].x >= ScreenSize.cx ||
        aScreenVertices[i].y < 0 || aScreenVertices[i].y >= ScreenSize.cy)
    {
      pdds->Unlock(NULL);
      return FALSE;
    }
  }

  for (i = 0; i < 6; ++i)
  {
    //*** Standard culling operation based on the z value of the
    //*** cross product of the edges: are the vertices oriented in the
    //*** counterclockwise or clockwise direction?
    real v1 = aScreenVertices[ CubeFaces[i][2] ].x -
      aScreenVertices[ CubeFaces[i][1] ].x;
    real w1 = aScreenVertices[ CubeFaces[i][0] ].x -
      aScreenVertices[ CubeFaces[i][1] ].x;
    real v2 = aScreenVertices[ CubeFaces[i][2] ].y -
      aScreenVertices[ CubeFaces[i][1] ].y;
    real w2 = aScreenVertices[ CubeFaces[i][0] ].y -
      aScreenVertices[ CubeFaces[i][1] ].y;
    if ((v1*w2 - v2*w1) <= 0)
      continue;

    //*** Get the shading color, palette is setup like so:
    //*** 10 system, 64 red, 64 green, 64 blue

    BYTE color;

    if (CubeColors[i][0] >= 128)
        color = (BYTE)(10 + 0*64 + (63 * CubeSurfaceShades[i]));
    else if (CubeColors[i][1] >= 128)
        color = (BYTE)(10 + 1*64 + (63 * CubeSurfaceShades[i]));
    else
        color = (BYTE)(10 + 2*64 + (63 * CubeSurfaceShades[i]));

    //*** Use code in tri.cpp draw the face

    Triangle8((BYTE*)ddsd.lpSurface, ddsd.lPitch,
        aScreenVertices[CubeFaces[i][0]],
        aScreenVertices[CubeFaces[i][1]],
        aScreenVertices[CubeFaces[i][2]],
        color);

    Triangle8((BYTE*)ddsd.lpSurface, ddsd.lPitch,
        aScreenVertices[CubeFaces[i][2]],
        aScreenVertices[CubeFaces[i][3]],
        aScreenVertices[CubeFaces[i][0]],
        color);
  }

  //*** Never ever forget to unlock!
  pdds->Unlock(NULL);
  return TRUE;
}
