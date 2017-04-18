/***************************************************************************/
/* NOTE:                                                                   */
/* This document is copyright (c) by Oz Solomonovich, and is bound by the  */
/* MIT open source license (www.opensource.org/licenses/mit-license.html). */
/* See License.txt for more information.                                   */
/***************************************************************************/


// FancyTabCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "FancyTabCtrl.h"
#include "Logger.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFancyTabCtrl

CFancyTabCtrl::CFancyTabCtrl() : m_pFont(NULL)
{
}

CFancyTabCtrl::~CFancyTabCtrl()
{
    delete m_pFont;
}


BEGIN_MESSAGE_MAP(CFancyTabCtrl, CTabCtrl)
	//{{AFX_MSG_MAP(CFancyTabCtrl)
	ON_WM_PAINT()
	ON_WM_RBUTTONDOWN()
	ON_WM_MBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFancyTabCtrl message handlers

void CFancyTabCtrl::OnPaint() 
{
    const int iCount = GetItemCount();
    CRect r_clipping;
    CDC *pDC;

    CRect r_client, r_tab_extreme, r_bkg;

    const int  iStyle           = GetStyle();
    const bool bIsHorizontal    = ((iStyle & TCS_VERTICAL) == 0);
    const bool bIsBottomOrRight = ((iStyle & TCS_BOTTOM) == TCS_BOTTOM);

    if (!bIsHorizontal)
    {
        // vertical tabs are to unpredictable
        Default();
        return ;
    }

    GetClientRect(r_client);
    r_bkg = r_client;

    if (iCount) 
    {
        PAINTSTRUCT ps;
        ::BeginPaint(m_hWnd, &ps);
        r_clipping = ps.rcPaint;
        ::EndPaint(m_hWnd, &ps);
        InvalidateRect(r_clipping);
        Default();
        pDC = new CClientDC(this);
    }
    else
    {
        pDC = new CPaintDC(this);
        r_clipping = r_client;
    }

    CDC& dc = *pDC;

    if (iCount == 0)
    {
        dc.FillSolidRect(r_client, ::GetSysColor(COLOR_BTNFACE));
    }

    const int iMargin = (m_iTabHeight - 4) / 2 + 2;
    if (bIsHorizontal)
    {
        r_client.left += 4;
        r_client.right -= 4;
        if (bIsBottomOrRight)
        {
            r_client.top += iMargin;
            r_client.bottom = r_client.top + 3;
        }
        else
        {
            r_client.bottom -= (iMargin + 4);
            r_client.top = r_client.bottom - 3;
        }
    }
    else
    {
        r_client.bottom -= 4;
        r_client.top += 4;
        if (bIsBottomOrRight)
        {
            r_client.left += iMargin;
            r_client.right = r_client.left + 3;
        }
        else
        {
            r_client.right -= (iMargin + 4);
            r_client.left = r_client.right - 3;
        }
    }

    if (iCount)
    {
        GetExtremeItemRect(r_tab_extreme);
        if (bIsHorizontal)
        {
            if (bIsBottomOrRight)
            {
                if (r_tab_extreme.top < r_client.top)
                {
                    r_client.left = r_tab_extreme.right + 8;
                }
                else
                {
                    r_client.OffsetRect(0, -2);
                }
            }
            else
            {
                if (r_tab_extreme.bottom > r_client.bottom)
                {
                    r_client.left = r_tab_extreme.right + 8;
                }
                else
                {
                    r_client.OffsetRect(0, 2);
                }
            }
            r_bkg.left = r_client.left;
        }
        else
        {
            if (bIsBottomOrRight)
            {
                if (r_tab_extreme.left < r_client.left)
                {
                    r_client.top = r_tab_extreme.bottom + 8;
                }
                else
                {
                    r_client.OffsetRect(-2, 0);
                }
            }
            else
            {
                if (r_tab_extreme.right > r_client.right)
                {
                    r_client.top = r_tab_extreme.bottom + 8;
                }
                else
                {
                    r_client.OffsetRect(2, 0);
                }
            }
            r_bkg.top = r_client.top;
        }
    }

    static bForceRepaintEdge = false;

//    r_client.IntersectRect(r_client, r_clipping);
    if (!r_client.IsRectEmpty())
    {
        // for single line tabs, force a repaint of the line strip in case
        // it paints over the panning buttons
        if (((iStyle & TCS_MULTILINE) == 0)  &&
            bForceRepaintEdge == false)
        {
            InvalidateRect(r_bkg);
            bForceRepaintEdge = true;
        }
        else
        {
            bForceRepaintEdge = false;
        }

        dc.Draw3dRect(r_client, ::GetSysColor(COLOR_BTNHILIGHT), 
            ::GetSysColor(COLOR_BTNSHADOW));

        if (bIsHorizontal)
        {
            r_client.OffsetRect(0, 4);
        }
        else
        {
            r_client.OffsetRect(5, 0);
        }

        dc.Draw3dRect(r_client, ::GetSysColor(COLOR_BTNHILIGHT), 
            ::GetSysColor(COLOR_BTNSHADOW));
    }
/*if (iCount)
dc.FillSolidRect(r_tab_extreme, RGB(0, 0, 200));
*/
    delete pDC;
}

