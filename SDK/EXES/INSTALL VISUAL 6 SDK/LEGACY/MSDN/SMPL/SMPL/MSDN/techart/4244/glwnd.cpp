// glwnd.cpp : implementation file
//

#include "stdafx.h"
#include "PicCube.h"
#include "GLlib.h"
#include "Scene.h"
#include "glwnd.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGLWnd

CGLWnd::CGLWnd()
{
	m_bInit = FALSE ;
}

CGLWnd::~CGLWnd()
{
}


BEGIN_MESSAGE_MAP(CGLWnd, CWnd)
	//{{AFX_MSG_MAP(CGLWnd)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_DESTROY()
	ON_WM_PALETTECHANGED()
	ON_WM_QUERYNEWPALETTE()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CGLWnd message handlers

BOOL CGLWnd::Create(CWnd* pParent, int cx, int cy)
{
    const char* pszClassName 
        = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW,
                              ::LoadCursor(AfxGetResourceHandle(),
                                           MAKEINTRESOURCE(IDC_NULLCURSOR)));

    // Create the window
	BOOL bResult = 
		CWnd::CreateEx(	WS_EX_TOPMOST,
						      pszClassName,
						      "Test", 
						      WS_CHILD | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
						      0,0,
						      cx,cy,
						      pParent->GetSafeHwnd(),
						      NULL) ;

	DWORD dwError = GetLastError() ;
  	
  	ASSERT(bResult) ;

	return bResult ;
}

int CGLWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	//
	// Create the OpenGL Scene
	//	
	BOOL bResult = m_aScene.Create(this) ;
	if (bResult)
		return 0 ;
	else
		return -1;
}

void CGLWnd::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);

   //
   // Set up mapping of OpenGL Scene
   //
	m_aScene.Resize(cx,cy) ;

   //
   // Initialize OpenGL
   //
	if (!m_bInit)
	{
		m_bInit = TRUE ;
		m_aScene.Init() ;
	}   	
}

void CGLWnd::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

   //
   // Render the OpenGL Scene
   //
	m_aScene.Render() ;
}

void CGLWnd::OnDestroy() 
{
	m_aScene.Destroy() ;

	CWnd::OnDestroy();			
}

void CGLWnd::OnPaletteChanged(CWnd* pFocusWnd) 
{
	//CView::OnPaletteChanged(pFocusWnd);
	TRACE("OnPaletteChanged\r\n") ;
    // See if the change was caused by us and ignore it if not.
    if (pFocusWnd != this) {
        OnQueryNewPalette();
    }
}

BOOL CGLWnd::OnQueryNewPalette() 
{
	//	return CView::OnQueryNewPalette();
	TRACE0("CGLWnd::OnQueryNewPalette\r\n") ;
    // We are going active or the system palette has changed,
    // so realize our palette.
	CPalette* pPal = m_aScene.GetPalette() ;
   if (pPal)
   {   	
      CDC* pDC = GetDC();
      pDC->SelectPalette(pPal, FALSE);
      UINT u = pDC->RealizePalette();
      ASSERT(u != GDI_ERROR) ;
      ReleaseDC(pDC);
      if (u != 0) {
            // Some colors changed, so we need to do a repaint.
         InvalidateRect(NULL, TRUE); // Repaint the lot.
      }
      return TRUE ;
   }
   return FALSE; // Windows ignores this.	
}

BOOL CGLWnd::OnEraseBkgnd(CDC* pDC) 
{
	return TRUE ;
}
