//--------------------------------------------------------------------
// Microsoft ADO Samples
//
// (c) 1996 Microsoft Corporation.  All Rights Reserved.
//
// @doc GetRows Sample
//
// @module	getrows.h
//
// @devnote None
//--------------------------------------------------------------------

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include <objbase.h>
#include <afxdisp.h>
#include <tchar.h>			// Unicode
#include <adoid.h>			// ADO C++ header	 
#include <adoint.h>			// ADO C++ header

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CGetRowsApp:
// See GetRows.cpp for the implementation of this class
//

class CGetRowsApp : public CWinApp
{
public:
	CGetRowsApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGetRowsApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CGetRowsApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
