/*
    main.c

    A sample Windows application

    Another fine Herman Rodent production

*/

#include "global.h"

//
// local data
//

static PRINTDLG pd;

//
// local functions
//

static void Create(HWND hWnd, LPCREATESTRUCT lpCI);
static void Size(HWND hWnd, UINT uiX, UINT uiY);
static void Move(HWND hWnd, UINT uiX, UINT uiY);
static void Command(HWND hWnd, WPARAM wParam, LPARAM lParam);
static void MeasureItem(HWND hWnd, UINT uiCtl, LPMEASUREITEMSTRUCT lpMI);
static void DrawItem(HWND hWnd, UINT uiCtl, LPDRAWITEMSTRUCT lpDI);
static void InitMenuPopup(HMENU hMenu, UINT uiIndex, BOOL bSystem);
static void Paint(HWND hWnd, LPPAINTSTRUCT lpPS);
static void DropFiles(HWND hWnd, HDROP hDrop);
static void DrawBand(HWND hWnd, LPRECT prc);

//
// Entry point
//

int PASCAL WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpszCmdLine,
                   int cmdShow)
{
    MSG msg;

    ghAppInstance = hInstance;
    gszAppName = "TBSS";

#ifdef DEBUG

    //
    // Get the debug level
    //

    __iDebugLevel = GetProfileInt(gszAppName, "debug", 1);

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

            if (!TranslateAccelerator(ghwndMain, ghAccTable, &msg)) {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }

        } else {

            //
            // perform some idle routine or just give up so Windows
            // can run till our next message.
            //

            WaitMessage();
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
    static POBJECT pDragObj;
    static BOOL bCaptured;
    static RECT rcBand;
    static int dx, dy;
    static UINT uiBorderHit;
    static HCURSOR hcurOld = NULL;
    HCURSOR hcurSize;

    switch(msg) {
    case WM_CREATE:
        Create(hWnd, (LPCREATESTRUCT)lParam);
        break;

    case WM_MOVE:
        Move(hWnd, LOWORD(lParam), HIWORD(lParam));
        break;

    case WM_SIZE:
        Size(hWnd, LOWORD(lParam), HIWORD(lParam));
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

    case WM_LBUTTONDOWN:

        //
        // See if we hit an object and if we did then 
        // bring the object to the top, select it
        // and set up the rubber band for a drag or resize operation
        //

        pDragObj = HitTestObj(LOWORD(lParam), HIWORD(lParam));
        SelectObj(pDragObj, TRUE);

        if (pDragObj) {

            dprintf2("Object hit");
            SetCapture(hWnd);
            bCaptured = TRUE;
            BringObjToTop(pDragObj);
            rcBand = pDragObj->rc;
            dx = LOWORD(lParam) - pDragObj->rc.left;
            dy = HIWORD(lParam) - pDragObj->rc.top;
            DrawBand(hWnd, &rcBand);

        }
        // drop throughbreak;

    case WM_MOUSEMOVE:

        if (!bCaptured) {

            //
            // Test to see if mouse is over a resize region
            //

            uiBorderHit = SizeBorderHitTestObj(LOWORD(lParam), 
                                               HIWORD(lParam));
        }

        switch (uiBorderHit) {
        case SB_HIT_TOP:
        case SB_HIT_BOTTOM:

            hcurSize = LoadCursor(NULL, IDC_SIZENS);
            hcurOld = SetCursor(hcurSize);
            break;

        case SB_HIT_LEFT:
        case SB_HIT_RIGHT:

            hcurSize = LoadCursor(NULL, IDC_SIZEWE);
            hcurOld = SetCursor(hcurSize);
            break;

        default:
            if (hcurOld) {
                SetCursor(hcurOld);
                hcurOld = NULL;
            }
        }

        if (bCaptured) {

            int w, h;

            DrawBand(hWnd, &rcBand);

            switch (uiBorderHit) {
            case SB_HIT_LEFT:
                rcBand.left = LOWORD(lParam);
                break;

            case SB_HIT_RIGHT:
                rcBand.right = LOWORD(lParam);
                break;

            case SB_HIT_TOP:
                rcBand.top = HIWORD(lParam);
                break;

            case SB_HIT_BOTTOM:
                rcBand.bottom = HIWORD(lParam);
                break;

            default:
                w = rcBand.right - rcBand.left;
                rcBand.left = LOWORD(lParam) - dx;
                rcBand.right = rcBand.left + w;
                h = rcBand.bottom - rcBand.top;
                rcBand.top = HIWORD(lParam) - dy;
                rcBand.bottom = rcBand.top + h;
                break;
            }

            DrawBand(hWnd, &rcBand);

        }
        break;

    case WM_LBUTTONUP:

        //
        // Set the insertion point to where the mouse click occured
        // If we are in the captured state, update the object
        // position and release the capture. Then redraw everything
        //

        gptInsert.x = LOWORD(lParam);
        gptInsert.y = HIWORD(lParam);

        if (bCaptured) {

            ReleaseCapture();
            bCaptured = FALSE;
            pDragObj->rc = rcBand;
        }
        InvalidateRect(hWnd, NULL, TRUE);

        break;

    case WM_PAINT:
        BeginPaint(hWnd, &ps);
        Paint(hWnd, &ps);
        EndPaint(hWnd, &ps);
        break;

    case WM_INITMENUPOPUP:
        InitMenuPopup((HMENU)wParam, LOWORD(lParam), (BOOL)HIWORD(lParam));
        break;

    case WM_DROPFILES:
        DropFiles(hWnd, (HDROP)wParam);
        break;

    case WM_CLOSE:
        if (PromptToSave()) {
            DestroyWindow(ghwndMain);
        }
        return 0; // say we handled the message

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
// Process WM_MOVE message
//

static void Move(HWND hWnd, UINT uiX, UINT uiY)
{

}

//
// Process WM_SIZE message
//

static void Size(HWND hWnd, UINT uiW, UINT uiH)
{

}

//
// Process WM_COMMAND messages
//

static void Command(HWND hWnd, WPARAM wParam, LPARAM lParam) 
{
    switch (wParam) {
    case IDM_NEW:
        FileNew(FILE_PROMPT_FOR_SAVE | FILE_UPDATE_CAPTION);
        break;

    case IDM_OPEN:
        FileOpen(NULL);
        break;

    case IDM_SAVE:
        FileSave(FILE_SAVE);
        break;

    case IDM_SAVEAS:
        FileSave(FILE_SAVE_AS);
        break;

    case IDM_PRINT:
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

    case IDM_EXIT:
        PostMessage(hWnd, WM_CLOSE, 0, 0l);
        break;

    case IDM_CUT:
    case IDM_COPY:
    case IDM_PASTE:
        ClipCommand(hWnd, wParam);
        break;

    case IDM_INSERTOBJECT:
        InsertObjCmd(hWnd);
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

    case IDM_DEBUG_DIRTY:
        gfDirty = TRUE;
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

        lpMI->itemHeight = gtmSysFont.tmHeight;
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
// Process WM_PAINT messages
//

static void Paint(HWND hWnd, LPPAINTSTRUCT lpPS)
{
    POBJECT pObj;


    //
    // Walk down the object list, rendering the objects
    //

    pObj = gpObjList;
    while (pObj) {
        RenderObj(lpPS->hdc, pObj);
        pObj = pObj->pNext;
    }

    //
    // Show where the insertion point is
    //

    SetROP2(lpPS->hdc, R2_NOT);
    MoveTo(lpPS->hdc, gptInsert.x - 10, gptInsert.y);
    LineTo(lpPS->hdc, gptInsert.x + 10, gptInsert.y);
    MoveTo(lpPS->hdc, gptInsert.x, gptInsert.y - 10);
    LineTo(lpPS->hdc, gptInsert.x, gptInsert.y + 10);

}

//
// Process WM_INITMENUPOPUP messages
//

static void InitMenuPopup(HMENU hmenuPopup, UINT uiIndex, BOOL bSystem)
{
    //
    // See if there is anything in the clipboard which
    // we should enable the Paste item for
    //

    InitClipMenu(hmenuPopup);

#ifdef DEBUG
    //
    // Set the state of the dirty flag menu item
    //

    EnableMenuItem(hmenuPopup,
                   IDM_DEBUG_DIRTY,
                   gfDirty ? MF_GRAYED | MF_DISABLED : MF_ENABLED);
#endif // DEBUG
}

//
// Process WM_DROPFILES messages
//

static void DropFiles(HWND hWnd, HDROP hDrop)
{
    UINT ui;
    char szName[_MAX_PATH];

    dprintf2("DropFiles");

    ui = DragQueryFile(hDrop, 0xFFFF, NULL, 0);
    if (ui == 0) {
        DragFinish(hDrop);
        return;
    }
    if (ui > 1) {
        Message(0, "Only the first file will be opened");
    }

    ui = DragQueryFile(hDrop, 0, szName, sizeof(szName));
    if (ui) {
        dprintf3("File: %s", (LPSTR)szName);
        FileOpen(szName);
    }
    DragFinish(hDrop);
}

//
// Show a message box
//

UINT cdecl Message(UINT uiBtns, LPSTR lpFormat, ...) 
{
    char buf[256];

    wvsprintf(buf, lpFormat, (LPSTR)(&lpFormat+1));
    MessageBeep(uiBtns ? uiBtns : MB_ICONEXCLAMATION);
    return (UINT) MessageBox(ghwndMain, 
                             buf, 
                             gszAppName, 
                             uiBtns ? uiBtns : MB_OK|MB_ICONEXCLAMATION);
}

//
// Draw a rubber band on a window
//

static void DrawBand(HWND hWnd, LPRECT prc)
{
    HDC hDC;
    HBRUSH hbrNull, hbrOld;

    hDC = GetDC(hWnd);
    hbrNull = GetStockObject(NULL_BRUSH);
    hbrOld = SelectObject(hDC, hbrNull);
    SetROP2(hDC, R2_NOT);
    Rectangle(hDC,
              prc->left, 
              prc->top,
              prc->right,
              prc->bottom);
    SelectObject(hDC, hbrOld);
    ReleaseDC(hWnd, hDC);
}
