//***********************************************************************
//
//  HexDump.cpp
//
//***********************************************************************

#include <afxwin.h>
#include "Resource.h"
#include "HexDump.h"
#include "HexDoc.h"
#include "HexView.h"

CHexDumpApp myApp;

BEGIN_MESSAGE_MAP (CHexDumpApp, CWinApp)
    ON_COMMAND (ID_FILE_OPEN, CWinApp::OnFileOpen)
    ON_COMMAND (ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP ()

BOOL CHexDumpApp::InitInstance ()
{
    SetRegistryKey ("Programming Windows 95 with MFC");
    LoadStdProfileSettings ();

    CSingleDocTemplate* pDocTemplate;
    pDocTemplate = new CSingleDocTemplate (
        IDR_MAINFRAME,
        RUNTIME_CLASS (CHexDoc),
        RUNTIME_CLASS (CFrameWnd),
        RUNTIME_CLASS (CHexView)
    );

    AddDocTemplate (pDocTemplate);

    CCommandLineInfo cmdInfo;
    ParseCommandLine (cmdInfo);

    if (!ProcessShellCommand (cmdInfo))
        return FALSE;

    m_pMainWnd->DragAcceptFiles ();
    return TRUE;
}
