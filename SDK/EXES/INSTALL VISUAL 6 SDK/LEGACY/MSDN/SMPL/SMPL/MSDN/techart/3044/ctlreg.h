// ctlreg.h : main header file for the CTLREG application
//

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CCtlregApp:
// See ctlreg.cpp for the implementation of this class
//

class CCtlregApp : public CWinApp
{
public:
	CCtlregApp();

// Overrides
	virtual BOOL InitInstance();

// Implementation

	//{{AFX_MSG(CCtlregApp)
	afx_msg void OnAppAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
