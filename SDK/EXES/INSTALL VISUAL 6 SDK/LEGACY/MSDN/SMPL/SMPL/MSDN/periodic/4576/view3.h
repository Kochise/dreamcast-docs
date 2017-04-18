////////////////////////////////////////////////////////////////
// VIEW3 Copyright 1996 Microsoft Systems Journal. 
// If this program works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
//
// See VIEW3.CPP for Description of program.
// 
#include "resource.h"

//////////////////
// Application class is generic
//
class CApp : public CWinApp {
public:
   virtual BOOL InitInstance();
   //{{AFX_MSG(CApp)
   afx_msg void OnAppAbout();
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
};
