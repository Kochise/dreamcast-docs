// SceneVw.cpp : implementation of the CSceneView class
//

#include "stdafx.h"
#include "easygl.h"

#include "easygdoc.h"
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
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSceneView construction/destruction

CSceneView::CSceneView()
{
	// TODO: add construction code here

}

CSceneView::~CSceneView()
{
}

/////////////////////////////////////////////////////////////////////////////
// CSceneView message handlers
