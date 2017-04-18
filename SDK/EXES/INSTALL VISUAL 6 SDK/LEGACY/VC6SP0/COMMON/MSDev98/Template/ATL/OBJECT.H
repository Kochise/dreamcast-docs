[!if=(FreeThreadedMarshaler, "TRUE")]
	[!set(NeedsGetControllingUnknown, "TRUE")]
[!endif]
// [!HeaderName] : Declaration of the [!ClassName]
[!crlf]

[!if=(FileExists, "FALSE")]
#ifndef __[!UpperShortName]_H_
#define __[!UpperShortName]_H_
[!crlf]
#include "resource.h"       // main symbols
[!else]
[!AddIncludeFile(TargetFile, "resource.h")]
[!endif]

[!crlf]
/////////////////////////////////////////////////////////////////////////////
// [!ClassName]

class ATL_NO_VTABLE [!ClassName] : 
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
	public CComCoClass<[!ClassName], &CLSID_[!CoClassName]>,
[!if=(IOBJECTWITHSITE, "TRUE")]
	public IObjectWithSiteImpl<[!ClassName]>,
[!endif]
[!if=(ISERVICEPROVIDER, "TRUE")]
	public IServiceProviderImpl<[!ClassName]>,
[!endif]

[!if=(ErrorInfoEnabled, "TRUE")]
	public ISupportErrorInfo,
[!endif]
[!if=(ConnectionPointsEnabled, "TRUE")]
	public IConnectionPointContainerImpl<[!ClassName]>,
[!endif]

[!if=(IPERSISTSTORAGE, "TRUE")]
	public IPersistStorageImpl<[!ClassName]>,
[!endif]
[!if=(ISPECIFYPROPERTYPAGES, "TRUE")]
	public ISpecifyPropertyPagesImpl<[!ClassName]>,
[!endif]
[!if=(IDATAOBJECT, "TRUE")]
	public IDataObjectImpl<[!ClassName]>,
[!endif]
[!if=(ConnectionPointsEnabled, "TRUE")]
[!if=(IPROVIDECLASSINFO2, "TRUE")]
	public IProvideClassInfo2Impl<&CLSID_[!CoClassName], &DIID__[!InterfaceName]Events, &LIBID_[!LibName]>,
[!endif]
[!if=(IPROPERTYNOTIFYSINK, "TRUE")]
	public IPropertyNotifySinkCP<[!ClassName]>,
[!endif]
[!else]
[!if=(IPROVIDECLASSINFO2, "TRUE")]
	public IProvideClassInfo2Impl<&CLSID_[!CoClassName], [!ConnectionPointInterface], &LIBID_[!LibName]>,
[!endif]
[!endif]
[!if=(Dual, "TRUE")]
	public IDispatchImpl<[!InterfaceName], &IID_[!InterfaceName], &LIBID_[!LibName]>
[!else]
	public [!InterfaceName]
[!endif]
{
public:
	[!ClassName]()
	{
[!if=(FreeThreadedMarshaler, "TRUE")]
		m_pUnkMarshaler = NULL;
[!endif]
	}

[!crlf]
DECLARE_REGISTRY_RESOURCEID([!IDR_REGISTRYID])

[!if=(Aggregatable, "NO")]
DECLARE_NOT_AGGREGATABLE([!ClassName])
[!endif]
[!if=(Aggregatable, "ONLY")]
DECLARE_ONLY_AGGREGATABLE([!ClassName])
[!endif]

[!if=(NeedsGetControllingUnknown, "TRUE")]
DECLARE_GET_CONTROLLING_UNKNOWN()
[!endif]
[!crlf]
DECLARE_PROTECT_FINAL_CONSTRUCT()

[!crlf]
BEGIN_COM_MAP([!ClassName])
	COM_INTERFACE_ENTRY([!InterfaceName])
[!if=(Dual, "TRUE")]
	COM_INTERFACE_ENTRY(IDispatch)
[!endif]
[!if=(ErrorInfoEnabled, "TRUE")]
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
[!endif]
[!if=(ConnectionPointsEnabled, "TRUE")]
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
[!endif]
[!if=(FreeThreadedMarshaler, "TRUE")]
	COM_INTERFACE_ENTRY_AGGREGATE(IID_IMarshal, m_pUnkMarshaler.p)
[!endif]
[!if=(ISPECIFYPROPERTYPAGES, "TRUE")]
	COM_INTERFACE_ENTRY_IMPL(ISpecifyPropertyPages)
[!endif]
[!if=(IPERSISTSTORAGE, "TRUE")]
	COM_INTERFACE_ENTRY_IMPL(IPersistStorage)
[!endif]
[!if=(IDATAOBJECT, "TRUE")]
	COM_INTERFACE_ENTRY_IMPL(IDataObject)
[!endif]
[!if=(IPROVIDECLASSINFO2, "TRUE")]
	COM_INTERFACE_ENTRY(IProvideClassInfo)
	COM_INTERFACE_ENTRY(IProvideClassInfo2)
[!endif]

[!if=(IOBJECTWITHSITE, "TRUE")]
	COM_INTERFACE_ENTRY(IObjectWithSite)
[!endif]
[!if=(ISERVICEPROVIDER, "TRUE")]
	COM_INTERFACE_ENTRY(IServiceProvider)
[!endif]

END_COM_MAP()

[!if=(ConnectionPointsEnabled, "TRUE")]
BEGIN_CONNECTION_POINT_MAP([!ClassName])
[!if=(IPROPERTYNOTIFYSINK, "TRUE")]
	CONNECTION_POINT_ENTRY(IID_IPropertyNotifySink)
[!endif]
END_CONNECTION_POINT_MAP()
[!crlf]
[!endif]

[!if=(FreeThreadedMarshaler, "TRUE")]
[!crlf]
	HRESULT FinalConstruct()
	{
		return CoCreateFreeThreadedMarshaler(
			GetControllingUnknown(), &m_pUnkMarshaler.p);
	}

[!crlf]
	void FinalRelease()
	{
		m_pUnkMarshaler.Release();
	}

[!crlf]
	CComPtr<IUnknown> m_pUnkMarshaler;
[!endif]

[!if=(ErrorInfoEnabled, "TRUE")]
[!crlf]
// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);
[!endif]

[!crlf]
[!if=(ISERVICEPROVIDER, "TRUE")]
	STDMETHOD(_InternalQueryService)(REFGUID guidService, REFIID riid, void** ppvObject)
	{
		return E_NOTIMPL;
	}
[!crlf]
[!endif]

// [!InterfaceName]
public:

};

[!crlf]
[!if=(FileExists, "FALSE")]
#endif //__[!UpperShortName]_H_
[!endif]
