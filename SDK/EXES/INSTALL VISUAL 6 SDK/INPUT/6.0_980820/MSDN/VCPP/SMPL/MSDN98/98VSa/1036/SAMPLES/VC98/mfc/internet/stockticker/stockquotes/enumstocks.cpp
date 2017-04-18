// EnumStocks.cpp : Implementation of CEnumStocks
//
// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) 1992-1998 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.

#include "stdafx.h"
#include "stockquotes.h"
#include "EnumStocks.h"

/////////////////////////////////////////////////////////////////////////////
// CEnumStocks
//
CEnumStocks::~CEnumStocks()
{
	for (CStockInfoList::iterator i = m_stockInfoList.begin();
		 i != m_stockInfoList.end(); i++)
	{
		delete *i;
	}
	m_stockInfoList.clear();
}

// Return next N stocks.
//
STDMETHODIMP CEnumStocks::Next(ULONG celt, STOCKINFO** rgelt, ULONG* pceltFetched)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	if (rgelt == NULL || (celt != 1 && pceltFetched == NULL))
		return E_POINTER;
	if (m_iterCur == m_stockInfoList.end())
		return E_FAIL;
	ULONG nRem = (ULONG)(m_stockInfoList.end() - m_iterCur);
	HRESULT hRes = S_OK;
	if (nRem < celt)
		hRes = S_FALSE;
	ULONG nMin = min(celt, nRem);
	if (pceltFetched != NULL)
		*pceltFetched = nMin;
	while(nMin--)
	{
		STOCKINFO** p_si1 = rgelt++;
		*p_si1 = (STOCKINFO*)::CoTaskMemAlloc(sizeof(STOCKINFO));
		STOCKINFO* p_si2 = *m_iterCur++;

		ocscpy((*p_si1)->m_rgSymbol, p_si2->m_rgSymbol);
		ocscpy((*p_si1)->m_rgCurrent, p_si2->m_rgCurrent);
		ocscpy((*p_si1)->m_rgChange, p_si2->m_rgChange);
	}
	return hRes;
}

// Skip N stocks.
//
STDMETHODIMP CEnumStocks::Skip(ULONG celt)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	if (m_stockInfoList.end() - m_iterCur <  celt)
	{
		m_iterCur = m_stockInfoList.end();
		return S_FALSE;
	}
	m_iterCur += celt;
	return S_OK;
}

// Start at beginning.
//
STDMETHODIMP CEnumStocks::Reset(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	m_iterCur = m_stockInfoList.begin();
	return S_OK;
}

// Make a copy of this Enumerator.
//
STDMETHODIMP CEnumStocks::Clone(IEnumStocks** ppEnum)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	typedef CComObject<CEnumStocks> _class;
	HRESULT hRes = E_POINTER;
	if (ppEnum != NULL)
	{
		_class* p = NULL;
		ATLTRY(p = new _class)
		if (p == NULL)
		{
			*ppEnum = NULL;
			hRes = E_OUTOFMEMORY;
		}
		else
		{
			// If the data is a copy then we need to keep "this" object around
			hRes = p->Init(m_stockInfoList.begin(), m_stockInfoList.end(), m_iterCur);
			if (FAILED(hRes))
				delete p;
			else
			{
				hRes = p->_InternalQueryInterface(IID_IEnumStocks, (void**)ppEnum);
				if (FAILED(hRes))
					delete p;
			}
		}
	}
	return hRes;
}

// Initialize from given stock data.
//
HRESULT CEnumStocks::Init(CStockList::iterator s, CStockList::iterator e)
{
	USES_CONVERSION;
	for (CStockList::iterator i = s; i != e; i++)
	{
		CStock      stock = *i;
		STOCKINFO*  psi = new STOCKINFO;
		ocscpy(psi->m_rgSymbol, T2COLE((LPCTSTR)stock.GetSymbol()));
		ocscpy(psi->m_rgCurrent, T2COLE((LPCTSTR)stock.GetCurrent()));
		ocscpy(psi->m_rgChange, T2COLE((LPCTSTR)stock.GetChange()));
		m_stockInfoList.push_back(psi);
	}
	m_iterCur = m_stockInfoList.begin();
	return S_OK;
}

// Initialize from given stock data, in a format that we store.
//
HRESULT CEnumStocks::Init(CStockInfoList::iterator s,
						  CStockInfoList::iterator e,
						  CStockInfoList::iterator cur)
{
	USES_CONVERSION;
	for (CStockInfoList::iterator i = s; i != e; i++)
	{
		STOCKINFO*  psiTmp = *i;
		STOCKINFO*  psi = new STOCKINFO;
		ocscpy(psi->m_rgSymbol, psiTmp->m_rgSymbol);
		ocscpy(psi->m_rgCurrent, psiTmp->m_rgCurrent);
		ocscpy(psi->m_rgChange, psiTmp->m_rgChange);
		m_stockInfoList.push_back(psiTmp);
	}
	m_iterCur = m_stockInfoList.begin() + (cur - s);
	return S_OK;
}
