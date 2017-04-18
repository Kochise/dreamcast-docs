#include "precomp.hxx"


LRESULT CALLBACK APPWndProc(HWND, UINT, WPARAM, LPARAM);

BOOL APPCreate(void);
void APPDestroy(void);

BOOL DDInit(HINSTANCE hInstance, HWND hwnd);
void DDDone(void);

void APPBlt(LPDIRECTDRAWSURFACE);

HINSTANCE               g_hInstance;
RECT                    g_rcDesktop;
HWND                    g_hwndAPP = NULL;
HFONT                   g_hfontDefault = NULL;

LPDIRECTDRAW            g_lpdd         = NULL;
LPDIRECTDRAWSURFACE     g_lpddsPrimary = NULL;
LPDIRECTDRAWSURFACE     g_lpddsBack    = NULL;
LPDIRECTDRAWSURFACE     g_lpddsTexture = NULL;

LPDIRECTINPUTDEVICE2    g_pdidevice2JoystickApp;


/********************************************************************

Function:

    WinMain

Description:

    The windows main entry point.

Return Value:
    
    int.

********************************************************************/

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInst,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
    MSG     msg;
    DDBLTFX ddbltfx;
	HKEY	hkey;
    
    g_hInstance = hInstance;

	if (ERROR_SUCCESS != RegOpenKeyEx (HKEY_LOCAL_MACHINE, 
        TEXT("System\\CurrentControlSet\\Control\\Layouts\\e0010404"), 0, 0, &hkey)) {

        OutputDebugString(TEXT("TCIME: ERROR: Traditional Chinese IME not enabled.\r\n\r\n"));
        OutputDebugString(TEXT("TCIME: To fix this, use the Configuration Tool to turn on the \"Traditional\r\n"));
        OutputDebugString(TEXT("TCIME: Chinese IME\" and \"MS Ming font\", and then rebuild the image.  \r\n\r\n"));
        OutputDebugString(TEXT("TCIME: Alternatively, from the WinCE command window, type \"set IMGTCIME=1\" \r\n"));
        OutputDebugString(TEXT("TCIME: and \"set COUNTRY=CHT\", then run \"makeimg\".\r\n"));
        return 0;
    } else {
        RegCloseKey (hkey);
    }

    if (GetACP() != DEFAULT_CODEPAGE) {
        OutputDebugString(TEXT("TCIME: ERROR: Default codepage is not Traditional Chinese codepage.\r\n\r\n"));
        OutputDebugString(TEXT("TCIME: To fix this, use the Configuration Tool to turn on the \"Traditional\r\n"));
        OutputDebugString(TEXT("TCIME: Chinese IME\" and \"MS Ming font\", and then rebuild the image.  \r\n\r\n"));
        OutputDebugString(TEXT("TCIME: Alternatively, from the WinCE command window, type \"set IMGTCIME=1\" \r\n"));
        OutputDebugString(TEXT("TCIME: and \"set COUNTRY=CHT\", then run \"makeimg\".\r\n"));
        return 0;
    }

    if (!AddFontResource(FONT_FILENAME)) {
        OutputDebugString(TEXT("TCIME: ERROR: Add font resource for 'msming.ttf' failed.\r\n\r\n"));
        OutputDebugString(TEXT("TCIME: To fix this, use the Configuration Tool to turn on the \"Traditional\r\n"));
        OutputDebugString(TEXT("TCIME: Chinese IME\" and \"MS Ming font\", and then rebuild the image.  \r\n\r\n"));
        OutputDebugString(TEXT("TCIME: Alternatively, from the WinCE command window, type \"set IMGTCIME=1\" \r\n"));
        OutputDebugString(TEXT("TCIME: and \"set COUNTRY=CHT\", then run \"makeimg\".\r\n"));
        return 0;
    }

    if (g_hfontDefault == NULL) {
        g_hfontDefault = CreateChineseFont(DEFAULT_FONTSIZE);
    }
    if (!g_hfontDefault) {
        RemoveFontResource(FONT_FILENAME);
        OutputDebugString(TEXT("TCIME: ERROR: Create default font failed.\r\n\r\n"));
        OutputDebugString(TEXT("TCIME: To fix this, use the Configuration Tool to turn on the \"Traditional\r\n"));
        OutputDebugString(TEXT("TCIME: Chinese IME\" and \"MS Ming font\", and then rebuild the image.  \r\n\r\n"));
        OutputDebugString(TEXT("TCIME: Alternatively, from the WinCE command window, type \"set IMGTCIME=1\" \r\n"));
        OutputDebugString(TEXT("TCIME: and \"set COUNTRY=CHT\", then run \"makeimg\".\r\n"));
        return 0;
    }

    g_rcDesktop.left = g_rcDesktop.top = 0;
    g_rcDesktop.right = GetSystemMetrics(SM_CXSCREEN);
    g_rcDesktop.bottom = GetSystemMetrics(SM_CYSCREEN);

    if (!APPCreate()) { return 0; }
    
    if (!DDInit(g_hInstance, g_hwndAPP)) {
        if (g_hwndAPP) {
            DestroyWindow(g_hwndAPP);
        }
        return 0;
    }

    EditBoxCreate();
    SKBCreate(PHONETIC);
    IndicatorCreate();
    RWNDCreate();
    CWNDCreate();

    SetFocus(g_hwndEditBox);

    // the background will be a white screen
    memset (&ddbltfx, 0, sizeof(ddbltfx));
    ddbltfx.dwSize = sizeof(ddbltfx);
    ddbltfx.dwFillColor = LIGHTGRAY;

    while (TRUE) {
        if (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE)) {
            if (!GetMessage(&msg, NULL, 0, 0)) {
                break;
            }

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        } else {
            CheckForHardwareKeyboard();

            SKBUpdate();
            CWNDUpdate();

            // clear the screen
            g_lpddsBack->Blt(&g_rcDesktop, NULL, NULL, DDBLT_COLORFILL|DDBLT_WAIT, &ddbltfx);

            EditBoxBlt(g_lpddsBack);
            IndicatorBlt(g_lpddsBack);
            SKBBlt(g_lpddsBack);
            RWNDBlt(g_lpddsBack);
            CWNDBlt(g_lpddsBack);
            CaretBlt(g_lpddsBack);

            g_lpddsPrimary->Flip(NULL, DDFLIP_WAIT);
        }
    }

    // clear the screen
    ddbltfx.dwFillColor = BLACK;
    g_lpddsBack->Blt(&g_rcDesktop, NULL, NULL, DDBLT_COLORFILL|DDBLT_WAIT, &ddbltfx);
    g_lpddsPrimary->Blt(&g_rcDesktop, NULL, NULL, DDBLT_COLORFILL|DDBLT_WAIT, &ddbltfx);
    g_lpddsPrimary->Flip(NULL, DDFLIP_WAIT);

    SKBDestroy();
    IndicatorDestroy();
    CWNDDestroy();
    RWNDDestroy();
    EditBoxDestroy();

    DDDone();

    APPDestroy();

    if (g_hfontDefault) {
        DeleteObject(g_hfontDefault);
        g_hfontDefault = NULL;
    }

    RemoveFontResource(FONT_FILENAME);

    return msg.wParam;
}


