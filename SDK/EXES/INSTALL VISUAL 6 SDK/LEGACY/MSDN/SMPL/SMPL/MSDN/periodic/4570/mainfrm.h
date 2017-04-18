//***************************************************************************
//
//  MainFrame.h
//
//***************************************************************************

class CMainFrame : public CFrameWnd
{
    DECLARE_DYNCREATE (CMainFrame)

private:
    CStatusBar m_wndStatusBar;

protected:
    afx_msg int OnCreate (LPCREATESTRUCT);
    DECLARE_MESSAGE_MAP ()
};
