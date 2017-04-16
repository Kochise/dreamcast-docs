////////////////////////////////////////////////////////////////
// TRAYTEST Copyright 1996 Microsoft Systems Journal. 
// If this program works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
//
// TRAYTEST illustrates how to use CTrayIcon. 
// All the activity takes place in MainFrm.cpp.

#include "stdafx.h"
#include "TrayTest.h"
#include "mainfrm.h"

CMyApp theApp;

BEGIN_MESSAGE_MAP(CMyApp, CWinApp)
	//{{AFX_MSG_MAP(CMyApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CMyApp::InitInstance()
{
	// Create main frame window (don't use doc/view stuff)
	// 
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	pMainFrame->ShowWindow(SW_HIDE);
	pMainFrame->UpdateWindow();
	m_pMainWnd = pMainFrame;
	OnAppAbout();
	return TRUE;
}

void CMyApp::OnAppAbout()
{
	CDialog(IDD_ABOUTBOX).DoModal();
}

