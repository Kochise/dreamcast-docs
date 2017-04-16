// pop3.h : main header file for the POP3 application
//

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CPop3App:
// See pop3.cpp for the implementation of this class
//

class CPop3App : public CWinApp
{
public:
	CPop3App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPop3App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
private:
    void DoConfig(CWnd* pParent);
    
	//{{AFX_MSG(CPop3App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

extern CPop3App theApp;

/////////////////////////////////////////////////////////////////////////////
