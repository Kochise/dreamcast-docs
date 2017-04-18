// osdibvw.cpp : implementation file
//
// There are two distinct functions which I have chosen to call Render and Draw.
// Render takes the background DIB and sprite list and copies their images to the 
// off-screen buffer (COffScreenDIBView).  Draw copies data from the off-screen 
// buffer to the physical display device. Both Render and Draw take an optional LPRECT
// parameter which describes the area to be updated.
//

#include "stdafx.h"
#include "anim32.h"  // for dprintf macros only
#include "osdibvw.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COffScreenDIBView

#define DIB_PAL_INDICIES 2

static DWORD dwStretchDIBitsMode = DIB_PAL_COLORS;


IMPLEMENT_DYNCREATE(COffScreenDIBView, CScrollView)

COffScreenDIBView::COffScreenDIBView()
{
    dprintf2("COffScreenDIBView::COffScreenDIBView()");
    m_pDIB = NULL;
    m_pPal = NULL;
    m_pOneToOneClrTab = NULL;
}

COffScreenDIBView::~COffScreenDIBView()
{
    dprintf2("COffScreenDIBView::~COffScreenDIBView()");
    if (m_pDIB) delete m_pDIB;
    if (m_pOneToOneClrTab) free(m_pOneToOneClrTab);
    if (m_pPal) delete m_pPal;
}


BEGIN_MESSAGE_MAP(COffScreenDIBView, CScrollView)
    //{{AFX_MSG_MAP(COffScreenDIBView)
    ON_WM_ERASEBKGND()
    ON_WM_PALETTECHANGED()
    ON_WM_QUERYNEWPALETTE()
    ON_COMMAND(ID_OPTIONS_PALCLR, OnOptionsPalclr)
    ON_UPDATE_COMMAND_UI(ID_OPTIONS_PALCLR, OnUpdateOptionsPalclr)
    ON_COMMAND(ID_OPTIONS_PALIND, OnOptionsPalind)
    ON_UPDATE_COMMAND_UI(ID_OPTIONS_PALIND, OnUpdateOptionsPalind)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COffScreenDIBView

// Create a new set of tables based on a given DIB
BOOL COffScreenDIBView::CreateTables(CDIB *pDIB)
{
    dprintf2("COffScreenDIBView::CreateTables()");
    ASSERT(pDIB);
    // Create the 1:1 color table
    if (m_pOneToOneClrTab) free(m_pOneToOneClrTab);
    m_pOneToOneClrTab = 
        (LPBITMAPINFO) malloc(sizeof(BITMAPINFOHEADER)
                              + 256 * sizeof(WORD));
    if (!m_pOneToOneClrTab) {
        dprintf1("Failed to create color table");
        return FALSE;
    }

    // Set up the table to match the DIB
    // by copying the BITMAPINFOHEADER and building a 1:1 color table
    memcpy(m_pOneToOneClrTab,
           pDIB->GetBitmapInfoAddress(),
           sizeof(BITMAPINFOHEADER));
    LPWORD pIndex;
    pIndex = (LPWORD)((LPBYTE)m_pOneToOneClrTab 
                      + sizeof(BITMAPINFOHEADER));
    int i;
    for (i = 0; i < 256; i++) {
        *pIndex++ = (WORD) i;
    }

    // Create a palette from the DIB we can use to do screen drawing
    if (m_pPal) delete m_pPal;
    m_pPal = new CDIBPal;
    if (!m_pPal->Create(pDIB)) {
        dprintf1("Failed to create palette");
        delete m_pPal;
        m_pPal =NULL;
        return FALSE;
    } else {
        m_pPal->SetSysPalColors();
    }
    return TRUE;
}

