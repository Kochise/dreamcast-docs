// Wizard97.cpp : Defines the class behaviors for the application.
//
// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) 1992-1998 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.

#include "stdafx.h"
#include "Wizard97.h"
#include "WizSheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWizard97App

BEGIN_MESSAGE_MAP(CWizard97App, CWinApp)
	//{{AFX_MSG_MAP(CWizard97App)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWizard97App construction

CWizard97App::CWizard97App()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CWizard97App object

CWizard97App theApp;

static BOOL Is256ColorSupported()
{
	BOOL bRetval = FALSE;

	// return TRUE if screen deivce supports 256 colors or better

	HDC hdc = GetDC(NULL);
	if (hdc != NULL)
	{
		if(GetDeviceCaps(hdc, BITSPIXEL) >= 8)
			bRetval = TRUE;
		ReleaseDC(NULL, hdc);
	}

	return bRetval;
}


/////////////////////////////////////////////////////////////////////////////
// CWizard97App initialization

BOOL CWizard97App::InitInstance()
{
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();         // Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();   // Call this when linking to MFC statically
#endif

	CBitmap bmpWatermark;
	CBitmap bmpHeader;

	if (Is256ColorSupported())
	{
		VERIFY(bmpWatermark.LoadBitmap(IDB_WATERMARK256));
		VERIFY(bmpHeader.LoadBitmap(IDB_BANNER256));
	}
	else
	{
		VERIFY(bmpWatermark.LoadBitmap(IDB_WATERMARK16));
		VERIFY(bmpHeader.LoadBitmap(IDB_BANNER16));
	}

	CWizard97Sheet dlg(IDS_SAMPLEWIZARD, NULL, 0, bmpWatermark, NULL, bmpHeader);
	dlg.m_psh.hInstance = ::GetModuleHandle(NULL);
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
