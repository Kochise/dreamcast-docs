// viewfvw.h : interface of the CViewfileView class
//
/////////////////////////////////////////////////////////////////////////////

class CViewfileView : public CView
{
protected: // create from serialization only
	CViewfileView();
	DECLARE_DYNCREATE(CViewfileView)

// Attributes
public:
	CViewfileDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CViewfileView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CViewfileView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CViewfileView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in viewfvw.cpp
inline CViewfileDoc* CViewfileView::GetDocument()
   { return (CViewfileDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
