// VCDravw.h : interface of the CVCDrawView class
//
/////////////////////////////////////////////////////////////////////////////

#include "icopalob.h"               // IDispatch interface
#include "idsobj.h"                 // IDispatch interface

class CVCDrawView : public CView
{
protected: // create from serialization only
	CVCDrawView();
	DECLARE_DYNCREATE(CVCDrawView)

// Attributes
public:
	CVCDrawDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVCDrawView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual void OnInitialUpdate();
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CVCDrawView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CVCDrawView)
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

    IColorPalObj m_iPalette;
    IDrawSurfObj m_iBkgnd;
    IDrawSurfObj m_iRedBall;
    IDrawSurfObj m_iBuffer;
    int m_iRedBallX;
    int m_iRedBallY;
    UINT m_uiTimer;
    int m_vy;

    void Render();
    void Draw();

};

#ifndef _DEBUG  // debug version in VCDravw.cpp
inline CVCDrawDoc* CVCDrawView::GetDocument()
   { return (CVCDrawDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
