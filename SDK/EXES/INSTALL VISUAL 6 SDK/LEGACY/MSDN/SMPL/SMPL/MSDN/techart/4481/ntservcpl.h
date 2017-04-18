// NTServCpl.h : main header file for the NTSERVCPL DLL
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
// CNTServCplApp
// See NTServCpl.cpp for the implementation of this class
//

class CNTServCplApp : public CWinApp
{
public:
	CNTServCplApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNTServCplApp)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CNTServCplApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

    CMyPanel m_Control;
};


/////////////////////////////////////////////////////////////////////////////
