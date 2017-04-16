// speller.h : main header file for the SPELLER application
//

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSpellerApp:
// See speller.cpp for the implementation of this class
//

class CSpellerApp : public CWinApp
{
public:
	CSpellerApp();

// Overrides
	virtual BOOL InitInstance();

// Implementation

	//{{AFX_MSG(CSpellerApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
