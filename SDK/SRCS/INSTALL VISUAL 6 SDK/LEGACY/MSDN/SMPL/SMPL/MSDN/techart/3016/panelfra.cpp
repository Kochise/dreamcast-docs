// panelfra.cpp : implementation file
//

#include "stdafx.h"
#include "fwtest.h"
#include "dlgpanel.h"
#include "dlgpanfm.h"
#include "panelfra.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPanelFrame

IMPLEMENT_DYNCREATE(CPanelFrame, CDlgPanelFrame)

CPanelFrame::CPanelFrame()
{
}

CPanelFrame::~CPanelFrame()
{
}

BEGIN_MESSAGE_MAP(CPanelFrame, CDlgPanelFrame)
    //{{AFX_MSG_MAP(CPanelFrame)
    ON_WM_CREATE()
    ON_BN_CLICKED(IDC_BUTTON, OnClickedButton)
    ON_BN_CLICKED(IDC_RADIO1, OnClickedRadio1)
    ON_BN_CLICKED(IDC_RADIO2, OnClickedRadio2)
    ON_BN_CLICKED(IDC_CHECK, OnClickedCheck)
    ON_LBN_SELCHANGE(IDC_LIST, OnSelchangeList)
    ON_BN_CLICKED(IDC_CLOSE, OnClickedClose)
    ON_WM_HSCROLL()
    ON_WM_VSCROLL()
    ON_CBN_SELCHANGE(IDC_COMBO, OnSelchangeCombo)
    ON_CBN_EDITCHANGE(IDC_COMBO, OnEditchangeCombo)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPanelFrame message handlers

int CPanelFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CDlgPanelFrame::OnCreate(lpCreateStruct) == -1)
        return -1;
    
    // Set the initial state of each control
    CEdit* pE = (CEdit*) m_wndPanel.GetDlgItem(IDC_EDIT);
    ASSERT(pE);
    pE->SetWindowText("Edit Control");

    CListBox* pLB = (CListBox*) m_wndPanel.GetDlgItem(IDC_LIST);
    ASSERT(pLB);
    pLB->AddString("One");
    pLB->AddString("Two");
    pLB->AddString("Three");

    CComboBox* pCB = (CComboBox*) m_wndPanel.GetDlgItem(IDC_COMBO);
    ASSERT(pCB);
    pCB->AddString("Nine");
    pCB->AddString("Ten");
    pCB->AddString("Eleven");
    pCB->SetWindowText("Combo");

    CScrollBar* pSB = (CScrollBar*) m_wndPanel.GetDlgItem(IDC_VSCROLLBAR);
    ASSERT(pSB);
    pSB->SetScrollRange(0, 100);
    pSB->SetScrollPos(50);

    pSB = (CScrollBar*) m_wndPanel.GetDlgItem(IDC_HSCROLLBAR);
    ASSERT(pSB);
    pSB->SetScrollRange(0, 100);
    pSB->SetScrollPos(50);

    CButton* pB = (CButton*) m_wndPanel.GetDlgItem(IDC_RADIO1);
    ASSERT(pB);
    pB->SetCheck(1);

    return 0;
}

void CPanelFrame::OnOK()
{
    AfxMessageBox("Yes, I'm OK. How are you?");
}

void CPanelFrame::OnClickedButton()
{
    AfxMessageBox("You pushed my button!");
}

void CPanelFrame::OnClickedRadio1()
{
    CEdit* pE = (CEdit*) m_wndPanel.GetDlgItem(IDC_EDIT);
    pE->SetWindowText("Radio 1");
}

void CPanelFrame::OnClickedRadio2()
{
    CEdit* pE = (CEdit*) m_wndPanel.GetDlgItem(IDC_EDIT);
    pE->SetWindowText("Radio 2");
}


void CPanelFrame::OnClickedCheck()
{
    CButton* pB = (CButton*) m_wndPanel.GetDlgItem(IDC_CHECK);
    int i = pB->GetCheck();
    CEdit* pE = (CEdit*) m_wndPanel.GetDlgItem(IDC_EDIT);
    pE->SetWindowText(i ? "Checked" : "Unchecked");
}

void CPanelFrame::OnEditchangeCombo()
{
    CComboBox* pCB = (CComboBox*) m_wndPanel.GetDlgItem(IDC_COMBO);
    CString str;
    pCB->GetWindowText(str);
    CEdit* pE = (CEdit*) m_wndPanel.GetDlgItem(IDC_EDIT);
    pE->SetWindowText(str);
}

void CPanelFrame::OnSelchangeList()
{
    CListBox* pLB = (CListBox*) m_wndPanel.GetDlgItem(IDC_LIST);
    int iSel = pLB->GetCurSel();
    ASSERT(iSel != LB_ERR);
    CString str;
    pLB->GetText(iSel, str);
    CEdit* pE = (CEdit*) m_wndPanel.GetDlgItem(IDC_EDIT);
    pE->SetWindowText(str);
}

void CPanelFrame::OnClickedClose()
{
    // Maybe notify someone here
    DestroyWindow();
}

void CPanelFrame::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
    CEdit* pE = (CEdit*) m_wndPanel.GetDlgItem(IDC_EDIT);
    pE->SetWindowText("HScrolling...");
}

void CPanelFrame::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
    CEdit* pE = (CEdit*) m_wndPanel.GetDlgItem(IDC_EDIT);
    pE->SetWindowText("VScrolling...");
}

void CPanelFrame::OnCancel()
{
    AfxMessageBox("OK, I won't do that.");
}

void CPanelFrame::OnSelchangeCombo()
{
    // Handle the CBN_SELCHANGE messages by converting them to 
    // CBN_EDITCHANGE messages.
    // CBN_SELCHANGE occurs before the edit window text has changed and
    // combo-boxes of the drop-down-list style don't send CBN_EDITCHANGE
    // messages so we post the CBN_EDITCHANGE message to ourself

    PostMessage(WM_COMMAND,
                MAKEWPARAM(IDC_COMBO, CBN_EDITCHANGE),
                (LPARAM)(m_wndPanel.GetDlgItem(IDC_COMBO)->m_hWnd));
}

