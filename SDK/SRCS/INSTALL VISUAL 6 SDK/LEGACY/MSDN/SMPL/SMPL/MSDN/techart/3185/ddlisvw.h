// ddlisvw.h : interface of the CDdlistView class
//
/////////////////////////////////////////////////////////////////////////////

#include "ddlstbox.h"

class CDdlistView : public CView
{
protected: // create from serialization only
    CDdlistView();
    DECLARE_DYNCREATE(CDdlistView)

// Attributes
public:
    CDdlistDoc* GetDocument();
    CDDListBox m_wndList;

// Operations
public:

// Implementation
public:
    virtual ~CDdlistView();
    virtual void OnDraw(CDC* pDC);  // overridden to draw this view
    virtual void OnInitialUpdate();
    virtual void OnUpdate(CView* pView, LPARAM lHint, CObject* pObj);


#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

    // Printing support
protected:
    virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
    virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
    virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Generated message map functions
protected:
    //{{AFX_MSG(CDdlistView)
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnDestroy();
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg void OnSetFocus(CWnd* pOldWnd);
    afx_msg void OnUpdateEditCopy(CCmdUI* pCmdUI);
    afx_msg void OnEditCopy();
    afx_msg void OnUpdateEditPaste(CCmdUI* pCmdUI);
    afx_msg void OnEditPaste();
    afx_msg LRESULT OnQueryDrop(WPARAM wParam,LPARAM lParam);
    afx_msg LRESULT OnDoDrop(WPARAM wParam,LPARAM lParam);
    afx_msg LRESULT OnBeginDragDrop(WPARAM wParam,LPARAM lParam);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ddlisvw.cpp
inline CDdlistDoc* CDdlistView::GetDocument()
   { return (CDdlistDoc*) m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
