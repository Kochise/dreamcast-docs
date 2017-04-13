/***********************************************************************
 *
 * File :       d3dex1.c
 *
 * Abstract :   A very simple Direct3D example which simply draws a
 *              single, rotating, Gouraud shaded triangle in a fixed
 *              size window.
 *
 *              For code clarity a number of issues have not been
 *              addressed in this sample. For example, full screen
 *              operation, resizing the window, texture mapping are
 *              not included. Furthermore, certain optimizations have
 *              not been included where they would obfuscate the code.
 *              Every attempt has been made to highlight these areas
 *              will extensive comments.
 *
 * Author :     Colin D. C. McCartney
 *
 * Date :       09/04/96
 *
 * Version :    V1.0
 *
 * To do:
 * - Handle DDERR_WRONGMODE
 *
 *  Copyright (C) 1995-1997 Microsoft Corporation. All Rights Reserved.
 ***********************************************************************/

/***********************************************************************
 *
 * Include files
 *
 ***********************************************************************/

#define  INITGUID
#include <windows.h>
#include <math.h>
#include <assert.h>
#include <ddraw.h>
#include <d3d.h>

#include "nowarn.h"
#include "resource.h"

// Multi-monitor support
// Include this header file which has helper functions 
// which help us use get the right DirectDraw object for
// the monitor(s) that we want to display on.
#include "ddmm.h"

#ifdef DEBUG
// Make it possible to get reasonable symbols for crummy debuggers
#define static 
#endif


 /***********************************************************************
 *
 * Constants
 *
 ***********************************************************************/

/*
 * Class name for this application's window class.
 */
#define WINDOW_CLASSNAME      "D3DSample1Class"

/*
 * Title for the application's window.
 */
#define WINDOW_TITLE          "D3D Sample 1"

/*
 * String to be displayed when the application is paused.
 */
#define PAUSED_STRING         "Paused"

/*
 * Half height of the view window.
 */
#define HALF_HEIGHT           D3DVAL(0.5)

/*
 * Front and back clipping planes.
 */
#define FRONT_CLIP            D3DVAL(1.0)
#define BACK_CLIP             D3DVAL(1000.0)

/*
 * Fixed window size.
 */
#define WINDOW_WIDTH          320
#define WINDOW_HEIGHT         200

/*
 * Maximum length of the chosen device name and description of the
 * chosen Direct3D device.
 */
#define MAX_DEVICE_NAME       256
#define MAX_DEVICE_DESC       256

/*
 * Amount to rotate per frame.
 */
#define M_PI                  3.14159265359
#define M_2PI                 6.28318530718
#define ROTATE_ANGLE_DELTA    (M_2PI / 300.0)

/*
 * Execute buffer contents
 */
#define NUM_VERTICES          3UL
#define NUM_INSTRUCTIONS      6UL
#define NUM_STATES            8UL
#define NUM_PROCESSVERTICES   1UL
#define NUM_TRIANGLES         1UL

/***********************************************************************
 *
 * Macro funtions.
 *
 ***********************************************************************/

/*
 * Extract the error code from an HRESULT
 */
#define CODEFROMHRESULT(hRes) ((hRes) & 0x0000FFFFUL)

/***********************************************************************
 *
 * Global store
 *
 ***********************************************************************/

/*
 * Application instance handle (set in WinMain).
 */
static HINSTANCE               hAppInstance              = NULL;

/*
 * Running in debug mode?
 */
static BOOL                    fDebug                    = FALSE;

/*
 * Is the app. active?
 */
static BOOL                    fActive                   = TRUE;

/*
 * Has the app. been suspended?
 */
static BOOL                    fSuspended                = FALSE;

/*
 * DirectDraw interfaces
 */
static LPDIRECTDRAW            lpdd                      = NULL;
static LPDIRECTDRAWSURFACE     lpddPrimary               = NULL;
static LPDIRECTDRAWSURFACE     lpddDevice                = NULL;
static LPDIRECTDRAWSURFACE     lpddZBuffer               = NULL;
static LPDIRECTDRAWPALETTE     lpddPalette               = NULL;

/*
 * Direct3D interfaces
 */
static LPDIRECT3D              lpd3d                     = NULL;
static LPDIRECT3DDEVICE        lpd3dDevice               = NULL;
static LPDIRECT3DMATERIAL      lpd3dMaterial             = NULL;
static LPDIRECT3DMATERIAL      lpd3dBackgroundMaterial   = NULL;
static LPDIRECT3DVIEWPORT      lpd3dViewport             = NULL;
static LPDIRECT3DLIGHT         lpd3dLight                = NULL;
static LPDIRECT3DEXECUTEBUFFER lpd3dExecuteBuffer        = NULL;

/*
 * Direct3D handles
 */
static D3DMATRIXHANDLE         hd3dWorldMatrix           = 0UL;
static D3DMATRIXHANDLE         hd3dViewMatrix            = 0UL;
static D3DMATRIXHANDLE         hd3dProjMatrix            = 0UL;
static D3DMATERIALHANDLE       hd3dSurfaceMaterial       = 0UL;
static D3DMATERIALHANDLE       hd3dBackgroundMaterial    = 0UL;

/*
 * Globals used for selecting the Direct3D device. They are
 * globals as it makes it easy for the enumeration callback
 * to read and write from them.
 */
static BOOL                    fDeviceFound              = FALSE;
static DWORD                   dwDeviceBitDepth          = 0UL;
static GUID                    guidDevice;
static char                    szDeviceName[MAX_DEVICE_NAME];
static char                    szDeviceDesc[MAX_DEVICE_DESC];
static D3DDEVICEDESC           d3dHWDeviceDesc;
static D3DDEVICEDESC           d3dSWDeviceDesc;

/*
 * The screen coordinates of the client area of the window. This
 * rectangle defines the destination into which we blit to update
 * the client area of the window with the results of the 3D rendering.
 */
static RECT                    rDstRect;

/*
 * This rectangle defines the portion of the rendering target surface
 * into which we render. The top left coordinates of this rectangle
 * are always zero and the right and bottom give the size of the
 * viewport.
 */
static RECT                    rSrcRect = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};

/*
 * Angle of rotation of the world matrix.
 */
static double                  dAngleOfRotation          = 0.0;

/*
 * Predefined transformations.
 */
static D3DMATRIX d3dWorldMatrix =
{
    D3DVAL( 1.0), D3DVAL( 0.0), D3DVAL( 0.0), D3DVAL( 0.0),
    D3DVAL( 0.0), D3DVAL( 1.0), D3DVAL( 0.0), D3DVAL( 0.0),
    D3DVAL( 0.0), D3DVAL( 0.0), D3DVAL( 1.0), D3DVAL( 0.0),
    D3DVAL( 0.0), D3DVAL( 0.0), D3DVAL( 0.0), D3DVAL( 1.0)
};

static D3DMATRIX d3dViewMatrix =
{
    D3DVAL( 1.0), D3DVAL( 0.0), D3DVAL( 0.0), D3DVAL( 0.0),
    D3DVAL( 0.0), D3DVAL( 1.0), D3DVAL( 0.0), D3DVAL( 0.0),
    D3DVAL( 0.0), D3DVAL( 0.0), D3DVAL( 1.0), D3DVAL( 0.0),
    D3DVAL( 0.0), D3DVAL( 0.0), D3DVAL( 5.0), D3DVAL( 1.0)
};

static D3DMATRIX d3dProjMatrix =
{
    D3DVAL( 2.0), D3DVAL( 0.0), D3DVAL( 0.0), D3DVAL( 0.0),
    D3DVAL( 0.0), D3DVAL( 2.0), D3DVAL( 0.0), D3DVAL( 0.0),
    D3DVAL( 0.0), D3DVAL( 0.0), D3DVAL( 1.0), D3DVAL( 1.0),
    D3DVAL( 0.0), D3DVAL( 0.0), D3DVAL(-1.0), D3DVAL( 0.0)
};

// Multimonitor globals
int     hMonitor;
char    szMonitor[128];
RECT    rectMonitor;


/***********************************************************************
 *
 * Function prototypes
 *
 ***********************************************************************/

static void           ReportError(HWND hwnd, int nMessage, HRESULT hRes);
static void           FatalError(HWND hwnd, int nMessage, HRESULT hRes);

static DWORD          BitDepthToFlags(DWORD dwBitDepth);
static DWORD          FlagsToBitDepth(DWORD dwFlags);

static void           SetPerspectiveProjection(LPD3DMATRIX lpd3dMatrix,
                                               double      dHalfHeight,
                                               double      dFrontClipping,
                                               double      dBackClipping);
static void           SetRotationAboutY(LPD3DMATRIX lpd3dMatrix,
                                        double      dAngleOfRotation);

static HRESULT        CreateDirect3D(HWND hwnd);
static HRESULT        ReleaseDirect3D(void);

static HRESULT        CreatePrimary(HWND hwnd);
static HRESULT        RestorePrimary(void);
static HRESULT        ReleasePrimary(void);

static HRESULT WINAPI EnumDeviceCallback(LPGUID          lpGUID, 
                                         LPSTR           lpszDeviceDesc,
                                         LPSTR           lpszDeviceName,
                                         LPD3DDEVICEDESC lpd3dHWDeviceDesc,
                                         LPD3DDEVICEDESC lpd3dSWDeviceDesc,
                                         LPVOID          lpUserArg);
static HRESULT        ChooseDevice(void);

static HRESULT        CreateDevice(DWORD dwWidth, DWORD dwHeight);
static HRESULT        RestoreDevice(void);
static HRESULT        ReleaseDevice(void);

static LRESULT        RestoreSurfaces(void);

static HRESULT        FillExecuteBuffer(void);
static HRESULT        CreateScene(void);
static HRESULT        ReleaseScene(void);
static HRESULT        AnimateScene(void);

static HRESULT        UpdateViewport(void);

static HRESULT        RenderScene(void);
static HRESULT        DoFrame(HWND hwnd);
static void           PaintSuspended(HWND hwnd, HDC hdc);

