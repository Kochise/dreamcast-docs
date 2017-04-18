// HotTubLevelGetterDLL.h : main header file for the HOTTUBLEVELGETTERDLL DLL
//

#if !defined(AFX_HOTTUBLEVELGETTERDLL_H__34CA0A49_F81C_11D0_8FE8_00409500EFA8__INCLUDED_)
#define AFX_HOTTUBLEVELGETTERDLL_H__34CA0A49_F81C_11D0_8FE8_00409500EFA8__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CHotTubLevelGetterDLLApp
// See HotTubLevelGetterDLL.cpp for the implementation of this class
//

class CHotTubLevelGetterDLLApp : public CWinApp
{
public:
	CHotTubLevelGetterDLLApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHotTubLevelGetterDLLApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CHotTubLevelGetterDLLApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HOTTUBLEVELGETTERDLL_H__34CA0A49_F81C_11D0_8FE8_00409500EFA8__INCLUDED_)
