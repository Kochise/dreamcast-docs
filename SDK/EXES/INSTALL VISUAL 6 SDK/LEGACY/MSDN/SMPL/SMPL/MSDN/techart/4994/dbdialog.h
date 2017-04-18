// deletedi.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDeleteDialog dialog

class CDeleteDialog : public CDialog
{
// Construction
public:
	CDeleteDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDeleteDialog)
	enum { IDD = IDD_DELETEDBRECORD };
	int		m_DeleteIndex;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDeleteDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDeleteDialog)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

// addrecor.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAddrecordDialog dialog

class CAddrecordDialog : public CDialog
{
// Construction
public:
	CAddrecordDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAddrecordDialog)
	enum { IDD = IDD_ADDDBRECORD };
	int		m_Val1;
	int		m_Val2;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAddrecordDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAddrecordDialog)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
