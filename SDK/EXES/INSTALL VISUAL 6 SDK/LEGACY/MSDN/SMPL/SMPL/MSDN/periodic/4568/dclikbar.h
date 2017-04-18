////////////////////////////////////////////////////////////////
// DCLIKBAR Copyright 1995 Microsoft Systems Journal. 
// If this program works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
//
// See DCLIKBAR.CPP for Description of program.

#include "resource.h"

class CDclikbarApp : public CWinApp {
public:
	CDclikbarApp();
	virtual BOOL InitInstance();

	//{{AFX_MSG(CDclikbarApp)
	afx_msg void OnAppAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
