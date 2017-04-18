// cstm3dlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCustom3Dlg dialog

class CCustom3Dlg : public CAppWizStepDlg
{
// Construction
public:
    int m_iNameType;
	int m_iLinkNameType;
protected:
    int m_iMyIndex;
public:
	CCustom3Dlg(int i);
	virtual BOOL OnDismiss();
// Dialog Data
	//{{AFX_DATA(CCustom3Dlg)
	enum { IDD = IDD_CUSTOM3 };
	BOOL	m_bBuffered;
	BOOL	m_bExclusive;
	CString	m_DevName;
	CString	m_LinkName;
	BOOL	m_bHasISR;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCustom3Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CCustom3Dlg)
	afx_msg void OnSetfocusDevname();
	afx_msg void OnDeviceunnamed();
	virtual BOOL OnInitDialog();
	afx_msg void OnSetfocusLinkname();
	afx_msg void OnLinkdyna();
	afx_msg void OnLinknamehere();
	afx_msg void OnLinkunnamed();
	afx_msg void OnDevicenamehere();
	afx_msg void OnDevicedyna();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
    virtual BOOL AssignValues(BOOL);

};
