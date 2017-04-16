// viewfile.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"

#include "viewfile.h"

#include "headers.h"

#include "mainfrm.h"
#include "childfrm.h"
#include "viewfdoc.h"

#include "fileview.h"

#include "pview.h"
#include "pviewdoc.h"

#include "nosysfra.h"


#include "viewfvw.h"
// this is where the custom views are defined
#include "leview.h"
#include "neview.h"
#include "rawview.h"
//#include "customvi.h"
#include "peview.h"
#include "dosview.h"

// this is where the custom frames are defined

#include "rawframe.h"
#include "dosframe.h"
#include "lecframe.h"
#include "pecframe.h"
//#include "custfram.h"
#include "necframe.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CViewfileApp

BEGIN_MESSAGE_MAP(CViewfileApp, CWinApp)
	//{{AFX_MSG_MAP(CViewfileApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CViewfileApp construction

CViewfileApp::CViewfileApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CViewfileApp object

CViewfileApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CViewfileApp initialization

BOOL CViewfileApp::InitInstance()
{
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.


	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	m_pRawTemplate = new CMultiDocTemplate(
		IDR_RAWTYPE,
		RUNTIME_CLASS(CViewfileDoc),
		RUNTIME_CLASS(CRawFrame), // custom MDI child frame
		RUNTIME_CLASS(CRawView));
	AddDocTemplate(m_pRawTemplate);

   m_pDOSTemplate = new CMultiDocTemplate(
		IDR_DOSTYPE,
		RUNTIME_CLASS(CViewfileDoc),
		RUNTIME_CLASS(CDOSFrame), // custom MDI child frame
		RUNTIME_CLASS(CDOSView));
	AddDocTemplate(m_pDOSTemplate);

   
    m_pNETemplate = new CMultiDocTemplate(
		IDR_NETYPE,
		RUNTIME_CLASS(CViewfileDoc),
		RUNTIME_CLASS(CNECFrame), // custom MDI child frame
		RUNTIME_CLASS(CNEView));
	AddDocTemplate(m_pNETemplate);
    
    m_pLETemplate = new CMultiDocTemplate(
		IDR_LETYPE,
		RUNTIME_CLASS(CViewfileDoc),
		RUNTIME_CLASS(CLECFrame), // custom MDI child frame
		RUNTIME_CLASS(CLEView));
	AddDocTemplate(m_pLETemplate);
    
    m_pPETemplate = new CMultiDocTemplate(
		IDR_PETYPE,
		RUNTIME_CLASS(CViewfileDoc),
		RUNTIME_CLASS(CPECFrame), // custom MDI child frame
		RUNTIME_CLASS(CPEView));
	AddDocTemplate(m_pPETemplate);

	m_pPViewTemplate = new CMultiDocTemplate(
	    IDR_PVIEWTYPE,
		RUNTIME_CLASS(CPViewDoc),
		RUNTIME_CLASS(CNoSysFrame),
		RUNTIME_CLASS(CPView));
	AddDocTemplate(m_pPViewTemplate);
    
    	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;
// this creates the process view window
	if (m_lpCmdLine[0] != '\0')
	{
		// TODO: add command line processing here
		// note: this will give us a RAW view because that view was created first...
     OpenDocumentFile(m_lpCmdLine);
	}

	// The main window has been initialized, so show and update it.
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();
    m_ProcessList = (CPViewDoc *)m_pPViewTemplate->OpenDocumentFile(NULL);
	return TRUE;
}

void CViewfileApp::RefreshProcessList()
{
 m_ProcessList->RefreshProcessList();
};

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//{{AFX_MSG(CAboutDlg)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CViewfileApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CViewfileApp commands

void CViewfileApp::SetStatusBarText(char *szText)
{
 ((CMainFrame *)m_pMainWnd)->SetStatusBar(szText);
}

CDocument* CViewfileApp::OpenDocumentFile(LPCTSTR lpszFileName) 
{
	CDocument *cdResult = CWinApp::OpenDocumentFile(lpszFileName);
	if (cdResult)
	   ((CViewfileDoc *)cdResult)->ActivateTheRightFrame();

	return cdResult;
}

