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
	//CEasyglDoc* GetDocument()   { return (CEasyglDoc*)m_pDocument; }

	// Rotation Support
	void Rotate(BOOL bRotate) ;
	void Tick() ;
	BOOL m_bRotate ;

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
	afx_msg void OnOptionsChange();
	afx_msg void OnRotateStart();
	afx_msg void OnUpdateRotateStart(CCmdUI* pCmdUI);
	afx_msg void OnRotateStop();
	afx_msg void OnUpdateRotateStop(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