static LRESULT        OnMove(HWND hwnd, int x, int y);
static LRESULT        OnSize(HWND hwnd, int w, int h);
static LRESULT        OnPaint(HWND hwnd, HDC hdc, LPPAINTSTRUCT lpps);
static LRESULT        OnIdle(HWND hwnd);

// Multimonitor 
static HRESULT	      CheckMonitors(HWND hwnd, BOOL fReset);

LRESULT CALLBACK      WndProc(HWND hwnd, UINT msg,
                              WPARAM wParam, LPARAM lParam);
int PASCAL            WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                              LPSTR lpszCommandLine, int cmdShow);

/***********************************************************************
 *
 * Macro functions
 *
 ***********************************************************************/

/***********************************************************************/

#ifdef _DEBUG
#define ASSERT(x)       assert(x)
#else
#define ASSERT(x)
#endif

/***********************************************************************/

/*
 * Used to keep the compiler happy about any unused parameters.
 */
#define USE_PARAM(x)    (x) = (x)

/***********************************************************************/

/***********************************************************************
 *
 * Functions
 *
 ***********************************************************************/

/***********************************************************************/

/*
 * Report the given error by display a message box.
 */
static void
ReportError(HWND hwnd, int nMessage, HRESULT hRes)
{
    HDC  hdc;
    char szBuffer[256];
    char szMessage[128];
    char szError[128];
    int  nStrID;

    /*
     * Turn the animation loop off.
     */
    fSuspended = TRUE;

    /*
     * Get the high level error message.
     */
    LoadString(hAppInstance, nMessage, szMessage, sizeof(szMessage));

    /*
     * We issue sensible error messages for common run time errors. For
     * errors which are internal or coding errors we simply issue an
     * error number (they should never occur).
     */
    switch (hRes)
    {
        case DDERR_EXCEPTION:        nStrID = IDS_ERR_EXCEPTION;        break;
        case DDERR_GENERIC:          nStrID = IDS_ERR_GENERIC;          break;
        case DDERR_OUTOFMEMORY:      nStrID = IDS_ERR_OUTOFMEMORY;      break;
        case DDERR_OUTOFVIDEOMEMORY: nStrID = IDS_ERR_OUTOFVIDEOMEMORY; break;
        case DDERR_SURFACEBUSY:      nStrID = IDS_ERR_SURFACEBUSY;      break;
        case DDERR_SURFACELOST:      nStrID = IDS_ERR_SURFACELOST;      break;
        case DDERR_WRONGMODE:        nStrID = IDS_ERR_WRONGMODE;        break;
        default:                     nStrID = IDS_ERR_INTERNALERROR;    break;
    }
    LoadString(hAppInstance, nStrID, szError, sizeof(szError));

    /*
     * Show the "paused" display.
     */
    hdc = GetDC(hwnd);
    PaintSuspended(hwnd, hdc);
    ReleaseDC(hwnd, hdc);

    /*
     * Convert the error code into a string (not very informative but
     * it keeps the code simple).
     */
    wsprintf(szBuffer, "%s\n%s (Error #%d)", szMessage, szError, CODEFROMHRESULT(hRes));
    MessageBox(hwnd, szBuffer, WINDOW_TITLE, MB_OK | MB_APPLMODAL);
    fSuspended = FALSE;
}

/***********************************************************************/

/*
 * Handle a fatal error. Displays the error message via a message box
 * and then destroys the window.
 */
static void
FatalError(HWND hwnd, int nMessage, HRESULT hRes)
{
    /*
     * Report the error.
     */
    ReportError(hwnd, nMessage, hRes);
    fSuspended = TRUE;

    /*
     * And shut down.
     *
     * NOTE: We don't attempt to clean up. That will be done
     * when WM_DESTROY happens.
     */
    DestroyWindow(hwnd);
}

/***********************************************************************/

/*
 * Converts a bit depth into the appropriate DirectDraw bit depth flag.
 */
static DWORD
BitDepthToFlags(DWORD dwBitDepth)
{
    switch (dwBitDepth)
    {
        case  1UL: return DDBD_1;
        case  2UL: return DDBD_2;
        case  4UL: return DDBD_4;
        case  8UL: return DDBD_8;
        case 16UL: return DDBD_16;
        case 24UL: return DDBD_24;
        case 32UL: return DDBD_32;
        default:   return 0UL;     /* Oh, please... */
    }
}

/***********************************************************************/

/*
 * Convert bit depth flags to an acutal bit count. Selects the smallest
 * bit count in the mask if more than one flag is present.
 */
static DWORD
FlagsToBitDepth(DWORD dwFlags)
{
    if (dwFlags & DDBD_1)
        return 1UL;
    else if (dwFlags & DDBD_2)
        return 2UL;
    else if (dwFlags & DDBD_4)
        return 4UL;
    else if (dwFlags & DDBD_8)
        return 8UL;
    else if (dwFlags & DDBD_16)
        return 16UL;
    else if (dwFlags & DDBD_24)
        return 24UL;
    else if (dwFlags & DDBD_32)
        return 32UL;
    else
        return 0UL; /* Oh, please... */
}

/***********************************************************************/

/*
 * Set the given matrix to a perspective transform for the given half
 * height and front and back clipping planes.
 */
static void
SetPerspectiveProjection(LPD3DMATRIX lpd3dMatrix,
                         double      dHalfHeight,
                         double      dFrontClipping,
                         double      dBackClipping)
{
    double dTmp1;
    double dTmp2;

    ASSERT(NULL != lpd3dMatrix);

    dTmp1 = dHalfHeight / dFrontClipping;
    dTmp2 = dBackClipping / (dBackClipping - dFrontClipping);

    lpd3dMatrix->_11 =  D3DVAL(2.0);
    lpd3dMatrix->_12 =  D3DVAL(0.0);
    lpd3dMatrix->_13 =  D3DVAL(0.0);
    lpd3dMatrix->_14 =  D3DVAL(0.0);
    lpd3dMatrix->_21 =  D3DVAL(0.0);
    lpd3dMatrix->_22 =  D3DVAL(2.0);
    lpd3dMatrix->_23 =  D3DVAL(0.0);
    lpd3dMatrix->_24 =  D3DVAL(0.0);
    lpd3dMatrix->_31 =  D3DVAL(0.0);
    lpd3dMatrix->_32 =  D3DVAL(0.0);
    lpd3dMatrix->_33 =  D3DVAL(dTmp1 * dTmp2);
    lpd3dMatrix->_34 =  D3DVAL(dTmp1);
    lpd3dMatrix->_41 =  D3DVAL(0.0);
    lpd3dMatrix->_42 =  D3DVAL(0.0);
    lpd3dMatrix->_43 =  D3DVAL(-dHalfHeight * dTmp2);
    lpd3dMatrix->_44 =  D3DVAL(0.0);
}


/***********************************************************************/

/*
 * Set the given matrix to a rotation about Y transform of the given
 * number of radians.
 */
static void
SetRotationAboutY(LPD3DMATRIX lpd3dMatrix, double dAngleOfRotation)
{
    D3DVALUE dvCos;
    D3DVALUE dvSin;

    ASSERT(NULL != lpd3dMatrix);

    dvCos = D3DVAL(cos(dAngleOfRotation));
    dvSin = D3DVAL(sin(dAngleOfRotation));

    lpd3dMatrix->_11 =  dvCos;
    lpd3dMatrix->_12 =  D3DVAL(0.0);
    lpd3dMatrix->_13 = -dvSin;
    lpd3dMatrix->_14 =  D3DVAL(0.0);
    lpd3dMatrix->_21 =  D3DVAL(0.0);
    lpd3dMatrix->_22 =  D3DVAL(1.0);
    lpd3dMatrix->_23 =  D3DVAL(0.0);
    lpd3dMatrix->_24 =  D3DVAL(0.0);
    lpd3dMatrix->_31 =  dvSin;
    lpd3dMatrix->_32 =  D3DVAL(0.0);
    lpd3dMatrix->_33 =  dvCos;
    lpd3dMatrix->_34 =  D3DVAL(0.0);
    lpd3dMatrix->_41 =  D3DVAL(0.0);
    lpd3dMatrix->_42 =  D3DVAL(0.0);
    lpd3dMatrix->_43 =  D3DVAL(0.0);
    lpd3dMatrix->_44 =  D3DVAL(1.0);
}

/***********************************************************************/

/*
 * Create the DirectDraw/3D driver object and get DirectDraw and Direct3D
 * interfaces for communicating with that object.
 */
static HRESULT
CreateDirect3D(HWND hwnd)
{
    HRESULT hRes;

    ASSERT(NULL == lpdd);
    ASSERT(NULL == lpd3d);

    /*
     * Create the DirectDraw/3D driver object and get the DirectDraw
     * interface to that object.
     */
    lpdd = DirectDrawCreateFromWindow(hwnd);
    if (lpdd == NULL)
        return E_FAIL;

    /*
     * As we are running in a window set the cooperative level to 
     * normal. Also, to ensure that the palette is realized correctly
     * we need to pass the hwnd of the main window.
     */
    hRes = lpdd->lpVtbl->SetCooperativeLevel(lpdd, hwnd, DDSCL_NORMAL);
    if (FAILED(hRes))
        return hRes;

    /*
     * Get the Direct3D interface to the DirectDraw/3D driver object.
     */
    hRes = lpdd->lpVtbl->QueryInterface(lpdd, &IID_IDirect3D, &lpd3d);
    if (FAILED(hRes))
        return hRes;

    return DD_OK;
}

/***********************************************************************/

/*
 * Release the DirectDraw/3D driver object.
 */
static HRESULT
ReleaseDirect3D(void)
{
    if (NULL != lpd3d)
    {
        lpd3d->lpVtbl->Release(lpd3d);
        lpd3d = NULL;
    }
    if (NULL != lpdd)
    {
        lpdd->lpVtbl->Release(lpdd);
        lpdd = NULL;
    }

    return DD_OK;
}

/***********************************************************************/

