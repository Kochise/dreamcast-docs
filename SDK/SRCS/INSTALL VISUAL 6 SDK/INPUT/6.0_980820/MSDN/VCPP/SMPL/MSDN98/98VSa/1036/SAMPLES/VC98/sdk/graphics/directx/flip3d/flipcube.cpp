/**************************************************************************

    FLIP3D.CPP - A spinning cube demo for DirectDraw

    using Direct3D imediate mode (RenderPrimitive) for rendering.

    uses D3DTLVERTEX, this app does all its own transform and lighting
    dumb3d.cpp is our "3d" package.

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

#define D3D_OVERLOADS

#include <windows.h>
#include <windowsx.h>
#include <mmsystem.h>
#include <ddraw.h>
#include <d3d.h>
#include <math.h>

#include "flipcube.h"
#include "dumb3d.h"
#include "d3dtex.h"

/**************************************************************************
  Global Variables
 **************************************************************************/

char szAppName[]="Flip3D";

HINSTANCE  hInstApp;
BOOL       fAppActive;
BOOL       fAppPaused;
HWND       hwndApp;
HACCEL     hAccelApp;
HFONT      AppFont;
SIZE	   ScreenSize;

/**************************************************************************
  DirectDraw Globals
 **************************************************************************/

IDirectDraw            *dd;
IDirectDrawSurface     *FrontBuffer;
IDirectDrawSurface     *BackBuffer;
IDirectDrawPalette     *Palette;
char                    DeviceName[128];

/**************************************************************************
  Direct3D Globals
 **************************************************************************/

IDirect3D2             *d3d;
IDirect3DDevice2       *d3dDevice;
IDirect3DViewport2     *d3dViewport;
IDirect3DLight         *d3dLight;
char                   *d3dName;

D3DCULL                 CullMode = D3DCULL_CCW;

D3DTexture              Texture;

D3DTEXTUREHANDLE TextureHandle      = 0;
BOOL             TexturePerspective = TRUE;
BOOL             TextureDither      = FALSE;
D3DTEXTUREBLEND  TextureBlend       = D3DTBLEND_MODULATE;
D3DMATERIALHANDLE hMat				= 0;
LPDIRECT3DMATERIAL2 lpMat			=NULL;

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

//*** Interaction
static POINT       Move;
static POINT       Last;

/**************************************************************************
   Internal function declarations
 **************************************************************************/
LONG  CALLBACK AppWndProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam);
BOOL  AppIdle(void);
void  ClearFrame(void);
void  RenderFrame(void);

void  TransformCube(matrix_4x4 const &Transform);

/**************************************************************************
 **************************************************************************/
BOOL  ProjectAndDrawCube(IDirect3DDevice2 *pd3d, int XOffset, int YOffset);

/**************************************************************************
 **************************************************************************/
void BuildDeviceMenu(void);
void BuildModeMenu(void);
BOOL DDSetMode(int,int,int);

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
  DDTerm
 **************************************************************************/

#define RELEASE(x) if (x) { x->Release(); x = NULL; }

void DDTerm(BOOL fAll=TRUE)
{
    RELEASE(d3dDevice);
    RELEASE(d3dViewport);
    RELEASE(d3dLight);

    RELEASE(BackBuffer);
    RELEASE(FrontBuffer);
    RELEASE(Palette);
	RELEASE(lpMat);

    Texture.Release();

    if (fAll)
    {
        RELEASE(d3d);
        RELEASE(dd);
    }
}

/**************************************************************************
 * FindDeviceCallback
 **************************************************************************/

BOOL CALLBACK FindDeviceCallback(GUID* lpGUID, LPSTR szName, LPSTR szDevice, LPVOID lParam)
{
    char ach[128];
    char * szFind = (char *)lParam;

    wsprintf(ach,"%s (%s)",szName, szDevice);

    if (lstrcmpi(szFind, szDevice) == 0 || lstrcmpi(szFind, ach) == 0)
    {
        DirectDrawCreate(lpGUID, &dd, NULL);
        return DDENUMRET_CANCEL;
    }
    return DDENUMRET_OK;
}

/**************************************************************************
  DDInit

  Description:
    initialize all the DirectDraw/Direct3D specific stuff
 **************************************************************************/

