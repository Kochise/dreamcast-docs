// updnctl.cpp : implementation file
//

#include "stdafx.h"
#include "dlgpanel.h"  // for palette message definition
#include "updnctl.h"

#define IDC_UP  100
#define IDC_DN  101


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

BOOL CUpDnCtl::m_bRegistered = Register();

BOOL CUpDnCtl::Register()
{
    // Register the window class of the control
    WNDCLASS wc;
    wc.style = CS_GLOBALCLASS
             | CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = UpDnWndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = NULL;
    wc.hIcon = NULL;
    wc.hCursor = ::LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = "UpDnCtl";

    if (!::RegisterClass(&wc)) {
        ASSERT(0);
        return FALSE;
    } 
    return TRUE;
}

LRESULT CALLBACK UpDnWndProc(HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uiMsg) {
    case WM_NCCREATE: {
        // Create a C++ object to handle the messages
        CUpDnCtl* pCtl = new CUpDnCtl;
        ASSERT(pCtl);
        // Attach the window handle to the new object
        BOOL b = pCtl->SubclassWindow(hWnd);
        ASSERT(b);
        return b;
        } break;

    default:
        return ::DefWindowProc(hWnd, uiMsg, wParam, lParam);
    }
}

/////////////////////////////////////////////////////////////////////////////
// CUpDnCtl

IMPLEMENT_DYNCREATE(CUpDnCtl, CWnd)

CUpDnCtl::CUpDnCtl()
{
    m_iWidth = 20;
    m_iHeight = 10;
    m_pPal = NULL;
    m_font.CreateStockObject(ANSI_FIXED_FONT);
    m_strCaption = "UpDnCtl";
    m_strTextSet = "1|2|5|10|20|50|100";
    m_iCurSel = 0;
}

CUpDnCtl::~CUpDnCtl()
{
    // don't destroy m_pPal - it's not ours
}

WNDPROC* CUpDnCtl::GetSuperWndProcAddr()
{
    // Provide a place for MFC's subclassing
    // mechanism to store the super-class pointer
    static WNDPROC NEAR pfnSuper = NULL;
    return &pfnSuper;
}

BEGIN_MESSAGE_MAP(CUpDnCtl, CWnd)
    //{{AFX_MSG_MAP(CUpDnCtl)
    ON_WM_NCDESTROY()
    ON_WM_PAINT()
    ON_WM_SIZE()
    ON_MESSAGE(DLGPANELMSG_SETPALETTE, OnSetPalette)
    ON_MESSAGE(WM_SETTEXT, OnSetText)
    ON_MESSAGE(WM_GETTEXT, OnGetText)
    ON_MESSAGE(WM_GETTEXTLENGTH, OnGetTextLength)
    ON_WM_CREATE()
    ON_CONTROL(BN_CLICKED, IDC_UP, OnUpClicked)
    ON_CONTROL(BN_CLICKED, IDC_DN, OnDnClicked)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUpDnCtl message handlers

void CUpDnCtl::OnNcDestroy()
{
    CWnd::OnNcDestroy();
    // Make sure the window was destroyed
    ASSERT(m_hWnd == NULL);
    // Destroy this object since it won't be destroyed otherwise
    delete this;
}

int CUpDnCtl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CWnd::OnCreate(lpCreateStruct) == -1)
        return -1;
    
    // Create the two buttons
    m_btnUp.Create("Up",
                   WS_CHILD|WS_VISIBLE,
                   CRect(0,0,0,0),
                   this,
                   IDC_UP); 
    m_btnDn.Create("Dn",
                   WS_CHILD|WS_VISIBLE,
                   CRect(0,0,0,0),
                   this,
                   IDC_DN); 
    
    return 0;
}

LRESULT CUpDnCtl::OnSetPalette(WPARAM wParam, LPARAM lParam)
{
    // A message from the parent telling us what palette to use
    m_pPal = (CPalette*) lParam;
    ASSERT(m_pPal);
    ASSERT(m_pPal->IsKindOf(RUNTIME_CLASS(CPalette)));
    // Recreate the screen buffer
    m_dsPanel.Create(m_iWidth, m_iHeight, m_pPal);
    // Redraw
    Render();
    Invalidate();
    return 0;
}

