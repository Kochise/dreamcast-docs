// clipvw.h : interface of the CClipView class
//
/////////////////////////////////////////////////////////////////////////////

class CClipView : public CView
{
protected: // create from serialization only
    CClipView();
    DECLARE_DYNCREATE(CClipView)

// Attributes
public:
    CClipDoc* GetDocument();

// Operations
public:

// Implementation
public:
    virtual ~CClipView();
    virtual void OnDraw(CDC* pDC);  // overridden to draw this view
    virtual void OnUpdate(CView* pView, LPARAM lHint, CObject* pHint);
    virtual void OnInitialUpdate();

#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

private:
    CListBox m_wndList;
    CFont m_font;
    int m_iFontHeight;
    int m_iFontWidth;
    CTransBmp m_bmSmile;

// Generated message map functions
protected:
    //{{AFX_MSG(CClipView)
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnDestroy();
    afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
    afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg void OnSetFocus(CWnd* pOldWnd);
    afx_msg void OnListBoxDblClick();
    afx_msg void OnUpdateEditCopy(CCmdUI* pCmdUI);
    afx_msg void OnEditCopy();
    afx_msg void OnUpdateEditPaste(CCmdUI* pCmdUI);
    afx_msg void OnEditPaste();
    afx_msg void OnUpdateEditDel(CCmdUI* pCmdUI);
    afx_msg void OnEditDel();
    afx_msg void OnEditAdd();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in clipvw.cpp
inline CClipDoc* CClipView::GetDocument()
   { return (CClipDoc*) m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
