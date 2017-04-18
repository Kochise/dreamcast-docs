// 16bit.h : main header file for the 16BIT application
//

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// C16bitApp:
// See 16bit.cpp for the implementation of this class
//

class C16bitApp : public CWinApp
{
public:
	C16bitApp();

// Overrides
	virtual BOOL InitInstance();

// Implementation

	//{{AFX_MSG(C16bitApp)
	afx_msg void OnAppAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
