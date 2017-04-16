// radiodlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRadioDlg dialog

class CRadioDlg : public CDialog
{
// Construction
public:
	CRadioDlg(CWnd* pParent = NULL);   // standard constructor
    void Create(CWnd* pParent);

// Dialog Data
	//{{AFX_DATA(CRadioDlg)
	enum { IDD = IDD_RADIODLG };
	CStatic	m_wndPwrInd;
	CButton	m_wndStation4;
	CButton	m_wndStation3;
	CButton	m_wndStation2;
	CButton	m_wndStation1;
	CButton	m_wndPower;
	CSliderCtrl	m_wndFrequency;
	//}}AFX_DATA

    CRadio* m_pRadio;
    IUnknown* m_punkRadio;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRadioDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

    void ShowProgram();

	// Generated message map functions
	//{{AFX_MSG(CRadioDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPowerBtn();
	afx_msg void OnStation1();
	afx_msg void OnStation2();
	afx_msg void OnStation3();
	afx_msg void OnStation4();
	afx_msg void OnClose();
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
};
