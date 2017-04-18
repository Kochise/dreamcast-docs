// radiodlg.cpp : implementation file
//

#include "stdafx.h"
#include "appliances.h"
#include "resource.h"
#include "..\include\impiunk.h"
#include "..\include\idrawing.h"
#include "..\include\iapplianceui.h"
#include "..\include\ibitmap.h"
#include "..\include\inotify.h"
#include "..\include\inotifysrc.h"
#include "radio.h"
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
    m_punkRadio = NULL;
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

// Interface map for Notification
BEGIN_INTERFACE_MAP(CRadioDlg, CDialog)
    INTERFACE_PART(CRadioDlg, IID_INotify, Notify)
END_INTERFACE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CRadioDlg message handlers

BOOL CRadioDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	ASSERT(m_pRadio);

    ASSERT(m_punkRadio);
    m_punkRadio->AddRef();

    // Tell it we'd like change notification
    INotifySrc* pINotifySrc = NULL;
    if (m_punkRadio->QueryInterface(IID_INotifySrc, (LPVOID*)&pINotifySrc) != S_OK) {
        TRACE("INotifySrc not supported\n");
    } else {

        // Give the COM object a pointer to our own INotify interface
        // and use the user info ptr to store the object's IUnknown ptr
        m_pINotify = NULL;
        ExternalQueryInterface(&IID_INotify, (LPVOID*)&m_pINotify);
        ASSERT(m_pINotify); 
        pINotifySrc->AddUser(m_pINotify, m_punkRadio);

        // free the interface
        pINotifySrc->Release();
    }

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

// Note: very important for modal dialogs to include
// this handler which is always the last thing called.
// this is where you can safely delete the C++ object
void CRadioDlg::PostNcDestroy() 
{
    // Remove the notification event
    INotifySrc* pINotifySrc = NULL;
    m_punkRadio->QueryInterface(IID_INotifySrc, (LPVOID*)&pINotifySrc);
    ASSERT(pINotifySrc);
    ASSERT(m_pINotify);
    pINotifySrc->RemoveUser(m_pINotify);
    pINotifySrc->Release();

    // Done with our own interface ptr
    m_pINotify->Release();

    // Release the ILight interface
    ASSERT(m_punkRadio);
    m_punkRadio->Release();
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

//////////////////////////////////////////////////////////////////////////////
// INotify

    IMPLEMENT_IUNKNOWN(CRadioDlg, Notify)

STDMETHODIMP CRadioDlg::XNotify::Change(LPVOID pUserInfo)
{
    METHOD_PROLOGUE(CRadioDlg, Notify);

    // The object has changed so redraw to see the effect
    pThis->ShowProgram();
    return NOERROR;
}
