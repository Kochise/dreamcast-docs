// childfrm.cpp : implementation of the CChildFrame class
//

#include "stdafx.h"
#include "viewfile.h"

#include "fileview.h"
#include "viewfdoc.h"

#include "childfrm.h"

extern CViewfileApp theApp;


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWnd)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWnd)
	//{{AFX_MSG_MAP(CChildFrame)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChildFrame construction/destruction

// note that this will be replaced by a tree view as soon as one becomes available...

CChildFrame::CChildFrame()
{
	// TODO: add member initialization code here
	
}

CChildFrame::~CChildFrame()
{
}

BOOL CChildFrame::OnCreateClient( LPCREATESTRUCT lpcs,
	CCreateContext* pContext)
{
	// TODO: Add your specialized code here and/or call the base class

  if (!m_wndSplitter.CreateStatic( this, m_iNumberRows, m_iNumberCols)) return FALSE;                 
  RECT rcClient;
  GetClientRect(&rcClient);
  int iAverageWidth=(rcClient.right-rcClient.left)/m_iNumberCols;
  int iAverageHeight=(rcClient.bottom-rcClient.top)/m_iNumberRows;
  int iRowC, iColC;
  for (iRowC=0;iRowC<m_iNumberRows;iRowC++)
   for (iColC=0;iColC<m_iNumberCols;iColC++)
    m_wndSplitter.CreateView(iRowC,iColC,m_ViewClass,CSize(iAverageWidth,iAverageHeight),pContext);
  m_AssociatedDocument = (CViewfileDoc *)((CFileView *)m_wndSplitter.GetPane(0,0))->GetDocument();
  return TRUE;

}

/////////////////////////////////////////////////////////////////////////////
// CChildFrame diagnostics

#ifdef _DEBUG
void CChildFrame::AssertValid() const
{
	CMDIChildWnd::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CChildFrame message handlers

BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs) 
{
  cs.style &= ~FWS_ADDTOTITLE;	
  return CMDIChildWnd::PreCreateWindow(cs);
}

