// FinSessn.h : Declaration of the CFinSessn

#ifndef __FINSESSN_H_
#define __FINSESSN_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CFinSessn
class ATL_NO_VTABLE CFinSessn : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CFinSessn, &CLSID_FinSessn>,
	public IDispatchImpl<IFinSessn, &IID_IFinSessn, &LIBID_FINSRVRLib>
{
public:
	CFinSessn()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_FINSESSN)

BEGIN_COM_MAP(CFinSessn)
	COM_INTERFACE_ENTRY(IFinSessn)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

// IFinSessn
public:
};

#endif //__FINSESSN_H_
