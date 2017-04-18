// vew.cpp : implementation of the CXlclientView class
//

#include "stdafx.h"
#include "xlclient.h"

#include "doc.h"
#include "view.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CXlclientView

IMPLEMENT_DYNCREATE(CXlclientView, CView)

BEGIN_MESSAGE_MAP(CXlclientView, CView)
	//{{AFX_MSG_MAP(CXlclientView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CXlclientView construction/destruction

CXlclientView::CXlclientView()
{
	// TODO: add construction code here

}

CXlclientView::~CXlclientView()
{
}

BOOL CXlclientView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CXlclientView drawing

void CXlclientView::OnDraw(CDC* pDC)
{
	CXlclientDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CXlclientView printing

BOOL CXlclientView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CXlclientView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CXlclientView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CXlclientView diagnostics

#ifdef _DEBUG
void CXlclientView::AssertValid() const
{
	CView::AssertValid();
}

void CXlclientView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CXlclientDoc* CXlclientView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CXlclientDoc)));
	return (CXlclientDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CXlclientView message handlers
