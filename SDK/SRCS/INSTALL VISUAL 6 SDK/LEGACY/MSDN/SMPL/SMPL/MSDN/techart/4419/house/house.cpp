// House.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "House.h"

#include "mainfrm.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHouseApp

BEGIN_MESSAGE_MAP(CHouseApp, CWinApp)
	//{{AFX_MSG_MAP(CHouseApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHouseApp construction

CHouseApp::CHouseApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CHouseApp object

CHouseApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CHouseApp initialization

BOOL CHouseApp::InitInstance()
{
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

	Enable3dControls();
	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

    // Make the debug window visible
    dprintf("COM object demo");

    // 3:Register our class factories
    COleObjectFactory::RegisterAll();

    // Create the main window
    CMainFrame* pFrame = new CMainFrame;
    ASSERT(pFrame);
    CString strClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS,
                                           LoadCursor(IDR_MAINFRAME),
                                           0,
                                           LoadIcon(IDR_MAINFRAME));

    pFrame->Create(strClass,
                   AfxGetAppName(),
                   WS_OVERLAPPED|WS_CAPTION|WS_SYSMENU|WS_BORDER
                    |WS_MINIMIZEBOX|WS_VISIBLE,
                   CFrameWnd::rectDefault,
                   NULL, // pParent
                   MAKEINTRESOURCE(IDR_MAINFRAME));
    m_pMainWnd = pFrame;
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
void CHouseApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CHouseApp commands

int CHouseApp::ExitInstance() 
{
	// 3:Revoke all class factories
    COleObjectFactory::RevokeAll();

	ExitDebug(); // close debug support	
	return CWinApp::ExitInstance();
}
