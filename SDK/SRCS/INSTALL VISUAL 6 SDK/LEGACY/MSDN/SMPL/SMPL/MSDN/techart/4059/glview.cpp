// glview.cpp : implementation of the CGLView class
//

#include "stdafx.h"

#include "cgl.h"
#include "glview.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGLView

//IMPLEMENT_DYNCREATE(CGLView, CView)

BEGIN_MESSAGE_MAP(CGLView, CView)
	//{{AFX_MSG_MAP(CGLView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_DESTROY()
	ON_WM_PALETTECHANGED()
	ON_WM_QUERYNEWPALETTE()
	ON_WM_NCCREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGLView construction/destruction

CGLView::CGLView()
{
}

CGLView::~CGLView()
{
}

/////////////////////////////////////////////////////////////////////////////
// CGLView message handlers

//
// OnEraseBkgnd: Don't erase the background. OpenGL will do it.
//
BOOL CGLView::OnEraseBkgnd(CDC* pDC) 
{
	//return CView::OnEraseBkgnd(pDC);
	return TRUE ;
}

//
// PreCreateWindow: Clip siblings and children.
//
BOOL CGLView::PreCreateWindow(CREATESTRUCT& cs) 
{
	TRACE0("PreCreateWindow\r\n") ;
  	cs.style |= WS_CLIPSIBLINGS | WS_CLIPCHILDREN; 
	return CView::PreCreateWindow(cs);
}

//
// OnNcCreate: Setup the m_pGL pointer so we can use virtual function calls.
//
BOOL CGLView::OnNcCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (!CView::OnNcCreate(lpCreateStruct))
		return FALSE;
	TRACE0("OnNcCreate\r\n") ;
	
	m_pGL = GetGLptr() ; // Moved from OnCreate
	ASSERT(m_pGL) ;
	
	return TRUE;
}

//
// OnCreate: Create a CGL object.
//
int CGLView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	TRACE0("OnCreate\r\n") ;

	//pGL = GetGLptr() ; // MOVED TO CTOR (NOT) move to NCCreate
	//ASSERT(pGL) ;

	BOOL bResult = m_pGL->Create(this) ;
	if (bResult)
		return 0 ;
	else
		return -1;
}

//
// OnSize: Resize the CGL object.
//
void CGLView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);	
	TRACE0("OnSize\r\n") ;

	m_pGL->Resize(cx,cy) ;	
}

//
// OnInitialUpate: Initialize the CGL object.
//
void CGLView::OnInitialUpdate() 
{
	TRACE0("OnInitialUpdate\r\n") ;	
	
	m_pGL->Init() ;
	CView::OnInitialUpdate();
}

//
// OnDraw: Render the CGL object.
//
void CGLView::OnDraw(CDC* pDC)
{
	TRACE0("OnDraw\r\n") ;
	m_pGL->Render() ;	
}

//
// OnDestory: Destory the CGL object.
//
void CGLView::OnDestroy() 
{
	m_pGL->Destroy() ;
	CView::OnDestroy();
}

void CGLView::OnPaletteChanged(CWnd* pFocusWnd) 
{
	//CView::OnPaletteChanged(pFocusWnd);
	TRACE("OnPaletteChanged\r\n") ;
    // See if the change was caused by us and ignore it if not.
    if (pFocusWnd != this) {
        OnQueryNewPalette();
    }
}

BOOL CGLView::OnQueryNewPalette() 
{
	//	return CView::OnQueryNewPalette();
	TRACE0("OnQueryNewPalette\r\n") ;
    // We are going active or the system palette has changed,
    // so realize our palette.
	CPalette* pPal = m_pGL->GetPalette() ;
    if (pPal) {   	
        CDC* pDC = GetDC();
        pDC->SelectPalette(pPal, FALSE);
        UINT u = pDC->RealizePalette();
        ReleaseDC(pDC);
       	if (u != 0) {
            // Some colors changed, so we need to do a repaint.
            InvalidateRect(NULL, TRUE); // Repaint the lot.
        }
    }
    return TRUE; // Windows ignores this.	
}

