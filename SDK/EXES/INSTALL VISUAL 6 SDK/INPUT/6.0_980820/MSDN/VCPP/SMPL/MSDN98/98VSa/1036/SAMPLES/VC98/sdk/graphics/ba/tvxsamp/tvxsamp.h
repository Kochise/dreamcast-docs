// TVXSamp.h : TV Viewer sample application
//
// Copyright (C) 1997 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Broadcast Architecture Programmer's Reference.
// For detailed information regarding Broadcast
// Architecture, see the reference.
//
//
//

#if !defined(AFX_TVXSAMP_H__FF521027_0CE4_11D1_98AE_080009DC95C5__INCLUDED_)
#define AFX_TVXSAMP_H__FF521027_0CE4_11D1_98AE_080009DC95C5__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTVXSampApp:
// See TVXSamp.cpp for the implementation of this class
//

class CTVXSampApp : public CWinApp
{
public:
	CTVXSampApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTVXSampApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTVXSampApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TVXSAMP_H__FF521027_0CE4_11D1_98AE_080009DC95C5__INCLUDED_)
