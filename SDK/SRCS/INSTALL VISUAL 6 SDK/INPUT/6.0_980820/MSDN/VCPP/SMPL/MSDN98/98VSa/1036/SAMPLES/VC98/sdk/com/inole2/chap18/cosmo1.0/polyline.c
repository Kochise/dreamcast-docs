/*
 * POLYLINE.C
 *
 * Window procedure for the polyline drawing window and support functions.
 * This window is not complicated.  On creation it allocates a block of
 * memory for a POLYLINE structure that contains 20 POINTs.  We do not
 * attempt to reallocate this array at all just to maintain simplicity.
 * This sample is to demonstrate OLE, not LocalReAlloc.
 *
 * Copyright(c) Microsoft Corp. 1992-1994 All Rights Reserved
 * Win32 version, January 1994
 */


#include <windows.h>
#include "cosmo.h"

/*
 * HACK:  To fix some Invalid hDC rips, we need to supress certain
 * operations on metafile DC's: GetMapMode, DPtoLP, LPtoDP.
 * We use this flag to indicate supression.
 */
BOOL fMetaDC=FALSE;



/*
 * HPolylineWindowCreate
 *
 * Purpose:
 *  Creates a Polyline window within the client area of hWndParent.
 *
 * Parameters:
 *  hWndParent      HWND of the parent window.
 *  hInstance       HINSTANCE of the application instance.
 *
 * Return Value:
 *  HWND            Result of the CreateWindowEx call.
 *
 */

HWND WINAPI HPolylineWindowCreate(HWND hWndParent, HINSTANCE hInstance)
    {
    RECT        rc;
    HWND        hWndT;

    /*
     * Create the secondary window for this application in a
     * shrunk client area.
     */
    GetClientRect(hWndParent, &rc);
    InflateRect(&rc, -8, -8);

    //Create the editor window.
    hWndT=CreateWindowEx(WS_EX_NOPARENTNOTIFY, rgpsz[IDS_CLASSPOLYLINE]
        , rgpsz[IDS_CLASSPOLYLINE], WS_CHILD | WS_VISIBLE, rc.left
        , rc.top, rc.right-rc.left, rc.bottom-rc.top
        , hWndParent, (HMENU)ID_POLYLINE, hInstance, NULL);

    return hWndT;
    }





/*
 * PolylineWndProc
 *
 * Purpose:
 *  Window procedure for the polyline drawing window.
 *
 * Parameters:
 *  The standard.
 *
 * Return Value:
 *  Standard.
 */

