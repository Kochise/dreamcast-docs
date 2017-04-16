// animtvw.h : interface of the CAnimTestView class
//
/////////////////////////////////////////////////////////////////////////////

class CAnimTestDoc;

class CAnimTestView : public COSBView
{
protected: // create from serialization only
    CAnimTestView();
    DECLARE_DYNCREATE(CAnimTestView)

// Attributes
public:
    CAnimTestDoc* GetDocument();
    
// Operations
public:
    void Idle();
    void DrawTriangle();


// Implementation
public:
    virtual ~CAnimTestView();
    virtual void OnDraw(CDC* pDC);  // overridden to draw this view
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

private:
    BOOL m_bIdle;
    double m_angle;

    void TestDIBSurf(CPalette* pPal);
    void Rotate(POINT* ppt, int iPoints, double a, int x, int y);

// Generated message map functions
protected:
    //{{AFX_MSG(CAnimTestView)
    afx_msg void OnTestDibsurf();
    afx_msg void OnTestMeter();
    afx_msg void OnTestDibsurfnp();
    afx_msg void OnTimer(UINT nIDEvent);
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnDestroy();
    afx_msg void OnTestVu();
    afx_msg void OnTestRecord();
    afx_msg void OnTestWavefile();
    afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTestWaveres();
	//}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in animtvw.cpp
inline CAnimTestDoc* CAnimTestView::GetDocument()
   { return (CAnimTestDoc*) m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
