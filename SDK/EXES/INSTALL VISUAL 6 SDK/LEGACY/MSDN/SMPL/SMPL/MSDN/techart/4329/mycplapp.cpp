// MyCplApp.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "MyCplApp.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyCplAppApp

BEGIN_MESSAGE_MAP(CMyCplAppApp, CWinApp)
	//{{AFX_MSG_MAP(CMyCplAppApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyCplAppApp construction

CMyCplAppApp::CMyCplAppApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CMyCplAppApp object

CMyCplAppApp theApp;
