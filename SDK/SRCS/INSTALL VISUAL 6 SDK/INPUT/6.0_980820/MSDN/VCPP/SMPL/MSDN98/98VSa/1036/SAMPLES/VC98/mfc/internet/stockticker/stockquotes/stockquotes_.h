// StockQuotes_.h : Declaration of the CStockQuotes
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

#ifndef __STOCKQUOTES_H_
#define __STOCKQUOTES_H_

#include "resource.h"       // main symbols
#include "cpstockquotes.h"
#include <afxole.h>

//////////////////////////////////////////////////////////////////////////////
// CStock
//
// Represents a stock.  Tracks current price, change from last price and
// stock symbol.
//
class CStock
{
public:
	CStock() {}
	CStock(const CString& strSymbol)
	: m_strSymbol(strSymbol) {}

	void        GetStockInfo(CString& strCurrent, CString& strChange)
		{ strCurrent = m_strCurrent; strChange = m_strChange; }
	void        SetStockInfo(const CString& strCurrent, const CString& strChange)
		{ SetCurrent(strCurrent); SetChange(strChange); }
	void        SetCurrent(const CString& strCurrent)
		{ m_strCurrent = strCurrent; }
	CString     GetCurrent()
		{ return m_strCurrent; }
	void        SetChange(const CString& strChange)
		{ m_strChange = strChange; }
	CString     GetChange()
		{ return m_strChange; }
	CString     GetSymbol()
		{ return m_strSymbol; }
	bool operator == (const CStock& s) const
		{ return m_strSymbol == s.m_strSymbol; }
	bool operator < (const CStock& s) const
		{ return m_strSymbol < s.m_strSymbol; }


protected:
	CString     m_strCurrent;   // current (or last) price.
	CString     m_strChange;    // change from previous price.
	CString     m_strSymbol;    // the stock that is being tracked.
};
typedef std::vector<CStock> CStockList;
typedef std::vector<CStock>::iterator CStockListIter;

//////////////////////////////////////////////////////////////////////////////
// CStockQuoteSource
//
// Source of the stock information.  Responsible for downloading and parsing
// info from web for given stock.  Multiple stock sources exist, if one fails
// hopfully one of the others will succeed.
//
class CStockQuoteSource
{
public:
	CStockQuoteSource() : m_bInTag(false) {}
	virtual ~CStockQuoteSource() {}

	virtual bool        Update(CInternetSession& session, CStock& stock)
		{  return DownloadStockInfo(session, stock); }
	virtual CString     GetURL() { return m_strURL; }
	virtual void        SetURL(const CString& strURL) {}

	// to make finding them easier since CStockQuotes need to access them to save their URLs.
	//
	virtual bool        IsMSInvestor() { return false; }
	virtual bool        IsISAPIDll() { return false; }

	bool operator == (const CStockQuoteSource& s) const
		{ return m_strURL == s.m_strURL; }
	bool operator < (const CStockQuoteSource& s) const
		{ return false; }

protected:
	BYTE*               m_buffer;       // buffer for data from web.
	CString             m_strURL;       // URL to connect to.
	bool                m_bInTag;       // parsing a tag?
	virtual bool        DownloadStockInfo(CInternetSession& session, CStock& stock);
	virtual bool        SetStockInfo(CHttpFile* pFile, CStock& stock) = 0;
	virtual bool        SetStockInfoHelper(CHttpFile* pFile, CStock& stock,
										   TCHAR* szCurText, TCHAR* szChangeText);
	virtual bool        ParseStockInfo(TCHAR* szBuf, TCHAR* szHeader, CString& strResult);
	virtual void        StripTags(LPTSTR pszBuffer);
	virtual void        StripExtraSpace(CString& s);
	virtual void        SetURLHelper(const CString& strURL, const CString& strURLTail);
};

//////////////////////////////////////////////////////////////////////////////
// CSQSMSInvestor
//
// Microsoft Investor Stock Quotes.
// NOTE: Because of changes in this web site the stock data can't be accessed
// as originally done.  As a result this stock source object can't be used as is.
// However, you can edit this class and access the site of you choice.  If you
// use the "Custom URL" in the properties page then you will need to use this
// class since the StockTicker control associates that property with this class.
//
class CSQSMSInvestor : public CStockQuoteSource
{
public:
	CSQSMSInvestor()
	: m_bFoundHeader(false)
	{
		m_strURL = _T("http://investor.msn.com/quotes/quote.asp?Symbol=");
	}

	virtual void        SetURL(const CString& strURL)
		{ SetURLHelper(strURL, _T("/quotes/quote.asp?Symbol=")); }

	virtual bool        IsMSInvestor() { return true; }

protected:
	virtual bool        SetStockInfo(CHttpFile* pFile, CStock& stock);
	virtual bool        ParseStockInfo(TCHAR* szBuf, TCHAR* szHeader, CString& strResult);

	bool                m_bFoundHeader;
};

//////////////////////////////////////////////////////////////////////////////
// CSQSISAPIDll
//
// ISAPI Dll Stock Source.
//
class CSQSISAPIDll : public CStockQuoteSource
{
public:
	CSQSISAPIDll()
	{
		m_strURL = _T("<Need to specify URL to ISAPI DLL>?QueryForStock?Symbol=");
	}

	virtual void        SetURL(const CString& strURL)
		{ SetURLHelper(strURL, _T("?QueryForStock?Symbol=")); }
	virtual bool        IsISAPIDll() { return true; }

protected:
	virtual bool        SetStockInfo(CHttpFile* pFile, CStock& stock);
};

