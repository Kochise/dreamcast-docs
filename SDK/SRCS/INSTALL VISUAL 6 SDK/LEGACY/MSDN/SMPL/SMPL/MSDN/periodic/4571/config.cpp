/////////////////////////////////////////////////////////////////////////////
// Config.cpp : implementation file
//
// This is a part of the Webster HTTP Server application
// for Microsoft Systems Journal
//

#include "stdafx.h"
#include "resource.h"
#include "Config.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CServer, CPropertyPage)
IMPLEMENT_DYNCREATE(CHTML, CPropertyPage)
IMPLEMENT_DYNCREATE(CLogging, CPropertyPage)
IMPLEMENT_DYNCREATE(CStatus, CPropertyPage)
IMPLEMENT_DYNCREATE(CAlert, CPropertyPage)


/////////////////////////////////////////////////////////////////////////////
// CServer property page

CServer::CServer() : CPropertyPage(CServer::IDD)
{
	//{{AFX_DATA_INIT(CServer)
	m_nPort = 0;
	m_nMaxConnects = 0;
	m_nSanityTime = 0;
	m_nTimeOut = 0;
	//}}AFX_DATA_INIT
}

CServer::~CServer()
{
}

void CServer::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CServer)
	DDX_Text(pDX, IDC_HTTP_PORT, m_nPort);
	DDX_Text(pDX, IDC_MAX_CONNECTS, m_nMaxConnects);
	DDX_Text(pDX, IDC_SANITY_TIME, m_nSanityTime);
	DDX_Text(pDX, IDC_TIMEOUT, m_nTimeOut);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CServer, CPropertyPage)
	//{{AFX_MSG_MAP(CServer)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CHTML property page

CHTML::CHTML() : CPropertyPage(CHTML::IDD)
{
	//{{AFX_DATA_INIT(CHTML)
	m_DefaultName = _T("");
	m_DefaultPath = _T("");
	m_nTagType = -1;
	m_TagFile = _T("");
	//}}AFX_DATA_INIT
}

CHTML::~CHTML()
{
}

void CHTML::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHTML)
	DDX_Text(pDX, IDC_HTML_DEFAULT, m_DefaultName);
	DDX_Text(pDX, IDC_HTML_PATH, m_DefaultPath);
	DDX_Radio(pDX, IDC_TAG_NONE, m_nTagType);
	DDX_Text(pDX, IDC_HTML_TAGFILE, m_TagFile);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CHTML, CPropertyPage)
	//{{AFX_MSG_MAP(CHTML)
	ON_BN_CLICKED(IDC_HTML_BROWSE, OnHtmlBrowse)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CLogging property page

CLogging::CLogging() : CPropertyPage(CLogging::IDD)
{
	//{{AFX_DATA_INIT(CLogging)
	m_bLogEnable = FALSE;
	m_LogPath = _T("");
	//}}AFX_DATA_INIT
}

CLogging::~CLogging()
{
}

void CLogging::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLogging)
	DDX_Check(pDX, IDC_LOG_ENABLE, m_bLogEnable);
	DDX_Text(pDX, IDC_LOG_PATH, m_LogPath);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLogging, CPropertyPage)
	//{{AFX_MSG_MAP(CLogging)
	ON_BN_CLICKED(IDC_LOG_BROWSE, OnLogBrowse)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CStatus property page

CStatus::CStatus() : CPropertyPage(CStatus::IDD)
{
	//{{AFX_DATA_INIT(CStatus)
	m_bStatusEnable = FALSE;
	m_bDebugEnable = FALSE;
	m_bHostName = FALSE;
	//}}AFX_DATA_INIT
}

CStatus::~CStatus()
{
}

void CStatus::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStatus)
	DDX_Check(pDX, IDC_STATUS_ENABLE, m_bStatusEnable);
	DDX_Check(pDX, IDC_DEBUG_ENABLE, m_bDebugEnable);
	DDX_Check(pDX, IDC_HOSTNAME_ENABLE, m_bHostName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStatus, CPropertyPage)
	//{{AFX_MSG_MAP(CStatus)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CAlert property page

CAlert::CAlert() : CPropertyPage(CAlert::IDD)
{
	//{{AFX_DATA_INIT(CAlert)
	m_bEnableSound = FALSE;
	m_bEnableIcon = FALSE;
	//}}AFX_DATA_INIT
}

CAlert::~CAlert()
{
}

void CAlert::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAlert)
	DDX_Check(pDX, IDC_ENABLE_SOUND, m_bEnableSound);
	DDX_Check(pDX, IDC_ENABLE_ICON, m_bEnableIcon);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAlert, CPropertyPage)
	//{{AFX_MSG_MAP(CAlert)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


