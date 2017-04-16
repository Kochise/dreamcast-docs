// necframe.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNECFrame frame

class CNECFrame : public CChildFrame
{
	DECLARE_DYNCREATE(CNECFrame)
protected:
	CNECFrame();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:

CNEView *GetDLLPane(void);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNECFrame)
	protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CNECFrame();

	// Generated message map functions
	//{{AFX_MSG(CNECFrame)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
