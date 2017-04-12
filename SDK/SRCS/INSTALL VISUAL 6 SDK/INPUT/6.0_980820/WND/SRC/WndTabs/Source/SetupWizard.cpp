/***************************************************************************/
/* NOTE:                                                                   */
/* This document is copyright (c) by Oz Solomonovich, and is bound by the  */
/* MIT open source license (www.opensource.org/licenses/mit-license.html). */
/* See License.txt for more information.                                   */
/***************************************************************************/

// SetupWizard.cpp : implementation file
//

#include "stdafx.h"
#include "wndtabs.h"
#include "HHSupp.h"
#include "SetupWizard.h"
#include "ShortcutsDlg.h"
#include "TabActivationShortcutsDlg.h"
#include "Config.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define CPropertySheet CPropertySheetEx
#define CPropertyPage  CSWPageBase

/////////////////////////////////////////////////////////////////////////////
// CSetupWizard

IMPLEMENT_DYNAMIC(CSetupWizard, CPropertySheet)

CSetupWizard::CSetupWizard(HBITMAP hbmWatermark, HBITMAP hbmHeader)
	:CPropertySheet("", 0, 0, hbmWatermark, NULL, hbmHeader)
{
    AddPage(&m_WelcomePage);
    AddPage(&m_KbdPage);
    AddPage(&m_DonePage);

    m_psh.dwFlags |= PSH_WIZARD97;
	m_psh.dwFlags &= ~PSH_HASHELP;
}

CSetupWizard::~CSetupWizard()
{
}


BEGIN_MESSAGE_MAP(CSetupWizard, CPropertySheet)
	//{{AFX_MSG_MAP(CSetupWizard)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSetupWizard message handlers


/////////////////////////////////////////////////////////////////////////////
// CSWPageBase property page

IMPLEMENT_DYNAMIC(CSWPageBase, CPropertyPageEx)

CSWPageBase::CSWPageBase(UINT nIDTemplate, UINT nIDHeaderTitle /*= 0*/, 
     UINT nIDHeaderSubTitle /*= 0*/) : CPropertyPageEx(nIDTemplate, 0, 
     nIDHeaderTitle, nIDHeaderSubTitle)
{
}

CSWPageBase::~CSWPageBase()
{
}

void CSWPageBase::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPageEx::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSWDonePage)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSWPageBase, CPropertyPageEx)
	//{{AFX_MSG_MAP(CSWDonePage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSWPageBase message handlers

BOOL CSWPageBase::OnInitDialog() 
{
	CPropertyPageEx::OnInitDialog();
	
	LOGFONT lf;
	GetFont()->GetLogFont(&lf);
	lf.lfWeight = FW_BOLD;
	m_fontBold.CreateFontIndirect(&lf);

    CWnd *pTitle = GetDlgItem(IDC_TITLE);
    if (pTitle != NULL)
    {
        pTitle->SetFont(&m_fontBold);
    }
	
	return TRUE;
}

BOOL CSWPageBase::OnQueryCancel() 
{
    return (AfxMessageBox(IDS_SW_EXIT_CONFIRM, MB_YESNO | MB_ICONQUESTION) 
        == IDYES);
}

LRESULT CSWPageBase::OnWizardNext() 
{
    UpdateData();
	return CPropertyPageEx::OnWizardNext();
}


/////////////////////////////////////////////////////////////////////////////
// CSWWelcomePage property page

CSWWelcomePage::CSWWelcomePage() : CPropertyPage(CSWWelcomePage::IDD)
{
	//{{AFX_DATA_INIT(CSWWelcomePage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_psp.dwFlags |= PSP_HIDEHEADER;
}


void CSWWelcomePage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSWWelcomePage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSWWelcomePage, CPropertyPage)
	//{{AFX_MSG_MAP(CSWWelcomePage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSWWelcomePage message handlers


/////////////////////////////////////////////////////////////////////////////
// CSWKbdPage property page

IMPLEMENT_DYNCREATE(CSWKbdPage, CPropertyPage)

CSWKbdPage::CSWKbdPage() : CPropertyPage(CSWKbdPage::IDD, 
    IDS_SW_TTL_KBD, IDS_SW_SUBTTL_KBD)
{
	//{{AFX_DATA_INIT(CSWKbdPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CSWKbdPage::~CSWKbdPage()
{
}

void CSWKbdPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSWKbdPage)
	DDX_Control(pDX, IDC_KEYBOARD_CUST_TAB_ACTIVATION, m_btnTabActivation);
	DDX_Control(pDX, IDC_KEYBOARD_CUST, m_btnCommonCommands);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSWKbdPage, CPropertyPage)
	//{{AFX_MSG_MAP(CSWKbdPage)
	ON_BN_CLICKED(IDC_KEYBOARD_CUST, OnKeyboardCust)
	ON_BN_CLICKED(IDC_KEYBOARD_CUST_TAB_ACTIVATION, OnKeyboardCustTabActivation)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSWKbdPage message handlers

BOOL CSWKbdPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
    m_btnCommonCommands.SetImage(IDB_KEYBOARD);
    m_btnTabActivation.SetImage(IDB_TABACTIVATE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSWKbdPage::OnKeyboardCust() 
{
    CShortcutsDlg dlg;
    dlg.DoModal();
}

void CSWKbdPage::OnKeyboardCustTabActivation() 
{
    CTabActivationShortcutsDlg dlg;
    dlg.DoModal();
}


/////////////////////////////////////////////////////////////////////////////
// CSWDonePage property page

IMPLEMENT_DYNCREATE(CSWDonePage, CPropertyPage)

CSWDonePage::CSWDonePage() : CPropertyPage(CSWDonePage::IDD)
{
	//{{AFX_DATA_INIT(CSWDonePage)
	m_bTour = TRUE;
	//}}AFX_DATA_INIT
	m_psp.dwFlags |= PSP_HIDEHEADER;
}

CSWDonePage::~CSWDonePage()
{
}

void CSWDonePage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSWDonePage)
	DDX_Check(pDX, IDC_TOUR, m_bTour);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSWDonePage, CPropertyPage)
	//{{AFX_MSG_MAP(CSWDonePage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSWDonePage message handlers

BOOL CSWDonePage::OnWizardFinish() 
{
    UpdateData();

    CSetupWizard *pWiz = (CSetupWizard *)GetParent();

    // Tour
    if (pWiz->m_DonePage.m_bTour)
    {
        CWaitCursor wc;
        CHyperLink::GotoURL("http://www.wndtabs.com/wt/tour/", SW_SHOWMAXIMIZED);
    }
	
	return CPropertyPage::OnWizardFinish();
}

BOOL CSWDonePage::OnSetActive() 
{
	((CPropertySheet *)GetParent())->SetWizardButtons(
        PSWIZB_BACK | PSWIZB_FINISH);
	
	return CPropertyPage::OnSetActive();
}

LRESULT CSWDonePage::OnWizardBack() 
{
	((CPropertySheet *)GetParent())->SetWizardButtons(
        PSWIZB_BACK | PSWIZB_NEXT);
	
	return CPropertyPage::OnWizardBack();
}
