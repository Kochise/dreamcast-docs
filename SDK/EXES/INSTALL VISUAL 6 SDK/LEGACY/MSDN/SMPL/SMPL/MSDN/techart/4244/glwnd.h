// glwnd.h : header file
//
#ifndef __GLWND_H__
#define __GLWND_H__
/////////////////////////////////////////////////////////////////////////////
// CGLWnd window

class CGLWnd : public CWnd
{
// Construction
public:
	CGLWnd();

// Attributes
public:
   CScene m_aScene ;

	BOOL m_bInit ;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGLWnd)
	public:
	virtual BOOL Create(CWnd* pParent, int cx, int cy);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CGLWnd();

	// Generated message map functions
protected:
	//{{AFX_MSG(CGLWnd)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg void OnDestroy();
	afx_msg void OnPaletteChanged(CWnd* pFocusWnd);
	afx_msg BOOL OnQueryNewPalette();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
#endif