/********************************************************************

Function:

    APPCreate
    APPDestroy

Description:

    The windows procedure body.

********************************************************************/
BOOL APPCreate(void)
{
    WNDCLASS wc;
    
    wc.style         = 0;;
    wc.lpfnWndProc   = (WNDPROC)DefWindowProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = g_hInstance;
    wc.hIcon         = NULL;
    wc.hCursor       = NULL;
    wc.hbrBackground = NULL;
    wc.lpszMenuName  = NULL;
    wc.lpszClassName = TEXT("TCImeSamp");
    
    if (!RegisterClass(&wc)) {
        return FALSE;
    }

    g_hwndAPP = CreateWindowEx(0,
                               TEXT("TCImeSamp"),
                               TEXT("TCImeSamp"),
                               0,
                               0,
                               0,
                               GetSystemMetrics(SM_CXSCREEN),
                               GetSystemMetrics(SM_CYSCREEN),
                               NULL,
                               NULL,
                               g_hInstance,
                               NULL);

    if (!g_hwndAPP) {
        return FALSE;
    }

    return TRUE;
}


void APPDestroy(void)
{
    if (g_hwndAPP) {
        DestroyWindow(g_hwndAPP);
        g_hwndAPP = NULL;
    }

    return;
}


/********************************************************************

Functions:

    DDInit
    DDDone

********************************************************************/

