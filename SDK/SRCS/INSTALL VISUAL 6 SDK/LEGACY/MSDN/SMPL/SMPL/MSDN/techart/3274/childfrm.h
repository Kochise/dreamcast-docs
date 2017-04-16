// childfrm.h : interface of the CChildFrame class
//
/////////////////////////////////////////////////////////////////////////////

class CViewfileDoc;     // forward declaration

class CChildFrame : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CChildFrame)

protected:
    int m_iNumberRows, m_iNumberCols;
	CRuntimeClass *m_ViewClass;
	CViewfileDoc *m_AssociatedDocument;

public:
	CChildFrame();

// Attributes
protected:
	CSplitterWnd m_wndSplitter;
public:
   char szStatusMessage[300];

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChildFrame)
	public:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CChildFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
protected:
	//{{AFX_MSG(CChildFrame)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