// Create a new buffer, tables and palette from a supplied DIB
BOOL COffScreenDIBView::CreateFromDIB(CDIB *pDIB)
{
    dprintf2("COffScreenDIBView::CreateFromDIB()");
    // delete any existing DIB and create a new one
    if (m_pDIB) delete m_pDIB;
    m_pDIB = new CDIB;
    if (!m_pDIB->Create(pDIB->GetWidth(), pDIB->GetHeight())) {
        dprintf1("Failed to create os dib");
        delete m_pDIB;
        m_pDIB = NULL;
        return FALSE;
    }
    dprintf3(" Size: %u x %u", pDIB->GetWidth(), pDIB->GetHeight());
    CSize sizeTotal;
    sizeTotal.cx = pDIB->GetWidth();
    sizeTotal.cy = pDIB->GetHeight();
    SetScrollSizes(MM_TEXT, sizeTotal);
    return CreateTables(pDIB);
}

// This function is only required to set some valid scroll range
// The value is irrelavant as it will be set correctly when the
// off screen buffer is created later.
void COffScreenDIBView::OnInitialUpdate()
{
    dprintf2("COffScreenDIBView::OnInitialUpdate()");
    CSize sizeTotal (100, 100);
    SetScrollSizes(MM_TEXT, sizeTotal);
}

// Draw a section of the off-screen image buffer to the screen.
void COffScreenDIBView::Draw(CDC *pDC, LPRECT pRect)
{
    CDC *pdc;
    CRect rcDraw;

    // make sure we have what we need to do a paint
    if (!m_pDIB || !m_pOneToOneClrTab) {
        dprintf1("No DIB or clr tab to paint from");
        return;
    }

    // see if a DC was supplied and get it if not
    if (pDC) {
        pdc = pDC;
    } else {
        pdc = GetDC();
    }

    // see if a rect was supplied and use the client area if not
    if (pRect) {
        rcDraw = *pRect;
    } else {
        GetClientRect(rcDraw);
    }

    // Get the clip box
    CRect rcClip;
    pdc->GetClipBox(rcClip);
    dprintf4(" Clip: %i,%i %i,%i", 
             rcClip.left, rcClip.top, rcClip.right, rcClip.bottom);

    // Create a rect for the DIB
    CRect rcDIB;
    m_pDIB->GetRect(&rcDIB);

    // Find a rectangle that describes the intersection of the draw
    // rect, clip rect and dib rect
    CRect rcBlt;
    rcBlt.IntersectRect(&rcDraw, &rcClip);
    rcBlt.IntersectRect(&rcBlt, &rcDIB);
    // Copy the update rectangle from the off-screen DC to the
    // window DC. Note that DIB origin is lower left corner.
    int w, h, xs, xd, yd, ys;
    w = rcBlt.right - rcBlt.left;
    h = rcBlt.bottom - rcBlt.top;
    xs = xd = rcBlt.left;
    yd = rcBlt.top;
    ys = m_pDIB->GetHeight() - rcBlt.bottom;
    dprintf4(" Blt: %i,%i %ix%i", 
             rcBlt.left, rcBlt.top, w, h);

    ASSERT(m_pPal);
    CPalette *ppalOld = pdc->SelectPalette(m_pPal, 0);
    pdc->RealizePalette();

#ifdef _DEBUG
    // Test to see if the system palette matches our logical
    // palette and if not, what's different
    {
        PALETTEENTRY peSys[256];
        HDC hdcScreen = ::GetDC(NULL);
        ::GetSystemPaletteEntries(hdcScreen, 
                                0,
                                256,
                                peSys);
        PALETTEENTRY peLog[256];
        m_pPal->GetPaletteEntries(0, 256, peLog);
        for (int i=0; i<256; i++) {
            if ( (peSys[i].peRed != peLog[i].peRed)
               ||(peSys[i].peGreen != peLog[i].peGreen)
               ||(peSys[i].peBlue != peLog[i].peBlue)) {
                    dprintf1("Pal mismatch %u: sys %2.2X,%2.2X, %2.2X, log %2.2X,%2.2X, %2.2X",
                             i,
                             peSys[i].peRed,peSys[i].peGreen,peSys[i].peBlue,
                             peLog[i].peRed,peLog[i].peGreen,peLog[i].peBlue);
                    break;
            }
        }
        ::ReleaseDC(NULL, hdcScreen);
    }
#endif // _DEBUG

    DWORD dwStart = dbgGetTime();
    StretchDIBits(pdc->GetSafeHdc(),
                xd,                 // dest x
                yd,                 // dest y
                w,                  // dest width
                h,                  // dest height
                xs,                 // src x
                ys,                 // src y
                w,                  // src width
                h,                  // src height
                m_pDIB->GetBitsAddress(), // bits
                m_pOneToOneClrTab,  // BITMAPINFO
                dwStretchDIBitsMode,// options
                SRCCOPY);           // rop
    dbgShowElapsedTime(" time: ", dwStart);
    pdc->SelectPalette(ppalOld, 0);

    // release the DC if it was one we created
    if (!pDC) ReleaseDC(pdc);
}