BOOL DDInit(HINSTANCE hInstance,
            HWND      hwnd)
{
    DDSURFACEDESC ddsd;
    DDSCAPS       ddscaps;
    HRESULT       ddrval;
    
    ddrval = DirectDrawCreate(NULL, &g_lpdd, NULL);
    if (ddrval != DD_OK) {
        OutputDebugString (TEXT("DirectDrawCreate failed.\r\n"));
        return FALSE;
    }
    
    ddrval = g_lpdd->SetCooperativeLevel(hwnd, DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN);
    if (ddrval != DD_OK) {
        OutputDebugString (TEXT("SetCooperativeLevel failed.\r\n"));
        return FALSE;
    }

    ddrval = g_lpdd->SetDisplayMode(g_rcDesktop.right, g_rcDesktop.bottom, 16);
    if (ddrval != DD_OK) {
        OutputDebugString (TEXT("SetDisplayMode failed.\r\n"));
        return FALSE;
    }
        
    ddsd.dwSize = sizeof(ddsd);
    ddsd.dwFlags = DDSD_CAPS | DDSD_BACKBUFFERCOUNT;
    ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE | DDSCAPS_FLIP | DDSCAPS_COMPLEX;
    ddsd.dwBackBufferCount = 1;
    ddrval = g_lpdd->CreateSurface(&ddsd, &g_lpddsPrimary, NULL);
    if (ddrval != DD_OK) {
        OutputDebugString (TEXT("Create primary surface failed.\r\n"));
        return FALSE;
    }

    ddscaps.dwCaps = DDSCAPS_BACKBUFFER;
    ddrval = g_lpddsPrimary->GetAttachedSurface(&ddscaps, &g_lpddsBack);
    if (ddrval != DD_OK) {
        OutputDebugString (TEXT("GetAttachedSurface failed.\r\n"));
        return FALSE;
    }

    // For desktop DirectDraw surface.
	memset(&ddsd,0,sizeof(ddsd));
	ddsd.dwSize=sizeof(ddsd);
	ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;
	ddsd.ddsCaps.dwCaps = DDSCAPS_VIDEOMEMORY | DDSCAPS_TEXTURE;
	ddsd.dwWidth = 640;
	ddsd.dwHeight = 480; 
	ddrval = g_lpdd->CreateSurface( &ddsd, &g_lpddsTexture, NULL );
    if (ddrval != DD_OK) {
        OutputDebugString (TEXT("Create Desktop surface failed.\r\n"));
        if (g_lpddsPrimary) {
            g_lpddsPrimary->Release();
            g_lpddsPrimary = NULL;
        }
        return FALSE;
    }

    CreateDirectInput (hInstance, hwnd, &g_pdidevice2JoystickApp);

    return TRUE;
}

void DDDone(void)
{
    if (!g_lpdd)
        return;
          
    if (g_lpddsPrimary) {
        g_lpddsPrimary->Release();
        g_lpddsPrimary = NULL;
    }

    if (g_lpddsTexture) {
        g_lpddsTexture->Release();
        g_lpddsTexture = NULL;
    }

    g_lpdd->Release();
    g_lpdd = NULL;
    DestroyDirectInput();

    return;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    CreateChineseFont
    
Description:

    Creates the Chinese font.

Return Value:

    The font is created.

-------------------------------------------------------------------*/
HFONT CreateChineseFont(LONG lFontHeight)
{
    LOGFONT lf;

    memset (&lf, 0, sizeof(lf));
    lf.lfHeight = lFontHeight;
    lf.lfCharSet = CHINESEBIG5_CHARSET;
    lf.lfOutPrecision = OUT_DEFAULT_PRECIS;
    lf.lfClipPrecision = CLIP_DEFAULT_PRECIS;
    lf.lfQuality = DEFAULT_QUALITY;
    lf.lfPitchAndFamily = DEFAULT_PITCH | FF_DONTCARE;
    _tcscpy(lf.lfFaceName, FONT_FACENAME);

    return CreateFontIndirect(&lf);
} // CreateChineseFont

