// CommandWindow.h : Declaration of the CCommandWindow

#ifndef __COMMANDWINDOW_H_
#define __COMMANDWINDOW_H_

#include "resource.h"       // main symbols
#include "devcmdCP.h"

/////////////////////////////////////////////////////////////////////////////
// CCommandWindow
class ATL_NO_VTABLE CCommandWindow : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CCommandWindow, &CLSID_CommandWindow>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CCommandWindow>,
	public IDispatchImpl<ICommandWindow, &IID_ICommandWindow, &LIBID_devcmdLib>,
	public CProxy_ICommandWindowEvents< CCommandWindow >
{
public:
	CCommandWindow()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_COMMANDWINDOW)
DECLARE_GET_CONTROLLING_UNKNOWN()

BEGIN_COM_MAP(CCommandWindow)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
	COM_INTERFACE_ENTRY(ICommandWindow)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY_AGGREGATE(IID_IMarshal, m_pUnkMarshaler.p)
END_COM_MAP()
BEGIN_CONNECTION_POINT_MAP(CCommandWindow)
	CONNECTION_POINT_ENTRY(DIID__ICommandWindowEvents)
END_CONNECTION_POINT_MAP()

	HRESULT FinalConstruct()
	{
		return CoCreateFreeThreadedMarshaler(
			GetControllingUnknown(), &m_pUnkMarshaler.p);
	}

	void FinalRelease()
	{
		m_pUnkMarshaler.Release();
	}

	CComPtr<IUnknown> m_pUnkMarshaler;

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);


// ICommandWindow
public:
	STDMETHOD(SetFocus)();
	IApplication * GetApp();
	STDMETHOD(DoClose)();
	STDMETHOD(Open)(IDispatch *pDispApplication);
	HRESULT FindApp();
	STDMETHOD(DoFireClose)();

protected:
	CComPtr<IApplication> m_spApplication;
};

#endif //__COMMANDWINDOW_H_
