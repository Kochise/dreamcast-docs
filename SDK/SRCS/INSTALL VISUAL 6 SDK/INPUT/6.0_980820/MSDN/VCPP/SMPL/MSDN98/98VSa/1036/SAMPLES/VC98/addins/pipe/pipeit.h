// PipeIt.h : Declaration of the CPipeIt

#ifndef __PIPEIT_H_
#define __PIPEIT_H_

#include "resource.h"       // main symbols
#include <ObjModel\addguid.h>
#include <ObjModel\appguid.h>
#include <ObjModel\bldguid.h>
#include <ObjModel\textguid.h>
#include <ObjModel\dbgguid.h>

/////////////////////////////////////////////////////////////////////////////
// CPipeIt
class ATL_NO_VTABLE CPipeIt : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CPipeIt, &CLSID_PipeIt>,
	public IDSAddIn,
	public IDispatchImpl<IPipeIt, &IID_IPipeIt, &LIBID_PIPELib>
{
public:
	CPipeIt()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_PIPEIT)

BEGIN_COM_MAP(CPipeIt)
	COM_INTERFACE_ENTRY(IPipeIt)
	COM_INTERFACE_ENTRY2(IDispatch, IPipeIt)
	COM_INTERFACE_ENTRY(IDSAddIn)
END_COM_MAP()

	CComPtr<IApplication> m_spApplication;
	DWORD m_dwAddInID;

// IDSAddIn methods
public:
	STDMETHOD(OnConnection)(IApplication* pApp, VARIANT_BOOL bFirstTime, long dwCookie, VARIANT_BOOL* bOnConnection);
	STDMETHOD(OnDisconnection)(VARIANT_BOOL bLastTime);

// IPipeIt
public:
	STDMETHOD(Filter)();
};

#endif //__PIPEIT_H_
