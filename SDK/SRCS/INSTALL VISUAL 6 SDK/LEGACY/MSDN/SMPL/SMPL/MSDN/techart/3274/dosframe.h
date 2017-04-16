// dosframe.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDOSFrame frame

class CDOSFrame : public CChildFrame
{
	DECLARE_DYNCREATE(CDOSFrame)
protected:
	CDOSFrame();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDOSFrame)
	protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CDOSFrame();

	// Generated message map functions
	//{{AFX_MSG(CDOSFrame)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
