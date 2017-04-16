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
	CEasyDIBDoc* GetDocument()   { return (CEasyDIBDoc*)m_pDocument; }

	CGLImage::TRANSLATEMETHOD m_theTranslationMethod;

protected:
	CScene aScene ;
	virtual CGL* GetGLptr() { return &aScene; }
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSceneView)
	public:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSceneView();

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSceneView)
	afx_msg void OnOpenBitmap();
	afx_msg void OnTranslationBoth();
	afx_msg void OnUpdateTranslationBoth(CCmdUI* pCmdUI);
	afx_msg void OnTranslationDiy();
	afx_msg void OnUpdateTranslationDiy(CCmdUI* pCmdUI);
	afx_msg void OnTranslationGdi();
	afx_msg void OnUpdateTranslationGdi(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
