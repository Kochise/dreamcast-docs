/**************************************************************************

    SCRAWL.CPP - A dumb drawing app demo for DirectInput

    Collects mouse data in various modes to demonstrate how it's done.

 **************************************************************************/
/**************************************************************************

    (C) Copyright 1995-1997 Microsoft Corp.  All rights reserved.

    You have a royalty-free right to use, modify, reproduce and
    distribute the Sample Files (and/or any modified version) in
    any way you find useful, provided that you agree that
    Microsoft has no warranty obligations or liability for any
    Sample Application Files which are modified.

 **************************************************************************/

#include <windows.h>
#include <windowsx.h>
#include <stdarg.h>

#define DIRECTINPUT_VERSION 0x0300      /* Remain DX3-compatible */
#include <dinput.h>

#include "scrawl.h"

/****************************************************************************
 *
 *      This is an incredibly dump app.  It just lets you "draw" on
 *      a monochrome bitmap via DirectInput.  The purpose is not to
 *      dazzle you with mind-altering brilliance.  It's just to show
 *      how to use the DirectInput mouse interface.
 *
 ****************************************************************************/

/****************************************************************************
 *
 *      Manifest constants
 *
 ****************************************************************************/

#define DINPUT_BUFFERSIZE           16

#define DINPUT_CXBITMAP             512
#define DINPUT_CYBITMAP             300

/****************************************************************************
 *
 *      Global variables
 *
 ****************************************************************************/

const char c_szAppName[] = "Scrawl";    /* My name */

HINSTANCE  g_hinst;                     /* My instance handle */
BOOL       g_fActive;                   /* Am I the active window? */

int        g_x = DINPUT_CXBITMAP / 2;   /* Virtual x-coordinate */
int        g_y = DINPUT_CYBITMAP / 2;   /* Virtual y-coordinate */

int        g_dxFuzz;                    /* Leftover x-fuzz from scaling */
int        g_dyFuzz;                    /* Leftover y-fuzz from scaling */
int        g_iSensitivity;              /* Mouse sensitivity */

HDC        g_hdc;                       /* Memory DC our picture lives in */
HBITMAP    g_hbm;                       /* Our picture */
HBITMAP    g_hbmDeselect;               /* Stock bitmap for deselecting */

HCURSOR    g_hcurCross;                 /* Crosshairs */
int        g_cxCross;                   /* Width of crosshairs cursor */
int        g_cyCross;                   /* Height of crosshairs cursor */
int        g_dxCrossHot;                /* Hotspot location of crosshairs */
int        g_dyCrossHot;                /* Hotspot location of crosshairs */
int        g_fShowCursor = 1;           /* Should the cursor be shown? */

/****************************************************************************
 *
 *      DirectInput globals
 *
 ****************************************************************************/

LPDIRECTINPUT          g_pdi;
LPDIRECTINPUTDEVICE    g_pMouse;

HANDLE                 g_hevtMouse;

/****************************************************************************
 *
 *      Complain
 *
 *      Whine and moan.
 *
 ****************************************************************************/

void CDECL
Complain(HWND hwndOwner, HRESULT hr, LPCSTR pszFormat, ...)
{
    va_list ap;
    char szBuf[1024];
    char *pszBuf;

    va_start(ap, pszFormat);

    pszBuf = szBuf + wsprintf(szBuf, pszFormat, ap);

    va_end(ap);

    wsprintf(pszBuf, "\n\nError = %08x", hr);

    MessageBox(hwndOwner, szBuf, c_szAppName, MB_OK);
}

/****************************************************************************
 *
 *      DIInit
 *
 *      Initialize the DirectInput variables.
 *
 ****************************************************************************/

