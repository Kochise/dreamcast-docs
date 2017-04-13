/*
 * PAGEWIN.CPP
 * Patron Chapter 13
 *
 * Window procedure for the Pages window and support functions.
 * This window manages its own scrollbars and viewport and provides
 * printing capabilities as well.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#include "patron.h"


/*
 * PagesWndProc
 *
 * Purpose:
 *  Window procedure for the Pages window.
 */

LRESULT APIENTRY PagesWndProc(HWND hWnd, UINT iMsg, WPARAM wParam
    , LPARAM lParam)
    {
    PCPages         ppg;
    PAINTSTRUCT     ps;
    HDC             hDC;
    int             iPos, iTmp;
    int             iMin, iMax;
    UINT            idScroll;
    BOOL            fDirty=FALSE;

    ppg=(PCPages)GetWindowLong(hWnd, PAGEWL_STRUCTURE);

    switch (iMsg)
        {
        case WM_CREATE:
            ppg=(PCPages)((LPCREATESTRUCT)lParam)->lpCreateParams;
            SetWindowLong(hWnd, PAGEWL_STRUCTURE, (LONG)ppg);

            ppg->m_hWnd=hWnd;
            break;


        case WM_PAINT:
            //CHAPTER13MOD
            /*
             * If there is currently a drag-rectangle showing, then
             * remove it before painting.  This insures that
             * painting doesn't blast part of that rectangle away so
             * that when we draw it next, garbage is left around.
             */
            if (ppg->m_fDragRectShown)
                ppg->DrawDropTargetRect(NULL, NULL);
            //End CHAPTER13MOD

            hDC=BeginPaint(hWnd, &ps);

            //Draw only if we have a page to show.
            if (0!=ppg->m_cPages)
                ppg->Draw(hDC, FALSE, FALSE);

            EndPaint(hWnd, &ps);

            //CHAPTER13MOD
            //Turn the rectangle back on, if necessary.
            if (ppg->m_fDragRectShown)
                ppg->DrawDropTargetRect(NULL, NULL);
            //End CHAPTER13MOD
            break;


        case WM_HSCROLL:
        case WM_VSCROLL:
            idScroll=(WM_HSCROLL==iMsg) ? SB_HORZ : SB_VERT;

            iPos=GetScrollPos(hWnd, idScroll);
            iTmp=iPos;
            GetScrollRange(hWnd, idScroll, &iMin, &iMax);

            switch (LOWORD(wParam))
                {
                case SB_LINEUP:     iPos -= 20;  break;
                case SB_PAGEUP:     iPos -=100;  break;
                case SB_LINEDOWN:   iPos += 20;  break;
                case SB_PAGEDOWN:   iPos +=100;  break;

                case SB_THUMBPOSITION:
                    iPos=ScrollThumbPosition(wParam, lParam);
                    break;

                //We don't want scrolling on this message.
                case SB_THUMBTRACK:
                    return 0L;
                }

            iPos=max(iMin, min(iPos, iMax));

            if (iPos!=iTmp)
                {
                //Set the new position and scroll the window
                SetScrollPos(hWnd, idScroll, iPos, TRUE);

                if (SB_HORZ==idScroll)
                    {
                    ppg->m_xPos=iPos;
                    ScrollWindow(hWnd, iTmp-iPos, 0, NULL, NULL);
                    }
                else
                    {
                    ppg->m_yPos=iPos;
                    ScrollWindow(hWnd, 0, iTmp-iPos, NULL, NULL);
                    }
                }

            break;

        case WM_LBUTTONDOWN:
            if (NULL==ppg->m_pPageCur)
                break;

            fDirty=ppg->m_pPageCur->OnLeftDown(wParam
                , LOWORD(lParam), HIWORD(lParam));
            break;

        case WM_LBUTTONUP:
            if (NULL==ppg->m_pPageCur)
                break;

            fDirty=ppg->m_pPageCur->OnLeftUp(wParam
                , LOWORD(lParam), HIWORD(lParam));
            break;

        case WM_LBUTTONDBLCLK:
            if (NULL==ppg->m_pPageCur)
                break;

            fDirty=ppg->m_pPageCur->OnLeftDoubleClick(wParam, LOWORD(lParam)
                , HIWORD(lParam));
            break;

        case WM_MOUSEMOVE:
            if (NULL==ppg->m_pPageCur)
                break;

            ppg->m_pPageCur->OnMouseMove(wParam, LOWORD(lParam)
                , HIWORD(lParam));
            break;

        case WM_TIMER:
            if (NULL==ppg->m_pPageCur)
                break;

            ppg->m_pPageCur->OnTimer(wParam);
            break;

        case WM_NCHITTEST:
            if (NULL!=ppg->m_pPageCur)
                {
                /*
                 * This just saves information in the page for
                 * OnSetCursor
                 */
                ppg->m_pPageCur->OnNCHitTest(LOWORD(lParam)
                    , HIWORD(lParam));
                }

            return DefWindowProc(hWnd, iMsg, wParam, lParam);

        case WM_SETCURSOR:
            if (NULL!=ppg->m_pPageCur)
                {
                if (ppg->m_pPageCur->OnSetCursor(LOWORD(lParam)))
                    break;
                }

            return DefWindowProc(hWnd, iMsg, wParam, lParam);


        default:
            return DefWindowProc(hWnd, iMsg, wParam, lParam);
        }

    ppg->m_fDirty |= fDirty;
    return 0L;
    }



