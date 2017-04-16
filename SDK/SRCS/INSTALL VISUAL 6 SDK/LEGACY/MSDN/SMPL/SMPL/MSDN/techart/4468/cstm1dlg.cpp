// cstm1dlg.cpp : implementation file
//

#include "stdafx.h"
#include "NtDDWzd.h"

#include "cstm1dlg.h"
#include "NtDDWzdaw.h"

#ifdef _PSEUDO_DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCustom1Dlg dialog


CCustom1Dlg::CCustom1Dlg()
	: CAppWizStepDlg(CCustom1Dlg::IDD)
{
	//{{AFX_DATA_INIT(CCustom1Dlg)
	//}}AFX_DATA_INIT
	m_iLanguageSupported = IDC_GENERATECCODE;

}


void CCustom1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CAppWizStepDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCustom1Dlg)
	//}}AFX_DATA_MAP
}

// This is called whenever the user presses Next, Back, or Finish with this step
//  present.  Do all validation & data exchange from the dialog in this function.
BOOL CCustom1Dlg::OnDismiss()
{
	if (!UpdateData(TRUE))
		return FALSE;
	// TODO: Set template variables based on the dialog's data.
    DefineBoolMacro(_T("MACBCPPSUPPORT"),(m_iLanguageSupported==IDC_GENERATECPPCODE));

	return TRUE;	// return FALSE if the dialog shouldn't be dismissed
}


BEGIN_MESSAGE_MAP(CCustom1Dlg, CAppWizStepDlg)
	//{{AFX_MSG_MAP(CCustom1Dlg)
	ON_BN_CLICKED(IDC_GENERATECCODE, OnGenerateccode)
	ON_BN_CLICKED(IDC_GENERATECPPCODE, OnGeneratecppcode)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CCustom1Dlg message handlers

void CCustom1Dlg::OnGenerateccode() 
{
	m_iLanguageSupported = IDC_GENERATECCODE;
	
}

void CCustom1Dlg::OnGeneratecppcode() 
{
	m_iLanguageSupported = IDC_GENERATECPPCODE;
	
}


BOOL CCustom1Dlg::OnInitDialog() 
{
	CAppWizStepDlg::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_iLanguageSupported = IDC_GENERATECCODE;
    CButton *cwndControl;
	cwndControl = (CButton *)GetDlgItem(m_iLanguageSupported);
	if (cwndControl) cwndControl->SetCheck(1);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

