// addwdlg.cpp : implementation file
//

#include "stdafx.h"
#include "speledit.h"
#include "addwdlg.h"
#include "recorddl.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAddWordDlg dialog

CAddWordDlg::CAddWordDlg(CWnd* pParent /*=NULL*/)
    : CDialog(CAddWordDlg::IDD, pParent)
{
    m_pWave = NULL;
    //{{AFX_DATA_INIT(CAddWordDlg)
    m_strText = "";
    //}}AFX_DATA_INIT
}

void CAddWordDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CAddWordDlg)
    DDX_Control(pDX, IDC_PLAY, m_wndPlay);
    DDX_Control(pDX, IDOK, m_wndOK);
    DDX_Control(pDX, IDC_TEXT, m_wndText);
    DDX_Text(pDX, IDC_TEXT, m_strText);
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAddWordDlg, CDialog)
    //{{AFX_MSG_MAP(CAddWordDlg)
    ON_BN_CLICKED(IDC_WAVEFILE, OnClickedWavefile)
    ON_EN_CHANGE(IDC_TEXT, OnChangeText)
    ON_BN_CLICKED(IDC_PLAY, OnClickedPlay)
    ON_BN_CLICKED(IDC_RECORDSOUND, OnClickedRecord)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAddWordDlg message handlers

BOOL CAddWordDlg::OnInitDialog()
{
    CDialog::OnInitDialog();
    
    ASSERT(m_pWave);
    ValidateButtons();    
    return TRUE;  // return TRUE  unless you set the focus to a control
}

void CAddWordDlg::OnClickedRecord()
{
    CRecordDlg dlg;
    if (dlg.DoModal() == IDOK) {
        if (m_pWave) delete m_pWave;
        ASSERT(dlg.m_pWave);
        m_pWave = dlg.m_pWave;
    }
    ValidateButtons();
}

void CAddWordDlg::OnClickedWavefile()
{
    // Show a dialog to allow the user to select a wave file
    CFileDialog dlg (TRUE,    // open
                     NULL,    // no default extension
                     NULL,    // no initial file name
                     OFN_FILEMUSTEXIST
                      | OFN_HIDEREADONLY,
                     "Wave files (*.WAV)|*.WAV|All files (*.*)|*.*||");
    if (dlg.DoModal() == IDOK) {
        CString strFile = dlg.GetPathName();
        m_pWave->Load(strFile);
    }
    ValidateButtons();
}

void CAddWordDlg::OnCancel()
{
    // TODO: Add extra cleanup here
    
    CDialog::OnCancel();
}

void CAddWordDlg::OnOK()
{
    // TODO: Add extra validation here
    
    CDialog::OnOK();
}

void CAddWordDlg::ValidateButtons()
{
    // Get the text for the word
    CString strText;
    m_wndText.GetWindowText(strText);
    // Check we have text and a wave file name
    if (strText.IsEmpty()
    ||  (m_pWave->GetNumSamples() < 100)) {   
        m_wndOK.EnableWindow(FALSE);
    } else {
        m_wndOK.EnableWindow(TRUE);
    }
    if (m_pWave->GetNumSamples() < 100) {
        m_wndPlay.EnableWindow(FALSE);
    } else {
        m_wndPlay.EnableWindow(TRUE);
    }
}

void CAddWordDlg::OnChangeText()
{
    ValidateButtons();
}

void CAddWordDlg::OnClickedPlay()
{
    m_pWave->Play();
}
