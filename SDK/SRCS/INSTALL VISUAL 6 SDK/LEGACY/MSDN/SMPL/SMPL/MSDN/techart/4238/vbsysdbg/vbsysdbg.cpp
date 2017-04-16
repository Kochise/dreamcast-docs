// VBSysDbg.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "VBSysDbg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVBSysDbgApp

BEGIN_MESSAGE_MAP(CVBSysDbgApp, CWinApp)
	//{{AFX_MSG_MAP(CVBSysDbgApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVBSysDbgApp construction

CVBSysDbgApp::CVBSysDbgApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CVBSysDbgApp object

CVBSysDbgApp theApp;

BOOL CVBSysDbgApp::InitInstance() 
{
	if (!CWinApp::InitInstance()) return FALSE;

    // Create the debug output window
    dprintf("VBSysDbg.Dll loaded");
    return TRUE;
}

int CVBSysDbgApp::ExitInstance() 
{
    dprintf("VBSysDbg.Dll exiting");
    
    // Save the position of the debug output window
    ExitDebug();
	
	return CWinApp::ExitInstance();
}
