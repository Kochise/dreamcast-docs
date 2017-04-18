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
//	Implementation of IErrorLog through XVErrorLog nested class to be used 
//	in some method calls.

#include "stdafx.h"
#include "vcontain.h"
#include "vcerrlog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CErrorLog

IMPLEMENT_DYNCREATE(CErrorLog, CCmdTarget)

CErrorLog::CErrorLog()
{
}

CErrorLog::~CErrorLog()
{
}


BEGIN_MESSAGE_MAP(CErrorLog, CCmdTarget)
	//{{AFX_MSG_MAP(CErrorLog)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CErrorLog message handlers
BEGIN_INTERFACE_MAP(CErrorLog, CCmdTarget)
    INTERFACE_PART(CErrorLog, IID_IErrorLog, VErrorLog)
END_INTERFACE_MAP()


ULONG EXPORT CErrorLog::XVErrorLog::AddRef ()
{
    METHOD_PROLOGUE(CErrorLog, VErrorLog)
    return pThis->ExternalAddRef();
}

ULONG EXPORT CErrorLog::XVErrorLog::Release ()
{
    METHOD_PROLOGUE(CErrorLog, VErrorLog)
    return pThis->ExternalRelease ();
}

HRESULT EXPORT CErrorLog::XVErrorLog::QueryInterface ( REFIID iid, 
													  void ** ppvObj )
{
    METHOD_PROLOGUE ( CErrorLog, VErrorLog )
    return ( HRESULT ) pThis->ExternalQueryInterface ( &iid, ppvObj );
}

STDMETHODIMP CErrorLog::XVErrorLog::AddError ( LPCOLESTR, LPEXCEPINFO )
{
	return ( HRESULT ) E_NOTIMPL;
}