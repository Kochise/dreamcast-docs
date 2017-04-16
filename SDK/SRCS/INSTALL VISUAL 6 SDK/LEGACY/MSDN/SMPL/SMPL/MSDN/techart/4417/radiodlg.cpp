// radiodlg.cpp : implementation file
//

#include "stdafx.h"
#include "COMBASE.h"
#include "MI_Appliances.h"
#include "resource.h"
#include "..\include\idrawing.h"
#include "..\include\iapplianceui.h"
#include "CRadio.h"
#include "radiodlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRadioDlg dialog


CRadioDlg::CRadioDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRadioDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRadioDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

    m_pRadio = NULL;
}

void CRadioDlg::Create(CWnd* pParent)
{
    CDialog::Create(IDD, pParent);
}

void CRadioDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRadioDlg)
	DDX_Control(pDX, IDC_PWRIND, m_wndPwrInd);
	DDX_Control(pDX, IDC_STATION4, m_wndStation4);
	DDX_Control(pDX, IDC_STATION3, m_wndStation3);
	DDX_Control(pDX, IDC_STATION2, m_wndStation2);
	DDX_Control(pDX, IDC_STATION1, m_wndStation1);
	DDX_Control(pDX, IDC_POWER, m_wndPower);
	DDX_Control(pDX, IDC_FREQUENCY, m_wndFrequency);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRadioDlg, CDialog)
	//{{AFX_MSG_MAP(CRadioDlg)
	ON_BN_CLICKED(IDC_POWER, OnPowerBtn)
	ON_BN_CLICKED(IDC_STATION1, OnStation1)
	ON_BN_CLICKED(IDC_STATION2, OnStation2)
	ON_BN_CLICKED(IDC_STATION3, OnStation3)
	ON_BN_CLICKED(IDC_STATION4, OnStation4)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CRadioDlg message handlers

BOOL CRadioDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	ASSERT(m_pRadio);

    // Show the current state
    m_wndFrequency.EnableWindow(FALSE); // For display only
    m_wndFrequency.SetRange(88, 108);
    ShowProgram();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CRadioDlg::OnClose() 
{
    DestroyWindow();
}

void CRadioDlg::PostNcDestroy() 
{
    delete this;
}

void CRadioDlg::OnPowerBtn() 
{
	// Toggle the radio power state
    m_pRadio->Power(!m_pRadio->IsOn());
    ShowProgram();
}

void CRadioDlg::OnStation1() 
{
	m_pRadio->SetStation(1);
    ShowProgram();
}

void CRadioDlg::OnStation2() 
{
	m_pRadio->SetStation(2);
    ShowProgram();
}

void CRadioDlg::OnStation3() 
{
	m_pRadio->SetStation(3);
    ShowProgram();
}

void CRadioDlg::OnStation4() 
{
	m_pRadio->SetStation(4);
    ShowProgram();
}

void CRadioDlg::ShowProgram()
{
    // Set the frequency indicator to show the current station
    int iMin, iMax;
    m_wndFrequency.GetRange(iMin, iMax);
    m_wndFrequency.SetPos(iMin + m_pRadio->GetStation() * (iMax - iMin) / 5);
    m_wndPwrInd.SetWindowText(m_pRadio->IsOn() ? "On" : "Off");
}
