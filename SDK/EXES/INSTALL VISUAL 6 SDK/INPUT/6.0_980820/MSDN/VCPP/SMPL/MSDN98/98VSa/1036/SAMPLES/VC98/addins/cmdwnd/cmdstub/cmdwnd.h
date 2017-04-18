// CmdWnd.h : Declaration of the CCmdWnd

#ifndef __CMDWND_H_
#define __CMDWND_H_

#include "resource.h"       // main symbols
#include <ObjModel\addguid.h>
#include <ObjModel\appguid.h>
#include <ObjModel\bldguid.h>
#include <ObjModel\textguid.h>
#include <ObjModel\dbgguid.h>

#include "..\msdevcmd\devcmd.h"

/////////////////////////////////////////////////////////////////////////////
// CCmdWnd
class ATL_NO_VTABLE CCmdWnd : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CCmdWnd, &CLSID_CmdWnd>,
	public IDispatchImpl<IApplicationEvents, &IID_IApplicationEvents, &LIBID_CMDSTUBLib>,
	public IDispatchImpl<IDebuggerEvents, &IID_IDebuggerEvents, &LIBID_CMDSTUBLib>,
	public IDSAddIn,
	public IDispatchImpl<ICmdWnd, &IID_ICmdWnd, &LIBID_CMDSTUBLib>,
	public IDispatchImpl<_ICommandWindowEvents, &DIID__ICommandWindowEvents, &LIBID_devcmdLib>
{
public:
	CCmdWnd();
	~CCmdWnd();

DECLARE_REGISTRY_RESOURCEID(IDR_CMDWND)

BEGIN_COM_MAP(CCmdWnd)
	COM_INTERFACE_ENTRY(ICmdWnd)
	COM_INTERFACE_ENTRY2(IDispatch, ICmdWnd)
	COM_INTERFACE_ENTRY(IDSAddIn)
	COM_INTERFACE_ENTRY(IApplicationEvents)
	COM_INTERFACE_ENTRY(IDebuggerEvents)
	COM_INTERFACE_ENTRY(_ICommandWindowEvents)
END_COM_MAP()

// _ICommandWindowEvents
public:
	HRESULT _stdcall OnClose();



// IDSAddIn methods
public:
	STDMETHOD(OnConnection)(IApplication* pApp, VARIANT_BOOL bFirstTime, long dwCookie, VARIANT_BOOL* bOnConnection);
	STDMETHOD(OnDisconnection)(VARIANT_BOOL bLastTime);

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

// IDebuggerEvents method
public:
    STDMETHOD(BreakpointHit)(IDispatch *pBreakpoint);

// ICmdWnd
public:
	STDMETHOD(DoCmdWnd)();

protected:
	CComPtr<IApplication> m_spApplication;
	DWORD m_dwAddInID;
	DWORD m_dwAppEvents;
	DWORD m_dwDbgEvents;
	CComPtr<ICommandWindow> m_pCommandWindow;
	DWORD m_dwCookie;


};

#endif //__CMDWND_H_
