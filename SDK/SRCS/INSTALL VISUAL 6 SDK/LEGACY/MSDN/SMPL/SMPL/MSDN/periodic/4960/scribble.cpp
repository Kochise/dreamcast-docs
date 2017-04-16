////////////////////////////////////////////////////////////////
// Modified SCRIBBLE Copyright 1996 Microsoft Systems Journal. 
// Portions Copyright (C) 1992-1995 Microsoft Corporation
// If this program works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
//
// This program is based on the SCRIBBLE program that comes with
// Microsoft Visual C++, as part of the MFC tutorial.
//
// This modified SCRIBBLE shows
//
// -how to write an SDI app that starts with an empty frame instead
//  of a new document;
//
// -how to write an exception handler to handle any uncaught exception
//  that occurs while the app is running.
//
// Mods identified with ***PD
//
#include "stdafx.h"
#include "Scribble.h"
#include "MainFrm.h"
#include "ScribDoc.h"
#include "ScribVw.h"
#include <eh.h>         // set_terminate
#include "TraceWin.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CScribbleApp

BEGIN_MESSAGE_MAP(CScribbleApp, CWinApp)
   //{{AFX_MSG_MAP(CScribbleApp)
   ON_COMMAND(ID_APP_ABOUT,    OnAppAbout)
   ON_COMMAND(ID_EX_USER,      OnExUser)
   ON_COMMAND(ID_EX_MEMORY,    OnExMemory)
   ON_COMMAND(ID_EX_RESOURCE,  OnExResource)
   //}}AFX_MSG_MAP
	ON_COMMAND(ID_FILE_NEW,     OnMyFileNew) // ***PD: my own handler
   ON_COMMAND(ID_FILE_OPEN,    CWinApp::OnFileOpen)
   ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

CScribbleApp theApp;

typedef void (*TERMINATE_FN)();
TERMINATE_FN old_terminate = NULL;

////////////////
// Custom terminate handler just displays message
//
void my_terminate()
{
   MessageBox(NULL, "Help me, I'm dying.", "Terminate", MB_OK);

	// Call old terminate fn, if any. On Windows, old_terminate is NULL;
   if (old_terminate)
      old_terminate();
}

CScribbleApp::CScribbleApp()
{
   MfxTraceInit();	// initialize TRACEWIN tracing
   old_terminate = set_terminate(my_terminate);
   TRACE("old terminate fn = %p\n", old_terminate);
}

CScribbleApp::~CScribbleApp()
{
   set_terminate(old_terminate);
}

//////////////////
// Initialize app
//
BOOL CScribbleApp::InitInstance()
{
   SetRegistryKey("MSJ");     // Use HKEY_CURRENT_USER\Software\MSJ for INI
   LoadStdProfileSettings();  // Load INI file options (including MRU file)

   // create doc template
   CDocTemplate* pDocTemplate;
   pDocTemplate = new CSingleDocTemplate(
      IDR_MAINFRAME,
      RUNTIME_CLASS(CScribbleDoc),
      RUNTIME_CLASS(CMainFrame),
      RUNTIME_CLASS(CScribbleView));
   AddDocTemplate(pDocTemplate);

// EnableShellOpen();            // Only need for File Manager double-click/DDE
   RegisterShellFileTypes(TRUE); // TRUE for Win 95
   
   // Parse command line for standard shell commands, DDE, file open
   CCommandLineInfo cmdInfo;
   ParseCommandLine(cmdInfo);
   if (!ProcessShellCommand(cmdInfo)) // dispatch command
      return FALSE;
   return TRUE;
}

//////////////////
// ***PD REALLY create new document: initialize the empty doc object.
//
void CScribbleApp::OnMyFileNew()
{
   OnFileNew(); // do normal thing to create new doc
                // (in case this is an open doc, reuse it)

   CFrameWnd* pFrame = (CFrameWnd*)m_pMainWnd;
   ASSERT_KINDOF(CFrameWnd, pFrame);
   CScribbleView* pView = (CScribbleView*)pFrame->GetActiveView();
   ASSERT_KINDOF(CScribbleView, pView);
   pView->GetDocument()->Initialize(); // initialize new doc
}

void CScribbleApp::OnAppAbout()
{
	CDialog(IDD_ABOUTBOX).DoModal();
}

//////////////////
// Commands to throw various kinds of exceptions.
//
void CScribbleApp::OnExUser()     { AfxThrowUserException();     }
void CScribbleApp::OnExMemory()   { AfxThrowMemoryException();   }
void CScribbleApp::OnExResource() { AfxThrowResourceException(); }

//////////////////
// Exception handler of last resort. Display message box describing
// exception, then try to save all files.
//
LRESULT CScribbleApp::ProcessWndProcException(CException* e, const MSG* pMsg)
{
   CString s = "An unhandled error occurred in your program.\n\n";
   CString m;
   m.Format("type\t%s\n", e->GetRuntimeClass()->m_lpszClassName);
   s += m;
   m.Format("HWND\t0x%04x\nmsg\t0x%04x\nwParam\t0x%08x\nlParam\t0x%08x",
      pMsg->hwnd, pMsg->message, pMsg->wParam, pMsg->lParam);
   s += m;
   s += "\n\nSelect:\nAbort \tto terminate the program;\n";
   s += "Retry \tto let MFC handle the error; or\n";
   s += "Ignore \tto do nothing.\n\n";
   s += "After this dialog, you'll have a chance to save modified documents.";
   int nRes = MessageBox(m_pMainWnd->GetSafeHwnd(), s, "Error!", 
      MB_ABORTRETRYIGNORE);

   // Save any modified docs
   SaveAllModified();

   if (nRes==IDABORT)
      THROW_LAST();        // will call terminate()
   else if (nRes==IDRETRY)
      return CWinApp::ProcessWndProcException(e, pMsg); // do MFC Thing

   return 0; // IDIGNORE
}
