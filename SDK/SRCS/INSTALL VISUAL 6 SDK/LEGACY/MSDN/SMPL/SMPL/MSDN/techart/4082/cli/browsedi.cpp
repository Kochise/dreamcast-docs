// browsedi.cpp : implementation file
//

#include "stdafx.h"
#include "cliapp.h"
#include "browsedi.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBrowseDialog dialog

CBrowseDialog::CBrowseDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CBrowseDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBrowseDialog)
	m_TargetName = "";
	//}}AFX_DATA_INIT
}

void CBrowseDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBrowseDialog)
	DDX_Text(pDX, IDC_EDIT1, m_TargetName);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CBrowseDialog, CDialog)
	//{{AFX_MSG_MAP(CBrowseDialog)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBrowseDialog message handlers


BOOL CBrowseDialog::OnInitDialog()
{ CDialog::OnInitDialog();
  SetWindowText(m_Title);
  return TRUE;
};
