// browsedi.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBrowseDialog dialog

class CBrowseDialog : public CDialog
{
// Construction
public:
	CBrowseDialog(CWnd* pParent = NULL);	// standard constructor
    BOOL OnInitDialog();
// Dialog Data
	//{{AFX_DATA(CBrowseDialog)
	enum { IDD = IDD_COMMDIALOG };
	CString	m_TargetName;
    CString m_Title;
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CBrowseDialog)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
