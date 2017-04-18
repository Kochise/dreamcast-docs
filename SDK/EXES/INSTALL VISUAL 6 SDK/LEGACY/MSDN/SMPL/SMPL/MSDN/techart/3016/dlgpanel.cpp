// dlgpanel.cpp : implementation file
//

#include "stdafx.h"
#include "fwtest.h"
#include "dlgtempl.h"
#include "dlgpanel.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgPanel

CDlgPanel::CDlgPanel()
{
    m_pPal = NULL;
}

CDlgPanel::~CDlgPanel()
{
    // don't destroy m_pPal - it's not ours
}


BEGIN_MESSAGE_MAP(CDlgPanel, CDialogBar)
    //{{AFX_MSG_MAP(CDlgPanel)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CDlgPanel::Create(CWnd* pParentWnd, UINT nIDTemplate,
                       UINT nStyle, UINT nID, CPalette* pPal)
{
    m_pPal = pPal;
    m_uiIDTemplate = nIDTemplate;
    BOOL b = CDialogBar::Create(pParentWnd, nIDTemplate,
                                nStyle, nID);
    if (!b) return FALSE;
    // send all child windows and thier children a message
    // containing the palette
    SendMessageToDescendants(DLGPANELMSG_SETPALETTE,
                             0, (LPARAM) m_pPal, TRUE);
    return TRUE;
}
                
/////////////////////////////////////////////////////////////////////////////
// CDlgPanel message handlers

// Stolen from MFC\SRC\BARCORE.CPP
LRESULT CDlgPanel::WindowProc(UINT nMsg, WPARAM wParam, LPARAM lParam)
{
    // parent notification messages are just passed to parent of control bar
    switch (nMsg)
    {
    case WM_COMMAND:
    case WM_DRAWITEM:
    case WM_MEASUREITEM:
    case WM_DELETEITEM:
    case WM_COMPAREITEM:
    case WM_VKEYTOITEM:
    case WM_CHARTOITEM:
    case WM_HSCROLL:      // new
    case WM_VSCROLL:      // new
        return ::SendMessage(::GetParent(m_hWnd), nMsg, wParam, lParam);
    }
    return CDialogBar::WindowProc(nMsg, wParam, lParam);
}

void CDlgPanel::GetPanelRect(RECT* pRect)
{
    // Return the size of the template in pixels
    // Load the dialog template
    CDlgTemplate tpl(m_uiIDTemplate);
    ASSERT(pRect);
    tpl.GetDlgRect(pRect);
}
