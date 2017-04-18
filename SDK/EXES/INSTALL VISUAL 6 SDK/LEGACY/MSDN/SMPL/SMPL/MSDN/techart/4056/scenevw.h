// SceneVw.h : interface of the CSceneView class
//
/////////////////////////////////////////////////////////////////////////////
#include "gllib.h"
#include "animate.h"
#include "Scene.h"
#include "SceneCI.h"
#include "CSceneBox.h"
#include "CSceneDodec.h"
#include "CScenePyramid.h"
#include "CSimpleDIB.h"

class CSceneView : public CGLView // ## CView
{
protected: // create from serialization only
	CSceneView();
	DECLARE_DYNCREATE(CSceneView)

// Attributes
public:
	CEasyBitDoc* GetDocument()   { return (CEasyBitDoc*)m_pDocument; }

	CDIBSurface m_aDIBSurface ;		// CDIBSurface from Nigel's Animation class.
	CSimpleDIB m_theSimpleDIB[3] ;	// DIB sections for rendering scenes.

	CScene m_aScene ; 				   // Scene which renders in the client area.
	CScene m_aSceneOnDIB ;			   // Scene which renders on m_aDIBSurface.

	CSize m_sizeBitmap;				   // Size of the bitmaps displayed on the left side of display.

	// Captions
	CFont m_font ;					      // Font for captions.
	int m_iFontHeight ;
	int m_iFontWidth ;

	// Helper
	void DrawBlueBorder(CDC* pdc) ;				   // Draw a border around the bitmaps.
   void DrawCaption(CDC* pdc, LPCTSTR str) ; 	// Write caption onto bitmaps.

	// Palette Helper
	CPalette* CopyPalette(CPalette* pPalOrg); 

	// Rotate
	BOOL m_bRotate ;
	void Rotate(BOOL bRotate) ;
	void Tick() ;

	// Timing Helper Funcitons.
	DWORD TimeIdentity(int iReps);
	BOOL m_bTiming ; 
	BOOL IsIdentityPal(CDC* pDC) ;

	// Status Bar update helper
	CMainFrame* m_pMainFrame ;

protected:

	virtual CGL* GetGLptr() { return &m_aScene; }
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSceneView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void OnDraw(CDC* pDC);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSceneView();

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSceneView)
	afx_msg void OnRotateStart();
	afx_msg void OnUpdateRotateStart(CCmdUI* pCmdUI);
	afx_msg void OnRotateStop();
	afx_msg void OnUpdateRotateStop(CCmdUI* pCmdUI);
	afx_msg void OnRotateBox();
	afx_msg void OnUpdateRotateBox(CCmdUI* pCmdUI);
	afx_msg void OnRotateDodec();
	afx_msg void OnUpdateRotateDodec(CCmdUI* pCmdUI);
	afx_msg void OnRotatePyramid();
	afx_msg void OnUpdateRotatePyramid(CCmdUI* pCmdUI);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimingBlting();
	afx_msg void OnPaletteChanged(CWnd* pFocusWnd);
	afx_msg BOOL OnQueryNewPalette();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
