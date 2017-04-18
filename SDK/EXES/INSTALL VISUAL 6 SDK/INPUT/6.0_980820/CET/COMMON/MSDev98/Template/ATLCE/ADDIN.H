// [!HeaderName] : Declaration of the [!ClassName]
[!crlf]

[!if=(FileExists, "FALSE")]
#ifndef __[!UpperShortName]_H_
#define __[!UpperShortName]_H_
[!crlf]
#include "resource.h"       // main symbols
#include <ObjModel\addguid.h>
#include <ObjModel\appguid.h>
#include <ObjModel\bldguid.h>
#include <ObjModel\textguid.h>
#include <ObjModel\dbgguid.h>
[!else]
[!AddIncludeFile(TargetFile, "resource.h")]
[!AddIncludeFile(TargetFile, "<ObjModel\addguid.h>)]
[!AddIncludeFile(TargetFile, "<ObjModel\appguid.h>)]
[!AddIncludeFile(TargetFile, "<ObjModel\bldguid.h>)]
[!AddIncludeFile(TargetFile, "<ObjModel\textguid.h>)]
[!AddIncludeFile(TargetFile, "<ObjModel\dbgguid.h>)]
[!endif]

[!crlf]
/////////////////////////////////////////////////////////////////////////////
// [!ClassName]

class ATL_NO_VTABLE [!ClassName] : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<[!ClassName], &CLSID_[!CoClassName]>,
[!if=(ApplicationEvents, "TRUE")]
	public IDispatchImpl<IApplicationEvents, &IID_IApplicationEvents, &LIBID_[!LibName]>,
[!endif]
[!if=(DebuggerEvents, "TRUE")]
	public IDispatchImpl<IDebuggerEvents, &IID_IDebuggerEvents, &LIBID_[!LibName]>,
[!endif]
	public IDSAddIn,
	public IDispatchImpl<[!InterfaceName], &IID_[!InterfaceName], &LIBID_[!LibName]>
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
BEGIN_COM_MAP([!ClassName])
	COM_INTERFACE_ENTRY([!InterfaceName])
	COM_INTERFACE_ENTRY2(IDispatch, [!InterfaceName])
	COM_INTERFACE_ENTRY(IDSAddIn)
[!if=(ApplicationEvents, "TRUE")]
	COM_INTERFACE_ENTRY(IApplicationEvents)
[!endif]
[!if=(DebuggerEvents, "TRUE")]
	COM_INTERFACE_ENTRY(IDebuggerEvents)
[!endif]
END_COM_MAP()

[!crlf]
	CComPtr<IApplication> m_spApplication;
	DWORD m_dwAddInID;
[!if=(ApplicationEvents, "TRUE")]
	DWORD m_dwAppEvents;
[!endif]
[!if=(DebuggerEvents, "TRUE")]
	DWORD m_dwDbgEvents;
[!endif]
[!crlf]

// IDSAddIn methods
public:
	STDMETHOD(OnConnection)(IApplication* pApp, VARIANT_BOOL bFirstTime, long dwCookie, VARIANT_BOOL* bOnConnection);
	STDMETHOD(OnDisconnection)(VARIANT_BOOL bLastTime);
[!crlf]

[!if=(ApplicationEvents, "TRUE")]
// IApplicationEvents methods
public:
	STDMETHOD(BeforeBuildStart)();
	STDMETHOD(BuildFinish)(long nNumErrors, long nNumWarnings);
	STDMETHOD(BeforeApplicationShutDown)();
	STDMETHOD(DocumentOpen)(IDispatch *pDocument);
	STDMETHOD(BeforeDocumentClose)(IDispatch *pDocument);
	STDMETHOD(DocumentSave)(IDispatch *pDocument);
	STDMETHOD(NewDocument)(IDispatch *pDocument);
	STDMETHOD(WindowActivate)(IDispatch *pWindow);
	STDMETHOD(WindowDeactivate)(IDispatch *pWindow);
	STDMETHOD(WorkspaceOpen)();
	STDMETHOD(WorkspaceClose)();
	STDMETHOD(NewWorkspace)();
[!crlf]
[!endif]

[!if=(DebuggerEvents, "TRUE")]
// IDebuggerEvents method
public:
    STDMETHOD(BreakpointHit)(IDispatch *pBreakpoint);
[!crlf]
[!endif]

// [!InterfaceName]
public:
[!if=(Toolbar, "TRUE")]
[!if!=(MethodName, "")]
	STDMETHOD([!MethodName])();
[!else]
	STDMETHOD(SampleMethod)();
[!endif]
[!endif]
};

[!crlf]
[!if=(FileExists, "FALSE")]
#endif //__[!UpperShortName]_H_
[!endif]
