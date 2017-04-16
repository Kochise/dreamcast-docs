// emfinfov.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEMFInfoView view

class CEMFInfoView : public CView
{
protected:
	CEMFInfoView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CEMFInfoView)
	LPBYTE m_pbEmfHeader;
// Attributes
public:
	CMetavw1Doc* GetDocument();
	CEdit m_editCtrl;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEMFInfoView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CEMFInfoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CEMFInfoView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in metavvw.cpp
inline CMetavw1Doc* CEMFInfoView::GetDocument()
   { return (CMetavw1Doc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
