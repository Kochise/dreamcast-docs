// lecframe.cpp : implementation file
//

#include "stdafx.h"
#include "viewfile.h"

#include "childfrm.h"
#include "lecframe.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLECFrame

IMPLEMENT_DYNCREATE(CLECFrame, CChildFrame)

CLECFrame::CLECFrame()
{
}

CLECFrame::~CLECFrame()
{
}


BEGIN_MESSAGE_MAP(CLECFrame, CChildFrame)
	//{{AFX_MSG_MAP(CLECFrame)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CLECFrame message handlers

BOOL CLECFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
 AfxMessageBox("sorry, the VxD file format is not documented...");
// DestroyWindow();
 return FALSE;
}
