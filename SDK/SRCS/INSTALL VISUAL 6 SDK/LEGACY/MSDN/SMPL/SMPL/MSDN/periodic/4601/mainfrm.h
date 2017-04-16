class CMainFrame : public CMDIFrameWnd {
   DECLARE_DYNAMIC(CMainFrame)
public:
   CMainFrame();
   virtual ~CMainFrame();
protected:  // control bar embedded members
   CStatusBar  m_wndStatusBar;
   CToolBar    m_wndToolBar;
   afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
   DECLARE_MESSAGE_MAP()
};
