// Session.h : Declaration of the CMyProviderSession
//
// This is a part of the Active Template Library.
// Copyright (C) 1998 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// ActiveX Template Library Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// ActiveX Template Library product.

#ifndef __CMyProviderSession_H_
#define __CMyProviderSession_H_
#include "resource.h"       // main symbols
#include "MyProviderRS.h"

/////////////////////////////////////////////////////////////////////////////
// CMyProviderSession
class ATL_NO_VTABLE CMyProviderSession :
	public CComObjectRootEx<CComMultiThreadModel>,
	public IGetDataSourceImpl<CMyProviderSession>,
	public IOpenRowsetImpl<CMyProviderSession>,
	public ISessionPropertiesImpl<CMyProviderSession>,
	public IObjectWithSiteSessionImpl<CMyProviderSession>,
	public IDBCreateCommandImpl<CMyProviderSession, CMyProviderCommand>
{
public:
	CMyProviderSession()
	{
	}
	HRESULT FinalConstruct()
	{
		return FInit();
	}
	STDMETHOD(OpenRowset)(IUnknown *pUnkOuter, DBID *pTableID, DBID *pIndexID, REFIID riid,
					   ULONG cPropertySets, DBPROPSET rgPropertySets[], IUnknown **ppRowset)
	{
		CAgentRowset* pAgentRS;
		return CreateRowset(pUnkOuter, pTableID, pIndexID, riid, cPropertySets, rgPropertySets, ppRowset, pAgentRS);

	}

BEGIN_PROPSET_MAP(CMyProviderSession)
	CHAIN_PROPERTY_SET(CMyProviderCommand)
END_PROPSET_MAP()

BEGIN_COM_MAP(CMyProviderSession)
	COM_INTERFACE_ENTRY(IGetDataSource)
	COM_INTERFACE_ENTRY(IOpenRowset)
	COM_INTERFACE_ENTRY(ISessionProperties)
	COM_INTERFACE_ENTRY(IObjectWithSite)
	COM_INTERFACE_ENTRY(IDBCreateCommand)
END_COM_MAP()
public:
};
#endif //__CMyProviderSession_H_