LRESULT WINAPI PolylineWndProc(HWND hWnd, UINT iMsg
    , WPARAM wParam, LPARAM lParam)
    {
    PAINTSTRUCT     ps;
    HDC             hDC;
    HWND            hWndParent;
    HLOCAL          hMem;
    LPPOLYLINE      ppl;
    RECT            rc;
    DWORD           dwRet=0L;

   #ifdef WIN32
    ppl=(LPPOLYLINE)(PSTR)GetWindowLong(hWnd, 0);
   #else
    ppl=(LPPOLYLINE)(PSTR)GetWindowWord(hWnd, 0);
   #endif

    if (WM_USER <= iMsg)
        return LPolylineUserMessage(hWnd, iMsg, wParam, lParam, ppl);


    switch (iMsg)
        {

        case WM_NCCREATE:
            hMem=LocalAlloc(LPTR, CBPOLYLINE);

            if (NULL==hMem)
                return 0L;

           #ifdef WIN32
            SetWindowLong(hWnd, 0, (LONG)hMem);
           #else
            SetWindowWord(hWnd, 0, (WORD)hMem);
           #endif
            return DefWindowProc(hWnd, iMsg, wParam, lParam);


        case WM_NCDESTROY:
           #ifdef WIN32
            hMem=(HLOCAL)GetWindowLong(hWnd, 0);
           #else
            hMem=(HLOCAL)GetWindowWord(hWnd, 0);
           #endif
            LocalFree(hMem);
            return DefWindowProc(hWnd, iMsg, wParam, lParam);


        case WM_CREATE:
            //Stash away the current window rectangle.
            GetClientRect(hWnd, &rc);
            RECTTORECTS(rc, ppl->rc);

            ppl->wVerMaj=VERSIONMAJOR;
            ppl->wVerMin=VERSIONMINOR;
            ppl->cPoints=0;
            break;


        case WM_PAINT:
            hDC=BeginPaint(hWnd, &ps);

            if (0!=ppl->cPoints)
                {
                ppl->fDrawEntire=TRUE;
                PolylineDraw(hWnd, hDC, ppl);
                }

            EndPaint(hWnd, &ps);
            break;

        case WM_LBUTTONDOWN:
            //Stop if we are already at the limit.
            if (CPOLYLINEPOINTS==ppl->cPoints)
                {
                MessageBeep(0);
                break;
                }

            //Stuff the new point in the array.
            ppl->rgpt[ppl->cPoints].x=LOWORD(lParam);
            ppl->rgpt[ppl->cPoints].y=HIWORD(lParam);

            ppl->cPoints++;

            //Draw the lines to this new point only.
            hDC=GetDC(hWnd);

            ppl->fDrawEntire=FALSE;
            PolylineDraw(hWnd, hDC, ppl);

            ReleaseDC(hWnd, hDC);

            hWndParent=GetParent(hWnd);

           #ifdef WIN32
            SendMessage(hWndParent, WM_COMMAND
                , MAKELONG(ID_POLYLINE, PLN_POINTCHANGE), (LPARAM)hWnd);
           #else
            SendMessage(hWndParent, WM_COMMAND
                , ID_POLYLINE, MAKELONG(hWnd, PLN_POINTCHANGE));
           #endif
            break;


        default:
            dwRet=DefWindowProc(hWnd, iMsg, wParam, lParam);
            break;
        }

    return dwRet;
    }







/*
 * LPolylineUserMessage
 *
 * Purpose:
 *  Handles all window-specific messages WM_USER and greater,
 *  for the Polyline window:
 *
 *  PLM_RECTSET:        Changes the size of the window and scales the
 *                      data points.
 *
 *  PLM_POLYLINESET:    Sets the current data points and the rectangle
 *                      used to generate the figure.
 *
 *  PLM_POLYLINEGET:    Retrieves the current data points and rectangle
 *                      used to generate the figure.
 *
 *  PLM_POLYLINENEW:    Resets the data points to defaults, meaning
 *                      a blank figure.
 *
 *  PLM_BACKUPUNDO:     Backs the figure up one point.
 *
 *  PLM_BITMAPGET:      Retrieves a bitmap (DDB) of the current image.
 *
 *  PLM_METAFILEGET:    Retrieves a metafile for the current image.
 *
 *  PLM_METAFILEPICTGET:Retrieves a METAFILEPICT structure of the image for
 *                      use in clipboard I/O.
 *
 * Parameters:
 *  hWnd            HWND of the Polyline window.
 *  iMsg            UINT message to process.
 *  wParam          WPARAM parameter of the message.
 *  lParam          LPARAM pameter of the message.
 *  ppl             LPPOLYLINE to the window's extra data structure.
 *
 * Return Value:
 *  DWORD           Value to return from the window procedure
 *                  that recieved the message.
 */

