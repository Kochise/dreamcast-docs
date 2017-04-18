// osbview.cpp : implementation of the COSBView class
//
// 6/8/94   Modified to use CreateDIBSection or WinG at runtime. Now 
//          provides a DC for GDI ops.
// @doc

#include "stdafx.h"
#include "animate.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COSBView

IMPLEMENT_DYNCREATE(COSBView, CScrollView)

BEGIN_MESSAGE_MAP(COSBView, CScrollView)
    //{{AFX_MSG_MAP(COSBView)
    ON_WM_PALETTECHANGED()
    ON_WM_QUERYNEWPALETTE()
    ON_WM_ERASEBKGND()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COSBView construction/destruction

COSBView::COSBView()
{
    m_pDIBSurf = NULL;
    m_pPal = NULL;
}

COSBView::~COSBView()
{
    if (m_pDIBSurf) delete m_pDIBSurf;
    if (m_pPal) delete m_pPal;
    EmptyDirtyList();
}

/*
@mfunc BOOL | COSBView | Create | Creates a new buffer to match
a suppied DIB.
@syntax BOOL Create(CDIB* pDIB);
@syntax BOOL Create(int w, int h, CPalette* pPal);
@parm CDIB* | pDIB | A pointer to a DIB on which the view is to be based.
@parm int | w | The width of the buffer.
@parm int | h | The height of the buffer.
@parm CPalette* | pPal | A palette to be used with the buffer.
@rdesc The return value is TRUE if the view is created, FALSE if not.
@comm The pDIB value is used to determine the hight, width and color table to use
in the off-screen buffer. Or if the alternate form is used, the width, height
and palette are set expilicitly.
@xref <c COSBView>
*/

BOOL COSBView::Create(CDIB* pDIB)
{
    // Create a palette from the DIB we can use to do screen drawing
    if (m_pPal) delete m_pPal;
    m_pPal = new CDIBPal;
    ASSERT(m_pPal);
    if (!m_pPal->Create(pDIB)) {
        TRACE("Failed to create palette");
        delete m_pPal;
        m_pPal = NULL;
        return FALSE;
    } else {
        // map the colors so we get an identity palette
        m_pPal->SetSysPalColors();
    }

    // delete any existing DIBSurface and create a new one
    if (m_pDIBSurf) delete m_pDIBSurf;
    m_pDIBSurf = new CDIBSurface;

    BOOL bResult = m_pDIBSurf->Create(pDIB->GetWidth(),
                                      pDIB->GetHeight(),
                                      m_pPal);
     
    if (!bResult) {
        TRACE("Failed to create os dib");
        delete m_pDIBSurf;
        m_pDIBSurf = NULL;
        return FALSE;
    }

    CSize sizeTotal;
    sizeTotal.cx = m_pDIBSurf->GetWidth();
    sizeTotal.cy = m_pDIBSurf->GetHeight();
    SetScrollSizes(MM_TEXT, sizeTotal);

    return TRUE;
}