void CFancyTabCtrl::GetCurrentItemRect(CRect& r)
{
    GetItemRect(GetCurSel(), r);
}

void CFancyTabCtrl::GetLastItemRect(CRect& r)
{
    GetItemRect(GetItemCount() - 1, r);
}

void CFancyTabCtrl::GetExtremeItemRect(CRect& r)
{
    const int iCount = GetItemCount();
    int i;

    CRect r_client, r_tab_curr, r2;

    GetClientRect(r_client);

    const bool bIsHorizontal    = ((GetStyle() & TCS_VERTICAL) == 0);
    const bool bIsBottomOrRight = ((GetStyle() & TCS_BOTTOM) == TCS_BOTTOM);

    GetLastItemRect(r);
    GetCurrentItemRect(r_tab_curr);

    if (bIsHorizontal)
    {
        if (bIsBottomOrRight)
        {                        
            if (r_tab_curr.top <= r.top)  //(1 ||r_tab_curr.bottom <= r.top)
            {
                // find top/right most tab
                for (i = 0; i < iCount; ++i)
                {
                    GetItemRect(i, r2);
                    if (r2.top < r.top)
                    {
                        r = r2;
                    }
                    if (r2.top == r.top &&
                        r2.right > r.right)
                    {
                        r = r2;
                    }
                }
            }
        }
        else
        {
            if (r_tab_curr.bottom > r.bottom)
            {
                // find bottom/right most tab
                for (i = 0; i < iCount; ++i)
                {
                    GetItemRect(i, r2);
                    if (r2.bottom > r.bottom)
                    {
                        r = r2;
                    }
                    if (r2.bottom == r.bottom &&
                        r2.right > r.right)
                    {
                        r = r2;
                    }
                }
            }
        }
    }
    else
    {
        if (bIsBottomOrRight)
        {
            if (r_tab_curr.left < r.left)
            {
                // find left/bottom most tab
                for (i = 0; i < iCount; ++i)
                {
                    GetItemRect(i, r2);
                    if (r2.left < r.left)
                    {
                        r = r2;
                    }
                    if (r2.left == r.left  &&
                        r2.bottom > r.bottom)
                    {
                        r = r2;
                    }
                }
            }
        }
        else
        {
            if (r_tab_curr.right > r.right)
            {
                // find right/bottom most tab
                for (i = 0; i < iCount; ++i)
                {
                    GetItemRect(i, r2);
                    if (r2.right > r.right)
                    {
                        r = r2;
                    }
                    if (r2.right == r.right &&
                        r2.bottom > r.bottom)
                    {
                        r = r2;
                    }
                }
            }
        }
    }
}

void CFancyTabCtrl::OnRButtonDown(UINT nFlags, CPoint point) 
{
    m_LastRClickPos = point;	
	CTabCtrl::OnRButtonDown(nFlags, point);
}


void CFancyTabCtrl::SetTabFont(CFont *pFont, BOOL bHasIcons)
{
    SetFont(pFont, FALSE);
    if (m_pFont == pFont) return;

    if (m_pFont) delete m_pFont;
    m_pFont = pFont;

    TEXTMETRIC tm;
    CDC *pDC = GetDC();
    CFont *pOldFont = pDC->SelectObject(m_pFont);
    pDC->SetMapMode(MM_TEXT);
    pDC->GetTextMetrics(&tm);

    m_iTabHeight = tm.tmHeight + tm.tmExternalLeading;
    if (m_iTabHeight < 14  &&  bHasIcons)
    {
        m_iTabHeight = 14;
    }
    m_iTabHeight += 5;
    pDC->SelectObject(pOldFont);
}

void CFancyTabCtrl::OnMButtonDown(UINT nFlags, CPoint point) 
{
    // pass this even to the parent for handeling
    ClientToScreen(&point);
    CWnd *pParent = GetParent();
    pParent->ScreenToClient(&point);
    pParent->SendMessage(WM_MBUTTONDOWN, nFlags, MAKELONG(point.x, point.y));
}
