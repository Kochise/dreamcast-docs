// animvw.cpp : implementation of the CAnimView class
//

#include "stdafx.h"
#include "anim32.h"
#include "animdoc.h"
#include "animvw.h"
#include "animsp.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAnimView

IMPLEMENT_DYNCREATE(CAnimView, COffScreenDIBView)

BEGIN_MESSAGE_MAP(CAnimView, COffScreenDIBView)
    //{{AFX_MSG_MAP(CAnimView)
    ON_COMMAND(ID_FILE_LOADBKGND, OnFileLoadbkgnd)
    ON_COMMAND(ID_FILE_LOADSPRITE, OnFileLoadsprite)
    ON_WM_LBUTTONDOWN()
    ON_WM_LBUTTONUP()
    ON_WM_MOUSEMOVE()
    ON_WM_LBUTTONDBLCLK()
    ON_COMMAND(ID_TEST_SPRITEPERF, OnTestSpriteperf)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAnimView construction/destruction

CAnimView::CAnimView()
{
    dprintf2("CAnimView::CAnimView()");
    m_bMouseCaptured = FALSE;
    m_pCapturedSprite = NULL;
}

CAnimView::~CAnimView()
{
    dprintf2("CAnimView::~CAnimView()");
}

/////////////////////////////////////////////////////////////////////////////
// CAnimView drawing
// All done by the base class

/////////////////////////////////////////////////////////////////////////////
// CAnimView diagnostics

#ifdef _DEBUG
void CAnimView::AssertValid() const
{
    COffScreenDIBView::AssertValid();
}

void CAnimView::Dump(CDumpContext& dc) const
{
    COffScreenDIBView::Dump(dc);
}

CAnimDoc* CAnimView::GetDocument() // non-debug version is inline
{
    ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CAnimDoc)));
    return (CAnimDoc*) m_pDocument;
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CAnimView message handlers

// Load a new background DIB
void CAnimView::OnFileLoadbkgnd()
{
    CAnimDoc* pDoc = GetDocument();

    CDIB *pdib = new CDIB;
    // Show the file open dialog for a DIB
    if (!pdib->Load()) {
        delete pdib;
        return;
    }
    // replace the existing background DIB which will cause
    // the view to create a new offscreen buffer with a new palette
    // and map the DIB to the new palette
    if (!pDoc->SetBkgnd(pdib)) {
        delete pdib;
    }
}

void CAnimView::OnFileLoadsprite()
{
    CAnimDoc* pDoc = GetDocument();

    CAnimSprite *psprite = new CAnimSprite;
    // show the file open dialog to load the image
    if (!psprite->Load()) {
        delete psprite;
        return;
    }
    // add the new sprite to the list
    pDoc->AddSprite(psprite);
}   

// Render the image of the background and sprites to the off-screen buffer
void CAnimView::Render(LPRECT pClipRect)
{
    CAnimDoc* pDoc = GetDocument();
    CRect rcDraw;

    // get the background DIB and render it
    CDIB *pdib = pDoc->GetBkgnd();
    if (pdib) {
        pdib->GetRect(&rcDraw);
        if (pClipRect) {
            rcDraw.IntersectRect(pClipRect, &rcDraw);
        }

        // draw the image of the DIB to the os buffer
        pdib->CopyBits(m_pDIB,           // dest DIB
                    rcDraw.left,
                    rcDraw.top,          // dest start point
                    rcDraw.right - rcDraw.left,
                    rcDraw.bottom - rcDraw.top,
                    rcDraw.left, 
                    rcDraw.top);
    }

    // Render the sprite list from the bottom of the list to the top
    // Note that we always clip to the background DIB
    CSpriteList *pList = pDoc->GetSpriteList();
    POSITION pos = pList->GetTailPosition();
    CSprite *pSprite;
    while (pos) {
        pSprite = pList->GetPrev(pos);
        pSprite->Render(m_pDIB, &rcDraw);
    }                 
}

