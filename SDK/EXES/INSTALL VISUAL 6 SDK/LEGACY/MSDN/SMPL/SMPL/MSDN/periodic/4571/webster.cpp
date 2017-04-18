/////////////////////////////////////////////////////////////////////////////
// Webster.cpp : Defines the class behaviors for the application.
//
// This is a part of the Webster HTTP Server application
// for Microsoft Systems Journal
//

#include "stdafx.h"
#include "Webster.h"

#include "MainFrm.h"
#include "WebDoc.h"
#include "WebView.h"
#include "Splash.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWebApp

BEGIN_MESSAGE_MAP(CWebApp, CWinApp)
	//{{AFX_MSG_MAP(CWebApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_APP_EXIT, OnAppExit)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWebApp construction

CWebApp::CWebApp()
{
	m_bOkToClose = TRUE ;	// for overriding WM_CLOSE
	m_State = ST_NULL ;	// not running yet
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CWebApp object

CWebApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CWebApp initialization

BOOL CWebApp::InitInstance()
{
	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// use the registry - do this before LoadStdProfileSettings()
 	SetRegistryKey ( IDS_REG_STRING ) ;
#if _MFC_VER < 0x0400
	HKEY hKey = GetAppRegistryKey() ;	// this creates the key initally
	RegCloseKey ( hKey ) ;
#endif
	LoadStdProfileSettings();  // Load standard INI file options (including MRU)
	LoadProps() ;				// Load all other application-specific properties

	// load our application icons
	m_pIconList[0] = LoadIcon ( MAKEINTRESOURCE(IDR_MAINFRAME) ) ;
	m_pIconList[1] = LoadIcon ( MAKEINTRESOURCE(IDI_IDLE) ) ;
	m_pIconList[2] = LoadIcon ( MAKEINTRESOURCE(IDI_CONNECT) ) ;

	// If we're running on Windows 95, we want to be hidden initially.
	// We know we're running from the notification icon in the system tray
	if ( ( GetVersion() & 0xff ) >= 4 )
	{
		m_bOkToClose = FALSE ;	// for overriding WM_CLOSE
		m_nCmdShow = SW_HIDE ;
	}

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CWebDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CWebView));
	AddDocTemplate(pDocTemplate);

	// Display the operating tip if running under Windows 95
	if ( ( (GetVersion() & 0xff) >= 4 ) &&
			GetProfileInt("","StartTip",0) == 0 )
	{
		CSplash dlg ;
		dlg.m_bNoNag = FALSE ;
		dlg.DoModal() ;
		WriteProfileInt ( "", "StartTip", dlg.m_bNoNag ) ;
	}

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CWebApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CWebApp global functions

void CWebApp::LoadProps()
{
	m_wwwPort		= GetProfileInt ( "Server", "PortNumber", 80 ) ;
	m_nMaxConnects	= GetProfileInt ( "Server", "MaxClients", 10 ) ;
	m_nTimeOut		= GetProfileInt ( "Server", "Timeout",    600 ) ;
	m_nSanityTime	= GetProfileInt ( "Server", "Sanity",     60 ) ;

	m_HTMLPath		= GetProfileString ( "HTML", "Dir",     ".\\html" ) ;
	m_HTMLDefault	= GetProfileString ( "HTML", "Default", "default.htm" ) ;
	m_HTMLBogus		= GetProfileString ( "HTML", "Bogus",   "bogus.htm" ) ;
	m_HTMLTag		= GetProfileString ( "HTML", "Tag",     "tag.htm" ) ;
	m_nTagType		= (TAG_TYPE)GetProfileInt ( "HTML", "TagType", TAG_AUTO ) ;

	m_bLogEnable	= GetProfileInt    ( "Logging", "Enable",  1 ) ;
	m_LogPath		= GetProfileString ( "Logging", "LogFile", ".\\webster.log" ) ;

	m_bShowStatus			= GetProfileInt ( "Status", "Enable",     1 ) ;
	m_bResolveClientname	= GetProfileInt ( "Status", "ClientName", 0 ) ;
	m_bDebugOutput			= GetProfileInt ( "Status", "Debug",      0 ) ;

	m_bEnableSound	= GetProfileInt ( "Alert", "SoundNotify", 1 ) ;
	m_bEnableIcon	= GetProfileInt ( "Alert", "IconNotify", 1 ) ;
}

void CWebApp::SaveProps()
{
	WriteProfileInt ( "Server", "PortNumber", m_wwwPort ) ;
	WriteProfileInt ( "Server", "MaxClients", m_nMaxConnects ) ;
	WriteProfileInt ( "Server", "Timeout",    m_nTimeOut ) ;
	WriteProfileInt ( "Server", "Sanity",     m_nSanityTime ) ;

	WriteProfileString ( "HTML", "Dir",     m_HTMLPath ) ;
	WriteProfileString ( "HTML", "Default", m_HTMLDefault ) ;
	WriteProfileString ( "HTML", "Bogus",   m_HTMLBogus ) ;
	WriteProfileString ( "HTML", "Tag",     m_HTMLTag ) ;
	WriteProfileInt    ( "HTML", "TagType", m_nTagType ) ;

	WriteProfileInt    ( "Logging", "Enable",  m_bLogEnable ) ;
	WriteProfileString ( "Logging", "LogFile", m_LogPath ) ;

	WriteProfileInt ( "Status", "Status",     m_bShowStatus ) ;
	WriteProfileInt ( "Status", "ClientName", m_bResolveClientname ) ;
	WriteProfileInt ( "Status", "Debug",      m_bDebugOutput ) ;

	WriteProfileInt ( "Alert", "SoundNotify",	m_bEnableSound ) ;
	WriteProfileInt ( "Alert", "IconNotify",	m_bEnableIcon ) ;
}

