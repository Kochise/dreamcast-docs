// animwnd.cpp : implementation file
//

#include "stdafx.h"
#include "animwnd.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAnimWndSpriteNotifyObj

CAnimWndSpriteNotifyObj::CAnimWndSpriteNotifyObj()
{
    m_pAnimWnd = NULL;
}

void CAnimWndSpriteNotifyObj::Change(CSprite* pSprite, CHANGETYPE change,
                                    CRect* pRect1, CRect* pRect2)
{
    ASSERT(m_pAnimWnd);
    if (change & CSpriteNotifyObj::ZORDER) {
        // reposition the sprite in the z-order list
        m_pAnimWnd->ReorderSprite(pSprite);
        // Add the sprite position to the dirty list
        m_pAnimWnd->AddDirtyRegion(pRect1);
    }
    if (change & CSpriteNotifyObj::POSITION) {
        // pRect1 and pRect2 point to old and new rect positions
        // add these rects to the dirty list
        m_pAnimWnd->AddDirtyRegion(pRect1);
        m_pAnimWnd->AddDirtyRegion(pRect2);
    }
    if (change & CSpriteNotifyObj::IMAGE) {
        // redraw the sprite
        // Add the sprite position to the dirty list
        m_pAnimWnd->AddDirtyRegion(pRect1);
    }
}

/////////////////////////////////////////////////////////////////////////////
// CAnimWnd

CAnimWnd::CAnimWnd()
{
    m_pPal = NULL;
    m_bMyPal = FALSE;
    m_clrBackground = PALETTERGB(178, 178, 178);
    m_NotifyObj.m_pAnimWnd = this;
}

CAnimWnd::~CAnimWnd()
{
    EmptyDirtyList();
    if (m_pPal && m_bMyPal) delete m_pPal;
}

BEGIN_MESSAGE_MAP(CAnimWnd, CWnd)
	//{{AFX_MSG_MAP(CAnimWnd)
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CAnimWnd::Create(const char* pszTitle, DWORD dwStyle, 
                      CWnd* pParent, int x, int y, int cx, int cy,
                      HCURSOR hCur, CPalette* pPal/*= NULL*/)
{
    // Save the palette, or create one
    if (pPal) {
        m_pPal = pPal;
        m_bMyPal = FALSE;
    } else {
        CDIBPal* pWashPal = new CDIBPal;
        ASSERT(pWashPal);
        pWashPal->CreateWash();
        m_pPal = pWashPal;
        m_bMyPal = TRUE;
    }

    // Create the off-screen rendering buffer
    m_dsBuffer.Create(cx, cy, m_pPal);

    // Create a class name
    const char* pszClassName 
        = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW, hCur);

    // Create the window
    return CWnd::CreateEx(0,
                          pszClassName,
                          pszTitle,
                          dwStyle,
                          x, y,
                          cx, cy,
                          pParent->GetSafeHwnd(),
                          NULL);
}

BOOL CAnimWnd::OnEraseBkgnd(CDC* pDC) 
{
	return TRUE; // Say we handled it
}

void CAnimWnd::OnPaint() 
{
    PAINTSTRUCT ps;
    BeginPaint(&ps);
    Render(&ps.rcPaint);
    Draw(&ps.rcPaint);
    EndPaint(&ps);
}

void CAnimWnd::Render(RECT* pClipRect/*= NULL*/)
{
    // Compute the clip box
    CRect rcDraw;
    m_dsBuffer.GetRect(&rcDraw);
    if (pClipRect) {
        rcDraw.IntersectRect(&rcDraw, pClipRect);
    }

    // The default action is to fill the buffer with the
    // background color or the background image and then 
    // render the sprite list
    CBrush br (m_clrBackground);
    CDC* pDC = m_dsBuffer.GetDC();
    ASSERT(pDC);
    pDC->FillRect(&rcDraw, &br);

    // Flush the GDI queue before doing any direct pixel ops
    GdiFlush();
    RenderSprites(pClipRect);
}

void CAnimWnd::RenderSprites(RECT* pClipRect/*= NULL*/)
{
    // Compute the clip box
    CRect rcDraw;
    m_dsBuffer.GetRect(&rcDraw);
    if (pClipRect) {
        rcDraw.IntersectRect(&rcDraw, pClipRect);
    }

    // Walk the sprite list rendering the sprites
    POSITION pos = m_SpriteList.GetTailPosition();
    CSprite* pSprite;
    while (pos) {
        pSprite = (CSprite*)m_SpriteList.GetPrev(pos);
        pSprite->Render(&m_dsBuffer, &rcDraw);
    }                 
}

