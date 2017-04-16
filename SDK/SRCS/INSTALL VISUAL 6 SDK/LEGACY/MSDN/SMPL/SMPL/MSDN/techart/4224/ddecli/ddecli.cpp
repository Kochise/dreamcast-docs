// DDECli.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "DDECli.h"
#include "myclient.h"
#include "myconv.h"
#include "DDECldlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDDEClientApp

BEGIN_MESSAGE_MAP(CDDEClientApp, CWinApp)
	//{{AFX_MSG_MAP(CDDEClientApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDDEClientApp construction

CDDEClientApp::CDDEClientApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CDDEClientApp object

CDDEClientApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CDDEClientApp initialization

BOOL CDDEClientApp::InitInstance()
{
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

	Enable3dControls();
	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	CDDECliDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

void CDDEClientApp::Status(const char* pszFormat, ...)
{
    char buf[1024];
	va_list arglist;
	va_start(arglist, pszFormat);
    vsprintf(buf, pszFormat, arglist);
	va_end(arglist);

    CDDECliDlg* pFrame = (CDDECliDlg*) m_pMainWnd;
    if (!pFrame) return;
    pFrame->Status(buf);
}
