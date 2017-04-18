// NTServCpl.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "NTServCpl.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNTServCplApp

BEGIN_MESSAGE_MAP(CNTServCplApp, CWinApp)
	//{{AFX_MSG_MAP(CNTServCplApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNTServCplApp construction

CNTServCplApp::CNTServCplApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CNTServCplApp object

CNTServCplApp theApp;