DWORD PASCAL LPolylineUserMessage(HWND hWnd, UINT iMsg, WPARAM wParam
    , LPARAM lParam, LPPOLYLINE ppl)
    {
    DWORD           dwRet=0L;
    HWND            hWndParent;
    HBITMAP         hBmp, hBmpT;
    HDC             hDC, hMemDC;
    LPPOLYLINE      pplT;
    LPMETAFILEPICT  pMF;
    HGLOBAL         hMem;
    HMETAFILE       hMF;
    RECT            rc;
    LPRECT          pRect;
    UINT            i;
    LONG            l, cx, cy, cxT, cyT;

    hWndParent=GetParent(hWnd);

    switch (iMsg)
        {
        case PLM_RECTSET:
            /*
             * Resize the window to the given size, letting WM_SIZE handlers
             * take care of the rest.
             */
            pRect=(LPRECT)lParam;

            /*
             * Scale all the current points to new dimensions.  ppl->rc
             * has the old dimensions, pRect points to the new.  We
             * force each of cx and cy to 1 if they are zero to prevent
             * exceptions.
             */

            RECTSTORECT(ppl->rc, rc);
            cxT=rc.right  - rc.left;
            cyT=rc.bottom - rc.top;

            RECTTORECTS(ppl->rc, *pRect);
            cx=pRect->right  - pRect->left;
            cy=pRect->bottom - pRect->top;

            //Prevent crashes
            if (0L==cxT)
                cxT=1;

            if (0L==cyT)
                cyT=1;

            //Loop through each point, scaling if necessary.
            for (i=0; i< ppl->cPoints; i++)
                {
                //Must use DWORD to insure proper scaling.
                if (cx!=cxT)
                    {
                    l=((LONG)ppl->rgpt[i].x*cx);
                    ppl->rgpt[i].x=(short)(l/cxT);
                    }

                if (cy!=cyT)
                    {
                    l=((LONG)ppl->rgpt[i].y*cy);
                    ppl->rgpt[i].y=(short)(l/cyT);
                    }
                }


            SetWindowPos(hWnd, NULL, pRect->left, pRect->top, (int)cx
                , (int)cy, SWP_NOMOVE | SWP_NOZORDER);


            //Check if we need to notify the parent.
            if (0!=wParam)
                {
               #ifdef WIN32
                SendMessage(hWndParent, WM_COMMAND
                    , MAKELONG(ID_POLYLINE, PLN_SIZECHANGE), (LPARAM)hWnd);
               #else
                SendMessage(hWndParent, WM_COMMAND
                    , ID_POLYLINE, MAKELONG(hWnd, PLN_SIZECHANGE));
               #endif
                }

            //Insure repaint
            InvalidateRect(hWnd, NULL, TRUE);
            UpdateWindow(hWnd);
            break;


        case PLM_POLYLINESET:
            /*
             * Copy the structure in lParam to ppl and repaint to
             * reflect the new point set.  Note that unlike the
             * PLM_RECTSET message, we do no scaling, assuming that
             * the rectangle in the POLYLINE structure is appropriate
             * for the data.
             */
            pplT=(LPPOLYLINE)lParam;
            *ppl=*pplT;

            //Resize this window to fit the data and notify the parent.
            SetWindowPos(hWnd, NULL, ppl->rc.left, ppl->rc.top
                , ppl->rc.right-ppl->rc.left, ppl->rc.bottom-ppl->rc.top
                , SWP_NOMOVE | SWP_NOZORDER);

            if (0!=wParam)
                {
               #ifdef WIN32
                SendMessage(hWndParent, WM_COMMAND
                    , MAKELONG(ID_POLYLINE, PLN_SIZECHANGE), (LPARAM)hWnd);
               #else
                SendMessage(hWndParent, WM_COMMAND
                    , ID_POLYLINE, MAKELONG(hWnd, PLN_SIZECHANGE));
               #endif
                }

            //Insure a repaint.
            InvalidateRect(hWnd, NULL, TRUE);
            UpdateWindow(hWnd);
            break;


        case PLM_POLYLINEGET:
            //Copy the structure in ppl to lParam.  No repaint needed.
            pplT=(LPPOLYLINE)lParam;
            *pplT=*ppl;
            break;


        case PLM_POLYLINENEW:
            //Clean out the POLYLINE structure and repaint the window.
            for (i=0; i< CPOLYLINEPOINTS; i++)
                {
                ppl->rgpt[i].x=0;
                ppl->rgpt[i].y=0;
                }

            ppl->cPoints=0;

            InvalidateRect(hWnd, NULL, TRUE);
            UpdateWindow(hWnd);
            break;


        case PLM_BACKUPUNDO:
            //Decrement the number of active points and repaint.
            if (ppl->cPoints > 0)
                {
                ppl->cPoints--;
                InvalidateRect(hWnd, NULL, TRUE);
                UpdateWindow(hWnd);
                }

            //Notify parent window of the change.
           #ifdef WIN32
            SendMessage(hWndParent, WM_COMMAND
                , MAKELONG(ID_POLYLINE, PLN_POINTCHANGE), (LPARAM)hWnd);
           #else
            SendMessage(hWndParent, WM_COMMAND
                , ID_POLYLINE, MAKELONG(hWnd, PLN_POINTCHANGE));
           #endif
            break;


        case PLM_BITMAPGET:
            /*
             * Create and return a bitmap of the window contents.
             * The bitmap is the size of the POLYLINE edit window.
             */

            hDC=GetDC(hWnd);
            hMemDC=CreateCompatibleDC(hDC);

            GetClientRect(hWnd, &rc);
            hBmp=CreateCompatibleBitmap(hDC, rc.right, rc.bottom);

            if (NULL!=hBmp)
                {
                //Draw the POLYLINE into the bitmap.
                hBmpT=SelectObject(hMemDC, hBmp);

                ppl->fDrawEntire=TRUE;
                PolylineDraw(hWnd, hMemDC, ppl);
                ppl->fDrawEntire=FALSE;

                SelectObject(hMemDC, hBmpT);
                }

            DeleteDC(hMemDC);
            ReleaseDC(hWnd, hDC);

            //Return the created bitmap handle.
            dwRet=(DWORD)(UINT)hBmp;
            break;


        case PLM_METAFILEGET:
            //Create a memory metafile and return its handle.
            hDC=(HDC)CreateMetaFile(NULL);
            hMF=NULL;

            if (NULL!=hDC)
                {
                /*
                 * This is absolutely essential to the metafile so it
                 * can be scaled in the clipboard and any destination
                 * application.
                 */
                fMetaDC=TRUE;
                SetMapMode(hDC, MM_ANISOTROPIC);
                GetClientRect(hWnd, &rc);
                SetWindowOrgEx(hDC, 0, 0, NULL);
                SetWindowExtEx(hDC, rc.right, rc.bottom, NULL);

                ppl->fDrawEntire=TRUE;
                PolylineDraw(hWnd, hDC, ppl);
                ppl->fDrawEntire=FALSE;

                hMF=CloseMetaFile(hDC);
                fMetaDC=FALSE;
                }

            dwRet=(DWORD)(UINT)hMF;
            break;


        case PLM_METAFILEPICTGET:
            /*
             * Create a METAFILEPICT structure for the clipboard.
             * First attempt to get a metafile.
             */
            lParam=SendMessage(hWnd, PLM_METAFILEGET, 0, 0L);
            hMF=(HMETAFILE)(UINT)lParam;

            if (NULL==hMF)
                break;

            //Allocate the METAFILEPICT structure.
            hMem=GlobalAlloc(GMEM_DDESHARE | GMEM_MOVEABLE
                , sizeof(METAFILEPICT));

            if (NULL==hMem)
                {
                DeleteMetaFile(hMF);
                break;
                }

            /*
             * Global lock only fails in PMODE if the selector is invalid
             * (like it was discarded) or references a 0 length segment,
             * neither of which can happen here.
             */
            pMF=(LPMETAFILEPICT)GlobalLock(hMem);

            pMF->hMF=hMF;
            pMF->mm=MM_ANISOTROPIC;             //Required by OLE libraries.

            //Insert the extents in MM_HIMETRIC units.
            GetClientRect(hWnd, &rc);

            RectConvertToHiMetric(hWnd, &rc);     //Found in CLIP.C
            pMF->xExt=rc.right;
            pMF->yExt=rc.bottom;

            GlobalUnlock(hMem);

            dwRet=(DWORD)(UINT)hMem;
            break;


        default:
            break;
        }

    return dwRet;
    }






