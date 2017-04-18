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
//	Implementation of IAdviseSink through XVAdvSink nested class to be used 
//  in some method calls.

#include "stdafx.h"
#include "vcontain.h"
#include "vcadvsnk.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAdvSink

IMPLEMENT_DYNCREATE(CAdvSink, CCmdTarget)

CAdvSink::CAdvSink()
{
}

CAdvSink::~CAdvSink()
{
}


BEGIN_MESSAGE_MAP(CAdvSink, CCmdTarget)
	//{{AFX_MSG_MAP(CAdvSink)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


BEGIN_INTERFACE_MAP(CAdvSink, CCmdTarget)
    INTERFACE_PART(CAdvSink, IID_IAdviseSink, VAdvSink)
END_INTERFACE_MAP()


ULONG  EXPORT CAdvSink::XVAdvSink::AddRef ()
{
    METHOD_PROLOGUE ( CAdvSink, VAdvSink )
    return pThis->ExternalAddRef();
}

ULONG  EXPORT CAdvSink::XVAdvSink::Release ()
{
    METHOD_PROLOGUE( CAdvSink, VAdvSink )
    return pThis->ExternalRelease();
}

HRESULT EXPORT CAdvSink::XVAdvSink::QueryInterface( REFIID iid, 
															void ** ppvObj )
{
    METHOD_PROLOGUE( CAdvSink, VAdvSink )
    return ( HRESULT ) pThis->ExternalQueryInterface( &iid, ppvObj );
}


void __stdcall CAdvSink::XVAdvSink::OnClose (  )
{
}


void __stdcall CAdvSink::XVAdvSink::OnDataChange ( FORMATETC *, STGMEDIUM * )
{
}


void __stdcall CAdvSink::XVAdvSink::OnRename ( IMoniker * )
{
}


void __stdcall CAdvSink::XVAdvSink::OnSave (  )
{
}


void __stdcall CAdvSink::XVAdvSink::OnViewChange ( DWORD , LONG )
{
}


