// EntryDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNewEntryDlg dialog

class CNewEntryDlg : public CDialog
{
// Construction
public:
	CNewEntryDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CNewEntryDlg)
	enum { IDD = IDD_NEWENTRY };
	CComboBox	m_cbMode;
	CString	m_strDate;
	CString	m_strDesc;
	double	m_dFreq;
	CString	m_strStation;
	CString	m_strTime;
	//}}AFX_DATA
	CString m_strMode;
	COleDateTime m_Date;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNewEntryDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNewEntryDlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
