/////////////////////////////////////////////////////////////////////////////
// WebView.h : interface of the CWebView class
//
// This is a part of the Webster HTTP Server application
// for Microsoft Systems Journal
//

class CWebView : public CScrollView
{
protected: // create from serialization only
	CWebView();
	DECLARE_DYNCREATE(CWebView)

// Attributes
public:
	CWebDoc* GetDocument();

// Operations
public:


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWebView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CWebView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CWebView)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in WebView.cpp
inline CWebDoc* CWebView::GetDocument()
   { return (CWebDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
