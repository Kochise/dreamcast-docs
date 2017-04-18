// SceneVw.h : interface of the CSceneView class
//
/////////////////////////////////////////////////////////////////////////////
#include "gllib.h"
#include "Scene.h"

class CSceneView : public CGLView
{
protected: // create from serialization only
	CSceneView();
	DECLARE_DYNCREATE(CSceneView)

// Attributes
public:
	CEasyTexDoc* GetDocument()   { return (CEasyTexDoc*)m_pDocument; }

	// Rotate
	BOOL m_bRotate ;
	void Rotate(BOOL bRotate) ;
	void Tick() ;

protected:
	CScene m_aScene ;
	virtual CGL* GetGLptr() { return &m_aScene; }
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSceneView)
	public:
	protected:
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
	afx_msg void OnRotatePyramid();
	afx_msg void OnUpdateRotatePyramid(CCmdUI* pCmdUI);
	afx_msg void OnRotateDodecahedron();
	afx_msg void OnUpdateRotateDodecahedron(CCmdUI* pCmdUI);
	afx_msg void OnTextureOpen();
	afx_msg void OnOptionsDecal();
	afx_msg void OnUpdateOptionsDecal(CCmdUI* pCmdUI);
	afx_msg void OnOptionsModulate();
	afx_msg void OnUpdateOptionsModulate(CCmdUI* pCmdUI);
	afx_msg void OnUpdateTextureOpen(CCmdUI* pCmdUI);
	afx_msg void OnTextureEnable();
	afx_msg void OnUpdateTextureEnable(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
