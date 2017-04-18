// DDESvvw.h : interface of the CDDEServView class
//
/////////////////////////////////////////////////////////////////////////////

class CDDEServView : public CEditView
{
protected: // create from serialization only
	CDDEServView();
	DECLARE_DYNCREATE(CDDEServView)

// Attributes
public:
	CDDEServDoc* GetDocument();

// Operations
public:
    void PrintLine(const char* pszFormat, ...);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDDEServView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDDEServView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
    int m_iCurrentLine;
    CFont m_font;


// Generated message map functions
protected:
	//{{AFX_MSG(CDDEServView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in DDESvvw.cpp
inline CDDEServDoc* CDDEServView::GetDocument()
   { return (CDDEServDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
