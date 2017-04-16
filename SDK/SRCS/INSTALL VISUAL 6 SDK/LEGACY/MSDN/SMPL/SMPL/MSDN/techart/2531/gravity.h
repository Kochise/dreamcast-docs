// gravity.h : main header file for the GRAVITY application
//

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols


/////////////////////////////////////////////////////////////////////////////
// CGravityApp:
// See gravity.cpp for the implementation of this class
//

class CGravityApp : public CWinApp
{
public:
	CGravityApp();

// Overrides
	virtual BOOL InitInstance();

// Implementation

	//{{AFX_MSG(CGravityApp)
	afx_msg void OnAppAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