void CHTML::OnHtmlBrowse() 
{
	// these are used for decomposing/recomposing file pathnames
	char	gcDrive[3],			// initial directory path
			gcDir[MAX_PATH],
			gcFname[MAX_PATH],
			gcExt[MAX_PATH] ;
	char	gcPath[MAX_PATH] ;	// recomposed direcory path

	// create basic file open dialog
	CFileDialog dlg ( TRUE,
					  "html",
					  m_DefaultPath,
					  OFN_HIDEREADONLY |
					  OFN_PATHMUSTEXIST |
					  OFN_FILEMUSTEXIST,
					  "HTML Files|*.htm*;|All Files|*.*||",
					  NULL ) ;
	// set the title
	dlg.m_ofn.lpstrTitle = "Default HTML File Select" ;
	// set the initial directory
	CString PathName ;
	CEdit *pEB_Path = (CEdit *)GetDlgItem ( IDC_HTML_PATH ) ;
	pEB_Path->GetWindowText ( PathName ) ;
	dlg.m_ofn.lpstrInitialDir = PathName ;
	// set the initial filename
	char fna[MAX_PATH] ;
	CEdit *pEB_Name = (CEdit *)GetDlgItem ( IDC_HTML_DEFAULT ) ;
	// get current filename from edit box
	pEB_Name->GetWindowText ( fna, MAX_PATH ) ;
	dlg.m_ofn.lpstrFile = fna ;
	if ( dlg.DoModal() == IDOK )	// get new filename
	{
		// get components of new filename
		m_DefaultPath = dlg.GetPathName() ;	// full filename
		_splitpath ( m_DefaultPath, gcDrive, gcDir, gcFname, gcExt ) ;

		// display path only in IDC_HTML_PATH
		_makepath ( gcPath, gcDrive, gcDir, NULL, NULL ) ;
		pEB_Path->SetWindowText ( gcPath ) ;

		// show filename only in IDC_HTML_DEFAULT
		m_DefaultName = dlg.GetFileTitle() ;
#if	_MFC_VER >= 0x0400
		// Prior to MFC 4.0, GetFileTitle() returned the base filename with
		// the extension. However, it now only returns the base filename.
		// The documentation still states: "GetFileTitle will return
		// "TEXT.DAT" for the file C:\FILES\TEXT.DAT.". This change in
		// behavior will no doubt be corrected, or the documentation changed
		// to match the behavior, in future releases. For the time being, my
		// workaround is to graft the extension back onto the base filename.
		m_DefaultName += gcExt ;
#endif
		// transfer back to edit box
		pEB_Name->SetWindowText ( m_DefaultName ) ;
	}
}

void CLogging::OnLogBrowse() 
{
	// these are used for decomposing/recomposing file pathnames
	char	gcDrive[3],			// initial directory path
			gcDir[MAX_PATH],
			gcFname[MAX_PATH],
			gcExt[MAX_PATH] ;
	char	gcPath[MAX_PATH] ;	// recomposed direcory path

	// create basic file open dialog
	CFileDialog dlg ( TRUE,
					  "log",
					  m_LogPath,
					  OFN_HIDEREADONLY,
					  "Log Files|*.log;|All Files|*.*||",
					  NULL ) ;
	// set the title
	dlg.m_ofn.lpstrTitle = "Log File Select" ;
	// set the initial directory
	CString PathName ;
	CEdit *pEB_Path = (CEdit *)GetDlgItem ( IDC_LOG_PATH ) ;
	pEB_Path->GetWindowText ( PathName ) ;
	_splitpath ( PathName, gcDrive, gcDir, gcFname, gcExt ) ;
	_makepath ( gcPath, gcDrive, gcDir, NULL, NULL ) ;
	dlg.m_ofn.lpstrInitialDir = gcPath ;
	// set the initial filename
	char fna[MAX_PATH] ;
	_makepath ( fna, NULL, NULL, gcFname, gcExt ) ;
	dlg.m_ofn.lpstrFile = fna ;
	if ( dlg.DoModal() == IDOK )	// get new filename
	{
		m_LogPath = dlg.GetPathName() ;	// full pathname
		pEB_Path->SetWindowText ( m_LogPath ) ;
	}
}

void CAlert::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CWnd* cWnd = GetDlgItem ( IDI_ICON_IDLE ) ;
	CPaintDC idleDC(cWnd) ;
	idleDC.DrawIcon ( 0, 0, m_hIdle ) ;

	cWnd = GetDlgItem ( IDI_ICON_ACTIVE ) ;
	CPaintDC activeDC(cWnd) ;
	activeDC.DrawIcon ( 0, 0, m_hActive ) ;
}
