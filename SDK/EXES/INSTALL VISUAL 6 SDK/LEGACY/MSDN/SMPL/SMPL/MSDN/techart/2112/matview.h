// dldetvw.h : interface of the CMatrixView class
//
/////////////////////////////////////////////////////////////////////////////

class CMatrixView : public CView
{
protected: // create from serialization only
	CMatrixView();
	DECLARE_DYNCREATE(CMatrixView)

// Attributes

private: 
    CEdit m_EditCtrl;
	HLOCAL m_hMemory;
public:
	CPetriNetDoc* GetDocument();

// Operations
public:


// Implementation
public:
	virtual ~CMatrixView();
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
    virtual void OnUpdate(CView *pSender, LPARAM lHint, CObject *pHint);
    virtual void OnActivateView(BOOL, CView*,CView *); 
// Generated message map functions
protected:
	//{{AFX_MSG(CMatrixView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnNetFindnetinvariants();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG	// debug version in dldetvw.cpp
inline CPetriNetDoc* CMatrixView::GetDocument()
   { return (CPetriNetDoc*) m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
