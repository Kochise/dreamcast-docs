////////////////////////////////////////////////////////////////
// VIEW3 Copyright 1996 Microsoft Systems Journal. 
// If this program works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
//
// VIEW3 Shows how to use CDynViewDocTemplate to implement an app that
// supports different views of the same document.
//
#include "stdafx.h"
#include "view3.h"
#include "MainFrm.h"
#include "ChildFrm.h"
#include "Doc.h"
#include "View.h"
#include "DynTempl.h"

#if (_MFC_VER < 0x0400)
#error Sorry, this program requires MFC Version 4.0 or later.
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(CApp, CWinApp)
   //{{AFX_MSG_MAP(CApp)
   ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
   //}}AFX_MSG_MAP
   ON_COMMAND(ID_FILE_NEW,  CWinApp::OnFileNew)
   ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()

// To add another view, put it in this table.
// Default view is first, must be in same order as "View As" menu commands.
//
static const DYNAMICVIEWINFO MyViewClasses[] = {
   { RUNTIME_CLASS(CView1), "ASCII" },
   { RUNTIME_CLASS(CView2), "Binary" },
   { RUNTIME_CLASS(CView3), "Binary Stripes" },
   { NULL, NULL }
};

CApp theApp;

BOOL CApp::InitInstance()
{
   // Create "dynamic" document template. 
   AddDocTemplate(new CDynViewDocTemplate(IDR_VIEW3TYPE,
      RUNTIME_CLASS(CView3Doc),
      RUNTIME_CLASS(CChildFrame),
      MyViewClasses)); // array of view classes

   // create main MDI Frame window (standard MFC)...
   CMainFrame* pMainFrame = new CMainFrame;
   if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
      return FALSE;
   m_pMainWnd = pMainFrame;

   // Standard AppWiz junk...
   CCommandLineInfo cmdInfo;
   ParseCommandLine(cmdInfo);
   if (!ProcessShellCommand(cmdInfo))
      return FALSE;

   pMainFrame->ShowWindow(m_nCmdShow);
   pMainFrame->UpdateWindow();

   return TRUE;
}

void CApp::OnAppAbout()
{
   CDialog aboutDlg(IDD_ABOUTBOX);
   aboutDlg.DoModal();
}
