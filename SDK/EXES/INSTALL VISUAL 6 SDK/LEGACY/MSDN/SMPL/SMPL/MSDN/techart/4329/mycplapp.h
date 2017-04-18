// MyCplApp.h : main header file for the MYCPLAPP DLL
//

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif
#ifdef IDC_STATIC
#undef IDC_STATIC
#endif
#include "resource.h"
#include "mypanel.h"
#include "mydialog.h"

/////////////////////////////////////////////////////////////////////////////
// CMyCplAppApp
// See MyCplApp.cpp for the implementation of this class
//

class CMyCplAppApp : public CWinApp
{
public:
	CMyCplAppApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyCplAppApp)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CMyCplAppApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

    // local data
    CMyPanel m_Control;
};


/////////////////////////////////////////////////////////////////////////////