/*
 * RectConvertMappings
 *
 * Purpose:
 *  Converts the contents of a rectangle from device to logical
 *  coordinates where the hDC defines the logical coordinates.
 *
 * Parameters:
 *  pRect           LPRECT containing the rectangle to convert.
 *  hDC             HDC describing the logical coordinate system.
 *                  if NULL, uses a screen DC in MM_LOMETRIC.
 *  fToDevice       BOOL TRUE to convert from uConv to device,
 *                  FALSE to convert device to uConv.
 *
 * Return Value:
 *  None
 */

void RectConvertMappings(LPRECT pRect, HDC hDC, BOOL fToDevice)
    {
    POINT   rgpt[2];
    BOOL    fSysDC=FALSE;

    if (NULL==pRect)
        return;

    rgpt[0].x=pRect->left;
    rgpt[0].y=pRect->top;
    rgpt[1].x=pRect->right;
    rgpt[1].y=pRect->bottom;

    if (NULL==hDC)
        {
        hDC=GetDC(NULL);
        SetMapMode(hDC, MM_LOMETRIC);
        fSysDC=TRUE;
        }

    if (fToDevice)
        LPtoDP(hDC, rgpt, 2);
    else
        DPtoLP(hDC, rgpt, 2);

    if (fSysDC)
        ReleaseDC(NULL, hDC);

    pRect->left=rgpt[0].x;
    pRect->top=rgpt[0].y;
    pRect->right=rgpt[1].x;
    pRect->bottom=rgpt[1].y;

    return;
    }






/*
 * CPages::Draw
 *
 * Purpose:
 *  Paints the current page in the pages window.
 *
 * Parameters:
 *  hDC             HDC to draw on, could be a metafile or printer
 *                  DC or any other type of DC.
 *  fNoColor        BOOL indicating if we should use screen colors
 *                  or printer colors (B&W).  Objects are printed
 *                  as-is, however.  This is TRUE for printer DCs
 *                  or print preview.
 *  fPrinter        BOOL indicating if this is a printer DC in which
 *                  case we eliminate some of the fancy drawing,
 *                  like shadows on the page and so forth.
 *
 * Return Value:
 *  None
 */