BOOL DIInit(HWND hwnd)
{
    HRESULT hr;

    /*
     *  Register with DirectInput and get an IDirectInput to play with.
     */
    hr = DirectInputCreate(g_hinst, DIRECTINPUT_VERSION, &g_pdi, NULL);

    if (FAILED(hr)) {
        Complain(hwnd, hr, "DirectInputCreate");
        return FALSE;
    }

    /*
     *  Obtain an interface to the system mouse device.
     */
    hr = g_pdi->CreateDevice(GUID_SysMouse, &g_pMouse, NULL);

    if (FAILED(hr)) {
        Complain(hwnd, hr, "CreateDevice(SysMouse)");
        return FALSE;
    }

    /*
     *  Set the data format to "mouse format".
     */
    hr = g_pMouse->SetDataFormat(&c_dfDIMouse);

    if (FAILED(hr)) {
        Complain(hwnd, hr, "SetDataFormat(SysMouse, dfDIMouse)");
        return FALSE;
    }


    /*
     *  Set the cooperativity level.
     */
    hr = g_pMouse->SetCooperativeLevel(hwnd,
                                       DISCL_EXCLUSIVE | DISCL_FOREGROUND);

    if (FAILED(hr)) {
        Complain(hwnd, hr, "SetCooperativeLevel(SysMouse)");
        return FALSE;
    }


    /*
     *  Create the handle that tells us new data is available.
     */
    g_hevtMouse = CreateEvent(0, 0, 0, 0);

    if (g_hevtMouse == NULL) {
        Complain(hwnd, GetLastError(), "CreateEvent");
        return FALSE;
    }

    /*
     *  Associate the event with the device.
     */
    hr = g_pMouse->SetEventNotification(g_hevtMouse);

    if (FAILED(hr)) {
        Complain(hwnd, hr, "SetEventNotification(SysMouse)");
        return FALSE;
    }

    /*
     *  Set the buffer size to DINPUT_BUFFERSIZE elements.
     *  The buffer size is a DWORD property associated with the device.
     */
    DIPROPDWORD dipdw =
        {
            {
                sizeof(DIPROPDWORD),        // diph.dwSize
                sizeof(DIPROPHEADER),       // diph.dwHeaderSize
                0,                          // diph.dwObj
                DIPH_DEVICE,                // diph.dwHow
            },
            DINPUT_BUFFERSIZE,              // dwData
        };

    hr = g_pMouse->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph);

    if (FAILED(hr)) {
        Complain(hwnd, hr, "Set buffer size(SysMouse)");
        return FALSE;
    }

    return TRUE;

}

/****************************************************************************
 *
 *      DITerm
 *
 *      Terminate our usage of DirectInput.
 *
 ****************************************************************************/

void DITerm(void)
{
    if (g_pdi)      g_pdi   ->Release(), g_pdi    = NULL;
    if (g_pMouse)   g_pMouse->Release(), g_pMouse = NULL;

    if (g_hevtMouse) CloseHandle(g_hevtMouse), g_hevtMouse = NULL;
}

/****************************************************************************
 *
 *      InvalidateCursorRect
 *
 *      Invalidate the rectangle that contains the cursor.
 *
 *      The coordinates are in client coordinates.
 *
 ****************************************************************************/

void InvalidateCursorRect(HWND hwnd)
{
    RECT rc = { g_x - g_dxCrossHot,             g_y - g_dyCrossHot,
                g_x - g_dxCrossHot + g_cxCross, g_y - g_dyCrossHot + g_cyCross };

    InvalidateRect(hwnd, &rc, 0);
}

/****************************************************************************
 *
 *      UpdateCursorPosition
 *
 *      Move our private cursor in the requested direction, subject
 *      to clipping, scaling, and all that other stuff.
 *
 *      This does not redraw the cursor.  You need to do that yourself.
 *
 ****************************************************************************/

