//////////////////
// Derived toolbar class to handle double-clicks.
//
class CMyToolBar : public CToolBar {
	static LPCSTR s_winClassName;
	DECLARE_DYNAMIC(CMyToolBar)
protected:
#if _MFC_VER < 0x0400
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
#endif
	//{{AFX_MSG(CMyToolBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//////////////////
// Standard main frame. 
// Overrides PreCreateWindow to change window class name.
//
class CMainFrame : public CMDIFrameWnd {
	static LPCSTR s_winClassName;
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();
	virtual ~CMainFrame();
protected:

#if _MSC_VER < 0x0400
	// Not required for MFC 4.0 and later.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
#endif

	CStatusBar  m_wndStatusBar;
	CMyToolBar  m_wndToolBar;

	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//////////////////
// Derived child frame overrides PreCreateWindow
// to change the window class name.
//
class CMyChildFrame : public CMDIChildWnd {
	static LPCSTR s_winClassName;
	DECLARE_DYNCREATE(CMyChildFrame)
public:
	CMyChildFrame();
	virtual ~CMyChildFrame();
protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//{{AFX_MSG(CMyChildFrame)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
