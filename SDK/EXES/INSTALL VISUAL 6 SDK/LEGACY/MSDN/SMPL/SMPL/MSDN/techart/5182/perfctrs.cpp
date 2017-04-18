#include "stdafx.h"
#include "FinSrvr.h"
#include "RegPCtrs.h"
#include "RegPCtrs_i.c"
#include "perfctrs.h"
//
// Utility functions to help with registration
//
bool RegisterPerformanceCounters(LPCTSTR pszAppName, CLSID clsidCollectionComp)
{
	//
	// Create the registration component and calls its registration function
	//
	IRegisterPerfmonObject *pRegistrar = NULL;
	HRESULT hRes = CoCreateInstance(CLSID_RegisterPerfmonObject, NULL, CLSCTX_SERVER, IID_IRegisterPerfmonObject, (void**)&pRegistrar);

	if (FAILED(hRes)) return false;

	_bstr_t appName(pszAppName);

	LPOLESTR pszGUID = NULL;
	hRes = StringFromCLSID(clsidCollectionComp, &pszGUID);
	_ASSERTE(SUCCEEDED(hRes));

	_bstr_t componentGUID(pszGUID);
	
	pRegistrar->Register(appName, componentGUID);

	CoTaskMemFree(pszGUID);

	pRegistrar->Release();

	return true;
}

bool UnRegisterPerformanceCounters(LPCTSTR pszAppName)
{
	//
	// Create the registration component and calls its unregister function
	//
	IRegisterPerfmonObject *pRegistrar = NULL;
	HRESULT hRes = CoCreateInstance(CLSID_RegisterPerfmonObject, NULL, CLSCTX_SERVER, IID_IRegisterPerfmonObject, (void**)&pRegistrar);

	if (FAILED(hRes)) return false;

	_bstr_t appName(pszAppName);

	pRegistrar->Unregister(appName);

	pRegistrar->Release();

	return true;
}

//
// IPerfmonCounterImpl
//
STDMETHODIMP IPerfmonCounterImpl::Collect(VARIANT *pVariant)
{
	//
	// Return the counter we are asked for
	//
	V_VT(pVariant) = VT_I4;
	V_I4(pVariant) = *m_pData;
	return S_OK;
}

STDMETHODIMP IPerfmonCounterImpl::GetName(BSTR *pName)
{
	CComBSTR bStr(m_name);
	*pName = bStr.Copy();
	return S_OK;
}

STDMETHODIMP IPerfmonCounterImpl::GetHelp(BSTR *pHelp)
{
	CComBSTR bStr(m_helpText);
	*pHelp = bStr.Copy();
	return S_OK;
}

STDMETHODIMP IPerfmonCounterImpl::GetIndex(long *pIndex)
{
	*pIndex = m_index;
	return S_OK;
}

STDMETHODIMP IPerfmonCounterImpl::GetDataType(short *pDataType)
{
	*pDataType = VT_I4;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// IPerfmonObjectImpl
IPerfmonObjectImpl::~IPerfmonObjectImpl()
{
	if (m_pCounters)
	{
		delete [] m_pCounters;
	}
}


STDMETHODIMP IPerfmonObjectImpl::GetName(BSTR *pName)
{
	CComBSTR bStr("FinServer");
	*pName = bStr.Copy();
	return S_OK;
}

STDMETHODIMP IPerfmonObjectImpl::GetHelp(BSTR *pHelp)
{
	CComBSTR bStr("FinServer counters");
	*pHelp = bStr.Copy();
	return S_OK;
}

STDMETHODIMP IPerfmonObjectImpl::GetIndex(long *pIndex)
{
	*pIndex = 0;
	return S_OK;
}

STDMETHODIMP IPerfmonObjectImpl::GetCounters(IUnknown **pCounters)
{
	//
	// Initialize the array of variants with a IPerfmonCounterImpl object
	// for each of our counters
	//
	if (m_pCounters != NULL)
		delete [] m_pCounters;

	const _PF_COUNTER_ENTRY* counterEntries = _GetPfCounterEntries();
	long sizeFromMap = sizeof(*counterEntries)/sizeof(_PF_COUNTER_ENTRY);

	m_pCounters = new CComVariant[sizeFromMap];
	long index = 2; // the object itself is 0, the counters start at 2
	for (int i=0; i < sizeFromMap; i++)
	{
		index = 2 + (i *2);
		AddCounterObject(i, 
			          index, 
					  (counterEntries[i]).m_pName, 
					  (counterEntries[i]).m_pHelpText,
					  (counterEntries[i]).m_pData);
	}

	//
	// Create an enumerator to hand to the caller
	//
	if (pCounters == NULL)
		return E_POINTER;

	*pCounters = NULL;
	typedef CComObject<CComEnum<IEnumVARIANT, &IID_IEnumVARIANT, VARIANT, _Copy<VARIANT> > > enumvar;
	enumvar* p = new enumvar;
	_ASSERTE(p);
	HRESULT hRes = p->Init(&m_pCounters[0], &m_pCounters[sizeFromMap], NULL, AtlFlagCopy);
	if (SUCCEEDED(hRes))
		hRes = p->QueryInterface(IID_IUnknown, (void**)pCounters);
	if (FAILED(hRes))
		delete p;
	return hRes;

}

void IPerfmonObjectImpl::AddCounterObject(int arrayIndex, int counterIndex, const CString& name, const CString& helpText, long *pData)
{
	_ASSERTE(m_pCounters);
	//
	// create an object
	//
	CComObject<IPerfmonCounterImpl> *pNew=NULL;
	HRESULT  hRes = CComObject<IPerfmonCounterImpl>::CreateInstance(&pNew);

	pNew->SetIndex(counterIndex);
	pNew->SetName(name);
	pNew->SetHelpText(helpText);
	pNew->SetData(pData);

	//
	// Get IDispatch pointer
	//
	IDispatch *pCounter = NULL;
	hRes = pNew->QueryInterface(IID_IDispatch, (void**)&pCounter);
	_ASSERTE(SUCCEEDED(hRes));

	//
	// create a variant and add it to the collection
	//
	CComVariant& var = m_pCounters[arrayIndex];
	V_VT(&var) = VT_DISPATCH;
	V_DISPATCH(&var) = pCounter;

}

STDMETHODIMP IPerfmonObjectImpl::GetNumCounters(long *pNumCounters)
{
	const _PF_COUNTER_ENTRY* counterEntries = _GetPfCounterEntries();
	long sizeFromMap = sizeof(*counterEntries)/sizeof(_PF_COUNTER_ENTRY);

	*pNumCounters =	sizeFromMap;
	return S_OK;
}
