// dragbvw.h : interface of the CDragbezView class
//
/////////////////////////////////////////////////////////////////////////////
#include <afxtempl.h>

class CDragbezView : public CView
{
protected: // create from serialization only
	CDragbezView();
	DECLARE_DYNCREATE(CDragbezView)

// Attributes
public:
	CDragbezDoc* GetDocument();
	CList <CCables, CCables&> m_connectorlist;
	CCables     *m_pCables;
	CCables      m_PickedCable;
	BOOL         m_bConnectorHit;
	int          m_nConnector;
    int          m_ViewLandmarks;
	CPoint       m_OldMousePos;
	POSITION     m_pos;
	SIZE         m_szHitPointDiff;
	BOOL         m_bGestureSet;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDragbezView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDragbezView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDragbezView)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnDestroy();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnViewLandmarks();
	afx_msg void OnEditClear();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in dragbvw.cpp
inline CDragbezDoc* CDragbezView::GetDocument()
   { return (CDragbezDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
