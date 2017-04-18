// SceneVw.cpp : implementation of the CSceneView class
//
 
#include "stdafx.h"
#include "EasyDib.h"

#include "EasyDdoc.h"
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
	ON_COMMAND(ID_OPEN_BITMAP, OnOpenBitmap)
	ON_COMMAND(ID_TRANSLATION_BOTH, OnTranslationBoth)
	ON_UPDATE_COMMAND_UI(ID_TRANSLATION_BOTH, OnUpdateTranslationBoth)
	ON_COMMAND(ID_TRANSLATION_DIY, OnTranslationDiy)
	ON_UPDATE_COMMAND_UI(ID_TRANSLATION_DIY, OnUpdateTranslationDiy)
	ON_COMMAND(ID_TRANSLATION_GDI, OnTranslationGdi)
	ON_UPDATE_COMMAND_UI(ID_TRANSLATION_GDI, OnUpdateTranslationGdi)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSceneView construction/destruction

CSceneView::CSceneView()
{
	m_theTranslationMethod = CGLImage::TRANS_BOTH ;
}

CSceneView::~CSceneView()
{
}


/////////////////////////////////////////////////////////////////////////////
// CSceneView message handlers

void CSceneView::OnOpenBitmap() 
{
    CString strFile;    
    // Show an open file dialog to get the name
    CFileDialog dlg   (TRUE,    // open
                       NULL,    // no default extension
                       NULL,    // no initial file name
                       OFN_FILEMUSTEXIST
                       | OFN_HIDEREADONLY,
                       "Image files (*.DIB, *.BMP)|*.DIB;*.BMP|All files (*.*)|*.*||");	 
    if (dlg.DoModal() == IDOK)
    {
        strFile = dlg.GetPathName();
		aScene.m_anImage.Load((LPCTSTR)strFile, m_theTranslationMethod) ;
		Invalidate(FALSE) ;
		UpdateWindow() ;	
    }
}

//
// Translation Method only affects loading of the DIBs.
// Display of the DIBs is not affected by changing translation method.
//
void CSceneView::OnTranslationBoth() 
{
	m_theTranslationMethod = CGLImage::TRANS_BOTH ;
}

void CSceneView::OnUpdateTranslationBoth(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_theTranslationMethod == CGLImage::TRANS_BOTH) ;
}

void CSceneView::OnTranslationDiy() 
{
	m_theTranslationMethod = CGLImage::TRANS_DIY ;
}

void CSceneView::OnUpdateTranslationDiy(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_theTranslationMethod == CGLImage::TRANS_DIY) ;
}

void CSceneView::OnTranslationGdi() 
{
	m_theTranslationMethod = CGLImage::TRANS_GDI ;
}

void CSceneView::OnUpdateTranslationGdi(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_theTranslationMethod == CGLImage::TRANS_GDI) ;
}
