// Intervw.cpp : implementation of the CInterpView class
//

#include "stdafx.h"
#include "Interp.h"

#include "Interdoc.h"
#include "Intervw.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInterpView

IMPLEMENT_DYNCREATE(CInterpView, CView)

BEGIN_MESSAGE_MAP(CInterpView, CView)
	//{{AFX_MSG_MAP(CInterpView)
	ON_COMMAND(ID_VIEW_INTERP, OnViewInterp)
	ON_COMMAND(ID_VIEW_NORMAL, OnViewNormal)
	ON_WM_PALETTECHANGED()
	ON_WM_QUERYNEWPALETTE()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_UPDATE_COMMAND_UI(ID_VIEW_INTERP, OnUpdateViewInterp)
	ON_UPDATE_COMMAND_UI(ID_VIEW_NORMAL, OnUpdateViewNormal)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInterpView construction/destruction

CInterpView::CInterpView()
{
	m_bInterpolate = FALSE;

}

CInterpView::~CInterpView()
{
}

/////////////////////////////////////////////////////////////////////////////
// CInterpView drawing

void CInterpView::OnDraw(CDC* pDC)
{
	CInterpDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// Copy the buffer to the window
    m_dsBuffer.Draw(pDC);
}

/////////////////////////////////////////////////////////////////////////////
// CInterpView diagnostics

#ifdef _DEBUG
void CInterpView::AssertValid() const
{
	CView::AssertValid();
}

void CInterpView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CInterpDoc* CInterpView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CInterpDoc)));
	return (CInterpDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CInterpView message handlers

void CInterpView::OnViewInterp() 
{
	m_bInterpolate = TRUE;
    Render();
    Invalidate(FALSE);
}

void CInterpView::OnViewNormal() 
{
	m_bInterpolate = FALSE;
    Render();
    Invalidate(FALSE);
}

// select and realise our palette
BOOL CInterpView::SelRelPal(BOOL bForceBkgnd)
{
    // We are going active so realize our palette
    CDC* pdc = GetDC();
    CInterpDoc* pDoc = GetDocument();
    CPalette *poldpal = pdc->SelectPalette(&pDoc->m_pal,
                                           bForceBkgnd);
    UINT u = pdc->RealizePalette();
    pdc->SelectPalette(poldpal, TRUE);
    pdc->RealizePalette();
    ReleaseDC(pdc);
    // If any colors have changed or we are in the
    // background, repaint the lot
    if (u || bForceBkgnd) {
        InvalidateRect(NULL, TRUE); // repaint
    }
    return (BOOL) u; // TRUE if some colors changed
}

void CInterpView::OnPaletteChanged(CWnd* pFocusWnd) 
{
    // See if the change was caused by us and ignore it if not
    if (pFocusWnd != this) {
        SelRelPal(TRUE); // realize in background 
    }
}

BOOL CInterpView::OnQueryNewPalette() 
{
    return SelRelPal(FALSE); // realize in foreground
}

void CInterpView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	if ((cx <= 0) || (cy <= 0)) return;

	// Update the size of the buffer
    CInterpDoc* pDoc = GetDocument();
    m_dsBuffer.Create(cx, cy, &pDoc->m_pal);
}

BOOL CInterpView::OnEraseBkgnd(CDC* pDC) 
{
	return TRUE;	
}

void CInterpView::Render()
{
    CDC* pDC = m_dsBuffer.GetDC();
    ASSERT(pDC);

	// Fill the background
    CBrush brFill (PALETTERGB(192, 192, 192));
    CRect rcBuffer;
    m_dsBuffer.GetRect(&rcBuffer);
    pDC->FillRect(&rcBuffer, &brFill);
    ::GdiFlush();

    // Copy the image 1:1
    CInterpDoc* pDoc = GetDocument();
    int w = min(48, pDoc->m_dib.GetWidth());
    int h = min(48, pDoc->m_dib.GetWidth());
    pDoc->m_dib.CopyBits(&m_dsBuffer,
                         0, 0,
                         w, h,
                         0, 0);

    // now do the stretching
    if (m_bInterpolate) {
        Interp2(96, 0,
                w*2, h*2,
                0, 0);

        Interp2(0, 192,
               w*4, h*4,
               96, 0);

        Interp2(240, 0,
               w*8, h*8,
               0, 192);

    } else {

        m_dsBuffer.StretchBits(&m_dsBuffer,
                               96, 0,
                               w*2, h*2,
                               0, 0,
                               w, h);

        m_dsBuffer.StretchBits(&m_dsBuffer,
                               0, 192,
                               w*4, h*4,
                               96, 0,
                               w*2, h*2);
        
        m_dsBuffer.StretchBits(&m_dsBuffer,
                               240, 0,
                               w*8, h*8,
                               0, 192,
                               w*4, h*4);
        
	}
}