void UpdateCursorPosition(int dx, int dy)
{

    /*
     *  Pick up any leftover fuzz from last time.  This is important
     *  when scaling down mouse motions.  Otherwise, the user can
     *  drag to the right extremely slow for the length of the table
     *  and not get anywhere.
     */
    dx += g_dxFuzz;     g_dxFuzz = 0;
    dy += g_dyFuzz;     g_dyFuzz = 0;

    switch (g_iSensitivity) {

    case 1:                             /* High sensitivity: Magnify! */
        dx *= 2;
        dy *= 2;
        break;

    case -1:                            /* Low sensitivity: Scale down */
        g_dxFuzz = dx % 2;              /* remember the fuzz for next time */
        g_dyFuzz = dy % 2;
        dx /= 2;
        dy /= 2;
        break;

    default:
    case 0:                             /* No sensitivity */
        ;                               /* No adjustments needed */
    }

    g_x += dx;
    g_y += dy;

    /* Clip the cursor to our client area */
    if (g_x < 0)                g_x = 0;
    if (g_x >= DINPUT_CXBITMAP) g_x = DINPUT_CXBITMAP - 1;

    if (g_y < 0)                g_y = 0;
    if (g_y >= DINPUT_CYBITMAP) g_y = DINPUT_CYBITMAP - 1;

}

/****************************************************************************
 *
 *      Scrawl_SyncAcquire
 *
 *      Acquire or unacquire the devices, depending on the the g_fActive
 *      flag.  This synchronizes the devices with our internal view of
 *      the world.
 *
 *      Also repaint the cursor so that it hides/shows in sync with
 *      acquisition.
 *
 ****************************************************************************/

void
Scrawl_SyncAcquire(HWND hwnd)
{
    if (g_fActive) {
        if (g_pMouse) g_pMouse->Acquire();
    } else {
        if (g_pMouse) g_pMouse->Unacquire();
    }

    InvalidateCursorRect(hwnd);
}

/****************************************************************************
 *
 *      Private messages
 *
 *      WM_SYNCACQUIRE forces us to re-synchronize our acquisition
 *      with the world.
 *
 ****************************************************************************/

#define WM_SYNCACQUIRE      (WM_USER + 0)

/****************************************************************************
 *
 *      Scrawl_OnClear
 *
 *      Wipe out the bitmap.
 *
 ****************************************************************************/

void Scrawl_OnClear(HWND hwnd)
{
    /*
     *  Start out all white.
     */
    PatBlt(g_hdc, 0, 0, DINPUT_CXBITMAP, DINPUT_CYBITMAP, WHITENESS);

    if (hwnd) {
        InvalidateRect(hwnd, 0, 0);
    }
}

/****************************************************************************
 *
 *      Scrawl_OnCreate
 *
 *      Set up the window by appending our custom commands to the System
 *      menu.
 *
 *      Also disable the menu items we don't want to see.
 *
 ****************************************************************************/

