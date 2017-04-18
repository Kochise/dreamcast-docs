// SIClientView.h : interface of the CClientView class
//
/////////////////////////////////////////////////////////////////////////////
#include "SimpleObject\ISimple.h"
#include "SmartInterface.h"

class CClientView : public CView
{
protected: // create from serialization only
	CClientView();
	DECLARE_DYNCREATE(CClientView)

// Attributes
public:
	CClientDoc* GetDocument();

   // SIClient originally used interface pointers
   //ISimple* m_pISimple ;
   // SIClient was converted to use smart interfaces
   CSmartInterface<ISimple> m_SISimple ;

  // Using pointers is confusing--> CSmartInterface<ISimple>* m_pISimple ;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClientView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CClientView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CClientView)
	afx_msg void OnObjectCreate();
	afx_msg void OnUpdateObjectCreate(CCmdUI* pCmdUI);
	afx_msg void OnObjectIncrement();
	afx_msg void OnUpdateObjectIncrement(CCmdUI* pCmdUI);
	afx_msg void OnObjectRelease();
	afx_msg void OnUpdateObjectRelease(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ClientView.cpp
inline CClientDoc* CClientView::GetDocument()
   { return (CClientDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
