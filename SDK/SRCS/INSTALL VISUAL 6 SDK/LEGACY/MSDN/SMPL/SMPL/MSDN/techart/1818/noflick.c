/*
    noflick.c

    Window procedure which doesn't flicker
*/

#include "global.h"

//
// local data
//

typedef struct _NoFlickStruct {
	char szCaption[1024];
	HFONT hfnt;
} NOFLICKSTRUCT;

typedef NOFLICKSTRUCT* PNOFLICKSTRUCT;

//
// local functions
//

static void Paint(HWND hWnd, LPPAINTSTRUCT lpPS, PNOFLICKSTRUCT pNFStruct);


//
// Window procedure
//


LRESULT CALLBACK NoFlickerWndProc(HWND hWnd, UINT msg, UINT uParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	PNOFLICKSTRUCT pNFStruct;

    switch(msg) {
	case WM_CREATE:
		pNFStruct = malloc(sizeof(NOFLICKSTRUCT));
		memset(pNFStruct, 0, sizeof(NOFLICKSTRUCT));
		SetWindowLong(hWnd, 0, (long) pNFStruct);
        break;

    case WM_SIZE:
        break;

    case WM_SETTEXT:
		pNFStruct = ((PNOFLICKSTRUCT)GetWindowLong(hWnd, 0));

		lstrcpy(pNFStruct->szCaption, (LPSTR)lParam);
        InvalidateRect(hWnd, NULL, TRUE);
        break;

    case WM_SETFONT:
		pNFStruct = ((PNOFLICKSTRUCT)GetWindowLong(hWnd, 0));
		pNFStruct->hfnt = (HFONT) uParam;
        break;

    case WM_ERASEBKGND:
        return (LRESULT)1; // say we handled it

    case WM_PAINT:
		pNFStruct = ((PNOFLICKSTRUCT)GetWindowLong(hWnd, 0));
        BeginPaint(hWnd, &ps);
		Paint(hWnd, &ps, pNFStruct);
        EndPaint(hWnd, &ps);
        break;

    case WM_DESTROY:
		pNFStruct = ((PNOFLICKSTRUCT)GetWindowLong(hWnd, 0));
		free(pNFStruct);
        break;

    default:
		return DefWindowProc(hWnd, msg, uParam, lParam);
        break;
    }
	return 0;
}

//
// Paint procedure
//

static void Paint(HWND hWnd, LPPAINTSTRUCT lpPS, PNOFLICKSTRUCT pNFStruct)
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

	if (pNFStruct->hfnt) {
		hfntOld = SelectObject(hdcMem, pNFStruct->hfnt);
    }

    //
    // Render the image into the offscreen dc
    //

    SetBkMode(hdcMem, TRANSPARENT);
    SetTextColor(hdcMem, GetSysColor(COLOR_WINDOWTEXT));
    DrawText(hdcMem,
			 pNFStruct->szCaption,
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


void NoFlickUpdate(HWND hWnd)
{
    RECT rc;
    HDC hdcMem;
    HBITMAP hbmMem, hbmOld;
    HBRUSH hbrBkGnd;
	HFONT hfntOld;
	HDC hdc;
	PNOFLICKSTRUCT pNFStruct;

	pNFStruct = ((PNOFLICKSTRUCT)GetWindowLong(hWnd, 0));

	hdc = GetDC(hWnd);
    GetClientRect(hWnd, &rc);
	hdcMem = CreateCompatibleDC(hdc);
	hbmMem = CreateCompatibleBitmap(hdc,
                                    rc.right-rc.left,
                                    rc.bottom-rc.top);

    hbmOld = SelectObject(hdcMem, hbmMem);
    hbrBkGnd = CreateSolidBrush(GetSysColor(COLOR_WINDOW));
    FillRect(hdcMem, &rc, hbrBkGnd);
    DeleteObject(hbrBkGnd);

	if (pNFStruct->hfnt) {
		hfntOld = SelectObject(hdcMem, pNFStruct->hfnt);
    }

    SetBkMode(hdcMem, TRANSPARENT);
    SetTextColor(hdcMem, GetSysColor(COLOR_WINDOWTEXT));
    DrawText(hdcMem,
			 pNFStruct->szCaption,
             -1,
             &rc,
             DT_CENTER);

    if (hfntOld) {
        SelectObject(hdcMem, hfntOld);
    }

	BitBlt(hdc,
           rc.left, rc.top,
           rc.right-rc.left, rc.bottom-rc.top,
           hdcMem,
           0, 0,
           SRCCOPY);

    SelectObject(hdcMem, hbmOld);
    DeleteObject(hbmMem);
    DeleteDC(hdcMem);
	ReleaseDC(hWnd,hdc);
}
