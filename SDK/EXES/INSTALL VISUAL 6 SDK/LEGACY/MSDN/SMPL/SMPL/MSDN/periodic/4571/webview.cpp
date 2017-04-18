/////////////////////////////////////////////////////////////////////////////
// WebView.cpp : implementation of the CWebView class
//
// This is a part of the Webster HTTP Server application
// for Microsoft Systems Journal
//

#include "stdafx.h"
#include "Webster.h"

#include "WebDoc.h"
#include "WebView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWebView

IMPLEMENT_DYNCREATE(CWebView, CScrollView)

BEGIN_MESSAGE_MAP(CWebView, CScrollView)
	//{{AFX_MSG_MAP(CWebView)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWebView construction/destruction

CWebView::CWebView()
{
}

CWebView::~CWebView()
{
}

/////////////////////////////////////////////////////////////////////////////
// CWebView drawing

void CWebView::OnDraw(CDC* pDC)
{
	CWebDoc* pDoc = GetDocument() ;	// we use this a lot...

	// Anything to display?
	pDoc->m_nLines = pDoc->m_strList.GetCount() ;
	if ( pDoc->m_nLines == 0 )
		return ;
	POSITION strPos = pDoc->m_strList.GetHeadPosition() ;
	if ( strPos == NULL )
		return ;

	// Prepare for text drawing
	TEXTMETRIC tm ;
	pDC->GetTextMetrics ( &tm ) ;
	pDC->SetBkMode ( TRANSPARENT ) ;

	// The document owns the list of message strings, so we just walk
	// this list, retrieving and displaying them.
	CString strMsg ;
	strMsg = pDoc->m_strList.GetAt ( strPos ) ;
	for ( int i = 0, yval = 0 ;
		  i < pDoc->m_nLines ;
		  i++, yval += tm.tmHeight )
	{
		pDC->TextOut ( 0, yval,
							strMsg, strMsg.GetLength() ) ;
		if ( strPos == NULL )
			break ;
		strMsg = pDoc->m_strList.GetNext ( strPos ) ;
	}		  
	SetScrollSizes( MM_TEXT, CSize(0, (pDoc->m_nLines+1)*tm.tmHeight));
}

void CWebView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);
}

/////////////////////////////////////////////////////////////////////////////
// CWebView diagnostics

#ifdef _DEBUG
void CWebView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CWebView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CWebDoc* CWebView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWebDoc)));
	return (CWebDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CWebView message handlers