/*
 * Create the primary surface (representing the desktop) and create and
 * attach a clipper and, if necessary, a palette.
 */
static HRESULT
CreatePrimary(HWND hwnd)
{
    HRESULT             hRes;
    DDSURFACEDESC       ddsd;
    LPDIRECTDRAWCLIPPER lpddClipper;
    HDC                 hdc;
    int                 i;
    PALETTEENTRY        peColorTable[256];

    ASSERT(NULL != hwnd);
    ASSERT(NULL != lpdd);
    ASSERT(NULL == lpddPrimary);
    ASSERT(NULL == lpddPalette);

    /*
     * Create the primary surface.
     */
    ZeroMemory(&ddsd, sizeof(ddsd));
    ddsd.dwSize         = sizeof(ddsd);
    ddsd.dwFlags        = DDSD_CAPS;
    ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;
    hRes = lpdd->lpVtbl->CreateSurface(lpdd, &ddsd, &lpddPrimary, NULL);
    if (FAILED(hRes))
        return hRes;

    /*
     * Create the clipper. We bind the application's window to the
     * clipper and attach it to the primary. This ensures then when we
     * blit from the rendering surface to the primary we don't write
     * outside the visible region of the window.
     */
    hRes = DirectDrawCreateClipper(0UL, &lpddClipper, NULL);
    if (FAILED(hRes))
        return hRes;
    hRes = lpddClipper->lpVtbl->SetHWnd(lpddClipper, 0UL, hwnd);
    if (FAILED(hRes))
    {
        lpddClipper->lpVtbl->Release(lpddClipper);
        return hRes;
    }
    hRes = lpddPrimary->lpVtbl->SetClipper(lpddPrimary, lpddClipper);
    if (FAILED(hRes))
    {
        lpddClipper->lpVtbl->Release(lpddClipper);
        return hRes;
    }

    /*
     * We release the clipper interface after attaching it to the surface
     * as we don't need to use it again. The surface holds a reference to
     * the clipper when its been attached. The clipper will therefore be
     * released when the surface is released.
     */
    lpddClipper->lpVtbl->Release(lpddClipper);

    /*
     * If the primary is palettized then so will the device (the device
     * surface must have the same pixel format as the current primary if
     * we want to double buffer with DirectDraw). Hence, if the primary
     * is palettized we need to create a palette and attach it to the
     * primary (and to the device surface when we create it).
     */
    ZeroMemory(&ddsd, sizeof(ddsd));
    ddsd.dwSize = sizeof(ddsd);
    hRes = lpddPrimary->lpVtbl->GetSurfaceDesc(lpddPrimary, &ddsd);
    if (FAILED(hRes))
        return hRes;
    if (ddsd.ddpfPixelFormat.dwFlags & DDPF_PALETTEINDEXED8)
    {
        /*
         * Initializing the palette correctly is essential. We are
         * running in a window so we need to be a good windows app
         * and not mess with the top ten and bottom ten static
         * colors. Therefore, we copy them from the system palette
         * and mark them as read only (D3DPAL_READONLY). The middle
         * 236 entries are free for use by Direct3D so we mark them
         * free (D3DPAL_FREE).
         *
         * NOTE: In order that the palette entries are correctly
         * allocated it is essential that the free entries are
         * also marked reserved to GDI (PC_RESERVED).
         *
         * NOTE: We don't need to specify the palette caps flag
         * DDPCAPS_INITIALIZE. This flag is obsolete. CreatePalette
         * must be given a valid palette entry array and always
         * initializes from it.
         */
        hdc = GetDC(NULL);
        GetSystemPaletteEntries(hdc, 0, 256, peColorTable);
        ReleaseDC(NULL, hdc);

        for (i = 0; i < 10; i++)
            peColorTable[i].peFlags = D3DPAL_READONLY;
        for (i = 10; i < 246; i++)
            peColorTable[i].peFlags = D3DPAL_FREE | PC_RESERVED;
        for (i = 246; i < 256; i++)
            peColorTable[i].peFlags = D3DPAL_READONLY;
        hRes = lpdd->lpVtbl->CreatePalette(lpdd,
                                           DDPCAPS_8BIT,
                                           peColorTable,
                                           &lpddPalette,
                                           NULL);
        if (FAILED(hRes))
            return hRes;

        hRes = lpddPrimary->lpVtbl->SetPalette(lpddPrimary, lpddPalette);
            return hRes;
    }

    return DD_OK;
}

/***********************************************************************/

/*
 * Attempt to restore the video memory allocated for the primary. This
 * function will be invoked by a DirectX function returning
 * DDERR_SURFACELOST due to a mode switch or fullscreen DOS box
 * invalidating video memory.
 */
static HRESULT
RestorePrimary(void)
{
    ASSERT(NULL != lpddPrimary);

    return lpddPrimary->lpVtbl->Restore(lpddPrimary);
}

/***********************************************************************/

/*
 * Release the primary surface and its attached clipper and palette.
 */
static HRESULT
ReleasePrimary(void)
{
    if (NULL != lpddPalette)
    {
        lpddPalette->lpVtbl->Release(lpddPalette);
        lpddPalette = NULL;
    }
    if (NULL != lpddPrimary)
    {
        lpddPrimary->lpVtbl->Release(lpddPrimary);
        lpddPrimary = NULL;
    }

    return DD_OK;
}

/***********************************************************************/

/*
 * This callback is invoked for each Direct3D device installed on the
 * system. For each device we get its identifying GUID, a name and
 * description, a description of its hardware and software capabilities
 * and a user argument (which we don't use).
 */
static HRESULT WINAPI
EnumDeviceCallback(LPGUID          lpGUID, 
                   LPSTR           lpszDeviceDesc,
                   LPSTR           lpszDeviceName,
                   LPD3DDEVICEDESC lpd3dHWDeviceDesc,
                   LPD3DDEVICEDESC lpd3dSWDeviceDesc,
                   LPVOID          lpUserArg)
{
    BOOL            fIsHardware;
    LPD3DDEVICEDESC lpd3dDeviceDesc;

    /*
     * We don't use the user argument so just keep the compiler happy.
     */
    USE_PARAM(lpUserArg);

    /*
     * If there is no hardware support then the color model is zero.
     */
    fIsHardware     = (0UL != lpd3dHWDeviceDesc->dcmColorModel);
    lpd3dDeviceDesc = (fIsHardware ? lpd3dHWDeviceDesc : lpd3dSWDeviceDesc);

    /*
     * If we are in debug mode and this is a hardware device skip it.
     */
    if (fDebug && fIsHardware)
        return D3DENUMRET_OK;

    /*
     * Does the device render at the depth we want?
     */
    if (0UL == (lpd3dDeviceDesc->dwDeviceRenderBitDepth & dwDeviceBitDepth))
    {
        /*
         * No skip this device.
         */
        return D3DENUMRET_OK;
    }

    /*
     * The device must support gouraud shaded triangles.
     */
    if (D3DCOLOR_MONO == lpd3dDeviceDesc->dcmColorModel)
    {
        if (!(lpd3dDeviceDesc->dpcTriCaps.dwShadeCaps & D3DPSHADECAPS_COLORGOURAUDMONO))
        {
            /*
             * No gouraud shading. Skip this device.
             */
            return D3DENUMRET_OK;
        }
    }
    else
    {
        if (!(lpd3dDeviceDesc->dpcTriCaps.dwShadeCaps & D3DPSHADECAPS_COLORGOURAUDRGB))
        {
            /*
             * No gouraud shading. Skip this device.
             */
            return D3DENUMRET_OK;
        }
    }

    if (!fIsHardware && fDeviceFound && (D3DCOLOR_RGB == lpd3dDeviceDesc->dcmColorModel))
    {
        /*
         * If this is software RGB and we already have found a software
         * mono already then we are not interested. Skip it.
         */
        return D3DENUMRET_OK;
    }

    /*
     * This is a device we are interested in - cache the details away.
     */
    fDeviceFound = TRUE;
    CopyMemory(&guidDevice, lpGUID, sizeof(GUID));
    strcpy(szDeviceDesc, lpszDeviceDesc);
    strcpy(szDeviceName, lpszDeviceName);
    CopyMemory(&d3dHWDeviceDesc, lpd3dHWDeviceDesc, sizeof(D3DDEVICEDESC));
    CopyMemory(&d3dSWDeviceDesc, lpd3dSWDeviceDesc, sizeof(D3DDEVICEDESC));

    /*
     * If this is a hardware device we have found what we are looking
     * for.
     */
    if (fIsHardware)
        return D3DENUMRET_CANCEL;

    /*
     * Keep looking...
     */
    return D3DENUMRET_OK;
}
                            
/***********************************************************************/

/*
 * Choose an appropriate Direct3D using the following mechanism:
 *
 * 1) Discard any devices which don't match the current display depth.
 * 2) Discard any devices which can't do gouraud shaded triangles.
 * 3) If a hardware device is found which matches 1) and 2) use it.
 *    However, if we are running in debug mode we will skip hardware.
 * 4) Otherwise favour Mono/Ramp mode software renderers over RGB ones
 *    as, at least until MMX is widespread, Mono will be faster.
 *
 * The actual implementation of this mechanism is in the callback
 * function above.
 */
static HRESULT
ChooseDevice(void)
{
    DDSURFACEDESC ddsd;
    HRESULT       hRes;

    ASSERT(NULL != lpd3d);
    ASSERT(NULL != lpddPrimary);

    /*
     * As we are running in a window we will not be changing the screen
     * depth and hence the pixel format of the rendering target must match
     * the pixel format of the current primary. Therefore, we need to
     * determine the pixel format of the primary.
     */
    ZeroMemory(&ddsd, sizeof(ddsd));
    ddsd.dwSize = sizeof(ddsd);
    hRes = lpddPrimary->lpVtbl->GetSurfaceDesc(lpddPrimary, &ddsd);
    if (FAILED(hRes))
        return hRes;

    dwDeviceBitDepth = BitDepthToFlags(ddsd.ddpfPixelFormat.dwRGBBitCount);

    /*
     * Enumerate the devices and pick one.
     */
    fDeviceFound = FALSE;
    hRes = lpd3d->lpVtbl->EnumDevices(lpd3d, EnumDeviceCallback, &fDeviceFound);
    if (FAILED(hRes))
        return hRes;

    if (!fDeviceFound)
    {
        /*
         * No suitable device was found. We have no alternative but to
         * fail creation entirely.
         */
        return DDERR_NOTFOUND;
    }

    return DD_OK;
}

