// mainfrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#include "..\include\appliancesid.h" // COM object ID
#include "..\include\idrawing.h" // IDrawing interface
#include "..\include\ioutlet.h" // IOutlet interface
#include "..\include\ilight.h" // ILight interface
#include "..\include\iapplianceui.h" // IApplianceUI interface

#define MAX_APPLIANCES 10

class CMainFrame : public CFrameWnd
{
public:
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
    CDIB        m_dibBkgnd;
    CDIBSurface m_dsBuffer; // off-screen paint buffer
    CDIBPal     m_pal;
    IUnknown*   m_pAppliance[MAX_APPLIANCES];
    CRect       m_rcAppliance[MAX_APPLIANCES];
    int         m_iNumAppliances;
    CRect*      m_pSelectRect;
    int         m_iSelect;

    void CreateAppliance(REFIID riid,
                         IUnknown** ppIUnknown,
                         int x, int y,
                         CRect* pRect);
    void DrawObject(CDC* pDC, IUnknown* pIUnknown, int x, int y);

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaletteChanged(CWnd* pFocusWnd);
	afx_msg BOOL OnQueryNewPalette();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
