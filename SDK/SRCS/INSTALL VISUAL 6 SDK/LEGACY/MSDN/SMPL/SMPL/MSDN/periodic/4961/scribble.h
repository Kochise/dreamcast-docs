////////////////////////////////////////////////////////////////
// Modified SCRIBBLE Copyright 1996 Microsoft Systems Journal. 
// Portions Copyright (C) 1992-1995 Microsoft Corporation.
// If this program works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
//
// See SCRIBBLE.CPP for Description of program.
//
#include "resource.h"       // main symbols

class CScribbleApp : public CWinApp {
public:
   CScribbleApp();
   ~CScribbleApp();
   virtual BOOL InitInstance();

	// ***PD Override exception handler
   virtual LRESULT ProcessWndProcException(CException* e, const MSG* pMsg);

   //{{AFX_MSG(CScribbleApp)
   afx_msg void OnAppAbout();
	afx_msg void OnMyFileNew();	// ***PD: This replaces OnFileNew to
											// handle ID_FILE_NEW
   afx_msg void OnExUser();
   afx_msg void OnExMemory();
   afx_msg void OnExResource();
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
};

