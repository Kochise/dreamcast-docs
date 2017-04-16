// tvdlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTelevisionDlg dialog

class CTelevisionDlg : public CDialog
{
// Construction
public:
	CTelevisionDlg(CWnd* pParent = NULL);   // standard constructor
    void Create(CWnd* pParent);

// Dialog Data
	//{{AFX_DATA(CTelevisionDlg)
	enum { IDD = IDD_TELEVISIONDLG };
	CStatic	m_wndPwrInd;
	//}}AFX_DATA
    
    CTelevision* m_pTV;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTelevisionDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTelevisionDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	afx_msg void OnPowerBtn();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
