// streams.cpp

#define VC_EXTRALEAN
#define STRICT

#include <afxwin.h>
#include <afxdlgs.h>
#include <mmsystem.h>
#include "resource.h"
#include "audiostream.h"
#include "streams.h"

/////////////////////////////////////////////////////////////////////////////

// theApp:
// Just creating this application object runs the whole application.
//
CTheApp theApp;

/////////////////////////////////////////////////////////////////////////////

// CMainWindow constructor:
// Create the window with the appropriate style, size, menu, etc.
//
CMainWindow::CMainWindow()
{
    LoadFrame(IDR_MAINFRAME);
}

// OnAbout:
// This member function is called when a WM_COMMAND message with an
// ID_APP_ABOUT code is received by the CMainWindow class object.   The
// message map below is responsible for this routing.
//
// We create a ClDialog object using the "AboutBox" resource (see
// hello.rc), and invoke it.
//
void CMainWindow::OnAbout()
{
    CDialog about(IDD_ABOUTBOX);
    about.DoModal();
}

// CMainWindow message map:
// Associate messages with member functions.
//
// It is implied that the ON_WM_PAINT macro expects a member function
// "void OnPaint()".
//
// It is implied that members connected with the ON_COMMAND macro
// receive no arguments and are void of return type, e.g., "void OnAbout()".
//
BEGIN_MESSAGE_MAP( CMainWindow, CFrameWnd )
    //{{AFX_MSG_MAP( CMainWindow )
    ON_COMMAND(ID_APP_ABOUT, OnAbout)
    ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
    ON_COMMAND(ID_TEST_PLAY, OnTestPlay)
    ON_COMMAND(ID_TEST_STOP, OnTestStop)
    ON_UPDATE_COMMAND_UI(ID_TEST_PLAY, OnUpdateTestPlay)
    ON_UPDATE_COMMAND_UI(ID_TEST_STOP, OnUpdateTestStop)
    ON_WM_CREATE()
    ON_WM_DESTROY()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTheApp

// InitInstance:
// When any CTheApp object is created, this member function is automatically
// called.  Any data may be set up at this point.
//
// Also, the main window of the application should be created and shown here.
// Return TRUE if the initialization is successful.
//
BOOL CTheApp::InitInstance()
{
    TRACE0("CTheApp::InitInstance\n");

    Enable3dControls(); // use 3d controls in dialogs

    m_pMainWnd = new CMainWindow;
    m_pMainWnd->ShowWindow(m_nCmdShow);
    m_pMainWnd->UpdateWindow();

    return TRUE;
}

void CMainWindow::OnFileOpen() 
{
    CString cstrPath;

    // Create standard Open File dialog
    CFileDialog * pfd 
        = new CFileDialog (TRUE, NULL, NULL,
                           OFN_EXPLORER | OFN_NONETWORKBUTTON | OFN_HIDEREADONLY,
                           "Wave Files (*.wav) | *.wav||", this);
    // Show dialog
    if (pfd->DoModal () == IDOK)
    {
        // Get pathname
        cstrPath = pfd->GetPathName();

        // Delete current AudioStream object
        if (m_pasCurrent)
        {
            delete (m_pasCurrent);
        }

        // Create new AudioStream object
        m_pasCurrent = new AudioStream;
        m_pasCurrent->Create ((LPSTR)(LPCTSTR (cstrPath)), m_pass);
    }
        
    delete (pfd);
}

void CMainWindow::OnTestPlay() 
{
    if (m_pasCurrent)
    {
        m_pasCurrent->Play ();
    }
}

void CMainWindow::OnTestStop() 
{
    if (m_pasCurrent)
    {
        m_pasCurrent->Stop ();
    }
}


void CMainWindow::OnUpdateTestPlay(CCmdUI* pCmdUI) 
{
    if (m_pasCurrent)
    {
        pCmdUI->Enable (TRUE);
    }
    else
    {
        pCmdUI->Enable (FALSE);
    }
}

void CMainWindow::OnUpdateTestStop(CCmdUI* pCmdUI) 
{
    if (m_pasCurrent)
    {
        pCmdUI->Enable (TRUE);
    }
    else
    {
        pCmdUI->Enable (FALSE);
    }
}

int CMainWindow::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
    if (CFrameWnd ::OnCreate(lpCreateStruct) == -1)
        return -1;

    // Create and initialize AudioStreamServices object.
    // This must be done once and only once for each window that uses
    // streaming services.
    m_pass = new AudioStreamServices;
    if (m_pass)
    {
        m_pass->Initialize (m_hWnd);
    }

    // Initialize ptr to current AudioStream object
    m_pasCurrent = NULL;
    
    return 0;
}

void CMainWindow::OnDestroy() 
{
    CFrameWnd ::OnDestroy();
    
    // Destroy current AudioStream object
    if (m_pasCurrent)
    {
        m_pasCurrent->Destroy ();
        delete (m_pasCurrent);
    }

    // Destroy AudioStreamServices object
    if (m_pass)
    {
        delete (m_pass);
    }
}
