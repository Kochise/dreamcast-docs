// RegisterPerfmonObject.h : Declaration of the CRegisterPerfmonObject

#ifndef __REGISTERPERFMONOBJECT_H_
#define __REGISTERPERFMONOBJECT_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CRegisterPerfmonObject
class ATL_NO_VTABLE CRegisterPerfmonObject : 
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CRegisterPerfmonObject, &CLSID_RegisterPerfmonObject>,
	public ISupportErrorInfo,
	public IDispatchImpl<IRegisterPerfmonObject, &IID_IRegisterPerfmonObject, &LIBID_REGPCTRSLib>
{
public:
	CRegisterPerfmonObject()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_REGISTERPERFMONOBJECT)

BEGIN_COM_MAP(CRegisterPerfmonObject)
	COM_INTERFACE_ENTRY(IRegisterPerfmonObject)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IRegisterPerfmonObject
public:
	STDMETHOD(Register)(BSTR appName, BSTR collectionGUID);
	STDMETHOD(Unregister)(BSTR appName);

private:
	static const CString hdrFileName;
	static const CString iniFileName;
	static const CString english;
	static const CString define;
	static const CString name;
	static const CString help;

	void UnlodCtr();
	void LodCtr();
	bool AddPerformanceKey();
	bool AddPerformanceData();

	CString m_appName;
	CString m_strClsid;
	CLSID   m_clsid;
};

#endif //__REGISTERPERFMONOBJECT_H_
