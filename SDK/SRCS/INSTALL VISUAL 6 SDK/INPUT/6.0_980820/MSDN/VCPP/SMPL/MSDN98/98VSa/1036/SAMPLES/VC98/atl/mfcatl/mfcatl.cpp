// MfcAtl.cpp : Defines the class behaviors for the application.
//
// This is a part of the Active Template Library.
// Copyright (C) 1996-1998 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Active Template Library Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Active Template Library product.

#include "premfcat.h"
#include "MfcAtl.h"
#include "MfcAtlDl.h"
#include "interf.h"
#include "ObjTwo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// ATL Global Module only instance
CAtlGlobalModule _Module;

// ATL GLobal Object Map
BEGIN_OBJECT_MAP(ObjectMap)
	OBJECT_ENTRY(CLSID_ObjectTwo, CObjectTwo)
END_OBJECT_MAP()


/////////////////////////////////////////////////////////////////////////////
// CMfcAtlApp

BEGIN_MESSAGE_MAP(CMfcAtlApp, CWinApp)
	//{{AFX_MSG_MAP(CMfcAtlApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// The one and only CMfcAtlApp object

CMfcAtlApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CMfcAtlApp initialization

BOOL CMfcAtlApp::InitInstance()
{
	// Initialize OLE libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	// Initialize the ATL Module
	_Module.Init(ObjectMap,m_hInstance);

#ifdef _AFXDLL
	Enable3dControls();         // Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();   // Call this when linking to MFC statically
#endif

	// Update the System Registry
	COleObjectFactory::UpdateRegistryAll();         // MFC Classes
	VERIFY(SUCCEEDED(_Module.RegisterServer(TRUE)));// ATL Classes

	// create the modeless dialog, originally hidden
	CMfcAtlDlg* pDlg = new CMfcAtlDlg;
	if (!pDlg->Create(IDD_MFCATL_DIALOG))
	{
		delete pDlg;
		return FALSE;
	}
	m_pMainWnd = pDlg;

	// Register OLE Class Factories
	// MFC ones are for multiple as specified by the IMPLEMENT_OLECREATE() macro
	COleObjectFactory::RegisterAll();
	// ATL ones specifically register with REGCLS_MULTIPLEUSE
	VERIFY(SUCCEEDED(_Module.RegisterClassObjects(CLSCTX_LOCAL_SERVER, REGCLS_MULTIPLEUSE)));

	// Parse the command line to see if launched as OLE server
	if (RunEmbedded() || RunAutomated())
	{
		// Application was run with /Embedding or /Automation.  Don't show the
		//  main window in this case.
		return TRUE;
	}
	pDlg->ShowWindow(m_nCmdShow);
	return TRUE;
}

int CMfcAtlApp::ExitInstance()
{
	// MFC's class factories registration is automatically revoked by MFC itself
	_Module.RevokeClassObjects(); // Revoke class factories for ATL
	_Module.Term();               // clanup ATL GLobal Module
	return CWinApp::ExitInstance();
}
