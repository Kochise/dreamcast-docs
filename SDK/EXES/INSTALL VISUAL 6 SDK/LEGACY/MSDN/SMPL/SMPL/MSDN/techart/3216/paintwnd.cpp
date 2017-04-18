// paintwnd.cpp : implementation file
//

#include "stdafx.h"
#include "MarkPnt.h"
#include "tools.h"
#include "paintwnd.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPaintWnd

CPaintWnd::CPaintWnd()
{
    m_Pal.CreateWash();
    m_Pal.SetSysPalColors();
    m_iNumPens = 8;
    m_Crayon[0].Load(IDR_DIB_RED, &m_Pal);
    m_Crayon[1].Load(IDR_DIB_BLUE, &m_Pal);
    m_Crayon[2].Load(IDR_DIB_GREEN, &m_Pal);
    m_Crayon[3].Load(IDR_DIB_YELLOW, &m_Pal);
    m_Crayon[4].Load(IDR_DIB_WHITE, &m_Pal);
    m_Crayon[5].Load(IDR_DIB_PURPLE, &m_Pal);
    m_Crayon[6].Load(IDR_DIB_GRAY, &m_Pal);
    m_Crayon[7].Load(IDR_DIB_CYAN, &m_Pal);
    m_Eraser.Load(IDR_DIB_ERASER, &m_Pal);
    m_Corner.Load(IDR_DIB_CORNER);
    m_Corner.MapColorsToPalette(&m_Pal);
    m_dibRing.Load(IDR_DIB_RING);
    m_dibRing.MapColorsToPalette(&m_Pal);
    m_ptPrev.x = -1;
    m_uiTimer = 0;
    m_iChangeLockoutTime = 0;
    m_pCellPoints = NULL;
}

CPaintWnd::~CPaintWnd()
{
    if (m_pCellPoints) delete m_pCellPoints;
}

BEGIN_MESSAGE_MAP(CPaintWnd, CAnimWnd)
	//{{AFX_MSG_MAP(CPaintWnd)
	ON_WM_CREATE()
	ON_WM_MOUSEMOVE()
	ON_WM_SIZE()
	ON_WM_PALETTECHANGED()
	ON_WM_QUERYNEWPALETTE()
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////////
// Window creation and sizing

BOOL CPaintWnd::Create(const char* pszTitle, DWORD dwStyle, 
                      CWnd* pParent, int x, int y, int cx, int cy)
{
    m_dsPaint.Create(cx, cy, &m_Pal);

    // Fill the paint buffer with the background color
    ErasePaintSurface();

    if (!CAnimWnd::Create(pszTitle,
                          dwStyle,
                          pParent,
                          x, y,
                          cx, cy,
                          ::LoadCursor(AfxGetResourceHandle(),
                                       MAKEINTRESOURCE(IDC_CURSOR)),
                           &m_Pal)) {
        return FALSE;
    }
    
    m_uiTimer = SetTimer(1, 100, NULL);
    return TRUE;                 
}

int CPaintWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CAnimWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
    // Add all the pens to the sprite list
    for (int i = 0; i < m_iNumPens; i++) {
        InsertSprite(&m_Crayon[i]);
    }

    // Make the first one current and on top
    m_pCurrentTool = &m_Crayon[0];
    m_pCurrentTool->SetZ(10);

    // Add the eraser to the sprite list
    InsertSprite(&m_Eraser);

    // And the other bits and pieces
    InsertSprite(&m_Corner);

    // Build the binder sprite
    m_Binder.Create(m_dibRing.GetWidth(),
                    ::GetSystemMetrics(SM_CYSCREEN),
                    &m_Pal);
    CRect rcBinder;
    m_Binder.GetRect(&rcBinder);
    CRect rcRing;
    m_dibRing.GetRect(&rcRing);
    int iRingHeight = m_dibRing.GetHeight();
    int iRingWidth = m_dibRing.GetWidth();
    for (int y = 0; y < rcBinder.bottom; y += iRingHeight) {
        rcRing.top = y;
        rcRing.bottom = y + iRingHeight;
        CRect rc;
        if (rc.IntersectRect(&rcRing, &rcBinder)) {
            // Something we should draw
                m_dibRing.CopyBits(&m_Binder,
                                   rc.left, rc.top,
                                   rc.right - rc.left, rc.bottom - rc.top,
                                   0, 0);
        }
    }
    // tell the sprite to re-get its transparency information
    m_Binder.MapColorsToPalette(&m_Pal);
    InsertSprite(&m_Binder);

	return 0;
}

void CPaintWnd::OnSize(UINT nType, int cx, int cy) 
{
	CAnimWnd::OnSize(nType, cx, cy);
	
    // Move all the crayons down to the bottom
    int h = m_Crayon[0].GetHeight();
    int w = m_Crayon[0].GetWidth();
    int y = cy - h - 1;
    int iCellWidth = cx / m_iNumPens;
    for (int i = 0; i < m_iNumPens; i++) {
        int x = i * iCellWidth 
              + cx / m_iNumPens / 2
              - w / 2;
        m_Crayon[i].SetPosition(x, y);
    }
    
    // Put the eraser at the bottom, left
    m_Eraser.SetPosition(iCellWidth / 2 - m_Eraser.GetWidth() / 2, y);    

    // Set up the page flip corner at the top right
    m_Corner.SetPosition(cx - m_Corner.GetWidth(), 0);

    // and the binder rings on the left
    m_Binder.SetPosition(-1, 0);
    m_Binder.SetZ(80);

    // Set up the background fading
    InitFade();

    Invalidate();
}

