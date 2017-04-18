// ctlrevw.cpp : implementation of the CCtlregView class
//

#include "stdafx.h"
#include "ctlreg.h"

#include "ctlredoc.h"
#include "ctlrevw.h"
#include "cctlreg.h"
#include "unregdlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCtlregView

IMPLEMENT_DYNCREATE(CCtlregView, CView)

BEGIN_MESSAGE_MAP(CCtlregView, CView)
	//{{AFX_MSG_MAP(CCtlregView)
	ON_COMMAND(IDM_CONTROLS_REGISTER, OnControlsRegister)
	ON_COMMAND(IDM_CONTROLS_UNREGISTER, OnControlsUnregister)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCtlregView construction/destruction

CCtlregView::CCtlregView()
{
}

CCtlregView::~CCtlregView()
{
}

/////////////////////////////////////////////////////////////////////////////
// CCtlregView drawing

void CCtlregView::OnDraw(CDC* pDC)
{
	CCtlregDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
}

/////////////////////////////////////////////////////////////////////////////
// CCtlregView diagnostics

#ifdef _DEBUG
void CCtlregView::AssertValid() const
{
	CView::AssertValid();
}

void CCtlregView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCtlregDoc* CCtlregView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCtlregDoc)));
	return (CCtlregDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCtlregView message handlers

void CCtlregView::OnControlsRegister() 
{
	static char BASED_CODE szFilter[] = "OLE controls (*.ocx) | *.ocx | DLL's (*.dll) | *.dll | OCX and DLL (*.ocx; *.dll) | *.ocx;*.dll | All Files (*.*) | *.* ||" ;

	CFileDialog aDlg(TRUE, "OCX", "*.ocx",OFN_PATHMUSTEXIST	|OFN_FILEMUSTEXIST ,szFilter,this ) ;	

	if (aDlg.DoModal() == IDOK)
	{
	   CString strCtlPathName = aDlg.GetPathName() ;
	   CCtlReg aCtlReg(strCtlPathName) ;
	   if (aCtlReg.Register())
	   {
	   		MessageBox("Successful control registration.","Control Registration.",MB_OK | MB_ICONINFORMATION) ;
	   }
	   else
	   {
	   		MessageBox("Control registration failed.",NULL,MB_OK | MB_ICONEXCLAMATION) ;
	   }
	}	
}

void CCtlregView::OnControlsUnregister() 
{
	CUnregisterDlg dlgUnReg(this);

	if(dlgUnReg.DoModal() == IDOK)
	{
		CCtlReg aCtlReg(dlgUnReg.m_strThePath); 
		if (aCtlReg.Unregister())
		{
			MessageBox("Control unregistered successfully.","Control Registration.",MB_OK | MB_ICONINFORMATION) ;
		}
		else
		{
			MessageBox("Unable to unregister control.",NULL,MB_OK | MB_ICONEXCLAMATION) ;
		}		
	}
}
