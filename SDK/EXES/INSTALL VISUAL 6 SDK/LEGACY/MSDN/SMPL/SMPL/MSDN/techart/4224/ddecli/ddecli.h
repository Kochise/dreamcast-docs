// DDECli.h : main header file for the DDECLI application
//

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include "..\stddde\stddde.h"

/////////////////////////////////////////////////////////////////////////////
// CDDEClientApp:
// See DDECli.cpp for the implementation of this class
//

class CDDEClientApp : public CWinApp
{
public:
	CDDEClientApp();
    void Status(const char* pszFormat, ...);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDDEClientApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CDDEClientApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

extern CDDEClientApp theApp;

#define STATUS theApp.Status
/////////////////////////////////////////////////////////////////////////////