/*
 * PolylineDraw
 *
 * Purpose:
 *  Paints the current line in the polyline window.
 *
 * Parameters:
 *  hWnd            HWND of the polyline window.
 *  hDC             HDC to draw on, could be a metafile or printer DC.
 *  ppl            LPPOLYLINE to the polyline structure.
 *
 * Return Value:
 *  none
 */

void PASCAL PolylineDraw(HWND hWnd, HDC hDC, LPPOLYLINE ppl)
    {

    HBRUSH          hBrush, hBrushT;
    HPEN            hPen, hPenT;
    UINT            i, j;
    UINT            nMM;
    POINTS          pt;
    POINT           rgpt[CPOLYLINEPOINTS];
    RECT            rc;
    COLORREF        cr;


    GetClientRect(hWnd, &rc);

    //Get the line color.
    cr=GetSysColor(COLOR_WINDOWTEXT);

    //Make a 32-bit working copy of the point array for DPtoLP.
    for (i=0; i < ppl->cPoints; i++)
        {
        rgpt[i].x=ppl->rgpt[i].x;
        rgpt[i].y=ppl->rgpt[i].y;
        }

    /*
     * If the mapping mode is not MM_TEXT, convert the points to
     * whatever mapping mode in in effect before drawing.
     * This specifically supports metafiles in MM_ANISOTROPIC.
     */
    nMM=fMetaDC ? MM_TEXT : GetMapMode(hDC);

    if (MM_TEXT!=nMM)
        DPtoLP(hDC, rgpt, ppl->cPoints);

    hPen=CreatePen(PS_SOLID, 1, cr);
    hPenT=SelectObject(hDC, hPen);

    hBrush=CreateSolidBrush(GetSysColor(COLOR_WINDOW));
    hBrushT=SelectObject(hDC, hBrush);

    /*
     * Either draw the entire figure or just a single point.  The
     * entire figure also includes erasing the background completely,
     * since hDC may be a metafile DC.  Drawing a single point just
     * updates the figure for that new point.
     */
    if (ppl->fDrawEntire)
        {
        //Erase the background for bitmaps and metafiles.
        SelectObject(hDC, GetStockObject(NULL_PEN));
        Rectangle(hDC, rc.left, rc.top, rc.right+1, rc.bottom+1);
        SelectObject(hDC, hPen);


        /*
         * If we are drawing the entire figure, then loop through each
         * point drawing a line to each successive point.
         */

        for (i=0; i < ppl->cPoints; i++)
            {
            for (j=i; j < ppl->cPoints; j++)
                {
                MoveToEx(hDC, rgpt[i].x, rgpt[i].y, NULL);
                LineTo(hDC, rgpt[j].x, rgpt[j].y);
                }
            }
        }
    else
        {
        /*
         * If we are only drawing the last point, just cycle once
         * through previous points.
         */

        //Get the last point entered in the array.
        j=ppl->cPoints-1;
        pt.x=(short)rgpt[j].x;
        pt.y=(short)rgpt[j].y;

        for (i=0; i < j; i++)
            {
            MoveToEx(hDC, pt.x, pt.y, NULL);
            LineTo(hDC, rgpt[i].x, rgpt[i].y);
            }
        }

    //If we only had one point, draw a dot to indicate it's position.
    if (1==ppl->cPoints)
        SetPixel(hDC, rgpt[0].x, rgpt[0].y, cr);


    SelectObject(hDC, hPenT);
    SelectObject(hDC, hBrushT);
    DeleteObject(hBrush);
    DeleteObject(hPen);
    return;
    }
