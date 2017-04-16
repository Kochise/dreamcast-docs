// metavvw.h : interface of the CMetavw1View class
//
/////////////////////////////////////////////////////////////////////////////

class CMetavw1View : public CView
{
protected: // create from serialization only
	CMetavw1View();
	DECLARE_DYNCREATE(CMetavw1View)
    BOOL FullDragOn();

	BOOL m_fDraw;
	BOOL m_fFullDragOn;
	UINT m_uiTimer;
	RECT m_rectDraw;
	

// Attributes
public:
	CMetavw1Doc* GetDocument();
	BOOL m_bSizing;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMetavw1View)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMetavw1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMetavw1View)
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnEditCopy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in metavvw.cpp
inline CMetavw1Doc* CMetavw1View::GetDocument()
   { return (CMetavw1Doc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
