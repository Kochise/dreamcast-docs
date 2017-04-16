// cpool.h : Declaration of the CPool

#ifndef __POOL_H_
#define __POOL_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CPool
class ATL_NO_VTABLE CPool : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CPool, &CLSID_CPool>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CPool>,
	public IDispatchImpl<IPool, &IID_IPool, &LIBID_FORUMPOOLLib>
{
public:
	CPool()
	{
		CLSID   pAdminId;
		HRESULT hResult;

		m_bInitialized = false;
		hResult = ::CLSIDFromProgID(TEXT("AdminPvt.CAdminPvt"), &pAdminId);
		if (hResult == NOERROR)
		{
			hResult = ::CoCreateInstance(pAdminId,NULL, CLSCTX_LOCAL_SERVER, IID_IDispatch, (void **)&m_oAdmin);
			if (hResult == NOERROR)
				m_bInitialized = true;
		}
	}
	~CPool()
	{
		if (m_oAdmin)
			m_oAdmin->Release();
	}

DECLARE_CLASSFACTORY_SINGLETON(CPool)

DECLARE_REGISTRY_RESOURCEID(IDR_POOL)

BEGIN_COM_MAP(CPool)
	COM_INTERFACE_ENTRY(IPool)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CPool)
END_CONNECTION_POINT_MAP()


// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IPool
public:
	STDMETHOD(GetForumService)(/*[out, retval]*/ IDispatch ** ppoAdmin);
private:
	bool		m_bInitialized;
	IDispatch * m_oAdmin;
};

#endif //__POOL_H_
