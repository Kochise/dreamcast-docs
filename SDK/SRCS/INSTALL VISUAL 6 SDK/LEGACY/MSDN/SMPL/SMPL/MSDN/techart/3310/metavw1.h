// metavw1.h : main header file for the METAVW1 application
//

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
//#include "emfinfov.h"

/////////////////////////////////////////////////////////////////////////////
// CMetavw1App:
// See metavw1.cpp for the implementation of this class
//

class CMetavw1App : public CWinApp
{
public:
	CMetavw1App();
	CMultiDocTemplate* pDocTemplate;
	CMultiDocTemplate* pEMFInfoTemplate;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMetavw1App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMetavw1App)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

extern CMetavw1App NEAR theApp;

/////////////////////////////////////////////////////////////////////////////
