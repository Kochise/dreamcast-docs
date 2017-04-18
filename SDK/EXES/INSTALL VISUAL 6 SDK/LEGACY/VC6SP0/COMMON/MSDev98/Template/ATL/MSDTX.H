// [!HeaderName] : Declaration of the [!ClassName]
[!crlf]

[!if=(FileExists, "FALSE")]
#ifndef __[!UpperShortName]_H_
#define __[!UpperShortName]_H_
[!crlf]
#include "resource.h"       // main symbols
#include <mtx.h>
[!else]
[!AddIncludeFile(TargetFile, "resource.h")]
[!AddIncludeFile(TargetFile, "<mtx.h>")]
[!endif]
[!crlf]
/////////////////////////////////////////////////////////////////////////////
// [!ClassName]

class ATL_NO_VTABLE [!ClassName] : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<[!ClassName], &CLSID_[!CoClassName]>,
[!if=(ObjectControl, "TRUE")]
	public IObjectControl,
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
	}

[!crlf]
DECLARE_REGISTRY_RESOURCEID([!IDR_REGISTRYID])
[!crlf]
DECLARE_PROTECT_FINAL_CONSTRUCT()
[!crlf]
DECLARE_NOT_AGGREGATABLE([!ClassName])

[!crlf]
BEGIN_COM_MAP([!ClassName])
	COM_INTERFACE_ENTRY([!InterfaceName])
[!if=(ObjectControl, "TRUE")]
	COM_INTERFACE_ENTRY(IObjectControl)
[!endif]
[!if=(Dual, "TRUE")]
	COM_INTERFACE_ENTRY(IDispatch)
[!endif]
END_COM_MAP()

[!if=(ObjectControl, "TRUE")]
[!crlf]
// IObjectControl
public:
	STDMETHOD(Activate)();
	STDMETHOD_(BOOL, CanBePooled)();
	STDMETHOD_(void, Deactivate)();
[!crlf]
	CComPtr<IObjectContext> m_spObjectContext;
[!endif]
[!crlf]
// [!InterfaceName]
public:
};

[!crlf]
[!if=(FileExists, "FALSE")]
#endif //__[!UpperShortName]_H_
[!endif]
