// lightdlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLightDlg dialog

class CLightDlg : public CDialog
{
// Construction
public:
	CLightDlg(CWnd* pParent = NULL);   // standard constructor
    void Create();

// Dialog Data
	//{{AFX_DATA(CLightDlg)
	enum { IDD = IDD_LIGHT };
	CSliderCtrl	m_wndBright;
	//}}AFX_DATA

    ILight* m_pILight;
    CWnd* m_pParent;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLightDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLightDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
