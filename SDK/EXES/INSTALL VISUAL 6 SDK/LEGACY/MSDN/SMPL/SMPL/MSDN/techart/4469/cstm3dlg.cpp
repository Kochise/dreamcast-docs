// cstm3dlg.cpp : implementation file
//

#include "stdafx.h"
#include "NtDDWzd.h"

#include "cstm3dlg.h"
#include "NtDDWzdaw.h"

#ifdef _PSEUDO_DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CCustom3Dlg dialog


CCustom3Dlg::CCustom3Dlg(int i)
	: CAppWizStepDlg(CCustom3Dlg::IDD)
{
    m_iMyIndex = i;
    m_iNameType = IDC_DEVICEUNNAMED;
	m_iLinkNameType = IDC_LINKUNNAMED;

	//{{AFX_DATA_INIT(CCustom3Dlg)
	m_bBuffered = FALSE;
	m_bExclusive = FALSE;
	m_DevName = _T("");
	m_LinkName = _T("");
	m_bHasISR = FALSE;
	//}}AFX_DATA_INIT
	AssignValues(FALSE);
}


void CCustom3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CAppWizStepDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCustom3Dlg)
	DDX_Check(pDX, IDC_BUFFERED, m_bBuffered);
	DDX_Check(pDX, IDC_EXCLUSIVE, m_bExclusive);
	DDX_Text(pDX, IDC_DEVNAME, m_DevName);
	DDX_Text(pDX, IDC_LINKNAME, m_LinkName);
	DDX_Check(pDX, IDC_HASISR, m_bHasISR);
	//}}AFX_DATA_MAP
}

// This is called whenever the user presses Next, Back, or Finish with this step
//  present.  Do all validation & data exchange from the dialog in this function.
BOOL CCustom3Dlg::OnDismiss()
{
	if (!UpdateData(TRUE))
		return FALSE;

	return AssignValues(TRUE);
}

BOOL CCustom3Dlg::AssignValues(BOOL bComesFromDialog)
{
	switch(m_iNameType)
	{
	 case IDC_DEVICENAMEHERE:
	      DefineStringMacro(_T("DEVICENAME"),m_iMyIndex,m_DevName);
		  DefineBoolMacro(_T("MACBSUPPLIESNAME"),m_iMyIndex,TRUE);
	      DefineBoolMacro(_T("MACBCOMPUTESNAME"),m_iMyIndex,FALSE);
	      DefineBoolMacro(_T("MACBUNNAMED"),m_iMyIndex,FALSE);
		  break;
	 case IDC_DEVICEDYNA:
	      DefineBoolMacro(_T("MACBCOMPUTESNAME"),m_iMyIndex,TRUE);
		  DefineBoolMacro(_T("MACBSUPPLIESNAME"),m_iMyIndex,FALSE);
	      DefineBoolMacro(_T("MACBUNNAMED"),m_iMyIndex,FALSE);

		  break;
     case IDC_DEVICEUNNAMED:
	      DefineBoolMacro(_T("MACBUNNAMED"),m_iMyIndex,TRUE);
	      DefineBoolMacro(_T("MACBCOMPUTESNAME"),m_iMyIndex,FALSE);
		  DefineBoolMacro(_T("MACBSUPPLIESNAME"),m_iMyIndex,FALSE);
		  break;
	};
	switch(m_iLinkNameType)
	{
	 case IDC_LINKNAMEHERE:
	      DefineStringMacro(_T("LINKNAME"),m_iMyIndex,m_LinkName);
		  DefineBoolMacro(_T("MACBSUPPLIESLNAME"),m_iMyIndex,TRUE);
	      DefineBoolMacro(_T("MACBCOMPUTESLNAME"),m_iMyIndex,FALSE);
	      DefineBoolMacro(_T("MACBLUNNAMED"),m_iMyIndex,FALSE);
		  break;
	 case IDC_LINKDYNA:
	      DefineBoolMacro(_T("MACBCOMPUTESLNAME"),m_iMyIndex,TRUE);
		  DefineBoolMacro(_T("MACBSUPPLIESLNAME"),m_iMyIndex,FALSE);
	      DefineBoolMacro(_T("MACBLUNNAMED"),m_iMyIndex,FALSE);

		  break;
     case IDC_LINKUNNAMED:
	      DefineBoolMacro(_T("MACBLUNNAMED"),m_iMyIndex,TRUE);
	      DefineBoolMacro(_T("MACBCOMPUTESLNAME"),m_iMyIndex,FALSE);
		  DefineBoolMacro(_T("MACBSUPPLIESLNAME"),m_iMyIndex,FALSE);
		  break;
	};

	 DefineBoolMacro(_T("MACBEXCLUSIVE"),m_iMyIndex,m_bExclusive);
     DefineBoolMacro(_T("MACBBUFFERED"),m_iMyIndex,m_bBuffered);
	 DefineBoolMacro(_T("MACBHASISR"),m_iMyIndex,m_bHasISR);
     DefineIntMacro(_T("INDEX"),m_iMyIndex,m_iMyIndex);
	return TRUE;	// return FALSE if the dialog shouldn't be dismissed
}


