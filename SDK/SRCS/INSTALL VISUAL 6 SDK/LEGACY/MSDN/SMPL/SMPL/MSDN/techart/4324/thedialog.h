// thedialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTheDialog dialog

class CTheDialog : public CDialog
{
// Construction
public:
	CTheDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTheDialog)
	enum { IDD = IDD_DIALOG1 };
	CStatic	m_staticChange;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTheDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
   virtual CString& CallMemberPtr() = 0 ;

	// Generated message map functions
	//{{AFX_MSG(CTheDialog)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
