/////////////////////////////////////////////////////////////////////////////
// MainFrm.cpp : implementation of the CMainFrame class
//
// This is a part of the Webster HTTP Server application
// for Microsoft Systems Journal
//

// enable this for using the WM_IDLEUPDATECMDUI for updateing the icon
#define	USE_IDLEUPDATECMDUI

#include "stdafx.h"
#include "afxpriv.h"	// WM_IDLEUPDATECMDUI
#include "Webster.h"

#include "MainFrm.h"
#include "WebDoc.h"
#include <mmsystem.h>	// PlaySound()

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(IDM_PROPERTIES, OnProperties)
	ON_COMMAND(IDM_UNHIDE, OnUnHide)
	ON_WM_TIMER()
	ON_MESSAGE(WM_KILL_SOCKET, OnKillSocket)
	ON_MESSAGE(WM_NEW_CLIENT, OnNewClient)
	ON_MESSAGE(WM_NEW_LOGFILE, OnNewLogfile)
	ON_MESSAGE(WM_MY_NOTIFY, OnMyNotify)
	ON_WM_CLOSE()
	ON_WM_DESTROY()
	ON_MESSAGE(WM_IDLEUPDATECMDUI, OnIdleUpdateCmdUI)
	//}}AFX_MSG_MAP
	// Global help commands
	ON_COMMAND(ID_HELP_FINDER, CFrameWnd::OnHelpFinder)
	ON_COMMAND(ID_HELP, CFrameWnd::OnHelp)
	ON_COMMAND(ID_CONTEXT_HELP, CFrameWnd::OnContextHelp)
	ON_COMMAND(ID_DEFAULT_HELP, CFrameWnd::OnHelpFinder)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// identifiers for tray icons
static const int	ID_ICON_MAIN	= 0 ;
static const int	ID_ICON_IDLE	= 1 ;
static const int	ID_ICON_ACTIVE	= 2 ;


/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	m_bWin95 = ( GetVersion() & 0xff ) >= 4 ;
	m_bHidden = m_bWin95 ;	// if (b_Win95) m_bHidden is TRUE	
	m_pTray = NULL ;
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	if (!m_wndToolBar.Create(this) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
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
	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	// load icon onto taskbar tray
	m_pTray = new CTrayNot ( this, WM_MY_NOTIFY,
									 "Webster", theApp.m_pIconList ) ;
	m_pTray->SetState ( ID_ICON_IDLE ) ;

	// create a sanity timer
	SetTimer ( IDT_SANITY_TIME, m_nSanityTime*1000, NULL ) ;
	return 0;
}

