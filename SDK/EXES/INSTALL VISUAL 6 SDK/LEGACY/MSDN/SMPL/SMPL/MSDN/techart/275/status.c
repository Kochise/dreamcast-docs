// COPYRIGHT:
//
//   (C) Copyright Microsoft Corp. 1993.  All rights reserved.
//
//   You have a royalty-free right to use, modify, reproduce and
//   distribute the Sample Files (and/or any modified version) in
//   any way you find useful, provided that you agree that
//   Microsoft has no warranty obligations or liability for any
//   Sample Application Files which are modified.
//
/*
    status.c

    Functions to support the status window

*/

#include <windows.h>

//
// Constants
//

#define MAXLISTLINES    100     // max list lines we keep

//
// Global data
//

HWND hwndStatus;

//
// function to add a string to the end of the status list
//

void cdecl Status(LPSTR lpFormat, ...) 
{
    int i;
    char buf[256];

    //
    // format the string
    //

    wvsprintf(buf, lpFormat, (LPSTR)(&lpFormat+1));

    //
    // stop the listbox repaints while we mess with it
    //

    SendMessage(hwndStatus, WM_SETREDRAW, (WPARAM) FALSE, (LPARAM) 0);

    //
    // get the item count
    //

    i = (int) SendMessage(hwndStatus, LB_GETCOUNT, (WPARAM) 0, (LPARAM) 0);
    if (i == LB_ERR) i = 0;

    //
    // scrub a few if we have too many
    //

    while (i >= MAXLISTLINES) {
        SendMessage(hwndStatus, LB_DELETESTRING, (WPARAM) 0, (LPARAM) 0);
        i--;
    }

    //
    // add the new one on at the end and scroll it into view
    //

    i = (int) SendMessage(hwndStatus, LB_ADDSTRING, (WPARAM) 0, (LPARAM) (LPSTR) buf);
    SendMessage(hwndStatus, LB_SETCURSEL, (WPARAM) i, (LPARAM) 0);

    //
    // enable the repaint now
    //

    SendMessage(hwndStatus, WM_SETREDRAW, (WPARAM) TRUE, (LPARAM) 0);
}

//
// Measure an item in our status listbox
//

void MeasureStatusItem(HWND hWnd, LPMEASUREITEMSTRUCT lpMIS)
{
    TEXTMETRIC tm;
    HDC hDC;


    hDC = GetDC(hWnd);
    GetTextMetrics(hDC, &tm);
    ReleaseDC(hWnd, hDC);
    lpMIS->itemHeight = tm.tmHeight;
}

//
// Display an item in one of our owner draw list boxes
//

void DrawStatusItem(HWND hWnd, LPDRAWITEMSTRUCT lpDI)
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
