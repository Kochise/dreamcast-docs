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
#include <asptlb.h>         // Active Server Pages Definitions
[!else]
[!AddIncludeFile(TargetFile, "resource.h")]
[!AddIncludeFile(TargetFile, "<asptlb.h>")]
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
[!if=(ErrorInfoEnabled, "TRUE")]
	public ISupportErrorInfo,
[!endif]
[!if=(ConnectionPointsEnabled, "TRUE")]
	public IConnectionPointContainerImpl<[!ClassName]>,
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
[!if=(FreeThreadedMarshaler, "TRUE")]		m_pUnkMarshaler = NULL;[!endif]
[!if=(OnStartPage, "TRUE")]		m_bOnStartPageCalled = FALSE;[!endif]
	}
[!crlf]
public:
[!crlf]
DECLARE_REGISTRY_RESOURCEID([!IDR_REGISTRYID])
[!crlf]
DECLARE_PROTECT_FINAL_CONSTRUCT()

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
END_COM_MAP()

[!if=(ConnectionPointsEnabled, "TRUE")]
[!crlf]
BEGIN_CONNECTION_POINT_MAP([!ClassName])
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
// [!InterfaceName]
public:
[!if=(OnStartPage, "TRUE")]
	//Active Server Pages Methods
	STDMETHOD(OnStartPage)(IUnknown* IUnk);
	STDMETHOD(OnEndPage)();
[!crlf]
private:
[!if=(Request, "TRUE")]
	CComPtr<IRequest> m_piRequest;					//Request Object
[!endif]
[!if=(Response, "TRUE")]
	CComPtr<IResponse> m_piResponse;				//Response Object
[!endif]
[!if=(Session, "TRUE")]
	CComPtr<ISessionObject> m_piSession;			//Session Object
[!endif]
[!if=(Server, "TRUE")]
	CComPtr<IServer> m_piServer;					//Server Object
[!endif]
[!if=(Application, "TRUE")]
	CComPtr<IApplicationObject> m_piApplication;	//Application Object
[!endif]
	BOOL m_bOnStartPageCalled;						//OnStartPage successful?
[!endif]
};

[!crlf]
[!if=(FileExists, "FALSE")]
#endif //__[!UpperShortName]_H_
[!endif]
