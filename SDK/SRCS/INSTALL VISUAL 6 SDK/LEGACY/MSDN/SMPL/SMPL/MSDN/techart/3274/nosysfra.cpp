// nosysfra.cpp : implementation file
//

#include "stdafx.h"
#include "viewfile.h"
#include "nosysfra.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNoSysFrame

IMPLEMENT_DYNCREATE(CNoSysFrame, CMDIChildWnd)

CNoSysFrame::CNoSysFrame()
{
}

CNoSysFrame::~CNoSysFrame()
{
}


BEGIN_MESSAGE_MAP(CNoSysFrame, CMDIChildWnd)
	//{{AFX_MSG_MAP(CNoSysFrame)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CNoSysFrame message handlers

BOOL CNoSysFrame::PreCreateWindow(CREATESTRUCT& cs) 
{
    cs.style &= ~WS_SYSMENU;	
	return CMDIChildWnd::PreCreateWindow(cs);
}
