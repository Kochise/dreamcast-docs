// DDESvvw.cpp : implementation of the CDDEServView class
//

#include "stdafx.h"
#include "DDEServ.h"

#include "DDESvdoc.h"
#include "DDESvvw.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDDEServView

IMPLEMENT_DYNCREATE(CDDEServView, CEditView)

BEGIN_MESSAGE_MAP(CDDEServView, CEditView)
	//{{AFX_MSG_MAP(CDDEServView)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDDEServView construction/destruction

CDDEServView::CDDEServView()
{
    m_font.CreateStockObject(ANSI_FIXED_FONT);
}

CDDEServView::~CDDEServView()
{
}

/////////////////////////////////////////////////////////////////////////////
// CDDEServView drawing

void CDDEServView::OnDraw(CDC* pDC)
{
	CDDEServDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CDDEServView diagnostics

#ifdef _DEBUG
void CDDEServView::AssertValid() const
{
	CEditView::AssertValid();
}

void CDDEServView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}

CDDEServDoc* CDDEServView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDDEServDoc)));
	return (CDDEServDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDDEServView message handlers

int CDDEServView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CEditView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
    GetEditCtrl().SetReadOnly();
    GetEditCtrl().SetFont(&m_font, FALSE);
    m_iCurrentLine = 0;
    PrintLine("Totally bogus DDE server");
    PrintLine("========================");
	
	return 0;
}

void CDDEServView::PrintLine(const char* pszFormat, ...)
{
    char buf[1024];
	va_list arglist;
	va_start(arglist, pszFormat);
    vsprintf(buf, pszFormat, arglist);
	va_end(arglist);
    strcat(buf, "\r\n");

    // add the new line to the edit ctrl
    CEdit& ec = GetEditCtrl();
    int iIndex = ec.LineIndex(m_iCurrentLine);
    ec.SetSel(iIndex, iIndex);
    ec.ReplaceSel(buf);
    m_iCurrentLine++;
}