BOOL Scrawl_OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct)
{
    HMENU hmenu = GetSystemMenu(hwnd, FALSE);

    EnableMenuItem(hmenu, SC_SIZE,     MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
    EnableMenuItem(hmenu, SC_MAXIMIZE, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);

    AppendMenu(hmenu, MF_ENABLED | MF_STRING, IDC_CLEAR, "C&lear\tDel");
    AppendMenu(hmenu, MF_ENABLED | MF_STRING, IDC_ABOUT, "&About\tF1");

    AppendMenu(hmenu, MF_ENABLED | MF_STRING | MF_POPUP,
                      (UINT)LoadMenu(g_hinst,
                                     MAKEINTRESOURCE(IDM_SENSITIVITY)),
                     "Sensitivit&y");

    return 1;
}

/****************************************************************************
 *
 *      Scrawl_OnInitMenuPopup
 *
 *      Initialize the sensitivity item accordingly.
 *
 ****************************************************************************/

void
Scrawl_OnInitMenuPopup(HWND hwnd, HMENU hmenu, UINT item, BOOL fSystemMenu)
{
    int iSensitivity;
    for (iSensitivity = -1; iSensitivity <= 1; iSensitivity++) {
        if (g_iSensitivity == iSensitivity) {
            CheckMenuItem(hmenu, IDC_SENSITIVITY_NORMAL + iSensitivity,
                          MF_BYCOMMAND | MF_CHECKED);
        } else {
            CheckMenuItem(hmenu, IDC_SENSITIVITY_NORMAL + iSensitivity,
                          MF_BYCOMMAND | MF_UNCHECKED);
        }
    }

}

/****************************************************************************
 *
 *      Scrawl_OnKeyDown
 *
 *      See if it's one of our accelerators.
 *
 ****************************************************************************/

void Scrawl_OnKeyDown(HWND hwnd, UINT vk, BOOL fDown, int cRepeat, UINT flags)
{
    switch (vk) {
    case '1':
    case '2':
    case '3':
        PostMessage(hwnd, WM_SYSCOMMAND, IDC_SENSITIVITY_NORMAL +
                                         vk - '2', 0);
        break;

    case VK_DELETE:
        PostMessage(hwnd, WM_SYSCOMMAND, IDC_CLEAR, 0);
        break;

    case VK_F1:
        PostMessage(hwnd, WM_SYSCOMMAND, IDC_ABOUT, 0);
        break;

    }
}

/****************************************************************************
 *
 *      Scrawl_OnPaint
 *
 *      Blt out our bitmap and draw our cursor on top of it.
 *
 ****************************************************************************/

void
Scrawl_OnPaint(HWND hwnd)
{
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hwnd, &ps);

    if (hdc) {

        BitBlt(hdc,
               ps.rcPaint.left,
               ps.rcPaint.top,
               ps.rcPaint.right - ps.rcPaint.left,
               ps.rcPaint.bottom - ps.rcPaint.top,
               g_hdc,
               ps.rcPaint.left,
               ps.rcPaint.top,
               SRCCOPY);

        if (g_fActive && g_fShowCursor) {
            DrawIcon(hdc, g_x - g_dxCrossHot,
                          g_y - g_dyCrossHot, g_hcurCross);
        }

        EndPaint(hwnd, &ps);
    }
}

/****************************************************************************
 *
 *      Scrawl_OnButton0Down_FlushMotion
 *
 *      Flush out any motion that we are holding.
 *
 ****************************************************************************/

typedef struct BUTTON0INFO {

    HDC hdcWindow;
    BOOL fMoved;
    DWORD dwSeqLastSeen;

} BUTTON0INFO, *PBUTTON0INFO;

void Scrawl_OnButton0Down_FlushMotion(PBUTTON0INFO pb0i)
{
    if (pb0i->fMoved) {
        pb0i->fMoved = 0;
        pb0i->dwSeqLastSeen = 0;
        LineTo(pb0i->hdcWindow, g_x, g_y);
        LineTo(g_hdc, g_x, g_y);
    }

}

/****************************************************************************
 *
 *      Scrawl_OnButton0Down
 *
 *      Enter draw mode.
 *
 *      If we are drawing a curve, then read buffered data and draw
 *      lines from point to point.  By reading buffered data, we can
 *      track the motion of the mouse accurately without coalescing.
 *
 *      This function illustrates how a non-message-based program can
 *      process buffered data directly from a device, processing
 *      messages only occasionally (as required by Windows).
 *
 *      This function also illustrates how an application can piece
 *      together buffered data elements based on the sequence number.
 *      A single mouse action (e.g., moving diagonally) is reported
 *      as a series of events, all with the same sequence number.
 *      Zero is never a valid DirectInput sequence number, so it is
 *      safe to use it as a sentinel value.
 *
 ****************************************************************************/

