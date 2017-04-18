// BaseLevelGetterDLL.h : main header file for the BASELEVELGETTERDLL DLL
//

#if !defined(AFX_BASELEVELGETTERDLL_H__C20EA04B_F61C_11D0_A25F_000000000000__INCLUDED_)
#define AFX_BASELEVELGETTERDLL_H__C20EA04B_F61C_11D0_A25F_000000000000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CBaseLevelGetterDLLApp
// See BaseLevelGetterDLL.cpp for the implementation of this class
//

class CBaseLevelGetterDLLApp : public CWinApp
{
public:
	CBaseLevelGetterDLLApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBaseLevelGetterDLLApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CBaseLevelGetterDLLApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BASELEVELGETTERDLL_H__C20EA04B_F61C_11D0_A25F_000000000000__INCLUDED_)
