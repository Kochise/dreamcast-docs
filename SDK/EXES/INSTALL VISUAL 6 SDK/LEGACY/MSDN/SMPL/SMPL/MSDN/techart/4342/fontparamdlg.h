// fontparamdlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFontParamDlg dialog

class CFontParamDlg : public CDialog
{
// Construction
public:
	CFontParamDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CFontParamDlg)
	enum { IDD = IDD_FONTPARAMDLG };
	float	m_fDeviation;
	float	m_fExtrusion;
	CString	m_theString;
	int		m_iFormatRadio;
	//}}AFX_DATA

// Other data
	LOGFONT m_logFont ;

// Default Values
	int m_iFormatDefault ;
	float m_fDeviationDefault ;
	float m_fExtrusionDefault ;
	CString m_theStringDefault ;
	LOGFONT* m_pLogFontDefault ;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFontParamDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFontParamDlg)
	afx_msg void OnBtnFont();
	afx_msg void OnBtnDefault();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
