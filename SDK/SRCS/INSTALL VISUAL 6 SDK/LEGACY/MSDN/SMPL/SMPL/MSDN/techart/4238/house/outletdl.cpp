// outletdl.cpp : implementation file
//

#include "stdafx.h"
#include "House.h"
#include "..\include\impiunk.h"
#include "..\include\ioutlet.h"
#include "..\include\inotify.h"
#include "..\include\inotifysrc.h"
#include "outletdl.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COutletDlg dialog


COutletDlg::COutletDlg(CWnd* pParent /*=NULL*/)
	: CDialog(COutletDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(COutletDlg)
	//}}AFX_DATA_INIT

	m_pIOutlet = NULL;
    m_pParent = NULL;
}

void COutletDlg::Create()
{
    CDialog::Create(IDD);
}

void COutletDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COutletDlg)
	DDX_Control(pDX, IDC_SWITCH, m_btnSwitch);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COutletDlg, CDialog)
	//{{AFX_MSG_MAP(COutletDlg)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_SWITCH, OnSwitch)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// Interface map for Notification
BEGIN_INTERFACE_MAP(COutletDlg, CDialog)
    INTERFACE_PART(COutletDlg, IID_INotify, Notify)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COutletDlg message handlers

BOOL COutletDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// Make sure we have an outlet to play with
	ASSERT(m_pIOutlet);

    // AddRef it so it can't go away while we are using it
    m_pIOutlet->AddRef();

    // Tell it we'd like change notification
    INotifySrc* pINotifySrc = NULL;
    if (m_pIOutlet->QueryInterface(IID_INotifySrc, (LPVOID*)&pINotifySrc) != S_OK) {

        dprintf2("INotifySrc not supported");
        // Must know which window to repaint for changes
        ASSERT(m_pParent);

    } else {

        // Give the COM object a pointer to our own INotify interface
        // and use the user info ptr to store the object's IUnknown ptr
        m_pINotify = NULL;
        ExternalQueryInterface(&IID_INotify, (LPVOID*)&m_pINotify);
        ASSERT(m_pINotify); 
        pINotifySrc->AddUser(m_pINotify, m_pIOutlet);

        // free the interface
        pINotifySrc->Release();

        // Don't need to do parent notification
        m_pParent = NULL;
    }

    ShowState();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void COutletDlg::OnClose() 
{
    DestroyWindow();
}

// Note: very important for modal dialogs to include
// this handler which is always the last thing called.
// this is where you can safely delete the C++ object
void COutletDlg::PostNcDestroy() 
{
    // Remove the notification event
    INotifySrc* pINotifySrc = NULL;
    m_pIOutlet->QueryInterface(IID_INotifySrc, (LPVOID*)&pINotifySrc);
    ASSERT(pINotifySrc);
    ASSERT(m_pINotify);
    pINotifySrc->RemoveUser(m_pINotify);
    pINotifySrc->Release();

    // Done with our own interface ptr
    m_pINotify->Release();

    // Release the IOutlet interface
    ASSERT(m_pIOutlet);
    m_pIOutlet->Release();
    delete this;
}

void COutletDlg::ShowState()
{
	ASSERT(m_pIOutlet);
    BOOL bState;
    m_pIOutlet->GetState(&bState);
    if (bState) {
        m_btnSwitch.SetWindowText("Off");
    } else {
        m_btnSwitch.SetWindowText("On");
    }
}

void COutletDlg::OnSwitch() 
{
	ASSERT(m_pIOutlet);
    BOOL bState;
    m_pIOutlet->GetState(&bState);
    if (bState) {
        m_pIOutlet->Off();
    } else {
        m_pIOutlet->On();
    }
    ShowState();

    // see if we need to repaint the parent
    if (m_pParent) m_pParent->Invalidate();
}

//////////////////////////////////////////////////////////////////////////////
// INotify

    IMPLEMENT_IUNKNOWN(COutletDlg, Notify)

STDMETHODIMP COutletDlg::XNotify::Change(LPVOID pUserInfo)
{
    METHOD_PROLOGUE(COutletDlg, Notify);

    // The object has changed so redraw to see the effect
    pThis->ShowState();

    return NOERROR;
}

