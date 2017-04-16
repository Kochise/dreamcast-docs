// unidlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CUniDlg dialog

class CUniDlg : public CDialog
{
// Construction
public:
	CUniDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CUniDlg)
	enum { IDD = IDD_UNIDLG };
	double	m_G;
	double	m_height;
	double	m_width;
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CUniDlg)
	afx_msg void OnClickedDefault();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
