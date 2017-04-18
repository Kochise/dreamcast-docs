// animvw.h : interface of the CAnimView class
//
/////////////////////////////////////////////////////////////////////////////

#include "osdibvw.h"
#include "rectls.h"

class CAnimView : public COffScreenDIBView
{
protected: // create from serialization only
    CAnimView();
    DECLARE_DYNCREATE(CAnimView)

public:
    CAnimDoc* GetDocument();
    virtual ~CAnimView();
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

protected:
//    virtual void OnInitialUpdate();     // first time after construct
    virtual void OnUpdate(CView *pView, LPARAM lHint, CObject *pObj);

private:
    void Render(LPRECT pClipRect = NULL);
    void RenderAndDrawDirtyList();

private:
    BOOL m_bMouseCaptured;          // TRUE if mouse captured
    CAnimSprite *m_pCapturedSprite; // Pointer to captured sprite (for drag)
    CPoint m_ptOffset;              // offset into sprite at capture time
    CRectList m_DirtyList;          // dirty rectangle list

// Generated message map functions
protected:
    //{{AFX_MSG(CAnimView)
    afx_msg void OnFileLoadbkgnd();
    afx_msg void OnFileLoadsprite();
    afx_msg void OnUpdateFileLoadbkgnd(CCmdUI* pCmdUI);
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnDestroy();
    afx_msg void OnTimer(UINT nIDEvent);
    afx_msg void OnTestSpriteperf();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in animvw.cpp
inline CAnimDoc* CAnimView::GetDocument()
   { return (CAnimDoc*) m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
