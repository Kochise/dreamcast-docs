////////////////////////////////////////////////////////////////
// ENUMDOC Copyright 1995 Microsoft Systems Journal. 
// If this program works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
//
// ENUMDOC illustrates how to enumerate all the docs in an MFC app.
// 
#include "stdafx.h"
#include "enumdoc.h"
#include "mainfrm.h"
#include "doc.h"
#include "view.h"
#include "docenum.h"

BEGIN_MESSAGE_MAP(CEnumdocApp, CWinApp)
   ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
   ON_COMMAND(ID_FILE_NEW,  CWinApp::OnFileNew)
   ON_COMMAND(ID_FILE_ENUM_DOCS, OnEnumDocs)
END_MESSAGE_MAP()

CEnumdocApp NEAR theApp;

CEnumdocApp::CEnumdocApp()
{
}

BOOL CEnumdocApp::InitInstance()
{
   // Register two document types
   CMultiDocTemplate* pDocTemplate = new CMultiDocTemplate(IDR_TYPEA,
      RUNTIME_CLASS(CDocA),
      RUNTIME_CLASS(CMDIChildWnd),
      RUNTIME_CLASS(CViewA));
   AddDocTemplate(pDocTemplate);

   pDocTemplate = new CMultiDocTemplate(IDR_TYPEB,
      RUNTIME_CLASS(CDocB),
      RUNTIME_CLASS(CMDIChildWnd),
      RUNTIME_CLASS(CViewB));
   AddDocTemplate(pDocTemplate);

   // Create main MDI Frame window
   CMainFrame* pMainFrame = new CMainFrame;
   if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
      return FALSE;
   m_pMainWnd = pMainFrame;

   pMainFrame->ShowWindow(m_nCmdShow);
   pMainFrame->UpdateWindow();

   return TRUE;
}

class CAboutDlg : public CDialog {
public:
   CAboutDlg() : CDialog(IDD_ABOUTBOX) { }
};

void CEnumdocApp::OnAppAbout()
{
   CAboutDlg aboutDlg;
   aboutDlg.DoModal();
}

//////////////////
// Implement "File Enumerate Docs" command.
//
void CEnumdocApp::OnEnumDocs()
{
   CBaseDoc *pDoc;
   CString msg;
   CDocEnumerator nextDoc;

   // Must cast to CBaseDoc. Use ASSERT for safety.
   while ((pDoc = (CBaseDoc*)nextDoc()) != NULL) {
      ASSERT(pDoc->IsKindOf(RUNTIME_CLASS(CBaseDoc)));
      pDoc->AddTitleToString(msg);
   }
   if (msg.IsEmpty())
      msg = "(Create some documents, then try it.)";

   // Display results in a message box
   m_pMainWnd->MessageBox(msg,"Results",MB_OK);
}
