// spellvw.h : interface of the CSpellView class
//
/////////////////////////////////////////////////////////////////////////////

class CSpellView : public CView
{
protected: // create from serialization only
    CSpellView();
    DECLARE_DYNCREATE(CSpellView)

// Attributes
public:
    CSpellDoc* GetDocument();

// Operations
public:

// Implementation
public:
    virtual ~CSpellView();
    virtual void OnDraw(CDC* pDC);  // overridden to draw this view
    virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint); 
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

private:
    CListBox m_wndList;

// Generated message map functions
protected:
    //{{AFX_MSG(CSpellView)
    afx_msg void OnEditAddWord();
    afx_msg void OnEditDeleteWord();
    afx_msg void OnUpdateEditDeleteWord(CCmdUI* pCmdUI);
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg void OnSetFocus(CWnd* pOldWnd);
    afx_msg void OnEditPlay();
    afx_msg void OnUpdateEditPlay(CCmdUI* pCmdUI);
    afx_msg void OnDoubleClick();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in spellvw.cpp
inline CSpellDoc* CSpellView::GetDocument()
   { return (CSpellDoc*) m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