void Scrawl_OnButton0Down(HWND hwnd)
{
    BUTTON0INFO b0i;

    /* Hide the cursor while scrawling */
    g_fShowCursor = FALSE;
    InvalidateCursorRect(hwnd);
    UpdateWindow(hwnd);

    /*
     *  For performance, draw directly onto the window's DC instead of
     *  invalidating and waiting for the WM_PAINT message.  Of course,
     *  we always draw onto our bitmap, too, since that's what really
     *  counts.
     */

    /* BUGBUG -- select a decent pen, too */
    b0i.hdcWindow = GetDC(hwnd);
    MoveToEx(b0i.hdcWindow, g_x, g_y, 0);
    MoveToEx(g_hdc, g_x, g_y, 0);

    /* BUGBUG -- save old pen */
    SelectObject(b0i.hdcWindow, GetStockObject(BLACK_PEN));
    SelectObject(g_hdc, GetStockObject(BLACK_PEN));

    b0i.fMoved = 0;
    b0i.dwSeqLastSeen = 0;

    /*
     *  Keep reading data elements until we see a "mouse button up" event.
     */
    BOOL fDone = 0;
    while (!fDone) {
        DIDEVICEOBJECTDATA od;

        DWORD dwElements = 1;

        HRESULT hr = g_pMouse->GetDeviceData(
                             sizeof(DIDEVICEOBJECTDATA), &od,
                             &dwElements, 0);

        /* Unable to read data */
        if (FAILED(hr)) {
            break;
        }

        /*
         *  If no data available, finish the element we had been
         *  collecting, and then process our message queue so
         * the system don't think we're hung.
         */
        if (dwElements == 0) {

            /* If there is a partial motion, flush it out */
            Scrawl_OnButton0Down_FlushMotion(&b0i);

            MSG msg;
            while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
                /* If it's a quit message, we're outta here */
                if (msg.message == WM_QUIT) {
                    fDone = TRUE;
                    /*
                     * Re-post the quit message so the
                     * outer loop will see it and exit.
                     */
                    PostQuitMessage(msg.wParam);
                    break;
                } else {
                    TranslateMessage(&msg);
                    DispatchMessage(&msg);
                }
            }
            continue;
        }

        /* If this is the start of a new event, flush out the old one */
        if (od.dwSequence != b0i.dwSeqLastSeen) {
            Scrawl_OnButton0Down_FlushMotion(&b0i);
            b0i.dwSeqLastSeen = od.dwSequence;
        }

        /* Look at the element to see what happened */

        switch (od.dwOfs) {

        /* DIMOFS_X: Mouse horizontal motion */
        case DIMOFS_X:
            UpdateCursorPosition(od.dwData, 0);
            b0i.fMoved = 1;
            break;


        /* DIMOFS_Y: Mouse vertical motion */
        case DIMOFS_Y:
            UpdateCursorPosition(0, od.dwData);
            b0i.fMoved = 1;
            break;

        /* DIMOFS_BUTTON0: Button 0 pressed or released */
        case DIMOFS_BUTTON0:

            if (!(od.dwData & 0x80)) { /* Button released */
                fDone = 1;
                Scrawl_OnButton0Down_FlushMotion(&b0i); /* Flush out dregs */
            }
            break;

        }
    }

    ReleaseDC(hwnd, b0i.hdcWindow);

    /* Re-show the cursor now that scrawling is finished */
    g_fShowCursor = TRUE;
    InvalidateCursorRect(hwnd);
}


/****************************************************************************
 *
 *      Scrawl_OnButton1Up
 *
 *      Pop up a context menu.
 *
 ****************************************************************************/

void Scrawl_OnButton1Up(HWND hwnd)
{
    POINT pt = { g_x, g_y };
    ClientToScreen(hwnd, &pt);

    /*
     *  Unacquire the devices so the user can interact with the menu.
     *
     *  Put the Windows cursor at the same location as our virtual cursor.
     *
     *  Hide the cursor while moving it so you don't get annoying flicker.
     */

    ShowCursor(FALSE);
    g_fActive = FALSE;
    Scrawl_SyncAcquire(hwnd);
    SetCursorPos(pt.x, pt.y);
    ShowCursor(TRUE);

    HMENU hmenuPopup = GetSystemMenu(hwnd, FALSE);

    UINT idc = TrackPopupMenuEx(hmenuPopup,
                                TPM_RIGHTBUTTON | TPM_RETURNCMD,
                                pt.x, pt.y, hwnd, 0);

    PostMessage(hwnd, WM_SYSCOMMAND, idc, 0L);

}

