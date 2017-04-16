// osdibvw.cpp : implementation file
//
// There are two distinct functions which I have chosen to call Render and Draw.
// Render takes the background DIB and sprite list and copies their images to the 
// off-screen buffer (COffScreenDIBView).  Draw copies data from the off-screen 
// buffer to the physical display device. Both Render and Draw take an optional LPRECT
// parameter which describes the area to be updated.
//

#include "stdafx.h"
//#include "gravity.h"  
#include "osdibvw.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COffScreenDIBView

IMPLEMENT_DYNCREATE(COffScreenDIBView, CScrollView)

COffScreenDIBView::COffScreenDIBView()
{
    //dprintf2("COffScreenDIBView::COffScreenDIBView()");
    m_pDIB = NULL;
    m_pPal = NULL;
    m_pOneToOneClrTab = NULL;
    m_bUseCreateDIBSection = FALSE;
    m_hbmSection = NULL;

    // try to get the CreateDIBSection proc. addr.
    HANDLE hMod = ::GetModuleHandle("gdi32");
    if (hMod) {
        m_pCDSProc = (CDSPROC *) GetProcAddress((HMODULE) hMod, "CreateDIBSection");
        if (m_pCDSProc) {
            m_bUseCreateDIBSection = TRUE;
      //      dprintf("Found CreateDIBSection");
        } else {
        //    dprintf("CreateDIBSection not found");
        }
    }    
}

COffScreenDIBView::~COffScreenDIBView()
{
//    dprintf2("COffScreenDIBView::~COffScreenDIBView()");
    if (m_pDIB) delete m_pDIB;
    if (m_pOneToOneClrTab) free(m_pOneToOneClrTab);
    if (m_pPal) delete m_pPal;

    if (m_hbmSection) ::DeleteObject(m_hbmSection);
}


BEGIN_MESSAGE_MAP(COffScreenDIBView, CScrollView)
    //{{AFX_MSG_MAP(COffScreenDIBView)
    ON_WM_ERASEBKGND()
    ON_WM_PALETTECHANGED()
    ON_WM_QUERYNEWPALETTE()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COffScreenDIBView

// Create a new buffer, tables and palette to match a supplied DIB
BOOL COffScreenDIBView::CreateFromDIB(CDIB *pDIB)
{
    // Create the 1:1 color table
    if (m_pOneToOneClrTab) free(m_pOneToOneClrTab);
    m_pOneToOneClrTab = 
        (LPBITMAPINFO) malloc(sizeof(BITMAPINFOHEADER)
                              + 256 * sizeof(WORD));
    if (!m_pOneToOneClrTab) {
        //dprintf1("Failed to create color table");
        return FALSE;
    }

    // Set up the table to match the DIB
    // by copying the BITMAPINFOHEADER and building a 1:1 color table
    memcpy(m_pOneToOneClrTab,
           pDIB->GetBitmapInfoAddress(),
           sizeof(BITMAPINFOHEADER));
    WORD *pIndex;
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
  //      dprintf1("Failed to create palette");
        delete m_pPal;
        m_pPal = NULL;
        return FALSE;
    } else {
        m_pPal->SetSysPalColors();
    }

    // delete any existing DIB and create a new one
    if (m_pDIB) delete m_pDIB;
    m_pDIB = new CDIB;
    BOOL bResult = FALSE;
    if (m_bUseCreateDIBSection) {
       // dprintf3("Creating DIB Section");
        if (m_hbmSection) ::DeleteObject(m_hbmSection);
        ASSERT(m_pCDSProc);

        CDC *pDC = GetDC();
        CPalette *pPalOld = pDC->SelectPalette(m_pPal, FALSE);
        pDC->RealizePalette();
        BYTE *pBits = NULL;
        m_hbmSection = (*m_pCDSProc)(pDC->GetSafeHdc(),
                                     m_pOneToOneClrTab,
                                     DIB_PAL_COLORS,
                                     (VOID **) &pBits,
                                     NULL,
                                     0);
        pDC->SelectPalette(pPalOld, FALSE);
        ASSERT(m_hbmSection);
        ASSERT(pBits);
        ReleaseDC(pDC);
        bResult = m_pDIB->Create(pDIB->GetBitmapInfoAddress(), pBits);
    } else {
        bResult = m_pDIB->Create(pDIB->GetWidth(), pDIB->GetHeight());
    } 
    if (!bResult) {
        //dprintf1("Failed to create os dib");
        delete m_pDIB;
        m_pDIB = NULL;
        return FALSE;
    }

    CSize sizeTotal;
    sizeTotal.cx = m_pDIB->GetWidth();
    sizeTotal.cy = m_pDIB->GetHeight();
    SetScrollSizes(MM_TEXT, sizeTotal);


    return TRUE;
}

void COffScreenDIBView::OnInitialUpdate()
{
    CSize sizeTotal;
    if (m_pDIB) {
        sizeTotal.cx = m_pDIB->GetWidth();
        sizeTotal.cy = m_pDIB->GetHeight();
    } else {
        sizeTotal.cx = 640;
        sizeTotal.cy = 480;
    }
    SetScrollSizes(MM_TEXT, sizeTotal);
}

