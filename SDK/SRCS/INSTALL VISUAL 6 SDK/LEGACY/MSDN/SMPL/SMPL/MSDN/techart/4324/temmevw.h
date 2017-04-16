// TemMevw.h : interface of the CTemMemPtrView class
//
/////////////////////////////////////////////////////////////////////////////

class CTemMemPtrView : public CView
{
protected: // create from serialization only
	CTemMemPtrView();
	DECLARE_DYNCREATE(CTemMemPtrView)

// Attributes
public:
	CTemMemPtrDoc* GetDocument();

// Operations
public:
   CString& CalledByDialog() ;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTemMemPtrView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTemMemPtrView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CTemMemPtrView)
	afx_msg void OnCallitFromview();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in TemMevw.cpp
inline CTemMemPtrDoc* CTemMemPtrView::GetDocument()
   { return (CTemMemPtrDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