/***********************************************************************/

/*
 * Create an instance of the Direct3D device we choose earlier with the
 * given width and height.
 *
 * This function handles all aspects of the device creation including
 * choosing surface memory type, create the device surface, the z-buffer
 * (if necessary) and attaching the palette (if required).
 */
static HRESULT
CreateDevice(DWORD dwWidth, DWORD dwHeight)
{
    LPD3DDEVICEDESC lpd3dDeviceDesc;
    DWORD           dwDeviceMemType;
    DWORD           dwZBufferMemType;
    DDSURFACEDESC   ddsd;
    HRESULT         hRes;
    DWORD           dwZBufferBitDepth;

    ASSERT(NULL != lpdd);
    ASSERT(NULL != lpd3d);
    ASSERT(NULL != lpddPrimary);
    ASSERT(NULL == lpddDevice);
    ASSERT(NULL == lpd3dDevice);

    /*
     * The first step is to determine the kind of memory (system or
     * video) from which the device surface should be allocated.
     */
    if (0UL != d3dHWDeviceDesc.dcmColorModel)
    {
        lpd3dDeviceDesc = &d3dHWDeviceDesc;

        /*
         * Device has a hardware rasterizer. Currently this means that
         * the device surface must be in video memory.
         */
        dwDeviceMemType  = DDSCAPS_VIDEOMEMORY;
        dwZBufferMemType = DDSCAPS_VIDEOMEMORY;
    }
    else
    {
        lpd3dDeviceDesc = &d3dSWDeviceDesc;

        /*
         * Device has a software rasterizer. We will let DirectDraw
         * decide where the device surface resides unless we are
         * running in debug mode in which case we will force it into
         * system memory. For a software rasterizer the z-buffer should
         * always go into system memory. A z-buffer in video memory will
         * kill performance.
         */
        dwDeviceMemType  = (fDebug ? DDSCAPS_SYSTEMMEMORY : 0UL);
        dwZBufferMemType = DDSCAPS_SYSTEMMEMORY;
    }

    /*
     * Create the device surface. The pixel format will be identical
     * to the primary so we don't have to explicitly specify it. We do
     * need to explicity specify the size, memory type and capabilities
     * of the surface.
     */
    ZeroMemory(&ddsd, sizeof(ddsd));
    ddsd.dwSize         = sizeof(ddsd);
    ddsd.dwFlags        = DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT;
    ddsd.dwWidth        = dwWidth;
    ddsd.dwHeight       = dwHeight;
    ddsd.ddsCaps.dwCaps = DDSCAPS_3DDEVICE | DDSCAPS_OFFSCREENPLAIN | dwDeviceMemType;
    hRes = lpdd->lpVtbl->CreateSurface(lpdd, &ddsd, &lpddDevice, NULL);
    if (FAILED(hRes))
        return hRes;

    /*
     * If we have created a palette then we have already determined that
     * the primary (and hence the device surface) is palettized so 
     * attach the palette to the device surface (its already attached to
     * the primary).
     */
    if (NULL != lpddPalette)
    {
        hRes = lpddDevice->lpVtbl->SetPalette(lpddDevice, lpddPalette);
        if (FAILED(hRes))
            return hRes;
    }

    /*
     * We now determine whether we need a z-buffer or not and if so
     * its bit depth. 
     */
    if (0UL != lpd3dDeviceDesc->dwDeviceZBufferBitDepth)
    {
        /*
         * The device supports z-buffering. Determine the depth. We
         * select the lowest supported z-buffer depth to save memory.
         * Accuracy is not too important for this sample.
         */
        dwZBufferBitDepth = FlagsToBitDepth(lpd3dDeviceDesc->dwDeviceZBufferBitDepth);

        /*
         * Create the z-buffer.
         */
        ZeroMemory(&ddsd, sizeof(ddsd));
        ddsd.dwSize            = sizeof(ddsd);
        ddsd.dwFlags           = DDSD_CAPS   |
                                 DDSD_WIDTH  |
                                 DDSD_HEIGHT |
                                 DDSD_ZBUFFERBITDEPTH;
        ddsd.ddsCaps.dwCaps    = DDSCAPS_ZBUFFER | dwZBufferMemType;
        ddsd.dwWidth           = dwWidth;
        ddsd.dwHeight          = dwHeight;
        ddsd.dwZBufferBitDepth = dwZBufferBitDepth;
        hRes = lpdd->lpVtbl->CreateSurface(lpdd, &ddsd, &lpddZBuffer, NULL);
        if (FAILED(hRes))
            return hRes;

        /*
         * Attach it to the rendering target.
         */
        hRes = lpddDevice->lpVtbl->AddAttachedSurface(lpddDevice, lpddZBuffer);
        if (FAILED(hRes))
            return hRes;
    }

    /*
     * Now all the elements are in place (device surface in correct
     * memory type, attached z-buffer of correct depth and memory
     * type, and palette if necessary) we can actually query for the
     * Direct3D we choose earlier.
     */
    hRes = lpddDevice->lpVtbl->QueryInterface(lpddDevice,
                                              &guidDevice,
                                              &lpd3dDevice);
    if (FAILED(hRes))
        return hRes;

    return DD_OK;
}

/***********************************************************************/

/*
 * Restore the video memory for the device surface and z-buffer if it
 * has been lost.
 */
static HRESULT
RestoreDevice(void)
{
    HRESULT hRes;

    if (NULL != lpddZBuffer)
    {
        hRes = lpddZBuffer->lpVtbl->Restore(lpddZBuffer);
        if (FAILED(hRes))
            return hRes;
    }

    if (NULL != lpddDevice)
    {
        hRes = lpddDevice->lpVtbl->Restore(lpddDevice);
        if (FAILED(hRes))
            return hRes;
    }

    return DD_OK;
}

/***********************************************************************/

/*
 * Release the Direct3D device and its associated surfaces.
 */
static HRESULT
ReleaseDevice(void)
{
    if (NULL != lpd3dDevice)
    {
        lpd3dDevice->lpVtbl->Release(lpd3dDevice);
        lpd3dDevice = NULL;
    }
    if (NULL != lpddZBuffer)
    {
        lpddZBuffer->lpVtbl->Release(lpddZBuffer);
        lpddZBuffer = NULL;
    }
    if (NULL != lpddDevice)
    {
        lpddDevice->lpVtbl->Release(lpddDevice);
        lpddDevice = NULL;
    }

    return DD_OK;
}

/***********************************************************************/

/*
 * Attempt to restore all the surfaces used by the application.
 */
static LRESULT
RestoreSurfaces(void)
{
    HRESULT hRes;

    hRes = RestorePrimary();
    if (FAILED(hRes))
        return hRes;

    hRes = RestoreDevice();
    if (FAILED(hRes))
        return hRes;

    return DD_OK;
}

/***********************************************************************/

/*
 * Fill the single execute buffer used in this sample with all the
 * vertices, transform, light and render state and drawing primitives
 * necessary to draw our triangle.
 *
 * NOTE: This is not the most efficient way of organizing the execute
 * buffer. For best performance you want to minimize state changes. In
 * this sample we submit the execute buffer for each frame in the
 * animation loop and no state in the buffer is modified. The only 
 * thing we modify is the world matrix (its contents - not its handle).
 * Therefore, it would be more efficient to extract all the static
 * state instructions into a separate execute buffer which we issue
 * once only at startup and, from then on, simply execute a second
 * execute buffer with vertices and triangles.
 * However, this sample is not exactly performance critical so we will
 * just use one execute buffer and resubmit it its entirety for each
 * frame.
 */