// Create a new buffer
BOOL COSBView::Create(int w, int h, CPalette* pPal)
{
    ASSERT(pPal);

    // Delete any private palette we might have
    if (m_pPal) delete m_pPal;
    m_pPal = NULL;

    // delete any existing DIBSurface and create a new one
    if (m_pDIBSurf) delete m_pDIBSurf;
    m_pDIBSurf = new CDIBSurface;
    BOOL bResult = m_pDIBSurf->Create(w, h, pPal);
     
    if (!bResult) {
        TRACE("Failed to create os dib");
        delete m_pDIBSurf;
        m_pDIBSurf = NULL;
        return FALSE;
    }

    CSize sizeTotal;
    sizeTotal.cx = m_pDIBSurf->GetWidth();
    sizeTotal.cy = m_pDIBSurf->GetHeight();
    SetScrollSizes(MM_TEXT, sizeTotal);

    return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// COSBView drawing

void COSBView::OnInitialUpdate()
{
    CSize sizeTotal;
    if (m_pDIBSurf) {
        sizeTotal.cx = m_pDIBSurf->GetWidth();
        sizeTotal.cy = m_pDIBSurf->GetHeight();
    } else {
        sizeTotal.cx = 640;
        sizeTotal.cy = 480;
    }
    SetScrollSizes(MM_TEXT, sizeTotal);
}

void COSBView::OnDraw(CDC* pDC)
{
    Draw();
}

/////////////////////////////////////////////////////////////////////////////
// COSBView diagnostics

#ifdef _DEBUG
void COSBView::AssertValid() const
{
    CScrollView::AssertValid();
}

void COSBView::Dump(CDumpContext& dc) const
{
    CScrollView::Dump(dc);
}

CDocument* COSBView::GetDocument() // non-debug version is inline
{
    return m_pDocument;
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// COSBView message handlers

/*
@mfunc CDC* | COSBView | GetBufferDC | Get a pointer to the buffer's
CDC object.
@syntax CDC* GetBufferDC();
@rdesc The return value is a pointer to the buffer's CDC object.
@xref <c COSBView>
*/

CDC* COSBView::GetBufferDC()
{
    ASSERT(m_pDIBSurf);
    return m_pDIBSurf->GetDC();
}

/*
@mfunc void | COSBView | Draw | Draw a section of the off-screen image
buffer to the screen.
@syntax void Draw(CRect* pRect = NULL);
@parm CRect* | pRect | A pointer to a CRect object desribing the area
of the buffer to be drawn.
@rdesc There is no return value.
@comm If no rectangle is supplied the entire buffer is drawn.
@xref <c COSBView>
*/

void COSBView::Draw(CRect* pRect)
{
    CClientDC dc(this);
    CRect rcDraw;

    // make sure we have what we need to do a paint
    if (!m_pDIBSurf) {
        TRACE("No DIB surface to paint from");
        return;
    }

    // see if a clip rect was supplied and use the client area if not
    if (pRect) {
        rcDraw = *pRect;
    } else {
        GetClientRect(rcDraw);
    }

    // Get the clip box
    CRect rcClip;
    dc.GetClipBox(rcClip);

    // Create a rect for the DIB
    CRect rcDIB;
    rcDIB.left = rcDIB.top = 0;
    rcDIB.right = m_pDIBSurf->GetWidth() - 1;
    rcDIB.bottom = m_pDIBSurf->GetHeight() - 1;

    // Find a rectangle that describes the intersection of the draw
    // rect, clip rect and dib rect
    CRect rcBlt = rcDraw & rcClip & rcDIB;

    // Copy the update rectangle from the off-screen DC to the
    // window DC. Note that DIB origin is lower left corner.
    int w, h, xs, xd, yd, ys;
    w = rcBlt.right - rcBlt.left;
    h = rcBlt.bottom - rcBlt.top;
    xs = xd = rcBlt.left;
    yd = rcBlt.top;
    ys = rcBlt.top;

    // if we have a palette, select and realize it
    CPalette *ppalOld = NULL;
    if(m_pPal) {
        ppalOld = dc.SelectPalette(m_pPal, 0);
        dc.RealizePalette();
    }

    // Note: you do not need to select the palette into
    // the memory DC because the DIB section is using palette
    // index values not colors
    m_pDIBSurf->BitBlt(&dc,
                       xd, yd,
                       w, h,
                       xs, ys);

    // select old palette if we altered it
    if (ppalOld) dc.SelectPalette(ppalOld, 0);
}

void COSBView::OnPaletteChanged(CWnd* pFocusWnd)
{
    // See if the change was caused by us and ignore it if not
    if (pFocusWnd != this) {
        OnQueryNewPalette();
    }
}

// Note: Windows actually ignores the return value
BOOL COSBView::OnQueryNewPalette()
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

/*
@mfunc void | COSBView | AddDirtyRegion | Add a region to the dirty list.
@syntax void AddDirtyRegion(CRect* prcNew);
@parm CRect* | prcNew | A pointer to a CRect object desribing the new 
region to be added to the dirty list.
@rdesc There is no return value.
@xref <c COSBView>
*/

void COSBView::AddDirtyRegion(CRect* prcNew)
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

/*
@mfunc void | COSBView | RenderAndDrawDirtyList | Render and draw
all the dirty regions.
@syntax void RenderAndDrawDirtyList();
@rdesc There is no return value.
@comm All the regions in the dirty list are rendered to the off-screen
buffer.  All the regions are then drawn from the off-screen buffer
to the screen.  Finally, the dirty list is reset.
@xref <c COSBView>
*/

// Render and draw all the dirty regions
void COSBView::RenderAndDrawDirtyList()
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
void COSBView::EmptyDirtyList()
{
    while (!m_DirtyList.IsEmpty()) {
        CRect* prc = (CRect*)m_DirtyList.RemoveHead();
        delete prc;
    }
}

// Update the view to reflect some change in the doc
void COSBView::OnUpdate(CView* pSender,
                        LPARAM lHint,
                        CObject* pHint)
{
    // Render and draw everything
    Render();
    Draw();
}

BOOL COSBView::OnEraseBkgnd(CDC* pDC)
{
    return TRUE;
}
