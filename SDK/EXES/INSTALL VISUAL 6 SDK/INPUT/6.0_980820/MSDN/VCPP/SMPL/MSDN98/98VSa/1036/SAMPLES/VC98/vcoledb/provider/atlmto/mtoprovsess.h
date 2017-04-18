// Session.h : Declaration of the CMtoProvSession
#ifndef __CMtoProvSession_H_
#define __CMtoProvSession_H_
#include "resource.h"       // main symbols
#include "MtoProvRS.h"
/////////////////////////////////////////////////////////////////////////////
// CMtoProvSession
class ATL_NO_VTABLE CMtoProvSession :
	public CComObjectRootEx<CComMultiThreadModel>,
	public IGetDataSourceImpl<CMtoProvSession>,
	public IOpenRowsetImpl<CMtoProvSession>,
	public ISessionPropertiesImpl<CMtoProvSession>,
	public IObjectWithSiteImpl<CMtoProvSession>,
	public IDBCreateCommandImpl<CMtoProvSession, CMtoProvCommand>
{
public:
	CMtoProvSession()
	{
	}
	HRESULT FinalConstruct()
	{
		return FInit();
	}
	STDMETHOD(OpenRowset)(IUnknown *pUnkOuter, DBID *pTableID, DBID *pIndexID, REFIID riid,
					   ULONG cPropertySets, DBPROPSET rgPropertySets[], IUnknown **ppRowset)
	{
		CMtoProvRowset* pRowset;
		return CreateRowset(pUnkOuter, pTableID, pIndexID, riid, cPropertySets, rgPropertySets, ppRowset, pRowset);
	}
BEGIN_PROPSET_MAP(CMtoProvSession)
BEGIN_PROPERTY_SET(DBPROPSET_SESSION)
		PROPERTY_INFO_ENTRY(SESS_AUTOCOMMITISOLEVELS)
END_PROPERTY_SET(DBPROPSET_SESSION)
END_PROPSET_MAP()
BEGIN_COM_MAP(CMtoProvSession)
	COM_INTERFACE_ENTRY(IGetDataSource)
	COM_INTERFACE_ENTRY(IOpenRowset)
	COM_INTERFACE_ENTRY(ISessionProperties)
	COM_INTERFACE_ENTRY(IObjectWithSite)
	COM_INTERFACE_ENTRY(IDBCreateCommand)
END_COM_MAP()
public:
};
#endif //__CMtoProvSession_H_
