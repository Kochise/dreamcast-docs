// EnumStocks.h : Declaration of the CEnumStocks
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

#ifndef __ENUMSTOCKS_H_
#define __ENUMSTOCKS_H_

#include "resource.h"       // main symbols
#include "stockquotes_.h"

/////////////////////////////////////////////////////////////////////////////
// CEnumStocks
//
// Enumerate stocks in "native" format.  Allows user to format data as they
// please.
//
class ATL_NO_VTABLE CEnumStocks :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CEnumStocks, &CLSID_EnumStocks>,
	public IEnumStocks
{
public:
	CEnumStocks()
	{
	}

	~CEnumStocks();

DECLARE_REGISTRY_RESOURCEID(IDR_ENUMSTOCKS)

BEGIN_COM_MAP(CEnumStocks)
	COM_INTERFACE_ENTRY(IEnumStocks)
END_COM_MAP()

// IEnumStocks
public:
	typedef std::vector<STOCKINFO*> CStockInfoList;

	STDMETHOD(Next)(ULONG celt, STOCKINFO** rgelt, ULONG* pceltFetched);
	STDMETHOD(Skip)(ULONG celt);
	STDMETHOD(Reset)(void);
	STDMETHOD(Clone)(IEnumStocks** ppEnum);

	HRESULT     Init(CStockList::iterator s, CStockList::iterator e);
	HRESULT     Init(CStockInfoList::iterator s,
					 CStockInfoList::iterator e,
					 CStockInfoList::iterator cur);

protected:
	CStockInfoList              m_stockInfoList;
	CStockInfoList::iterator    m_iterCur;
};

#endif //__ENUMSTOCKS_H_
