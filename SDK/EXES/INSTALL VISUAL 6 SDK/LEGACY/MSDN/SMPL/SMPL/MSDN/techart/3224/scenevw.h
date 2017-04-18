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
	CEasyCIDoc* GetDocument()   { return (CEasyCIDoc*)m_pDocument; }


protected:
	CScene aScene ;
	virtual CGL* GetGLptr() { return &aScene; }
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
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
