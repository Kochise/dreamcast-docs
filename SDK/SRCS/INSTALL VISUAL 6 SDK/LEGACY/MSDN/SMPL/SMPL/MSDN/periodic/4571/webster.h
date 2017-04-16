/////////////////////////////////////////////////////////////////////////////
// Webster.h : main header file for the WEBSTER application
//
// This is a part of the Webster HTTP Server application
// for Microsoft Systems Journal
//
#include "resource.h"       // main symbols

// our own user-defined windows messages for inter-class notifications
#define	WM_NEW_CLIENT			WM_USER
#define	WM_KILL_SOCKET			WM_USER+1
#define	WM_MY_NOTIFY			WM_USER+2
#define	WM_NEW_LOGFILE			WM_USER+3

// timer ID's
#define	IDT_SANITY_TIME		1	// periodic check for idle connections

#include "Props.h"	// CWebProps

/////////////////////////////////////////////////////////////////////////////
// CWebApp:
// See Webster.cpp for the implementation of this class
//

class CWebApp : public CWinApp
{
public:
	CWebApp();

	BOOL	m_bOkToClose ;	// used to override WM_CLOSE

// Attributes
	enum SERVER_STATE
	{
		ST_NULL,		// not initialized yet
		ST_WAITING,		// waiting for request
		ST_SENDING		// send in progress
	} m_State ;

	//////////// Server Properties ///////////////

	// Server properties
	UINT		m_wwwPort ;			// well-known WWW port number
	UINT		m_nMaxConnects ;	// max number of connections we'll allow
	UINT		m_nTimeOut ;		// idle-client disconnect limit
	UINT		m_nSanityTime ;		// watchdog timer period

	// HTML properties
	CString		m_HTMLPath ;		// root path for HTML docs
	CString		m_HTMLDefault ;		// FNA for Default msg
	CString		m_HTMLBogus ;		// FNA for Bogus msg
	CString		m_HTMLTag ;			// FNA for Tag msg
	enum TAG_TYPE
	{
		TAG_NONE = 0,
		TAG_AUTO,
		TAG_FILE
	} m_nTagType ;

	// Logging properties
	BOOL		m_bLogEnable ;
	CString		m_LogPath ;

	// Status properties
	BOOL		m_bShowStatus ;
	BOOL		m_bResolveClientname ;
	BOOL		m_bDebugOutput ;

	// Alert properties
	BOOL		m_bEnableSound ;
	BOOL		m_bEnableIcon ;
	CString	m_IdlePath ;
	CString	m_ActivePath ;
	HICON		m_pIconList[3] ;	// hMain, hIdle, hActive

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWebApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
public:
	void LoadProps ( void ) ;
	void SaveProps ( void ) ;
	LPSTR MapErrMsg ( DWORD dwErr ) ;

	//{{AFX_MSG(CWebApp)
	afx_msg void OnAppAbout();
	afx_msg void OnAppExit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

// we reference this guy a lot...
extern CWebApp theApp ;

/////////////////////////////////////////////////////////////////////////////