BOOL DDInit(char *szDevice=NULL)
{
    HRESULT err;

    DDTerm();

    if (szDevice && szDevice[0])
        DirectDrawEnumerate(FindDeviceCallback, (LPVOID)szDevice);

    if (dd == NULL)
    {
        szDevice = NULL;
        err = DirectDrawCreate(NULL, &dd, NULL);
    }

    if (dd == NULL)
    {
        MessageBox(hwndApp, "This app requires DirectDraw", szAppName, MB_OK);
        return FALSE;
    }

    err = dd->SetCooperativeLevel(hwndApp,
        DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN | DDSCL_ALLOWMODEX);

    if (err != DD_OK)
        return FALSE;

    err = dd->QueryInterface(IID_IDirect3D2, (void**)&d3d);

    if (err != DD_OK)
    {
        MessageBox(hwndApp, "This app requires DirectX 5.0", szAppName, MB_OK);
        return FALSE;
    }
    //
    //Not imp
    //
    BuildModeMenu();

    if (!DDSetMode(640,480,16) &&
        !DDSetMode(640,480,8))
    {
        return FALSE;
    }

    char ach[128];
    wsprintf(ach, "%s - %s %s", szAppName, szDevice ? szDevice : "DISPLAY", d3dName);
    SetWindowText(hwndApp, ach);

    return TRUE;
}

/**************************************************************************
  Init3DState
 **************************************************************************/
BOOL Init3DState()
{
    D3DMATERIAL mat;
	
    /*
     * Set default render state
     */
    d3dDevice->SetRenderState(D3DRENDERSTATE_ZENABLE, 0);
    d3dDevice->SetRenderState(D3DRENDERSTATE_ZWRITEENABLE, 0);
    d3dDevice->SetRenderState(D3DRENDERSTATE_SHADEMODE, D3DSHADE_FLAT);

    /*
     * load our single texture map from a resource
     */
    Texture.Load(d3dDevice, "Win95");
//  Texture.Load(d3dDevice, "Checker");
    TextureHandle = Texture.GetHandle();

    if (d3d->CreateMaterial(&lpMat, NULL) != D3D_OK) {
		return FALSE;
    }
    memset(&mat, 0, sizeof(D3DMATERIAL));
    mat.dwSize = sizeof(D3DMATERIAL);
    mat.diffuse.r = (D3DVALUE)1.0;
    mat.diffuse.g = (D3DVALUE)1.0;
    mat.diffuse.b = (D3DVALUE)1.0;
    mat.ambient.r = (D3DVALUE)1.0;
    mat.ambient.g = (D3DVALUE)1.0;
    mat.ambient.b = (D3DVALUE)1.0;
    mat.specular.r = (D3DVALUE)1.0;
    mat.specular.g = (D3DVALUE)1.0;
    mat.specular.b = (D3DVALUE)1.0;
    mat.power = (float)40.0;
    mat.hTexture = TextureHandle;
    mat.dwRampSize = 1;
    lpMat->SetMaterial(&mat);
    lpMat->GetHandle(d3dDevice, &hMat);

    return TRUE;
}

/**************************************************************************
  Init3D
 **************************************************************************/
