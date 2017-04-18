// DlgProxy.h : TV Viewer sample application
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
//

#if !defined(AFX_DLGPROXY_H__FF52102B_0CE4_11D1_98AE_080009DC95C5__INCLUDED_)
#define AFX_DLGPROXY_H__FF52102B_0CE4_11D1_98AE_080009DC95C5__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CTVXSampDlg;

/////////////////////////////////////////////////////////////////////////////
// CTVXSampDlgAutoProxy command target

class CTVXSampDlgAutoProxy : public CCmdTarget
{
	DECLARE_DYNCREATE(CTVXSampDlgAutoProxy)

	CTVXSampDlgAutoProxy();           // protected constructor used by dynamic creation

// Attributes
public:
	CTVXSampDlg* m_pDialog;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTVXSampDlgAutoProxy)
	public:
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CTVXSampDlgAutoProxy();

	// Generated message map functions
	//{{AFX_MSG(CTVXSampDlgAutoProxy)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	DECLARE_OLECREATE(CTVXSampDlgAutoProxy)

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CTVXSampDlgAutoProxy)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPROXY_H__FF52102B_0CE4_11D1_98AE_080009DC95C5__INCLUDED_)
