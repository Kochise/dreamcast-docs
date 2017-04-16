// ctlrevw.h : interface of the CCtlregView class
//
/////////////////////////////////////////////////////////////////////////////

class CCtlregView : public CView
{
protected: // create from serialization only
	CCtlregView();
	DECLARE_DYNCREATE(CCtlregView)

// Attributes
public:
	CCtlregDoc* GetDocument();

// Operations
public:

// Implementation
public:
	virtual ~CCtlregView();
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CCtlregView)
	afx_msg void OnControlsRegister();
	afx_msg void OnControlsUnregister();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ctlrevw.cpp
inline CCtlregDoc* CCtlregView::GetDocument()
   { return (CCtlregDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