BOOL Init3D()
{
    HRESULT err = E_FAIL;

    //
    // create a Direct3D device.
    // first try HAL, then RGB, RAMP
    //
    d3dName = "HAL";
    err = d3d->CreateDevice(IID_IDirect3DHALDevice, BackBuffer, &d3dDevice);
    
    if (err != DD_OK)
    {
        d3dName = "RGB";
        err = d3d->CreateDevice(IID_IDirect3DRGBDevice, BackBuffer, &d3dDevice);
    }

    if (err != DD_OK)
    {
        d3dName = "RAMP";
        err = d3d->CreateDevice(IID_IDirect3DRampDevice, BackBuffer, &d3dDevice);
    }

    if (err != DD_OK)
        return FALSE;

    //
    // now make a Viewport
    //
    err = d3d->CreateViewport(&d3dViewport, NULL);

    if (err != DD_OK)
        return FALSE;

    err = d3dDevice->AddViewport(d3dViewport);

    /*
     * Setup the viewport for a reasonable viewing area
     */
    D3DVIEWPORT2 viewData;
    memset(&viewData, 0, sizeof(D3DVIEWPORT2));
    viewData.dwSize = sizeof(D3DVIEWPORT2);
    viewData.dwX = 0;
    viewData.dwY = 0;
    viewData.dwWidth  = ScreenSize.cx;
    viewData.dwHeight = ScreenSize.cy;
    viewData.dvClipX = -1.0f;
    viewData.dvClipWidth = 2.0f;
    viewData.dvClipHeight = (D3DVALUE)(ScreenSize.cy * 2.0 / ScreenSize.cx);
    viewData.dvClipY = viewData.dvClipHeight / 2.0f;
    viewData.dvMinZ = 0.0f;
    viewData.dvMaxZ = 1.0f;
    err = d3dViewport->SetViewport2(&viewData);

    if (err != DD_OK)
	return FALSE;

    err = d3dDevice->SetCurrentViewport(d3dViewport);

    if (err != DD_OK)
        return FALSE;

    if (!Init3DState())
	return FALSE;

    return TRUE;
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
    DDTerm(FALSE);

    //
    // Create surfaces
    //
    // what we want is a double buffered surface in video memory
    // so we try to create this first.
    //
    // if we cant get a double buffered surface, we try for a double
    // buffered surface not being specific about video memory, we will
    // get back a main-memory surface, that wont use HW page flipping
    // but at least we run.
    //
    // NOTE you need to recreate the surfaces for a new display mode
    // they wont work when/if the mode is changed.
    //
    DDSURFACEDESC ddsd;

    ZeroMemory(&ddsd, sizeof(ddsd));
    ddsd.dwSize = sizeof(ddsd);
    ddsd.dwFlags = DDSD_CAPS | DDSD_BACKBUFFERCOUNT;
    ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE |
                          DDSCAPS_FLIP |
                          DDSCAPS_COMPLEX |
                          DDSCAPS_3DDEVICE |
                          DDSCAPS_VIDEOMEMORY;
#ifdef TRIPLE_BUFFER
    ddsd.dwBackBufferCount = 2;
#else
    ddsd.dwBackBufferCount = 1;
#endif

    // try to get a triple/double buffered video memory surface.
    err = dd->CreateSurface(&ddsd, &FrontBuffer, NULL);

    // try to get a double buffered video memory surface.
    if (err != DD_OK && ddsd.dwBackBufferCount == 2)
    {
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
    if (bpp == 8)
    {
        PALETTEENTRY ape[256];

        // get the current windows colors.
        GetPaletteEntries((HPALETTE)GetStockObject(DEFAULT_PALETTE), 0,  10, &ape[0]);
        GetPaletteEntries((HPALETTE)GetStockObject(DEFAULT_PALETTE), 10, 10, &ape[246]);

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
            BackBuffer->SetPalette(Palette);
        }
    }

    if (!Init3D())
        return FALSE;

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
  BuildModeMenu
 **************************************************************************/
#define MAKEMENUITEMDATA(width, height, bpp) \
        (width) | ((height) << 12) | ((bpp) << 24)

HRESULT CALLBACK BuildModeMenuCallback(LPDDSURFACEDESC pdds, LPVOID lParam)
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

void BuildModeMenu()
{
    // Enumerate all posible display modes, and stick them in our menu.
    // we use the extra item DWORD of a menu item to store the mode info

    DeleteMenu(GetMenu(hwndApp), 2, MF_BYPOSITION);

    HMENU hmenu = CreatePopupMenu();
    dd->EnumDisplayModes(0,NULL,(LPVOID)hmenu,BuildModeMenuCallback);
    AppendMenu(GetMenu(hwndApp),MF_POPUP,(UINT)hmenu,"&Modes");
}

/**************************************************************************
 * BuildDeviceMenu
 **************************************************************************/

BOOL CALLBACK BuildDeviceMenuCallback(GUID* lpGUID, LPSTR szName, LPSTR szDevice, LPVOID lParam)
{
    HMENU hmenu = (HMENU)lParam;
    char ach[80];
    int n;

    n = GetMenuItemCount(hmenu);
    wsprintf(ach,"%s (%s)",szName, szDevice);
    AppendMenu(hmenu,MF_STRING,MENU_DEVICE+n,ach);
    return DDENUMRET_OK;
}

void BuildDeviceMenu()
{
    HMENU hmenu = CreatePopupMenu();
    DirectDrawEnumerate(BuildDeviceMenuCallback, (LPVOID)hmenu);
    AppendMenu(GetMenu(hwndApp),MF_POPUP,(UINT)hmenu,"&Device");
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

  BuildDeviceMenu();

  //
  // read the device name from WIN.INI so we come up on the last device
  // that the user picked.
  //
  GetProfileString(szAppName, "Device", "", DeviceName, sizeof(DeviceName));

  if (!DDInit(DeviceName))
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
  //*** Spin while the app is active, lbutton is up, and spinning is on.

  //*** Spin while the app is iconized.
  if (fAppActive && !fAppPaused)
  {
    //*** If the app is active, spin the cube and redraw
    if (GetAsyncKeyState(VK_LBUTTON) < 0)
    {
        if(Move.x || Move.y)
        {
            matrix_4x4 Movement;
            Movement.ConcatenateYRotation(Move.x);
            Movement.ConcatenateXRotation(Move.y);
            Move.x = Move.y = 0;
            TransformCube(Movement);
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
  {
     FrontBuffer->Restore();
     Texture.Restore();
  }

  //*** use the blter to do a color fill to clear the back buffer

  DDBLTFX ddbltfx;
  ddbltfx.dwSize = sizeof(ddbltfx);
  ddbltfx.dwFillColor = 0;
  BackBuffer->Blt(NULL,NULL,NULL,DDBLT_COLORFILL | DDBLT_WAIT,&ddbltfx);

  ProjectAndDrawCube(d3dDevice, ScreenSize.cx/2, ScreenSize.cy/2);

  if (BackBuffer->GetDC(&hdc) == DD_OK)
  {
    //*** draw stats, like frame number and frame rate

    char ach[128];
    int len;
    static char szHelp[] = "F10=Menu F7=Smaller F8=Larger";

    SetBkMode(hdc, TRANSPARENT);
    SelectObject(hdc, AppFont);

    len = wsprintf(ach, "FPS %02d Frame %05d (%s)", FrameRate, FrameCount, d3dName);

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

void AppInitMenuPopup(HWND hwnd, HMENU hmenu, UINT uPos, BOOL fSys)
{
    if (fSys) return;       /* Don't mess with the sysmenu */

    switch (uPos) {
    case 0:                 /* Cube menu */
        CheckMenuItem(hmenu, MENU_CULL_NONE, CullMode == D3DCULL_NONE ? MF_CHECKED : MF_UNCHECKED);
        CheckMenuItem(hmenu, MENU_CULL_CW,   CullMode == D3DCULL_CW   ? MF_CHECKED : MF_UNCHECKED);
        CheckMenuItem(hmenu, MENU_CULL_CCW,  CullMode == D3DCULL_CCW  ? MF_CHECKED : MF_UNCHECKED);

        CheckMenuItem(hmenu, MENU_TEXTURE,    TextureHandle ? MF_CHECKED : MF_UNCHECKED);
        CheckMenuItem(hmenu, MENU_DITHER,     TextureDither ? MF_CHECKED : MF_UNCHECKED);
        CheckMenuItem(hmenu, MENU_PERSPECTIVE,TexturePerspective ? MF_CHECKED : MF_UNCHECKED);
        CheckMenuItem(hmenu, MENU_MODULATE,   TextureBlend == D3DTBLEND_MODULATE ? MF_CHECKED : MF_UNCHECKED);
        CheckMenuItem(hmenu, MENU_COPY,       TextureBlend == D3DTBLEND_COPY ? MF_CHECKED : MF_UNCHECKED);
        CheckMenuItem(hmenu, MENU_DECAL,      TextureBlend == D3DTBLEND_DECAL ? MF_CHECKED : MF_UNCHECKED);
        break;

    case 1:                 /* Device menu */
    case 2:                 /* Mode menu */
        /*
         *  Compute how many menu items fit on the screen.
         *
         *  Note that we use ScreenSize instead of SM_CYSCREEN.
         *  This allows us to do the right thing in the face of
         *  multiple monitors.  (ScreenSize is the size of our
         *  monitor.)
         */
        int cmi;

        cmi = GetMenuItemCount(hmenu);
        if (cmi) {

            RECT rcClient;
            GetClientRect(hwnd, &rcClient);

            RECT rc;
            GetMenuItemRect(hwnd, hmenu, 0, &rc);

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

            DDSURFACEDESC ddsd;
            ZeroMemory(&ddsd, sizeof(ddsd));
            ddsd.dwSize = sizeof(ddsd);
            FrontBuffer->GetSurfaceDesc(&ddsd);
            int width  = ddsd.dwWidth;
            int height = ddsd.dwHeight;
            int bpp    = ddsd.ddpfPixelFormat.dwRGBBitCount;
            DWORD dwItemDataMatch = MAKEMENUITEMDATA(width, height, bpp);

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

            for (int imi = 0; imi < cmi; imi++) {
                mii.cch = sizeof(tsz) / sizeof(tsz[0]);
                if (GetMenuItemInfo(hmenu, imi, MF_BYPOSITION, &mii)) {
                    if (imi > 0 && imi % cmiScreen == 0) {
                        mii.fType |= MFT_MENUBARBREAK;
                    } else {
                        mii.fType &= ~MFT_MENUBARBREAK;
                    }

                    if (mii.dwItemData == dwItemDataMatch) {
                        mii.fState |= MFS_CHECKED;
                    } else {
                        mii.fState &= ~MFS_CHECKED;
                    }

                    SetMenuItemInfo(hmenu, imi, MF_BYPOSITION, &mii);
                }
            }

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
  switch (msg)
  {
    case WM_CREATE:
      break;

    case WM_ACTIVATEAPP:
      //*** Keep track of whether or not the app is in the foreground
      fAppActive = (BOOL)wParam;
      break;

    case WM_SETCURSOR:
      if (fAppActive && !fAppPaused && BackBuffer)
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

        case MENU_TEXTURE:
          TextureHandle = TextureHandle ? 0 : Texture.GetHandle();
          break;

        case MENU_PERSPECTIVE:  TexturePerspective = !TexturePerspective; break;
        case MENU_DITHER:       TextureDither      = !TextureDither; break;

        case MENU_MODULATE:     TextureBlend = D3DTBLEND_MODULATE; break;
        case MENU_COPY:         TextureBlend = D3DTBLEND_COPY;     break;
        case MENU_DECAL:        TextureBlend = D3DTBLEND_DECAL;    break;

        case MENU_CULL_NONE:    CullMode = D3DCULL_NONE; break;
        case MENU_CULL_CW:      CullMode = D3DCULL_CW;   break;
        case MENU_CULL_CCW:     CullMode = D3DCULL_CCW;  break;
      }
      if (LOWORD(wParam) >= MENU_DEVICE && LOWORD(wParam) < MENU_DEVICE+100)
      {
        GetMenuString(GetMenu(hwnd), LOWORD(wParam), DeviceName, sizeof(DeviceName), MF_BYCOMMAND);
        WriteProfileString(szAppName, "Device", DeviceName);
        DDInit(DeviceName);
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
      hwndApp = NULL;
      PostQuitMessage(0);
      break;

    case WM_PAINT:
      break;

#if 0   // fullscreen apps dont need to do this!
        // and using SM_CYSCREEN is incorrect for other devices.
    case WM_MOVE:
    case WM_SIZE:
    case WM_DISPLAYCHANGE:
      if (fAppActive && !IsIconic(hwnd))
      {
	RECT Rect;
	SetRect(&Rect, 0, GetSystemMetrics(SM_CYCAPTION), GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
        AdjustWindowRectEx(&Rect, WS_POPUP | WS_CAPTION, FALSE, 0);
        SetWindowPos(hwnd, NULL, Rect.left, Rect.top, Rect.right-Rect.left, Rect.bottom-Rect.top, SWP_NOACTIVATE | SWP_NOZORDER);
      }
      break;
#endif

    case WM_LBUTTONDOWN:
      //*** Get the start location for mouse rotations
      Last.x = LOWORD(lParam);
      Last.y = HIWORD(lParam);
      break;

    case WM_MOUSEMOVE:
      //*** While the mouse button is down, keep track of movement
      //*** to update the eye position
      if(GetKeyState(VK_LBUTTON) < 0)
      {
        Move.x = (int)LOWORD(lParam) - Last.x;
        Move.y = (int)HIWORD(lParam) - Last.y;
        Last.x = LOWORD(lParam);
        Last.y = HIWORD(lParam);
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

    if (CullMode != D3DCULL_CCW)
    {
        if (Shade < 0) Shade = -Shade;
    }

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

BOOL ProjectAndDrawCube(IDirect3DDevice2 *dev, int XOffset, int YOffset)
{
  HRESULT err;

  //*** Create a viewing transform for the current eye position
  vector_4 ViewDirection = Origin - Viewpoint;
  ViewDirection.Normalize();
  view_transform View(Viewpoint, ViewDirection, Up);

  //*** Transform and project the vertices into screen space
  int i;
  float aScreenVerticesX[8];
  float aScreenVerticesY[8];
  float aScreenVerticesZ[8];
  float aScreenVerticesW[8];

  for (i = 0; i < 8; ++i)
  {
    point_4 Temp = View * CubeVertices[i];
    Temp = ViewPerspective * Temp;
    Temp.Homogenize();

    aScreenVerticesX[i] = (float)Temp.GetX() + XOffset;
    aScreenVerticesY[i] = (float)Temp.GetY() + YOffset;
    aScreenVerticesZ[i] = (float)Temp.GetZ();
    aScreenVerticesW[i] = (float)Temp.GetW();

  }

  err = dev->BeginScene();

  //
  // NOTE NOTE NOTE NOTE NOTE
  // dont be as stupid as this sample, dont change the render
  // state every frame unless you need to.
  //
  dev->SetLightState(D3DLIGHTSTATE_MATERIAL,			hMat);
  dev->SetRenderState(D3DRENDERSTATE_CULLMODE,           CullMode);
  dev->SetRenderState(D3DRENDERSTATE_DITHERENABLE,       TextureDither);
  dev->SetRenderState(D3DRENDERSTATE_TEXTUREPERSPECTIVE, TexturePerspective);
  dev->SetRenderState(D3DRENDERSTATE_TEXTUREMAPBLEND,    TextureBlend);
  dev->SetRenderState(D3DRENDERSTATE_TEXTUREHANDLE,      TextureHandle);

  for (i = 0; i < 6; ++i)
  {
    //*** Get the shading colors

    int Red, Green, Blue;

    Red   = (int)(CubeColors[i][0] * CubeSurfaceShades[i]);
    Green = (int)(CubeColors[i][1] * CubeSurfaceShades[i]);
    Blue  = (int)(CubeColors[i][2] * CubeSurfaceShades[i]);

    //*** Collect the correct points in an array
    D3DTLVERTEX TLVertices[6];

    for (int j = 0; j < 4; ++j)
    {
        TLVertices[j].sx = aScreenVerticesX[CubeFaces[i][j]];
        TLVertices[j].sy = aScreenVerticesY[CubeFaces[i][j]];
        TLVertices[j].sz = aScreenVerticesZ[CubeFaces[i][j]];
        TLVertices[j].rhw = (float)(1.0 / aScreenVerticesW[CubeFaces[i][j]]);
        TLVertices[j].color = RGB_MAKE(Red, Green, Blue);
        TLVertices[j].specular = RGB_MAKE(0,0,0);
    }

    TLVertices[0].tu = 0.0f; TLVertices[0].tv = 0.0f;
    TLVertices[1].tu = 1.0f; TLVertices[1].tv = 0.0f;
    TLVertices[2].tu = 1.0f; TLVertices[2].tv = 1.0f;
    TLVertices[3].tu = 0.0f; TLVertices[3].tv = 1.0f;

    //*** Use DrawPrim to draw the face
    err = dev->DrawPrimitive(D3DPT_TRIANGLEFAN, D3DVT_TLVERTEX, TLVertices, 4, D3DDP_WAIT);
  }

  err = dev->EndScene();

  return TRUE;
}