void CPaintWnd::OnDestroy() 
{
    if (m_uiTimer) KillTimer(1);
}

void CPaintWnd::PostNcDestroy() 
{
    // We must delete the window object ourselves since the
    // app framework doesn't do this.
    delete this;
}

//////////////////////////////////////////////////////////////////////////////
// Palette handling

void CPaintWnd::OnPaletteChanged(CWnd* pFocusWnd) 
{
    // See if the change was caused by us and ignore it if not
    if (pFocusWnd != this) {
        OnQueryNewPalette();
    }
}

BOOL CPaintWnd::OnQueryNewPalette() 
{
    // We are going active so realize our palette
    if (m_pPal) {
        CDC* pdc = GetDC();
        CPalette *poldpal = pdc->SelectPalette(m_pPal, FALSE);
        UINT u = pdc->RealizePalette();
        ReleaseDC(pdc);
        if (u != 0) {
            // some colors changed so we need to do a repaint
            InvalidateRect(NULL, TRUE); // repaint the lot
            return TRUE; // say we did something
        }
    }
    return FALSE; // say we did nothing
}

/////////////////////////////////////////////////////////////////////////////
// Rendering and Drawing

void CPaintWnd::ErasePaintSurface()
{
    CBrush br (PALETTERGB(178,178,178));
    CDC* pDC = m_dsPaint.GetDC();
    ASSERT(pDC);
    CRect rcDraw;
    m_dsPaint.GetRect(&rcDraw);
    pDC->FillRect(&rcDraw, &br);
    GdiFlush();
}

void CPaintWnd::Render(RECT* pClipRect)
{
    // Compute the clip box
    CRect rcDraw;
    m_dsPaint.GetRect(&rcDraw);
    if (pClipRect) {
        rcDraw.IntersectRect(&rcDraw, pClipRect);
    }

    // Copy the paint area to the buffer
    m_dsPaint.CopyBits(&m_dsBuffer,
                       rcDraw.left, rcDraw.top,
                       rcDraw.right - rcDraw.left, rcDraw.bottom - rcDraw.top,
                       rcDraw.left, rcDraw.top);

    // Call base class to render the sprites
    CAnimWnd::RenderSprites(pClipRect);
}

//////////////////////////////////////////////////////////////////////////////
// User Interface

void CPaintWnd::OnMouseMove(UINT nFlags, CPoint point) 
{

    // Move the current pen to the new position
    ASSERT(m_pCurrentTool);
    m_pCurrentTool->SetPosition(point.x, point.y - m_pCurrentTool->GetHeight());

    // If no buttons are down we paint.
    if ((nFlags & (MK_LBUTTON | MK_RBUTTON)) == 0) {

        // get the paint area DC
        CDC* pDC = m_dsPaint.GetDC();
    
        // create the pen
        CPen pen(PS_SOLID,
                 m_pCurrentTool->GetSize(),
                 m_pCurrentTool->GetColor());    
        CPen* ppenOld = pDC->SelectObject(&pen);

        if (m_ptPrev.x == -1) {
            m_ptPrev = point;
        }
        pDC->MoveTo(m_ptPrev);
        pDC->LineTo(point);    
        pDC->SelectObject(ppenOld);
        GdiFlush();

        CRect rc;
        rc.left = min(point.x, m_ptPrev.x);
        rc.top = min(point.y, m_ptPrev.y);
        rc.right = max(point.x, m_ptPrev.x);
        rc.bottom = max(point.y, m_ptPrev.y);
        rc.InflateRect(m_pCurrentTool->GetSize(), m_pCurrentTool->GetSize());

        AddDirtyRegion(&rc);
    }

    // See if we are in tool-change lockout time
    if (m_iChangeLockoutTime == 0) {
        // OK for a tool change

        // test for a hit in a sprite just below where the tool is
        // (so we don't hit test inside the tool itself)
        int x = m_pCurrentTool->GetX();
        int y = m_pCurrentTool->GetY();
        CDrawingTool* pspNewTool = (CDrawingTool*)
            HitTestSprite(CPoint(x, y + m_pCurrentTool->GetHeight() + 10));
        if (pspNewTool && pspNewTool->IsKindOf(RUNTIME_CLASS(CDrawingTool))) {
            m_pCurrentTool->SetPosition(pspNewTool->GetX(),
                                      pspNewTool->GetY());
            m_pCurrentTool->SetZ(50);
            m_pCurrentTool = pspNewTool;
            m_pCurrentTool->SetPosition(x, y);
            m_pCurrentTool->SetZ(10);
            // Restart the lockout timer
            m_iChangeLockoutTime = 10; // 1.0s
        }
    }

    // Draw all the changes
    RenderAndDrawDirtyList();

    m_ptPrev = point;
}

void CPaintWnd::OnLButtonDown(UINT nFlags, CPoint point) 
{
    // See if we got a hit in the page-turn corner
    if (m_Corner.HitTest(point)) {
        ErasePaintSurface();
        Invalidate();
    }
}

//////////////////////////////////////////////////////////////////////////////
// Background processing

void CPaintWnd::OnTimer(UINT nIDEvent) 
{
    // Update the tool-change lockout timer
    if (m_iChangeLockoutTime > 0) {
        m_iChangeLockoutTime--;
    }

    // Do some of the image fading
    Fade(4);
}

