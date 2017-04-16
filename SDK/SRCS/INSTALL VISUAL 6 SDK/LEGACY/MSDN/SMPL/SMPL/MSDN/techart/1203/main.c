/*
    main.c

    A sample Windows application

    Another fine Herman Rodent production

*/

#include "global.h"

//
// local data
//

static BOOL bCaptured = FALSE;
static PSPRITE pCapturedSprite = NULL;
static int iDX, iDY;
static PSPRITE pSelectedSprite = NULL;

//
// local functions
//

static void Create(HWND hWnd, LPCREATESTRUCT lpCI);
static void Size(HWND hWnd, UINT uiX, UINT uiY);
static void Command(HWND hWnd, WPARAM wParam, LPARAM lParam);
static void MeasureItem(HWND hWnd, UINT uiCtl, LPMEASUREITEMSTRUCT lpMI);
static void DrawItem(HWND hWnd, UINT uiCtl, LPDRAWITEMSTRUCT lpDI);
static void InitMenuPopup(HMENU hMenu, UINT uiIndex, BOOL bSystem);

//
// Entry point
//

int PASCAL WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpszCmdLine,
                   int cmdShow)
{
    MSG msg;

    hAppInstance = hInstance;
    szAppName = "Sprites";

#ifdef DEBUG

    //
    // Get the debug level
    //

    __iDebugLevel = GetProfileInt(szAppName, "debug", 1);

#endif // DEBUG

    //
    // We allow multiple instances
    //

    if (!hPrevInstance) {
        if (!InitFirstInstance(hInstance)) {
            return 1;
        }
    }

    //
    // Do the per instance initialization
    //

    if (!InitCurrentInstance(hInstance, lpszCmdLine, cmdShow)) {
        return 1;
    }

    //
    // Check for messages from Windows and process them.
    // If we have nothing else to do, maybe perform some idle function
    // 

    do {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {

            //
            // got a message to process
            //

            if (msg.message == WM_QUIT) break;

            //
            // Do the accelerator thing
            //

            if (!TranslateAccelerator(hwndMain, hAccTable, &msg)) {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }

        } else {

            //
            // perform some idle routine or just give up so Windows
            // can run till our next message.
            //

#ifdef WAIT_LOOP
            if (bAutoUpdate && !bCaptured) {
                UpdatePositions();
            } else {
                WaitMessage();
            }
#else
            WaitMessage();
#endif
        }
    } while (1);

    return (msg.wParam);
}
    
//
// main window message handler
//

LRESULT CALLBACK MainWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;

    switch(msg) {
    case WM_CREATE:
        Create(hWnd, (LPCREATESTRUCT)lParam);
        break;

    case WM_SIZE:
        Size(hWnd, LOWORD(lParam), HIWORD(lParam));
        break;

#ifdef TIMER_TICKS
    case WM_TIMER:
        if (bAutoUpdate && !bCaptured) UpdatePositions();
        break;
#endif

    case WM_LBUTTONDOWN:

        dprintf3("Mouse down at %u,%u", LOWORD(lParam), HIWORD(lParam));
        if (!bCaptured) {

            //
            // See if it hit a sprite
            //

            pCapturedSprite = SpriteHitTest(LOWORD(lParam), HIWORD(lParam));

            if (pCapturedSprite && IsSpriteSelectable(pCapturedSprite)) {

                bCaptured = TRUE;
                SetCapture(hWnd);
                dprintf2("Sprite hit");
                iDX = LOWORD(lParam) - pCapturedSprite->x;
                iDY = HIWORD(lParam) - pCapturedSprite->y;
                dprintf3(" Sprite is at %u,%u,%u (%ux%u)", 
                         pCapturedSprite->x, 
                         pCapturedSprite->y, 
                         pCapturedSprite->z, 
                         pCapturedSprite->width,
                         pCapturedSprite->height);
            }
        }
        break;

    case WM_MOUSEMOVE:

        if (bCaptured) {

            SetSpritePosition(pCapturedSprite, 
                              LOWORD(lParam)-iDX, 
                              HIWORD(lParam)-iDY,
                              UPDATE_SCREEN);

        }
        break;

    case WM_LBUTTONUP:

        dprintf3("Mouse up at %u,%u", LOWORD(lParam), HIWORD(lParam));
        if (bCaptured) {

            ReleaseCapture();
            bCaptured = FALSE;
            pCapturedSprite = NULL;
            dprintf2("Sprite released");
        }
        break;

    case WM_LBUTTONDBLCLK:

        pSelectedSprite = SpriteHitTest(LOWORD(lParam), HIWORD(lParam));
        if (pSelectedSprite) {
            SpriteDialog(pSelectedSprite);
        } else {
            MessageBeep(NULL);
        }
        break;


    case WM_COMMAND:
        Command(hWnd, wParam, lParam); 
        break;

    case WM_MEASUREITEM:
        MeasureItem(hWnd, (UINT)wParam, (LPMEASUREITEMSTRUCT)lParam);
        return (LRESULT) TRUE;

    case WM_DRAWITEM:
        DrawItem(hWnd, (UINT)wParam, (LPDRAWITEMSTRUCT) lParam);
        break;

    case WM_PAINT:
        BeginPaint(hWnd, &ps);
        Paint(ps.hdc, &(ps.rcPaint));
        EndPaint(hWnd, &ps);
        break;

    case WM_QUERYNEWPALETTE:
    case WM_PALETTECHANGED:
        return PaletteMessage(hWnd, msg, wParam, lParam);
        break;

    case WM_INITMENUPOPUP:
        InitMenuPopup((HMENU)wParam, LOWORD(lParam), (BOOL)HIWORD(lParam));
        break;

    case WM_DESTROY:
        Terminate();
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hWnd, msg, wParam, lParam);
        break;
    }
    return NULL;
}

