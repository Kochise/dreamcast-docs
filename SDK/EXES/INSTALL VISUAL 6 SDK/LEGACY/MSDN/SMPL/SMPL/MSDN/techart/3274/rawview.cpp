// rawview.cpp : implementation file
//

#include "stdafx.h"
#include "viewfile.h"

#include "viewfdoc.h"

#include "rawview.h"

extern CViewfileApp theApp;



#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRawView

IMPLEMENT_DYNCREATE(CRawView, CScrollView)

CRawView::CRawView()
{
    m_cfFixedFont = new(CFont);
    m_cfFixedFont->CreateStockObject(ANSI_FIXED_FONT);

}

CRawView::~CRawView()
{
}


BEGIN_MESSAGE_MAP(CRawView, CScrollView)
	//{{AFX_MSG_MAP(CRawView)
	ON_WM_DESTROY()
	ON_WM_VSCROLL()
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CRawView drawing

void CRawView::OnDraw(CDC* pDC)
{
   CViewfileDoc* pDoc = GetDocument();

    CFont *pOldFont = pDC->SelectObject(m_cfFixedFont);
    CRect rcWnd;
    GetClientRect(&rcWnd);
    m_iWndLines = rcWnd.bottom / m_iFontHeight;

    // compute the start point
    int iOffset = m_iFirstLine * 16;
    int iRemaining = pDoc->ImageFileLength() - iOffset;
    int iLine = 0;
    BYTE *pData = pDoc->AdjustPointerAbsolute(0);
    if (!pData) {
        pDC->TextOut(0, 0, "No data", 7);
    } else {
        while ((iRemaining > 0) && (iLine < m_iWndLines)) {
            char buf[80];
            sprintf(buf, "%8.8lX  ", iOffset);
            BYTE *p = pData + iOffset;
            int iCount = iRemaining;
            for (int i = 0; i < 16; i++) {
                if (iCount > 0) {
                    sprintf(&buf[strlen(buf)],
                            "%2.2X ",
                            *p);
                } else {
                    strcat(buf, "   ");
                }
                iCount--;
                p++;
            }
            strcat(buf, "  ");
            p = pData + iOffset;
            iCount = iRemaining;
            for (i = 0; i < 16; i++) {
                if ((iCount > 0) && isprint(*p)) {
                    sprintf(&buf[strlen(buf)],
                            "%c",
                            *p);
                } else if (iCount > 0) {
                    strcat(buf, ".");
                } else {
                    strcat(buf, " ");
                }
                iCount--;
                p++;
            }
            pDC->TextOut(0,
                    iLine * m_iFontHeight,
                    buf,
                    strlen(buf));
            iOffset += 16;
            iRemaining -= 16;
            iLine++;
        }
        if (iLine < m_iWndLines) {
            CRect rc = rcWnd;
            rc.top = iLine * m_iFontHeight;
            pDC->ExtTextOut(0,
                            iLine * m_iFontHeight,
                            ETO_OPAQUE,
                            &rc,
                            "",
                            0,
                            NULL);
        }
    }
    pDC->SelectObject(pOldFont);


//	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CRawView diagnostics

#ifdef _DEBUG
void CRawView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CRawView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CViewfileDoc* CRawView::GetDocument() // non-debug version is inline
{
    ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CViewfileDoc)));
    return (CViewfileDoc*) m_pDocument;
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CRawView message handlers

void CRawView::OnInitialUpdate() 
{
	// TODO: Add your specialized code here and/or call the base class
	
    CDC *pDC = GetDC();
    CFont *pOldFont = pDC->SelectObject(m_cfFixedFont);
    TEXTMETRIC tm;
    pDC->GetTextMetrics(&tm);
    pDC->SelectObject(pOldFont);
    m_iFontHeight = tm.tmHeight + tm.tmExternalLeading;
    m_iFontWidth = tm.tmMaxCharWidth;
    m_iFirstLine = 0;
    m_iLastLine = 0;
    m_iWndLines = 0;

 
    CSize sz;
    sz.cx = m_iFontWidth * 80;
    sz.cy = 1000;
    SetScrollSizes(MM_TEXT, sz);
    CViewfileDoc* pDoc = GetDocument();
    m_iLastLine = (pDoc->ImageFileLength() + 15) / 16;

  }

void CRawView::OnDestroy() 
{
	delete m_cfFixedFont;
	CScrollView::OnDestroy();
	
	// TODO: Add your message handler code here
	
}

void CRawView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CScrollView::OnPrepareDC(pDC, pInfo);
    CPoint pt = pDC->GetViewportOrg();
    pt.y = 0;
    pDC->SetViewportOrg(pt);

}

void CRawView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
    switch (nSBCode) {
    case SB_TOP:
        m_iFirstLine = 0;
        break;
    
    case SB_BOTTOM:
        m_iFirstLine = m_iLastLine;
        break;
    
    case SB_LINEUP:
        m_iFirstLine--;
        break;
        
    case SB_PAGEUP:    
        m_iFirstLine -= m_iWndLines;
        break;

    case SB_LINEDOWN:
        m_iFirstLine++;
        break;

    case SB_PAGEDOWN:
        m_iFirstLine += m_iWndLines;
        break;
    
    case SB_THUMBPOSITION:
    case SB_THUMBTRACK:
        m_iFirstLine = nPos 
                     * (m_iLastLine - m_iWndLines)
                     / 1000;
        break;

    default:
        return;
    }

    if (m_iFirstLine < 0) m_iFirstLine = 0;
    if (m_iWndLines >= m_iLastLine) {
        m_iFirstLine = 0;
    } else if (m_iFirstLine >= m_iLastLine - m_iWndLines) {
        m_iFirstLine = m_iLastLine - m_iWndLines;
    }

    int iPos;
    if (m_iWndLines >= m_iLastLine) {
        iPos = 0;
    } else {
        iPos = (1000 * m_iFirstLine)
             / (m_iLastLine - m_iWndLines);
    }
    SetScrollPos(SB_VERT, iPos, TRUE);
    Invalidate(FALSE);
	// TODO: Add your message handler code here and/or call default
	
//	CEditView::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CRawView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default

   switch (nChar) {
    case VK_HOME:
        OnVScroll(SB_TOP, 0, NULL);
        break;

    case VK_END:
        OnVScroll(SB_BOTTOM, 0, NULL);
        break;

    case VK_UP:
        OnVScroll(SB_LINEUP, 0, NULL);
        break;

    case VK_DOWN:
        OnVScroll(SB_LINEDOWN, 0, NULL);
        break;

    case VK_PRIOR:
        OnVScroll(SB_PAGEUP, 0, NULL);
        break;

    case VK_NEXT:
        OnVScroll(SB_PAGEDOWN, 0, NULL);
        break;
    
    default:    
        CScrollView::OnKeyDown(nChar, nRepCnt, nFlags);
        break;
    }

	
//	CEditView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CRawView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CScrollView::OnActivateView(bActivate, pActivateView, pDeactiveView);
    theApp.SetStatusBarText(((CViewfileDoc *)GetDocument())->szStatusMessage);

}
