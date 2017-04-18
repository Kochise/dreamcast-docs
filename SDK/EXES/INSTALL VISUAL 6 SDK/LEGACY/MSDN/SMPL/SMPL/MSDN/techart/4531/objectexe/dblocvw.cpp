// DBLocvw.cpp : implementation of the CDBLocalView class
//

#include "stdafx.h"
#include "DBLocal.h"

#include "DBLocdoc.h"
#include "DBLocvw.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDBLocalView

IMPLEMENT_DYNCREATE(CDBLocalView, CView)

BEGIN_MESSAGE_MAP(CDBLocalView, CView)
	//{{AFX_MSG_MAP(CDBLocalView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDBLocalView construction/destruction

CDBLocalView::CDBLocalView()
{
	// TODO: add construction code here

}

CDBLocalView::~CDBLocalView()
{
}

/////////////////////////////////////////////////////////////////////////////
// CDBLocalView drawing

void CDBLocalView::OnDraw(CDC* pDC)
{
	CDBLocalDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CDBLocalView printing

BOOL CDBLocalView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CDBLocalView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CDBLocalView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CDBLocalView diagnostics

#ifdef _DEBUG
void CDBLocalView::AssertValid() const
{
	CView::AssertValid();
}

void CDBLocalView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDBLocalDoc* CDBLocalView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDBLocalDoc)));
	return (CDBLocalDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDBLocalView message handlers
