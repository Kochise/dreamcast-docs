//***********************************************************************
//
//  EZPrint.cpp
//
//***********************************************************************

#include <afxwin.h>
#include "Resource.h"
#include "EZPrint.h"
#include "EZPrintDoc.h"
#include "EZPrintView.h"

CPrintApp myApp;

BEGIN_MESSAGE_MAP (CPrintApp, CWinApp)
    ON_COMMAND (ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP ()

BOOL CPrintApp::InitInstance ()
{
    CSingleDocTemplate* pDocTemplate;
    pDocTemplate = new CSingleDocTemplate (
        IDR_MAINFRAME,
        RUNTIME_CLASS (CPrintDoc),
        RUNTIME_CLASS (CFrameWnd),
        RUNTIME_CLASS (CPrintView)
    );

    AddDocTemplate (pDocTemplate);

    CCommandLineInfo cmdInfo;
    ParseCommandLine (cmdInfo);

    if (!ProcessShellCommand (cmdInfo))
        return FALSE;

    return TRUE;
}
