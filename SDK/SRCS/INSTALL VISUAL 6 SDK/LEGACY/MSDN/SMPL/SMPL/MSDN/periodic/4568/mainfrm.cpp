#include "stdafx.h"
#include "dclikbar.h"
#include "mainfrm.h"

#ifndef AfxRegisterClass
// AfxRegisterClass is only defined in 32-bit versions of MFC
#define AfxRegisterClass ::RegisterClass
#endif

// The symbol _afxWndControlBar contains the window class name that
// MFC uses to register the control bar. The definition of this symbol is
// private to MFC, so use it at your own risk. If you don't like to use
// externs that belong to MFC, you can just use "AfxControlBar" as the
// class name--for pre-4.0 versions of MFC ONLY! Starting in version 4.0, 
// MFC uses the Windows common control toolbar class and all the code
// shown here to turn on CS_DBLCLKS is unnecessary.
//
#if _MFC_VER < 0x0300
extern const char BASED_CODE _afxWndControlBar[];
#elif _MFC_VER < 0x0400
extern const TCHAR _afxWndControlBar[];
#endif

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// Static class member holds window class name
// (NULL if not registered yet).
// 
LPCSTR CMainFrame::s_winClassName = NULL;

static UINT BASED_CODE buttons[] = {
	ID_FILE_NEW, 
	ID_SEPARATOR, 
	ID_APP_ABOUT
};

static UINT BASED_CODE indicators[] = {
	ID_SEPARATOR,
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

CMainFrame::CMainFrame()
{
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndToolBar.Create(this) ||
		!m_wndToolBar.LoadBitmap(IDR_MAINFRAME) ||
		!m_wndToolBar.SetButtons(buttons,
		  sizeof(buttons)/sizeof(UINT)) )
	{
		TRACE("Failed to create toolbar\n");
		return -1;      // fail to create
	}
	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE("Failed to create status bar\n");
		return -1;      // fail to create
	}
	return 0;
}

//////////////////
// Helper function to register a new window class based on an already
// existing window class, but with a different name and icon. 
// Returns new name if successful; otherwise NULL.
//
static LPCSTR RegisterSimilarClass(LPCSTR lpszNewClassName,
	LPCSTR lpszOldClassName, UINT nIDResource)
{
	// Get class info for old class.
	//
	HINSTANCE hInst = AfxGetInstanceHandle();
	WNDCLASS wc;
	if (!::GetClassInfo(hInst, lpszOldClassName, &wc)) {
		TRACE("Can't find window class %s\n", lpszOldClassName);
		return NULL;
	}

	// Register new class with same info, but different name and icon.
	//
	wc.lpszClassName = lpszNewClassName;
	wc.hIcon = ::LoadIcon(hInst, MAKEINTRESOURCE(nIDResource));
	if (!AfxRegisterClass(&wc)) {
		TRACE("Unable to register window class%s\n", lpszNewClassName);
		return NULL;
	}
	return lpszNewClassName;
}

//////////////////
// Override to register the different class and change window class name.
//
BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if (!CFrameWnd::PreCreateWindow(cs))
		return FALSE;

	if (s_winClassName==NULL) {	
		// One-time initialization: register the class
		//
		s_winClassName = RegisterSimilarClass("MyMainFrame", 
			cs.lpszClass, IDR_MAINFRAME);
		if (!s_winClassName)
			return FALSE;
	}
	cs.lpszClass = s_winClassName;
	return TRUE;
}

////////////////////////////////////////////////////////////////
// CMyChildFrame implementation
//
IMPLEMENT_DYNCREATE(CMyChildFrame, CMDIChildWnd)

BEGIN_MESSAGE_MAP(CMyChildFrame, CMDIChildWnd)
	//{{AFX_MSG_MAP(CMyChildFrame)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// Static class member holds window class name
// (NULL if not registered yet).
// 
LPCSTR CMyChildFrame::s_winClassName = NULL;

CMyChildFrame::CMyChildFrame()
{
}

CMyChildFrame::~CMyChildFrame()
{
}

//////////////////
// Override to register the different class and change window class name.
//
BOOL CMyChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if (!CMDIChildWnd::PreCreateWindow(cs))
		return FALSE;

	if (s_winClassName==NULL) {
		// One-time initialization: register the class
		//
		s_winClassName = RegisterSimilarClass("MyChildFrame", 
			cs.lpszClass, IDR_DOCTYPE);
		if (!s_winClassName)
			return FALSE;
	}
	cs.lpszClass = s_winClassName;
	return TRUE;
}

////////////////////////////////////////////////////////////////
// CMyToolBar implementation. 
//

IMPLEMENT_DYNAMIC(CMyToolBar, CToolBar)

BEGIN_MESSAGE_MAP(CMyToolBar, CToolBar)
	//{{AFX_MSG_MAP(CMyToolBar)
	ON_WM_LBUTTONDBLCLK()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//////////////////
// Handle double-click
//
void CMyToolBar::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	MessageBox("OK, I got the double-click. Now what?");
}

// Static class member holds window class name
// (NULL if not registered yet).
// 
LPCSTR CMyToolBar::s_winClassName = NULL;

//////////////////
// Override this function to register the different class
// Required for pre-4.0 MFC ONLY! MFC version 4.0 and later uses 
// real Win32 toolbar control, which accepts double-clicks, 
// so there's no need to register a new class.
//
#if _MFC_VER < 0x0400

BOOL CMyToolBar::PreCreateWindow(CREATESTRUCT& cs)
{
	if (!CToolBar::PreCreateWindow(cs))
		return FALSE;

	if (s_winClassName==NULL) {	

		// One-time initialization: register new class with same info, 
		// but different name and style.
		//
		WNDCLASS wc;
		HINSTANCE hInst = AfxGetInstanceHandle();

		// Get data for AfxControlBar
		if (!::GetClassInfo(hInst, _afxWndControlBar, &wc)) {
			TRACE("Can't find window class \"%s\"\n", _afxWndControlBar);
			return FALSE;
		}

		// Change name and style to allow double-clicks
		wc.lpszClassName = "MyControlBar";
		wc.style |= CS_DBLCLKS;
		if (!AfxRegisterClass(&wc)) {
			TRACE("Unable to register window class MyControlBar\n");
			return FALSE;
		}
		s_winClassName = wc.lpszClassName;
	}
	cs.lpszClass = s_winClassName;
	return TRUE;
}

#endif // _MFC_VER