static HRESULT
FillExecuteBuffer(void)
{
    HRESULT              hRes;
    D3DEXECUTEBUFFERDESC d3dExeBufDesc;
    LPD3DVERTEX          lpVertex;
    LPD3DINSTRUCTION     lpInstruction;
    LPD3DPROCESSVERTICES lpProcessVertices;
    LPD3DTRIANGLE        lpTriangle;
    LPD3DSTATE           lpState;

    ASSERT(NULL != lpd3dExecuteBuffer);
    ASSERT(0UL  != hd3dSurfaceMaterial);
    ASSERT(0UL  != hd3dWorldMatrix);
    ASSERT(0UL  != hd3dViewMatrix);
    ASSERT(0UL  != hd3dProjMatrix);

    /*
     * Lock the execute buffer.
     */
    ZeroMemory(&d3dExeBufDesc, sizeof(d3dExeBufDesc));
    d3dExeBufDesc.dwSize = sizeof(d3dExeBufDesc);
    hRes = lpd3dExecuteBuffer->lpVtbl->Lock(lpd3dExecuteBuffer, &d3dExeBufDesc);
    if (FAILED(hRes))
        return hRes;

    /*
     * For explanatory purposes we fill the execute buffer by casting
     * a pointer to the execute buffer to the appropriate data structures.
     *
     * !!! NOTE: Issue - alignment.
     */
    lpVertex = (LPD3DVERTEX)d3dExeBufDesc.lpData;

    /*
     * First vertex.
     */
    lpVertex->dvX  = D3DVAL( 0.0); /* Position in model coordinates       */
    lpVertex->dvY  = D3DVAL( 1.0);
    lpVertex->dvZ  = D3DVAL( 0.0);
    lpVertex->dvNX = D3DVAL( 0.0); /* Normalized illumination normal      */
    lpVertex->dvNY = D3DVAL( 0.0);
    lpVertex->dvNZ = D3DVAL(-1.0);
    lpVertex->dvTU = D3DVAL( 0.0); /* Texture coordinates (not used here) */
    lpVertex->dvTV = D3DVAL( 1.0);
    lpVertex++;

    /*
     * Second vertex.
     */
    lpVertex->dvX  = D3DVAL( 1.0); /* Position in model coordinates       */
    lpVertex->dvY  = D3DVAL(-1.0);
    lpVertex->dvZ  = D3DVAL( 0.0);
    lpVertex->dvNX = D3DVAL( 0.0); /* Normalized illumination normal      */
    lpVertex->dvNY = D3DVAL( 0.0);
    lpVertex->dvNZ = D3DVAL(-1.0);
    lpVertex->dvTU = D3DVAL( 1.0); /* Texture coordinates (not used here) */
    lpVertex->dvTV = D3DVAL( 1.0);
    lpVertex++;

    /*
     * Third vertex.
     */
    lpVertex->dvX  = D3DVAL(-1.0); /* Position in model coordinates       */
    lpVertex->dvY  = D3DVAL(-1.0);
    lpVertex->dvZ  = D3DVAL( 0.0);
    lpVertex->dvNX = D3DVAL( 0.0); /* Normalized illumination normal      */
    lpVertex->dvNY = D3DVAL( 0.0);
    lpVertex->dvNZ = D3DVAL(-1.0);
    lpVertex->dvTU = D3DVAL( 1.0); /* Texture coordinates (not used here) */
    lpVertex->dvTV = D3DVAL( 0.0);
    lpVertex++;

    /*
     * Transform state - world, view and projection.
     */
    lpInstruction = (LPD3DINSTRUCTION)lpVertex;
    lpInstruction->bOpcode = D3DOP_STATETRANSFORM;
    lpInstruction->bSize   = sizeof(D3DSTATE);
    lpInstruction->wCount  = 3U;
    lpInstruction++;
    lpState = (LPD3DSTATE)lpInstruction;
    lpState->dtstTransformStateType = D3DTRANSFORMSTATE_WORLD;
    lpState->dwArg[0] = hd3dWorldMatrix;
    lpState++;
    lpState->dtstTransformStateType = D3DTRANSFORMSTATE_VIEW;
    lpState->dwArg[0] = hd3dViewMatrix;
    lpState++;
    lpState->dtstTransformStateType = D3DTRANSFORMSTATE_PROJECTION;
    lpState->dwArg[0] = hd3dProjMatrix;
    lpState++;

    /*
     * Lighting state.
     */
    lpInstruction = (LPD3DINSTRUCTION)lpState;
    lpInstruction->bOpcode = D3DOP_STATELIGHT;
    lpInstruction->bSize   = sizeof(D3DSTATE);
    lpInstruction->wCount  = 2U;
    lpInstruction++;
    lpState = (LPD3DSTATE)lpInstruction;
    lpState->dlstLightStateType = D3DLIGHTSTATE_MATERIAL;
    lpState->dwArg[0] = hd3dSurfaceMaterial;
    lpState++;
    lpState->dlstLightStateType = D3DLIGHTSTATE_AMBIENT;
    lpState->dwArg[0] = RGBA_MAKE(128, 128, 128, 128);
    lpState++;

    /*
     * Render state.
     */
    lpInstruction = (LPD3DINSTRUCTION)lpState;
    lpInstruction->bOpcode = D3DOP_STATERENDER;
    lpInstruction->bSize = sizeof(D3DSTATE);
    lpInstruction->wCount = 3U;
    lpInstruction++;
    lpState = (LPD3DSTATE)lpInstruction;
    lpState->drstRenderStateType = D3DRENDERSTATE_FILLMODE;
    lpState->dwArg[0] = D3DFILL_SOLID;
    lpState++;
    lpState->drstRenderStateType = D3DRENDERSTATE_SHADEMODE;
    lpState->dwArg[0] = D3DSHADE_GOURAUD;
    lpState++;
    lpState->drstRenderStateType = D3DRENDERSTATE_DITHERENABLE;
    lpState->dwArg[0] = TRUE;
    lpState++;

    /*
     * The process vertices instruction tells the driver what to
     * do with the vertices in the buffer. In this sample we want
     * Direct3D to perform the entire pipeline on our behalf so
     * the instruction is D3DPROCESSVERTICES_TRANSFORMLIGHT.
     */
    lpInstruction = (LPD3DINSTRUCTION)lpState;
    lpInstruction->bOpcode = D3DOP_PROCESSVERTICES;
    lpInstruction->bSize   = sizeof(D3DPROCESSVERTICES);
    lpInstruction->wCount  = 1U;
    lpInstruction++;
    lpProcessVertices = (LPD3DPROCESSVERTICES)lpInstruction;
    lpProcessVertices->dwFlags    = D3DPROCESSVERTICES_TRANSFORMLIGHT;
    lpProcessVertices->wStart     = 0U;           /* First source vertex */
    lpProcessVertices->wDest      = 0U;
    lpProcessVertices->dwCount    = NUM_VERTICES; /* Number of vertices  */
    lpProcessVertices->dwReserved = 0UL;
    lpProcessVertices++;

    /*
     * Draw the triangle.
     */
    lpInstruction = (LPD3DINSTRUCTION)lpProcessVertices;
    lpInstruction->bOpcode = D3DOP_TRIANGLE;
    lpInstruction->bSize   = sizeof(D3DTRIANGLE);
    lpInstruction->wCount  = 1U;
    lpInstruction++;
    lpTriangle = (LPD3DTRIANGLE)lpInstruction;
    lpTriangle->wV1    = 0U; 
    lpTriangle->wV2    = 1U;
    lpTriangle->wV3    = 2U;
    lpTriangle->wFlags = D3DTRIFLAG_EDGEENABLETRIANGLE;
    lpTriangle++;

    /*
     * Stop execution of the buffer.
     */
    lpInstruction = (LPD3DINSTRUCTION)lpTriangle;
    lpInstruction->bOpcode = D3DOP_EXIT;
    lpInstruction->bSize   = 0UL;
    lpInstruction->wCount  = 0U;

    /*
     * Unlock the execute buffer.
     */
    lpd3dExecuteBuffer->lpVtbl->Unlock(lpd3dExecuteBuffer);

    return DD_OK;
}

/***********************************************************************/

/*
 * Create the elements making up the 3D scene.
 *
 * In this sample the scene consists of the single light, the viewport,
 * the background and surface material, the three transformation matrices
 * and the execute buffer holding the state changes and drawing primitives.
 */