//////////////////////////////////////////////////////////////////////////////
// CSQSList
//
// List of stock quote sources.
//
class CSQSList : public std::vector<CStockQuoteSource*>
{
public:
	CSQSList() {}
	~CSQSList() { Cleanup(); }

	void Init();        // creates all the sources here.

	CStockQuoteSource* GetMSInvestor();
	CStockQuoteSource* GetStockSourceISAPIDll();

protected:
	void Cleanup();
};

/////////////////////////////////////////////////////////////////////////////
// CEnumStocksAsString
//
// IEnumString wrapper that formats the stock info into a string.
// The format is [*]<symbol>: (<change>)
// The '*' indicates that the information came from the ISAPI DLL and is
// not real data.  If data for the stock could not be found then <change> becomes
// "<NA>".
//
class CStockUpdateNotify;
class CEnumStocksAsString :
	public CComObjectRootEx<CComObjectThreadModel>,
	public IUnknown
{
public:
	typedef std::vector<LPOLESTR> CStocksAsString;
	typedef _Copy<LPOLESTR>       CCopy;

	CEnumStocksAsString() {}
	~CEnumStocksAsString();

BEGIN_COM_MAP(CEnumStocksAsString)
	COM_INTERFACE_ENTRY(IUnknown)
	COM_INTERFACE_ENTRY_IID(IID_IEnumString, CEnumStocksAsString)
END_COM_MAP()


	STDMETHOD(Next)(ULONG celt, LPOLESTR* rgelt, ULONG* pceltFetched);
	STDMETHOD(Skip)(ULONG celt);
	STDMETHOD(Reset)(void);
	STDMETHOD(Clone)(IEnumString** ppEnum);

	void    Init(CStockList::iterator s, CStockList::iterator e);
	HRESULT Init(CStocksAsString::iterator s, CStocksAsString::iterator e,
				 CStocksAsString::iterator cur);

protected:
	CStocksAsString             m_stocksAsString;
	CStocksAsString::iterator   m_iterCur;

};

//////////////////////////////////////////////////////////////////////////////
// CStockQuotes
//
// Keeps track and manages the stock information.
//

class ATL_NO_VTABLE CStockQuotes :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CStockQuotes, &CLSID_CoStockQuotes>,
	public IConnectionPointContainerImpl<CStockQuotes>,
	public IDispatchImpl<IStockQuotes, &IID_IStockQuotes, &LIBID_STOCKQUOTESLib>,
	public CProxyIStockEvents<CStockQuotes>,
	public IProvideClassInfo2Impl<&CLSID_CoStockQuotes, &IID_IStockEvents,
								  &LIBID_STOCKQUOTESLib>
{
public:
	CStockQuotes()
	{
		m_sqsList.Init();
		m_pStockUpdateNotify = 0;
		m_bNeedToStopUpdating = false;
		m_pINetSession = 0;
	}
	~CStockQuotes()
	{
	}

	void            FinalRelease();
	HRESULT         FinalConstruct();
	HRESULT         DoUpdate();
	void            NotifyThreadEnding()
	{
		m_pStockUpdateNotify = 0;   // thread has ended so don't access.
	}

DECLARE_REGISTRY_RESOURCEID(IDR_STOCKQUOTES)

BEGIN_COM_MAP(CStockQuotes)
	COM_INTERFACE_ENTRY(IStockQuotes)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
	COM_INTERFACE_ENTRY(IProvideClassInfo2)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CStockQuotes)
	CONNECTION_POINT_ENTRY(IID_IStockEvents)
END_CONNECTION_POINT_MAP()


// IStockQuotes
public:
	STDMETHOD(GetStockSourceISAPIDllURL)(BSTR* pVal);
	STDMETHOD(SetStockSourceISAPIDllURL)(BSTR newVal);
	STDMETHOD(GetMSInvestorURL)(BSTR* pVal);
	STDMETHOD(SetMSInvestorURL)(BSTR newVal);
	STDMETHOD(PauseUpdating)();
	STDMETHOD(StopUpdating)();
	STDMETHOD(StartUpdating)(int nUpdateInterval);
	STDMETHOD(Load)(IStream* pIStream);
	STDMETHOD(Save)(IStream* pIStream);
	STDMETHOD(StockCount)(int* cnt);
	STDMETHOD(EnumStocks)(IEnumStocks** ppEnum);
	STDMETHOD(EnumAsString)(IEnumString** ppEnum);
	STDMETHOD(Remove)(BSTR bstrSymbol);
	STDMETHOD(Add)(BSTR bstrSymbol);
	STDMETHOD(Update)();
	STDMETHOD(IsUpdating)(BOOL* b) { return *b = g_bUpdating; }

protected:
	CStockList          m_stockList;        // stock info list.
	CSQSList            m_sqsList;          // stock quotes source list.
	CStockUpdateNotify* m_pStockUpdateNotify;   // ptr to thread object.
	bool                m_bNeedToStopUpdating;  // terminate update now.
	CInternetSession*   m_pINetSession;     // inet session.

	void            ShutdownUpdating();
	void            DelSession(bool bCloseFirst = true);
	void            TermNotifyThread();
	void            PrintStocks();      // for debugging.
	void            SaveString(COleStreamFile& strmFile, CString& s);
	void            LoadString(COleStreamFile& strmFile, CString& s);
};

#endif //__STOCKQUOTES_H_
