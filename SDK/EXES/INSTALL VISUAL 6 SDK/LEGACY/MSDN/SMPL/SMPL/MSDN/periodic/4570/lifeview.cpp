//***************************************************************************
//
//  LifeView.cpp
//
//***************************************************************************

#include <afxwin.h>
#include <afxext.h>

#include "Resource.h"
#include "MainFrm.h"
#include "LifeDoc.h"
#include "LifeView.h"

IMPLEMENT_DYNCREATE (CLifeView, CScrollView)

BEGIN_MESSAGE_MAP (CLifeView, CScrollView)
    ON_WM_SIZE ()
    ON_WM_ERASEBKGND ()
    ON_WM_LBUTTONDOWN ()
    ON_WM_MOUSEMOVE ()
END_MESSAGE_MAP ()

CLifeView::CLifeView ()
{
    m_bmGrayCell.LoadBitmap ("GrayCell");
    m_bmBlueCell.LoadBitmap ("BlueCell");
}

void CLifeView::OnInitialUpdate ()
{
    m_nPrevRow = -1;
    m_nPrevCol = -1;

    SetScrollParms ();
    CRect rect;
    GetClientRect (&rect);
    SetGridOrigin (rect.Width (), rect.Height ());
    CScrollView::OnInitialUpdate ();
}

void CLifeView::OnUpdate (CView* pSender, LPARAM lHint, CObject* pHint)
{
    Invalidate (lHint ? FALSE : TRUE);
}

void CLifeView::OnSize (UINT nType, int cx, int cy)
{
    CScrollView::OnSize (nType, cx, cy);
    SetGridOrigin (cx, cy);
}

BOOL CLifeView::OnEraseBkgnd (CDC* pDC)
{
    CRect rect;
    GetClientRect (&rect);
    CBrush brush ((COLORREF) ::GetSysColor (COLOR_APPWORKSPACE));
    pDC->FillRect (rect, &brush);
    return TRUE;
}

void CLifeView::OnDraw (CDC* pDC)
{
    CLifeDoc* pDoc = GetDocument ();
    CSize size = pDoc->GetGridSize ();

    CDC mdcGray, mdcBlue;
    mdcGray.CreateCompatibleDC (pDC);
    mdcBlue.CreateCompatibleDC (pDC);

    CBitmap* pOldGrayBitmap = mdcGray.SelectObject (&m_bmGrayCell);
    CBitmap* pOldBlueBitmap = mdcBlue.SelectObject (&m_bmBlueCell);

    CRect rect;
    rect = ((CPaintDC*) pDC)->m_ps.rcPaint;
    pDC->DPtoLP (&rect);

    int x1, y1, x2, y2;
    x1 = max (0, (rect.left - m_ptOrg.x) / CELLWIDTH);
    y1 = max (0, (rect.top - m_ptOrg.y) / CELLHEIGHT);
    x2 = min (size.cx, ((rect.right - m_ptOrg.x) / CELLWIDTH) + 1);
    y2 = min (size.cy, ((rect.bottom - m_ptOrg.y) / CELLHEIGHT) + 1);

    int i, j;
    for (i=y1; i<y2; i++)
        for (j=x1; j<x2; j++)
            pDC->BitBlt (m_ptOrg.x + (j * CELLWIDTH),
                m_ptOrg.y + (i * CELLHEIGHT), CELLWIDTH, CELLHEIGHT,
                pDoc->GetCell (i, j) ? &mdcBlue : &mdcGray, 0, 0, SRCCOPY);

    mdcBlue.SelectObject (pOldBlueBitmap);
    mdcGray.SelectObject (pOldGrayBitmap);
}

void CLifeView::OnLButtonDown (UINT nFlags, CPoint point)
{
    CLifeDoc* pDoc = GetDocument ();
    CSize size = pDoc->GetGridSize ();

    if ((point.x < m_ptOrg.x) ||
        (point.x > (m_ptOrg.x + (size.cx * CELLWIDTH))) ||
        (point.y < m_ptOrg.y) ||
        (point.y > (m_ptOrg.y + (size.cy * CELLHEIGHT))))
        return;

    point.x -= m_ptOrg.x;
    point.y -= m_ptOrg.y;

    CClientDC dc (this);
    OnPrepareDC (&dc);
    dc.DPtoLP (&point);

    int nRow = point.y / CELLHEIGHT;
    int nCol = point.x / CELLWIDTH;

    m_nPrevRow = nRow;
    m_nPrevCol = nCol;

    BOOL bState = pDoc->ToggleCell (nRow, nCol);
    DrawCell (&dc, nRow, nCol, bState);
}

void CLifeView::OnMouseMove (UINT nFlags, CPoint point)
{
    if (!(nFlags & MK_LBUTTON))
        return;

    CLifeDoc* pDoc = GetDocument ();
    CSize size = pDoc->GetGridSize ();

    if ((point.x < m_ptOrg.x) ||
        (point.x > (m_ptOrg.x + (size.cx * CELLWIDTH))) ||
        (point.y < m_ptOrg.y) ||
        (point.y > (m_ptOrg.y + (size.cy * CELLHEIGHT))))
        return;

    point.x -= m_ptOrg.x;
    point.y -= m_ptOrg.y;

    CClientDC dc (this);
    OnPrepareDC (&dc);
    dc.DPtoLP (&point);

    int nRow = point.y / CELLHEIGHT;
    int nCol = point.x / CELLWIDTH;

    if ((nRow == m_nPrevRow) && (nCol == m_nPrevCol))
        return;

    m_nPrevRow = nRow;
    m_nPrevCol = nCol;

    BOOL bState = pDoc->ToggleCell (nRow, nCol);
    DrawCell (&dc, nRow, nCol, bState);
}

void CLifeView::DrawCell (CDC* pDC, int nRow, int nCol, BOOL bState)
{
    CDC mdc;
    mdc.CreateCompatibleDC (pDC);
    CBitmap* pOldBitmap = mdc.SelectObject (bState ?
        &m_bmBlueCell : &m_bmGrayCell);

    pDC->BitBlt (m_ptOrg.x + (nCol * CELLWIDTH),
        m_ptOrg.y + (nRow * CELLHEIGHT), CELLWIDTH, CELLHEIGHT, &mdc,
        0, 0, SRCCOPY);

    mdc.SelectObject (pOldBitmap);
}

void CLifeView::SetGridOrigin (int cx, int cy)
{
    m_ptOrg.x = m_ptOrg.y = 0;
    CSize size = GetDocument ()->GetGridSize ();
    if (cx > (size.cx * CELLWIDTH))
        m_ptOrg.x = (cx - (size.cx * CELLWIDTH)) / 2;
    if (cy > (size.cy * CELLHEIGHT))
        m_ptOrg.y = (cy - (size.cy * CELLHEIGHT)) / 2;
}

void CLifeView::SetScrollParms ()
{
    CSize sizeTotal = GetDocument ()->GetGridSize ();
    sizeTotal.cx *= CELLWIDTH;
    sizeTotal.cy *= CELLHEIGHT;

    CSize sizePage (CELLWIDTH * 10, CELLHEIGHT * 10);
    CSize sizeLine (CELLWIDTH, CELLHEIGHT);

    SetScrollSizes (MM_TEXT, sizeTotal, sizePage, sizeLine);
}

CLifeDoc* CLifeView::GetDocument ()
{
    return (CLifeDoc*) m_pDocument;
}
