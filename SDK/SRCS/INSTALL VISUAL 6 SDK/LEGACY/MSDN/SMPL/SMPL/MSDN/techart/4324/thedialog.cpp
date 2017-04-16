// thedialog.cpp : implementation file
//

#include "stdafx.h"
#include "TemMemPtr.h"
#include "thedialog.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTheDialog dialog


CTheDialog::CTheDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CTheDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTheDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CTheDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTheDialog)
	DDX_Control(pDX, IDC_CHANGE, m_staticChange);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTheDialog, CDialog)
	//{{AFX_MSG_MAP(CTheDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CTheDialog message handlers

BOOL CTheDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_staticChange.SetWindowText(CallMemberPtr()) ;
		
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
