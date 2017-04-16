// mainfrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "DDEServ.h"
#include "ddesvdoc.h"
#include "ddesvvw.h"
#include "datadlg.h"
#include "mainfrm.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_EDIT_DATA, OnEditData)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// arrays of IDs used to initialize control bars
	
// toolbar buttons - IDs are command buttons
static UINT BASED_CODE buttons[] =
{
	// same order as in the bitmap 'toolbar.bmp'
	ID_FILE_NEW,
	ID_FILE_OPEN,
	ID_FILE_SAVE,
		ID_SEPARATOR,
	ID_EDIT_CUT,
	ID_EDIT_COPY,
	ID_EDIT_PASTE,
		ID_SEPARATOR,
	ID_FILE_PRINT,
	ID_APP_ABOUT,
};

static UINT BASED_CODE indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.Create(this) ||
		!m_wndToolBar.LoadBitmap(IDR_MAINFRAME) ||
		!m_wndToolBar.SetButtons(buttons,
		  sizeof(buttons)/sizeof(UINT)))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	// TODO: Remove this if you don't want tool tips
	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY);

    //
    // Start the DDE server
    //

    if (!m_Server.Create(AfxGetAppName())) {
        char buf[128];
        sprintf(buf,
                "Service failed to start. Error: %d",
                m_Server.GetLastError());
        AfxMessageBox(buf);
    }

	return 0;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

void CMainFrame::PrintLine(const char* pszFormat, ...)
{
    char buf[1024];
	va_list arglist;
	va_start(arglist, pszFormat);
    vsprintf(buf, pszFormat, arglist);
	va_end(arglist);

    CDocument* pDoc = GetActiveDocument();
    if (!pDoc) return;

    POSITION pos = pDoc->GetFirstViewPosition();
    if (!pos) return;

    CDDEServView* pView = (CDDEServView*) pDoc->GetNextView(pos);
    if (!pView) return;
    ASSERT(pView->IsKindOf(RUNTIME_CLASS(CDDEServView)));
    pView->PrintLine(buf);
}



BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs) 
{
	// Fix the window size
    cs.cx = ::GetSystemMetrics(SM_CXSCREEN) / 3;
    cs.cy = ::GetSystemMetrics(SM_CYSCREEN) / 2;
	
	return CFrameWnd::PreCreateWindow(cs);
}

void CMainFrame::OnEditData() 
{
	CDataDlg dlg;
	dlg.m_str1 = m_Server.m_StringItem1;	
	dlg.m_str2 = m_Server.m_StringItem2;
	if (dlg.DoModal() != IDOK) return;
	m_Server.m_StringItem1.SetData(dlg.m_str1);	
	m_Server.m_StringItem2.SetData(dlg.m_str2);	
}

void CMainFrame::OnDestroy() 
{
	CFrameWnd::OnDestroy();
	
	m_Server.Shutdown();	
}