static HRESULT
CreateScene(void)
{
    HRESULT              hRes;
    D3DMATERIAL          d3dMaterial;
    D3DLIGHT             d3dLight;
    DWORD                dwVertexSize;
    DWORD                dwInstructionSize;
    DWORD                dwExecuteBufferSize;
    D3DEXECUTEBUFFERDESC d3dExecuteBufferDesc;
    D3DEXECUTEDATA       d3dExecuteData;

    ASSERT(NULL != lpd3d);
    ASSERT(NULL != lpd3dDevice);
    ASSERT(NULL == lpd3dViewport);
    ASSERT(NULL == lpd3dMaterial);
    ASSERT(NULL == lpd3dBackgroundMaterial);
    ASSERT(NULL == lpd3dExecuteBuffer);
    ASSERT(NULL == lpd3dLight);
    ASSERT(0UL  == hd3dWorldMatrix);
    ASSERT(0UL  == hd3dViewMatrix);
    ASSERT(0UL  == hd3dProjMatrix);

    /*
     * Create the light.
     */
    hRes = lpd3d->lpVtbl->CreateLight(lpd3d, &lpd3dLight, NULL);
    if (FAILED(hRes))
        return hRes;

    ZeroMemory(&d3dLight, sizeof(d3dLight));
    d3dLight.dwSize = sizeof(d3dLight);
    d3dLight.dltType = D3DLIGHT_POINT;
    d3dLight.dcvColor.dvR    = D3DVAL( 1.0);
    d3dLight.dcvColor.dvG    = D3DVAL( 1.0);
    d3dLight.dcvColor.dvB    = D3DVAL( 1.0);
    d3dLight.dcvColor.dvA    = D3DVAL( 1.0);
    d3dLight.dvPosition.dvX  = D3DVAL( 1.0);
    d3dLight.dvPosition.dvY  = D3DVAL(-1.0);
    d3dLight.dvPosition.dvZ  = D3DVAL(-1.0);
    d3dLight.dvAttenuation0  = D3DVAL( 1.0);
    d3dLight.dvAttenuation1  = D3DVAL( 0.1);
    d3dLight.dvAttenuation2  = D3DVAL( 0.0);
    hRes = lpd3dLight->lpVtbl->SetLight(lpd3dLight, &d3dLight);
    if (FAILED(hRes))
        return hRes;

    /*
     * Create the background material.
     */
    hRes = lpd3d->lpVtbl->CreateMaterial(lpd3d, &lpd3dBackgroundMaterial, NULL);
    if (FAILED(hRes))
        return hRes;

    ZeroMemory(&d3dMaterial, sizeof(d3dMaterial));
    d3dMaterial.dwSize = sizeof(d3dMaterial);
    d3dMaterial.dcvDiffuse.r  = D3DVAL(0.0);
    d3dMaterial.dcvDiffuse.g  = D3DVAL(0.0);
    d3dMaterial.dcvDiffuse.b  = D3DVAL(0.0);
    d3dMaterial.dcvAmbient.r  = D3DVAL(0.0);
    d3dMaterial.dcvAmbient.g  = D3DVAL(0.0);
    d3dMaterial.dcvAmbient.b  = D3DVAL(0.0);
    d3dMaterial.dcvSpecular.r = D3DVAL(0.0);
    d3dMaterial.dcvSpecular.g = D3DVAL(0.0);
    d3dMaterial.dcvSpecular.b = D3DVAL(0.0);
    d3dMaterial.dvPower       = D3DVAL(0.0);

    /*
     * As this is the background material we don't want a ramp allocated (we
     * are not going to be smooth shading the background).
     */
    d3dMaterial.dwRampSize    = 1UL;
    
    hRes = lpd3dBackgroundMaterial->lpVtbl->SetMaterial(lpd3dBackgroundMaterial,
                                                        &d3dMaterial);
    if (FAILED(hRes))
        return hRes;
    hRes = lpd3dBackgroundMaterial->lpVtbl->GetHandle(lpd3dBackgroundMaterial,
                                                      lpd3dDevice,
                                                      &hd3dBackgroundMaterial);
    if (FAILED(hRes))
        return hRes;

    /*
     * Create the viewport.
     *
     * The actual viewport parameter are set in the function UpdateViewport
     * which is called in response to WM_SIZE.
     */
    hRes = lpd3d->lpVtbl->CreateViewport(lpd3d, &lpd3dViewport, NULL);
    if (FAILED(hRes))
        return hRes;
    hRes = lpd3dDevice->lpVtbl->AddViewport(lpd3dDevice, lpd3dViewport);
    if (FAILED(hRes))
        return hRes;
    hRes = lpd3dViewport->lpVtbl->SetBackground(lpd3dViewport, hd3dBackgroundMaterial);
    if (FAILED(hRes))
        return hRes;
    hRes = lpd3dViewport->lpVtbl->AddLight(lpd3dViewport, lpd3dLight);
    if (FAILED(hRes))
        return hRes;

    /*
     * Create the matrices.
     */
    hRes = lpd3dDevice->lpVtbl->CreateMatrix(lpd3dDevice, &hd3dWorldMatrix);
    if (FAILED(hRes))
        return hRes;
    hRes = lpd3dDevice->lpVtbl->SetMatrix(lpd3dDevice, hd3dWorldMatrix, &d3dWorldMatrix);
    if (FAILED(hRes))
        return hRes;
    hRes = lpd3dDevice->lpVtbl->CreateMatrix(lpd3dDevice, &hd3dViewMatrix);
    if (FAILED(hRes))
        return hRes;
    hRes = lpd3dDevice->lpVtbl->SetMatrix(lpd3dDevice, hd3dViewMatrix, &d3dViewMatrix);
    if (FAILED(hRes))
        return hRes;
    hRes = lpd3dDevice->lpVtbl->CreateMatrix(lpd3dDevice, &hd3dProjMatrix);
    if (FAILED(hRes))
        return hRes;
    SetPerspectiveProjection(&d3dProjMatrix, HALF_HEIGHT, FRONT_CLIP, BACK_CLIP);
    hRes = lpd3dDevice->lpVtbl->SetMatrix(lpd3dDevice, hd3dProjMatrix, &d3dProjMatrix);
    if (FAILED(hRes))
        return hRes;

    /*
     * Create the surface material.
     */
    hRes = lpd3d->lpVtbl->CreateMaterial(lpd3d, &lpd3dMaterial, NULL);
    if (FAILED(hRes))
        return hRes;
    ZeroMemory(&d3dMaterial, sizeof(d3dMaterial));
    d3dMaterial.dwSize = sizeof(d3dMaterial);

    /*
     * Base green with white specular.
     */
    d3dMaterial.dcvDiffuse.r  = D3DVAL(0.0);
    d3dMaterial.dcvDiffuse.g  = D3DVAL(1.0);
    d3dMaterial.dcvDiffuse.b  = D3DVAL(0.0);
    d3dMaterial.dcvAmbient.r  = D3DVAL(0.0);
    d3dMaterial.dcvAmbient.g  = D3DVAL(0.4);
    d3dMaterial.dcvAmbient.b  = D3DVAL(0.0);
    d3dMaterial.dcvSpecular.r = D3DVAL(1.0);
    d3dMaterial.dcvSpecular.g = D3DVAL(1.0);
    d3dMaterial.dcvSpecular.b = D3DVAL(1.0);
    d3dMaterial.dvPower       = D3DVAL(20.0);
    d3dMaterial.dwRampSize    = 16UL;
    
    hRes = lpd3dMaterial->lpVtbl->SetMaterial(lpd3dMaterial, &d3dMaterial);
    if (FAILED(hRes))
        return hRes;

    hRes = lpd3dMaterial->lpVtbl->GetHandle(lpd3dMaterial, lpd3dDevice, &hd3dSurfaceMaterial);
    if (FAILED(hRes))
        return hRes;

    /*
     * Build the execute buffer.
     */
    dwVertexSize        = (NUM_VERTICES        * sizeof(D3DVERTEX));
    dwInstructionSize   = (NUM_INSTRUCTIONS    * sizeof(D3DINSTRUCTION))     +
                          (NUM_STATES          * sizeof(D3DSTATE))           +
                          (NUM_PROCESSVERTICES * sizeof(D3DPROCESSVERTICES)) +
                          (NUM_TRIANGLES       * sizeof(D3DTRIANGLE));
    dwExecuteBufferSize = dwVertexSize + dwInstructionSize;
    ZeroMemory(&d3dExecuteBufferDesc, sizeof(d3dExecuteBufferDesc));
    d3dExecuteBufferDesc.dwSize       = sizeof(d3dExecuteBufferDesc);
    d3dExecuteBufferDesc.dwFlags      = D3DDEB_BUFSIZE;
    d3dExecuteBufferDesc.dwBufferSize = dwExecuteBufferSize;
    hRes = lpd3dDevice->lpVtbl->CreateExecuteBuffer(lpd3dDevice,
                                                    &d3dExecuteBufferDesc,
                                                    &lpd3dExecuteBuffer,
                                                    NULL);
    if (FAILED(hRes))
        return hRes;

    /*
     * Fill the execute buffer with the required vertices, state
     * instructions and drawing primitives.
     */
    hRes = FillExecuteBuffer();
    if (FAILED(hRes))
        return hRes;

    /*
     * Set the execute data so Direct3D knows how many vertices are in the
     * buffer and where the instructions start.
     */
    ZeroMemory(&d3dExecuteData, sizeof(d3dExecuteData));
    d3dExecuteData.dwSize = sizeof(d3dExecuteData);
    d3dExecuteData.dwVertexCount       = NUM_VERTICES;
    d3dExecuteData.dwInstructionOffset = dwVertexSize;
    d3dExecuteData.dwInstructionLength = dwInstructionSize;
    hRes = lpd3dExecuteBuffer->lpVtbl->SetExecuteData(lpd3dExecuteBuffer, &d3dExecuteData);
    if (FAILED(hRes))
        return hRes;

    return DD_OK;
}

/***********************************************************************/

/*
 * Release all the objects comprising the 3D scene.
 */
static HRESULT
ReleaseScene(void)
{
    if (NULL != lpd3dExecuteBuffer)
    {
        lpd3dExecuteBuffer->lpVtbl->Release(lpd3dExecuteBuffer);
        lpd3dExecuteBuffer = NULL;
    }
    if (NULL != lpd3dBackgroundMaterial)
    {
        lpd3dBackgroundMaterial->lpVtbl->Release(lpd3dBackgroundMaterial);
        lpd3dBackgroundMaterial = NULL;
    }
    if (NULL != lpd3dMaterial)
    {
        lpd3dMaterial->lpVtbl->Release(lpd3dMaterial);
        lpd3dMaterial = NULL;
    }
    if (0UL != hd3dWorldMatrix)
    {
        lpd3dDevice->lpVtbl->DeleteMatrix(lpd3dDevice, hd3dWorldMatrix);
        hd3dWorldMatrix = 0UL;
    }
    if (0UL != hd3dViewMatrix)
    {
        lpd3dDevice->lpVtbl->DeleteMatrix(lpd3dDevice, hd3dViewMatrix);
        hd3dViewMatrix = 0UL;
    }
    if (0UL != hd3dProjMatrix)
    {
        lpd3dDevice->lpVtbl->DeleteMatrix(lpd3dDevice, hd3dProjMatrix);
        hd3dProjMatrix = 0UL;
    }
    if (NULL != lpd3dLight)
    {
        lpd3dLight->lpVtbl->Release(lpd3dLight);
        lpd3dLight = NULL;
    }
    if (NULL != lpd3dViewport)
    {
        lpd3dViewport->lpVtbl->Release(lpd3dViewport);
        lpd3dViewport = NULL;
    }

    return DD_OK;
}

/***********************************************************************/

/*
 * Animate the scene.
 *
 * The animation in this sample is simply a rotation about the Y axis.
 * So all we need to do is build a rotation matrix and set the world
 * matrix to that new rotation matrix.
 *
 * Note, we don't need to modify the execute buffer in any way to peform
 * this rotation. We simply set the matrix and resubmit the execute
 * buffer.
 */
static HRESULT
AnimateScene(void)
{
    HRESULT hRes;

    ASSERT(NULL != lpd3dDevice);
    ASSERT(0UL  != hd3dWorldMatrix);

    /*
     * We rotate the triangle by setting the world transform to a
     * rotation matrix.
     */
    SetRotationAboutY(&d3dWorldMatrix, dAngleOfRotation);
    dAngleOfRotation += ROTATE_ANGLE_DELTA;
    hRes = lpd3dDevice->lpVtbl->SetMatrix(lpd3dDevice,
                                          hd3dWorldMatrix,
                                          &d3dWorldMatrix);
    if (FAILED(hRes))
        return hRes;

    return DD_OK;
}

/***********************************************************************/

/*
 * Update the viewport in response to a change in window size. This
 * ensures that we render at a resolution which matches the client
 * area of the target window.
 */
static HRESULT
UpdateViewport(void)
{
    D3DVIEWPORT d3dViewport;

    ASSERT(NULL != lpd3dViewport);

    ZeroMemory(&d3dViewport, sizeof(d3dViewport));
    d3dViewport.dwSize   = sizeof(d3dViewport);
    d3dViewport.dwX      = 0UL;
    d3dViewport.dwY      = 0UL;
    d3dViewport.dwWidth  = (DWORD)rSrcRect.right;
    d3dViewport.dwHeight = (DWORD)rSrcRect.bottom;
    d3dViewport.dvScaleX = D3DVAL((float)d3dViewport.dwWidth / 2.0);
    d3dViewport.dvScaleY = D3DVAL((float)d3dViewport.dwHeight / 2.0);
    d3dViewport.dvMaxX   = D3DVAL(1.0);
    d3dViewport.dvMaxY   = D3DVAL(1.0);
    return lpd3dViewport->lpVtbl->SetViewport(lpd3dViewport, &d3dViewport);
}