//
// Process WM_CREATE message
//

static void Create(HWND hWnd, LPCREATESTRUCT lpCI)
{

}

//
// Process WM_SIZE message
//

static void Size(HWND hWnd, UINT uiX, UINT uiY)
{

}

//
// Process WM_COMMAND messages
//

static void Command(HWND hWnd, WPARAM wParam, LPARAM lParam) 
{
    PRINTDLG pd;

    switch (wParam) {
    case IDM_LOADSCENE:
        LoadScene(NULL);
        break;

    case IDM_LOADBKGND:
        LoadBackground(NULL, UPDATE_SCREEN);
        break;

    case IDM_LOADSPRITE:
        LoadSprite(NULL, UPDATE_SCREEN);
        break;

    case IDM_PRINT:
        memset(&pd, 0, sizeof(pd));
        pd.lStructSize = sizeof(pd);
        pd.hwndOwner = hWnd;
        pd.Flags = PD_RETURNDC;
        if (PrintDlg(&pd)) {
            Print(pd.hDC);
        }
        DeleteDC(pd.hDC);
        if (pd.hDevMode) GlobalFree(pd.hDevMode);
        if (pd.hDevNames) GlobalFree(pd.hDevNames);
        break;

    case IDM_PRINTSETUP:
        memset(&pd, 0, sizeof(pd));
        pd.lStructSize = sizeof(pd);
        pd.hwndOwner = hWnd;
        pd.Flags = PD_PRINTSETUP;
        PrintDlg(&pd);
        break;

    case IDM_REFRESH:
        InvalidateRect(hwndMain, NULL, FALSE);
        break;

    case IDM_REDRAW:
        Redraw(NULL, UPDATE_SCREEN);
        break;

    case IDM_SHOWUPDATES:
        bShowUpdateRects = !bShowUpdateRects;
        break;

    case IDM_AUTOUPDATE:
        bAutoUpdate = !bAutoUpdate;
        break;

    case IDM_FILLBKGND:
        FillBkGnd();
        break;

    case IDM_EXIT:
        PostMessage(hWnd, WM_CLOSE, 0, 0l);
        break;

    case IDM_HELPCONTENTS:
        Help(hWnd, wParam);
        break;

    case IDM_ABOUT:
        About(hWnd);
        break;

#ifdef DEBUG
    case IDM_DEBUG0:
    case IDM_DEBUG1:
    case IDM_DEBUG2:
    case IDM_DEBUG3:
    case IDM_DEBUG4:
        SetDebugLevel(wParam - IDM_DEBUG0);
        break;
#endif

    default:
        break;
    }
}

//
// Process WM_DRAWITEM and WM_MEASUREITEM messages
//

static void MeasureItem(HWND hWnd, UINT uiCtl, LPMEASUREITEMSTRUCT lpMI)
{
    switch (uiCtl) {

    default:

        //
        // Return the height of the system font
        //

        lpMI->itemHeight = tmSysFont.tmHeight;
        break;
    }
}

static void DrawItem(HWND hWnd, UINT uiCtl, LPDRAWITEMSTRUCT lpDI)
{
    switch (uiCtl) {

    default:
        break;
    }
}

//
// Process WM_INITMENUPOPUP messages
//

static void InitMenuPopup(HMENU hmenuPopup, UINT uiIndex, BOOL bSystem)
{
    CheckMenuItem(hmenuPopup,
                  IDM_SHOWUPDATES,
                  bShowUpdateRects ? MF_CHECKED : MF_UNCHECKED);

    CheckMenuItem(hmenuPopup,
                  IDM_AUTOUPDATE,
                  bAutoUpdate ? MF_CHECKED : MF_UNCHECKED);

    EnableMenuItem(hmenuPopup,
                   IDM_LOADSPRITE,
                   pdibBkGnd ? MF_ENABLED : MF_DISABLED | MF_GRAYED);
}

//
// Show a message box
//

UINT cdecl Message(UINT uiBtns, LPSTR lpFormat, ...) 
{
    char buf[256];

    wvsprintf(buf, lpFormat, (LPSTR)(&lpFormat+1));
    MessageBeep(uiBtns ? uiBtns : MB_ICONEXCLAMATION);
    return (UINT) MessageBox(hwndMain, 
                             buf, 
                             szAppName, 
                             uiBtns ? uiBtns : MB_OK|MB_ICONEXCLAMATION);
}

