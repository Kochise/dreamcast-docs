// DDEServ.h : main header file for the DDESERV application
//

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
#include "..\stddde\stddde.h"

/////////////////////////////////////////////////////////////////////////////
// CDDEServ:
// See DDEServ.cpp for the implementation of this class
//

class CDDEServ : public CWinApp
{
public:
	CDDEServ();
    void Status(const char* pszFormat, ...);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDDEServ)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CDDEServ)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

extern CDDEServ theApp;

#define STATUS theApp.Status

/////////////////////////////////////////////////////////////////////////////
