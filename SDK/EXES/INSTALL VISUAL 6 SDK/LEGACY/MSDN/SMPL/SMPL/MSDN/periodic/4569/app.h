////////////////////////////////////////////////////////////////
// TRACEWIN Copyright 1995 Microsoft Systems Journal. 
// If this program works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
//
// TRACEWIN applet sits around waiting for diagnostic messages from 
// MFC apps that have #included TRACEWIN.H

#include "resource.h"

/////////////////
// Application class
//
class CApp : public CWinApp {
public:
	CApp();
	virtual BOOL InitInstance();

	//{{AFX_MSG(CApp)
	afx_msg void OnAppAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