/****************************************************************************
 *
 *      Scrawl_OnMouseInput
 *
 *      The mouse moved while nothing was happening.  Walk the event list
 *      and update the mouse position for each event.  If we see a button
 *      event, then stop pulling events and leave the elements in the
 *      input buffer for the drawing handler to pull.
 *
 *
 ****************************************************************************/

void
Scrawl_OnMouseInput(HWND hwnd)
{
    /* Invalidate the old cursor so it will be erased */
    InvalidateCursorRect(hwnd);

    /*
     *  Attempt to read one data element.  Continue as long as
     *  device data is available.
     */
    BOOL fDone = 0;
    while (!fDone) {
        DIDEVICEOBJECTDATA od;

        DWORD dwElements = 1;

        HRESULT hr = g_pMouse->GetDeviceData(
                             sizeof(DIDEVICEOBJECTDATA), &od,
                             &dwElements, 0);

        if (hr == DIERR_INPUTLOST) {
            /*
             *  We had acquisition, but lost it.  Try to reacquire it.
             *
             *  WARNING!  DO NOT ATTEMPT TO REACQUIRE IF YOU GET
             *  DIERR_NOTACQUIRED!  Otherwise, you're extremely likely
             *  to get caught in an infinite loop:  The acquire will fail,
             *  and you'll get another DIERR_NOTACQUIRED so you'll
             *  try to aquire again, and that'll fail, etc.
             */
            PostMessage(hwnd, WM_SYNCACQUIRE, 0, 0L);
            break;
        }

        /* Unable to read data or no data available */
        if (FAILED(hr) || dwElements == 0) {
            break;
        }

        /* Look at the element to see what happened */

        switch (od.dwOfs) {

        /* DIMOFS_X: Mouse horizontal motion */
        case DIMOFS_X: UpdateCursorPosition(od.dwData, 0); break;


        /* DIMOFS_Y: Mouse vertical motion */
        case DIMOFS_Y: UpdateCursorPosition(0, od.dwData); break;

        /* DIMOFS_BUTTON0: Button 0 pressed or released */
        case DIMOFS_BUTTON0:

            if (od.dwData & 0x80) { /* Button pressed */
                fDone = 1;
                Scrawl_OnButton0Down(hwnd); /* Go into button-down mode */
            }
            break;

        /* DIMOFS_BUTTON1: Button 1 pressed or released */
        case DIMOFS_BUTTON1:

            if (!(od.dwData & 0x80)) {  /* Button released */
                fDone = 1;
                Scrawl_OnButton1Up(hwnd); /* Context menu time */
            }
        }

    }

    /* Invalidate the new cursor so it will be drawn */
    InvalidateCursorRect(hwnd);

}

/****************************************************************************
 *
 *      ScrawlWndProc
 *
 *      Application window procedure.
 *
 ****************************************************************************/

