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
//	Implementation of IDataObject through XVDataObject nested class to be 
//  used in some method calls.

#include "stdafx.h"
#include "vcontain.h"
#include "vcdatobj.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDataObject

IMPLEMENT_DYNCREATE(CDataObject, CCmdTarget)

CDataObject::CDataObject()
{
}

CDataObject::~CDataObject()
{
}


BEGIN_MESSAGE_MAP(CDataObject, CCmdTarget)
	//{{AFX_MSG_MAP(CDataObject)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


BEGIN_INTERFACE_MAP(CDataObject, CCmdTarget)
    INTERFACE_PART(CDataObject, IID_IDataObject, VDataObject)
END_INTERFACE_MAP()


ULONG  EXPORT CDataObject::XVDataObject::AddRef()
{
    METHOD_PROLOGUE ( CDataObject, VDataObject )
    return pThis->ExternalAddRef ();
}

ULONG  EXPORT CDataObject::XVDataObject::Release ()
{
    METHOD_PROLOGUE( CDataObject, VDataObject )
    return pThis->ExternalRelease ();
}

HRESULT  EXPORT CDataObject::XVDataObject::QueryInterface(REFIID iid, 
															void ** ppvObj)
{
    METHOD_PROLOGUE ( CDataObject, VDataObject )
    return ( HRESULT ) pThis->ExternalQueryInterface ( &iid, ppvObj );
}



STDMETHODIMP CDataObject::XVDataObject::QueryGetData  ( LPFORMATETC )
{
	return ( HRESULT )  E_NOTIMPL;
}


STDMETHODIMP CDataObject::XVDataObject::DAdvise  ( FORMATETC  *, DWORD, 
													LPADVISESINK , DWORD * )
{
	return ( HRESULT )  E_NOTIMPL;
}


STDMETHODIMP CDataObject::XVDataObject::GetData  ( LPFORMATETC, LPSTGMEDIUM  )
{
	return ( HRESULT )  E_NOTIMPL;
}


STDMETHODIMP CDataObject::XVDataObject::DUnadvise  ( DWORD )
{
	return ( HRESULT ) E_NOTIMPL;
}


STDMETHODIMP CDataObject::XVDataObject::GetDataHere  ( LPFORMATETC, LPSTGMEDIUM  )
{
	return ( HRESULT ) E_NOTIMPL;
}


STDMETHODIMP CDataObject::XVDataObject::GetCanonicalFormatEtc  ( LPFORMATETC, 
																	LPFORMATETC )
{
	return ( HRESULT )  E_NOTIMPL;
}


STDMETHODIMP CDataObject::XVDataObject::SetData  ( LPFORMATETC, STGMEDIUM *,
																			BOOL )
{
	return ( HRESULT )  E_NOTIMPL;
}


STDMETHODIMP CDataObject::XVDataObject::EnumFormatEtc  ( DWORD, 
															LPENUMFORMATETC * )
{
	return ( HRESULT )  E_NOTIMPL;
}


STDMETHODIMP CDataObject::XVDataObject::EnumDAdvise  ( LPENUMSTATDATA * )
{
	return ( HRESULT )  E_NOTIMPL;
}

