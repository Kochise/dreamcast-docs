/*
 * POLYWIN.CPP
 * Polyline Component Chapter 21
 *
 * Window procedure for the polyline drawing window and support
 * functions.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#include "polyline.h"


/*
 * PolylineWndProc
 *
 * Purpose:
 *  Window procedure for the polyline drawing window.
 */

LRESULT APIENTRY PolylineWndProc(HWND hWnd, UINT iMsg
    , WPARAM wParam, LPARAM lParam)
    {
    PCPolyline      ppl;
    PAINTSTRUCT     ps;
    HDC             hDC;
    POINTS          pt;
    RECT            rc;

    ppl=(PCPolyline)GetWindowLong(hWnd, PLWL_STRUCTURE);

    switch (iMsg)
        {
        case WM_CREATE:
            ppl=(PCPolyline)((LPCREATESTRUCT)lParam)->lpCreateParams;
            SetWindowLong(hWnd, PLWL_STRUCTURE, (LONG)ppl);
            ppl->m_hWnd=hWnd;
            break;


        case WM_PAINT:
            hDC=BeginPaint(hWnd, &ps);
            GetClientRect(hWnd, &rc);
            ppl->Draw(hDC, FALSE, TRUE, &rc, NULL);
            EndPaint(hWnd, &ps);
            break;


        case WM_LBUTTONDOWN:
            //Stop if we are already at the limit.
            if (CPOLYLINEPOINTS==ppl->m_pl.cPoints)
                {
                MessageBeep(0);
                break;
                }

            //Convert the points into 0-32767 range
            GetClientRect(hWnd, &rc);
            pt=MAKEPOINTS(lParam);
            ppl->PointScale(&rc, &pt, FALSE);

            ppl->m_pl.rgpt[ppl->m_pl.cPoints++]=pt;

            //Draw the lines to this new point only.
            hDC=GetDC(hWnd);
            ppl->Draw(hDC, FALSE, FALSE, &rc, NULL);
            ReleaseDC(hWnd, hDC);

            if (NULL!=ppl->m_pAdv)
                ppl->m_pAdv->OnPointChange();

            ppl->SendAdvise(OBJECTCODE_DATACHANGED);
            break;


        default:
            return DefWindowProc(hWnd, iMsg, wParam, lParam);
        }

    return 0L;
    }







/*
 * CPolyline::Draw
 *
 * Purpose:
 *  Paints the current line in the polyline window.
 *
 * Parameters:
 *  hDC             HDC to draw on, a metafile or printer DC.
 *  fMetafile       BOOL indicating if hDC is a metafile or not,
 *                  so we can avoid operations that RIP.
 *  fEntire         BOOL indicating if we should draw the entire
 *                  figure or not.
 *  pRect           LPRECT defining the bounds in which to draw.
 *  ppl             PPOLYLINEDATA to draw.  If NULL, use current.
 *
 * Return Value:
 *  None
 */