void CUpDnCtl::OnSize(UINT nType, int cx, int cy)
{
    CWnd::OnSize(nType, cx, cy);
    if ((cx < 10) || (cy < 10)) return;

    // Resize the screen buffer to occupy the client area
    m_dsPanel.Create(cx, cy, m_pPal);

    // Save the size
    m_iWidth = cx;
    m_iHeight = cy;

    // Move the buttons
    int w = cx/2;
    int h = cy - cy/2;
    m_btnUp.MoveWindow(0, cy/2, w, h);
    m_btnDn.MoveWindow(w, cy/2, cx-w, h);
    // Redraw the lot
    Render();
    Invalidate();
}

void CUpDnCtl::Render()
{
    // Render the panel image
    CRect rc;
    m_dsPanel.GetRect(&rc);
    rc.bottom = rc.bottom/2;
    CDC* pDC = m_dsPanel.GetDC();

    // Put black rectangle around the outside and fill the middle
    // with gray
    CBrush brSurface;
    brSurface.CreateSolidBrush(PALETTERGB(192,192,192));
    CBrush* pbrOld = pDC->SelectObject(&brSurface);
    pDC->Rectangle(&rc);

    // Draw the highlights
    CPen penShadow(PS_SOLID, 1, PALETTERGB(128,128,128));
    CPen* ppenOld = pDC->SelectObject(&penShadow);
    pDC->MoveTo(rc.left+1, rc.bottom-2);
    pDC->LineTo(rc.left+1, rc.top+1);
    pDC->LineTo(rc.right-1, rc.top+1);
    CPen penHighlight(PS_SOLID, 1, PALETTERGB(255,255,255));
    pDC->SelectObject(&penHighlight);
    pDC->MoveTo(rc.left+2, rc.bottom-2);
    pDC->LineTo(rc.right-2, rc.bottom-2);
    pDC->LineTo(rc.right-2, rc.top+1);

    // Now draw the text in the middle
    rc.InflateRect(-3, -2);
    pDC->SetBkMode(TRANSPARENT);
    CFont* pfntOld = pDC->SelectObject(&m_font);
    pDC->DrawText(m_strCaption, -1, &rc, DT_LEFT|DT_VCENTER);

    // Tidy up
    pDC->SelectObject(pfntOld);
    pDC->SelectObject(pbrOld);
    pDC->SelectObject(ppenOld);
}

void CUpDnCtl::OnPaint()
{
    CPaintDC dc(this); // device context for painting
    // Copy the panel image to the screen DC
    m_dsPanel.Draw(&dc);
}

LRESULT CUpDnCtl::OnSetText(WPARAM, LPARAM lParam)
{
    m_strCaption = (char*)lParam;
    Render();
    RedrawWindow();
    return TRUE;
}

LRESULT CUpDnCtl::OnGetText(WPARAM wParam, LPARAM lParam)
{
    int iMaxLen = (int)wParam;
    if (iMaxLen == 0) return 0;  // nothing copied
    char* pszDest = (char*)lParam;

    int iCopied = min(iMaxLen, m_strCaption.GetLength());
    strncpy(pszDest, (const char*)m_strCaption, iCopied);
    return iCopied;
}

LRESULT CUpDnCtl::OnGetTextLength(WPARAM, LPARAM)
{
    return m_strCaption.GetLength();
}

void CUpDnCtl::OnUpClicked()
{
    if (m_iCurSel == 0) return;
    SetCurSel(m_iCurSel - 1);
}

void CUpDnCtl::OnDnClicked()
{
    SetCurSel(m_iCurSel + 1);
}

void CUpDnCtl::SetCurSel(int iSel)
{
    ASSERT(iSel >= 0);

    const char* pSet = (const char*) m_strTextSet;
    ASSERT(pSet);
    int i = iSel;
    while (i--) {
        // move on to the next section
        while (*pSet != '|') {
            pSet++;
            if (*pSet == '\0') return; // ran out of string
        }
        pSet++;
    }

    // Set the caption to where we are now
    m_strCaption = "";
    while (*pSet && (*pSet != '|')) {
        m_strCaption += *pSet++;
    }
    m_iCurSel = iSel;
    Render();
    RedrawWindow();

    // Notify parent of the change
    GetParent()->SendMessage(WM_COMMAND,
                             MAKEWPARAM(GetDlgCtrlID(), CBN_EDITCHANGE),
                             LPARAM(m_hWnd));
                             
}

void CUpDnCtl::SetButtonText(const char* pszUp, const char* pszDn)
{
    GetDlgItem(IDC_UP)->SetWindowText(pszUp);
    GetDlgItem(IDC_DN)->SetWindowText(pszDn);
}
