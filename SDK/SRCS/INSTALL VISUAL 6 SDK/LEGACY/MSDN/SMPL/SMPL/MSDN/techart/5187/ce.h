//////////////////////////////////////////////////////////////////////////////
// CE.h				- Copyright (C) 1997 Microsoft Corporation				//
//					- All rights reserved.									//
// Date				- 12/11/97												//
// Purpose			- Header for main application file						//
//////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CE_H__0B2CE6F5_71A5_11D1_B887_00AA00C0803B__INCLUDED_)
#define AFX_CE_H__0B2CE6F5_71A5_11D1_B887_00AA00C0803B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

class CCEApp : public CWinApp
{
public:
	CCEApp(LPCTSTR lpszAppName);

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCEApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CCEApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};




//{{AFX_INSERT_LOCATION}}

#endif // !defined(AFX_CE_H__0B2CE6F5_71A5_11D1_B887_00AA00C0803B__INCLUDED_)