// This is a very generic redraw function which just copies the 
// redraw rect from the OS DIB to the DC.
void COffScreenDIBView::OnDraw(CDC* pDC)
{
    dprintf2("COffScreenDIBView::OnDraw()");
    Draw(pDC);
}

CAnimDoc* COffScreenDIBView::GetDocument() // non-debug version is inline
{
    dprintf2("COffScreenDIBView::GetDocument()");
    ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CAnimDoc)));
    return (CAnimDoc*) m_pDocument;
}

/////////////////////////////////////////////////////////////////////////////
// COffScreenDIBView message handlers

// erase the background
BOOL COffScreenDIBView::OnEraseBkgnd(CDC* pDC)
{
    dprintf2("COffScreenDIBView::OnEraseBkgnd()");
    // Fill everything with blackness
    CRect rcClip;
    pDC->GetClipBox(rcClip);
    CBrush br (RGB(128,128,128));
    pDC->FillRect(&rcClip, &br);
    return TRUE; // say we erased it
}

void COffScreenDIBView::OnPaletteChanged(CWnd* pFocusWnd)
{
    dprintf2("COffScreenDIBView::OnPaletteChanged()");
    // See if the change was caused by us and ignore it if not
    if (pFocusWnd != this) {
        OnQueryNewPalette();
    }
}

// Note: Windows actually ignores the return value
BOOL COffScreenDIBView::OnQueryNewPalette()
{
    dprintf2("COffScreenDIBView::OnQueryNewPalette()");

    // We are going active so realize our palette
    if (m_pPal) {
        dprintf3(" Realizing palette");
        CDC* pdc = GetDC();
        CPalette *poldpal = pdc->SelectPalette(m_pPal, FALSE);
        UINT u = pdc->RealizePalette();
        ReleaseDC(pdc);
        if (u != 0) {
            // some colors changed so we need to do a repaint
            dprintf3(" Repainting with new palette");
            InvalidateRect(NULL, TRUE); // repaint the lot
            return TRUE; // say we did something
        }
    }
    return FALSE; // say we did nothing
}

// Map the colors in a DIB to match the current palette we are using
BOOL COffScreenDIBView::MapDIBColors(CDIB *pdib)
{
    dprintf2("COffScreenDIBView::MapDIBColors()");
    if (!m_pPal) {
        dprintf1("No palette to map to");
        return FALSE;
    }
    return pdib->MapColorsToPalette(m_pPal);
}

void COffScreenDIBView::OnOptionsPalclr()
{
    dwStretchDIBitsMode = DIB_PAL_COLORS;
}

void COffScreenDIBView::OnUpdateOptionsPalclr(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(dwStretchDIBitsMode == DIB_PAL_COLORS);
}

void COffScreenDIBView::OnOptionsPalind()
{
    dwStretchDIBitsMode = DIB_PAL_INDICIES;
}

void COffScreenDIBView::OnUpdateOptionsPalind(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(dwStretchDIBitsMode == DIB_PAL_INDICIES);
}
