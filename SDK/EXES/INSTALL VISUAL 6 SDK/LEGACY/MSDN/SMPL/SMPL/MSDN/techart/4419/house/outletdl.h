// outletdl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COutletDlg dialog

class COutletDlg : public CDialog
{
// Construction
public:
	COutletDlg(CWnd* pParent = NULL);   // standard constructor
    void Create();

// Dialog Data
	//{{AFX_DATA(COutletDlg)
	enum { IDD = IDD_DIALOG1 };
	CButton	m_wndOn;
	CButton	m_wndOff;
	//}}AFX_DATA

    IOutlet* m_pIOutlet;
    CWnd* m_pParent;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COutletDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(COutletDlg)
	afx_msg void OnOffbtnClicked();
	afx_msg void OnOnBtnClicked();
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
