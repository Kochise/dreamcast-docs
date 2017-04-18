// DataSrc.h : Declaration of the CDirDataSource
//
// This is a part of the ActiveX Template Library.
// Copyright (C) 1998 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// ActiveX Template Library Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// ActiveX Template Library product.

#ifndef __DATASOURCE_H_
#define __DATASOURCE_H_

#include "resource.h"       // main symbols
#include "rowset.h"
/////////////////////////////////////////////////////////////////////////////
// CDirDataSource
class ATL_NO_VTABLE CDirDataSource :
	public CComObjectRootEx<CComMultiThreadModel>,
	public IPersistImpl<CDirDataSource>,
	public IDBInitializeImpl<CDirDataSource>,
	public IDBCreateSessionImpl<CDirDataSource, CDirSession>,
	public IDBPropertiesImpl<CDirDataSource>,
	public CComCoClass<CDirDataSource, &CLSID_DataSource>,
	public IInternalConnectionImpl<CDirDataSource>
{
public:
	CDirDataSource()
	{
	}
	HRESULT FinalConstruct()
	{
		return FInit();
	}

DECLARE_REGISTRY_RESOURCEID(IDR_DATASOURCE)


BEGIN_PROPSET_MAP(CDirDataSource)
	BEGIN_PROPERTY_SET(DBPROPSET_DATASOURCEINFO)
		PROPERTY_INFO_ENTRY(ACTIVESESSIONS)
		PROPERTY_INFO_ENTRY(DATASOURCEREADONLY)
		PROPERTY_INFO_ENTRY(BYREFACCESSORS)
		PROPERTY_INFO_ENTRY(OUTPUTPARAMETERAVAILABILITY)
		PROPERTY_INFO_ENTRY(PROVIDEROLEDBVER)
		PROPERTY_INFO_ENTRY(DSOTHREADMODEL)
		PROPERTY_INFO_ENTRY(USERNAME)
	END_PROPERTY_SET(DBPROPSET_DATASOURCEINFO)
	BEGIN_PROPERTY_SET(DBPROPSET_DBINIT)
		PROPERTY_INFO_ENTRY(AUTH_PASSWORD)
		PROPERTY_INFO_ENTRY(AUTH_PERSIST_SENSITIVE_AUTHINFO)
		PROPERTY_INFO_ENTRY(AUTH_USERID)
		PROPERTY_INFO_ENTRY(INIT_DATASOURCE)
		PROPERTY_INFO_ENTRY(INIT_HWND)
		PROPERTY_INFO_ENTRY(INIT_LCID)
		PROPERTY_INFO_ENTRY(INIT_LOCATION)
		PROPERTY_INFO_ENTRY(INIT_PROVIDERSTRING)
	END_PROPERTY_SET(DBPROPSET_DBINIT)
	CHAIN_PROPERTY_SET(CDirCommand)
END_PROPSET_MAP()

	typedef IDBCreateSessionImpl<CDirDataSource,CDirSession> DBCreateSessionClass;

BEGIN_COM_MAP(CDirDataSource)
	COM_INTERFACE_ENTRY(IPersist)
	COM_INTERFACE_ENTRY_IID(IID_IDBCreateSession, DBCreateSessionClass)
	COM_INTERFACE_ENTRY(IDBInitialize)
	COM_INTERFACE_ENTRY(IDBProperties)
	COM_INTERFACE_ENTRY(IInternalConnection)
END_COM_MAP()

};

#endif //__DATASOURCE_H_