LONG CALLBACK ScrawlWndProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
    switch (msg) {

    HANDLE_MSG(hwnd, WM_CREATE, Scrawl_OnCreate);

    HANDLE_MSG(hwnd, WM_PAINT, Scrawl_OnPaint);

    HANDLE_MSG(hwnd, WM_INITMENUPOPUP, Scrawl_OnInitMenuPopup);

    HANDLE_MSG(hwnd, WM_KEYDOWN, Scrawl_OnKeyDown);

    /*
     *  Reacquire the mouse and keyboard when we are the active window.
     *  Unacquire them when we stop being the active window.
     */
    case WM_ACTIVATE:
        g_fActive = wParam == WA_ACTIVE || wParam == WA_CLICKACTIVE;
        Scrawl_SyncAcquire(hwnd);
        break;

    /*
     *  Unacquire the devices if a menu appears, so that the user can
     *  interact with the menu in the normal manner.
     *
     *  From Windows' point of view, we are still the active window
     *  when a menu appears, but we want to act like the menu deactivated
     *  us.
     */
    case WM_ENTERMENULOOP:
    case WM_ENTERSIZEMOVE:
        g_fActive = FALSE;
        Scrawl_SyncAcquire(hwnd);
        break;

    /*
     *  Reacquire the devices when the menu goes away.
     *
     *  SUBTLETY 1:  Windows actually sends the WM_EXITMENULOOP message
     *  before all the menu-related stuff is finished, so post ourselves
     *  a private message to reacquire after the menu has been torn
     *  down for real.
     *
     *  SUBTLETY 2:  Don't assume that just because the menu is going
     *  away that you are still the active window.  You might not be.
     *
     *  SUBTLETY 3:  Don't assume that just because you're the active
     *  window that you are restored and ready for action.  You might
     *  just be a taskbar button.
     */
    case WM_EXITMENULOOP:
    case WM_EXITSIZEMOVE:
        g_fActive = GetActiveWindow() == hwnd && !IsIconic(hwnd);
        PostMessage(hwnd, WM_SYNCACQUIRE, 0, 0L);
        break;

    case WM_SYNCACQUIRE:
        Scrawl_SyncAcquire(hwnd);
        break;

    case WM_SYSCOMMAND:

        LRESULT lRc;
        switch (GET_WM_COMMAND_ID(wParam, lParam)) {
        case IDC_CLEAR:
            Scrawl_OnClear(hwnd);
            lRc = 0;
            break;

        case IDC_ABOUT:
            MessageBox(hwnd, "Scrawl DirectInput Sample v1.0",
                    c_szAppName, MB_OK);
            lRc = 0;
            break;

        /*
         *  Eat the screen-saver notification.
         */
        case SC_SCREENSAVE:
            lRc = 0;
            break;

        case IDC_SENSITIVITY_LOW:
        case IDC_SENSITIVITY_NORMAL:
        case IDC_SENSITIVITY_HIGH:
            g_iSensitivity = (signed short)GET_WM_COMMAND_ID(wParam, lParam)
                                - IDC_SENSITIVITY_NORMAL;
            lRc = 0;
            break;

        default:
            lRc = DefWindowProc(hwnd, msg, wParam, lParam);
            break;
        }

        /*
         * The WM_SYSCOMMAND might've been a WM_CLOSE, in which case
         * our window no longer exists.  So be careful.
         */
        if (IsWindow(hwnd)) {
            Scrawl_SyncAcquire(hwnd);
        }
        return lRc;


    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    }

    return DefWindowProc(hwnd, msg, wParam, lParam);
}

/****************************************************************************
 *
 *      AppInit
 *
 *      Set up everything the application needs to get started.
 *
 ****************************************************************************/

