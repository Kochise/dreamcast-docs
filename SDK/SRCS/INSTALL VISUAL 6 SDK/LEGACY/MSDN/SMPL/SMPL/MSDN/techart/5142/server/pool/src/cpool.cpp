// cpool.cpp : Implementation of CPool
#include "stdafx.h"
#include "ForumPool.h"
#include "cpool.h"

/////////////////////////////////////////////////////////////////////////////
// CPool

STDMETHODIMP CPool::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IPool,
	};
	for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CPool::GetForumService(IDispatch * * ppoAdmin)
{
	if (m_bInitialized == true)
		*ppoAdmin = m_oAdmin;

	if (m_oAdmin)
		m_oAdmin->AddRef();

	return S_OK;
}