/***********************************************************************/

/*
 * Render the 3D scene.
 *
 * Fundamentally this involved submitting our single execute buffer.
 * However, we also need to clear the back and z-buffers and demark
 * the start and end of the scene (which in this case is a single
 * execute).
 */
static HRESULT
RenderScene(void)
{
    HRESULT hRes;
    D3DRECT d3dRect;

    ASSERT(NULL != lpd3dViewport);
    ASSERT(NULL != lpd3dDevice);
    ASSERT(NULL != lpd3dExecuteBuffer);

    /*
     * Clear both back and z-buffer.
     *
     * NOTE: Its safe to specify the z-buffer clear flag even if we
     * don't have an attached z-buffer. Direct3D will simply discard
     * the flag if no z-buffer is being used.
     *
     * NOTE: For maximum efficiency we only want to clear those
     * regions of the device surface and z-buffer which we actually
     * rendered to in the last frame. This is the purpose of the
     * array of rectangles and count passed to this function. It is
     * possible to query Direct3D for the regions of the device
     * surface that were rendered to by that execute. The application
     * can then accumulate those rectangles and clear only those
     * regions. However this is a very simple sample and so, for
     * simplicity, we will just clear the entire device surface and
     * z-buffer. Probably not something you want to do in a real
     * application.
     */
    d3dRect.lX1 = rSrcRect.left;
    d3dRect.lX2 = rSrcRect.right;
    d3dRect.lY1 = rSrcRect.top;
    d3dRect.lY2 = rSrcRect.bottom;
    hRes = lpd3dViewport->lpVtbl->Clear(lpd3dViewport,
                                        1UL,
                                        &d3dRect,
                                        D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER);
    if (FAILED(hRes))
        return hRes;

    /*
     * Start the scene.
     *
     * This function must be called once and once only for every frame
     * of animation. If you have multiple execute buffers comprising a
     * single frame you must have one call to BeginScene() before
     * submitting those execute buffers.
     *
     * NOTE: If you have more than one device being rendered in a
     * single frame, say a rear view mirror in a racing game, call
     * BeginScene() and EndScene() once for each device.
     */
    hRes = lpd3dDevice->lpVtbl->BeginScene(lpd3dDevice);
    if (FAILED(hRes))
        return hRes;

    /*
     * Submit the execute buffer.
     *
     * We want Direct3D to clip the data on our behalf so we specify
     * D3DEXECUTE_CLIPPED.
     */
    hRes = lpd3dDevice->lpVtbl->Execute(lpd3dDevice,
                                        lpd3dExecuteBuffer,
                                        lpd3dViewport,
                                        D3DEXECUTE_CLIPPED);
    if (FAILED(hRes))
    {
        lpd3dDevice->lpVtbl->EndScene(lpd3dDevice);
        return hRes;
    }

    /*
     * End the scene.
     */
    hRes = lpd3dDevice->lpVtbl->EndScene(lpd3dDevice);
    if (FAILED(hRes))
        return hRes;

    /*
     * At this point the scene will have been rendered and the device
     * surface will hold the contents of the rendering.
     */

    return DD_OK;
}

/***********************************************************************/

/*
 * Render and show a single frame.
 *
 * This involves rendering the scene and blitting the result to client
 * area of the application window on the primary surface.
 *
 * NOTE: This function handles lost surfaces by attempting to restore
 * the applications surfaces and then retrying the rendering.
 */
static HRESULT
DoFrame(HWND hwnd)
{
    HRESULT hRes;

    /*
     * We keeping trying until we succeed or we fail for a reason
     * other than DDERR_SURFACELOST.
     */
    while (TRUE)
    {
        hRes = RenderScene();
        if (SUCCEEDED(hRes))
        {
	    POINT pt;
	    RECT rTmp;

	    pt.x = pt.y = 0;
	    ClientToScreen( hwnd, &pt );

	    rTmp = rDstRect;

	    // For multi-monitor systems, we need to translate
	    // the Desktop coordinates into Device coordinates.
	    pt.x -= rectMonitor.left;
	    pt.y -= rectMonitor.top;
	    OffsetRect(&rTmp, pt.x, pt.y);

            hRes = lpddPrimary->lpVtbl->Blt(lpddPrimary,
                                            &rTmp,
                                            lpddDevice,
                                            &rSrcRect,
                                            DDBLT_WAIT,
                                            NULL);
            if (SUCCEEDED(hRes))
                /*
                 * It worked. Bail.
                 */
                return hRes;
        }
        while (DDERR_SURFACELOST == hRes)
            /*
             * The surfaces are lost. Restore them.
             */
            hRes = RestoreSurfaces();
        if (FAILED(hRes))
            /*
             * Something went wrong and it wasn't DDERR_SURFACELOST.
             */
            return hRes;
    }
}

/***********************************************************************/

/*
 * The application suspends when in the background or when handling and
 * error. We signal this fact by drawing a notification string in the
 * client area of the window.
 */
static void
PaintSuspended(HWND hwnd, HDC hdc)
{
    HPEN     hOldPen;
    HBRUSH   hOldBrush;
    COLORREF crOldTextColor;
    int      oldMode;
    int      x;
    int      y;
    SIZE     size;
    RECT     rect;
    int      nStrLen;

    /*
     * Black background.
     */
    hOldPen   = SelectObject(hdc, GetStockObject(NULL_PEN));
    hOldBrush = SelectObject(hdc, GetStockObject(BLACK_BRUSH));

    /*
     * White text.
     */
    oldMode = SetBkMode(hdc, TRANSPARENT);
    crOldTextColor = SetTextColor(hdc, RGB(255, 255, 255));

    GetClientRect(hwnd, &rect);

    /*
     * Clear the client area.
     */
    Rectangle(hdc, rect.left, rect.top, rect.right + 1, rect.bottom + 1);

    /*
     * Draw the string centered in the client area.
     */
    nStrLen = strlen(PAUSED_STRING);
    GetTextExtentPoint32(hdc, PAUSED_STRING, nStrLen, &size);
    x = (rect.right  - size.cx) / 2;
    y = (rect.bottom - size.cy) / 2;
    TextOut(hdc, x, y, PAUSED_STRING, nStrLen);

    SetTextColor(hdc, crOldTextColor);
    SetBkMode(hdc, oldMode);

    SelectObject(hdc, hOldBrush);
    SelectObject(hdc, hOldPen);
}

/***********************************************************************/

static LRESULT
OnMove(HWND hwnd, int x, int y)
{
    HRESULT hRes;

    hRes = CheckMonitors(hwnd, FALSE);
    if (FAILED(hRes))
    {
	return 0L;
    }

    /*
     * No action if the device has not yet been created or if we are
     * suspended.
     */
    if ((NULL != lpd3dDevice) && !fSuspended)
    {
        /*
         * Repaint the client area.
         */
        hRes = DoFrame(hwnd);
        if (FAILED(hRes))
        {
            FatalError(hwnd, IDS_ERRMSG_RENDERSCENE, hRes);
            return 0L;
        }
    }

    return 0L;
}

/***********************************************************************/
#define FORCE_RESET TRUE

static HRESULT
CheckMonitors(HWND hwnd, BOOL fReset)
{   
    HRESULT     hRes;
    char        szBuffer[128];

    if (!fReset && hMonitor == DirectDrawDeviceFromWindow(hwnd, NULL, NULL))
	return S_OK;

    // If we do, then first release what we have so far
    ReleaseScene();
    ReleaseDevice();
    ReleasePrimary();
    ReleaseDirect3D();

    // Update our monitor information
    hMonitor = DirectDrawDeviceFromWindow(hwnd, szMonitor, &rectMonitor);

    // Now start from scratch
    hRes = CreateDirect3D(hwnd);
    if (FAILED(hRes))
    {
        ReportError(hwnd, IDS_ERRMSG_CREATEDEVICE, hRes);
        ReleaseDirect3D();
        return -1L;
    }

    hRes = CreatePrimary(hwnd);
    if (FAILED(hRes))
    {
        ReportError(hwnd, IDS_ERRMSG_INITSCREEN, hRes);
        ReleasePrimary();
        ReleaseDirect3D();
        return -1L;
    }

    hRes = ChooseDevice();
    if (FAILED(hRes))
    {
        ReportError(hwnd, IDS_ERRMSG_NODEVICE, hRes);
        ReleasePrimary();
        ReleaseDirect3D();
        return -1L;
    }

    hRes = CreateDevice((DWORD)rSrcRect.right, (DWORD)rSrcRect.bottom);
    if (FAILED(hRes))
    {
        FatalError(hwnd, IDS_ERRMSG_CREATEDEVICE, hRes);
	ReleaseDevice();
        ReleasePrimary();
        ReleaseDirect3D();
        return 0L;
    }
    hRes = CreateScene();
    if (FAILED(hRes))
    {
        FatalError(hwnd, IDS_ERRMSG_BUILDSCENE, hRes);
	ReleaseDevice();
        ReleasePrimary();
        ReleaseDirect3D();
        return 0L;
    }

    hRes = UpdateViewport();
    if (FAILED(hRes))
    {
        FatalError(hwnd, IDS_ERRMSG_UPDATEVIEWPORT, hRes);
	ReleaseScene();
	ReleaseDevice();
        ReleasePrimary();
        ReleaseDirect3D();
        return 0L;
    }


    /*
     * Update the title to show the name of the chosen device.
     */
    wsprintf(szBuffer, "%s: %s", WINDOW_TITLE, szDeviceName);
    SetWindowText(hwnd, szBuffer);

    return 0L;
}

/***********************************************************************/

/***********************************************************************/

