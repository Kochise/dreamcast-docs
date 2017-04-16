// vudlg.cpp : implementation file
//

#include "stdafx.h"
#include "animtest.h"
#include "vudlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVUDlg dialog

CVUDlg::CVUDlg(CWnd* pParent /*=NULL*/)
    : CDialog(CVUDlg::IDD, pParent)
{
    //{{AFX_DATA_INIT(CVUDlg)
        // NOTE: the ClassWizard will add member initialization here
    //}}AFX_DATA_INIT
    m_pSB = NULL;
    m_pPal = NULL;  // 9/28/95 NigelT Added palette
}

void CVUDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CVUDlg)
        // NOTE: the ClassWizard will add DDX and DDV calls here
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CVUDlg, CDialog)
    //{{AFX_MSG_MAP(CVUDlg)
    ON_WM_HSCROLL()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVUDlg message handlers

void CVUDlg::OnOK()
{
    // TODO: Add extra validation here
    
    CDialog::OnOK();
}

BOOL CVUDlg::OnInitDialog()
{
    CDialog::OnInitDialog();
    
    m_pSB = (CScrollBar*)GetDlgItem(IDC_SB);
    ASSERT(m_pSB);
    m_pSB->SetScrollRange(0, 32767, FALSE);
    CRect rcVU (10, 10, 250, 210);
    m_VU.Create("VU",
                WS_CHILD | WS_VISIBLE,
                rcVU,
                this,
                1,
                m_pPal); // 9/28/95 NigelT Added palette
    m_VU.SetValue(0, 0);
    
    return TRUE;  // return TRUE  unless you set the focus to a control
}

void CVUDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
    switch (nSBCode) {
    case SB_THUMBTRACK:
    case SB_THUMBPOSITION:
        m_VU.SetValue(nPos, nPos);
        pScrollBar->SetScrollPos(nPos, TRUE);
        break;
    default:
        break;
    }
}
