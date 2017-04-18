// DlgProxy.cpp : implementation file
//

#include "stdafx.h"
#include "LevelViewer.h"
#include "DlgProxy.h"
#include "LevelViewerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLevelViewerDlgAutoProxy

IMPLEMENT_DYNCREATE(CLevelViewerDlgAutoProxy, CCmdTarget)

CLevelViewerDlgAutoProxy::CLevelViewerDlgAutoProxy()
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
	ASSERT_KINDOF(CLevelViewerDlg, AfxGetApp()->m_pMainWnd);
	m_pDialog = (CLevelViewerDlg*) AfxGetApp()->m_pMainWnd;
	m_pDialog->m_pAutoProxy = this;
}

CLevelViewerDlgAutoProxy::~CLevelViewerDlgAutoProxy()
{
	// To terminate the application when all objects created with
	// 	with OLE automation, the destructor calls AfxOleUnlockApp.
	//  Among other things, this will destroy the main dialog
	AfxOleUnlockApp();
}

void CLevelViewerDlgAutoProxy::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CCmdTarget::OnFinalRelease();
}

BEGIN_MESSAGE_MAP(CLevelViewerDlgAutoProxy, CCmdTarget)
	//{{AFX_MSG_MAP(CLevelViewerDlgAutoProxy)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CLevelViewerDlgAutoProxy, CCmdTarget)
	//{{AFX_DISPATCH_MAP(CLevelViewerDlgAutoProxy)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_ILevelViewer to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {74234459-F528-11D0-A980-0020182A7050}
static const IID IID_ILevelViewer =
{ 0x74234459, 0xf528, 0x11d0, { 0xa9, 0x80, 0x0, 0x20, 0x18, 0x2a, 0x70, 0x50 } };

BEGIN_INTERFACE_MAP(CLevelViewerDlgAutoProxy, CCmdTarget)
	INTERFACE_PART(CLevelViewerDlgAutoProxy, IID_ILevelViewer, Dispatch)
END_INTERFACE_MAP()

// The IMPLEMENT_OLECREATE2 macro is defined in StdAfx.h of this project
// {74234457-F528-11D0-A980-0020182A7050}
IMPLEMENT_OLECREATE2(CLevelViewerDlgAutoProxy, "LevelViewer.Application", 0x74234457, 0xf528, 0x11d0, 0xa9, 0x80, 0x0, 0x20, 0x18, 0x2a, 0x70, 0x50)

/////////////////////////////////////////////////////////////////////////////
// CLevelViewerDlgAutoProxy message handlers
