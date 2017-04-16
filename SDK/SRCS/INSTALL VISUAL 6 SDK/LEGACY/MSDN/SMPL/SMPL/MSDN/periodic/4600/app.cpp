////////////////////////////////////////////////////////////////
// TRACEWIN Copyright 1995 Microsoft Systems Journal. 
// If this program works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
//
// Application object for TRACEWIN applet.
// 
#include "stdafx.h"
#include "app.h"
#include "mainfrm.h"
#include "winplace.h"

CApp NEAR theApp;

BEGIN_MESSAGE_MAP(CApp, CWinApp)
	//{{AFX_MSG_MAP(CApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CApp::CApp()
{
}

BOOL CApp::InitInstance()
{
	// Save settings in registry, not INI file
	SetRegistryKey("MSJ");

   // Create main frame window (don't use doc/view stuff)
   // 
   CMainFrame* pMainFrame = new CMainFrame;
   if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
      return FALSE;

	// Load window position from profile
	CWindowPlacement wp;
	if (!wp.Restore(CMainFrame::REGKEY, pMainFrame))
		pMainFrame->ShowWindow(m_nCmdShow);
   pMainFrame->UpdateWindow();
   m_pMainWnd = pMainFrame;

	return TRUE;
}

void CApp::OnAppAbout()
{
	CDialog(IDD_ABOUTBOX).DoModal();
}
