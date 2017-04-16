// lecframe.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLECFrame frame

class CLECFrame : public CChildFrame
{
	DECLARE_DYNCREATE(CLECFrame)
protected:
	CLECFrame();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLECFrame)
	protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CLECFrame();

	// Generated message map functions
	//{{AFX_MSG(CLECFrame)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
