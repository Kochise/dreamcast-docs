// tpprops.cpp : implementation file
//

#include "stdafx.h"
#include "dldetect.h"
#include "tpprops.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTPProps dialog

CTPProps::CTPProps(CWnd* pParent /*=NULL*/)
	: CDialog(CTPProps::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTPProps)
	m_Name = "";
	//}}AFX_DATA_INIT
}

void CTPProps::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTPProps)
	DDX_Text(pDX, IDD_DIALOG1, m_Name);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTPProps, CDialog)
	//{{AFX_MSG_MAP(CTPProps)
	ON_BN_CLICKED(IDC_CHECK2, OnClickedCheck2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTPProps message handlers


void CTPProps::OnClickedCheck2()
{
m_Marked=!m_Marked;
	
}

BOOL CTPProps::OnInitDialog()
{ CButton *cdControl;
	CDialog::OnInitDialog();
	cdControl = (CButton *)GetDlgItem(IDC_CHECK2);
	if (m_iType&PLACE_TYPE)
	 {cdControl->EnableWindow(TRUE);
	  if (m_Marked) cdControl->SetCheck(1);
	  else cdControl->SetCheck(0);
	 }
	 else
	 cdControl->EnableWindow(FALSE);
	 cdControl=(CButton *)GetDlgItem(IDC_CHECK1);
	return TRUE;  // return TRUE  unless you set the focus to a control
}
