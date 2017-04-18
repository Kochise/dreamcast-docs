// PAppDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPAppDlg dialog

class CPAppDlg : public CDialog
{
// Construction
public:
	CPAppDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CPAppDlg)
	enum { IDD = IDD_PARSEAPP_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPAppDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CPAppDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	afx_msg void OnGetfile();
	afx_msg void OnRequest();
	afx_msg void OnResponse();
	afx_msg void OnAcctstmt();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
