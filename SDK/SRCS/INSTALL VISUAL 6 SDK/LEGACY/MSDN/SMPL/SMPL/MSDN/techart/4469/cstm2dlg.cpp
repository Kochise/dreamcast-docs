// cstm2dlg.cpp : implementation file
//

#include "stdafx.h"
#include "NtDDWzd.h"

#include "resource.h"  // for the constants used in cstmdlg2.h
#include "cstm2dlg.h"
#include "NtDDWzdaw.h"

#ifdef _PSEUDO_DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

DriverOperations g_Operations[MAXOPERATIONS]=
  {
   {IDC_OPERATIONOPEN,"Open","CREATE",0},
   {IDC_OPERATIONCLOSE,"Close","CLOSE",0},
   {IDC_OPERATIONREAD,"Read","READ",0},
   {IDC_OPERATIONWRITE,"Write","WRITE",0},
   {IDC_OPERATIONFLUSH,"Flush","FLUSH_BUFFERS",0},
   {IDC_OPERATIONCLEANUP,"Cleanup","CLEANUP",0},
   {IDC_OPERATIONIOCTL,"IoControl","DEVICE_CONTROL",0},
   {IDC_OPERATIONUNLOAD,NULL,NULL,0},
   {IDC_OPERATIONSTARTIO,NULL,NULL,0}
  };

/////////////////////////////////////////////////////////////////////////////
// CCustom2Dlg dialog


CCustom2Dlg::CCustom2Dlg()
	: CAppWizStepDlg(CCustom2Dlg::IDD)
{
	//{{AFX_DATA_INIT(CCustom2Dlg)
	m_bHasAsynch = FALSE;
	m_iNumDevices = 1;
	//}}AFX_DATA_INIT
	AssignValues(FALSE);
}


void CCustom2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CAppWizStepDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCustom2Dlg)
	DDX_Check(pDX, IDC_ASYNCHIO, m_bHasAsynch);
	DDX_Text(pDX, IDC_EDIT1, m_iNumDevices);
	//}}AFX_DATA_MAP
}

// This is called whenever the user presses Next, Back, or Finish with this step
//  present.  Do all validation & data exchange from the dialog in this function.
BOOL CCustom2Dlg::OnDismiss()
{
	if (!UpdateData(TRUE))
		return FALSE;
	return AssignValues(TRUE);
}

BOOL CCustom2Dlg::AssignValues(BOOL bComesFromDialog)
{
	DefineBoolMacro(_T("MACBASYNC"),m_bHasAsynch);
	DefineIntMacro(_T("NUMDEVICES"),m_iNumDevices);
    CButton *cwndControl;
	DefineBoolMacro(_T("MACBHASIOCTL_ALL"),FALSE);
	for (int i=0; i<MAXOPERATIONS-2; i++)   // RAc
	{
	 if (bComesFromDialog)
	 {
	  cwndControl = (CButton *)GetDlgItem(g_Operations[i].iId);
      if (cwndControl->GetCheck()==1)
	  {
	   DefineStringMacro(_T("OPERATION"),i,g_Operations[i].Name);
	   DefineStringMacro(_T("IRPCODE"),i,g_Operations[i].FullName);
      };
	  if (g_Operations[i].iId == IDC_OPERATIONIOCTL)
	  {
	   DefineBoolMacro(_T("MACBHASIOCTL"),i,TRUE);
	   DefineBoolMacro(_T("MACBHASIOCTL_ALL"),TRUE);
	  };
	 }; // if (bComesFromDialog)
	 DefineIntMacro(_T("OPINDEX"),i,i);
	}; // for loop
    DefineIntMacro(_T("NUM_OPS"),MAXOPERATIONS-2);
	DefineIntMacro(_T("NUM_OPSNOIOCTL"),MAXOPERATIONS-3);
    if (bComesFromDialog)
	{
	 cwndControl = (CButton *)GetDlgItem(IDC_OPERATIONUNLOAD);
	 if (cwndControl->GetCheck()==1)
	  DefineBoolMacro(_T("MACBHASUNLOADROUTINE"),TRUE);
	 cwndControl = (CButton *)GetDlgItem(IDC_OPERATIONSTARTIO);
	 if (cwndControl->GetCheck()==1)
	  DefineBoolMacro(_T("MACBHASSTARTIO"),TRUE);
	};
// now register the number of extra steps...
    if (bComesFromDialog)
	  NtDDWzdaw.RegisterNewSteps(m_iNumDevices-1);    
 	return TRUE;	// return FALSE if the dialog shouldn't be dismissed
}


BEGIN_MESSAGE_MAP(CCustom2Dlg, CAppWizStepDlg)
	//{{AFX_MSG_MAP(CCustom2Dlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CCustom2Dlg message handlers

BOOL CCustom2Dlg::OnInitDialog() 
{
	CAppWizStepDlg::OnInitDialog();
	for (int i=0;i<MAXOPERATIONS;i++)
	  ((CButton *)GetDlgItem(g_Operations[i].iId))->SetCheck(g_Operations[i].iState);
//	m_iNumDevices=1;
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
