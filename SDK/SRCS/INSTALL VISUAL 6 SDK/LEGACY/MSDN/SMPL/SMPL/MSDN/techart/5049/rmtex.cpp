/*
 *  Copyright (C) 1995, 1996, 1997 Microsoft Corporation. 
 *  All Rights Reserved.
 *
 *  File:    rmtex.cpp
 *  Purpose: Basic Windows and DirectX functionality 
 *           for texture-mapping sample
 */

#define INITGUID

#include <windows.h>
#include <commctrl.h>   // includes the common control header
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <math.h>
#include <direct.h>
#include <d3drmwin.h>
#include <d3drm.h>
#include "rmdemo.h"             
#include "rmtex.h"       /* defines constants used in rmtex.rc */
#include "rmerror.h"     /* prototypes for error reporting: error.c */
#include "props.h"

#define MAX_DRIVERS 5    /* maximum D3D drivers we ever expect to find */

void __cdecl
Msg( LPSTR fmt, ... );
char*
MyErrorToString(HRESULT error);
/* 
 * GLOBAL VARIABLES
 */
LPDIRECT3DRM lpD3DRM;           /* Direct3DRM object */
LPDIRECTDRAWCLIPPER lpDDClipper;/* DirectDrawClipper object */

struct _myglobs {
    LPDIRECT3DRMDEVICE dev;     /* Direct3DRM device */
    LPDIRECT3DRMVIEWPORT view;  /* Direct3DRM viewport through which we view
                                   the scene */
    LPDIRECT3DRMFRAME scene;    /* Master frame in which others are placed */
    LPDIRECT3DRMFRAME camera;   /* Frame describing the users POV */

    GUID DriverGUID[MAX_DRIVERS];     /* GUIDs of the available D3D drivers */
    char DriverName[MAX_DRIVERS][50]; /* names of the available D3D drivers */
    int  NumDrivers;                  /* number of available D3D drivers */
    int  CurrDriver;                  /* number of D3D driver currently
                                         being used */

    D3DRMRENDERQUALITY RenderQuality;   /* current shade mode, fill mode and
                                           lighting state */
    D3DRMTEXTUREQUALITY TextureQuality; /* current texture interpolation */
    BOOL bDithering;                    /* is dithering on? */
    BOOL bAntialiasing;                 /* is antialiasing on? */

    BOOL bQuit;                 /* program is about to terminate */
    BOOL bInitialized;          /* all D3DRM objects have been initialized */
    BOOL bMinimized;            /* window is minimized */
    BOOL bSingleStepMode;       /* render one frame at a time */
    BOOL bDrawAFrame;           /* render on this pass of the main loop */
    BOOL bNoTextures;           /* this sample doesn't use any textures */
    BOOL bConstRenderQuality;   /* this sample is not constructed with
                                   MeshBuilders and so the RenderQuality
                                   cannot be changed */

    int BPP;                    /* bit depth of the current display mode */

} myglobs;
int  wrapType;
static HWND hProp = NULL;

/*
 * PROTOTYPES
 */
static HWND InitApp(HINSTANCE, int);
static void InitGlobals(void);
long FAR PASCAL WindowProc(HWND, UINT, WPARAM, LPARAM);
static BOOL CreateDevAndView(LPDIRECTDRAWCLIPPER lpDDClipper, int driver, int width, int height);
static BOOL RenderLoop(void);
static void CleanUpAndPostQuit(void);
static BOOL SetRenderState(void);
static BOOL EnumDevices(HWND win);
extern "C" void ReadMouse(int*, int*, int*);
extern "C" LPDIRECT3DRMFRAME fObj;

/****************************************************************************/
/*                               WinMain                                    */
/****************************************************************************/
/*
 * Initializes the application then enters a message loop which renders the
 * scene until a quit message is received.
 */
