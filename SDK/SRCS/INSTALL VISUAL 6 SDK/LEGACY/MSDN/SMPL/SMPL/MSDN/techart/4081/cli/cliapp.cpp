// npseccli.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"

#include "common.h"

#include "cliapp.h"

#include "mainfrm.h"

#include "easyview.h"
#include "clidoc.h"
#include "cliview.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSecCliApp

BEGIN_MESSAGE_MAP(CSecCliApp, CWinApp)
	//{{AFX_MSG_MAP(CSecCliApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSecCliApp construction

CSecCliApp::CSecCliApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CSecCliApp object

CSecCliApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CSecCliApp initialization

BOOL CSecCliApp::InitInstance()
{
	// Standard initialization
	Enable3dControls();

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register document templates

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CSecCliDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CSecCliView));
	AddDocTemplate(pDocTemplate);

	// create a new (empty) document
	OnFileNew();

//	if (m_lpCmdLine[0] != '\0')
//	{
//	}


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
void CSecCliApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CSecCliApp commands

#include "browsedi.h"

int CSecCliApp::ExitInstance() 
{
	return CWinApp::ExitInstance();
}

