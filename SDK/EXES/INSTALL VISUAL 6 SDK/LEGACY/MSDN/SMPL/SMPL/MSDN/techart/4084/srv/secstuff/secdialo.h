// secdialo.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSecDialog dialog

class CSecDialog : public CDialog
{
// Construction
public:
	CSecDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSecDialog)
	enum { IDD = IDD_GetSecDialog };
	CString	m_UserName;
	CString	m_DomainName;
	int m_iButtonPushed;
	LPSTR m_Title;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSecDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSecDialog)
	afx_msg void OnRadio1();
	afx_msg void OnRadio2();
	afx_msg void OnRadio3();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
