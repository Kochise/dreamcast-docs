// scopescr.cpp : implementation file
//

#include "stdafx.h"
#include "fwtest.h"
#include "scopescr.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CScopeScreen

CScopeScreen::CScopeScreen()
{
    m_pPal = NULL;
}

CScopeScreen::~CScopeScreen()
{
    // Don't delete m_pPal - it's not ours
}


BEGIN_MESSAGE_MAP(CScopeScreen, CWnd)
    //{{AFX_MSG_MAP(CScopeScreen)
    ON_WM_SIZE()
    ON_WM_ERASEBKGND()
    ON_WM_PAINT()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScopeScreen message handlers

BOOL CScopeScreen::Create(CWnd* pParentWnd, UINT nID, CPalette* pPal)
{
    m_pPal = pPal;
    return CWnd::Create(NULL,
                        NULL,
                        WS_CHILD|WS_VISIBLE,
                        CRect(0,0,0,0),
                        pParentWnd,
                        nID);
}

void CScopeScreen::OnSize(UINT nType, int cx, int cy)
{
    CWnd::OnSize(nType, cx, cy);
    // Resize the screen buffer to occupy the client area
    m_dibSurf.Create(max(cx,10), max(cy,10), m_pPal);
    // Save the size
    m_iScreenWidth = cx;
    m_iScreenHeight = cy;
    // Set up the screen as blank with the grid showing
    Erase();
    DrawGrid();
}

BOOL CScopeScreen::OnEraseBkgnd(CDC* pDC)
{
    return TRUE; // say we handled it
}

void CScopeScreen::OnPaint()
{
    CPaintDC dc(this); // device context for painting
    // Simply copy the buffer to the DC
    m_dibSurf.Draw(&dc);    
}

void CScopeScreen::Erase()
{
    CDC* pDC = m_dibSurf.GetDC();
    CBrush br(PALETTERGB(0,85,0));
    CRect rc;
    m_dibSurf.GetRect(&rc);
    pDC->FillRect(&rc, &br);
}

void CScopeScreen::DrawGrid()
{
    // Standard grid is 8 high by 10 wide
    CDC* pDC = m_dibSurf.GetDC();
    CPen penScale(PS_SOLID, 1, RGB(0, 0, 0));
    CPen* ppenOld = pDC->SelectObject(&penScale);
    int iXCells = 10;
    int iYCells = 8;
    int iXTicks = iXCells * 5;
    int iYTicks = iYCells * 5;
    int iTickWidth = 2;
    int iTickHeight = 2; 
    // do the minor lines
    for (int i = 1; i < iXCells; i++) {
        pDC->MoveTo(i * m_iScreenWidth / iXCells, 0);
        pDC->LineTo(i * m_iScreenWidth / iXCells, m_iScreenHeight);
    }
    for (i = 1; i < iYCells; i++) {
        pDC->MoveTo(0, i * m_iScreenHeight / iYCells);
        pDC->LineTo(m_iScreenWidth, i * m_iScreenHeight / iYCells);
    }
    // Put tick marks on the axis lines
    for (i = 1; i < iXTicks; i++) {
        pDC->MoveTo(i * m_iScreenWidth / iXTicks,
                    m_iScreenHeight/2 - iTickWidth);
        pDC->LineTo(i * m_iScreenWidth / iXTicks,
                    m_iScreenHeight/2 + iTickWidth);
    }
    for (i = 1; i < iYTicks; i++) {
        pDC->MoveTo(m_iScreenWidth/2 - iTickHeight,
                    i * m_iScreenHeight / iYTicks);
        pDC->LineTo(m_iScreenWidth/2 + iTickHeight,
                    i * m_iScreenHeight / iYTicks);
    }

    pDC->SelectObject(ppenOld);
}

CDC* CScopeScreen::GetDC()
{
    return m_dibSurf.GetDC();
}

void CScopeScreen::GetRect(CRect* prc)
{
    m_dibSurf.GetRect(prc);
}
