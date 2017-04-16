/*
    flicker.c

    Window procedure which flickers
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

LRESULT CALLBACK FlickerWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
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
    HFONT hfntOld = NULL;

    GetClientRect(hWnd, &rc);
    SetBkMode(lpPS->hdc, TRANSPARENT);

    if (hfnt) {
        hfntOld = SelectObject(lpPS->hdc, hfnt);
    }

    SetTextColor(lpPS->hdc, GetSysColor(COLOR_WINDOWTEXT));

    DrawText(lpPS->hdc,
             szCaption,
             -1,
             &rc,
             DT_CENTER);

    if (hfntOld) {
        SelectObject(lpPS->hdc, hfntOld);
    }
}
