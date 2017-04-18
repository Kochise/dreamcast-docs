// outletdl.cpp : implementation file
//

#include "stdafx.h"
#include "House.h"
#include "..\include\ioutlet.h"
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
	DDX_Control(pDX, IDC_OnBtn, m_wndOn);
	DDX_Control(pDX, IDC_OFFBTN, m_wndOff);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COutletDlg, CDialog)
	//{{AFX_MSG_MAP(COutletDlg)
	ON_BN_CLICKED(IDC_OFFBTN, OnOffbtnClicked)
	ON_BN_CLICKED(IDC_OnBtn, OnOnBtnClicked)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// COutletDlg message handlers

void COutletDlg::OnOffbtnClicked() 
{
	ASSERT(m_pIOutlet);
    m_pIOutlet->Off();
    m_pParent->Invalidate(); // repaint	
}

void COutletDlg::OnOnBtnClicked() 
{
	ASSERT(m_pIOutlet);
    m_pIOutlet->On();
    m_pParent->Invalidate(); // repaint	
}

BOOL COutletDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// Make sure we have an outlet to play with
	ASSERT(m_pIOutlet);

    // AddRef it so it can't go away while we are using it
    m_pIOutlet->AddRef();

    // And know which window to repaint for changes
    ASSERT(m_pParent);

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
    // Release the IOutlet interface
    ASSERT(m_pIOutlet);
    m_pIOutlet->Release();
    delete this;
}
