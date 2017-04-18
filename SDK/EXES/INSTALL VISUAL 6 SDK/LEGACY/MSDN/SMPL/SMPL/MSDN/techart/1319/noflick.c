/*
    noflick.c

    Window procedure which doesn't flicker
*/

#include "global.h"

//
// local data
//

static char szCaption[1024];
static HFONT hfnt;


//
// local functions
//

static void Paint(HWND hWnd, LPPAINTSTRUCT lpPS);


//
// Window procedure
//

LRESULT CALLBACK NoFlickerWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;

    switch(msg) {
    case WM_CREATE:
        break;

    case WM_SIZE:
        break;

    case WM_SETTEXT:
        lstrcpy(szCaption, (LPSTR)lParam);
        InvalidateRect(hWnd, NULL, TRUE);
        break;

    case WM_SETFONT:
        hfnt = (HFONT) wParam;
        break;

    case WM_ERASEBKGND:
        return (LRESULT)1; // say we handled it

    case WM_PAINT:
        BeginPaint(hWnd, &ps);
        Paint(hWnd, &ps);
        EndPaint(hWnd, &ps);
        break;

    case WM_DESTROY:
        break;

    default:
        return DefWindowProc(hWnd, msg, wParam, lParam);
        break;
    }
    return NULL;
}

//
// Paint procedure
//

static void Paint(HWND hWnd, LPPAINTSTRUCT lpPS)
{
    RECT rc;
    HDC hdcMem;
    HBITMAP hbmMem, hbmOld;
    HBRUSH hbrBkGnd;
    HFONT hfntOld;

    //
    // Get the size of the client rectangle
    //

    GetClientRect(hWnd, &rc);

    //
    // Create a compatible DC
    //

    hdcMem = CreateCompatibleDC(lpPS->hdc);

    //
    // Create a bitmap big enough for our client rect
    //

    hbmMem = CreateCompatibleBitmap(lpPS->hdc,
                                    rc.right-rc.left,
                                    rc.bottom-rc.top);

    //
    // Select the bitmap into the off-screen dc
    //

    hbmOld = SelectObject(hdcMem, hbmMem);

    //
    // Erase the background
    //

    hbrBkGnd = CreateSolidBrush(GetSysColor(COLOR_WINDOW));
    FillRect(hdcMem, &rc, hbrBkGnd);
    DeleteObject(hbrBkGnd);

    //
    // Select the font
    //

    if (hfnt) {
        hfntOld = SelectObject(hdcMem, hfnt);
    }

    //
    // Render the image into the offscreen dc
    //

    SetBkMode(hdcMem, TRANSPARENT);
    SetTextColor(hdcMem, GetSysColor(COLOR_WINDOWTEXT));
    DrawText(hdcMem,
             szCaption,
             -1,
             &rc,
             DT_CENTER);

    if (hfntOld) {
        SelectObject(hdcMem, hfntOld);
    }

    //
    // Blit the changes to the screen dc
    //

    BitBlt(lpPS->hdc, 
           rc.left, rc.top,
           rc.right-rc.left, rc.bottom-rc.top,
           hdcMem,
           0, 0,
           SRCCOPY);

    //
    // Done with off screen bitmap and dc
    //

    SelectObject(hdcMem, hbmOld);
    DeleteObject(hbmMem);
    DeleteDC(hdcMem);

}
