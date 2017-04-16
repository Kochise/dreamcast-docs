// LogVwDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLogViewDlg dialog

class CLogViewDlg : public CDialog
{
// Construction
public:
	CLogViewDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CLogViewDlg)
	enum { IDD = IDD_LOGVIEW_DIALOG };
	CButton	m_btnDelete;
	CListBox	m_lbBand;
	CListBox	m_lbLogs;
	double	m_dFreq;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLogViewDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CLogViewDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnLookup();
	virtual void OnCancel();
	afx_msg void OnClose();
	afx_msg void OnDestroy();
	afx_msg void OnSelchangeLogs();
	afx_msg void OnNewEntry();
	afx_msg void OnDelete();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()


	CDaoDatabase m_db;
	CDaoRecordset m_rsLogs;

	void UpdateBandInfo();
};
