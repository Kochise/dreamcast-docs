// FinCounters.cpp : Implementation of IPerfmonObjectImpl
#include "stdafx.h"
#include "FinSrvr.h"
#include "FinCtrs.h"

long CFinCounters::m_numSessions = 5;

STDMETHODIMP CFinCounters::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IPerfmonObject,
	};
	for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}
