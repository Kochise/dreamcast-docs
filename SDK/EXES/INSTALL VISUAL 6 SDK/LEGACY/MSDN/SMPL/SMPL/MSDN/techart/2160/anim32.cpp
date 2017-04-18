// anim32.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "anim32.h"
#include "mainfrm.h"
#include "animdoc.h"
#include "animvw.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAnimApp

BEGIN_MESSAGE_MAP(CAnimApp, CWinApp)
    //{{AFX_MSG_MAP(CAnimApp)
    ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
        // NOTE - the ClassWizard will add and remove mapping macros here.
        //    DO NOT EDIT what you see in these blocks of generated code !
    //}}AFX_MSG_MAP
    // Standard file based document commands
    ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
    ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAnimApp construction

CAnimApp::CAnimApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CAnimApp object

CAnimApp NEAR theApp;
#ifdef _DEBUG
CDbgWnd theDbgWnd;      // debug window
#endif // _DEBUG
int theDbgLevel;        // debug level

/////////////////////////////////////////////////////////////////////////////
// CAnimApp initialization

BOOL CAnimApp::InitInstance()
{
#ifdef _DEBUG
    // Create the debug window
    theDbgWnd.Create();
    dprintf("Started");
    LARGE_INTEGER li;
    QueryPerformanceFrequency(&li);
    dprintf("Perf. freq: %lu, %lu", li.HighPart, li.LowPart);

#endif // _DEBUG

    // Standard initialization
    // If you are not using these features and wish to reduce the size
    //  of your final executable, you should remove from the following
    //  the specific initialization routines you do not need.

    SetDialogBkColor();        // set dialog background color to gray
    LoadStdProfileSettings();  // Load standard INI file options (including MRU)

    // Register the application's document templates.  Document templates
    //  serve as the connection between documents, frame windows and views.

    AddDocTemplate(new CSingleDocTemplate(IDR_MAINFRAME,
            RUNTIME_CLASS(CAnimDoc),
            RUNTIME_CLASS(CMainFrame),     // main SDI frame window
            RUNTIME_CLASS(CAnimView)));


    // simple command line parsing
    if (m_lpCmdLine[0] == '\0')
    {
        // create a new (empty) document
        OnFileNew();
    }
    else
    {
        // open an existing document
        OpenDocumentFile(m_lpCmdLine);
    }

    return TRUE;
}


int CAnimApp::ExitInstance()
{
#ifdef _DEBUG
    theDbgWnd.DestroyWindow();
#endif // _DEBUG
    return CWinApp::ExitInstance();
}
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
void CAnimApp::OnAppAbout()
{
    CAboutDlg aboutDlg;
    aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CAnimApp commands

BOOL CAnimApp::OnIdle(LONG lCount)
{
    CWinApp::OnIdle(lCount);

    if (!m_pMainWnd) return FALSE;
    CMainFrame *pFrameWnd = (CMainFrame *)m_pMainWnd;
    ASSERT(pFrameWnd->IsKindOf(RUNTIME_CLASS(CMainFrame)));
    CAnimDoc *pDoc = (CAnimDoc *) pFrameWnd->GetActiveDocument();
    if (!pDoc) return FALSE;
    ASSERT(pDoc->IsKindOf(RUNTIME_CLASS(CAnimDoc)));
    pDoc->UpdateSpritePositions();
    return TRUE; // need more idle cycles
}
