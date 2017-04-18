// fwtesvw.h : interface of the CFwtestView class
//
/////////////////////////////////////////////////////////////////////////////

class CFwtestView : public CView
{
protected: // create from serialization only
	CFwtestView();
	DECLARE_DYNCREATE(CFwtestView)

// Attributes
public:
	CFwtestDoc* GetDocument();

// Operations
public:

// Implementation
public:
	virtual ~CFwtestView();
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Printing support
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Generated message map functions
protected:
	//{{AFX_MSG(CFwtestView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG	// debug version in fwtesvw.cpp
inline CFwtestDoc* CFwtestView::GetDocument()
   { return (CFwtestDoc*) m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
