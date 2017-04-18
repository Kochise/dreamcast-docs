// NTSerdlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNTServCtrlDlg dialog

class CNTServCtrlDlg : public CDialog
{
// Construction
public:
	CNTServCtrlDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CNTServCtrlDlg)
	enum { IDD = IDD_NTSERVCTRL_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNTServCtrlDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
    UINT m_uiTimer;

    void ShowState();

	// Generated message map functions
	//{{AFX_MSG(CNTServCtrlDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnQuery();
	afx_msg void OnStart();
	afx_msg void OnStop();
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
