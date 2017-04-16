////////////////////////////////////////////////////////////////
// DCLIKBAR Copyright 1995 Microsoft Systems Journal. 
// If this program works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
//
// DCLIKBAR shows how to change the window class name of your application's
// main windows, and also how to implement a control bar that allows 
// double-clicking.
//
// All the interesting code is in MAINFRM.CPP
// Makefiles: DCLIK152.MAK for VC++ 1.52
//            DCLIKB22.MAK for VC++ 2.2
//            DCLIKB40.MAK for VC++ 4.0

#include "stdafx.h"
#include "dclikbar.h"
#include "mainfrm.h"
#include "doc.h"
#include "view.h"

CDclikbarApp NEAR theApp;

BEGIN_MESSAGE_MAP(CDclikbarApp, CWinApp)
	//{{AFX_MSG_MAP(CDclikbarApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()

CDclikbarApp::CDclikbarApp()
{
}

BOOL CDclikbarApp::InitInstance()
{
	SetDialogBkColor();        // Set dialog background color to gray

	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(
		IDR_DOCTYPE,
		RUNTIME_CLASS(CMyDoc),
		RUNTIME_CLASS(CMyChildFrame),
		RUNTIME_CLASS(CMyView));
	AddDocTemplate(pDocTemplate);

	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;

	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	OnFileNew();

	return TRUE;
}

class CAboutDlg : public CDialog {
public:
	CAboutDlg() : CDialog(IDD_ABOUTBOX) { }
};

void CDclikbarApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}
