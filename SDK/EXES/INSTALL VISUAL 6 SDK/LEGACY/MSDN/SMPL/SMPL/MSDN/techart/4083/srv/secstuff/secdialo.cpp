// secdialo.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "secdialo.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSecDialog dialog


CSecDialog::CSecDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CSecDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSecDialog)
	m_UserName = _T("");
	m_DomainName = _T("");
	//}}AFX_DATA_INIT
}


void CSecDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSecDialog)
	DDX_Text(pDX, IDC_EDIT1, m_UserName);
	DDX_Text(pDX, IDC_EDIT2, m_DomainName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSecDialog, CDialog)
	//{{AFX_MSG_MAP(CSecDialog)
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	ON_BN_CLICKED(IDC_RADIO3, OnRadio3)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CSecDialog message handlers

void CSecDialog::OnRadio1() 
{
	m_iButtonPushed = IDC_RADIO1;	
}

void CSecDialog::OnRadio2() 
{
	m_iButtonPushed = IDC_RADIO2;	
}

void CSecDialog::OnRadio3() 
{
	m_iButtonPushed = IDC_RADIO3;	
}

BOOL CSecDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	SetWindowText(m_Title);
		
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
