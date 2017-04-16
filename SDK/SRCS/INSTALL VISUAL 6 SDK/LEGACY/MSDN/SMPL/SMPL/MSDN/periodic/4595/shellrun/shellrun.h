/******************************************************************************
Module name: ShellRun.h
Written by:  Jeffrey Richter
Purpose:     Shell Run CWinApp-derived class description file.
******************************************************************************/


#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols


/////////////////////////////////////////////////////////////////////////////
// CShellRunApp:
// See ShellRun.cpp for the implementation of this class
//

class CShellRunApp : public CWinApp {
public:
	CShellRunApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CShellRunApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CShellRunApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


//////////////////////////////// End of File //////////////////////////////////
