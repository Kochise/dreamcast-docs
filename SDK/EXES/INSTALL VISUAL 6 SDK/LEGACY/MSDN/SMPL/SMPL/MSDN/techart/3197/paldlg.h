// paldlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPaletteDlg dialog

class CPaletteDlg : public CDialog
{
// Construction
public:
	CPaletteDlg(CWnd* pParent = NULL);   // standard constructor
	void EnableControls(BOOL bEnable) ;

// Dialog Data
	//{{AFX_DATA(CPaletteDlg)
	enum { IDD = IDD_PALETTE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	BOOL m_bSysColor ;
	int m_iGamma ;
	BOOL m_b332 ;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPaletteDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
  void OnOK();

	// Generated message map functions
	//{{AFX_MSG(CPaletteDlg)
	afx_msg void On332();
	afx_msg void OnWash();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
