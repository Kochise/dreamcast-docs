// dldmfvw.h : interface of the CNetView class
//
/////////////////////////////////////////////////////////////////////////////

class matrix;

class CNetView : public CScrollView
{
protected: // create from serialization only
	CNetView();
	DECLARE_DYNCREATE(CNetView)

private: 

TP *m_tpActivated;
SIZE m_SizeNet;
int m_iSnapSize;
// class-specific variables

public:

CRITICAL_SECTION m_csDrawGuard;
place *m_places;
transition *m_transitions;


// Attributes
public:
	CPetriNetDoc* GetDocument();
	CPetriNetDoc *m_pAttachedDocument;

// Operations
public:

// Implementation
public:
	virtual ~CNetView();
	virtual void OnPrepareDC(CDC *pDC, CPrintInfo *pInfo);
    virtual void OnDraw(CDC* pDC);  // overridden to draw this view
    virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
    virtual void OnInitialUpdate();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// helper functions

    void RecalcScrollDimensions(int NewX, int NewY, BOOL bDirection);
	void ConvertScreenToLog(POINT *pt);
    CPoint ConvertScreenToLog(CPoint pt);
	void NukeNet();
    void DeleteLinks(TPLIST *tpList);
    void DeleteChain(TP *objects, BOOL bType);
    void DumpCoordinateData(HANDLE hFile);
	void Cleanup(transition *);
	void TraverseTransitions(place *);
	void FinishPlace(place *);
	void FinishTransition(transition *);
	CString GrabNameFromNet(BOOL, int);



// Generated message map functions
protected:
	//{{AFX_MSG(CNetView)
	afx_msg void OnNetNewtransitionundercursor();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnNetNewplaceundercursor();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnDestroy();
	afx_msg void OnNetDeletemarkedobjectdel();
	afx_msg void OnNetSnapnettogrid();
	afx_msg void OnNetSetgridsize();
	afx_msg void OnNetEditpropertiesformarkedobjectenter();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG	// debug version in dldmfvw.cpp
inline CPetriNetDoc* CNetView::GetDocument()
   { return (CPetriNetDoc*) m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
