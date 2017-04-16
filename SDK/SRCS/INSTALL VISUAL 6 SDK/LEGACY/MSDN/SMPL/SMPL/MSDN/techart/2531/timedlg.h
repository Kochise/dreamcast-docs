// timedlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTimeDlg dialog

class CTimeDlg : public CDialog
{
// Construction
public:
	CTimeDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTimeDlg)
	enum { IDD = IDD_TIMEDLG };
	UINT	m_time;
	double	m_SecsPerTick;
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CTimeDlg)
	afx_msg void OnClickedDefault();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
