//***************************************************************************
//
//  Life.cpp
//
//***************************************************************************

#include <afxwin.h>
#include <afxext.h>

#include "Resource.h"
#include "Life.h"
#include "LifeDoc.h"
#include "MainFrm.h"
#include "LifeView.h"
#include "AboutDlg.h"

CLifeApp myApp;

BEGIN_MESSAGE_MAP (CLifeApp, CWinApp)
    ON_COMMAND (ID_FILE_NEW, CWinApp::OnFileNew)
    ON_COMMAND (ID_FILE_OPEN, CWinApp::OnFileOpen)
    ON_COMMAND (ID_APP_ABOUT, OnAppAbout)
END_MESSAGE_MAP ()

BOOL CLifeApp::InitInstance ()
{
    SetRegistryKey ("Microsoft Systems Journal");
    LoadStdProfileSettings ();

    CSingleDocTemplate* pDocTemplate;
    pDocTemplate = new CSingleDocTemplate (
        IDR_MAINFRAME,                  // Resource ID
        RUNTIME_CLASS (CLifeDoc),       // Document class
        RUNTIME_CLASS (CMainFrame),     // Frame window class
        RUNTIME_CLASS (CLifeView)       // View class
    );

    AddDocTemplate (pDocTemplate);

    EnableShellOpen ();
    RegisterShellFileTypes ();

    CCommandLineInfo cmdInfo;
    ParseCommandLine (cmdInfo);

    if (!ProcessShellCommand (cmdInfo))
        return FALSE;

    m_pMainWnd->DragAcceptFiles ();
    return TRUE;
}

void CLifeApp::OnAppAbout ()
{
    CAboutDialog dlg;
    dlg.DoModal ();
}
