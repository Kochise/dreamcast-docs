/******************************************************************************
Module name: ShellRun.cpp
Written by:  Jeffrey Richter
Purpose:     Shell Run CWinApp-derived class implementation file.
******************************************************************************/


#include "stdafx.h"
#include "ShellRun.h"
#include "AppBar.h"
#include "SRBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CShellRunApp


BEGIN_MESSAGE_MAP(CShellRunApp, CWinApp)
	//{{AFX_MSG_MAP(CShellRunApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CShellRunApp construction

CShellRunApp::CShellRunApp() {
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


/////////////////////////////////////////////////////////////////////////////
// The one and only CShellRunApp object

CShellRunApp theApp;


/////////////////////////////////////////////////////////////////////////////
// CShellRunApp initialization

BOOL CShellRunApp::InitInstance() {

   CSRBar ShellRunBar(NULL);
	m_pMainWnd = &ShellRunBar;
   ShellRunBar.DoModal();

   // Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}


//////////////////////////////// End of File //////////////////////////////////
