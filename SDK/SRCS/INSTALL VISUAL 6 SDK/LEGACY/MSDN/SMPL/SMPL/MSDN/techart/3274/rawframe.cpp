// rawframe.cpp : implementation file
//

#include "stdafx.h"
#include "viewfile.h"
//#include "childfrm.h"
#include "rawframe.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRawFrame

IMPLEMENT_DYNCREATE(CRawFrame, CMDIChildWnd)

CRawFrame::CRawFrame()
{
}

CRawFrame::~CRawFrame()
{
}


BEGIN_MESSAGE_MAP(CRawFrame, CMDIChildWnd)
	//{{AFX_MSG_MAP(CRawFrame)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CRawFrame message handlers

BOOL CRawFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
		
	if (!CMDIChildWnd::OnCreateClient(lpcs, pContext)) return FALSE;
    ShowWindow(SW_MINIMIZE);
	return TRUE;
}