// Render and draw each rectangle in the dirty list then
// reset the list
void CAnimView::RenderAndDrawDirtyList()
{
    // Merge the list to reduce the number of rectangles
    m_DirtyList.Merge();
    POSITION pos;
    CRect *pRect;
    for (pos = m_DirtyList.GetHeadPosition(); pos != NULL;) {
        pRect = m_DirtyList.GetNext(pos); // inc pos
        ASSERT(pRect);
        Render(pRect);
        Draw(NULL, pRect);
    }
    m_DirtyList.RemoveAll();            
}

// Called when the document has changed in some way.  We use the lHint
// parameter to work out what we need to do.
// If no hint is defined then we default to repainting everything.
void CAnimView::OnUpdate(CView *pView, LPARAM lHint, CObject *pObj)
{
    dprintf2("CAnimView::OnUpdate");
    CDIB *pdib;
    CSize size;
    CRect rcFrame;
    CRect rcView;
    CRect rcDraw;
    CAnimSprite *pSprite;
    CFrameWnd* pFrame;
    CAnimDoc* pDoc = GetDocument();

    switch (lHint) {
    case HINT_NEWBKGNDDIB:
        dprintf3("  HINT_NEWBKGNDDIB");
        // Create a new off-screen buffer to match the
        // new background DIB
        ASSERT(pObj->IsKindOf(RUNTIME_CLASS(CDIB)));
        pdib = (CDIB *) pObj;
        CreateFromDIB(pdib);
        // Map the DIB colors to match the palette
        MapDIBColors(pdib);
        // Adjust the frame window to fit the new background
        pFrame = GetParentFrame();
        ASSERT(pFrame != NULL);
        pFrame->GetWindowRect(rcFrame);
        size = rcFrame.Size();
        if (IsWindowVisible()) {
            GetClientRect(rcView);
            size.cx -= (rcView.right - pdib->GetWidth());
            size.cy -= (rcView.bottom - pdib->GetHeight());
        } else {
            size.cx = GetSystemMetrics(SM_CXSCREEN) / 2;
            size.cy = GetSystemMetrics(SM_CYSCREEN) / 2;
        }
        pFrame->SetWindowPos(NULL,
                             0, 0, 
                             size.cx, size.cy,
                             SWP_NOMOVE|SWP_NOZORDER|SWP_NOACTIVATE);
        // Render and paint the whole off-screen buffer to the screen
        Render();
        Draw();
        break;
    case HINT_NEWSPRITE:
        dprintf3("  HINT_NEWSPRITE");
        ASSERT(pObj->IsKindOf(RUNTIME_CLASS(CAnimSprite)));
        pSprite = (CAnimSprite *) pObj;
        // map the DIB colors to the os-DIB palette
        pSprite->MapColorsToPalette(m_pPal);
        // Re-render the area occupied by the new sprite
        pSprite->GetRect(&rcDraw);
        Render(&rcDraw);
        Draw(NULL, &rcDraw);
        break;
    case HINT_DIRTY:
        dprintf4("  HINT_DIRTY");
        m_DirtyList.Add((CRect *) pObj);
        break;
    case HINT_DIRTYLIST:
        dprintf4("  HINT_DIRTYLIST");
        RenderAndDrawDirtyList();
        break;
    default:
        dprintf3("  (no hint)");
        // just do a complete repaint 
        // from the off-screen DIB to the screen
        Render();
        Draw();
        break;
    }
}