void CAnimWnd::Draw(RECT* pClipRect/*= NULL*/)
{
    CClientDC dc(this);
    CRect rcDraw;

    // Get the client area clipping box
    dc.GetClipBox(&rcDraw);

    // intersect with supplied clip box
    if (pClipRect) {
        rcDraw.IntersectRect(&rcDraw, pClipRect);
    }

    // intersect with the buffer rect
    CRect rcBuf;
    m_dsBuffer.GetRect(&rcBuf);
    rcDraw.IntersectRect(&rcDraw, &rcBuf);

    // if we have a palette, select and realize it
    CPalette *ppalOld = NULL;
    if(m_pPal) {
        ppalOld = dc.SelectPalette(m_pPal, 0);
        dc.RealizePalette();
    }

    // Note: you do not need to select the palette into
    // the memory DC because the DIB section is using palette
    // index values not colors
    m_dsBuffer.BitBlt(&dc,
                       rcDraw.left, rcDraw.top,
                       rcDraw.right - rcDraw.left, rcDraw.bottom - rcDraw.top,
                       rcDraw.left, rcDraw.top);

    // select old palette if we altered it
    if (ppalOld) dc.SelectPalette(ppalOld, 0);
}

/////////////////////////////////////////////////////////////////////////////////
// Dirty region management

void CAnimWnd::AddDirtyRegion(RECT* prcNew)
{
    // get the rectangle currently at the top of the list
    POSITION pos = m_DirtyList.GetHeadPosition();
    if (pos) {
        CRect* prcTop = (CRect*)m_DirtyList.GetNext(pos);
        CRect rcTest;
        // If the new one intersects the top one merge them
        if (rcTest.IntersectRect(prcTop, prcNew)) {
            prcTop->UnionRect(prcTop, prcNew);
            return;
        }
    }
    // list is empty or there was no intersection
    CRect *prc = new CRect;
    *prc = *prcNew; // copy the data
    // add a new rectangle to the list
    m_DirtyList.AddHead((CObject*)prc);
}

// Render and draw all the dirty regions
void CAnimWnd::RenderAndDrawDirtyList()
{
    POSITION pos = m_DirtyList.GetHeadPosition();
    // Render all the dirty regions
    while (pos) {
        // get the next region
        CRect* pRect = (CRect*)m_DirtyList.GetNext(pos);
        // render it
        Render(pRect);
    }
    // Draw all the dirty regions to the screen
    while (!m_DirtyList.IsEmpty()) {
        // get the next region
        CRect* pRect = (CRect*)m_DirtyList.RemoveHead();
        Draw(pRect);
        // done with it
        delete pRect;
    }
}

// Empty the dirty list
void CAnimWnd::EmptyDirtyList()
{
    while (!m_DirtyList.IsEmpty()) {
        CRect* prc = (CRect*)m_DirtyList.RemoveHead();
        delete prc;
    }
}

/////////////////////////////////////////////////////////////////////////////////
// Sprite management

// Add a sprite to the list, placing it according to its z-order value
BOOL CAnimWnd::InsertSprite(CSprite* pNewSprite)
{
    // Set the notification object pointer in the sprite
    // to our notifiaction object
    pNewSprite->SetNotificationObject(&m_NotifyObj);

    // Walk down the list until we either get to the end
    // or we find a sprite with the same or higher z order
    // in which case we insert just before that one.

    POSITION pos, posThis;
    CSprite *pSprite;
    for (pos = m_SpriteList.GetHeadPosition(); pos != NULL;) {
        posThis = pos;
        pSprite = (CSprite*)m_SpriteList.GetNext(pos); // inc pos
        if (pSprite->GetZ() >= pNewSprite->GetZ()) {
            m_SpriteList.InsertBefore(posThis, pNewSprite);
            return TRUE;
        }
    }
    // nothing with same or higher z-order so add it to the end
    m_SpriteList.AddTail(pNewSprite); 
    return TRUE;
}

// remove a sprite from the list, but do not delete it
CSprite* CAnimWnd::RemoveSprite(CSprite* pSprite)
{
    POSITION pos = m_SpriteList.Find(pSprite);
    if (pos == NULL) {
        return NULL;
    }
    m_SpriteList.RemoveAt(pos);
    return pSprite;
}

// Reorder a sprite in the list
void CAnimWnd::ReorderSprite(CSprite*pSprite)
{
    // Remove the sprite from the list
    if (!RemoveSprite(pSprite)) {
        TRACE("Unable to find sprite");
        return; // not there
    }
    // Now insert it again in the right place
    InsertSprite(pSprite);
}

// Test for a mouse hit on any sprite in the list
CSprite* CAnimWnd::HitTestSprite(CPoint point)
{
    // Walk the list top down
    POSITION pos;
    CSprite *pSprite;
    for (pos = m_SpriteList.GetHeadPosition(); pos != NULL;) {
        pSprite = (CSprite*)m_SpriteList.GetNext(pos); // inc pos
        if (pSprite->HitTest(point)) {
            return pSprite;
        }
    }
    return NULL;
}

