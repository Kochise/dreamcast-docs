/*
 * DRAGDROP.CPP
 * Patron Chapter 21
 *
 * Member functions of the CPages class concerned with drag-drop
 * and other object-placement functionality.  Moved here to clean
 * up CPAGES.CPP somewhat.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#include "patron.h"


/*
 * CPages::UTestDroppablePoint
 *
 * Purpose:
 *  Returns if the point in pptl is on the paper in the current page
 *  and alternately if it's within horizontal or vertical inset
 *  regions.
 *
 * Parameters:
 *  pptl            PPOINTL containing the point in screen
 *                  coordinates.
 *
 * Return Value:
 *  UINT            A UDROP_* value.
 */

UINT CPages::UTestDroppablePoint(PPOINTL pptl)
    {
    POINT       pt;
    RECT        rc, rcT, rcC;
    UINT        uRet;

    POINTFROMPOINTL(pt, *pptl);
    ScreenToClient(m_hWnd, &pt);

    CalcBoundingRect(&rc, FALSE);

    GetClientRect(m_hWnd, &rcC);
    IntersectRect(&rcT, &rc, &rcC);

    //Check for at least a client area hit.
    if (!PtInRect(&rcT, pt))
        return UDROP_NONE;

    uRet=UDROP_CLIENT;

    //Scroll checks happen on client area, not document area
    if (PtInRect(&rcC, pt))
        {
        //Check horizontal inset
        if (pt.x <= rcC.left+(int)m_uScrollInset)
            uRet |= UDROP_INSETLEFT;
        else if (pt.x >= rcC.right-(int)m_uScrollInset)
            uRet |= UDROP_INSETRIGHT;

        //Check vertical inset
        if (pt.y <= rcC.top+(int)m_uScrollInset)
            uRet |= UDROP_INSETTOP;
        else if (pt.y >= rcC.bottom-(int)m_uScrollInset)
            uRet |= UDROP_INSETBOTTOM;
        }

    return uRet;
    }




/*
 * CPages::DrawDropTargetRect
 *
 * Purpose:
 *  Draws a dotted rectangle on the Pages window to show where
 *  a drop might occur.  This is a toggle function.
 *
 * Parameters:
 *  pptl            PPOINTL containing the upper-left point
 *                  in screen coordinates.
 *  pszl            LPSIZEL containing the rect extents in device
 *                  units.
 *
 * Return Value:
 *  None
 */

void CPages::DrawDropTargetRect(PPOINTL pptl, LPSIZEL pszl)
    {
    POINT           pt;
    RECT            rc, rcT;
    HDC             hDC;

    if (NULL==pptl && NULL==pszl)
        {
        /*
         * This case is used from WM_PAINT in pagewin.cpp so we can
         * control the proper visibility of the drag rectangle when
         * we're scrolling.  If drag-drop happens between two apps,
         * then any ScrollWindow will cause a WM_PAINT after we
         * leave DragOver, so that paint would normally overwrite
         * the last drawn rectangle.  To alleviate that, WM_PAINT
         * will remove the last rect by sending us NULLs, paint,
         * then reinstate the rectangle.
         */
        pptl=&m_ptlRect;
        pszl=&m_szlRect;
        }
    else
        {
        m_ptlRect.x=pptl->x;
        m_ptlRect.y=pptl->y;
        m_szlRect.cx=pszl->cx;
        m_szlRect.cy=pszl->cy;

        //Flag is only affected from IDropTarget, not WM_PAINT calls
        m_fDragRectShown=!m_fDragRectShown;
        }

    POINTFROMPOINTL(pt, *pptl);
    ScreenToClient(m_hWnd, &pt);
    SetRect(&rc, pt.x, pt.y, pt.x+(int)pszl->cx
        , pt.y+(int)pszl->cy);

    CalcBoundingRect(&rcT, FALSE);
    IntersectRect(&rc, &rc, &rcT);

    if (!IsRectEmpty(&rc))
        {
        hDC=GetDC(m_hWnd);
        DrawFocusRect(hDC, &rc);
        ReleaseDC(m_hWnd, hDC);
        }

    return;
    }




/*
 * CPages::AdjustPosition
 *
 * Purpose:
 *  Adjusts a point for the scrolling offset and then converts it
 *  and a size from device into LOMETRIC units.
 *
 * Parameters:
 *  pptl            PPOINTL to adjust and convert
 *  pszl            LPSIZEL to convert
 *
 * Return Value:
 *  None
 */

void CPages::AdjustPosition(PPOINTL pptl, LPSIZEL pszl)
    {
    RECT        rc;

    SetRect(&rc, m_xPos+(int)pptl->x
        , m_yPos+(int)pptl->y, (int)pszl->cx, (int)pszl->cy);

    RectConvertMappings(&rc, NULL, FALSE);

    pptl->x=rc.left;
    pptl->y=rc.top;

    pszl->cx=rc.right;
    pszl->cy=rc.bottom;

    return;
    }
