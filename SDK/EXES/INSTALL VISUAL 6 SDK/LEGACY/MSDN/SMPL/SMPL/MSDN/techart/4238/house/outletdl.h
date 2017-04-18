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
	enum { IDD = IDD_OUTLET };
	CButton	m_btnSwitch;
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
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	afx_msg void OnSwitch();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

    // INotify support
    // Declare the interface map for this object
    DECLARE_INTERFACE_MAP()

    // INotify interface
    BEGIN_INTERFACE_PART(Notify, INotify)
        STDMETHOD(Change)(LPVOID pUserInfo);
    END_INTERFACE_PART(Notify)

    INotify* m_pINotify;

    // helpers
    void ShowState();
};
