// DontShowAgainDlg.cpp : implementation file
//

#include "stdafx.h"
#include "wndtabs.h"
#include "DontShowAgainDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDontShowAgainDlg dialog


CDontShowAgainDlg::CDontShowAgainDlg(
    LPCTSTR pszText, 
    BOOL& bShowIt,
    UINT nType /*= MB_OK | MB_ICONEXCLAMATION*/, 
    LPCTSTR pszDontAskText /*= NULL*/,
    LPCTSTR pszCaption /*= NULL*/) : CDialog(IDD_DONT_SHOW_AGAIN),
        m_bShowIt(bShowIt),
        m_nType(nType), m_pszDontShowText(pszDontAskText), 
        m_pszCaption(pszCaption)
{
	//{{AFX_DATA_INIT(CDontShowAgainDlg)
	m_bDontShowAgain = !bShowIt;
	//}}AFX_DATA_INIT

    m_sText = pszText;
}


void CDontShowAgainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDontShowAgainDlg)
	DDX_Control(pDX, IDC_STATIC_ICON, m_Icon);
	DDX_Check(pDX, IDC_DONT_SHOW_AGAIN, m_bDontShowAgain);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDontShowAgainDlg, CDialog)
	//{{AFX_MSG_MAP(CDontShowAgainDlg)
	ON_BN_CLICKED(IDC_DONT_SHOW_AGAIN, OnDontShowAgain)
	ON_BN_CLICKED(IDYES, OnYes)
	ON_BN_CLICKED(IDNO, OnNo)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDontShowAgainDlg message handlers

BOOL CDontShowAgainDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

    CWnd *pWndDontShowText = GetDlgItem(IDC_DONT_SHOW_AGAIN);
    CWnd *pMainTxt = GetDlgItem(IDC_TEXT);
    CRect r;

    pMainTxt->GetWindowRect(r);

    CSize sz, sz_accumulated(0, 0);
    CDC *pDC = GetDC();
    CFont *pOldFont;

    pOldFont = pDC->GetCurrentFont();
    pDC->SelectObject(GetFont());

    CString cStr;
    int i = 0;
    while (AfxExtractSubString(cStr, m_sText, i))
    {
        ++i;
        cStr += ' ';
        sz = pDC->GetTabbedTextExtent(cStr, 0, NULL);
        if (sz_accumulated.cx < sz.cx)
        {
            sz_accumulated.cx = sz.cx;
        }
        sz_accumulated.cy += sz.cy;
    }
    pDC->SelectObject(pOldFont);
	ReleaseDC(pDC);

    CSize sz_diff(0, 0);
    
    if (r.Height() < sz_accumulated.cy)
    {
        sz_diff.cy = sz_accumulated.cy - r.Height();
    }
    if (r.Width() < sz_accumulated.cx)
    {
        sz_diff.cx = sz_accumulated.cx - r.Width();
    }

    r.bottom += sz_diff.cy;
    r.right  += sz_diff.cx;
    ScreenToClient(r);
    pMainTxt->MoveWindow(r);
   
    CWnd *pWnd = pMainTxt->GetNextWindow();
    while (pWnd)
    {
        pWnd->GetWindowRect(r);
        ScreenToClient(r);
        if (!pWnd->GetNextWindow())
        {
            r.OffsetRect(0, sz_diff.cy);
        }
        else
        {
            r.OffsetRect(sz_diff.cx / 2, sz_diff.cy);
        }
        pWnd->MoveWindow(r);
        pWnd = pWnd->GetNextWindow();
    }

    GetWindowRect(r);
    r.bottom += sz_diff.cy;
    r.right  += sz_diff.cx;
    MoveWindow(r);

    if (m_pszCaption)
    {
        SetWindowText(m_pszCaption);
    }
    else
    {
        SetWindowText(AfxGetApp()->m_pszAppName);
    }

    if (m_pszDontShowText)
    {
        pWndDontShowText->SetWindowText(m_pszDontShowText);
    }
    else
    {
        CString s;
        s.LoadString(IDS_DONT_SHOW_MSG_AGAIN);
        pWndDontShowText->SetWindowText(s);
    }
     
    WT_ASSERT(m_nType & MB_ICONMASK);

    char *icon;
    switch (m_nType & MB_ICONMASK)
    {
        case MB_ICONEXCLAMATION:
            icon = IDI_EXCLAMATION;
            break;

        case MB_ICONHAND:
            icon = IDI_HAND;
            break;

        case MB_ICONQUESTION:
            icon = IDI_QUESTION;
            break;

        case MB_ICONASTERISK:
            icon = IDI_ASTERISK;
            break;

        DEFAULT_UNREACHABLE;
    }

    MessageBeep(m_nType & MB_ICONMASK);

    m_Icon.SetIcon(AfxGetApp()->LoadStandardIcon(icon));

    int idDefButton;
    if (m_nType & MB_YESNO)
    {
        GetDlgItem(IDYES)->ShowWindow(SW_SHOW);
        GetDlgItem(IDNO)->ShowWindow(SW_SHOW);
        idDefButton = IDYES;
    }
    else
    {
        idDefButton = IDOK;
        GetDlgItem(IDOK)->ShowWindow(SW_SHOW);
    }
    ((CButton *)GetDlgItem(idDefButton))->SetButtonStyle(BS_DEFPUSHBUTTON);

    if (m_nType & MB_TOPMOST)
    {
        SetWindowPos(&wndTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
    }

    CenterWindow();
	
	return TRUE;  
}

void CDontShowAgainDlg::OnYes() 
{
    EndDialog(IDYES);
}

void CDontShowAgainDlg::OnNo() 
{
    EndDialog(IDNO);
}

void CDontShowAgainDlg::OnDontShowAgain() 
{
	UpdateData();
    m_bShowIt = !m_bDontShowAgain;
}

int CDontShowAgainDlg::DoMessageBox(LPCTSTR lpszText, BOOL& bShowIt, 
    UINT nType, LPCTSTR pszDontShowAgainTxt)
{
    if (bShowIt)
    {
        CDontShowAgainDlg dlg(lpszText, bShowIt, nType, 
            pszDontShowAgainTxt);
        return dlg.DoModal();
    }

    return IDCANCEL;
}

int CDontShowAgainDlg::DoMessageBox(int idTextRes, BOOL& bShowIt, UINT nType,
    LPCTSTR pszDontShowAgainTxt)
{
    CString str;
    str.LoadString(idTextRes);
    return DoMessageBox(str, bShowIt, nType, pszDontShowAgainTxt);
}

void CDontShowAgainDlg::OnPaint() 
{
    Default();
	CClientDC dc(this); // device context for painting
    CFont *pOldFont;

    pOldFont = dc.GetCurrentFont();
    dc.SelectObject(GetFont());

    const CWnd *pMainTxt = GetDlgItem(IDC_TEXT);
    CRect r, r2;
    CString cStr;

    pMainTxt->GetWindowRect(r);
    ScreenToClient(r);

    CPoint pt = r.TopLeft();

    dc.SetBkMode(TRANSPARENT);
//    dc.FillSolidRect(r, RGB(200, 200, 0));
    dc.DrawText(m_sText, m_sText.GetLength(), r, DT_EXPANDTABS | DT_NOCLIP);

    dc.SelectObject(pOldFont);
}
