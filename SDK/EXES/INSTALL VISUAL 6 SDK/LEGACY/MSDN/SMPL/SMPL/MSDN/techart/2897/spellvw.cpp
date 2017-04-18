// spellvw.cpp : implementation of the CSpellView class
//

#include "stdafx.h"
#include "speledit.h"

#include "spelldoc.h"
#include "spellvw.h"
#include "addwdlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSpellView

IMPLEMENT_DYNCREATE(CSpellView, CView)

BEGIN_MESSAGE_MAP(CSpellView, CView)
    //{{AFX_MSG_MAP(CSpellView)
    ON_COMMAND(ID_EDIT_ADDWORD, OnEditAddWord)
    ON_COMMAND(ID_EDIT_DELETEWORD, OnEditDeleteWord)
    ON_UPDATE_COMMAND_UI(ID_EDIT_DELETEWORD, OnUpdateEditDeleteWord)
    ON_WM_CREATE()
    ON_WM_SIZE()
    ON_WM_SETFOCUS()
    ON_COMMAND(ID_EDIT_PLAY, OnEditPlay)
    ON_UPDATE_COMMAND_UI(ID_EDIT_PLAY, OnUpdateEditPlay)
    ON_LBN_DBLCLK(IDC_LIST, OnDoubleClick)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSpellView construction/destruction

CSpellView::CSpellView()
{
    // TODO: add construction code here
}

CSpellView::~CSpellView()
{
}

/////////////////////////////////////////////////////////////////////////////
// CSpellView drawing

void CSpellView::OnDraw(CDC* pDC)
{
    CSpellDoc* pDoc = GetDocument();

    // TODO: add draw code here
}

void CSpellView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
    switch (lHint) {
    case HINT_NEW_WORD: {
        // Add the new word to the list unless we already have it
        const char* pszWord = (const char*)pHint;
        int iSel = m_wndList.FindStringExact(-1, pszWord);
        if (iSel == LB_ERR) {
            m_wndList.AddString(pszWord);
        }
        m_wndList.SelectString(-1, pszWord);
        } break;

    default: {
        // rebuild the list
        m_wndList.ResetContent();
        CSpellDoc* pDoc = GetDocument();
        POSITION pos = pDoc->m_WordMap.GetStartPosition();
        while(pos) {
            CString strWord;
            CWave* pWave;
            pDoc->m_WordMap.GetNextAssoc(pos, strWord, pWave);
            m_wndList.AddString(strWord);
        }
        } break;
    }
}
 

/////////////////////////////////////////////////////////////////////////////
// CSpellView diagnostics

#ifdef _DEBUG
void CSpellView::AssertValid() const
{
    CView::AssertValid();
}

void CSpellView::Dump(CDumpContext& dc) const
{
    CView::Dump(dc);
}

CSpellDoc* CSpellView::GetDocument() // non-debug version is inline
{
    ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSpellDoc)));
    return (CSpellDoc*) m_pDocument;
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSpellView message handlers

void CSpellView::OnEditAddWord()
{
    // Show the Add Word dialog
    CAddWordDlg dlg;
    dlg.m_pWave = new CWave;
    if (dlg.DoModal() != IDOK) {
        delete dlg.m_pWave;
        return;
    }
    // Add the word to the doc
    CSpellDoc* pDoc = GetDocument();
    if (!pDoc->AddWord(dlg.m_strText, dlg.m_pWave)) {
        delete dlg.m_pWave;
    }
}

void CSpellView::OnEditDeleteWord()
{
    // Get the selected word
    int iSel = m_wndList.GetCurSel();
    if (iSel == LB_ERR) return; // no selection
    CString strWord;
    m_wndList.GetText(iSel, strWord);
    // remove it from the doc
    CSpellDoc* pDoc = GetDocument();
    pDoc->DeleteWord(strWord);
}

void CSpellView::OnUpdateEditDeleteWord(CCmdUI* pCmdUI)
{
    int iSel = m_wndList.GetCurSel();
    pCmdUI->Enable(iSel == LB_ERR ? FALSE : TRUE);
}

int CSpellView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CView::OnCreate(lpCreateStruct) == -1)
        return -1;
    
    // Create the listbox
    CRect rcClient;
    GetClientRect(&rcClient); 
    m_wndList.Create(WS_CHILD | WS_VISIBLE | WS_VSCROLL
                        | LBS_SORT
                        | LBS_DISABLENOSCROLL
                        | LBS_HASSTRINGS
                        | LBS_NOTIFY 
                        | LBS_NOINTEGRALHEIGHT,
                     rcClient,
                     this,
                     IDC_LIST);

    return 0;
}

void CSpellView::OnSize(UINT nType, int cx, int cy)
{
    CView::OnSize(nType, cx, cy);
    
    m_wndList.SetWindowPos(NULL,
                           0, 0,
                           cx, cy,
                           SWP_NOZORDER);
}

void CSpellView::OnSetFocus(CWnd* pOldWnd)
{
    CView::OnSetFocus(pOldWnd);
    
    m_wndList.SetFocus();
}

void CSpellView::OnEditPlay()
{
    int iSel = m_wndList.GetCurSel();
    if(iSel == LB_ERR) return;
    CString strWord;
    m_wndList.GetText(iSel, strWord);
    CSpellDoc* pDoc = GetDocument();
    pDoc->PlayWord(strWord);
}

void CSpellView::OnUpdateEditPlay(CCmdUI* pCmdUI)
{
    int iSel = m_wndList.GetCurSel();
    pCmdUI->Enable(iSel == LB_ERR ? FALSE : TRUE);
}

void CSpellView::OnDoubleClick()
{
    OnEditPlay();
}