void CInterpView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	// The document has changed or the type of rendering required
    // so render the lot and redraw the screen 

    // Get the palette into the buffer
    CInterpDoc* pDoc = GetDocument();
    m_dsBuffer.SetPalette(&pDoc->m_pal);

    // Build a new interpolation map
    PALETTEENTRY pe[256];
    int r1, g1, b1, r2, g2, b2;
    BYTE pixel;
    pDoc->m_pal.GetPaletteEntries(0, 256, pe);
    for (int i = 0; i < 256; i++) {
        r1 = pe[i].peRed;
        g1 = pe[i].peGreen;
        b1 = pe[i].peBlue;
        for (int j = i; j < 256; j++) {
            if (i == j) {
                m_Imap2[i][j] = i;
            } else {
                r2 = pe[j].peRed;
                g2 = pe[j].peGreen;
                b2 = pe[j].peBlue;
                pixel = pDoc->m_pal.GetNearestPaletteIndex(RGB((r1+r2)/2,
                                                                   (g1+g2)/2,
                                                                   (b1+b2)/2));
                m_Imap2[i][j] = pixel;
                m_Imap2[j][i] = pixel;
            }
        }
    }

    Render();
    Invalidate(FALSE);
}

void CInterpView::Interp2(int xd, int yd, int wd, int hd, int xs, int ys)
{
    // Copy source to dest, stretching by 2
    int ws = wd / 2;
    int hs = wd / 2;

    BITMAPINFO* pBMI = m_dsBuffer.GetBitmapInfoAddress();
    ASSERT(pBMI);
    ASSERT(pBMI->bmiHeader.biBitCount == 8);
    // test for silly cases
    if (ws == 0 || hs == 0) return;

    // get pointers to the start points in the source
    // and destination DIBs. Note that this will be the bottom left
    // corner of the DIB as the scan lines are reversed in memory
    BYTE* pSrcLine = (BYTE*)m_dsBuffer.GetPixelAddress(xs, ys + hs - 1);
    ASSERT(pSrcLine);
    BYTE* pDestLine = (BYTE*)m_dsBuffer.GetPixelAddress(xd, yd + hs*2 - 1);
    ASSERT(pDestLine);

    // get the scan line widths of each DIB
    int iScanS = m_dsBuffer.GetStorageWidth();
    int iScanD = m_dsBuffer.GetStorageWidth();

    BYTE* pd;
    BYTE* ps;
    BYTE* ps1;
    BYTE* ps2;
    int i;
    // process each source line
    for (int l = 0; l < hs; l++) {

        // copy the source pixels to every other destination pixel
        pd = pDestLine;
        ps = pSrcLine;
        for (i = 0; i < ws; i++) {
            *pd = *ps++;
            pd += 2;
        }

        // fill in the gaps with the average of the pixels either side
        ps1 = pDestLine;
        ps2 = pDestLine + 2;
        pd = pDestLine + 1;
        for (i = 0; i < ws - 1; i++) {
            *pd = m_Imap2[*ps1][*ps2];
            ps1 += 2;
            ps2 += 2;
            pd += 2;
        }
        // the last pixel is a simple copy of the one before it
        *pd = *ps1;

        pDestLine += iScanD * 2;
        pSrcLine += iScanS;
    }

    // process the missing lines in the destination
    pSrcLine = (BYTE*)m_dsBuffer.GetPixelAddress(xd, yd + hs*2 - 1);
    ASSERT(pSrcLine);

    for (l = 0; l < hs-1; l++) {

        ps1 = pSrcLine;
        ps2 = pSrcLine + iScanD * 2;
        pd = pSrcLine + iScanD;

        for (i = 0; i < wd; i++) {
            *pd++ = m_Imap2[*ps1++][*ps2++];
        }

        pSrcLine += iScanS * 2;
    }

    // the last line is a simple copy of the one before it
    ps = pSrcLine;
    pd = pSrcLine + iScanD;
    for (i = 0; i < wd; i++) {
        *pd++ = *ps++;
    }
}

void CInterpView::OnUpdateViewInterp(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(!m_bInterpolate);
}

void CInterpView::OnUpdateViewNormal(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_bInterpolate);
}
