// wordview.cpp : implementation file
//

#include "stdafx.h"
#include "speller.h"
#include "spelldoc.h"
#include "wordview.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWordView

IMPLEMENT_DYNCREATE(CWordView, CFormView)

CWordView::CWordView()
    : CFormView(CWordView::IDD)
{
    //{{AFX_DATA_INIT(CWordView)
    m_strWord = "";
    //}}AFX_DATA_INIT
    m_wavRight.LoadResource(IDR_RIGHT);
    m_wavWrong.LoadResource(IDR_WRONG);
    m_wavSilence.LoadResource(IDR_SILENCE);
    m_wavInstruct.LoadResource(IDR_INSTRUCT);
    m_wavNoWords.LoadResource(IDR_NOWORDS);
    m_iRight = 0;
    m_iWrong = 0;
    // Create the font we will use in the edit control
    m_fntEdit.CreateFont(50, 0,
                         0, 0, FW_BOLD, FALSE, FALSE, FALSE,
                         OEM_CHARSET, OUT_DEFAULT_PRECIS,
                         CLIP_DEFAULT_PRECIS, PROOF_QUALITY,
                         FF_DONTCARE | TMPF_TRUETYPE, "Arial");
    m_uiTimer = 0;
}

CWordView::~CWordView()
{
}

void CWordView::DoDataExchange(CDataExchange* pDX)
{
    CFormView::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CWordView)
    DDX_Control(pDX, IDC_TRYIT, m_wndTryit);
    DDX_Control(pDX, IDC_WORD, m_wndWord);
    DDX_Control(pDX, IDC_SCORE, m_wndScore);
    DDX_Text(pDX, IDC_WORD, m_strWord);
    //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CWordView, CFormView)
    //{{AFX_MSG_MAP(CWordView)
    ON_BN_CLICKED(IDC_PLAYSOUND, OnClickedPlaysound)
    ON_BN_CLICKED(IDC_TRYIT, OnClickedTryit)
    ON_WM_DESTROY()
    ON_WM_TIMER()
    ON_BN_CLICKED(IDC_HELP, OnClickedHelp)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWordView message handlers

void CWordView::OnInitialUpdate()
{
    // Resize the main wndow to fit the dialog template
    // See KB Q98598
    CFormView::OnInitialUpdate();
    GetParentFrame()->RecalcLayout();
    ResizeParentToFit(FALSE);
    ResizeParentToFit(TRUE);

    CSpellerDoc* pDoc = GetDocument();
    CWave* pWave = pDoc->GetCurrentWave();
    if (pWave) {
        pWave->Play();
    }
    // Start the update timer
    RestartTimer();
    m_wndWord.SetFont(&m_fntEdit);
}

void CWordView::OnUpdate(CView* pView, LPARAM lHint, CObject* pObj)
{
}

void CWordView::OnClickedPlaysound()
{
    RestartTimer();
    CSpellerDoc* pDoc = GetDocument();
    CWave* pWave = pDoc->GetCurrentWave();
    if (pWave) {
        pWave->Play();
        m_wndWord.SetFocus();
    } else {
        m_wavNoWords.Play();
        AfxMessageBox("There are no words in the word list to play");
    }
}

void CWordView::OnClickedTryit()
{
    RestartTimer();
    CSpellerDoc* pDoc = GetDocument();
    CString* pStr = pDoc->GetCurrentWord();
    if (!pStr || pStr->IsEmpty()) {
        m_wavNoWords.Play();
        AfxMessageBox("There are no words in the word list to play");
        return;
    }
    // get the edit text
    CString strEdit;
    m_wndWord.GetWindowText(strEdit);
    if (strEdit.CompareNoCase(*pStr) == 0) {
        m_wavRight.Play();
        pDoc->GetNextWord();
        m_wndWord.SetWindowText("");
        m_iRight++;
    } else {
        m_wavWrong.Play();
        m_iWrong++;
    } 
    CWave* pWave = pDoc->GetCurrentWave();
    m_wavSilence.Play();
    if (pWave) pWave->Play();
    m_wndWord.SetFocus();
    char buf[64];
    sprintf(buf, "%d right, %d wrong", m_iRight, m_iWrong);
    m_wndScore.SetWindowText(buf);
}

void CWordView::RestartTimer()
{
    if (m_uiTimer) {
        KillTimer(1);
    }
    // Set it for 20 seconds
    m_uiTimer = SetTimer(1, 20000, NULL);
}

void CWordView::OnDestroy()
{
    CFormView::OnDestroy();
    
    if (m_uiTimer) {
        KillTimer(1);
        m_uiTimer = 0;
    }
}

void CWordView::OnTimer(UINT nIDEvent)
{
    CSpellerDoc* pDoc = GetDocument();
    CWave* pWave = pDoc->GetCurrentWave();
    if (pWave) {
        pWave->Play();
    }
}

void CWordView::OnClickedHelp()
{
    RestartTimer();
    m_wavInstruct.Play();
    m_wndWord.SetFocus();
    RestartTimer();
}
