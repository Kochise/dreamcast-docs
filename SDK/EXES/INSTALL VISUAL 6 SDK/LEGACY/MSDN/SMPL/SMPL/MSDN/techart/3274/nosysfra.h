// nosysfra.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNoSysFrame frame

class CNoSysFrame : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CNoSysFrame)
protected:
	CNoSysFrame();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNoSysFrame)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CNoSysFrame();

	// Generated message map functions
	//{{AFX_MSG(CNoSysFrame)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
