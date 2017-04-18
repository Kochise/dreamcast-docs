// pecframe.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPECFrame frame

class CPECFrame : public CChildFrame  
{
	DECLARE_DYNCREATE(CPECFrame)
protected:
	CPECFrame();           // protected constructor used by dynamic creation

// Attributes
public:

CPEView *GetDLLPane(void);


// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPECFrame)
	protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CPECFrame();

	// Generated message map functions
	//{{AFX_MSG(CPECFrame)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
