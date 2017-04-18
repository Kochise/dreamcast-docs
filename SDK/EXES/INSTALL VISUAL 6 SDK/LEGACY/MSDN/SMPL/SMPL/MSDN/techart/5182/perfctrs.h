// PerfCounters.h : Declaration of macros, etc .. for perf counters

#ifndef __PERFCOUNTERS_H_
#define __PERFCOUNTERS_H_

//
// Utility functions to help with registration
//
bool RegisterPerformanceCounters(LPCTSTR pszAppName, CLSID clsidCollectionComp);
bool UnRegisterPerformanceCounters(LPCTSTR pszAppName);

//
// Counter map stuff - for now
//
struct _PF_COUNTER_ENTRY
{
	char *m_pName;
	char *m_pHelpText;
	long *m_pData;
};

#define EMPTY_COUNTER_MAP()	virtual const _PF_COUNTER_ENTRY*  _GetPfCounterEntries()=0;
#define BEGIN_COUNTER_MAP(x)	const _PF_COUNTER_ENTRY*  _GetPfCounterEntries() { \
                                static const _PF_COUNTER_ENTRY _counterEntries[] = { 
#define COUNTER_ENTRY_LONG(x, y, z) {x, y, z},
#define COUNTER_ENTRY_LONG_FUNC(x, y, z) 
#define END_COUNTER_MAP()       {NULL, NULL, NULL}};\
                                return _counterEntries; }

//
// IPerfmonCounterImpl
//
class IPerfmonCounterImpl : 
	public CComDualImpl<IPerfmonCounter, &IID_IPerfmonCounter, &LIBID_FINSRVRLib>, 
	public ISupportErrorInfo,
	public CComObjectRoot
{
public:
	IPerfmonCounterImpl() : m_index(0), m_name(), m_helpText() {}
	virtual ~IPerfmonCounterImpl() {}

BEGIN_COM_MAP(IPerfmonCounterImpl)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IPerfmonCounter)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

void SetIndex(long index) { m_index = index; }
void SetName(const CString& name) { m_name = name; }
void SetHelpText(const CString& helpText) { m_helpText = helpText; }
void SetData(long *pData) { m_pData = pData; }

//
// IPerfmonCounter
//
STDMETHOD (Collect)(VARIANT *pVariant);
STDMETHOD (GetName)(BSTR *pName);
STDMETHOD (GetHelp)(BSTR *pHelp);
STDMETHOD (GetIndex)(long *pIndex);
STDMETHOD (GetDataType)(short *pDataType);

//ISupportErrorInfo
STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid)
{
	return (InlineIsEqualGUID(IID_IPerfmonCounter,riid)) ? S_OK : S_FALSE;
}

private:
	long m_index; // the counter's index 0, 2, 4, etc ...
	CString m_name;
	CString m_helpText;
	long *m_pData;
};

/////////////////////////////////////////////////////////////////////////////
// IPerfmonObjectImpl
class ATL_NO_VTABLE IPerfmonObjectImpl : 
	public IDispatchImpl<IPerfmonObject, &IID_IPerfmonObject, &LIBID_FINSRVRLib>
{
public:
	IPerfmonObjectImpl() : m_pCounters(NULL){ }
	virtual ~IPerfmonObjectImpl();

EMPTY_COUNTER_MAP()

// IPerfmonObject
STDMETHOD(GetName)(BSTR *pName);
STDMETHOD(GetHelp)(BSTR *pHelp);
STDMETHOD(GetIndex)(long *pIndex);
STDMETHOD(GetCounters)(IUnknown **pCounters);
STDMETHOD(GetNumCounters)(long *pNumCounters);

private:
	void AddCounterObject(int arrayIndex, int counterIndex, const CString& name, const CString& helpText, long *pData);

	CComVariant* m_pCounters; // an array of counters to give to the caller thru IEnumVARIANT
};

#endif //