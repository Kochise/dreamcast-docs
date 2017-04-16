// configdl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CConfigDlg dialog

class CConfigDlg : public CDialog
{
// Construction
public:
	CConfigDlg(CWnd* pParent = NULL);   // standard constructor

	BOOL m_bDefault[6] ;
	CString m_strPath[6] ;
	static LPCSTR s_key[6];

	CString m_strDefault ;
	CString m_strSection;
	CString m_strIniName ;

	void HandleRadioBtn(int i) ;

// Dialog Data
	//{{AFX_DATA(CConfigDlg)
	enum { IDD = IDD_CONFIGDLG };
	CButton	m_checkDefault;
	CButton	m_btnFace1;
	CEdit	m_editPath;
	CButton	m_btnBrowse;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConfigDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CConfigDlg)
	afx_msg void OnBrowse();
	virtual BOOL OnInitDialog();
	afx_msg void OnFace1();
	afx_msg void OnFace2();
	afx_msg void OnFace3();
	afx_msg void OnFace4();
	afx_msg void OnFace5();
	afx_msg void OnFace6();
	afx_msg void OnKillfocusEdit1();
	virtual void OnOK();
	afx_msg void OnCheckdefault();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
