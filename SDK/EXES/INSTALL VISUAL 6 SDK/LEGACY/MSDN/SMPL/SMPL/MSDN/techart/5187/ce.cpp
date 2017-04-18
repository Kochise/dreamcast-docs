//////////////////////////////////////////////////////////////////////////////
// CE.cpp	- Copyright (C) 1997 Microsoft Corporation						//
//          - All rights reserved.											//
// Date     - 12/11/97														//
// Purpose  - Main application module for CE Personal Information Manager	//
//////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CE.h"
#include "CEDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


BEGIN_MESSAGE_MAP(CCEApp, CWinApp)
END_MESSAGE_MAP()


CCEApp::CCEApp(LPCTSTR lpszAppName)
	: CWinApp(lpszAppName)
// Constructor
// Purpose		- Initialization
{
	// No initialization requid
}

CCEApp theApp(_T("CE"));

BOOL CCEApp::InitInstance()
{
	// Construct the main dialog window
	CCEDlg dlg;

	m_pMainWnd = &dlg;
	
	// Run it
	dlg.DoModal();
	
	return FALSE;
}
