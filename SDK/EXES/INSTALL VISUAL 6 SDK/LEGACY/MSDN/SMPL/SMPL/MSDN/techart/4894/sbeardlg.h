// SurfBearDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSurfBearDlg dialog

class CSurfBearDlg : public CDialog
{
// Construction
public:
	CSurfBearDlg(CWnd* pParent = NULL);	// standard constructor

   CString m_strServer ;
   CString m_strPath ;

   CBitmapButton m_btnBitmapHelp ;
// Dialog Data
	//{{AFX_DATA(CSurfBearDlg)
	enum { IDD = IDD_SURFBEAR_DIALOG };
	CButton	m_btnAccess;
	CButton	m_btnGoto;
	CButton	m_btnClose;
	CEdit	m_editBrowse;
	CEdit	m_editAddress;
	CAnimateCtrl	m_ctrlAnimate;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSurfBearDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
   CInternetThread m_InternetThread ;

   // helper
   void EnableUI(BOOL bEnable) ;
   void SetEditBrowseSize(int cx, int cy) ;
   // other
   HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSurfBearDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnGotoBtn();
	afx_msg void OnSize(UINT nType, int cx, int cy);
   afx_msg LRESULT OnReadFileCompleted(WPARAM wParam, LPARAM lParam) ;
	afx_msg void OnBtnAccess();
  	afx_msg void OnHelpAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
