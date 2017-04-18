// dialerdl.cpp : implementation file
//

#include "stdafx.h"
#include <tapi.h>
#include "resource.h"
#include "tapiutils.h"
#include "dialit.h"
#include "dialerdl.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialerDlg dialog


CDialerDlg::CDialerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDialerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialerDlg)
	m_Phone = _T("");
	//}}AFX_DATA_INIT
}


void CDialerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialerDlg)
	DDX_Text(pDX, IDE_PHONE, m_Phone);
	DDV_MaxChars(pDX, m_Phone, 32);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialerDlg, CDialog)
	//{{AFX_MSG_MAP(CDialerDlg)
	ON_BN_CLICKED(ID_DIAL, OnDial)
	ON_BN_CLICKED(ID_HANGUP, OnHangup)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDialerDlg message handlers

void CDialerDlg::OnDial() 
{
    // Dial the call
    m_bCallInProgress = TRUE;

    GetDlgItemText(IDE_PHONE, m_tapiObj.m_szPhoneNumber, 32);
    if (!m_tapiObj.DialCall(m_tapiObj.m_szPhoneNumber))
        OutputDebugString("Dial call failed.\n");
	
}

void CDialerDlg::OnHangup() 
{
    if (m_bCallInProgress)
        m_tapiObj.HangupCall();

    EndDialog(ID_HANGUP);	
}


BOOL CDialerDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

    m_tapiObj.Create(m_szDefaultNumber);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