void CPolyline::Draw(HDC hDC, BOOL fMetafile, BOOL fEntire
    , LPRECT pRect, PPOLYLINEDATA ppl)
    {
    HBRUSH          hBrush;
    HPEN            hPen;
    HGDIOBJ         hObj1, hObj2;
    UINT            i, j;
    int             nDC;
    POINTS          pt1,pt2;
    POINT           rgpt[CPOLYLINEPOINTS];

    if (NULL==ppl)
        ppl=&m_pl;

    nDC=SaveDC(hDC);

    for (i=0; i < ppl->cPoints; i++)
        {
        rgpt[i].x=ppl->rgpt[i].x;
        rgpt[i].y=ppl->rgpt[i].y;
        }

    //Printer and frozen differences handled in IViewObject::Draw

    hPen=CreatePen(ppl->iLineStyle, 1, ppl->rgbLine);
    hObj1=SelectObject(hDC, hPen);

    hBrush=CreateSolidBrush(ppl->rgbBackground);
    hObj2=SelectObject(hDC, hBrush);
    SetBkColor(hDC, ppl->rgbBackground);

    /*
     * Either draw the entire figure or just a single point.  The
     * entire figure also includes erasing the background completely,
     * since hDC may be a metafile DC.  Drawing a single point just
     * updates the figure for that new point.
     */
    if (fEntire || 0==ppl->cPoints)
        {
        //Erase the background for bitmaps and metafiles.
        SelectObject(hDC, GetStockObject(NULL_PEN));
        Rectangle(hDC, pRect->left, pRect->top, pRect->right+1
            , pRect->bottom+1);
        SelectObject(hDC, hPen);

        /*
         * If we are drawing the entire figure, then loop through
         * each point drawing a line to each successive point.
         */

        for (i=0; i < ppl->cPoints; i++)
            {
            for (j=i; j < ppl->cPoints; j++)
                {
                pt1.x=(short)rgpt[i].x;
                pt1.y=(short)rgpt[i].y;
                pt2.x=(short)rgpt[j].x;
                pt2.y=(short)rgpt[j].y;

                PointScale(pRect, &pt1, TRUE);
                PointScale(pRect, &pt2, TRUE);
                MoveToEx(hDC, pt1.x, pt1.y, NULL);
                LineTo(hDC, pt2.x, pt2.y);
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
        pt1.x=(short)rgpt[j].x;
        pt1.y=(short)rgpt[j].y;
        PointScale(pRect, &pt1, TRUE);

        for (i=0; i < j; i++)
            {
            pt2.x=(short)rgpt[i].x;
            pt2.y=(short)rgpt[i].y;
            PointScale(pRect, &pt2, TRUE);

            MoveToEx(hDC, pt1.x, pt1.y, NULL);
            LineTo(hDC, pt2.x, pt2.y);
            }
        }

    //If we have one point, draw a dot to indicate it's position.
    if (1==ppl->cPoints)
        {
        pt1.x=(short)rgpt[0].x;
        pt1.y=(short)rgpt[0].y;
        PointScale(pRect, &pt1, TRUE);
        SetPixel(hDC, pt1.x, pt1.y, m_pl.rgbLine);
        }

    SelectObject(hDC, hObj1);
    SelectObject(hDC, hObj2);
    DeleteObject(hBrush);
    DeleteObject(hPen);

    RestoreDC(hDC, nDC);
    return;
    }







/*
 * CPolyline::PointScale
 *
 * Purpose:
 *  Scales a point to or from a relative window coordinate to a
 *  0-32767 coordinate.
 *
 * Parameters:
 *  pRect           LPRECT of the window.
 *  ppt             LPPOINTS to convert
 *  fScaleToWindow  BOOL indicating direction of scaling.
 *
 * Return Value:
 *  None
 */

void CPolyline::PointScale(LPRECT pRect, LPPOINTS ppt
    , BOOL fScaleToWindow)
    {
    DWORD   cx, cy;

    //Window size
    cx=(DWORD)(pRect->right-pRect->left);
    cy=(DWORD)(pRect->bottom-pRect->top);

    //Prevent crashes
    if (0L==cx) cx=1;
    if (0L==cy) cy=1;

    //Must use DWORD to insure proper scaling.

    /*
     * As an in-proc server we may not have a rectangle where the
     * top left was (0,0) which was always true when we drew to
     * a Polyline window.  But this may be a container's hDC in
     * which case we'd better place the points in the container's
     * rectangle.  That is, we have to add/subtract pRect->left
     * and ->top in these calculations.
     */

    if (fScaleToWindow)
        {
        ppt->x=pRect->left+(UINT)(((DWORD)ppt->x*cx) >> 15);
        ppt->y=pRect->top+(UINT)(((DWORD)ppt->y*cy)  >> 15);
        }
    else
        {
        ppt->x=(UINT)(((DWORD)(ppt->x - pRect->left) << 15)/cx);
        ppt->y=(UINT)(((DWORD)(ppt->y - pRect->top)  << 15)/cy);
        }

    return;
    }



/*
 * PolyDlgProc
 *
 * Purpose:
 *  Dialog procedure for a window in which to display the Polyline
 *  for editing.  This pretty much handles all editing functionality
 *  for the embedded object.
 */

BOOL APIENTRY PolyDlgProc(HWND hDlg, UINT iMsg
    , WPARAM wParam, LPARAM lParam)
    {
    PCPolyline      ppl=NULL;
    HWND            hWnd;
    RECT            rc;
    POINT           pt;
    UINT            uID, uTemp;
    UINT            cx, cy;

   #ifdef WIN32
    ppl=(PCPolyline)GetProp(hDlg, PROP_POINTER);
   #else
    WORD            w1, w2;

    w1=(WORD)GetProp(hDlg, PROP_SELECTOR);
    w2=(WORD)GetProp(hDlg, PROP_OFFSET);

    ppl=(PCPolyline)MAKELP(w1, w2);
   #endif

    switch (iMsg)
        {
        case WM_INITDIALOG:
            ppl=(PCPolyline)lParam;
            ppl->m_hDlg=hDlg;

           #ifdef WIN32
            //Properties are 32-bits in Win32
            SetProp(hDlg, PROP_POINTER, (HANDLE)ppl);
           #else
            SetProp(hDlg, PROP_SELECTOR, (HANDLE)SELECTOROF(ppl));
            SetProp(hDlg, PROP_OFFSET,   (HANDLE)OFFSETOF(ppl));
           #endif

            //Create the Polyline to exactly cover the static rect.
            hWnd=GetDlgItem(hDlg, ID_POLYLINERECT);
            GetWindowRect(hWnd, &rc);
            SETPOINT(pt, rc.left, rc.top);
            ScreenToClient(hDlg, &pt);

            //Set the polyline just within the black frame
            SetRect(&rc, pt.x, pt.y, pt.x+(rc.right-rc.left)
                , pt.y+(rc.bottom-rc.top));
            InflateRect(&rc, -1, -1);

            //Try to create the window.
            ppl->m_pImpIPolyline->Init(hDlg, &rc, WS_CHILD | WS_VISIBLE
                , ID_POLYLINE);

            //Set the initial line style radiobutton.
            ppl->m_pImpIPolyline->LineStyleGet(&uTemp);
            CheckRadioButton(hDlg, ID_LINESOLID, ID_LINEDASHDOTDOT
                , uTemp+ID_LINEMIN);

            //Don't set focus--it takes it away from the container.
            return FALSE;


        case WM_SHOWWINDOW:
            if (LOWORD(wParam))
                {
                //Center the dialog on the screen
                cx=GetSystemMetrics(SM_CXSCREEN);
                cy=GetSystemMetrics(SM_CYSCREEN);
                GetWindowRect(hDlg, &rc);
                SetWindowPos(hDlg, NULL, (cx-(rc.right-rc.left))/2
                    , (cy-(rc.bottom-rc.top))/2, 0, 0, SWP_NOZORDER
                    | SWP_NOSIZE);

                //We didn't SetFocus from WM_INITDIALOG.  Do it now.
                SetFocus(GetDlgItem(hDlg, IDOK));
                }

            break;


        case WM_COMMAND:
            uID=LOWORD(wParam);

            switch (uID)
                {
                case IDOK:
                    //Close the dialog, but save first.
                    if (NULL!=ppl)
                        {
                        //IOleObject::Close does what we want
                        ppl->m_pImpIOleObject->Close
                            (OLECLOSE_SAVEIFDIRTY);
                        }

                    break;

                case ID_UNDO:
                    if (NULL!=ppl)
                        ppl->m_pImpIPolyline->Undo();
                    break;

                case ID_COLORLINE:
                case ID_COLORBACK:
                    if (NULL!=ppl)
                        {
                        UINT            i;
                        COLORREF        rgColors[16];
                        CHOOSECOLOR     cc;

                        //Invoke the color chooser for either color
                        uTemp=(ID_COLORBACK==uID)
                            ? POLYLINECOLOR_BACKGROUND
                            : POLYLINECOLOR_LINE;

                        for (i=0; i<16; i++)
                            rgColors[i]=RGB(0, 0, i*16);

                        memset(&cc, 0, sizeof(CHOOSECOLOR));
                        cc.lStructSize=sizeof(CHOOSECOLOR);
                        cc.lpCustColors=rgColors;
                        cc.hwndOwner=hDlg;
                        cc.Flags=CC_RGBINIT;
                        ppl->m_pImpIPolyline->ColorGet(uTemp
                            , &cc.rgbResult);

                        if (ChooseColor(&cc))
                            {
                            //rgColor is just some COLORREF pointer
                            ppl->m_pImpIPolyline->ColorSet(uTemp
                                , cc.rgbResult, rgColors);
                            }
                        }
                    break;

                case ID_LINESOLID:
                case ID_LINEDASH:
                case ID_LINEDOT:
                case ID_LINEDASHDOT:
                case ID_LINEDASHDOTDOT:
                    if (NULL!=ppl)
                        {
                        ppl->m_pImpIPolyline
                            ->LineStyleSet(uID-ID_LINEMIN, &uTemp);
                        }

                    break;
                }
            break;

        case WM_DESTROY:
           #ifdef WIN32
            RemoveProp(hDlg, PROP_POINTER);
           #else
            RemoveProp(hDlg, PROP_SELECTOR);
            RemoveProp(hDlg, PROP_OFFSET);
           #endif
            break;

        case WM_CLOSE:
            //This will do the IDOK handling, then send POLYM_CLOSE
            SendCommand(hDlg, IDOK, 0, NULL);
            break;

        case POLYM_CLOSE:
            ShowWindow(hDlg, SW_HIDE);
            ppl->SendAdvise(OBJECTCODE_HIDEWINDOW);
            break;
        }

    return FALSE;
    }
