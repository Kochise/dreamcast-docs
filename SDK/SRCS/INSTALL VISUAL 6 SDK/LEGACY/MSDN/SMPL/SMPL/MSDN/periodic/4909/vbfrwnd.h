// VBFrWnd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CVBFrameWnd window
class CMSJDragCtrl;

class CVBFrameWnd : public CWnd
{
// Construction
public:
	CVBFrameWnd();

// Attributes
public:
	CMSJDragCtrl * m_ctrlwnd;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVBFrameWnd)
	//}}AFX_VIRTUAL

protected:
	static WNDPROC pfnSuperWndProc ;
    virtual WNDPROC* GetSuperWndProcAddr() 
                      {return &pfnSuperWndProc;}

// Implementation
public:
	virtual ~CVBFrameWnd();

	// Generated message map functions
protected:
	//{{AFX_MSG(CVBFrameWnd)
	afx_msg void OnDropFiles(HDROP hDropInfo);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
