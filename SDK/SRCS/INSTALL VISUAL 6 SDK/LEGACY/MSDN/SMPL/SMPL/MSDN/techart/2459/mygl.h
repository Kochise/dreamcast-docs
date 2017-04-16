// mygl.h : main header file for the MYGL application
//

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMyglApp:
// See mygl.cpp for the implementation of this class
//

class CMyglApp : public CWinApp
{
public:
	CMyglApp();

// Overrides
	virtual BOOL InitInstance();

// Implementation

	//{{AFX_MSG(CMyglApp)
	afx_msg void OnAppAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
