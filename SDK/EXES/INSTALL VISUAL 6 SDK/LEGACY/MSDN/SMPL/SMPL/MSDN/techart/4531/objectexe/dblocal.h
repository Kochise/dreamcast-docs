// DBLocal.h : main header file for the DBLOCAL application
//

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CDBLocalApp:
// See DBLocal.cpp for the implementation of this class
//

class CDB;

class CDBLocalApp : public CWinApp
{
	friend CDB;

public:
	CDBLocalApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDBLocalApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
	DWORD m_dwDBFactory;
	CDocument* m_pLastDoc;

	//{{AFX_MSG(CDBLocalApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
