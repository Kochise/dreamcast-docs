// formwnd.cpp : implementation file
//

#include "stdafx.h"
#include "auxdata.h"
#include "formwnd.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFormWnd

IMPLEMENT_DYNAMIC(CFormWnd, CWnd)

BEGIN_MESSAGE_MAP(CFormWnd, CWnd)
    //{{AFX_MSG_MAP(CFormWnd)
    ON_WM_CREATE()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

CFormWnd::CFormWnd(LPCSTR lpszTemplateName)
{
    m_lpszTemplateName = lpszTemplateName;
    m_pCreateContext = NULL;
}

CFormWnd::CFormWnd(UINT nIDTemplate)
{
    m_lpszTemplateName = MAKEINTRESOURCE(nIDTemplate);
    m_pCreateContext = NULL;
}

// virtual override of CWnd::Create
BOOL CFormWnd::Create(LPCSTR /*lpszClassName ignored*/,
    LPCSTR /*lpszWindowName ignored*/, DWORD dwRequestedStyle,
    const RECT& rect, CWnd* pParentWnd, UINT nID,
    CCreateContext* pContext)
{
    ASSERT(pParentWnd != NULL);
    ASSERT(m_lpszTemplateName != NULL);

    m_pCreateContext = pContext;    // save state for later OnCreate

#ifdef _DEBUG
    // dialog template must exist and be invisible with WS_CHILD set
    if (!_AfxCheckDialogTemplate(m_lpszTemplateName, TRUE))
    {
        ASSERT(FALSE);          // invalid dialog template name
        PostNcDestroy();        // cleanup if Create fails too soon
        return FALSE;
    }
#endif //_DEBUG

    HINSTANCE hInst = AfxGetResourceHandle();

    _AfxHookWindowCreate(this);
    HWND hWnd = ::CreateDialog(hInst, m_lpszTemplateName,
            pParentWnd->GetSafeHwnd(), NULL);
    if (!_AfxUnhookWindowCreate())
        PostNcDestroy();        // cleanup if Create fails too soon

    if (hWnd == NULL)
        return FALSE;

    ASSERT(hWnd == m_hWnd);
    m_pCreateContext = NULL;

    // we use the style from the template - but make sure that
    //  the WS_BORDER bit is correct
    DWORD dwStyle = GetStyle();
    if ((dwStyle & WS_BORDER) != (dwRequestedStyle & WS_BORDER))
    {
        // toggle WS_BORDER on invisible window
        ::SetWindowLong(m_hWnd, GWL_STYLE, dwStyle ^ WS_BORDER);
    }

    _AfxSetDlgCtrlID(m_hWnd, nID);

    CRect rectTemplate;
    GetWindowRect(rectTemplate);
    SetScrollSizes(MM_TEXT, rectTemplate.Size());

    // initialize controls etc
    if (!ExecuteDlgInit(m_lpszTemplateName))
        return FALSE;

    // force the size requested
    SetWindowPos(NULL, rect.left, rect.top,
        rect.right - rect.left, rect.bottom - rect.top,
        SWP_NOZORDER|SWP_NOACTIVATE);

    // make visible if requested
    if (dwRequestedStyle & WS_VISIBLE)
        ShowWindow(SW_NORMAL);

    return TRUE;
}

void CFormWnd::OnInitialUpdate()
{
    ASSERT_VALID(this);

    if (!UpdateData(FALSE))
        TRACE0("UpdateData failed during formview initial update\n");
    CWnd::OnInitialUpdate();
}

int CFormWnd::OnCreate(LPCREATESTRUCT lpcs)
{
    // since we can't get the create context parameter passed in
    //  through CreateDialog, we use a temporary member variable
    lpcs->lpCreateParams = (LPSTR)m_pCreateContext;
    return CWnd::OnCreate(lpcs);
}

BOOL CFormWnd::PreTranslateMessage(MSG* pMsg)
{
    ASSERT(pMsg != NULL);
    ASSERT_VALID(this);
    ASSERT(m_hWnd != NULL);

    // don't translate dialog messages when in Shift+F1 help mode
    if (AfxGetApp()->m_bHelpMode)
        return FALSE;

    // since 'IsDialogMessage' will eat frame window accelerators,
    //   we call the frame window's PreTranslateMessage first
    CWnd* pFrame;
    if ((pFrame = GetParentFrame()) != NULL)
    {
        if (pFrame->PreTranslateMessage(pMsg))
            return TRUE;        // eaten by frame accelerator
        // check for parent of the frame in case of MDI
        if ((pFrame = pFrame->GetParentFrame()) != NULL &&
          pFrame->PreTranslateMessage(pMsg))
            return TRUE;        // eaten by frame accelerator
    }

    // filter both messages to dialog and from children
    return ::IsDialogMessage(m_hWnd, pMsg);
}


void CFormWnd::OnDraw(CDC* pDC)
{
    ASSERT_VALID(this);

    // do nothing - dialog controls will paint themselves,
    //   and Windows dialog controls do not support printing
    if (pDC->IsPrinting())
        TRACE0("Warning: CFormWnd does not support printing\n");
}

WNDPROC* CFormWnd::GetSuperWndProcAddr()
{
    static WNDPROC NEAR pfnSuper;
    return &pfnSuper;
}

//////////////////////////////////////////////////////////////////////////
// CFormWnd diagnostics

#ifdef _DEBUG
void CFormWnd::Dump(CDumpContext& dc) const
{
    ASSERT_VALID(this);
    CView::Dump(dc);
    AFX_DUMP0(dc, "\nm_lpszTemplateName = ");
    if (HIWORD(m_lpszTemplateName) == 0)
        dc << (int)LOWORD(m_lpszTemplateName);
    else
        dc << m_lpszTemplateName;
}

void CFormWnd::AssertValid() const
{
    CView::AssertValid();
}
#endif

//////////////////////////////////////////////////////////////////////////
