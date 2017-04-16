// rawframe.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRawFrame frame

class CRawFrame : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CRawFrame)
protected:
	CRawFrame();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRawFrame)
	protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CRawFrame();

	// Generated message map functions
	//{{AFX_MSG(CRawFrame)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