int PASCAL
WinMain (HINSTANCE this_inst, HINSTANCE prev_inst, LPSTR cmdline, int cmdshow)
{
    HWND    hwnd;
    MSG     msg;
    HACCEL  accel;
    int     failcount = 0;  /* number of times RenderLoop has failed */

    prev_inst;
    cmdline;
    hInst = this_inst;
    wrapType = MENU_WRAP_CYL;
    InitCommonControls();
    /*
     * Create the window and initialize all objects needed to begin rendering
     */
    if (!(hwnd = InitApp(this_inst, cmdshow)))
        return 1;

    accel = LoadAccelerators(this_inst, "AppAccel");

    while (!myglobs.bQuit) {
        /* 
         * Monitor the message queue until there are no pressing
         * messages
         */
        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            if (hProp)
            {
               if (PropSheet_IsDialogMessage(hProp,&msg))
                  break;
               if (!PropSheet_GetCurrentPageHwnd(hProp))
	                PostMessage(win,WM_COMMAND,MENU_WRAP_VALS_KILL,TRUE);
            }
            if (msg.message == WM_QUIT) {
                CleanUpAndPostQuit();
                break;
            }
            if (!TranslateAccelerator(msg.hwnd, accel, &msg)) {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        if (myglobs.bQuit)
            break;
        /* 
         * If the app is not minimized, not about to quit and D3DRM has
         * been initialized, we can render
         */
        if (!myglobs.bMinimized && !myglobs.bQuit && myglobs.bInitialized) {
            /*
             * If were are not in single step mode or if we are and the
             * bDrawAFrame flag is set, render one frame
             */
            if (!(myglobs.bSingleStepMode && !myglobs.bDrawAFrame)) {
                /* 
                 * Attempt to render a frame, if it fails, take a note.  If
                 * rendering fails more than twice, abort execution.
                 */
                if (!RenderLoop())
                    ++failcount;
                if (failcount > 2) {
                    Msg("Rendering has failed too many times.  Aborting execution.\n");
                    CleanUpAndPostQuit();
                    break;
                }
            }
            /*
             * Reset the bDrawAFrame flag if we are in single step mode
             */
            if (myglobs.bSingleStepMode)
                myglobs.bDrawAFrame = FALSE;
        } else {
            WaitMessage();
        }
    }
    DestroyWindow(hwnd);
    if ( fObj )
       RELEASE(fObj);
    if ( mesh )
       RELEASE(mesh);
    return msg.wParam;
}

/****************************************************************************/
/*                   Initialization and object creation                     */
/****************************************************************************/
/*
 * InitApp
 * Creates window and initializes all objects neccessary to begin rendering
 */
HWND win;
static HWND
InitApp(HINSTANCE this_inst, int cmdshow)
{
    HDC hdc;
    DWORD flags;
    WNDCLASS wc;
    Defaults defaults;
    HRESULT rval;
    RECT rc;

    /*
     * set up and registers the window class
     */
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WindowProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = sizeof(DWORD);
    wc.hInstance = this_inst;
    wc.hIcon = LoadIcon(this_inst, "AppIcon");
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wc.lpszMenuName = "AppMenu";
    wc.lpszClassName = "D3DRM Example";
    if (!RegisterClass(&wc))
        return FALSE;
    /*
     * Initialize the global variables and allow the sample code to override
     * some of these default settings.
     */
    InitGlobals();
    defaults.bNoTextures = myglobs.bNoTextures;
    defaults.bConstRenderQuality = myglobs.bConstRenderQuality;
    defaults.bResizingDisabled = FALSE;
    lstrcpy(defaults.Name, "D3DRM Example");
    OverrideDefaults(&defaults);
    myglobs.bNoTextures = defaults.bNoTextures;
    myglobs.bConstRenderQuality = defaults.bConstRenderQuality;
    /*
     * Create the window
     */
    if (defaults.bResizingDisabled)
        flags =  WS_VISIBLE | WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU |
                 WS_MINIMIZEBOX | WS_MAXIMIZEBOX;
    else
        flags = WS_OVERLAPPEDWINDOW;
    win =
        CreateWindow
        (   "D3DRM Example",            /* class */
            defaults.Name,              /* caption */
            flags,                      /* style */
            CW_USEDEFAULT,              /* init. x pos */
            CW_USEDEFAULT,              /* init. y pos */
            300,                        /* init. x size */
            300,                        /* init. y size */
            NULL,                       /* parent window */
            NULL,                       /* menu handle */
            this_inst,                  /* program handle */
            NULL                        /* create parms */
        );
    if (!win)
        return FALSE;
    /*
     * Record the current display BPP
     */
    hdc = GetDC(win);
    myglobs.BPP = GetDeviceCaps(hdc, BITSPIXEL);
    ReleaseDC(win, hdc);
    /*
     * Enumerate the D3D drivers and select one
     */
    if (!EnumDevices(win))
        return FALSE;
    /*
     * Create the D3DRM object and the D3DRM window object
     */
    rval = Direct3DRMCreate(&lpD3DRM);
    if (rval != D3DRM_OK) {
        Msg("Failed to create Direct3DRM.\n%s", D3DRMErrorToString(rval));
        return FALSE;
    }
    /*
     * Create the master scene frame and camera frame
     */
    rval = lpD3DRM->CreateFrame(NULL, &myglobs.scene);
    if (rval != D3DRM_OK) {
        Msg("Failed to create the master scene frame.\n%s", D3DRMErrorToString(rval));
        return FALSE;
    }
    rval = lpD3DRM->CreateFrame(myglobs.scene, &myglobs.camera);
    if (rval != D3DRM_OK) {
        Msg("Failed to create the camera's frame.\n%s", D3DRMErrorToString(rval));
        return FALSE;
    }
    rval = myglobs.camera->SetPosition(myglobs.scene, D3DVAL(0.0), D3DVAL(0.0), D3DVAL(0.0));
    if (rval != D3DRM_OK) {
        Msg("Failed to position the camera in the frame.\n%s", D3DRMErrorToString(rval));
        return FALSE;
    }
    /*
     * Create a clipper and associate the window with it
     */
    rval = DirectDrawCreateClipper(0, &lpDDClipper, NULL);
    if (rval != DD_OK) {
        Msg("Failed to create DirectDrawClipper");
        return FALSE;
    }
    rval = lpDDClipper->SetHWnd(0, win);
    if (rval != DD_OK) {
        Msg("Failed to set hwnd on the clipper");
        return FALSE;
    }
    /*
     * Created the D3DRM device with the selected D3D driver
     */
    GetClientRect(win, &rc);
    if (!CreateDevAndView(lpDDClipper, myglobs.CurrDriver, rc.right, rc.bottom)) {
        return FALSE;
    }
    /*
     * Create the scene to be rendered by calling this sample's BuildScene
     */
    if (!BuildScene(myglobs.dev, myglobs.view, myglobs.scene, myglobs.camera))
        return FALSE;
    /*
     * Now we are ready to render
     */
    myglobs.bInitialized = TRUE;
    /*
     * Display the window
     */
    ShowWindow(win, cmdshow);
    UpdateWindow(win);

    return win;
}

/*
 * CreateDevAndView
 * Create the D3DRM device and viewport with the given D3D driver and of the
 * specified size.
 */
static BOOL
CreateDevAndView(LPDIRECTDRAWCLIPPER lpDDClipper, int driver, int width, int height)
{
    HRESULT rval;

    if (!width || !height) {
        Msg("Cannot create a D3DRM device with invalid window dimensions.");
        return FALSE;
    }
    /*
     * Create the D3DRM device from this window and using the specified D3D
     * driver.
     */
    rval = lpD3DRM->CreateDeviceFromClipper(lpDDClipper, &myglobs.DriverGUID[driver],
                                        width, height, &myglobs.dev);
    if (rval != D3DRM_OK) {
        Msg("Failed to create the D3DRM device from the clipper.\n%s",
            D3DRMErrorToString(rval));
        return FALSE;
    }
    /*
     * Create the D3DRM viewport using the camera frame.  Set the background
     * depth to a large number.  The width and height may be slightly
     * adjusted, so get them from the device to be sure.
     */
    width = myglobs.dev->GetWidth();
    height = myglobs.dev->GetHeight();
    rval = lpD3DRM->CreateViewport(myglobs.dev, myglobs.camera, 0, 0, width,
                                   height, &myglobs.view);
    if (rval != D3DRM_OK) {
        Msg("Failed to create the D3DRM viewport.\n%s",
            D3DRMErrorToString(rval));
        RELEASE(myglobs.dev);
        return FALSE;
    }
    rval = myglobs.view->SetBack(D3DVAL(5000.0));
    if (rval != D3DRM_OK) {
        Msg("Failed to set the background depth of the D3DRM viewport.\n%s",
            D3DRMErrorToString(rval));
        RELEASE(myglobs.dev);
        RELEASE(myglobs.view);
        return FALSE;
    }
    /*
     * Set the render quality, fill mode, lighting state and color shade info
     */
    if (!SetRenderState())
        return FALSE;
    return TRUE;
}

/****************************************************************************/
/*                         D3D Device Enumeration                           */
/****************************************************************************/
/*
 * BPPToDDBD
 * Converts bits per pixel to a DirectDraw bit depth flag
 */
static DWORD
BPPToDDBD(int bpp)
{
    switch(bpp) {
        case 1:
            return DDBD_1;
        case 2:
            return DDBD_2;
        case 4:
            return DDBD_4;
        case 8:
            return DDBD_8;
        case 16:
            return DDBD_16;
        case 24:
            return DDBD_24;
        case 32:
            return DDBD_32;
        default:
            return 0;
    }
}

/*
 * enumDeviceFunc
 * Callback function which records each usable D3D driver's name and GUID
 * Chooses a driver to begin with and sets *lpContext to this starting driver
 */
static HRESULT
WINAPI enumDeviceFunc(LPGUID lpGuid, LPSTR lpDeviceDescription, LPSTR lpDeviceName,
        LPD3DDEVICEDESC lpHWDesc, LPD3DDEVICEDESC lpHELDesc, LPVOID lpContext)
{
    static BOOL hardware = FALSE; /* current start driver is hardware */
    static BOOL mono = FALSE;     /* current start driver is mono light */
    LPD3DDEVICEDESC lpDesc;
    int *lpStartDriver = (int *)lpContext;
    /*
     * Decide which device description we should consult
     */
    lpDesc = lpHWDesc->dcmColorModel ? lpHWDesc : lpHELDesc;
    /*
     * If this driver cannot render in the current display bit depth skip
     * it and continue with the enumeration.
     */
    if (!(lpDesc->dwDeviceRenderBitDepth & BPPToDDBD(myglobs.BPP)))
        return D3DENUMRET_OK;
    /*
     * Record this driver's info
     */
    memcpy(&myglobs.DriverGUID[myglobs.NumDrivers], lpGuid, sizeof(GUID));
    lstrcpy(&myglobs.DriverName[myglobs.NumDrivers][0], lpDeviceName);
    /*
     * Choose hardware over software, RGB lights over mono lights
     */
    if (*lpStartDriver == -1) {
        /*
         * this is the first valid driver
         */
        *lpStartDriver = myglobs.NumDrivers;
        hardware = lpDesc == lpHWDesc ? TRUE : FALSE;
        mono = lpDesc->dcmColorModel & D3DCOLOR_MONO ? TRUE : FALSE;
    } else if (lpDesc == lpHWDesc && !hardware) {
        /*
         * this driver is hardware and start driver is not
         */
        *lpStartDriver = myglobs.NumDrivers;
        hardware = lpDesc == lpHWDesc ? TRUE : FALSE;
        mono = lpDesc->dcmColorModel & D3DCOLOR_MONO ? TRUE : FALSE;
    } else if ((lpDesc == lpHWDesc && hardware ) || (lpDesc == lpHELDesc
                                                     && !hardware)) {
        if (lpDesc->dcmColorModel == D3DCOLOR_MONO && !mono) {
            /*
             * this driver and start driver are the same type and this
             * driver is mono while start driver is not
             */
            *lpStartDriver = myglobs.NumDrivers;
            hardware = lpDesc == lpHWDesc ? TRUE : FALSE;
            mono = lpDesc->dcmColorModel & D3DCOLOR_MONO ? TRUE : FALSE;
        }
    }
    myglobs.NumDrivers++;
    if (myglobs.NumDrivers == MAX_DRIVERS)
        return (D3DENUMRET_CANCEL);
    return (D3DENUMRET_OK);
}

/*
 * EnumDevices
 * Enumerate the available D3D drivers, add them to the file menu, and choose
 * one to use.
 */
static BOOL
EnumDevices(HWND win)
{
    LPDIRECTDRAW lpDD;
    LPDIRECT3D lpD3D;
    HRESULT rval;
    HMENU hmenu;
    int i;

    /*
     * Create a DirectDraw object and query for the Direct3D interface to use
     * to enumerate the drivers.
     */
    rval = DirectDrawCreate(NULL, &lpDD, NULL);
    if (rval != DD_OK) {
        Msg("Creation of DirectDraw HEL failed.\n%s", D3DRMErrorToString(rval));
        return FALSE;
    }
    rval = lpDD->QueryInterface(IID_IDirect3D, (void**) &lpD3D);
    if (rval != DD_OK) {
        Msg("Creation of Direct3D interface failed.\n%s", D3DRMErrorToString(rval));
        lpDD->Release();
        return FALSE;
    }
    /*
     * Enumerate the drivers, setting CurrDriver to -1 to initialize the
     * driver selection code in enumDeviceFunc
     */
    myglobs.CurrDriver = -1;
    rval = lpD3D->EnumDevices(enumDeviceFunc, &myglobs.CurrDriver);
    if (rval != DD_OK) {
        Msg("Enumeration of drivers failed.\n%s", D3DRMErrorToString(rval));
        return FALSE;
    }
    /*
     * Make sure we found at least one valid driver
     */
    if (myglobs.NumDrivers == 0) {
        Msg("Could not find a D3D driver which is compatible with this display depth");
        return FALSE;
    }
    lpD3D->Release();
    lpDD->Release();
    /*
     * Add the driver names to the File menu
     */
    hmenu = GetSubMenu(GetMenu(win), 0);
    for (i = 0; i < myglobs.NumDrivers; i++) {
        InsertMenu(hmenu, 5 + i, MF_BYPOSITION | MF_STRING, MENU_FIRST_DRIVER + i,
                   myglobs.DriverName[i]);
    }
    return TRUE;
}

/****************************************************************************/
/*                             Render Loop                                  */
/****************************************************************************/
/*
 * Clear the viewport, render the next frame and update the window
 */
static BOOL
RenderLoop()
{
    HRESULT rval;
    /*
     * Tick the scene
     */
    rval = myglobs.scene->Move(D3DVAL(1.0));
    if (rval != D3DRM_OK) {
        Msg("Moving scene failed.\n%s", D3DRMErrorToString(rval));
        return FALSE;
    }
    /* 
     * Clear the viewport
     */
    rval = myglobs.view->Clear();
    if (rval != D3DRM_OK) {
        Msg("Clearing viewport failed.\n%s", D3DRMErrorToString(rval));
        return FALSE;
    }
    /*
     * Render the scene to the viewport
     */
    rval = myglobs.view->Render(myglobs.scene);
    if (rval != D3DRM_OK) {
        Msg("Rendering scene failed.\n%s", D3DRMErrorToString(rval));
        return FALSE;
    }
    /*
     * Update the window
     */
    rval = myglobs.dev->Update();
    if (rval != D3DRM_OK) {
        Msg("Updating device failed.\n%s", D3DRMErrorToString(rval));
        return FALSE;
    }
    return TRUE;
}


/****************************************************************************/
/*                    Windows Message Handlers                              */
/****************************************************************************/
/*
 * AppAbout
 * About box message handler
 */
BOOL
FAR PASCAL AppAbout(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lParam)
{
  switch (msg)
  {
    case WM_COMMAND:
      if (LOWORD(wparam) == IDOK)
        EndDialog(hwnd, TRUE);
      break;

    case WM_INITDIALOG:
      return TRUE;
  }
  return FALSE;
}

HRESULT loadTextures(char *name, void *arg, LPDIRECT3DRMTEXTURE *tex)
{
    /* IDirect3DRM::LoadTexture checks whether the texture is a PPM or
    BMP which it knows how to load. If you want to load other formats 
    you could add code to the callback to load the code into an D3DRMIMAGE
    structure and call IDirect3DRM::CreateTexture */
    HRESULT rval;
    rval = lpD3DRM->LoadTexture(name, tex);
    if (rval != D3DRM_OK) {
        Msg("Failed to load texture.\n%s", MyErrorToString(rval));
    }
    return rval;
}
//
HMENU hm;
D3DRMIMAGE* texImage;
LPDIRECT3DRMMESH mesh;
D3DRMBOX box;
D3DVALUE minx;    
D3DVALUE maxx;
D3DVALUE width;
D3DVALUE miny;
D3DVALUE maxy;
D3DVALUE height;
D3DVALUE minz;    
D3DVALUE maxz;
D3DVALUE depth;
//
void loadXFile(char* file)
{
   LPDIRECT3DRMMESHBUILDER builder = NULL;
   LPDIRECT3DRMMATERIAL mat = NULL;

   myglobs.scene->DeleteChild(fObj);
	 RELEASE(fObj);
   RELEASE(mesh);
	 
   lpD3DRM->CreateFrame(myglobs.scene, &fObj);
   fObj->SetPosition(myglobs.scene, 
      D3DVAL(0), D3DVAL(0), D3DVAL(15));
   fObj->SetRotation(myglobs.scene, 
      D3DVAL(1.1), D3DVAL(0.3), D3DVAL(0.0),
      D3DVAL(0.04));
   lpD3DRM->CreateMeshBuilder(&builder);
   builder->Load((LPVOID)file,NULL,D3DRMLOAD_FROMFILE,
     NULL,NULL);
   lpD3DRM->CreateMaterial(D3DVAL(10.0),&mat);
   builder->SetMaterial(mat);
   builder->SetColorRGB(D3DVAL(1.0), D3DVAL(1.0), D3DVAL(1.0));
   builder->CreateMesh(&mesh);
   setBoxDims(&box);
   fObj->AddVisual((LPDIRECT3DRMVISUAL)mesh);

   RELEASE(mat);
   RELEASE(builder);
}
//
LPDIRECT3DRMTEXTURE tex = NULL;
//
void loadTexFile(char* file)
{
   HRESULT rval;
   LPDIRECT3DRMMESH mesh = NULL;
   LPDIRECT3DRMMESHBUILDER builder = NULL;
   LPDIRECT3DRMVISUALARRAY visuals;
   LPDIRECT3DRMVISUAL v;
   int count,i;

   if ( tex)
	    RELEASE(tex);
   rval = loadTextures(file,NULL,&tex);
   if (rval == D3DRM_OK) {
       texImage = tex->GetImage();
       if ( texImage->width == texImage->height && texImage->width % 2 == 0 )
       {
         tex->SetColors(256);
         fObj->GetVisuals(&visuals);
         tex->SetDecalScale(TRUE);
	       tex->SetDecalOrigin(128, 128);
         myglobs.scene->SetSceneBackgroundImage(tex);
         count = visuals->GetSize();
         for (i = 0; i < count; i++) {
             visuals->GetElement(i, &v);
         
             if (SUCCEEDED(v->QueryInterface(IID_IDirect3DRMMesh, (void**)&mesh))) 
             {
                rval = mesh->SetGroupMapping(-1,D3DRMMAP_PERSPCORRECT);
                rval = mesh->SetGroupTexture(-1,tex);
             }
       		  RELEASE(v);
       		  RELEASE(mesh);
         }
       }
       else
          MessageBox(NULL,"not power of 2 or square texture",
             file,MB_OK);
       RELEASE(visuals);
	 }
}


#define MAXFILTERBUF 256
//
void  WINAPI  SplitPath( LPSTR lpszFileName, LPSTR lpszDrive, LPSTR lpszDir, LPSTR lpszFile, int nFileOffset, LPSTR lpszExt, int nExtOffset)
{
  char	szPath[MAXFILTERBUF];
  LPSTR lpszPath;
  LPSTR lpszTemp;
  int	nFileNameLen = nExtOffset - (nFileOffset + 1);
  int	i;

  /* init ptrs */
  lpszPath = szPath;
  lpszTemp = lpszFileName;

  /* pick off the path */
  for (i = 0; i < nFileOffset; i++, lpszTemp++, lpszPath++)
    *lpszPath = *lpszTemp;
  *lpszPath = '\0';

  lpszPath = szPath;

  /* pick off the drive designator */
  for (i = 0; i < 2; i++, lpszPath++, lpszDrive++)
    *lpszDrive = *lpszPath;
  *lpszDrive = '\0';

  /* pick off the directory */
  while (*lpszPath != '\0')
    *lpszDir++ = *lpszPath++;
  *lpszDir = '\0';

  /* reset temp ptr */
  lpszTemp = lpszFileName;

  /* index to filename */
  lpszTemp += nFileOffset;

  /* pick off the filename */
  for (i = 0; i < nFileNameLen; i++, lpszTemp++, lpszFile++)
    *lpszFile = *lpszTemp;
  *lpszFile = '\0';

  /* reset temp ptr */
  lpszTemp = lpszFileName;

  /* index to file extension */
  lpszTemp += nExtOffset;

  /* pick off the ext */
  while (*lpszTemp != '\0')
    *lpszExt++ = *lpszTemp++;
  *lpszExt = '\0';

}
//
static LPDIRECT3DRMFRAME wrapCam;
//
void CDECL 
applyWrapDecal(LPDIRECT3DRMFRAME frame, void* arg, D3DVALUE delta)
{
    LPDIRECT3DRMWRAP wrap = (LPDIRECT3DRMWRAP) arg;
    LPDIRECT3DRMVISUALARRAY visuals;
    LPDIRECT3DRMVISUAL v;
    int count, i;

    frame->GetVisuals(&visuals);
    if (visuals) {
        count = visuals->GetSize();
   
        for (i = 0; i < count; i++) {
            visuals->GetElement(i, &v);
            if ( v ) {
				   wrap->ApplyRelative(frame, (LPDIRECT3DRMOBJECT) v);
			   	v->Release();
			    }
        }
        visuals->Release();
    }
}
void CDECL 
applyWrapCamera(LPDIRECT3DRMFRAME frame, void* arg, D3DVALUE delta)
{
    LPDIRECT3DRMWRAP wrap = (LPDIRECT3DRMWRAP) arg;
	  if ( wrap )
	    wrap->ApplyRelative(frame, (LPDIRECT3DRMOBJECT) wrapCam);

}
void CDECL 
cleanupWrap(LPDIRECT3DRMOBJECT obj, void* arg)
{
    LPDIRECT3DRMWRAP wrap = (LPDIRECT3DRMWRAP) arg;
    obj;

    wrap->Release();
}
//
LPDIRECT3DRMWRAP wrap = NULL;
LPDIRECT3DRMFRAME axis = NULL;
LPDIRECT3DRMFRAME orbit = NULL;
//
/*
 * WindowProc
 * Main window message handler
 */
LONG FAR PASCAL WindowProc(HWND win, UINT msg, WPARAM wparam, LPARAM lparam)
{
    int i;
    HRESULT rval;
    RECT rc;
    LPDIRECT3DRMVISUALARRAY visuals;
    LPDIRECT3DRMVISUAL v;
    int count;

    switch (msg)    {
			case WM_CREATE:
				DragAcceptFiles(win,TRUE);
				break;	
      case WM_KEYDOWN:
            fObj->GetVisuals(&visuals);
            count = visuals->GetSize();
            for (i = 0; i < count; i++) {
                visuals->GetElement(i, &v);

                RELEASE(mesh);
                if (SUCCEEDED(v->QueryInterface(IID_IDirect3DRMMesh, (void**)&mesh))) 
                {
                   switch (wparam)
                   {
                   case VK_SUBTRACT:
                       mesh->Scale(D3DVAL(0.9), D3DVAL(0.9), D3DVAL(0.9));
                       break;
                   case VK_ADD:
                       mesh->Scale(D3DVAL(1.1), D3DVAL(1.1), D3DVAL(1.1));
                       break;
                   }
                   setBoxDims(&box);
                   RELEASE(visuals);
                   RELEASE(v);
                   if ( hProp )
                   {
                      NMHDR n;
					            n.hwndFrom = hProp;
					            n.idFrom = 0;
                      n.code = PSN_SETACTIVE;
                      SendMessage(hwPageVal,WM_NOTIFY,0,(LPARAM)&n);
                   }
                }
            }
            break;

        case WM_INITMENUPOPUP:
            hm = (HMENU)wparam;
            /*
             * Check and enable the appropriate menu items
             */
            CheckMenuItem((HMENU)wparam, MENU_STEP,(myglobs.bSingleStepMode) ? MF_CHECKED : MF_UNCHECKED);
            EnableMenuItem((HMENU)wparam, MENU_GO,(myglobs.bSingleStepMode) ? MF_ENABLED : MF_GRAYED);
            CheckMenuItem((HMENU)wparam, wrapType,MF_CHECKED);
            for (i = 0; i < myglobs.NumDrivers; i++) {
                CheckMenuItem((HMENU)wparam, MENU_FIRST_DRIVER + i,
                       (i == myglobs.CurrDriver) ? MF_CHECKED : MF_UNCHECKED);
            }
            break;
		case WM_DROPFILES:
			 // A file is being dropped.
   			int iFiles;
   			char lpszFile [MAX_PATH];
   			HDROP hDropInfo;
   			hDropInfo = (HANDLE)wparam;

   			// Get the number of files.
   			iFiles = DragQueryFile (hDropInfo, (DWORD)(-1), (LPSTR)NULL, 0);

   			if (iFiles != 1) 
      			MessageBox (win, "One file at a time, please.", NULL, MB_OK);

   			else
   			{
				   int slen;
           char szDrive[3],szPath[256],szFile[256],szExt[256];
				   int nFileOffset,nExtOffset;
				   nFileOffset = nExtOffset = 0;
      		 DragQueryFile (hDropInfo, 0, lpszFile, sizeof (lpszFile));
					 slen = strlen(lpszFile);
            	if ( nExtOffset == 0 || nFileOffset == 0 )
            	{
            	   LPSTR lp;
            	   int   Ext = '.';
            	   int   fN  = '\\';
            	   lp  = strchr(lpszFile,Ext);
            	   nExtOffset  = lp - lpszFile + 1;
            	   lp  = strrchr(lpszFile,fN);
            	   nFileOffset  = lp - lpszFile + 1;
            	}
              SplitPath(lpszFile,szDrive,szPath,szFile,nFileOffset,szExt,nExtOffset);
			    	if ( _strnicmp(szExt,"X",1)== 0 )
						bX = TRUE;
					else
						bX = FALSE;
              if ( bX )
                loadXFile(lpszFile);
              else
                loadTexFile(lpszFile);
				}
				break;
        case WM_COMMAND:
            switch(LOWORD(wparam)) {
                case MENU_ABOUT:
                    DialogBox((HINSTANCE)GetWindowLong(win, GWL_HINSTANCE),
                              "AppAbout", win, (DLGPROC)AppAbout);
                    break;
                case MENU_FILE_OPEN:
                    char *file;
                    LPDIRECT3DRMTEXTURE tex;
                    file = OpenNewFile(win, "Open Texture or Mesh File");
                    if ( bX )
                    {
							   loadXFile(file);
                    }
                    else
                    {
							   loadTexFile(file);
                    }
                    break;
                case MENU_EXIT:
	                  RELEASE(tex);
                    CleanUpAndPostQuit();
                    break;
                case MENU_STEP:
                    /*
                     * Begin single step more or draw a frame if in single
                     * step mode
                     */
                    if (!myglobs.bSingleStepMode) {
                        myglobs.bSingleStepMode = TRUE;
                        myglobs.bDrawAFrame = TRUE;
                    } else if (!myglobs.bDrawAFrame) {
                        myglobs.bDrawAFrame = TRUE;
                    }
                    break;
                case MENU_GO:
                    /*
                     * Exit single step mode
                     */
                    myglobs.bSingleStepMode = FALSE;
                    break;
                case MENU_WRAP_VALS:
					      if ( hProp == NULL )
							{
					         hProp = (HWND)CreatePropertySheet(win);
							}
					      break;
                case MENU_WRAP_VALS_KILL:
                    if ( hProp )
					      {
						      DestroyWindow(hProp);
						      hProp = NULL;
					      }
					      break;

                case MENU_WRAP_FLAT:
                case MENU_WRAP_CYL:
                case MENU_WRAP_SPHR:
                case MENU_WRAP_CHROME:
					      if ( wrapType == MENU_WRAP_CHROME && wrap)
						    {
   					       fObj->DeleteMoveCallback(applyWrapDecal,(void*)wrap);
							     wrap->Release();
							     wrap = NULL;
							     wrapCam = NULL;
                   fObj->DeleteChild(orbit);
                   fObj->DeleteChild(axis);
						    }
                CheckMenuItem(hm,wrapType,MF_UNCHECKED);
                wrapType = wparam;
                CheckMenuItem(hm,wrapType,MF_CHECKED);
                fObj->GetVisuals(&visuals);
                count = visuals->GetSize();
                for (i = 0; i < count; i++) {
                        visuals->GetElement(i, &v);

                if (SUCCEEDED(v->QueryInterface(IID_IDirect3DRMMesh, (void**)&mesh))) 
                {
                    setBoxDims(&box);
                    switch(wparam)
                    {
                            case MENU_WRAP_FLAT:
                              if (FAILED(lpD3DRM->CreateWrap(D3DRMWRAP_FLAT, 
										               NULL,
                                   wOx,wOy,wOz,
                                   wZx,wZy,wZz,
                                   wYx,wYy,wYz,
                                   tOx,tOy,
                                   tSx,tSy,
                               &wrap)))
                                 break;
                              if (FAILED(wrap->Apply((LPDIRECT3DRMOBJECT) mesh)))
                                 break;
							  
                              RELEASE(wrap);
                              break;
                            case MENU_WRAP_CYL:
                              if (FAILED(lpD3DRM->CreateWrap(D3DRMWRAP_CYLINDER, 
										               NULL, 
                                   wOx,wOy,wOz,
                                   wZx,wZy,wZz,
                                   wYx,wYy,wYz,
                                   tOx,tOy,
                                   tSx,tSy,
                               &wrap)))
                                 break;
                              if (FAILED(wrap->Apply((LPDIRECT3DRMOBJECT) mesh)))
                                 break;
							  
                              RELEASE(wrap);
                              break;
                            case MENU_WRAP_SPHR:
                              if (FAILED(lpD3DRM->CreateWrap(D3DRMWRAP_SPHERE, 
										               NULL, 
                                   wOx,wOy,wOz,
                                   wZx,wZy,wZz,
                                   wYx,wYy,wYz,
                                   tOx,tOy,
                                   tSx,tSy,
                               &wrap)))
                                 break;
                              if (FAILED(wrap->Apply((LPDIRECT3DRMOBJECT) mesh)))
                                 break;
							  
                              RELEASE(wrap);
                              break;
                            case MENU_WRAP_CHROME:
                              if (FAILED(lpD3DRM->CreateWrap(D3DRMWRAP_CHROME, 
                                   myglobs.camera,
                                   wOx,wOy,wOz,
                                   wZx,wZy,wZz,
                                   wYx,wYy,wYz,
                                   tOx,tOy,
                                   tSx,tSy,
                                     &wrap)))
                                   break;
							  wrapCam = myglobs.camera;
	                          mesh->SetGroupColorRGB(0, D3DVAL(1.0), D3DVAL(1.0), D3DVAL(1.0));
	                          mesh->SetGroupColorRGB(1, D3DVAL(1.0), D3DVAL(1.0), D3DVAL(1.0));
                              fObj->AddMoveCallback(applyWrapDecal, (void *) wrap);
							  break;
                            }
                        }
                    }
                    RELEASE(visuals);
                    RELEASE(v);
                    RELEASE(mesh);
                    break;
                             }
                /*
                 * Changing the D3D Driver
                 */
                if (LOWORD(wparam) >= MENU_FIRST_DRIVER &&
                    LOWORD(wparam) < MENU_FIRST_DRIVER + MAX_DRIVERS &&
                    myglobs.CurrDriver != LOWORD(wparam) - MENU_FIRST_DRIVER){
                        /*
                         * Release the current viewport and device and create
                         * the new one
                         */
                        RELEASE(myglobs.view);
                        RELEASE(myglobs.dev);
                        myglobs.CurrDriver = LOWORD(wparam)-MENU_FIRST_DRIVER;
                        GetClientRect(win, &rc);
                        if (!CreateDevAndView(lpDDClipper, myglobs.CurrDriver,
                                              rc.right, rc.bottom)) {
                            CleanUpAndPostQuit();
                        }
                }
                /*
                 * Draw a frame in single step mode after ever command
                 */
                myglobs.bDrawAFrame = TRUE;
            break;
    case WM_DESTROY:
        CleanUpAndPostQuit();
        break;
    case WM_SIZE:
        /*
         * Handle resizing of the window
         */
        {
        int width = LOWORD(lparam);
        int height = HIWORD(lparam);
        if (width && height) {
            int view_width = myglobs.view->GetWidth();
            int view_height = myglobs.view->GetHeight();
            int dev_width = myglobs.dev->GetWidth();
            int dev_height = myglobs.dev->GetHeight();
            /*
             * If the window hasn't changed size and we aren't returning from
             * a minimize, there is nothing to do
             */
            if (view_width == width && view_height == height &&
                !myglobs.bMinimized)
                break;
            if (width <= dev_width && height <= dev_height) {
                /*
                 * If the window has shrunk, we can use the same device with a
                 * new viewport
                 */
                RELEASE(myglobs.view);
                rval = lpD3DRM->CreateViewport(myglobs.dev, myglobs.camera,
                                               0, 0, width, height,
                                               &myglobs.view);
                if (rval != D3DRM_OK) {
                    Msg("Failed to resize the viewport.\n%s",
                        D3DRMErrorToString(rval));
                    CleanUpAndPostQuit();
                    break;
                }
                rval = myglobs.view->SetBack(D3DVAL(5000.0));
                if (rval != D3DRM_OK) {
                    Msg("Failed to set background depth after viewport resize.\n%s",
                        D3DRMErrorToString(rval));
                    CleanUpAndPostQuit();
                    break;
                }
            } else {
                /*
                 * If the window got larger than the current device, create a
                 * new device.
                 */
                RELEASE(myglobs.view);
                RELEASE(myglobs.dev);
                if (!CreateDevAndView(lpDDClipper, myglobs.CurrDriver, width,
                    height)) {
                    CleanUpAndPostQuit();
                    break;
                }
            }
            /*
             * We must not longer be minimized
             */
            myglobs.bMinimized = FALSE;
        } else {
            /*
             * This is a minimize message
             */
            myglobs.bMinimized = TRUE;
        }
        }
        break;
    case WM_ACTIVATE:
        {
        /*
         * Create a Windows specific D3DRM window device to handle this
         * message
         */
        LPDIRECT3DRMWINDEVICE windev;
        if (!myglobs.dev)
            break;
        if (SUCCEEDED(myglobs.dev->QueryInterface(IID_IDirect3DRMWinDevice,
            (void **) &windev)))  {
                if (FAILED(windev->HandleActivate(wparam)))
                    Msg("Failed to handle WM_ACTIVATE.\n");
                windev->Release();
        } else {
            Msg("Failed to create Windows device to handle WM_ACTIVATE.\n");
        }
        }
        break;
    case WM_PAINT:
        if (!myglobs.bInitialized || !myglobs.dev)
            return DefWindowProc(win, msg, wparam, lparam);
        /*
         * Create a Windows specific D3DRM window device to handle this
         * message
         */
        RECT r;
        PAINTSTRUCT ps;
        LPDIRECT3DRMWINDEVICE windev;

        if (GetUpdateRect(win, &r, FALSE)) {
            BeginPaint(win, &ps);
            if (SUCCEEDED(myglobs.dev->QueryInterface(IID_IDirect3DRMWinDevice,
                (void **) &windev))) {
                if (FAILED(windev->HandlePaint(ps.hdc)))
                    Msg("Failed to handle WM_PAINT.\n");
                windev->Release();
            } else {
                Msg("Failed to create Windows device to handle WM_PAINT.\n");
            }
            EndPaint(win, &ps);
        }
        break;
    default:
        return DefWindowProc(win, msg, wparam, lparam);
    }
    return 0L;
}

/*
 * SetRenderState
 * Set the render quality, dither toggle and shade info if any of them has
 * changed
 */
BOOL
SetRenderState(void)
{
    HRESULT rval;
    /*
     * Set the render quality (light toggle, fill mode, shade mode)
     */
    if (myglobs.dev->GetQuality() != myglobs.RenderQuality) {
        rval = myglobs.dev->SetQuality(myglobs.RenderQuality);
        if (rval != D3DRM_OK) {
            Msg("Setting the render quality failed.\n%s",
                D3DRMErrorToString(rval));
            return FALSE;
        }
    }
    /*
     * Set dithering toggle
     */
    if (myglobs.dev->GetDither() != myglobs.bDithering) {
        rval = myglobs.dev->SetDither(myglobs.bDithering);
        if (rval != D3DRM_OK) {
            Msg("Setting dither mode failed.\n%s", D3DRMErrorToString(rval));
            return FALSE;
        }
    }
    /*
     * Set the texture quality (point or linear filtering)
     */
    if (myglobs.dev->GetTextureQuality() != myglobs.TextureQuality) {
        rval = myglobs.dev->SetTextureQuality(myglobs.TextureQuality);
        if (rval != D3DRM_OK) {
            Msg("Setting texture quality failed.\n%s",
                D3DRMErrorToString(rval));
            return FALSE;
        }
    }
    /*
     * Set shade info based on current bits per pixel
     */
    switch (myglobs.BPP) {
        case 1:
            if (FAILED(myglobs.dev->SetShades(4)))
                goto shades_error;
            if (FAILED(lpD3DRM->SetDefaultTextureShades(4)))
                goto shades_error;
            break;
        case 16:
            if (FAILED(myglobs.dev->SetShades(32)))
                goto shades_error;
            if (FAILED(lpD3DRM->SetDefaultTextureColors(64)))
                goto shades_error;
            if (FAILED(lpD3DRM->SetDefaultTextureShades(32)))
                goto shades_error;
            break;
        case 24:
        case 32:
            if (FAILED(myglobs.dev->SetShades(256)))
                goto shades_error;
            if (FAILED(lpD3DRM->SetDefaultTextureColors(64)))
                goto shades_error;
            if (FAILED(lpD3DRM->SetDefaultTextureShades(256)))
                goto shades_error;
            break;
    }
    return TRUE;
shades_error:
    Msg("A failure occurred while setting color shade information.\n");
    return FALSE;
}

/****************************************************************************/
/*                          Additional Functions                            */
/****************************************************************************/
/*
 * InitGlobals
 * Initialize the global variables
 */
void
InitGlobals(void)
{
    lpD3DRM = NULL;
    memset(&myglobs, 0, sizeof(myglobs));
    myglobs.RenderQuality = D3DRMLIGHT_ON | D3DRMFILL_SOLID |
                            D3DRMSHADE_GOURAUD;
    myglobs.TextureQuality = D3DRMTEXTURE_NEAREST;
}

/*
 * CleanUpAndPostQuit
 * Release all D3DRM objects, post a quit message and set the bQuit flag
 */
void
CleanUpAndPostQuit(void)
{
    myglobs.bInitialized = FALSE;
    RELEASE(myglobs.scene);
    RELEASE(myglobs.camera);
    RELEASE(myglobs.view);
    RELEASE(myglobs.dev);
    RELEASE(lpD3DRM);
    RELEASE(lpDDClipper);
    myglobs.bQuit = TRUE;
}
/*
 * MyErrorToString
 * Returns a pointer to a string describing the given error code.
 */
char*
MyErrorToString(HRESULT error)
{
    switch(error) {
        case DD_OK:
            /* Also includes D3D_OK and D3DRM_OK */
            return "No error.\0";
        case DDERR_ALREADYINITIALIZED:
            return "This object is already initialized.\0";
        case DDERR_BLTFASTCANTCLIP:
            return "Return if a clipper object is attached to the source surface passed into a BltFast call.\0";
        case DDERR_CANNOTATTACHSURFACE:
            return "This surface can not be attached to the requested surface.\0";
        case DDERR_CANNOTDETACHSURFACE:
            return "This surface can not be detached from the requested surface.\0";
        case DDERR_CANTCREATEDC:
            return "Windows can not create any more DCs.\0";
        case DDERR_CANTDUPLICATE:
            return "Can't duplicate primary & 3D surfaces, or surfaces that are implicitly created.\0";
        case DDERR_CLIPPERISUSINGHWND:
            return "An attempt was made to set a cliplist for a clipper object that is already monitoring an hwnd.\0";
        case DDERR_COLORKEYNOTSET:
            return "No src color key specified for this operation.\0";
        case DDERR_CURRENTLYNOTAVAIL:
            return "Support is currently not available.\0";
        case DDERR_DIRECTDRAWALREADYCREATED:
            return "A DirectDraw object representing this driver has already been created for this process.\0";
        case DDERR_EXCEPTION:
            return "An exception was encountered while performing the requested operation.\0";
        case DDERR_EXCLUSIVEMODEALREADYSET:
            return "An attempt was made to set the cooperative level when it was already set to exclusive.\0";
        case DDERR_GENERIC:
            return "Generic failure.\0";
        case DDERR_HEIGHTALIGN:
            return "Height of rectangle provided is not a multiple of reqd alignment.\0";
        case DDERR_HWNDALREADYSET:
            return "The CooperativeLevel HWND has already been set. It can not be reset while the process has surfaces or palettes created.\0";
        case DDERR_HWNDSUBCLASSED:
            return "HWND used by DirectDraw CooperativeLevel has been subclassed, this prevents DirectDraw from restoring state.\0";
        case DDERR_IMPLICITLYCREATED:
            return "This surface can not be restored because it is an implicitly created surface.\0";
        case DDERR_INCOMPATIBLEPRIMARY:
            return "Unable to match primary surface creation request with existing primary surface.\0";
        case DDERR_INVALIDCAPS:
            return "One or more of the caps bits passed to the callback are incorrect.\0";
        case DDERR_INVALIDCLIPLIST:
            return "DirectDraw does not support the provided cliplist.\0";
        case DDERR_INVALIDDIRECTDRAWGUID:
            return "The GUID passed to DirectDrawCreate is not a valid DirectDraw driver identifier.\0";
        case DDERR_INVALIDMODE:
            return "DirectDraw does not support the requested mode.\0";
        case DDERR_INVALIDOBJECT:
            return "DirectDraw received a pointer that was an invalid DIRECTDRAW object.\0";
        case DDERR_INVALIDPARAMS:
            return "One or more of the parameters passed to the function are incorrect.\0";
        case DDERR_INVALIDPIXELFORMAT:
            return "The pixel format was invalid as specified.\0";
        case DDERR_INVALIDPOSITION:
            return "Returned when the position of the overlay on the destination is no longer legal for that destination.\0";
        case DDERR_INVALIDRECT:
            return "Rectangle provided was invalid.\0";
        case DDERR_LOCKEDSURFACES:
            return "Operation could not be carried out because one or more surfaces are locked.\0";
        case DDERR_NO3D:
            return "There is no 3D present.\0";
        case DDERR_NOALPHAHW:
            return "Operation could not be carried out because there is no alpha accleration hardware present or available.\0";
        case DDERR_NOBLTHW:
            return "No blitter hardware present.\0";
        case DDERR_NOCLIPLIST:
            return "No cliplist available.\0";
        case DDERR_NOCLIPPERATTACHED:
            return "No clipper object attached to surface object.\0";
        case DDERR_NOCOLORCONVHW:
            return "Operation could not be carried out because there is no color conversion hardware present or available.\0";
        case DDERR_NOCOLORKEY:
            return "Surface doesn't currently have a color key\0";
        case DDERR_NOCOLORKEYHW:
            return "Operation could not be carried out because there is no hardware support of the destination color key.\0";
        case DDERR_NOCOOPERATIVELEVELSET:
            return "Create function called without DirectDraw object method SetCooperativeLevel being called.\0";
        case DDERR_NODC:
            return "No DC was ever created for this surface.\0";
        case DDERR_NODDROPSHW:
            return "No DirectDraw ROP hardware.\0";
        case DDERR_NODIRECTDRAWHW:
            return "A hardware-only DirectDraw object creation was attempted but the driver did not support any hardware.\0";
        case DDERR_NOEMULATION:
            return "Software emulation not available.\0";
        case DDERR_NOEXCLUSIVEMODE:
            return "Operation requires the application to have exclusive mode but the application does not have exclusive mode.\0";
        case DDERR_NOFLIPHW:
            return "Flipping visible surfaces is not supported.\0";
        case DDERR_NOGDI:
            return "There is no GDI present.\0";
        case DDERR_NOHWND:
            return "Clipper notification requires an HWND or no HWND has previously been set as the CooperativeLevel HWND.\0";
        case DDERR_NOMIRRORHW:
            return "Operation could not be carried out because there is no hardware present or available.\0";
        case DDERR_NOOVERLAYDEST:
            return "Returned when GetOverlayPosition is called on an overlay that UpdateOverlay has never been called on to establish a destination.\0";
        case DDERR_NOOVERLAYHW:
            return "Operation could not be carried out because there is no overlay hardware present or available.\0";
        case DDERR_NOPALETTEATTACHED:
            return "No palette object attached to this surface.\0";
        case DDERR_NOPALETTEHW:
            return "No hardware support for 16 or 256 color palettes.\0";
        case DDERR_NORASTEROPHW:
            return "Operation could not be carried out because there is no appropriate raster op hardware present or available.\0";
        case DDERR_NOROTATIONHW:
            return "Operation could not be carried out because there is no rotation hardware present or available.\0";
        case DDERR_NOSTRETCHHW:
            return "Operation could not be carried out because there is no hardware support for stretching.\0";
        case DDERR_NOT4BITCOLOR:
            return "DirectDrawSurface is not in 4 bit color palette and the requested operation requires 4 bit color palette.\0";
        case DDERR_NOT4BITCOLORINDEX:
            return "DirectDrawSurface is not in 4 bit color index palette and the requested operation requires 4 bit color index palette.\0";
        case DDERR_NOT8BITCOLOR:
            return "DirectDrawSurface is not in 8 bit color mode and the requested operation requires 8 bit color.\0";
        case DDERR_NOTAOVERLAYSURFACE:
            return "Returned when an overlay member is called for a non-overlay surface.\0";
        case DDERR_NOTEXTUREHW:
            return "Operation could not be carried out because there is no texture mapping hardware present or available.\0";
        case DDERR_NOTFLIPPABLE:
            return "An attempt has been made to flip a surface that is not flippable.\0";
        case DDERR_NOTFOUND:
            return "Requested item was not found.\0";
        case DDERR_NOTLOCKED:
            return "Surface was not locked.  An attempt to unlock a surface that was not locked at all, or by this process, has been attempted.\0";
        case DDERR_NOTPALETTIZED:
            return "The surface being used is not a palette-based surface.\0";
        case DDERR_NOVSYNCHW:
            return "Operation could not be carried out because there is no hardware support for vertical blank synchronized operations.\0";
        case DDERR_NOZBUFFERHW:
            return "Operation could not be carried out because there is no hardware support for zbuffer blitting.\0";
        case DDERR_NOZOVERLAYHW:
            return "Overlay surfaces could not be z layered based on their BltOrder because the hardware does not support z layering of overlays.\0";
        case DDERR_OUTOFCAPS:
            return "The hardware needed for the requested operation has already been allocated.\0";
        case DDERR_OUTOFMEMORY:
            return "DirectDraw does not have enough memory to perform the operation.\0";
        case DDERR_OUTOFVIDEOMEMORY:
            return "DirectDraw does not have enough memory to perform the operation.\0";
        case DDERR_OVERLAYCANTCLIP:
            return "The hardware does not support clipped overlays.\0";
        case DDERR_OVERLAYCOLORKEYONLYONEACTIVE:
            return "Can only have ony color key active at one time for overlays.\0";
        case DDERR_OVERLAYNOTVISIBLE:
            return "Returned when GetOverlayPosition is called on a hidden overlay.\0";
        case DDERR_PALETTEBUSY:
            return "Access to this palette is being refused because the palette is already locked by another thread.\0";
        case DDERR_PRIMARYSURFACEALREADYEXISTS:
            return "This process already has created a primary surface.\0";
        case DDERR_REGIONTOOSMALL:
            return "Region passed to Clipper::GetClipList is too small.\0";
        case DDERR_SURFACEALREADYATTACHED:
            return "This surface is already attached to the surface it is being attached to.\0";
        case DDERR_SURFACEALREADYDEPENDENT:
            return "This surface is already a dependency of the surface it is being made a dependency of.\0";
        case DDERR_SURFACEBUSY:
            return "Access to this surface is being refused because the surface is already locked by another thread.\0";
        case DDERR_SURFACEISOBSCURED:
            return "Access to surface refused because the surface is obscured.\0";
        case DDERR_SURFACELOST:
            return "Access to this surface is being refused because the surface memory is gone. The DirectDrawSurface object representing this surface should have Restore called on it.\0";
        case DDERR_SURFACENOTATTACHED:
            return "The requested surface is not attached.\0";
        case DDERR_TOOBIGHEIGHT:
            return "Height requested by DirectDraw is too large.\0";
        case DDERR_TOOBIGSIZE:
            return "Size requested by DirectDraw is too large, but the individual height and width are OK.\0";
        case DDERR_TOOBIGWIDTH:
            return "Width requested by DirectDraw is too large.\0";
        case DDERR_UNSUPPORTED:
            return "Action not supported.\0";
        case DDERR_UNSUPPORTEDFORMAT:
            return "FOURCC format requested is unsupported by DirectDraw.\0";
        case DDERR_UNSUPPORTEDMASK:
            return "Bitmask in the pixel format requested is unsupported by DirectDraw.\0";
        case DDERR_VERTICALBLANKINPROGRESS:
            return "Vertical blank is in progress.\0";
        case DDERR_WASSTILLDRAWING:
            return "Informs DirectDraw that the previous Blt which is transfering information to or from this Surface is incomplete.\0";
        case DDERR_WRONGMODE:
            return "This surface can not be restored because it was created in a different mode.\0";
        case DDERR_XALIGN:
            return "Rectangle provided was not horizontally aligned on required boundary.\0";
        case D3DERR_BADMAJORVERSION:
            return "D3DERR_BADMAJORVERSION\0";
        case D3DERR_BADMINORVERSION:
            return "D3DERR_BADMINORVERSION\0";
        case D3DERR_EXECUTE_LOCKED:
            return "D3DERR_EXECUTE_LOCKED\0";
        case D3DERR_EXECUTE_NOT_LOCKED:
            return "D3DERR_EXECUTE_NOT_LOCKED\0";
        case D3DERR_EXECUTE_CREATE_FAILED:
            return "D3DERR_EXECUTE_CREATE_FAILED\0";
        case D3DERR_EXECUTE_DESTROY_FAILED:
            return "D3DERR_EXECUTE_DESTROY_FAILED\0";
        case D3DERR_EXECUTE_LOCK_FAILED:
            return "D3DERR_EXECUTE_LOCK_FAILED\0";
        case D3DERR_EXECUTE_UNLOCK_FAILED:
            return "D3DERR_EXECUTE_UNLOCK_FAILED\0";
        case D3DERR_EXECUTE_FAILED:
            return "D3DERR_EXECUTE_FAILED\0";
        case D3DERR_EXECUTE_CLIPPED_FAILED:
            return "D3DERR_EXECUTE_CLIPPED_FAILED\0";
        case D3DERR_TEXTURE_NO_SUPPORT:
            return "D3DERR_TEXTURE_NO_SUPPORT\0";
        case D3DERR_TEXTURE_NOT_LOCKED:
            return "D3DERR_TEXTURE_NOT_LOCKED\0";
        case D3DERR_TEXTURE_LOCKED:
            return "D3DERR_TEXTURELOCKED\0";
        case D3DERR_TEXTURE_CREATE_FAILED:
            return "D3DERR_TEXTURE_CREATE_FAILED\0";
        case D3DERR_TEXTURE_DESTROY_FAILED:
            return "D3DERR_TEXTURE_DESTROY_FAILED\0";
        case D3DERR_TEXTURE_LOCK_FAILED:
            return "D3DERR_TEXTURE_LOCK_FAILED\0";
        case D3DERR_TEXTURE_UNLOCK_FAILED:
            return "D3DERR_TEXTURE_UNLOCK_FAILED\0";
        case D3DERR_TEXTURE_LOAD_FAILED:
            return "D3DERR_TEXTURE_LOAD_FAILED\0";
        case D3DERR_MATRIX_CREATE_FAILED:
            return "D3DERR_MATRIX_CREATE_FAILED\0";
        case D3DERR_MATRIX_DESTROY_FAILED:
            return "D3DERR_MATRIX_DESTROY_FAILED\0";
        case D3DERR_MATRIX_SETDATA_FAILED:
            return "D3DERR_MATRIX_SETDATA_FAILED\0";
        case D3DERR_SETVIEWPORTDATA_FAILED:
            return "D3DERR_SETVIEWPORTDATA_FAILED\0";
        case D3DERR_MATERIAL_CREATE_FAILED:
            return "D3DERR_MATERIAL_CREATE_FAILED\0";
        case D3DERR_MATERIAL_DESTROY_FAILED:
            return "D3DERR_MATERIAL_DESTROY_FAILED\0";
        case D3DERR_MATERIAL_SETDATA_FAILED:
            return "D3DERR_MATERIAL_SETDATA_FAILED\0";
        case D3DERR_LIGHT_SET_FAILED:
            return "D3DERR_LIGHT_SET_FAILED\0";
        case D3DRMERR_BADOBJECT:
            return "D3DRMERR_BADOBJECT\0";
        case D3DRMERR_BADTYPE:
            return "D3DRMERR_BADTYPE\0";
        case D3DRMERR_BADALLOC:
            return "D3DRMERR_BADALLOC\0";
        case D3DRMERR_FACEUSED:
            return "D3DRMERR_FACEUSED\0";
        case D3DRMERR_NOTFOUND:
            return "D3DRMERR_NOTFOUND\0";
        case D3DRMERR_NOTDONEYET:
            return "D3DRMERR_NOTDONEYET\0";
        case D3DRMERR_FILENOTFOUND:
            return "The file was not found.\0";
        case D3DRMERR_BADFILE:
            return "D3DRMERR_BADFILE\0";
        case D3DRMERR_BADDEVICE:
            return "D3DRMERR_BADDEVICE\0";
        case D3DRMERR_BADVALUE:
            return "D3DRMERR_BADVALUE\0";
        case D3DRMERR_BADMAJORVERSION:
            return "D3DRMERR_BADMAJORVERSION\0";
        case D3DRMERR_BADMINORVERSION:
            return "D3DRMERR_BADMINORVERSION\0";
        case D3DRMERR_UNABLETOEXECUTE:
            return "D3DRMERR_UNABLETOEXECUTE\0";
        default:
            return "Unrecognized error value.\0";
    }
}

