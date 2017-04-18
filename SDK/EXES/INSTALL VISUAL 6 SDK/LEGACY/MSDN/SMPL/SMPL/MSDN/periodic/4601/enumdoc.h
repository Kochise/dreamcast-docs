////////////////////////////////////////////////////////////////
// ENUMDOC Copyright 1995 Microsoft Systems Journal. 
// If this program works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
//
// ENUMDOC illustrates how to enumerate all the docs in an MFC app.
// 
#include "resource.h"

class CEnumdocApp : public CWinApp {
public:
   CEnumdocApp();
   virtual BOOL InitInstance();
   afx_msg void OnAppAbout();
   afx_msg void OnEnumDocs();
   DECLARE_MESSAGE_MAP()
};