static LRESULT
OnSize(HWND hwnd, int w, int h)
{
    HRESULT       hRes;
    DDSURFACEDESC ddsd;

    // Check if we need to update our monitor information
    // This can happen if our window is being sized onto
    // another monitor.
    hRes = CheckMonitors(hwnd, FALSE);
    if (FAILED(hRes))
    {
	return 0L;
    }


    /*
     * Nothing to do if we are suspended.
     */
    if (!fSuspended)
    {
        /*
         * Update the source and destination rectangles (used by the
         * blit which shows the rendering in the client area).
         */
        rDstRect.right  = rDstRect.left + w;
        rDstRect.bottom = rDstRect.top  + h;

	// If the window is sized to something larger than our initial size
	// then just use DDraw stretch. If it is something smaller
	// then reduce the complexity for Direct3D since the stretch
	// will just drop pixels anyhow.
        rSrcRect.right  = min(w, WINDOW_WIDTH);
        rSrcRect.bottom = min(h, WINDOW_HEIGHT);

        if (NULL != lpd3dDevice)
        {
            /*
             * We already have a device. But is it big enough for the the
             * new window client size?
             *
             * NOTE: As this window is fixed size we should not ever be
             * end up being resized. But just in case we will handle it.
             * This will be useful when we make the application resizable.
             */
            ZeroMemory(&ddsd, sizeof(ddsd));
            ddsd.dwSize = sizeof(ddsd);
            hRes = lpddDevice->lpVtbl->GetSurfaceDesc(lpddDevice, &ddsd);
            if (FAILED(hRes))
            {
                FatalError(hwnd, IDS_ERRMSG_DEVICESIZE, hRes);
                return 0L;
            }
    
            if ((w > (int)ddsd.dwWidth) || (h > (int)ddsd.dwHeight))
            {
                /*
                 * Nope, the device is too small. We need to shut it down
                 * and rebuild it.
                 */

                /*
                 * Execute buffers are bound to devices so when we release
                 * the device we must release the execute buffer.
                 */
                ReleaseScene();
                ReleaseDevice();
            }
        }

        if (NULL == lpd3dDevice)
        {
            /*
             * No Direct3D device yet. This is either because this is the
             * first time through the loop or because we discarded the
             * existing device because it was not big enough for the new
             * window client size.
             */
            hRes = CreateDevice((DWORD)w, (DWORD)h);
            if (FAILED(hRes))
            {
                FatalError(hwnd, IDS_ERRMSG_CREATEDEVICE, hRes);
                return 0L;
            }
            hRes = CreateScene();
            if (FAILED(hRes))
            {
                FatalError(hwnd, IDS_ERRMSG_BUILDSCENE, hRes);
                return 0L;
            }
        }

        hRes = UpdateViewport();
        if (FAILED(hRes))
        {
            FatalError(hwnd, IDS_ERRMSG_UPDATEVIEWPORT, hRes);
            return 0L;
        }

        /*
         * Render at the new size and show the results in the window's
         * client area.
         */
        hRes = DoFrame(hwnd);
        if (FAILED(hRes))
        {
            FatalError(hwnd, IDS_ERRMSG_RENDERSCENE, hRes);
            return 0L;
        }
    }

    return 0L;
}

/***********************************************************************/

static LRESULT
OnPaint(HWND hwnd, HDC hdc, LPPAINTSTRUCT lpps)
{
    HRESULT hRes;

    USE_PARAM(lpps);

    if (!fSuspended && (NULL != lpd3dDevice))
    {
        /*
         * NOTE: DoFrame() re-renders the scene as well as blitting the
         * result to the primary. As all we really want to do here is
         * repaint the client area we don't really need to re-render -
         * just re-blit. For this simple sample this inefficiency
         * doesn't matter but for real applications not re-rendering
         * may be a useful optimization.
         */
        hRes = DoFrame(hwnd);
        if (FAILED(hRes))
        {
            FatalError(hwnd, IDS_ERRMSG_RENDERSCENE, hRes);
            return 0L;
        }
    }
    else
    {
        /*
         * Show the suspended image if we are not active, or suspended or
         * if we have not yet created the device.
         */
        PaintSuspended(hwnd, hdc);
    }

    return 0L;
}

/***********************************************************************/

static LRESULT
OnIdle(HWND hwnd)
{
    HRESULT hRes;

    /*
     * Only animate if we aren't suspended
     * and we have completed initialization.
     */
    if ( !fSuspended && (NULL != lpd3dDevice))
    {
        hRes = AnimateScene();
        if (FAILED(hRes))
        {
            FatalError(hwnd, IDS_ERRMSG_ANIMATESCENE, hRes);
            return 0L;
        }

        hRes = DoFrame(hwnd);
        if (FAILED(hRes))
        {
            FatalError(hwnd, IDS_ERRMSG_RENDERSCENE, hRes);
            return 0L;
        }
    }

    return 0L;
}

/***********************************************************************/

LRESULT CALLBACK
WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    HDC         hdc;
    PAINTSTRUCT ps;
    LRESULT     lResult;
    HRESULT     hRes;

    switch (msg)
    {
        case WM_CREATE:

	    hRes = CheckMonitors(hwnd, FORCE_RESET);
	    if (FAILED(hRes))
		return -1;

            return 0L;

        case WM_MOVE:
            return OnMove(hwnd, (int)(signed short)LOWORD(lParam), (int)(signed short)HIWORD(lParam));

        case WM_SIZE:
            return OnSize(hwnd, (int)LOWORD(lParam), (int)HIWORD(lParam));

        case WM_ERASEBKGND:
            /*
             * Our rendering fills the entire viewport so we won't bother
             * erasing the background.
             */
            return 1L;

        case WM_PAINT:
            hdc = BeginPaint(hwnd, &ps);

            lResult = OnPaint(hwnd, hdc, &ps);

            EndPaint(hwnd, &ps);
            return lResult;

        case WM_ACTIVATEAPP:
            fActive = (BOOL)wParam;
            if (fActive && !fSuspended && (NULL != lpddPalette))
            {
                /*
                 * Realizing the palette using DirectDraw is quite different
                 * from GDI. To realize the palette we call SetPalette()
                 * each time our application is activated.
                 *
                 * NOTE: DirectDraw spots the fact that the new palette is the
                 * same as the old one and so does not increase the reference
                 * count of the palette.
                 */
                hRes = lpddPrimary->lpVtbl->SetPalette(lpddPrimary, lpddPalette);
                if (FAILED(hRes))
                {
                    FatalError(hwnd, IDS_ERRMSG_REALIZEPALETTE, hRes);
                    return 0L;
                }

            }
            else
            {
                /*
                 * If we have been deactived invalidate to show the suspended
                 * display.
                 */
                InvalidateRect(hwnd, NULL, FALSE);
            }
            return 0L;

        case WM_KEYUP:
            /*
             * We use the escape key as a quick way of getting out of the
             * application.
             */
            if (VK_ESCAPE == (int)wParam)
            {
                DestroyWindow(hwnd);
                return 0L;
            }
            break;

        case WM_CLOSE:
            DestroyWindow(hwnd);
            return 0L;

        case WM_DESTROY:
            /*
             * All cleanup is done here when terminating normally or
             * shutting down due to an error.
             */
            ReleaseScene();
            ReleaseDevice();
            ReleasePrimary();
            ReleaseDirect3D();

            PostQuitMessage(0);
            return 0L;
    }

    return DefWindowProc(hwnd, msg, wParam, lParam);
}
                        
/***********************************************************************/

int PASCAL
WinMain(HINSTANCE hInstance,
        HINSTANCE hPrevInstance,
        LPSTR     lpszCommandLine,
        int       cmdShow)
{
    WNDCLASS wndClass;
    HWND     hwnd;
    MSG      msg;

    USE_PARAM(hPrevInstance);

    /*
     * Record the instance handle.
     */
    hAppInstance = hInstance;

    /*
     * Very, very primitive command line processing. We only have one
     * option, debug so we will just assume that if anything was
     * specified on the command line that means debug mode (no hardware
     * all surfaces explicitly in system memory).
     */
    if (0 != *lpszCommandLine)
        fDebug = TRUE;

    /*
     * Register the window class.
     */
    wndClass.style         = 0;
    wndClass.lpfnWndProc   = WndProc;
    wndClass.cbClsExtra    = 0;
    wndClass.cbWndExtra    = 0;
    wndClass.hInstance     = hInstance;
    wndClass.hIcon         = LoadIcon(hAppInstance, MAKEINTRESOURCE(IDI_APPICON));
    wndClass.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wndClass.hbrBackground = GetStockObject(WHITE_BRUSH);
    wndClass.lpszMenuName  = NULL;
    wndClass.lpszClassName = WINDOW_CLASSNAME;

    RegisterClass(&wndClass);

    /*
     * Create the main window of the instance.
     */
    hwnd = CreateWindow(WINDOW_CLASSNAME,
                        WINDOW_TITLE,
                        WS_OVERLAPPED | WS_SYSMENU | WS_SIZEBOX,
                        CW_USEDEFAULT, CW_USEDEFAULT,
                        WINDOW_WIDTH, WINDOW_HEIGHT,
                        NULL,
                        NULL,
                        hInstance,
                        NULL);

    ShowWindow(hwnd, cmdShow);
    UpdateWindow(hwnd);

    /*
     * The main message dispatch loop.
     *
     * NOTE: For simplicity we handle the message loop with a
     * simple PeekMessage scheme. This might not be the best
     * mechanism for a real application (a separate render worker
     * thread might be better). 
     */
    while (TRUE)
    {
        if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
        {
            /*
             * Message pending. If its QUIT then exit the message
             * loop. Otherwise, process the message.
             */
            if (WM_QUIT == msg.message)
            {
                break;
            }
            else
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else
        {
            /*
             * Animate the scene.
             */
            OnIdle(hwnd);
        }
    }

    return msg.wParam;
}

/***********************************************************************/

/***********************************************************************
 *
 * End of file
 *
 ***********************************************************************/
