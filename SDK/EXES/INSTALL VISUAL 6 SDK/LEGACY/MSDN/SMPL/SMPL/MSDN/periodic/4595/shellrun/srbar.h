/******************************************************************************
Module name: SRBar.h
Written by:  Jeffrey Richter
Purpose:     ShellRun class description file.
******************************************************************************/


class CSRBar : public CAppBar {

protected:  // Internal implementation state variables
   // CSRBar's class-specific constants
   static const TCHAR m_szAppName[];
   static const TCHAR m_szRegSubkey[];

   CSize m_szExeBtnDims;   // The preferred size of the Execute button
   CSize m_szMinTracking;  // The minimum size of the client area

public:  // Public member functions
	CSRBar(CWnd* pParent = NULL);

protected:  // Internal implementation functions
   void HideFloatAdornments (BOOL fHide);

protected:  // Overridable functions
   void OnAppBarStateChange (BOOL fProposed, UINT uStateProposed);

// Dialog Data
	//{{AFX_DATA(CSRBar)
	enum { IDD = IDD_SHELLRUN };
	CButton	m_btnExecute;
	CEdit	m_edtCommand;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSRBar)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
   void CSRBar::OnCancel();
	// Generated message map functions
	//{{AFX_MSG(CSRBar)
	virtual BOOL OnInitDialog();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnAppbarAboutAppBar();
	afx_msg void OnAppbarAlwaysOnTop();
	afx_msg void OnAppbarAutohide();
	afx_msg void OnAppbarExit();
	afx_msg void OnExecute();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


//////////////////////////////// End of File //////////////////////////////////
