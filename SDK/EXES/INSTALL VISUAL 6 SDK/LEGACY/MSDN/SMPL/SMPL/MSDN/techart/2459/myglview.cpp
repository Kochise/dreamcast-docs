// myglview.cpp : implementation of the CMyglView class
//
#include "stdafx.h"
#include <windows.h>
#include "COpenGL.h"
#include "mygl.h"

#include "mygldoc.h"
#include "myglview.h"
#include "drawgl.h"
#include "pixform.h"
#include "pfdinfo.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyglView
IMPLEMENT_DYNCREATE(CMyglView, CView)

BEGIN_MESSAGE_MAP(CMyglView, CView)
	//{{AFX_MSG_MAP(CMyglView)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_COMMAND(ID_PIXFMT_CHOOSE, OnPixfmtChoose)
	ON_COMMAND(ID_PIXFMT_DESCRIBE, OnPixfmtDescribe)
	ON_COMMAND(ID_PIXFMT_ENUM, OnPixfmtEnum)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyglView construction/destruction

CMyglView::CMyglView()
{
}

CMyglView::~CMyglView()
{
  delete m_glptr;
}

/////////////////////////////////////////////////////////////////////////////
// 
CMyglView *CMyglView::GetView()
{
  CFrameWnd *pFrame = (CFrameWnd *)(AfxGetApp()->m_pMainWnd);
  CView *pView = pFrame->GetActiveView();
  if (!pView)
    return (NULL);
  if (!pView->IsKindOf(RUNTIME_CLASS(CMyglView)))
    return (NULL);
  return (CMyglView *)pView;
}



/////////////////////////////////////////////////////////////////////////////
// CMyglView drawing
void CMyglView::OnDraw(CDC* pDC)
{
  CMyglDoc* pDoc = GetDocument();
  RECT rc;
  HGLRC hglrc = m_glptr->wglGetCurrentContext();

  if (hglrc)
  {
    if (!m_glptr->IsSurfaceInitialized())
	{
	 initialize(GetSafeHwnd());
	 m_glptr->SetSurfaceInitialized();
	}
    GetClientRect(&rc);
    DrawScene(rc);
  }
  
}

/////////////////////////////////////////////////////////////////////////////
// CMyglView diagnostics

#ifdef _DEBUG
void CMyglView::AssertValid() const
{
	CView::AssertValid();
}
  						    
void CMyglView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMyglDoc* CMyglView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyglDoc)));
	return (CMyglDoc*) m_pDocument;
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyglView message handlers
int CMyglView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{

    if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	HWND hwnd = GetSafeHwnd();
	HDC hdc = ::GetDC(hwnd);
    m_glptr = new COpenGL(hdc);
   	return 0;
}


/////////////////////////////////////////////////////////////////////////////
//  
BOOL CMyglView::PreCreateWindow(CREATESTRUCT& cs)
{
  //the view windows style bits must include WS_CLIPSIBLINGS and
  //WS_CLIPCHILDREN so that the wgl functions will work. This is
  //
  cs.style = cs.style | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

  return CView::PreCreateWindow(cs);
}


/////////////////////////////////////////////////////////////////////////////
// CMyglView WM_DESTROY

void CMyglView::OnDestroy()
{

   	CView::OnDestroy();
	HWND hwnd = GetSafeHwnd();
	//
	//Release the current GL rendering context and device context
	//
	m_glptr->ReleaseGLRC(hwnd);
	
}

/////////////////////////////////////////////////////////////////////////////
//  
void CMyglView::OnPixfmtChoose()
{
	CPixForm PixForm;
	PixForm.SetID(ID_PIXFMT_CHOOSE);
	PixForm.SetGLptr(m_glptr);
	PixForm.DoModal();
	
}

/////////////////////////////////////////////////////////////////////////////
//  
void CMyglView::OnPixfmtDescribe()
{

	if (m_glptr->wglGetCurrentContext())
	{ 
	  CPFDInfo pfdInfo;
      pfdInfo.SetGLptr(m_glptr);
	  pfdInfo.DoModal();
	}
	else MessageBox( "No current rendering context", NULL, MB_ICONEXCLAMATION | MB_OK);
	
}

/////////////////////////////////////////////////////////////////////////////
// 
void CMyglView::OnPixfmtEnum()
{
	CPixForm PixForm;
	PixForm.SetID(ID_PIXFMT_ENUM);
	PixForm.SetGLptr(m_glptr);
	PixForm.DoModal();
}
 
/////////////////////////////////////////////////////////////////////////////
// 
void CMyglView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

    resize(GetSafeHwnd());	
}