// This is a table for translating WinSock error codes into text messages.
// The FormatMessage() API did not provide WinSock error code translation at
// the time of this writing. For a more user-friendly implementation, the
// cryptic WSAE codes can be translated into more infomative descriptions.
static struct _tagWSATable
{
	DWORD		dwCode ;
	LPCTSTR	szMsg ;
} _WSATable[] = {
	// Windows Sockets definitions of regular Microsoft C error constants
	{ WSAEINTR          , "INTR" },
	{ WSAEBADF          , "BADF" },
	{ WSAEACCES         , "ACCES" },
	{ WSAEFAULT         , "FAULT" },
	{ WSAEINVAL         , "INVAL" },
	{ WSAEMFILE         , "MFILE" },
	// Windows Sockets definitions of regular Berkeley error constants
	{ WSAEWOULDBLOCK    , "WOULDBLOCK" },
	{ WSAEINPROGRESS    , "INPROGRESS" },
	{ WSAEALREADY       , "ALREADY" },
	{ WSAENOTSOCK       , "NOTSOCK" },
	{ WSAEDESTADDRREQ   , "DESTADDRREQ" },
	{ WSAEMSGSIZE       , "MSGSIZE" },
	{ WSAEPROTOTYPE     , "PROTOTYPE" },
	{ WSAENOPROTOOPT    , "PROTOOPT" },
	{ WSAEPROTONOSUPPORT, "PROTONOSUPPORT" },
	{ WSAESOCKTNOSUPPORT, "SOCKTNOSUPPORT" },
	{ WSAEOPNOTSUPP     , "OPNOTSUPP" },
	{ WSAEPFNOSUPPORT   , "PFNOSUPPORT" },
	{ WSAEAFNOSUPPORT   , "AFNOSUPPORT" },
	{ WSAEADDRINUSE     , "ADDRINUSE" },
	{ WSAEADDRNOTAVAIL  , "ADDRNOTAVAIL" },
	{ WSAENETDOWN       , "NETDOWN" },
	{ WSAENETUNREACH    , "NETUNREACH" },
	{ WSAENETRESET      , "NETRESET" },
	{ WSAECONNABORTED   , "CONNABORTED" },
	{ WSAECONNRESET     , "CONNRESET" },
	{ WSAENOBUFS        , "NOBUFS" },
	{ WSAEISCONN        , "ISCONN" },
	{ WSAENOTCONN       , "NOTCONN" },
	{ WSAESHUTDOWN      , "SHUTDOWN" },
	{ WSAETOOMANYREFS   , "TOOMANYREFS" },
	{ WSAETIMEDOUT      , "TIMEDOUT" },
	{ WSAECONNREFUSED   , "CONNREFUSED" },
	{ WSAELOOP          , "LOOP" },
	{ WSAENAMETOOLONG   , "NAMETOOLONG" },
	{ WSAEHOSTDOWN      , "HOSTDOWN" },
	{ WSAEHOSTUNREACH   , "HOSTUNREACH" },
	{ WSAENOTEMPTY      , "NOTEMPTY" },
	{ WSAEPROCLIM       , "WSAPROCLIM" },
	{ WSAEUSERS         , "USERS" },
	{ WSAEDQUOT         , "DQUOT" },
	{ WSAESTALE         , "STALE" },
	{ WSAEREMOTE        , "REMOTE" },
	{ WSAEDISCON        , "DISCON" }
} ;
static const int _WSATableLen = sizeof(_WSATable)/sizeof(struct _tagWSATable) ;

// This routine returns a string formatted from the system error message
// database. As noted, FormatMessage() does not yet handle WinSock errors,
// so we must handle them ourselves.
LPSTR CWebApp::MapErrMsg ( DWORD dwErr )
{
	// __declspec (thread) necessary if you will use multiple threads
	__declspec (thread) static char szMsgBuf[128] ;

	if ( dwErr > WSABASEERR )	// check for WinSock error
	{
		// default message in case table lookup fails
		wsprintf ( szMsgBuf, "WinSock Error: %ld", dwErr ) ;
		for ( int i = 0 ; i < _WSATableLen ; i++ )
		{
			if ( dwErr == _WSATable[i].dwCode )
			{
				wsprintf ( szMsgBuf, "WinSock Error: WSA%s", _WSATable[i].szMsg ) ;
				break ;
			}
		}
	}
	else	// otherwise, default system error
	{
		// default message in case FormatMessage fails
		wsprintf ( szMsgBuf, "Error %ld", dwErr ) ;
		::FormatMessage ( FORMAT_MESSAGE_FROM_SYSTEM,
						  NULL,
						  dwErr,
						  LANG_NEUTRAL,
						  szMsgBuf,
						  sizeof(szMsgBuf),
						  NULL ) ;
	}
	return ( szMsgBuf ) ;
}

/////////////////////////////////////////////////////////////////////////////
// CWebApp commands

void CWebApp::OnAppExit() 
{
	m_bOkToClose = TRUE ;
	CWinApp::OnAppExit() ;
}