BEGIN_MESSAGE_MAP(CCustom3Dlg, CAppWizStepDlg)
	//{{AFX_MSG_MAP(CCustom3Dlg)
	ON_EN_SETFOCUS(IDC_DEVNAME, OnSetfocusDevname)
	ON_BN_CLICKED(IDC_DEVICEUNNAMED, OnDeviceunnamed)
	ON_EN_SETFOCUS(IDC_LINKNAME, OnSetfocusLinkname)
	ON_BN_CLICKED(IDC_LINKDYNA, OnLinkdyna)
	ON_BN_CLICKED(IDC_LINKNAMEHERE, OnLinknamehere)
	ON_BN_CLICKED(IDC_LINKUNNAMED, OnLinkunnamed)
	ON_BN_CLICKED(IDC_DEVICENAMEHERE, OnDevicenamehere)
	ON_BN_CLICKED(IDC_DEVICEDYNA, OnDevicedyna)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CCustom3Dlg message handlers

void CCustom3Dlg::OnSetfocusDevname() 
{
    CheckRadioButton(IDC_DEVICEUNNAMED,IDC_DEVICENAMEHERE,IDC_DEVICENAMEHERE);
	m_iNameType=IDC_DEVICENAMEHERE;
}

void CCustom3Dlg::OnDeviceunnamed() 
{
  m_iNameType = IDC_DEVICEUNNAMED;	
  CheckRadioButton(IDC_LINKUNNAMED,IDC_LINKNAMEHERE,IDC_LINKUNNAMED);

}

void CCustom3Dlg::OnDevicenamehere() 
{
 m_iNameType = IDC_DEVICENAMEHERE;	
}

void CCustom3Dlg::OnDevicedyna() 
{
 m_iNameType = IDC_DEVICEDYNA;	
}


BOOL CCustom3Dlg::OnInitDialog() 
{
	CAppWizStepDlg::OnInitDialog();
	
	CWnd *cwndHeader = GetDlgItem(IDC_BOXHEADER);
	char szBuf[30];
	sprintf(szBuf,"Name for device %d",m_iMyIndex);
	cwndHeader->SetWindowText(szBuf);
    CheckRadioButton(IDC_DEVICEUNNAMED,IDC_DEVICENAMEHERE,IDC_DEVICEUNNAMED);
    m_iNameType = IDC_DEVICEUNNAMED;
    CheckRadioButton(IDC_LINKUNNAMED,IDC_LINKNAMEHERE,IDC_LINKUNNAMED);
	m_iLinkNameType = IDC_LINKUNNAMED;
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CCustom3Dlg::OnSetfocusLinkname() 
{
 if (m_iNameType == IDC_DEVICEUNNAMED)	
  {
   CheckRadioButton(IDC_LINKUNNAMED,IDC_LINKNAMEHERE,IDC_LINKUNNAMED);
   GetDlgItem(IDC_DEVICEUNNAMED)->SetFocus();
   m_iLinkNameType = IDC_LINKUNNAMED;
   }
 else
  {
   CheckRadioButton(IDC_LINKUNNAMED,IDC_LINKNAMEHERE,IDC_LINKNAMEHERE);
   m_iLinkNameType = IDC_LINKNAMEHERE;
  };	
}

void CCustom3Dlg::OnLinkdyna() 
{
 if (m_iNameType == IDC_DEVICEUNNAMED)
 {	
  CheckRadioButton(IDC_LINKUNNAMED,IDC_LINKNAMEHERE,IDC_LINKUNNAMED);
  m_iLinkNameType = IDC_LINKUNNAMED;
 }
 else
 m_iLinkNameType=IDC_LINKDYNA;	
}

void CCustom3Dlg::OnLinknamehere() 
{
 if (m_iNameType == IDC_DEVICEUNNAMED)	
 {
  CheckRadioButton(IDC_LINKUNNAMED,IDC_LINKNAMEHERE,IDC_LINKUNNAMED);
  m_iLinkNameType;
 }
 else
 m_iLinkNameType=IDC_LINKNAMEHERE;	
}

void CCustom3Dlg::OnLinkunnamed() 
{
 if (m_iNameType == IDC_DEVICEUNNAMED)	
  CheckRadioButton(IDC_LINKUNNAMED,IDC_LINKNAMEHERE,IDC_LINKUNNAMED);
 else
 m_iLinkNameType=IDC_LINKUNNAMED;	
}


