// DocProps.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDocProps dialog

class CDocProps : public CDialog
{
// Construction
public:
	IMsocAutoCorrect* m_pAutoCorrect;
	IMsocBuiltinDocProps* m_pBuiltInDocProps;
	IMsocDocProps* m_pDocProps;
	CDocProps(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDocProps)
	enum { IDD = IDD_PROPERTIES };
	CString	m_EditComments;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDocProps)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDocProps)
	afx_msg void OnAllprops();
	afx_msg void OnChangeEditcomments();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
