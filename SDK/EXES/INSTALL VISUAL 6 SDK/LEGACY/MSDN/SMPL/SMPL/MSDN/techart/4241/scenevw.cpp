// SceneVw.cpp : implementation of the CSceneView class
//

#include "stdafx.h"
#include "EasyTex.h"

#include "EasyTdoc.h"
#include "SceneVw.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSceneView

IMPLEMENT_DYNCREATE(CSceneView, CView /* CGLView */)

BEGIN_MESSAGE_MAP(CSceneView, CGLView)
	//{{AFX_MSG_MAP(CSceneView)
	ON_COMMAND(ID_ROTATE_START, OnRotateStart)
	ON_UPDATE_COMMAND_UI(ID_ROTATE_START, OnUpdateRotateStart)
	ON_COMMAND(ID_ROTATE_STOP, OnRotateStop)
	ON_UPDATE_COMMAND_UI(ID_ROTATE_STOP, OnUpdateRotateStop)
	ON_COMMAND(ID_ROTATE_BOX, OnRotateBox)
	ON_UPDATE_COMMAND_UI(ID_ROTATE_BOX, OnUpdateRotateBox)
	ON_COMMAND(ID_ROTATE_PYRAMID, OnRotatePyramid)
	ON_UPDATE_COMMAND_UI(ID_ROTATE_PYRAMID, OnUpdateRotatePyramid)
	ON_COMMAND(ID_ROTATE_DODECAHEDRON, OnRotateDodecahedron)
	ON_UPDATE_COMMAND_UI(ID_ROTATE_DODECAHEDRON, OnUpdateRotateDodecahedron)
	ON_COMMAND(ID_TEXTURE_OPEN, OnTextureOpen)
	ON_COMMAND(ID_OPTIONS_DECAL, OnOptionsDecal)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_DECAL, OnUpdateOptionsDecal)
	ON_COMMAND(ID_OPTIONS_MODULATE, OnOptionsModulate)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_MODULATE, OnUpdateOptionsModulate)
	ON_UPDATE_COMMAND_UI(ID_TEXTURE_OPEN, OnUpdateTextureOpen)
	ON_COMMAND(ID_TEXTURE_ENABLE, OnTextureEnable)
	ON_UPDATE_COMMAND_UI(ID_TEXTURE_ENABLE, OnUpdateTextureEnable)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSceneView construction/destruction

CSceneView::CSceneView()
{
	m_bRotate = FALSE ;
}

CSceneView::~CSceneView()
{
}

/////////////////////////////////////////////////////////////////////////////
// CGLEasyView OnIdle rotation support
//
void CSceneView::Rotate(BOOL bRotate)
{
	m_bRotate = bRotate ;
 	// Stop idle loop mode
 	CEasyTexApp* pApp = (CEasyTexApp*) AfxGetApp();
 	pApp->SetIdleEvent(m_bRotate ? this : NULL);
}

void CSceneView::Tick()
{
	m_aScene.Rotate() ;
	Invalidate(FALSE) ;
	UpdateWindow() ;
}

void CSceneView::OnRotateStart() 
{
	Rotate(TRUE) ;
}

void CSceneView::OnUpdateRotateStart(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_bRotate) ;
}

void CSceneView::OnRotateStop() 
{
	Rotate(FALSE) ;
	Invalidate(FALSE) ;
	UpdateWindow() ;
}

void CSceneView::OnUpdateRotateStop(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(!m_bRotate) ;
}

void CSceneView::OnRotateBox() 
{
	m_aScene.SetRotatingObject(CScene::Box) ;
}

void CSceneView::OnUpdateRotateBox(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_aScene.GetRotatingObject() == CScene::Box) ;
	pCmdUI->Enable(!m_bRotate) ;
}

void CSceneView::OnRotateDodecahedron() 
{
	m_aScene.SetRotatingObject(CScene::Dodec) ;
}

void CSceneView::OnUpdateRotateDodecahedron(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_aScene.GetRotatingObject() == CScene::Dodec) ;
	pCmdUI->Enable(!m_bRotate) ;
}

void CSceneView::OnRotatePyramid() 
{
	m_aScene.SetRotatingObject(CScene::Pyramid) ;
}


void CSceneView::OnUpdateRotatePyramid(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_aScene.GetRotatingObject() == CScene::Pyramid) ;
	pCmdUI->Enable(!m_bRotate) ;
}

void CSceneView::OnTextureOpen() 
{
	if (m_aScene.GetTextureMap())
	{   
		Invalidate(FALSE) ;
		UpdateWindow() ;	
	}
}

void CSceneView::OnUpdateTextureOpen(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(!m_bRotate) ;
}


void CSceneView::OnOptionsDecal() 
{
	m_aScene.SetDecalMode(TRUE) ;	
	Invalidate(FALSE) ;
	UpdateWindow() ;	
}

void CSceneView::OnUpdateOptionsDecal(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_aScene.GetDecalMode()) ;
	pCmdUI->Enable(!m_bRotate) ;
}

void CSceneView::OnOptionsModulate() 
{
	m_aScene.SetDecalMode(FALSE) ;	
	Invalidate(FALSE) ;
	UpdateWindow() ;	
}

void CSceneView::OnUpdateOptionsModulate(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(!m_aScene.GetDecalMode()) ;
	pCmdUI->Enable(!m_bRotate) ;	
}


void CSceneView::OnTextureEnable() 
{
	BOOL bMode = m_aScene.GetTextureMode() ;
	m_aScene.SetTextureMode(!bMode) ;
	Invalidate(FALSE) ;
	UpdateWindow() ;
}

void CSceneView::OnUpdateTextureEnable(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_aScene.GetTextureMode()) ;   
}


