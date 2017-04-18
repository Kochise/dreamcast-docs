//--------------------------------------------------------------------
// Microsoft ADO Samples
//
// (c) 1996 Microsoft Corporation.  All Rights Reserved.
//
// @doc ADORead Sample
//
// @module	ADOread.h
//
// @devnote None
//--------------------------------------------------------------------
// ADORead.h : main header file for the ADOREAD application
//

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include <objbase.h>
#include <afxdisp.h>
#include <tchar.h>			// Unicode
//#include <ado.h>			// ADO C++ header
#include "adoint.h"			// ADO C++ header
#include "adoid.h"			// ADO C++ header

/////////////////////////////////////////////////////////////////////////////
// CADOReadApp:
// See ADORead.cpp for the implementation of this class
//

class CADOReadApp : public CWinApp
{
public:
	CADOReadApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CADOReadApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CADOReadApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
