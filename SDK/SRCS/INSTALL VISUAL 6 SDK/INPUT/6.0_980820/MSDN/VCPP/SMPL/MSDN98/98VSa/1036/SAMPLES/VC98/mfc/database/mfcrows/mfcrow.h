// MFCRow.h : main header file for the MFCROW application
//
// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) 1992-1998 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.

#if !defined(AFX_MFCROW_H__2B60A6FC_22FC_11D1_8FD3_000000000000__INCLUDED_)
#define AFX_MFCROW_H__2B60A6FC_22FC_11D1_8FD3_000000000000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

// Make our _Module visible to everyone

extern CComModule _Module;

/////////////////////////////////////////////////////////////////////////////
// CMFCRowApp:
// See MFCRow.cpp for the implementation of this class
//

class CMFCRowApp : public CWinApp
{
public:
	CMFCRowApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMFCRowApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMFCRowApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MFCROW_H__2B60A6FC_22FC_11D1_8FD3_000000000000__INCLUDED_)
