////////////////
// Standard MFC main frame window
//
class CMainFrame : public CMDIFrameWnd {
public:
   CMainFrame();
   virtual ~CMainFrame();
protected:
   CStatusBar  m_wndStatusBar;
   CToolBar    m_wndToolBar;
   //{{AFX_MSG(CMainFrame)
   afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
   //}}AFX_MSG
   DECLARE_DYNAMIC(CMainFrame)
   DECLARE_MESSAGE_MAP()
};
