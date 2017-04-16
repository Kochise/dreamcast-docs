// paldlgcpp : implementation file
//

#include "stdafx.h"
#include "glpal.h"
#include "paldlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPaletteDlg dialog


CPaletteDlg::CPaletteDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPaletteDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPaletteDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	m_bSysColor = TRUE ;
	m_iGamma = 10 ;
	m_b332 = TRUE ;

}


void CPaletteDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPaletteDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPaletteDlg, CDialog)
	//{{AFX_MSG_MAP(CPaletteDlg)
	ON_BN_CLICKED(IDC_332, On332)
	ON_BN_CLICKED(IDC_WASH, OnWash)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CPaletteDlg helper functions

void CPaletteDlg::EnableControls(BOOL bEnable)
{
 	GetDlgItem(IDC_GROUP_PAL)->EnableWindow(bEnable) ;	
 	GetDlgItem(IDC_SYSCLR)->EnableWindow(bEnable) ;	
 	GetDlgItem(IDC_GAMMA_STAT)->EnableWindow(bEnable) ;	
 	GetDlgItem(IDC_GAMMA_1)->EnableWindow(bEnable) ;	
 	GetDlgItem(IDC_GAMMA_2)->EnableWindow(bEnable) ;	
 	GetDlgItem(IDC_GAMMA_3)->EnableWindow(bEnable) ;	
 	GetDlgItem(IDC_GAMMA_4)->EnableWindow(bEnable) ;	
 	GetDlgItem(IDC_GROUP_PAL)->EnableWindow(bEnable) ;	
}
/////////////////////////////////////////////////////////////////////////////
// CPaletteDlg message handlers

void CPaletteDlg::On332() 
{
	EnableControls(TRUE) ;	
}

void CPaletteDlg::OnWash() 
{
	EnableControls(FALSE) ;
}

BOOL CPaletteDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	if (m_b332)
		CheckRadioButton(IDC_332, IDC_WASH, IDC_332) ;
	else
		CheckRadioButton(IDC_332, IDC_WASH, IDC_WASH) ;

	EnableControls(m_b332) ;

	int iGammaBtnID ;
	switch(m_iGamma)
	{
	case 14:
		iGammaBtnID = IDC_GAMMA_2 ;
		break;
	case 18:
		iGammaBtnID = IDC_GAMMA_3 ;
		break;
	case 20:
		iGammaBtnID = IDC_GAMMA_4 ;
		break;
	case 10:
	default:
		iGammaBtnID = IDC_GAMMA_1 ;
		break;
	}
	CheckRadioButton(IDC_GAMMA_1,IDC_GAMMA_4,iGammaBtnID) ;
	CheckDlgButton(IDC_SYSCLR, m_bSysColor) ;
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPaletteDlg::OnOK()
{
	TRACE("OnOK\r\n") ;

	m_b332 = (IDC_332 == GetCheckedRadioButton(IDC_332, IDC_WASH))  ;	
	m_bSysColor  = IsDlgButtonChecked(IDC_SYSCLR) ;

	int iGammaBtnID = GetCheckedRadioButton(IDC_GAMMA_1, IDC_GAMMA_4) ;
	switch(iGammaBtnID)
	{
	case IDC_GAMMA_2 :
		m_iGamma = 14 ;
		break;
	case IDC_GAMMA_3 :
		m_iGamma = 18 ;
		break;
	case IDC_GAMMA_4 :
		m_iGamma = 20 ;
		break;
	case IDC_GAMMA_1 :
	default:
		m_iGamma = 10 ;
		break;
	}
	
	CDialog::OnOK() ;	
}
