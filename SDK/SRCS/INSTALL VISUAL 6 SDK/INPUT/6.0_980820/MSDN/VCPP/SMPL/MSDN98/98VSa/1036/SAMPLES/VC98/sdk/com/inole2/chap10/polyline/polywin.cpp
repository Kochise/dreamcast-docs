/*
 * POLYWIN.CPP
 * Polyline Component Chapter 10
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

            //New repaints this window, so store the hWnd here.
            ppl->m_hWnd=hWnd;
            ppl->m_pImpIPolyline->New();
            break;


        case WM_PAINT:
            hDC=BeginPaint(hWnd, &ps);
            ppl->Draw(hDC, FALSE, TRUE);
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
            ppl->Draw(hDC, FALSE, FALSE);
            ReleaseDC(hWnd, hDC);

            if (NULL!=ppl->m_pAdv)
                ppl->m_pAdv->OnPointChange();

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
 *
 * Return Value:
 *  None
 */

void CPolyline::Draw(HDC hDC, BOOL fMetafile, BOOL fEntire)
    {
    HBRUSH          hBrush;
    HPEN            hPen;
    HGDIOBJ         hObj1, hObj2;
    UINT            i, j;
    UINT            uMM;
    POINTS          pt1, pt2;
    POINT           rgpt[CPOLYLINEPOINTS];
    RECT            rc;

    GetClientRect(m_hWnd, &rc);

    /*
     * Make a 32-bit copy of the points in the POLYLINE itself
     * so we can use DPtoLP and LPtoDP.
     */
    for (i=0; i < m_pl.cPoints; i++)
        {
        rgpt[i].x=m_pl.rgpt[i].x;
        rgpt[i].y=m_pl.rgpt[i].y;
        }

    /*
     * If the mapping mode is not MM_TEXT, convert the points to
     * whatever mapping mode in in effect before drawing.
     * This specifically supports metafiles in MM_ANISOTROPIC.
     */
    uMM=fMetafile ? MM_TEXT : GetMapMode(hDC);

    if (MM_TEXT!=uMM)
        DPtoLP(hDC, rgpt, m_pl.cPoints);

    hPen=CreatePen(m_pl.iLineStyle, 1, m_pl.rgbLine);
    hObj1=SelectObject(hDC, hPen);

    hBrush=CreateSolidBrush(m_pl.rgbBackground);
    hObj2=SelectObject(hDC, hBrush);
    SetBkColor(hDC, m_pl.rgbBackground);

    /*
     * Either draw the entire figure or just a single point.  The
     * entire figure also includes erasing the background
     * completely, since hDC may be a metafile DC.  Drawing a single
     * point just updates the figure for that new point.
     */
    if (fEntire || 0==m_pl.cPoints)
        {
        //Erase the background for bitmaps and metafiles.
        SelectObject(hDC, GetStockObject(NULL_PEN));
        Rectangle(hDC, rc.left, rc.top, rc.right+1, rc.bottom+1);
        SelectObject(hDC, hPen);


        /*
         * If we are drawing the entire figure, then loop through
         * each point drawing a line to each successive point.
         */

        for (i=0; i < m_pl.cPoints; i++)
            {
            for (j=i; j < m_pl.cPoints; j++)
                {
                pt1.x=(short)rgpt[i].x;
                pt1.y=(short)rgpt[i].y;
                pt2.x=(short)rgpt[j].x;
                pt2.y=(short)rgpt[j].y;

                PointScale(&rc, &pt1, TRUE);
                PointScale(&rc, &pt2, TRUE);
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
        j=m_pl.cPoints-1;
        pt1.x=(short)rgpt[j].x;
        pt1.y=(short)rgpt[j].y;
        PointScale(&rc, &pt1, TRUE);

        for (i=0; i < j; i++)
            {
            pt2.x=(short)rgpt[i].x;
            pt2.y=(short)rgpt[i].y;
            PointScale(&rc, &pt2, TRUE);

            MoveToEx(hDC, pt1.x, pt1.y, NULL);
            LineTo(hDC, pt2.x, pt2.y);
            }
        }

    //If we have one point, draw a dot to indicate it's position.
    if (1==m_pl.cPoints)
        {
        pt1.x=(short)rgpt[0].x;
        pt1.y=(short)rgpt[0].y;
        PointScale(&rc, &pt1, TRUE);
        SetPixel(hDC, pt1.x, pt1.y, m_pl.rgbLine);
        }

    //Restore original points.
    if (MM_TEXT!=uMM)
        LPtoDP(hDC, rgpt, m_pl.cPoints);

    SelectObject(hDC, hObj1);
    SelectObject(hDC, hObj2);
    DeleteObject(hBrush);
    DeleteObject(hPen);
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
    if (fScaleToWindow)
        {
        ppt->x=(UINT)(((DWORD)ppt->x*cx) >> 15);
        ppt->y=(UINT)(((DWORD)ppt->y*cy) >> 15);
        }
    else
        {
        ppt->x=(UINT)(((DWORD)ppt->x << 15)/cx);
        ppt->y=(UINT)(((DWORD)ppt->y << 15)/cy);
        }

    return;
    }
