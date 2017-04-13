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

//////////////////////////////////////////////////////////////////////////////
// CProxyIStockQuotes
class CProxyIStockQuotes : public CComPtr<IStockQuotes>
{

//IStockQuotes : IDispatch
public:
	HRESULT Create()
	{
		return ::CoCreateInstance(CLSID_CoStockQuotes, 0, CLSCTX_SERVER,
								  IID_IStockQuotes, (void**)&p);
	}

	HRESULT Update()
	{
		return p->Update();
	}
	HRESULT Add(
		BSTR bstrSymbol)
	{
		return p->Add(bstrSymbol);
	}
	HRESULT Remove(
		BSTR bstrSymbol)
	{
		return p->Remove(bstrSymbol);
	}
	HRESULT EnumAsString(
		IEnumString * * ppenum)
	{
		return p->EnumAsString(ppenum);
	}
	HRESULT EnumStocks(
		IEnumStocks * * ppenum)
	{
		return p->EnumStocks(ppenum);
	}
	HRESULT StockCount(
		int * cnt)
	{
		return p->StockCount(cnt);
	}
	HRESULT Save(
		IStream * pIStream)
	{
		return p->Save(pIStream);
	}
	HRESULT Load(
		IStream * pIStream)
	{
		return p->Load(pIStream);
	}
	HRESULT StartUpdating(
		int nUpdateInterval)
	{
		return p->StartUpdating(nUpdateInterval);
	}
	HRESULT StopUpdating()
	{
		return p->StopUpdating();
	}

	HRESULT IsUpdating(BOOL* b)
	{
		return p->IsUpdating(b);
	}

	HRESULT PauseUpdating()
	{
		return p->PauseUpdating();
	}

	HRESULT SetMSInvestorURL(BSTR newVal)
	{
		return p->SetMSInvestorURL(newVal);
	}

	HRESULT GetMSInvestorURL(BSTR* pVal)
	{
		return p->GetMSInvestorURL(pVal);
	}

	HRESULT SetStockSourceISAPIDllURL(BSTR newVal)
	{
		return p->SetStockSourceISAPIDllURL(newVal);
	}

	HRESULT GetStockSourceISAPIDllURL(BSTR* pVal)
	{
		return p->GetStockSourceISAPIDllURL(pVal);
	}
};
