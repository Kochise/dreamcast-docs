// npscesrv.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"

#include "common.h"

#include "srvapp.h"

#include "mainfrm.h"
#include "srvdoc.h"
#include "easyview.h"
#include "srvview.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSecSrvApp

BEGIN_MESSAGE_MAP(CSecSrvApp, CWinApp)
	//{{AFX_MSG_MAP(CSecSrvApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	//}}AFX_MSG_MAP
	// Standard file based document commands
    ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSecSrvApp construction

CSecSrvApp::CSecSrvApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CSecSrvApp object

CSecSrvApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CSecSrvApp initialization

//#include "sec.h"

BOOL CSecSrvApp::InitInstance()
{ 
	// Standard initialization
	Enable3dControls();

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register document templates

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CSecSrvDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CSecSrvView));
	AddDocTemplate(pDocTemplate);

//    InitializeWellKnownSIDs();


	// create a new (empty) document
	OnFileNew();

	if (m_lpCmdLine[0] != '\0')
	{
	}
// we need this to be a "real" PostMessage and therefore get the "real" window
// handle because the posting will come from a different process...
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

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
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
void CSecSrvApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CSecSrvApp commands

int CSecSrvApp::ExitInstance() 
{
	return CWinApp::ExitInstance();
}

