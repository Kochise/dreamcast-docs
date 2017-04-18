//***************************************************************************
//
//  LifeView.h
//
//***************************************************************************

class CLifeView : public CScrollView
{
    DECLARE_DYNCREATE (CLifeView)

private:
    int     m_nPrevRow;
    int     m_nPrevCol;
    CBitmap m_bmGrayCell;
    CBitmap m_bmBlueCell;
    CPoint  m_ptOrg;

    void DrawCell (CDC*, int, int, BOOL);
    void SetGridOrigin (int, int);
    void SetScrollParms ();

public:
    CLifeView ();
    CLifeDoc* GetDocument ();
    virtual void OnInitialUpdate ();

protected:
    virtual void OnDraw (CDC*);
    virtual void OnUpdate (CView*, LPARAM, CObject*);

    afx_msg void OnSize (UINT, int, int);
    afx_msg BOOL OnEraseBkgnd (CDC*);
    afx_msg void OnLButtonDown (UINT, CPoint);
    afx_msg void OnMouseMove (UINT, CPoint);

    DECLARE_MESSAGE_MAP ()
};
