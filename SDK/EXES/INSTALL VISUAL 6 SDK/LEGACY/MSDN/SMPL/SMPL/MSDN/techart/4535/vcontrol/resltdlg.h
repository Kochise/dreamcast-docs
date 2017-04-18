// ResltDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CResultsDialog dialog

class CResultsDialog : public CDialog
{
// Construction
public:
	CResultsDialog( CWnd* pParent = NULL);   // standard constructor

	CObArray* m_pInterfaceResultsArray;

// Dialog Data
	//{{AFX_DATA(CResultsDialog)
	enum { IDD = IDD_RESULTSDIALOG };
	CListBox	m_listboxResuls;
	BOOL	m_checkFailures;
	BOOL	m_checkMandatory;
	BOOL	m_checkOptional;
	BOOL	m_checkSuccess;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CResultsDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	void FillResultsListBox(void);
	BOOL ShouldDisplay(CVerificationResult* pResult);

	int m_nMandatoryFailures;
	int m_nMandatorySuccesses;
	int m_nOptionalTests;

	// Generated message map functions
	//{{AFX_MSG(CResultsDialog)
	afx_msg void OnChkFail();
	afx_msg void OnChkMandatory();
	afx_msg void OnChkOptional();
	afx_msg void OnChkSuccess();
	virtual BOOL OnInitDialog();
	afx_msg void OnResultsfile();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
