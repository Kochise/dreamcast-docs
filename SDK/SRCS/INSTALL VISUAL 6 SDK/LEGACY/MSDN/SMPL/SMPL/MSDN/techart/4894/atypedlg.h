// AccessTypeDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAccessTypeDlg dialog

class CAccessTypeDlg : public CDialog
{
// Construction
public:
	CAccessTypeDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAccessTypeDlg)
	enum { IDD = IDD_DLG_ACCESSTYPES };
	int		m_iRadioBtns;
	CString	m_strProxyServer;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAccessTypeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAccessTypeDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
