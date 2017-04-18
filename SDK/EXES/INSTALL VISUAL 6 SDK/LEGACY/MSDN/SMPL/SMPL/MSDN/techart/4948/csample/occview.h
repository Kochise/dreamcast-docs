// OCCSampView.h : interface of the COCCSampView class
//
/////////////////////////////////////////////////////////////////////////////

class COCCSampView : public CView
{
protected: // create from serialization only
	COCCSampView();
	DECLARE_DYNCREATE(COCCSampView)

// Attributes
public:
	BOOL m_fDocListCreated;
	CListBox m_docList;
	COCCSampDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COCCSampView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~COCCSampView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(COCCSampView)
	afx_msg void OnProperties();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in OCCSampView.cpp
inline COCCSampDoc* COCCSampView::GetDocument()
   { return (COCCSampDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
