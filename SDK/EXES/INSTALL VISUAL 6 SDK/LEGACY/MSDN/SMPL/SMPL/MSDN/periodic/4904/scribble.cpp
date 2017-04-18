////////////////////////////////////////////////////////////////
// Modified SCRIBBLE Copyright 1996 Microsoft Systems Journal. 
// If this program works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
//
// This modified SCRIBBLE program shows how to store a document in the
// resource file and then load it using the normal serialization mechanism.
//
// Modifications to original program are tagged "**MOD**".
// 

#include "stdafx.h"
#include "Scribble.h"
#include "MainFrm.h"
#include "ChildFrm.h"
#include "ScribDoc.h"
#include "ScribVw.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(CScribbleApp, CWinApp)
	//{{AFX_MSG_MAP(CScribbleApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_FILE_SAMPLE, OnFileSample)  // **MOD** 
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

CScribbleApp::CScribbleApp()
{
}

CScribbleApp theApp;

BOOL CScribbleApp::InitInstance()
{
	LoadStdProfileSettings();

	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(
		IDR_SCRIBBTYPE,
		RUNTIME_CLASS(CScribbleDoc),
		RUNTIME_CLASS(CChildFrame),
		RUNTIME_CLASS(CScribbleView));

	AddDocTemplate(pDocTemplate);

	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;

	// Enable drag/drop open.  We don't call this in Win32, since a
	//  document file extension wasn't chosen while running AppWizard.
	m_pMainWnd->DragAcceptFiles();

	// Enable DDE Execute open
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The main window has been initialized, so show and update it.
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	return TRUE;
}

void CScribbleApp::OnAppAbout()
{
	CDialog(IDD_ABOUTBOX).DoModal();
}

//////////////////
// **MOD** handle "File New Sample"
//
void CScribbleApp::OnFileSample() 
{
	OnFileNew();	// create new (empty) doc
	CScribbleDoc* pDoc = (CScribbleDoc*)
		((CFrameWnd*)m_pMainWnd)->GetActiveFrame()->GetActiveDocument();
	ASSERT_VALID(pDoc);
	ASSERT_KINDOF(CScribbleDoc, pDoc);

	// load resource doc IDR_MAINFRAME
	VERIFY(pDoc->OnOpenDocument(IDR_MAINFRAME));

	// give it a name
	pDoc->SetPathName(_T("Sample.SCB"));
}
