// NoThreadDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNoThreadDialog dialog

class CNoThreadDialog : public CDialog
{
// Construction
public:
	CNoThreadDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CNoThreadDialog)
	enum { IDD = IDD_NOTHREADDIALOG };
	int		m_NoThreads;
	int		m_Delay;
	//}}AFX_DATA

    int m_iCompType;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNoThreadDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNoThreadDialog)
	afx_msg void OnIobound();
	afx_msg void OnCpubound();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
