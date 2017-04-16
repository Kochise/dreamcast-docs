//OLE Control Container Verification Application, Version 1.00
//
//Copyright (c) 1995-6 Microsoft Corp, All Rights Reserved
//
//	This is a part of the Microsoft Source Code Samples.
//	This source code is only intended as a supplement to
//	the Microsoft Development Tools and/or WinHelp implementation.
//	See these sources for detailed information regarding the
//	Microsoft sample programs.
//
//Revisions:
//	November 30, 1995	mtm		First Implementation
//
//Purpose:
//	Implementation of CPropertyBag class.  

	
#include "stdafx.h"
#include "vcontain.h"
#include "vcprpbag.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPropertyBag

IMPLEMENT_DYNCREATE(CPropertyBag, CCmdTarget)

CPropertyBag::CPropertyBag ()
{
}

CPropertyBag::~CPropertyBag ()
{
}


BEGIN_MESSAGE_MAP(CPropertyBag, CCmdTarget)
	//{{AFX_MSG_MAP(CPropertyBag)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPropertyBag message handlers

BEGIN_INTERFACE_MAP(CPropertyBag, CCmdTarget)
    INTERFACE_PART(CPropertyBag, IID_IPropertyBag, VPropertyBag)
END_INTERFACE_MAP()


ULONG  EXPORT CPropertyBag::XVPropertyBag::AddRef ()
{
    METHOD_PROLOGUE( CPropertyBag, VPropertyBag )
    return pThis->ExternalAddRef ();
}

ULONG  EXPORT CPropertyBag::XVPropertyBag::Release ()
{
    METHOD_PROLOGUE( CPropertyBag, VPropertyBag )
    return pThis->ExternalRelease ();
}

HRESULT  EXPORT CPropertyBag::XVPropertyBag::QueryInterface( REFIID iid, 
														void ** ppvObj )
{
    METHOD_PROLOGUE( CPropertyBag, VPropertyBag )
    return ( HRESULT ) pThis->ExternalQueryInterface( &iid, ppvObj);
}


STDMETHODIMP CPropertyBag::XVPropertyBag::Read ( LPCOLESTR, LPVARIANT,
														LPERRORLOG )
{
	return ( HRESULT) E_NOTIMPL;
}


STDMETHODIMP CPropertyBag::XVPropertyBag::Write ( LPCOLESTR, LPVARIANT )
{
	return ( HRESULT) E_NOTIMPL;
}