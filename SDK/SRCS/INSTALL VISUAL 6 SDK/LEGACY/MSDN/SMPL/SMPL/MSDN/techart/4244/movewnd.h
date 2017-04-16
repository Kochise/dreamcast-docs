// movewnd.h : header file
//
#ifndef __CMOVINGCHILDWND_H__
#define __CMOVINGCHILDWND_H__

/////////////////////////////////////////////////////////////////////////////
// CMovingChildWnd window

class CMovingChildWnd : public CSaveWnd
{
// Construction
public:
	CMovingChildWnd();

// Attributes
public:
	UINT m_uiTimer ;
	BOOL m_bInit  ;

	CGLWnd m_wndMovingChild ;
// Operations
public:
	// Floating Window Support
	void MoveBuffer(int curX, int curY) ;
	BOOL ShowBuffer() ;

	double m_xTransInc;
	double m_yTransInc;
	int m_wxSize;
	int m_wySize;
	int m_xSize;
	int m_ySize ;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMovingChildWnd)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMovingChildWnd();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMovingChildWnd)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaletteChanged(CWnd* pFocusWnd);
	afx_msg BOOL OnQueryNewPalette();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

#endif