// Draw a section of the off-screen image buffer to the screen.
void COffScreenDIBView::Draw(CDC *pDC, LPRECT pRect)
{
    CDC *pdc;
    CRect rcDraw;

    // make sure we have what we need to do a paint
    if (!m_pDIB || !m_pOneToOneClrTab) {
        //dprintf1("No DIB or clr tab to paint from");
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
    //dprintf4(" Clip: %i,%i %i,%i", 
     //        rcClip.left, rcClip.top, rcClip.right, rcClip.bottom);

    // Create a rect for the DIB
    CRect rcDIB;
    rcDIB.left = rcDIB.top = 0;
    rcDIB.right = m_pDIB->GetWidth() - 1;
    rcDIB.bottom = m_pDIB->GetHeight() - 1;

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
    if (m_bUseCreateDIBSection) {
        ys = rcBlt.top;
    } else {
        ys = m_pDIB->GetHeight() - rcBlt.bottom;
    }
    //dprintf4(" Blt: %i,%i %ix%i", 
      //       rcBlt.left, rcBlt.top, w, h);

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
                    //dprintf1("Pal mismatch %u: sys %2.2X,%2.2X, %2.2X, log %2.2X,%2.2X, %2.2X",
                    //         i,
                    //         peSys[i].peRed,peSys[i].peGreen,peSys[i].peBlue,
                    //         peLog[i].peRed,peLog[i].peGreen,peLog[i].peBlue);
                    break;
            }
        }
        ::ReleaseDC(NULL, hdcScreen);
    }
#endif // _DEBUG

    //DWORD dwStart = dbgGetTime();
    LPBYTE pBits;
    if (m_bUseCreateDIBSection) {
        HDC dcMem = ::CreateCompatibleDC(pdc->GetSafeHdc());
        HBITMAP hbmOld = (HBITMAP) ::SelectObject(dcMem, m_hbmSection);
        // Note: you do not need to select the palette into
        // the memory DC because the DIB section is using palette
        // index values not colors
        ::BitBlt(pdc->GetSafeHdc(),
                 xd, yd,
                 w, h,
                 dcMem,
                 xs, ys,
                 SRCCOPY);
        ::SelectObject(dcMem, hbmOld);
        ::DeleteDC(dcMem);
    } else {
        pBits = m_pDIB->GetBitsAddress();
        StretchDIBits(pdc->GetSafeHdc(),
                    xd,                 // dest x
                    yd,                 // dest y
                    w,                  // dest width
                    h,                  // dest height
                    xs,                 // src x
                    ys,                 // src y
                    w,                  // src width
                    h,                  // src height
                    pBits,              // bits
                    m_pOneToOneClrTab,  // BITMAPINFO
                    DIB_PAL_COLORS,// options
                    SRCCOPY);           // rop
    }

    //dbgShowElapsedTime(" time: ", dwStart);
    pdc->SelectPalette(ppalOld, 0);

    // release the DC if it was one we created
    if (!pDC) ReleaseDC(pdc);
}


// This is a very generic redraw function which just copies the 
// redraw rect from the OS DIB to the DC.
void COffScreenDIBView::OnDraw(CDC* pDC)
{
    Draw(pDC);
}

CAnimDoc* COffScreenDIBView::GetDocument() // non-debug version is inline
{
    ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CAnimDoc)));
    return (CAnimDoc*) m_pDocument;
}

/////////////////////////////////////////////////////////////////////////////
// COffScreenDIBView message handlers

// erase the background
BOOL COffScreenDIBView::OnEraseBkgnd(CDC* pDC)
{
    // Fill everything with blackness
    CRect rcClip;
    pDC->GetClipBox(rcClip);
    CBrush br (RGB(128,128,128));
    pDC->FillRect(&rcClip, &br);
    return TRUE; // say we erased it
}

void COffScreenDIBView::OnPaletteChanged(CWnd* pFocusWnd)
{
    // See if the change was caused by us and ignore it if not
    if (pFocusWnd != this) {
        OnQueryNewPalette();
    }
}

// Note: Windows actually ignores the return value
BOOL COffScreenDIBView::OnQueryNewPalette()
{
    // We are going active so realize our palette
    if (m_pPal) {
        //dprintf3(" Realizing palette");
        CDC* pdc = GetDC();
        CPalette *poldpal = pdc->SelectPalette(m_pPal, FALSE);
        UINT u = pdc->RealizePalette();
        ReleaseDC(pdc);
        if (u != 0) {
            // some colors changed so we need to do a repaint
            //dprintf3(" Repainting with new palette");
            InvalidateRect(NULL, TRUE); // repaint the lot
            return TRUE; // say we did something
        }
    }
    return FALSE; // say we did nothing
}

// Map the colors in a DIB to match the current palette we are using
BOOL COffScreenDIBView::MapDIBColors(CDIB *pdib)
{
    if (!m_pPal) {
        //dprintf1("No palette to map to");
        return FALSE;
    }
    return pdib->MapColorsToPalette(m_pPal);
}

