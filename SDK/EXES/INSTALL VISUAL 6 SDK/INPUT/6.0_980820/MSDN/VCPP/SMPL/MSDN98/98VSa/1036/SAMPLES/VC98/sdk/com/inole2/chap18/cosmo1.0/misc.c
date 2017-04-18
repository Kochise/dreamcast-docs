/*
 * MISC.C
 *
 * Functions without any other reasonable home:
 *  WindowTitleSet, RectConvertToHiMetric, RectConvertToDevice
 *
 * Copyright(c) Microsoft Corp. 1992-1994 All Rights Reserved
 * Win32 version, January 1994
 */


#include <windows.h>
#include <ole.h>
#include "cosmo.h"




/*
 * WindowTitleSet
 *
 * Purpose:
 *  Handles changing the window's caption bar depending on the file
 *  that is loaded.
 *
 * Parameters:
 *  hWnd            HWND of the window to change.
 *  pszFile         LPSTR of the file loaded.
 *
 * Return Value:
 *  none.
 */

void WINAPI WindowTitleSet(HWND hWnd, LPSTR pszFile)
    {
    char        szTitle[CCHPATHMAX];

    wsprintf(szTitle, "%s - %s", (LPSTR)rgpsz[IDS_CAPTION], pszFile);
    SetWindowText(hWnd, szTitle);
    return;
    }







/*
 * RectConvertToHiMetric
 *
 * Purpose:
 *  Converts the contents of a rectangle from MM_TEXT into MM_HIMETRIC
 *  specifically for use in converting a RECT of a window into
 *  a RECT for a METAFILEPICT structure.
 *
 * Parameters:
 *  hWnd            HWND of the window providing the display context
 *  pRect           LPRECT containing the rectangle to convert.
 *
 * Return Value:
 *  None.
 */

void WINAPI RectConvertToHiMetric(HWND hWnd, LPRECT pRect)
    {
    HDC      hDC;
    POINT    pt;

    hDC=GetDC(hWnd);
    SetMapMode(hDC, MM_HIMETRIC);

    //Convert upper left corner
    pt.x=pRect->left;
    pt.y=pRect->top;
    DPtoLP(hDC, &pt, 1);
    pRect->left=pt.x;
    pRect->top=-pt.y;

    //Convert lower right corner
    pt.x=pRect->right;
    pt.y=pRect->bottom;
    DPtoLP(hDC, &pt, 1);
    pRect->right=pt.x;
    pRect->bottom=-pt.y;

    ReleaseDC(hWnd, hDC);
    return;
    }







/*
 * RectConvertToDevice
 *
 * Purpose:
 *  Converts the contents of a rectangle from MM_HIMETRIC into MM_TEXT
 *  specifically for use in converting a RECT of an OLE object into
 *  a RECT for a window.
 *
 * Parameters:
 *  hWnd            HWND of the window providing the display context
 *  pRect           LPRECT containing the rectangle to convert.
 *
 * Return Value:
 *  None.
 */

void WINAPI RectConvertToDevice(HWND hWnd, LPRECT pRect)
    {
    HDC      hDC;
    POINT    pt;

    hDC=GetDC(hWnd);
    SetMapMode(hDC, MM_HIMETRIC);

    //Convert upper left corner
    pt.x=pRect->left;
    pt.y=pRect->bottom;
    LPtoDP(hDC, &pt, 1);
    pRect->left=pt.x;
    pRect->bottom=pt.y;

    //Convert lower right corner
    pt.x=pRect->right;
    pt.y=pRect->top;
    LPtoDP(hDC, &pt, 1);
    pRect->right=pt.x;
    pRect->top=pt.y;

    ReleaseDC(hWnd, hDC);
    return;
    }
