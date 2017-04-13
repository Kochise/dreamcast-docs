// DlgProxy.cpp : TV Viewer sample application
//
// Copyright (C) 1997 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Broadcast Architecture Programmer's Reference.
// For detailed information regarding Broadcast
// Architecture, see the reference.
// implementation file
//

#include "stdafx.h"
#include "TVXSamp.h"
#include "DlgProxy.h"
#include "TVXSampDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTVXSampDlgAutoProxy

IMPLEMENT_DYNCREATE(CTVXSampDlgAutoProxy, CCmdTarget)

CTVXSampDlgAutoProxy::CTVXSampDlgAutoProxy()
{
	EnableAutomation();
	
	// To keep the application running as long as an OLE automation 
	//	object is active, the constructor calls AfxOleLockApp.
	AfxOleLockApp();

	// Get access to the dialog through the application's
	//  main window pointer.  Set the proxy's internal pointer
	//  to point to the dialog, and set the dialog's back pointer to
	//  this proxy.
	ASSERT (AfxGetApp()->m_pMainWnd != NULL);
	ASSERT_VALID (AfxGetApp()->m_pMainWnd);
	ASSERT_KINDOF(CTVXSampDlg, AfxGetApp()->m_pMainWnd);
	m_pDialog = (CTVXSampDlg*) AfxGetApp()->m_pMainWnd;
	m_pDialog->m_pAutoProxy = this;
}

CTVXSampDlgAutoProxy::~CTVXSampDlgAutoProxy()
{
	// To terminate the application when all objects created with
	// 	with OLE automation, the destructor calls AfxOleUnlockApp.
	//  Among other things, this will destroy the main dialog
	AfxOleUnlockApp();
}

void CTVXSampDlgAutoProxy::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CCmdTarget::OnFinalRelease();
}

BEGIN_MESSAGE_MAP(CTVXSampDlgAutoProxy, CCmdTarget)
	//{{AFX_MSG_MAP(CTVXSampDlgAutoProxy)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CTVXSampDlgAutoProxy, CCmdTarget)
	//{{AFX_DISPATCH_MAP(CTVXSampDlgAutoProxy)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_ITVXSamp to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {FF521024-0CE4-11D1-98AE-080009DC95C5}
static const IID IID_ITVXSamp =
{ 0xff521024, 0xce4, 0x11d1, { 0x98, 0xae, 0x8, 0x0, 0x9, 0xdc, 0x95, 0xc5 } };

BEGIN_INTERFACE_MAP(CTVXSampDlgAutoProxy, CCmdTarget)
	INTERFACE_PART(CTVXSampDlgAutoProxy, IID_ITVXSamp, Dispatch)
END_INTERFACE_MAP()

// The IMPLEMENT_OLECREATE2 macro is defined in StdAfx.h of this project
// {FF521022-0CE4-11D1-98AE-080009DC95C5}
IMPLEMENT_OLECREATE2(CTVXSampDlgAutoProxy, "TVXSamp.Application", 0xff521022, 0xce4, 0x11d1, 0x98, 0xae, 0x8, 0x0, 0x9, 0xdc, 0x95, 0xc5)

/////////////////////////////////////////////////////////////////////////////
// CTVXSampDlgAutoProxy message handlers
