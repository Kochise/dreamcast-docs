// tvdlg.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "..\include\idrawing.h"
#include "..\include\iapplianceui.h"
#include "..\include\ibitmap.h"
#include "..\include\inotify.h"
#include "..\include\inotifysrc.h"
#include "appliances.h"
#include "televisi.h"
#include "tvdlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTelevisionDlg dialog


CTelevisionDlg::CTelevisionDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTelevisionDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTelevisionDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
    m_pTV = NULL;
}

void CTelevisionDlg::Create(CWnd* pParent)
{
    CDialog::Create(IDD, pParent);
}

void CTelevisionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTelevisionDlg)
	DDX_Control(pDX, IDC_PWRIND, m_wndPwrInd);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTelevisionDlg, CDialog)
	//{{AFX_MSG_MAP(CTelevisionDlg)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_POWER, OnPowerBtn)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CTelevisionDlg message handlers

BOOL CTelevisionDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	ASSERT(m_pTV);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CTelevisionDlg::OnClose() 
{
    DestroyWindow();
}

void CTelevisionDlg::PostNcDestroy() 
{
    delete this;
}

void CTelevisionDlg::OnPowerBtn() 
{
	// Toggle the TV power state
    m_pTV->Power(!m_pTV->IsOn());

    // Show the new state
    m_wndPwrInd.SetWindowText(m_pTV->IsOn() ? "On" : "Off");
}
