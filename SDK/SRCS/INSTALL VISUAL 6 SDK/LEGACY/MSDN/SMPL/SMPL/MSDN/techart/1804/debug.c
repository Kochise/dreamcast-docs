/*
    debug.c

    Functions to support a popup debug window

    Debug level 4 now includes the time of the message in ms

*/

#include "global.h"

//
// Constants
//

#define MAXLISTLINES    100     // max list lines we keep
#define IDC_LIST        1       // listbox id

//
// local data
//

HWND hwndDebug;
HWND hwndDebugList;

#ifdef DEBUG

//
// Set the current debug level
//

void SetDebugLevel(int i)
{
    HMENU hMenu;
    int m;

    hMenu = GetMenu(ghwndMain); 
    for (m=IDM_DEBUG0; m<=IDM_DEBUG4; m++) {
        CheckMenuItem(hMenu, m, MF_UNCHECKED);
    }
    CheckMenuItem(hMenu, i + IDM_DEBUG0, MF_CHECKED);
    __iDebugLevel = i;
}

//
// Show a message box with assertion failure info in it
//

void __AssertMsg(LPSTR exp, LPSTR file, int line)
{
    char buf[256];
    int i;

    wsprintf(buf, 
             "Exp: %s\nFile: %s, Line %d",
             (LPSTR)exp,
             (LPSTR)file,
             line);
    DbgOut("ASSERT: Exp: %s", (LPSTR)exp);
    DbgOut(" File: %s, Line %d", (LPSTR)file, line);
    i = MessageBox(ghwndMain,
                   buf,
                   "Assertion failure", 
                   MB_OK | MB_ICONEXCLAMATION);
}

//
// function to add a string to the end of the debug list
//

void cdecl DbgOut(LPSTR lpFormat, ...) 
{
    int i;
    char buf[256];
    MMTIME mmtime;

    //
    // See if we have a debug window or not.
    // If not then try to create one.
    //

    if (!hwndDebug) {

        wsprintf(buf, "%s - Debug", (LPSTR)gszAppName);
        hwndDebug = CreateWindow("Debug",
                            buf,
                            WS_POPUP | WS_VISIBLE | WS_CAPTION | WS_SYSMENU
                                | WS_BORDER | WS_THICKFRAME | WS_MINIMIZEBOX,
                            GetSystemMetrics(SM_CXSCREEN) / 2,
                            GetSystemMetrics(SM_CYSCREEN) * 3 / 4,
                            GetSystemMetrics(SM_CXSCREEN) / 2,
                            GetSystemMetrics(SM_CYSCREEN) / 4,
                            (HWND)NULL,
                            (HMENU)NULL,
                            ghAppInstance,
                            (LPSTR)NULL
                            );

        if (!hwndDebug) return;
    }

    //
    // format the string
    //

    if (__iDebugLevel >= 4) {

        mmtime.wType = TIME_MS;
        timeGetSystemTime(&mmtime, sizeof(mmtime));
        wsprintf(buf, "%5.5ums:", LOWORD(mmtime.u.ms));
        wvsprintf(&buf[lstrlen(buf)], lpFormat, (LPSTR)(&lpFormat+1));

    } else {

        wvsprintf(buf, lpFormat, (LPSTR)(&lpFormat+1));
    }

    //
    // get the item count
    //

    i = (int) SendMessage(hwndDebugList, LB_GETCOUNT, (WPARAM) 0, (LPARAM) 0);
    if (i == LB_ERR) i = 0;

    //
    // scrub a few if we have too many
    //

    while (i >= MAXLISTLINES) {
        SendMessage(hwndDebugList, LB_DELETESTRING, (WPARAM) 0, (LPARAM) 0);
        i--;
    }

    //
    // add the new one on at the end and scroll it into view
    //

    i = (int) SendMessage(hwndDebugList, LB_ADDSTRING, (WPARAM) 0, (LPARAM) (LPSTR) buf);
    SendMessage(hwndDebugList, LB_SETCURSEL, (WPARAM) i, (LPARAM) 0);

}

//
// Measure an item in our debug listbox
//

static void MeasureDebugItem(HWND hWnd, LPMEASUREITEMSTRUCT lpMIS)
{
    TEXTMETRIC tm;
    HDC hDC;


    hDC = GetDC(hWnd);
    GetTextMetrics(hDC, &tm);
    ReleaseDC(hWnd, hDC);
    lpMIS->itemHeight = tm.tmHeight;
}

//
// Display an item in our debug listbox
//

void DrawDebugItem(HWND hWnd, LPDRAWITEMSTRUCT lpDI)
{
    HBRUSH hbrBkGnd;
    RECT rc;
    HDC hDC;
    char buf[256];
    
    hDC = lpDI->hDC;
    rc = lpDI->rcItem;

    switch (lpDI->itemAction) {

    case ODA_SELECT:
    case ODA_DRAWENTIRE:

        //
        // erase the rectangle
        //

        hbrBkGnd = CreateSolidBrush(GetSysColor(COLOR_WINDOW));
        FillRect(hDC, &rc, hbrBkGnd);
        DeleteObject(hbrBkGnd);

            //
            // show the text in our standard font
            //
    
            SetBkMode(hDC, TRANSPARENT);
    
            SendMessage(lpDI->hwndItem, 
                        LB_GETTEXT, 
                        lpDI->itemID, 
                        (LPARAM)(LPSTR)buf);

            ExtTextOut(hDC, 
                       rc.left+2, rc.top,
                       ETO_CLIPPED,
                       &rc, 
                       buf,
                       lstrlen(buf), 
                       NULL);
    
        break;
    
    }
}


#endif // DEBUG

//
// Window procedure for debug window
//

LRESULT CALLBACK DebugWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;

    switch(msg) {
    case WM_CREATE:

        //
        // Create the listbox 
        //

        hwndDebugList = CreateWindow("Listbox",
                            "",
                            WS_CHILD | WS_VISIBLE | WS_VSCROLL
                             | LBS_DISABLENOSCROLL
                             | LBS_HASSTRINGS | LBS_OWNERDRAWFIXED
                             | LBS_NOINTEGRALHEIGHT,
                            0,
                            0,
                            0,
                            0,
                            hWnd,
                            (HMENU)IDC_LIST,
                            ghAppInstance,
                            (LPSTR)NULL
                            );

        break;

    case WM_SIZE:
        SetWindowPos(hwndDebugList,
                     NULL,
                     0, 0,
                     LOWORD(lParam), HIWORD(lParam),
                     SWP_NOZORDER);
        break;

    case WM_SETFOCUS:
        SetFocus(hwndDebugList);
        break;

    case WM_MEASUREITEM:
        MeasureDebugItem(hWnd, (LPMEASUREITEMSTRUCT)lParam);
        return (LRESULT) TRUE;

    case WM_DRAWITEM:
        DrawDebugItem(hWnd, (LPDRAWITEMSTRUCT) lParam);
        break;

    case WM_PAINT:
        BeginPaint(hWnd, &ps);
        EndPaint(hWnd, &ps);
        break;

    case WM_DESTROY:
        hwndDebug = NULL;
        break;

    default:
        return DefWindowProc(hWnd, msg, wParam, lParam);
        break;
    }
    return NULL;
}

void ClearDebugHistory()
{
    if (hwndDebugList) {
        SendMessage(hwndDebugList, LB_RESETCONTENT, 0, 0);
    }
}
