// [!DataSourceFile] : Declaration of the [!DataSource]

[!if=(FileExists, "FALSE")]
#ifndef __[!DataSource]_H_
#define __[!DataSource]_H_

#include "resource.h"       // main symbols
#include "[!RowsetFile]"
[!else]
[!AddIncludeFile(TargetFile, "resource.h")]
[!AddIncludeFile(TargetFile, RowsetFile)]
[!endif]
/////////////////////////////////////////////////////////////////////////////
// CDataSource
class ATL_NO_VTABLE [!DataSource] : 
[!if=(ThreadingModel, "Single")]
	public CComObjectRootEx<CComSingleThreadModel>,
[!endif]
[!if=(ThreadingModel, "Apartment")]
	public CComObjectRootEx<CComSingleThreadModel>,
[!endif]
[!if=(ThreadingModel, "Both")]
	public CComObjectRootEx<CComMultiThreadModel>,
[!endif]
[!if=(ThreadingModel, "Free")]
	public CComObjectRootEx<CComMultiThreadModel>,
[!endif]
	public CComCoClass<[!DataSource], &CLSID_[!CoClassName]>,
	public IDBCreateSessionImpl<[!DataSource], [!Session]>,
	public IDBInitializeImpl<[!DataSource]>,
	public IDBPropertiesImpl<[!DataSource]>,
	public IPersistImpl<[!DataSource]>,
	public IInternalConnectionImpl<[!DataSource]>
{
public:
	HRESULT FinalConstruct()
	{
		return FInit();
	}

DECLARE_REGISTRY_RESOURCEID([!IDR_REGISTRYID])
BEGIN_PROPSET_MAP([!DataSource])
	BEGIN_PROPERTY_SET(DBPROPSET_DATASOURCEINFO)
		PROPERTY_INFO_ENTRY(ACTIVESESSIONS)
		PROPERTY_INFO_ENTRY(DATASOURCEREADONLY)
		PROPERTY_INFO_ENTRY(BYREFACCESSORS)
		PROPERTY_INFO_ENTRY(OUTPUTPARAMETERAVAILABILITY)
		PROPERTY_INFO_ENTRY(PROVIDEROLEDBVER)
		PROPERTY_INFO_ENTRY(DSOTHREADMODEL)
		PROPERTY_INFO_ENTRY(SUPPORTEDTXNISOLEVELS)
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
		PROPERTY_INFO_ENTRY(INIT_MODE)
		PROPERTY_INFO_ENTRY(INIT_PROMPT)
		PROPERTY_INFO_ENTRY(INIT_PROVIDERSTRING)
		PROPERTY_INFO_ENTRY(INIT_TIMEOUT)
	END_PROPERTY_SET(DBPROPSET_DBINIT)
	CHAIN_PROPERTY_SET([!Command])
END_PROPSET_MAP()

BEGIN_COM_MAP([!DataSource])
	COM_INTERFACE_ENTRY(IDBCreateSession)
	COM_INTERFACE_ENTRY(IDBInitialize)
	COM_INTERFACE_ENTRY(IDBProperties)
	COM_INTERFACE_ENTRY(IPersist)
	COM_INTERFACE_ENTRY(IInternalConnection)
END_COM_MAP()

public:
};

[!if=(FileExists, "FALSE")]
#endif //__[!DataSource]_H_
[!endif]

