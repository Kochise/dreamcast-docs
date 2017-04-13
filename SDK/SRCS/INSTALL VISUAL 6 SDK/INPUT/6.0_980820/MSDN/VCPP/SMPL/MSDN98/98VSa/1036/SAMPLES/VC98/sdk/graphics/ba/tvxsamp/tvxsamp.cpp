//---------------------------------------------------------------------------------
// TVXSampDlg.cpp : TV Viewer sample application
//---------------------------------------------------------------------------------
// Copyright (C) 1997 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Broadcast Architecture Programmer's Reference.
// For more information about writing applications that interact
// with TV Viewer, see `` Creating TV Viewer Controls ``
// in the Broadcast Architecture Programmer's Reference.
//
//

#include "stdafx.h"
#include "TVXSamp.h"
#include "TVXSampDlg.h"
#include "Tvdisp.h"
#include <initguid.h>

DEFINE_GUID(IID_ITVViewer,0x3F8A2EA1L,0xC171,0x11CF,0x86,0x8C,0x00,0x80,0x5F,0x2C,0x11,0xCE);
DEFINE_GUID(IID_ITVDisp, 0x3F8A2EA1L, 0xC171,0x11cf,0x86,0x8C,0x00,0x80,0x5F,0x2C,0x11,0xCE);
DEFINE_GUID(CLSID_TVViewer,0x5543DD10L,0xB41D,0x11CF,0x86,0x82,0x00,0x80,0x5F,0x2C,0x11,0xCE);

extern ITVViewer *TVX;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTVXSampApp

BEGIN_MESSAGE_MAP(CTVXSampApp, CWinApp)
	//{{AFX_MSG_MAP(CTVXSampApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTVXSampApp construction

CTVXSampApp::CTVXSampApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CTVXSampApp object

CTVXSampApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CTVXSampApp initialization

BOOL CTVXSampApp::InitInstance()
{
	// Initialize OLE libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	//--------------< code that gets a reference to TV Viewer >-------------
//---------------------------------------------------------------------------------
	/* 
	The following code gets a reference to TV Viewer which
	TVXSamp uses to call the ITVViewer methods.
	This is implemented during TVXSamp's initialization 
	to ensure that it connects to TV Viewer before 
	calling the ITVViewer methods.

	TV Viewer must be running or else the following code will fail.
	*/
	HRESULT hr = 0;
	IUnknown *punk;
	IDispatch *dispatch;

	hr = GetActiveObject(CLSID_TVViewer,NULL,&punk);
	if (SUCCEEDED(hr))
	{
		hr=punk->QueryInterface(IID_IDispatch,(void**) &dispatch);
		punk->Release();
		if (SUCCEEDED(hr))
		{
			TVX=new ITVViewer(dispatch);
		}
	}


	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

	// Parse the command line to see if launched as OLE server
	if (RunEmbedded() || RunAutomated())
	{
		// Register all OLE server (factories) as running.  This enables the
		//  OLE libraries to create objects from other applications.
		COleTemplateServer::RegisterAll();
	}
	else
	{
		// When a server application is launched stand-alone, it is a good idea
		//  to update the system registry in case it has been damaged.
		COleObjectFactory::UpdateRegistryAll();
	}

	CTVXSampDlg dlg;
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
