// DBview.cpp : implementation of the CDBView class
//

#include "stdafx.h"
#include "DB.h"

#include "DBdoc.h"
#include "DBview.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDBView

IMPLEMENT_DYNCREATE(CDBView, CView)

BEGIN_MESSAGE_MAP(CDBView, CView)
	//{{AFX_MSG_MAP(CDBView)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDBView construction/destruction

CDBView::CDBView()
{
	// TODO: add construction code here

}

CDBView::~CDBView()
{
}

/////////////////////////////////////////////////////////////////////////////
// CDBView drawing

void CDBView::OnDraw(CDC* pDC)
{
	CDBDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDC->TextOut(10,10, pDoc->m_csData); //CPPtoCOM: just display string at fixed position
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CDBView printing

BOOL CDBView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CDBView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CDBView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CDBView diagnostics

#ifdef _DEBUG
void CDBView::AssertValid() const
{
	CView::AssertValid();
}

void CDBView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDBDoc* CDBView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDBDoc)));
	return (CDBDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDBView message handlers

