// dialerdl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDialerDlg dialog

class CDialerDlg : public CDialog
{
// Construction
public:
	CDialerDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDialerDlg)
	enum { IDD = IDD_DIAL };
	CString	m_Phone;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
    CTapiConnection m_tapiObj;
    BOOL m_bCallInProgress;
    char m_szDefaultNumber[32];


protected:

	// Generated message map functions
	//{{AFX_MSG(CDialerDlg)
	afx_msg void OnDial();
	afx_msg void OnHangup();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
