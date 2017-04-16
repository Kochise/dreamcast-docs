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
    virtual void OnInitialUpdate();     // first time after construct
    virtual void OnUpdate(CView *pView, LPARAM lHint, CObject *pObj);

protected: //DER --- the following protected stuff is all mine
	UINT m_timer ;
	
private:
    void Render(LPRECT pClipRect = NULL);
    void RenderAndDrawDirtyList();

private:
    //BOOL m_bMouseCaptured;          // TRUE if mouse captured
    /*DER --- CAnimSprite*/ 
    //CBody *m_pCapturedSprite; // Pointer to captured sprite (for drag)
    //CPoint m_ptOffset;              // offset into sprite at capture time
    CRectList m_DirtyList;          // dirty rectangle list

// Generated message map functions
protected:
    //{{AFX_MSG(CAnimView)
   afx_msg void OnFileLoadbkgnd();
   afx_msg void OnFileLoadsprite();
   afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
   afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
   afx_msg void OnDestroy();
   afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnSimulateGo();
	afx_msg void OnUpdateSimulateGo(CCmdUI* pCmdUI);
	afx_msg void OnSimulateStop();
	afx_msg void OnUpdateSimulateStop(CCmdUI* pCmdUI);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnUpdateFileLoadsprite(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFileLoadbkgnd(CCmdUI* pCmdUI);
	afx_msg void OnOptionsUniverse();
	afx_msg void OnUpdateOptionsUniverse(CCmdUI* pCmdUI);
	//}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in animvw.cpp
inline CAnimDoc* CAnimView::GetDocument()
   { return (CAnimDoc*) m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
