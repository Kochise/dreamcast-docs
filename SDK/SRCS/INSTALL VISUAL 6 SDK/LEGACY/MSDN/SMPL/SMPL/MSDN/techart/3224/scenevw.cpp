// SceneVw.cpp : implementation of the CSceneView class
//

#include "stdafx.h"
#include "EasyCI.h"

#include "EasyCdoc.h"
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
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSceneView construction/destruction

CSceneView::CSceneView()
{
}

CSceneView::~CSceneView()
{
}

/////////////////////////////////////////////////////////////////////////////
// CSceneView message handlers

int CSceneView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	BOOL bResult = m_pGL->Create(this, PFD_TYPE_COLORINDEX) ;
	if (bResult)
		return 0 ;
	else
		return -1;
}
