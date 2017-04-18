// tpprops.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTPProps dialog

class CTPProps : public CDialog
{
// Construction
public:
	CTPProps(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTPProps)
	enum { IDD = IDD_PTPROPS };
	short	m_iType;
	CString	m_Name;
	BOOL    m_Marked;
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CTPProps)
	afx_msg void OnClickedCheck2();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
