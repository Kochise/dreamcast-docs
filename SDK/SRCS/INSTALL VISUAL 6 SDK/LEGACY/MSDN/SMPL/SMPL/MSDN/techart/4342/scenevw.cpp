// SceneVw.cpp : implementation of the CSceneView class
//

#include "stdafx.h"
#include "EasyFont.h"

#include "EasyFdoc.h"
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
	ON_COMMAND(ID_OPTIONS_CHANGE, OnOptionsChange)
	ON_COMMAND(ID_ROTATE_START, OnRotateStart)
	ON_UPDATE_COMMAND_UI(ID_ROTATE_START, OnUpdateRotateStart)
	ON_COMMAND(ID_ROTATE_STOP, OnRotateStop)
	ON_UPDATE_COMMAND_UI(ID_ROTATE_STOP, OnUpdateRotateStop)
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
// Rotation Support

void CSceneView::Rotate(BOOL bRotate)
{
	m_bRotate = bRotate ;
 	// Stop idle loop mode
 	CEasyFontApp* pApp = (CEasyFontApp*) AfxGetApp();
 	pApp->SetIdleEvent(m_bRotate ? this : NULL);
}

void CSceneView::Tick()
{
	m_aScene.Rotate() ;
	Invalidate(FALSE) ;
	UpdateWindow() ;
}

/////////////////////////////////////////////////////////////////////////////
// CSceneView message handlers

void CSceneView::OnOptionsChange() 
{
	m_aScene.DoDialog(this); 	
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
