// fwtest.h : main header file for the FWTEST application
//

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CFwtestApp:
// See fwtest.cpp for the implementation of this class
//

class CFwtestApp : public CWinApp
{
public:
	CFwtestApp();

// Overrides
	virtual BOOL InitInstance();

// Implementation

	//{{AFX_MSG(CFwtestApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