void CPages::Draw(HDC hDC, BOOL fNoColor, BOOL fPrinter)
    {
    RECT            rc, rcT;
    UINT            uMM;
    HPEN            hPen;
    HBRUSH          hBrush;
    HGDIOBJ         hObj1, hObj2;
    COLORREF        cr;
    TCHAR           szTemp[20];
    UINT            cch;
    SIZE            sz;
    PCPage          pPage;
    RECT            rcPos;

    //Make sure the DC is in LOMETRIC
    uMM=SetMapMode(hDC, MM_LOMETRIC);

    if (!fPrinter)
        {
        /*
         * We maintain a 6mm border around the page on the screen
         * besides 12.7mm margins.  We also have to account for
         * the scroll position with m_*Pos which are in pixels so
         * we have to convert them.
         */

        SetRect(&rcPos, m_xPos, m_yPos, 0, 0);
        RectConvertMappings(&rcPos, hDC, FALSE);

        rc.left  = LOMETRIC_BORDER-rcPos.left;
        rc.top   =-LOMETRIC_BORDER-rcPos.top;
        }
    else
        {
        /*
         * We define the corner of the printed paper at a negative
         * offset so rc.right and rc.bottom come out right below.
         */
        SetRect(&rc, -(int)m_xMarginLeft, m_yMarginTop, 0, 0);
        }

    rc.right=rc.left+m_cx+(m_xMarginLeft+m_xMarginRight);
    rc.bottom=rc.top-m_cy-(m_yMarginTop+m_yMarginBottom);

    //Draw a rect filled with the window color to show the page.
    if (!fPrinter)
        {
        if (fNoColor)
            {
            //Black frame, white box for printed colors.
            hPen  =CreatePen(PS_SOLID, 0, RGB(0,0,0));
            hBrush=CreateSolidBrush(RGB(255, 255, 255));
            }
        else
            {
            //Normal colors on display
            hPen=CreatePen(PS_SOLID, 0
                , GetSysColor(COLOR_WINDOWFRAME));
            hBrush=CreateSolidBrush(GetSysColor(COLOR_WINDOW));
            }

        hObj1=SelectObject(hDC, hPen);
        hObj2=SelectObject(hDC, hBrush);

        //Paper boundary
        Rectangle(hDC, rc.left, rc.top, rc.right, rc.bottom+1);

        /*
         * Draw a shadow on the *visual* bottom and right edges
         * .5mm wide.  If the button shadow color and workspace
         * colors match, then use black.  We always use black
         * when printing as well.
         */
        if (fNoColor)
            cr=RGB(0,0,0);
        else
            {
            cr=GetSysColor(COLOR_BTNSHADOW);

            if (GetSysColor(COLOR_APPWORKSPACE)==cr)
                cr=RGB(0,0,0);
            }

        cr=SetBkColor(hDC, cr);
        SetRect(&rcT, rc.left+5, rc.bottom, rc.right+5,rc.bottom-5);
        ExtTextOut(hDC, 0, 0, ETO_OPAQUE, &rcT, NULL, 0, NULL);

        SetRect(&rcT, rc.right, rc.top-5, rc.right+5, rc.bottom-5);
        ExtTextOut(hDC, 0, 0, ETO_OPAQUE, &rcT, NULL, 0, NULL);
        SetBkColor(hDC, cr);

        SelectObject(hDC, hObj1);
        SelectObject(hDC, hObj2);
        DeleteObject(hBrush);
        DeleteObject(hPen);
        }

    //Write the page number in the lower left corner
    if (!fNoColor)
        {
        SetTextColor(hDC, GetSysColor(COLOR_WINDOWTEXT));
        SetBkColor(hDC, GetSysColor(COLOR_WINDOW));
        }

    //Write the page number in our page font.
    cch=wsprintf(szTemp, TEXT("Page %d"), m_iPageCur+1);

    hObj1=SelectObject(hDC, m_hFont);
    GetTextExtentPoint(hDC, szTemp, cch, &sz);

    TextOut(hDC, rc.left+m_xMarginLeft
        , rc.bottom+m_yMarginBottom+sz.cy, szTemp, cch);

    SelectObject(hDC, hObj1);

    //Rectangle to show border.
    MoveToEx(hDC, rc.left+m_xMarginLeft, rc.top-m_yMarginTop, NULL);
    LineTo(hDC, rc.left+m_xMarginLeft,   rc.bottom+m_yMarginBottom);
    LineTo(hDC, rc.right-m_xMarginRight, rc.bottom+m_yMarginBottom);
    LineTo(hDC, rc.right-m_xMarginRight, rc.top-m_yMarginTop);
    LineTo(hDC, rc.left+m_xMarginLeft,   rc.top-m_yMarginTop);

    /*
     * Go draw the objects on this page.  If the page is not open,
     * we open it anyway.  If it is already open, then opening again
     * will bump it's reference count, so the Close in ineffectual.
     */
    if (PageGet(m_iPageCur, &pPage, TRUE))
        {
        if (!fPrinter)
            {
            pPage->Draw(hDC, rcPos.left, rcPos.top, fNoColor
                , fPrinter);
            }
        else
            pPage->Draw(hDC, 0, 0, fNoColor, fPrinter);

        pPage->Close(FALSE);
        }

    SetMapMode(hDC, uMM);
    return;
    }





/*
 * CPages::UpdateScrollRanges
 *
 * Purpose:
 *  Reset scrollbar ranges (horizontal and vertical) depending on
 *  the window size and the page size.  This function may remove
 *  the scrollbars altogether.
 *
 * Parameters:
 *  None, but set m_cx, m_cy and size m_hWnd before calling.
 *
 * Return Value:
 *  None
 */

