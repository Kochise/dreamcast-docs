// DlgAdvanced.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "DlgAdvanced.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgAdvanced dialog


CDlgAdvanced::CDlgAdvanced(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAdvanced::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgAdvanced)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgAdvanced::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgAdvanced)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgAdvanced, CDialog)
	//{{AFX_MSG_MAP(CDlgAdvanced)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgAdvanced message handlers
