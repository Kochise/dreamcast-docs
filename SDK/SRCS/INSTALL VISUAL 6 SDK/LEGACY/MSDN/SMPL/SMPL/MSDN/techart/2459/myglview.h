// myglview.h : interface of the CMyglView class
//
/////////////////////////////////////////////////////////////////////////////
#include "COpenGL.h"

class CMyglView : public CView
{
public:
    COpenGL *m_glptr;

protected: // create from serialization only
	CMyglView();
	DECLARE_DYNCREATE(CMyglView)

// Attributes
public:
	CMyglDoc* GetDocument();

// Operations
public:

// Implementation
public:
	virtual ~CMyglView();
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	static  CMyglView* GetView(void);
	BOOL    PreCreateWindow(CREATESTRUCT& cs);
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;

#endif


// Generated message map functions
protected:
	//{{AFX_MSG(CMyglView)
	afx_msg int  OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnPixfmtChoose();
	afx_msg void OnPixfmtDescribe();
	afx_msg void OnPixfmtEnum();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG	// debug version in myglview.cpp
inline CMyglDoc* CMyglView::GetDocument()
   { return (CMyglDoc*) m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
