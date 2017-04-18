////////////////////////////////////////////////////////////////
// TRAYTEST Copyright 1996 Microsoft Systems Journal. 
// See TRAYTEST.CPP for description of program.
// 
#include "resource.h"

class CMyApp : public CWinApp {
public:
	virtual BOOL InitInstance();
	//{{AFX_MSG(CMyApp)
	afx_msg void OnAppAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