void CAnimView::OnLButtonDown(UINT nFlags, CPoint point)
{
    dprintf3("Mouse down at %u,%u", point.x, point.y);
    if (!m_bMouseCaptured) {
        CAnimDoc* pDoc = GetDocument();
        // See if it hit a sprite
        m_pCapturedSprite = (CAnimSprite *)
            (pDoc->GetSpriteList())->HitTest(point);
        if (m_pCapturedSprite && m_pCapturedSprite->IsSelectable()) {
            m_bMouseCaptured = TRUE;
            SetCapture();
            dprintf2("Sprite hit");
            m_ptOffset.x = point.x - m_pCapturedSprite->GetX();
            m_ptOffset.y = point.y - m_pCapturedSprite->GetY();
            dprintf3(" Sprite is at %u,%u,%u (%ux%u)", 
                     m_pCapturedSprite->GetX(), 
                     m_pCapturedSprite->GetY(), 
                     m_pCapturedSprite->GetZ(), 
                     m_pCapturedSprite->GetWidth(),
                     m_pCapturedSprite->GetHeight());
        }
    }
}

void CAnimView::OnMouseMove(UINT nFlags, CPoint point)
{
    if (m_bMouseCaptured) {
        ASSERT(m_pCapturedSprite);
        m_pCapturedSprite->SetPosition(point.x - m_ptOffset.x, 
                                       point.y - m_ptOffset.y);
        // Render and draw the current dirty area
        RenderAndDrawDirtyList();
    }
}

void CAnimView::OnLButtonUp(UINT nFlags, CPoint point)
{
    dprintf3("Mouse up at %u,%u", point.x, point.y);
    if (m_bMouseCaptured) {
        ::ReleaseCapture();
        m_bMouseCaptured = FALSE;
        m_pCapturedSprite = NULL;
        dprintf2("Sprite released");
    }
}

void CAnimView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
    CAnimDoc* pDoc = GetDocument();
    CAnimSprite *pSprite = (CAnimSprite *)
        (pDoc->GetSpriteList())->HitTest(point);
    ASSERT(pSprite->IsKindOf(RUNTIME_CLASS(CAnimSprite)));
    if (pSprite) {
        if (pSprite->DoDialog()) {
            pDoc->UpdateAllViews(NULL);
        }
    } else {
        ::MessageBeep(NULL);
    }
}

// Run a test of the sprite rendering performance.  Uses a copy of
// the first sprite in the list or creates on if none present
void CAnimView::OnTestSpriteperf()
{
    // See if there is a sprite we can clone
    CAnimDoc* pDoc = GetDocument();
    CSpriteList *pList = pDoc->GetSpriteList();
    POSITION pos = pList->GetHeadPosition();
    CSprite *psprite = NULL;
    CDIB *pdib = NULL;
    int oldx, oldy;
    if (pos) {
        psprite = pList->GetNext(pos);
        oldx = psprite->GetX();
        oldy = psprite->GetY();
    } else {
        // create a sprite
        psprite = new CSprite;
        ASSERT(psprite);
        // Map the DIB colors to match the current palette
        psprite->MapColorsToPalette(m_pPal);
    }
    // start a debug timer
    DWORD dwStart = dbgGetTime();
    // render it to the background and to the screen several times
    int i, j, x, y;
    for (i = 0; i < 10; i++) {
        x = i * (m_pDIB->GetWidth() - psprite->GetWidth()) / 9;
        for (j = 0; j < 10; j++) {
            y = j * (m_pDIB->GetHeight() - psprite->GetWidth()) /9;
            psprite->SetPosition(x, y);
            CRect rcDraw;
            psprite->GetRect(&rcDraw);
            psprite->Render(m_pDIB, &rcDraw); 
            Draw(NULL, &rcDraw);
        }
    }
    DWORD dwEnd = dbgGetTime();
    DWORD dwTime = dwEnd - dwStart;
    LARGE_INTEGER liFreq;
    QueryPerformanceFrequency(&liFreq);
    dwTime /= liFreq.LowPart / 10000; // 1/10 ms units
    // show the time
    char buf[128];
    sprintf(buf, "Elapsed time %u.%ums",
             dwTime / 10,
             dwTime % 10);
    AfxMessageBox(buf);
    // tidy up
    if (pdib) {
        delete psprite;
    } else {
        psprite->SetPosition(oldx, oldy);
    }
    Render();
    Draw();    
}
