// viewfvw.cpp : implementation of the CViewfileView class
//

#include "stdafx.h"
#include "viewfile.h"

#include "viewfdoc.h"
#include "viewfvw.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CViewfileView

IMPLEMENT_DYNCREATE(CViewfileView, CView)

BEGIN_MESSAGE_MAP(CViewfileView, CView)
	//{{AFX_MSG_MAP(CViewfileView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CViewfileView construction/destruction

CViewfileView::CViewfileView()
{
	// TODO: add construction code here

}

CViewfileView::~CViewfileView()
{
}

/////////////////////////////////////////////////////////////////////////////
// CViewfileView drawing

void CViewfileView::OnDraw(CDC* pDC)
{
	CViewfileDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CViewfileView printing

BOOL CViewfileView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CViewfileView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CViewfileView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CViewfileView diagnostics

#ifdef _DEBUG
void CViewfileView::AssertValid() const
{
	CView::AssertValid();
}

void CViewfileView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CViewfileDoc* CViewfileView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CViewfileDoc)));
	return (CViewfileDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CViewfileView message handlers
