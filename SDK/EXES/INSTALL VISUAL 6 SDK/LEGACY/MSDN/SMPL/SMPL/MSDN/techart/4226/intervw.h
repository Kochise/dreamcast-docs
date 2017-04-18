// Intervw.h : interface of the CInterpView class
//
/////////////////////////////////////////////////////////////////////////////

class CInterpView : public CView
{
protected: // create from serialization only
	CInterpView();
	DECLARE_DYNCREATE(CInterpView)

// Attributes
public:
	CInterpDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInterpView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	protected:
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CInterpView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
    CDIBSurface m_dsBuffer;
    BOOL m_bInterpolate;
    BYTE m_Imap2[256][256];

    BOOL SelRelPal(BOOL bForceBkgnd);
    void Render();
    void Interp2(int xd, int yd, int wd, int hd, int xs, int ys);

// Generated message map functions
protected:
	//{{AFX_MSG(CInterpView)
	afx_msg void OnViewInterp();
	afx_msg void OnViewNormal();
	afx_msg void OnPaletteChanged(CWnd* pFocusWnd);
	afx_msg BOOL OnQueryNewPalette();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnUpdateViewInterp(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewNormal(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in Intervw.cpp
inline CInterpDoc* CInterpView::GetDocument()
   { return (CInterpDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
