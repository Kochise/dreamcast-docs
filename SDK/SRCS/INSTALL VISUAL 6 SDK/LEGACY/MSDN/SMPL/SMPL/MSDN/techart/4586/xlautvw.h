// XlAutvw.h : interface of the CXlAutoView class
//
/////////////////////////////////////////////////////////////////////////////

class CXlAutoCntrItem;

class CXlAutoView : public CView
{
protected: // create from serialization only
	CXlAutoView();
	DECLARE_DYNCREATE(CXlAutoView)

// Attributes
public:
	CXlAutoDoc* GetDocument();
	// m_pSelection holds the selection to the current CXlAutoCntrItem.
	// For many applications, such a member variable isn't adequate to
	//  represent a selection, such as a multiple selection or a selection
	//  of objects that are not CXlAutoCntrItem objects.  This selection
	//  mechanism is provided just to help you get started.

	// TODO: replace this selection mechanism with one appropriate to your app.
	CXlAutoCntrItem* m_pSelection;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXlAutoView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual BOOL IsSelected(const CObject* pDocItem) const;// Container support
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CXlAutoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CXlAutoView)
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnInsertObject();
	afx_msg void OnCancelEditCntr();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnAddstuffAdddata();
	afx_msg void OnAddstuffAddchart();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in XlAutvw.cpp
inline CXlAutoDoc* CXlAutoView::GetDocument()
   { return (CXlAutoDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
