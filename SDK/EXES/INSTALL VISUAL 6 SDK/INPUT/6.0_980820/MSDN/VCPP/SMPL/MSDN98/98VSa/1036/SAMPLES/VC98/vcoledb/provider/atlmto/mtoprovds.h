// MtoProvDS.h : Declaration of the CMtoProvSource
#ifndef __CMtoProvSource_H_
#define __CMtoProvSource_H_
#include "resource.h"       // main symbols
#include "MtoProvRS.h"

struct __declspec(uuid("E3CE8A61-8B11-11D1-9EBB-00000000FECB")) MTOEnumStruct;
//
//  ,

/////////////////////////////////////////////////////////////////////////////
// CDataSource
template <class T>
class ATL_NO_VTABLE CMtoProvSourceBase :
	public CComObjectRootEx<CComMultiThreadModel>,
	public IDBCreateSessionImpl<T, CMtoProvSession>,
	public IDBInitializeImpl<T>,
	public IDBPropertiesImpl<T>,
	public IPersistImpl<T>,
	public IInternalConnectionImpl<T>,
	public ISourcesRowset,
	public IParseDisplayName

{
public:
	HRESULT FinalConstruct()
	{
		return FInit();
	}
DECLARE_REGISTRY_RESOURCEID(IDR_MTOPROV)
BEGIN_PROPSET_MAP(CMtoProvSource)
	BEGIN_PROPERTY_SET(DBPROPSET_DATASOURCEINFO)
		PROPERTY_INFO_ENTRY(ACTIVESESSIONS)
		PROPERTY_INFO_ENTRY(DATASOURCEREADONLY)
		PROPERTY_INFO_ENTRY(BYREFACCESSORS)
		PROPERTY_INFO_ENTRY(OUTPUTPARAMETERAVAILABILITY)
		PROPERTY_INFO_ENTRY(SUPPORTEDTXNISOLEVELS)
		PROPERTY_INFO_ENTRY(USERNAME)
	END_PROPERTY_SET(DBPROPSET_DATASOURCEINFO)
	BEGIN_PROPERTY_SET(DBPROPSET_DBINIT)
		PROPERTY_INFO_ENTRY(AUTH_PASSWORD)
		PROPERTY_INFO_ENTRY(AUTH_PERSIST_SENSITIVE_AUTHINFO)
		PROPERTY_INFO_ENTRY(AUTH_USERID)
		PROPERTY_INFO_ENTRY_VALUE(INIT_DATASOURCE, OLESTR("tb2"))
		PROPERTY_INFO_ENTRY(INIT_HWND)
		PROPERTY_INFO_ENTRY(INIT_LCID)
		PROPERTY_INFO_ENTRY(INIT_LOCATION)
		PROPERTY_INFO_ENTRY(INIT_MODE)
		PROPERTY_INFO_ENTRY(INIT_PROMPT)
		PROPERTY_INFO_ENTRY(INIT_PROVIDERSTRING)
		PROPERTY_INFO_ENTRY(INIT_TIMEOUT)
	END_PROPERTY_SET(DBPROPSET_DBINIT)
	CHAIN_PROPERTY_SET(CMtoProvCommand)
END_PROPSET_MAP()

	STDMETHOD(GetSourcesRowset)(IUnknown *pUnkOuter, REFIID riid,
								ULONG cProperties,DBPROPSET rgProperties[],
								IUnknown **ppSourcesRowset);

	STDMETHOD(ParseDisplayName)(IBindCtx *pbc, LPOLESTR pszDisplayName,
								ULONG *pchEaten, IMoniker **ppmkOut)
	{
		ATLTRACE("CMTOEnum::ParseDisplayName\n");
		if (pchEaten = NULL)
			pchEaten = (ULONG*)_alloca(sizeof(ULONG));
		*pchEaten = lstrlenW(pszDisplayName);
		return CreatePointerMoniker(GetUnknown(), ppmkOut);
	}

BEGIN_COM_MAP(CMtoProvSourceBase<T>)
	COM_INTERFACE_ENTRY(IDBCreateSession)
	COM_INTERFACE_ENTRY(IDBInitialize)
	COM_INTERFACE_ENTRY(IDBProperties)
	COM_INTERFACE_ENTRY(IPersist)
	COM_INTERFACE_ENTRY(IInternalConnection)
	COM_INTERFACE_ENTRY(IParseDisplayName)
	COM_INTERFACE_ENTRY(ISourcesRowset)
END_COM_MAP()
public:

};

class CMtoProvSource :
	public CMtoProvSourceBase<CMtoProvSource>,
	public CComCoClass<CMtoProvSource, &CLSID_MtoProv>
{
public:
};

class CMtoProvSourceEnum :
	public CMtoProvSourceBase<CMtoProvSourceEnum>,
	public CComCoClass<CMtoProvSourceEnum, &__uuidof(MTOEnumStruct)>
{
public:
};

class CMtoEnumRowset : public CRowsetImpl< CMtoEnumRowset, CEnumRowsetImpl, CMtoProvCommand>
{
public:
	HRESULT Execute(DBPARAMS * , LONG* pcRowsAffected)
	{
		CEnumRowsetImpl rs;

		lstrcpyW(rs.m_szSourcesName, OLESTR("testing"));
		lstrcpyW(rs.m_szSourcesParseName, OLESTR("one"));
		lstrcpyW(rs.m_szSourcesDescription, OLESTR("two"));
		rs.m_iType = DBSOURCETYPE_DATASOURCE;
		rs.m_bIsParent = VARIANT_FALSE;
		if (!m_rgRowData.Add(rs))
			return E_OUTOFMEMORY;
		*pcRowsAffected  = 1;
		return S_OK;
	}
};

template <class T>
HRESULT CMtoProvSourceBase<T>::GetSourcesRowset(IUnknown *pUnkOuter, REFIID riid,
							ULONG cProperties,DBPROPSET rgProperties[],
							IUnknown **ppSourcesRowset)
{
	ATLTRACE("CMTOEnum::GetSourcesRowset\n");
//  typedef CSessionRowsetCreator<CMtoProvSource, CMtoEnumRowset> CMtoEnumRowsetCreator;
//  return CMtoEnumRowsetCreator::CreateRowset(pUnkOuter, NULL, NULL, riid, cProperties, rgProperties, (CMtoProvSource*)this, ppSourcesRowset);
	return S_OK;
}

#endif //__CMtoProvSource_H_