// create the view's splitter window
BOOL CMainFrame::OnCreateClient( LPCREATESTRUCT /*lpcs*/,
	CCreateContext* pContext)
{
	return m_wndSplitter.Create ( this,
											2, 1,		// allow 2 horizontal panes
											CSize( 10, 10 ),
											pContext ) ;
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
// Helper for handling Windows 95 taskbar tray icon status indicator

void CMainFrame::NotifyHandler ( BOOL bShowActive )
{
	if ( theApp.m_bEnableIcon )
		m_pTray->SetState ( bShowActive ? ID_ICON_ACTIVE : ID_ICON_IDLE ) ;
	else
		m_pTray->SetState ( ID_ICON_MAIN ) ;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

// This is the handler for the Properties dialog box
void CMainFrame::OnProperties()
{
	CWebProps dlgProps ;

	dlgProps.GetProps() ;
	if ( dlgProps.DoModal() == IDOK )
		dlgProps.SetProps() ;
}

// This is the handler for the Open item on the tray icon's popup menu
// This restores the window if it has been hidden.
// Note that I use SW_RESTORE instead of SW_SHOW in the tray notification
//    because we may have minimized, as well as hidden, our window.
void CMainFrame::OnUnHide()
{
	ShowWindow ( SW_RESTORE ) ;
	m_bHidden = FALSE ;
}

// This is the WM_TIMER message handler for the periodic sanity check.
void CMainFrame::OnTimer(UINT nIDEvent) 
{
	if ( theApp.m_State == CWebApp::ST_NULL )
		return ;	// not running yet!

	if ( nIDEvent == IDT_SANITY_TIME )	// periodic sanity check
	{
		// If the timer setting has changed,
		// then reset the timer with the new value
		if ( m_nSanityTime != theApp.m_nSanityTime )
		{
			m_nSanityTime = theApp.m_nSanityTime ;
			KillTimer ( IDT_SANITY_TIME ) ;
			SetTimer( IDT_SANITY_TIME, m_nSanityTime*1000, NULL ) ;
		}
		// Have the document check for aged connections
		CWebDoc* pDoc = (CWebDoc*)GetActiveDocument() ;                 
		pDoc->CheckIdleConnects() ;
		// As long as we're at it, update the tray icon
		NotifyHandler ( pDoc->ActiveClients() ) ;
	}
	CFrameWnd::OnTimer(nIDEvent);
}

// This handler is executed when a client object has completed its
// service.
// The document handles the operation of destroying the socket, but since
// the document can't deal with WM_ messages, we have to initiate the
// action from the main frame.
// We also update the icon while we're at it.
LONG CMainFrame::OnKillSocket ( WPARAM wParam, LPARAM lParam ) 
{
	CWebDoc* pDoc = (CWebDoc*)GetActiveDocument() ;
	pDoc->DbgMessage ( "   MainFrame::OnMsgKillSocket() ->" ) ;
	pDoc->KillSocket ( (CClient*)lParam ) ;
	NotifyHandler ( pDoc->ActiveClients() ) ;	// update the tray icon
	return ( 0 ) ;
}

// This handler is executed when the document creates a new client object.
// Its only purpose is to set the notification mechanisms to indicate a
// new client connection.
LONG CMainFrame::OnNewClient ( WPARAM wParam, LPARAM lParam ) 
{
	NotifyHandler ( TRUE ) ;	// update the tray icon
	if ( theApp.m_bEnableSound )	// do the audible notification
	{
		// if we don't support sound, use the system beeper
		if ( ! ::PlaySound ( "SystemDefault", NULL, SND_ALIAS | SND_ASYNC ) )
			MessageBeep ( 0xffffffff ) ;
	}
	return ( 0 ) ;
}

// This handler is executed when a new log file is needed. Usually only
// triggered when the log file name is changed in the configuration
// properties dialog.
LONG CMainFrame::OnNewLogfile ( WPARAM wParam, LPARAM lParam ) 
{
	CWebDoc* pDoc = (CWebDoc*)GetActiveDocument() ;                 
	pDoc->OpenLogfile() ;
	return ( 0 ) ;
}

// This is the system tray notification handler.
// On a right-button click, it creates a popup menu
// On a left-button double click, it executes the default popup menu
// item which unhides the application.
LONG CMainFrame::OnMyNotify ( WPARAM wParam, LPARAM lParam ) 
{
	switch ( lParam )
	{
		case WM_RBUTTONDOWN:
		{
			CMenu menu ;
			VERIFY(menu.LoadMenu(IDR_POPUPMENU));
			CMenu* pPopup = menu.GetSubMenu ( 0 ) ;
			ASSERT(pPopup != NULL);
			POINT pt ;
			GetCursorPos ( &pt ) ;
			pPopup->TrackPopupMenu ( TPM_LEFTALIGN | TPM_RIGHTBUTTON,
											  pt.x, pt.y, AfxGetMainWnd() ) ;
			break ;
		}
		case WM_LBUTTONDBLCLK:
			if ( m_bHidden )	// only if we're not already visible
				OnUnHide() ;
			break ;
	}
	return ( 0 ) ;
}

// Override WM_CLOSE so that clicking on the Close Application button
// simply hides the window. To really close the application, the File/Exit
// item is selected which sets the m_bOkToClose flag and allows us to call
// OnClose().
void CMainFrame::OnClose() 
{
	if ( theApp.m_bOkToClose )
	{
		KillTimer ( IDT_SANITY_TIME ) ;
		if ( m_pTray )	// remove icon from taskbar tray
		{
			delete m_pTray ;
			m_pTray = NULL ;
		}
		CFrameWnd::OnClose() ;
	}
	else	// otherwise, just hide ourselves and stay alive
	{
		theApp.HideApplication() ;
		m_bHidden = TRUE ;
	}
}

// Make sure we've removed the icon from the taskbar
void CMainFrame::OnDestroy() 
{
	CFrameWnd::OnDestroy();
	if ( m_pTray )	// remove icon from taskbar tray
	{
		delete m_pTray ;
		m_pTray = NULL ;
	}
}

// This is executed whenever the message queue is empty.
// See Paul DiLascia's C/C++ column in MSJ Oct. 1994.
LRESULT CMainFrame::OnIdleUpdateCmdUI ( WPARAM wParam, LPARAM )
{
	// update the tray icon
	NotifyHandler ( ((CWebDoc*)GetActiveDocument())->ActiveClients() ) ;
	return 0L;
}
