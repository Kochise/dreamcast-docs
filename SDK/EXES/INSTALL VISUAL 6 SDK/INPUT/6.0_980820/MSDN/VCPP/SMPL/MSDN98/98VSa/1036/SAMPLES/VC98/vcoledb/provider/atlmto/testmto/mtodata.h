// MTOData.h : Declaration of the CMTOData

#ifndef __MTODATA_H_
#define __MTODATA_H_

#include "resource.h"       // main symbols
#include "..\\atlmto.h"
#include "Checking_Account.h"

/////////////////////////////////////////////////////////////////////////////
// CMTOData
class ATL_NO_VTABLE CMTOData :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CMTOData, &CLSID_MTOData>,
	public IDispatchImpl<IMTOTest, &IID_IMTOTest, &LIBID_TESTMTOLib>,
	public IDispatchImpl<IMTOData, &__uuidof(IMTOData), &LIBID_TESTMTOLib>
{
public:
	CMTOData()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_MTODATA)

typedef IDispatchImpl<IMTOTest, &IID_IMTOTest, &LIBID_TESTMTOLib> dispClass;

BEGIN_COM_MAP(CMTOData)
	COM_INTERFACE_ENTRY(IMTOTest)
	COM_INTERFACE_ENTRY(IMTOData)
	COM_INTERFACE_ENTRY2(IDispatch, dispClass)
END_COM_MAP()

// IMTOData
public:
	STDMETHOD(GetData)(int* pnRows, BSTR* pContext, BSTR* pRowset);
	STDMETHOD(GetAccounts)(double balance, BSTR* pContext);

	CChecking_Account m_acctQuery;
};

#endif //__MTODATA_H_