HWND AppInit(HINSTANCE hinst, int nCmdShow)
{

    /* Save instance handle for people who care */
    g_hinst = hinst;

    /*
     *  Get our crosshairs cursor and extract the the width and
     *  hotspot location so we can draw it manually.
     */
    g_hcurCross = LoadCursor(NULL, IDC_CROSS);

    ICONINFO ii;

    GetIconInfo(g_hcurCross, &ii);

    BITMAP bm;

    GetObject(ii.hbmMask, sizeof(BITMAP), &bm);

    if (ii.hbmMask)  DeleteObject(ii.hbmMask);
    if (ii.hbmColor) DeleteObject(ii.hbmColor);

    g_dxCrossHot = ii.xHotspot;
    g_dyCrossHot = ii.yHotspot;

    g_cxCross = bm.bmWidth;
    g_cyCross = bm.bmHeight;

    /*
     *  Create our scrawl bitmap and set it up.
     */
    HDC hdc = GetDC(0);
    g_hdc = CreateCompatibleDC(hdc);
    ReleaseDC(0, hdc);

    if (!g_hdc) return NULL;

    g_hbm = CreateBitmap(DINPUT_CXBITMAP, DINPUT_CYBITMAP, 1, 1, 0);

    if (!g_hbm) return NULL;

    g_hbmDeselect = (HBITMAP) SelectObject(g_hdc, g_hbm);

    Scrawl_OnClear(0);

    /*
     *  Set up the window class.
     */
    WNDCLASS wc;

    wc.hCursor        = LoadCursor(0, IDC_ARROW);
    wc.hIcon          = LoadIcon(hinst, MAKEINTRESOURCE(IDI_MAIN));
    wc.lpszMenuName   = NULL;
    wc.lpszClassName  = c_szAppName;
    wc.hbrBackground  = 0;
    wc.hInstance      = hinst;
    wc.style          = 0;
    wc.lpfnWndProc    = ScrawlWndProc;
    wc.cbClsExtra     = 0;
    wc.cbWndExtra     = 0;

    if (!RegisterClass(&wc)) {
        return NULL;
    }

    DWORD dwStyle = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
    DWORD dwExStyle = WS_EX_APPWINDOW;

    RECT rc = { 0, 0, DINPUT_CXBITMAP, DINPUT_CYBITMAP };

    AdjustWindowRectEx(&rc, dwStyle, FALSE, dwExStyle);

    HWND hwnd = CreateWindowEx(
                    dwExStyle,          // ExStyle
                    c_szAppName,        // Class name
                    c_szAppName,        // Caption
                    dwStyle,            // Style
                    CW_USEDEFAULT, CW_USEDEFAULT,  // Position
                    rc.right - rc.left, // cx
                    rc.bottom - rc.top, // cy
                    0,                  // Parent window (no parent)
                    0,                  // use class menu
                    g_hinst,            // handle to module instance
                    0                   // no params to pass on
                    );

    if (!DIInit(hwnd)) {
        DestroyWindow(hwnd);
        return NULL;
    }

    ShowWindow(hwnd, nCmdShow);

    return hwnd;
}

/****************************************************************************
 *
 *      WinMain
 *
 *      Application entry point.
 *
 *      The main message loop illustrates how a message-driven program
 *      can use event notifications to be signalled when new data is
 *      available from a device.
 *
 ****************************************************************************/

int PASCAL
WinMain(HINSTANCE hinst, HINSTANCE hinstPrev, LPSTR szCmdLine, int nCmdShow)
{
    MSG msg;
    msg.wParam = 0;         /* In case something goes horribly wrong */

    HWND hwnd = AppInit(hinst, nCmdShow);

    if (hwnd) {

        /*
         *  Since we use notification handles, we need to use
         *  MsgWaitForMultipleObjects to wait for the event or
         *  a message, whichever comes first.
         */

        BOOL fDone = FALSE;

        while (!fDone) {

            DWORD dw = MsgWaitForMultipleObjects(1, &g_hevtMouse, 0, INFINITE,
                                                 QS_ALLINPUT);

            switch (dw) {

            /* WAIT_OBJECT_0 + 0 means that g_hevtMouse was signalled */
            case WAIT_OBJECT_0 + 0:
                Scrawl_OnMouseInput(hwnd);
                break;

            /* WAIT_OBJECT_0 + 1 means that we have messages to process */
            case WAIT_OBJECT_0 + 1:

                while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {

                    /* If it's a quit message, we're outta here */
                    if (msg.message == WM_QUIT) {
                        fDone = TRUE;
                    } else {
                        TranslateMessage(&msg);
                        DispatchMessage(&msg);
                    }
                }
                break;
            }
        }
    }

    DITerm();

    if (g_hdc) {
        if (g_hbmDeselect) {
            SelectObject(g_hdc, g_hbmDeselect);
        }
        DeleteDC(g_hdc);
    }

    if (g_hbm) {
        DeleteObject(g_hbm);
    }

  return msg.wParam;

}
