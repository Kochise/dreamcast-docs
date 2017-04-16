// dlgpanfm.cpp : implementation file
//

#include "stdafx.h"
#include "dlgpanel.h"
#include "dlgpanfm.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgPanelFrame

IMPLEMENT_DYNCREATE(CDlgPanelFrame, CMDIChildWnd)

CDlgPanelFrame::CDlgPanelFrame()
{
    m_pPal = NULL;
}

CDlgPanelFrame::~CDlgPanelFrame()
{
    // Don't delete m_pPal - it's not ours
}


BEGIN_MESSAGE_MAP(CDlgPanelFrame, CMDIChildWnd)
    //{{AFX_MSG_MAP(CDlgPanelFrame)
    ON_WM_CREATE()
    ON_WM_SIZE()
    ON_COMMAND(IDOK, OnOK)
    ON_COMMAND(IDCANCEL, OnCancel)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CDlgPanelFrame::Create(LPCSTR lpszWindowName,
                            const RECT& rc,
                            CMDIFrameWnd* pParentWnd,
                            UINT uiTemplateID,
                            UINT uiResourceID,
                            CPalette* pPal/*= NULL*/)
{
    m_pPal = pPal;
    m_uiTemplateID = uiTemplateID;

    // Create the window with a caption and just a thin border
    return CMDIChildWnd::Create(GetIconWndClass(WS_CHILD|WS_VISIBLE|WS_OVERLAPPEDWINDOW,
                                                uiResourceID),
                                lpszWindowName,
                                WS_CHILD|WS_VISIBLE|WS_OVERLAPPED
                                    |WS_CAPTION|WS_BORDER,
                                rc,
                                pParentWnd);
}

int CDlgPanelFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CMDIChildWnd::OnCreate(lpCreateStruct) == -1)
        return -1;
    
    // Create the dialog panel
    // Note that we send them the palette we are using.
 
    ASSERT(m_uiTemplateID);
    if (!m_wndPanel.Create(this,
                           m_uiTemplateID,
                           CBRS_TOP,
                           1, // Child ID
                           m_pPal)) {
        TRACE("Failed to create panel from template");
        return -1;
    }

    return 0;
}                            

void CDlgPanelFrame::OnSize(UINT nType, int cx, int cy)
{
    CMDIChildWnd::OnSize(nType, cx, cy);
    
    // Get the size of the panel and resize the parent frame to fit
    CRect rcPanel;
    m_wndPanel.GetPanelRect(&rcPanel);
    if ((cx == rcPanel.right) && (cy == rcPanel.bottom)) {
        return;
    }
    CRect rcWnd;
    GetWindowRect(&rcWnd);
    rcWnd.right -= cx - rcPanel.right;
    rcWnd.bottom -= cy - rcPanel.bottom;
    SetWindowPos(NULL,
                 0, 0,
                 rcWnd.right - rcWnd.left,
                 rcWnd.bottom - rcWnd.top,
                 SWP_NOZORDER|SWP_NOACTIVATE|SWP_NOMOVE); 
}

void CDlgPanelFrame::OnOK()
{
    TRACE("No OnOK handler in your derived class");
}

void CDlgPanelFrame::OnCancel()
{
    TRACE("No OnCancel handler in your derived class");
}

