// rawview.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRawView view

class CRawView : public CScrollView
{
protected:
	CRawView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CRawView)


private:
    CFont *m_cfFixedFont;
    int m_iFontWidth;
    int m_iFontHeight;
    int m_iFirstLine;
    int m_iLastLine;
    int m_iWndLines;

// Attributes

public:
    CViewfileDoc* GetDocument();


// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRawView)
	public:
	virtual void OnInitialUpdate();
	virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CRawView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CRawView)
	afx_msg void OnDestroy();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


#ifndef _DEBUG  // debug version in filedvw.cpp
inline CViewfileDoc* CRawView::GetDocument()
   { return (CViewfileDoc*) m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