void CPages::UpdateScrollRanges(void)
    {
    UINT        cxSB;   //Scrollbar width and height.
    UINT        cySB;
    UINT        cx, cy;
    UINT        dx, dy;
    UINT        u;
    int         iMin, iMax;
    RECT        rc;
    BOOL        fHScroll;
    BOOL        fVScroll;
    BOOL        fWasThere;

    GetClientRect(m_hWnd, &rc);

    cx=rc.right-rc.left;
    cy=rc.bottom-rc.top;

    //Convert dimensions of the image in LOMETRIC to pixels.
    SetRect(&rc, (m_cx+m_xMarginLeft+m_xMarginRight
        +LOMETRIC_BORDER*2), (m_cy+m_yMarginTop
        +m_yMarginBottom+LOMETRIC_BORDER*2), 0, 0);

    RectConvertMappings(&rc, NULL, TRUE);

    dx=rc.left;
    dy=-rc.top;

    //Assume that both scrollbars will be visible.
    fHScroll=TRUE;
    fVScroll=TRUE;

    /*
     * Determine:
     *  1)  Which scrollbars are needed.
     *  2)  How many divisions to give scrollbars so as to
     *      only scroll as little as necessary.
     */

    //Scrollbar dimensions in our units.
    cxSB=GetSystemMetrics(SM_CXVSCROLL);
    cySB=GetSystemMetrics(SM_CYHSCROLL);

    //Remove horizontal scroll if window >= cxPage+borders
    if (cx >= dx)
        fHScroll=FALSE;


    /*
     * If we still need a horizontal scroll, see if we need a
     * vertical taking the height of the horizontal scroll into
     * account.
     */

    u=fHScroll ? cySB : 0;

    if ((cy-u) >= dy)
        fVScroll=FALSE;

    //Check if adding vert scrollbar necessitates a horz now.
    u=fVScroll ? cxSB : 0;
    fHScroll=((cx-u) < dx);

    /*
     * Modify cx,cy to reflect the new client area before scaling
     * scrollbars.  We only affect the client size if there is a
     * *change* in scrollbar status:  if the scrollbar was there
     * but is no longer, then add to the client size; if it was
     * not there but now is, then subtract.
     */

    //Change cx depending on vertical scrollbar change
    GetScrollRange(m_hWnd, SB_VERT, &iMin, &iMax);
    fWasThere=(0!=iMin || 0!=iMax);

    if (fWasThere && !fVScroll)
        cx+=cxSB;

    if (!fWasThere && fVScroll)
        cx-=cxSB;

    //Change cy depending on horizontal scrollbar change
    GetScrollRange(m_hWnd, SB_HORZ, &iMin, &iMax);
    fWasThere=(0!=iMin || 0!=iMax);

    if (fWasThere && !fHScroll)
        cy+=cySB;

    if (!fWasThere && fHScroll)
        cy-=cySB;


    /*
     * Show/Hide the scrollbars if necessary and set the ranges.
     * The range is the number of units of the page we cannot see.
     */
    if (fHScroll)
        {
        //Convert current scroll position to new range.
        u=GetScrollPos(m_hWnd, SB_HORZ);

        if (0!=u)
            {
            GetScrollRange(m_hWnd, SB_HORZ, &iMin, &iMax);
            u=MulDiv(u, (dx-cx), (iMax-iMin));
            }

        SetScrollRange(m_hWnd, SB_HORZ, 0, dx-cx, FALSE);
        SetScrollPos(m_hWnd, SB_HORZ, u, TRUE);
        m_xPos=u;
        }
    else
        {
        SetScrollRange(m_hWnd, SB_HORZ, 0, 0, TRUE);
        m_xPos=0;
        }

    if (fVScroll)
        {
        //Convert current scroll position to new range.
        u=GetScrollPos(m_hWnd, SB_VERT);

        if (0!=u)
            {
            GetScrollRange(m_hWnd, SB_VERT, &iMin, &iMax);
            u=MulDiv(u, (dy-cy), (iMax-iMin));
            }

        SetScrollRange(m_hWnd, SB_VERT, 0, dy-cy, FALSE);
        SetScrollPos(m_hWnd, SB_VERT, u, TRUE);

        m_yPos=u;
        }
    else
        {
        SetScrollRange(m_hWnd, SB_VERT, 0, 0, TRUE);
        m_yPos=0;
        }

    //Repaint to insure that changes to m_x/yPos are reflected
    InvalidateRect(m_hWnd, NULL, TRUE);

    return;
    }
