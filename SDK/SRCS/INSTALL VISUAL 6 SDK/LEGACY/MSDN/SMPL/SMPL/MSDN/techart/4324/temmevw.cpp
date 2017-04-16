// TemMevw.cpp : implementation of the CTemMemPtrView class
//

#include "stdafx.h"
#include "TemMemPtr.h"

#include "TemMedoc.h"
#include "TemMevw.h"

#include "TheDialog.h"
#include "TemplateDialog.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTemMemPtrView

IMPLEMENT_DYNCREATE(CTemMemPtrView, CView)

BEGIN_MESSAGE_MAP(CTemMemPtrView, CView)
	//{{AFX_MSG_MAP(CTemMemPtrView)
	ON_COMMAND(ID_CALLIT_FROMVIEW, OnCallitFromview)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTemMemPtrView construction/destruction

CTemMemPtrView::CTemMemPtrView()
{
	// TODO: add construction code here

}

CTemMemPtrView::~CTemMemPtrView()
{
}

/////////////////////////////////////////////////////////////////////////////
// CTemMemPtrView drawing

void CTemMemPtrView::OnDraw(CDC* pDC)
{
	CTemMemPtrDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CTemMemPtrView diagnostics

#ifdef _DEBUG
void CTemMemPtrView::AssertValid() const
{
	CView::AssertValid();
}

void CTemMemPtrView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTemMemPtrDoc* CTemMemPtrView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTemMemPtrDoc)));
	return (CTemMemPtrDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTemMemPtrView message handlers

void CTemMemPtrView::OnCallitFromview() 
{
   CTemplateDialog<CTemMemPtrView> aDlg ;
   aDlg.SetObjectPtr(this) ;
   aDlg.SetMemFunctPtr(&CTemMemPtrView::CalledByDialog) ;

	aDlg.DoModal() ;
		
}

CString& CTemMemPtrView::CalledByDialog()
{
   return CString("Hello from the View class.") ;
}
