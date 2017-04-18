// fwtesvw.cpp : implementation of the CFwtestView class
//

#include "stdafx.h"
#include "fwtest.h"

#include "fwtesdoc.h"
#include "fwtesvw.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFwtestView

IMPLEMENT_DYNCREATE(CFwtestView, CView)

BEGIN_MESSAGE_MAP(CFwtestView, CView)
	//{{AFX_MSG_MAP(CFwtestView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFwtestView construction/destruction

CFwtestView::CFwtestView()
{
	// TODO: add construction code here
}

CFwtestView::~CFwtestView()
{
}

/////////////////////////////////////////////////////////////////////////////
// CFwtestView drawing

void CFwtestView::OnDraw(CDC* pDC)
{
	CFwtestDoc* pDoc = GetDocument();

	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CFwtestView printing

BOOL CFwtestView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CFwtestView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CFwtestView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}




/////////////////////////////////////////////////////////////////////////////
// CFwtestView diagnostics

#ifdef _DEBUG
void CFwtestView::AssertValid() const
{
	CView::AssertValid();
}

void CFwtestView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CFwtestDoc* CFwtestView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFwtestDoc)));
	return (CFwtestDoc*) m_pDocument;
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFwtestView message handlers
