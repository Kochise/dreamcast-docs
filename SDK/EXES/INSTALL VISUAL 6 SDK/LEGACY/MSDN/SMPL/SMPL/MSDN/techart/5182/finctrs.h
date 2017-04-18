// FinCounters.h : Declaration of the IPerfmonObjectImpl

#ifndef __FINCOUNTERS_H_
#define __FINCOUNTERS_H_

#include "resource.h"       // main symbols
#include "PerfCtrs.h"

class ATL_NO_VTABLE CFinCounters : 
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CFinCounters, &CLSID_CFinCntrs>,
	public ISupportErrorInfo,
	public IPerfmonObjectImpl
{
public:
	CFinCounters() { }
	virtual ~CFinCounters() {}

DECLARE_REGISTRY_RESOURCEID(IDR_CFINCNTRS)

BEGIN_COM_MAP(CFinCounters)
	COM_INTERFACE_ENTRY(IPerfmonObject)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

static long m_numSessions;

BEGIN_COUNTER_MAP(IPerfmonCounterImpl)
	COUNTER_ENTRY_LONG("ActiveSessions",
                       "The number of users connected to the application",
                        &m_numSessions)
	COUNTER_ENTRY_LONG_FUNC("ODBCConnections",
                            "The number of ODBC connections the application has open",
                             "z")
END_COUNTER_MAP()


// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);
};

#endif //__FINCOUNTERS_H_
