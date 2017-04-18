// MTOData.cpp : Implementation of CMTOData
#include "stdafx.h"
#include "TestMTO.h"
#include "MTOData.h"
#include "..\atlmto.h"

/////////////////////////////////////////////////////////////////////////////
// CMTOData


STDMETHODIMP CMTOData::GetAccounts(double balance, BSTR *pContext)
{
	HRESULT hr = m_acctQuery.Open(balance);
	if (FAILED(hr))
		return hr;
	CVirtualBytes buf(100000);
	m_acctQuery.WriteMetaData(buf);
	Write(buf, balance);
	*pContext = buf;
	m_acctQuery.Close();
	m_acctQuery.ReleaseCommand();
	return S_OK;
}

STDMETHODIMP CMTOData::GetData(int* pnRows, BSTR* pContext, BSTR* pRowset)
{
	HRESULT hr = m_acctQuery.Open(*((double*)(*pContext)));
	if (FAILED(hr))
		return hr;
	hr = m_acctQuery.Snapshot();
	if (FAILED(hr))
		return hr;
	*pnRows = m_acctQuery.m_nRowsRead;
	*pRowset = m_acctQuery;
	m_acctQuery.Close();
	m_acctQuery.ReleaseCommand();
	return S_OK;
}
