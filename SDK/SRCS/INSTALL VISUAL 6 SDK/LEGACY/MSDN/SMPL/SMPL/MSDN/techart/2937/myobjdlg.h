// myobjdlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyObjDlg dialog

class CMyObjDlg : public CDialog
{
// Construction
public:
	CMyObjDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMyObjDlg)
	enum { IDD = IDD_MYOBJEDITDLG };
	CString	m_strText;
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CMyObjDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
