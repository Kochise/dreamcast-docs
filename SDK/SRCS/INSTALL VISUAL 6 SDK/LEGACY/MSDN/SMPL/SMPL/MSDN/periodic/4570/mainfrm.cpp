//***************************************************************************
//
//  MainFrame.cpp
//
//***************************************************************************

#include <afxwin.h>
#include <afxext.h>

#include "Resource.h"
#include "MainFrm.h"

IMPLEMENT_DYNCREATE (CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP (CMainFrame, CFrameWnd)
    ON_WM_CREATE ()
END_MESSAGE_MAP ()

int CMainFrame::OnCreate (LPCREATESTRUCT lpcs)
{
    if (CFrameWnd::OnCreate (lpcs) == -1)
        return -1;

    m_wndStatusBar.Create (this);
    UINT nIndicator = ID_SEPARATOR;
    m_wndStatusBar.SetIndicators (&nIndicator, 1);
    return 0;
}
