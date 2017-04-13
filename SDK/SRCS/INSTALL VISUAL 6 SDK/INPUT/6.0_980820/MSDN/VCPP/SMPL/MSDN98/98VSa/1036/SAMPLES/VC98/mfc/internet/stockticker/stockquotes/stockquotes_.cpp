// StockQuotes_.cpp : Implementation of CStockQuotes
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
#include "StockQuotes_.h"
#include "enumstocks.h"
#include "stockupdatenotify.h"

static bool  g_bStopUpdating = false;   // stop updating now.
bool         g_bUpdating = false;       // currently updating data from net?

/////////////////////////////////////////////////////////////////////////////
// CEnumStocksAsString

CEnumStocksAsString::~CEnumStocksAsString()
{
	// delete all the stock symbols.
	//
	for (CStocksAsString::iterator i = m_stocksAsString.begin();
		 i != m_stocksAsString.end(); i++)
	{
		::SysFreeString(*i);
	}
	m_stocksAsString.clear();
}

// Return next N stocks, formated in a string.
//
STDMETHODIMP CEnumStocksAsString::Next(ULONG celt, LPOLESTR* rgelt, ULONG* pceltFetched)
{
	if (rgelt == NULL || (celt != 1 && pceltFetched == NULL))
		return E_POINTER;
	if (m_iterCur == m_stocksAsString.end())
		return E_FAIL;
	ULONG nRem = (ULONG)(m_stocksAsString.end() - m_iterCur);
	HRESULT hRes = S_OK;
	if (nRem < celt)
		hRes = S_FALSE;
	ULONG nMin = min(celt, nRem);
	if (pceltFetched != NULL)
		*pceltFetched = nMin;
	while(nMin--)
		CCopy::copy(rgelt++, &(*m_iterCur++));
	return hRes;
}

// Skip the next N stocks.
//
STDMETHODIMP CEnumStocksAsString::Skip(ULONG celt)
{
	if (m_stocksAsString.end() - m_iterCur <  celt)
	{
		m_iterCur = m_stocksAsString.end();
		return S_FALSE;
	}
	m_iterCur += celt;
	return S_FALSE;
}

// Start at the begining.
//
STDMETHODIMP CEnumStocksAsString::Reset(void)
{
	m_iterCur = m_stocksAsString.begin();
	return S_OK;
}

// Make a copy.
//
STDMETHODIMP CEnumStocksAsString::Clone(IEnumString** ppEnum)
{
	typedef CComObject<CEnumStocksAsString> _class;
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
			hRes = p->Init(m_stocksAsString.begin(), m_stocksAsString.end(),
						   m_iterCur);
			if (FAILED(hRes))
				delete p;
			else
			{
				hRes = p->_InternalQueryInterface(IID_IEnumString, (void**)ppEnum);
				if (FAILED(hRes))
					delete p;
			}
		}
	}
	return hRes;
}

// Helper to initialize object.  Use given iterators to transform CStock info
// into a string.  The string has the form: <symbol>: <price>(<change>) OR
// <symbol>: <NA> if stock data is not available.
//
void CEnumStocksAsString::Init(CStockList::iterator s, CStockList::iterator e)
{
	for (CStockList::iterator i = s; i != e; i++)
	{
		CStock      stock = *i;
		CString     str;
		str = stock.GetSymbol();
		str += _T(": ");
		str += stock.GetCurrent();
		if (stock.GetCurrent() != _T("<NA>"))
		{
			str += _T("(");
			str += stock.GetChange() + _T(")");
		}

		m_stocksAsString.push_back(str.AllocSysString());
	}
	m_iterCur = m_stocksAsString.begin();
}

// Initialize from a CStockAsString object - similar to a copy contructor.
//
HRESULT CEnumStocksAsString::Init(CStocksAsString::iterator s,
								  CStocksAsString::iterator e,
								  CStocksAsString::iterator cur)
{
	for (; s != e; s++)
		m_stocksAsString.push_back(::SysAllocString(*s));
	m_iterCur = m_stocksAsString.begin() + (cur - s);
	return S_OK;
}



/////////////////////////////////////////////////////////////////////////////
// CStockQuotes

// If the notify thread is going post message to it and return immediately .
// Otherwise update now, in which case the function will not return until
// the download is complete.
//
STDMETHODIMP CStockQuotes::Update()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	if (m_pStockUpdateNotify)
	{
		m_pStockUpdateNotify->PostThreadMessage(WM_STOCK_UPDATE_NOTIFY_NOW, 0, 0);
		return S_OK;
	}
	else
		return DoUpdate();
}

// Add a stock.  If the stock symbol is already added then do nothing.
//
STDMETHODIMP CStockQuotes::Add(BSTR bstrSymbol)
{
	Lock();

	CStock  s(bstrSymbol);
	if (std::find(m_stockList.begin(), m_stockList.end(), s) ==
		m_stockList.end())
		m_stockList.push_back(s);
	Unlock();
	return S_OK;
}

// Remove a stock.
//
STDMETHODIMP CStockQuotes::Remove(BSTR bstrSymbol)
{
	Lock();
	CStockListIter i = std::find(m_stockList.begin(),
								 m_stockList.end(), CStock(CString(bstrSymbol)));
	if (i != m_stockList.end())
		m_stockList.erase(i);
	Unlock();
	return S_OK;
}

// Return an IEnumString object which contains the formated stock information.
//
STDMETHODIMP CStockQuotes::EnumAsString(IEnumString** ppEnum)
{
	if (ppEnum == NULL)
		return E_POINTER;
	*ppEnum = NULL;
	CComObject<CEnumStocksAsString>* pEnum = NULL;
	ATLTRY(pEnum = new CComObject<CEnumStocksAsString>);
	if (pEnum == NULL)
		return E_OUTOFMEMORY;
	Lock();
	pEnum->Init(m_stockList.begin(), m_stockList.end());
	Unlock();
	HRESULT hRes = pEnum->QueryInterface(IID_IEnumString, (void**)ppEnum);
	if (FAILED(hRes))
		delete pEnum;
	return hRes;
}

// Return an IEnumStocks object which contains the raw stock data.
//
STDMETHODIMP CStockQuotes::EnumStocks(IEnumStocks** ppEnum)
{
	if (ppEnum == NULL)
		return E_POINTER;
	*ppEnum = NULL;
	CComObject<CEnumStocks>* pEnum = NULL;
	ATLTRY(pEnum = new CComObject<CEnumStocks>);
	if (pEnum == NULL)
		return E_OUTOFMEMORY;
	Lock();
	pEnum->Init(m_stockList.begin(), m_stockList.end());
	Unlock();
	HRESULT hRes = pEnum->QueryInterface(IID_IEnumStocks, (void**)ppEnum);
	if (FAILED(hRes))
		delete pEnum;
	return hRes;
}

// Return number of stocks being tracked.
//
STDMETHODIMP CStockQuotes::StockCount(int* cnt)
{
	*cnt = m_stockList.size();
	return S_OK;
}

//
// Save stock symbols to given stream.
//
STDMETHODIMP CStockQuotes::Save(IStream* pIStream)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	Lock();
	COleStreamFile  file(pIStream);
	int             size = m_stockList.size();  // number of stock symbols to save.
	file.Write(&size, sizeof(size));
	for (CStockListIter i = m_stockList.begin(); i != m_stockList.end(); i++)
		SaveString(file, (*i).GetSymbol());

	// save URLs
	//
	CStockQuoteSource*  p = m_sqsList.GetMSInvestor();
	CString             strEmpty(_T(""));
	if (p)
		SaveString(file, p->GetURL());
	else
		SaveString(file, strEmpty);
	p = m_sqsList.GetStockSourceISAPIDll();
	if (p)
		SaveString(file, p->GetURL());
	else
		SaveString(file, strEmpty);

	file.Detach();      // don't want to close the stream.
	Unlock();
	return S_OK;
}

// Load stock symbols from given stream.
//
STDMETHODIMP CStockQuotes::Load(IStream* pIStream)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	Lock();
	COleStreamFile  file(pIStream);

	m_stockList.clear();            // remove all stocks.
	int             size = 0;
	CString         strTmp;
	file.Read(&size, sizeof(size)); // number of stock symbols to read.
	for (int i = 0; i < size; i++)
	{
		LoadString(file, strTmp);
		m_stockList.push_back(CStock(strTmp));      // add to list.
	}

	// load URLs.
	//
	CStockQuoteSource*  p;
	LoadString(file, strTmp);
	if (strTmp.GetLength())
	{
		p = m_sqsList.GetMSInvestor();
		if (p)
			p->SetURL(strTmp);
	}
	LoadString(file, strTmp);
	if (strTmp.GetLength())
	{
		p = m_sqsList.GetStockSourceISAPIDll();
		if (p)
			p->SetURL(strTmp);
	}

	file.Detach();      // don't want to close stream.
	Unlock();
	return S_OK;
}

// Create worker thread that will setup a timer and call back into us
// every "nUpdateInterval" minutes.  If the tread is already runniing just
// adjust the update interval.
//
STDMETHODIMP CStockQuotes::StartUpdating(int nUpdateInterval)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	if (!m_pStockUpdateNotify)
	{
		m_pStockUpdateNotify =
			(CStockUpdateNotify*)AfxBeginThread(RUNTIME_CLASS(CStockUpdateNotify));
		m_pStockUpdateNotify->Init(this);
	}
	if (m_pStockUpdateNotify)
		m_pStockUpdateNotify->SetNotifyInterval(nUpdateInterval);
	return S_OK;
}

// If we are updating (accessing the net) close the connection.  Terminate
// notification thread.
//
STDMETHODIMP CStockQuotes::StopUpdating()
{
	ShutdownUpdating();
	return S_OK;
}

// Set flag indicating that notifications should not occur.
//
STDMETHODIMP CStockQuotes::PauseUpdating()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	if (m_pStockUpdateNotify)
		m_pStockUpdateNotify->SuspendNotifications();
	return S_OK;
}

// Get and Set MS Investor and stock source ISAPI dll URLs.
//
STDMETHODIMP CStockQuotes::SetMSInvestorURL(BSTR newVal)
{
	CStockQuoteSource* pSQS = m_sqsList.GetMSInvestor();
	if (pSQS)
		pSQS->SetURL(newVal);

	return S_OK;
}

STDMETHODIMP CStockQuotes::GetMSInvestorURL(BSTR * pVal)
{
	USES_CONVERSION;

	CComBSTR        bstr(T2BSTR(_T("")));
	CStockQuoteSource* pSQS = m_sqsList.GetMSInvestor();
	if (pSQS)
		bstr = T2BSTR((LPCTSTR)pSQS->GetURL());
	*pVal = bstr.Detach();

	return S_OK;
}

STDMETHODIMP CStockQuotes::SetStockSourceISAPIDllURL(BSTR newVal)
{
	CStockQuoteSource* pSQS = m_sqsList.GetStockSourceISAPIDll();
	if (pSQS)
		pSQS->SetURL(newVal);

	return S_OK;
}

STDMETHODIMP CStockQuotes::GetStockSourceISAPIDllURL(BSTR * pVal)
{
	USES_CONVERSION;

	CComBSTR        bstr(T2BSTR(_T("")));
	CStockQuoteSource* pSQS = m_sqsList.GetStockSourceISAPIDll();
	if (pSQS)
		bstr = T2BSTR((LPCTSTR)pSQS->GetURL());
	*pVal = bstr.Detach();

	return S_OK;
}

// Close any pending updates and terminate thread.
//
void CStockQuotes::FinalRelease()
{
	ShutdownUpdating();
}

HRESULT CStockQuotes::FinalConstruct()
{
	return S_OK;
}

// Connect to net and download data for all stocks.  Close session (connection)
// at end of download.
//
HRESULT CStockQuotes::DoUpdate()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (g_bUpdating)
		return S_OK;

	Lock();
	g_bUpdating = true;
	DWORD   dwAccessType = PRE_CONFIG_INTERNET_ACCESS;

	try
	{
		// pretend we are IE 4.
		//
		m_pINetSession = new CInternetSession(_T("User-Agent: Mozilla/4.0*\r\n"));

		for (CStockListIter i = m_stockList.begin();
			 !g_bStopUpdating && i != m_stockList.end(); i++)
		{
			bool    bFoundInfo = false;
			for (CSQSList::iterator j = m_sqsList.begin();
				 !g_bStopUpdating && j != m_sqsList.end(); j++)
			{
				if ((*j)->Update(*m_pINetSession, *i))
				{
					bFoundInfo = true;
					break;
				}
			}
			if (!bFoundInfo)   // no stock info, set indicator string.
				i->SetCurrent(_T("<NA>"));
		}
		Fire_InfoUpdate();
	}
	catch(CInternetException* e)
	{
		// if closed prematurely then ok, otherwise let user know.
		//
		if (e->m_dwError != ERROR_INVALID_HANDLE)
		{
			TCHAR   buf[1025];
			e->GetErrorMessage(buf, 1024);
			::MessageBox(0, buf, _T("Stock Quotes Component Error"),
						 MB_ICONEXCLAMATION | MB_OK);
		}
		e->Delete();
	}
	DelSession();
	g_bUpdating = false;
	Unlock();
	return S_OK;
}

// Helper function to shutdown the updating process, terminates any pending
// updates.
//
void CStockQuotes::ShutdownUpdating()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	g_bStopUpdating = true;
	if (m_pINetSession)
		m_pINetSession->Close();

	TermNotifyThread();
	DelSession(false);
	g_bStopUpdating = false;
}

// Helper function to close and delete session.
//
void CStockQuotes::DelSession(bool bCloseFirst)
{
	if (bCloseFirst && m_pINetSession)
		m_pINetSession->Close();
	delete m_pINetSession;
	m_pINetSession = 0;
}

// Helper function to terminate notification thread.
// Waits for thread to end, otherwise we could get a memory leak when things
// shutdown.
//
void CStockQuotes::TermNotifyThread()
{
	if (m_pStockUpdateNotify)
	{
		HANDLE hThread = m_pStockUpdateNotify->m_hThread;
		m_pStockUpdateNotify->PostThreadMessage(WM_QUIT, 0, 0);
		::WaitForSingleObject(hThread, 30000);
	}
}

// Write CString to stream.
//
//
void CStockQuotes::SaveString(COleStreamFile& strmFile, CString& s)
{
	int     size;
	LPTSTR  psz;
	size = s.GetLength();
	psz = s.LockBuffer();
	strmFile.Write(&size, sizeof(size));        // size of string.
	strmFile.Write(psz, size);                  // string.
	s.UnlockBuffer();
}

// Read CString from stream.
//
//
void CStockQuotes::LoadString(COleStreamFile& strmFile, CString& s)
{
	TCHAR           buf[128];       // more than enough for a stock symbol.
	int             strSize = 0;

	memset(buf, 0, sizeof(TCHAR)*128);
	strmFile.Read(&strSize, sizeof(strSize));   // size of string.
	strmFile.Read(buf, strSize);
	s = buf;
}


// debugging function.
// format:
// <symbol>:<price> <change>
void CStockQuotes::PrintStocks()
{
#if 0   // set to 1 to use.
	for (CStockListIter i = m_stockList.begin();
		 i != m_stockList.end(); i++)
	{
		CStock  s = *i;
		std::cout << (LPCTSTR)s.GetSymbol() << _T(":") << (LPCTSTR)s.GetCurrent() << _T(" ")
				  << (LPCTSTR)s.GetChange() << std::endl;
	}
#endif
}


///////////////////////////////////////////////////////////////////////////////
// CStockQuoteSource
//

// StripTags() rips through a buffer and removes HTML tags from it.
// The function uses a static variable to remember its state in case
// a HTML tag spans a buffer boundary.
//
void CStockQuoteSource::StripTags(LPTSTR pszBuffer)
{
	LPTSTR pszSource = pszBuffer;
	LPTSTR pszDest = pszBuffer;

	while (*pszSource != '\0')
	{
		if (m_bInTag)
		{
			if (*pszSource == '>')
				m_bInTag = FALSE;
			pszSource++;
		}
		else
		{
			if (*pszSource == '<')
				m_bInTag = TRUE;
			else
			{
				*pszDest = *pszSource;
				pszDest++;
			}
			pszSource++;
		}
	}
	*pszDest = '\0';
}


// Strips extra WS such that there are no 2 or more adjacent WS characters.
// Don't add space after the '/' character.
//
void CStockQuoteSource::StripExtraSpace(CString& s)
{
	CString temp;
	int     size = s.GetLength();

	for (int i = 0; i < size; i++)
	{
		int x = i;
		while (i < size && _istspace(s[i]))
			i++;
		if ((i - x > 0) &&
			(s[x-1] != _T('/') && s[x-1] != _T('+') && s[x-1] != _T('-')))
			temp += _T(' ');
		temp += s[i];
	}
	s = temp;
}


// Do the download of the stock info.  Several types of exceptions may be
// thrown.  Just return 0 on an exception unless it is a CInternetException,
// then pass it on up.
//
bool CStockQuoteSource::DownloadStockInfo(CInternetSession& session, CStock& stock)
{
	TCHAR               pszURL[1024];   // URL to connect to.
	DWORD               dwHttpRequestFlags = INTERNET_FLAG_EXISTING_CONNECT;
	const TCHAR         szHeaders[] =
//!:        _T("Accept: text/*\r\nUser-Agent: Stock Quotes\r\n");
		_T("Accept: text/*\r\nUser-Agent: Mozilla/4.0*\r\n");

	CHttpConnection*    pServer = NULL;
	CHttpFile*          pFile = NULL;
	bool                retval = true;

	m_bInTag = false;
	// construct URL to connect to.
	//
	_tcscpy(pszURL, (LPCTSTR)GetURL());
	_tcscat(pszURL, (LPCTSTR)stock.GetSymbol());
	try
	{
		CString         strServerName;
		CString         strObject;
		INTERNET_PORT   nPort;
		DWORD           dwServiceType;

		if (!AfxParseURL(pszURL, dwServiceType, strServerName, strObject, nPort) ||
			dwServiceType != INTERNET_SERVICE_HTTP)
		{
			throw 1;
		}

		if (g_bStopUpdating)
			throw 99;

		pServer = session.GetHttpConnection(strServerName, nPort);

		if (g_bStopUpdating)
			throw 99;

		pFile = pServer->OpenRequest(CHttpConnection::HTTP_VERB_GET,
			strObject, NULL, 1, NULL, NULL, dwHttpRequestFlags);
//!:        pFile->AddRequestHeaders(szHeaders);
		pFile->SendRequest();

		if (g_bStopUpdating)
			throw 99;

		DWORD dwRet;
		pFile->QueryInfoStatusCode(dwRet);

		// if access was denied exit out.

		if (dwRet == HTTP_STATUS_DENIED)
		{
			throw 1;
		}

		if (g_bStopUpdating)
			throw 99;

		retval = SetStockInfo(pFile, stock);

		pFile->Close();
		pServer->Close();
	}
	catch(CInternetException* e)
	{
		if (pFile != NULL)
			delete pFile;
		if (pServer != NULL)
			delete pServer;

		retval = false;
		throw e;
	}
	catch(...)
	{
		retval = false;
	}

	if (pFile != NULL)
		delete pFile;
	if (pServer != NULL)
		delete pServer;

	return retval;
}

// Read data from net and attempt to find key words that identify where
// the stock info is.
//
bool CStockQuoteSource::SetStockInfoHelper(CHttpFile* pFile, CStock& stock, TCHAR* szCurText, TCHAR* szChangeText)
{
	CString cur;
	CString change;
	int     cnt = 0;

	TCHAR sz[1024];
	while (!g_bStopUpdating && pFile->ReadString(sz, 1023) && cnt != 2)
	{
		StripTags(sz);
		if (cnt == 0 && ParseStockInfo(sz, szCurText, cur))
		{
			stock.SetCurrent(cur);
			cnt++;
		}

		// assume change value comes after current.
		//
		if (cnt == 1 && ParseStockInfo(sz, szChangeText, change))
		{
			stock.SetChange(change);
			cnt++;
		}
	}
	return cnt == 2;
}

// Using the szHeader member try to find the "key word" that identifies the
// stock info.  If found then read until we run into something other than
// a space, digit, +, -, or / characters.  If this algorithm does not
// work for your site, just override.
//
bool CStockQuoteSource::ParseStockInfo(TCHAR* szBuf, TCHAR* szHeader, CString& strResult)
{
	TCHAR*  temp = _tcsstr(szBuf, szHeader);

	if (temp)
	{
		temp += _tcslen(szHeader);

		// skip leading WS so the first character to be processed can be checked for
		// validity more accurately.
		while (*temp && _istspace(*temp)) temp++;
	}
	while(temp && *temp)
	{
		if (_istdigit(*temp) || _istspace(*temp) || *temp == '+' || *temp == '-' || *temp == '/' || *temp == '.')
			strResult += *temp;
		else
			break;
		temp++;
	}
	if (!strResult.IsEmpty())
	{
		strResult.TrimLeft();
		strResult.TrimRight();
		StripExtraSpace(strResult);
		return true;
	}
	return false;
}

// This helper function just checks to see if the given url ends with a '='.
// If is does then there is nothing else to do.  Otherwise append the given tail
// to the url.
//
//
//
void CStockQuoteSource::SetURLHelper(const CString& strURL,
									 const CString& strURLTail)
{
	m_strURL = strURL;
	if (strURL[strURL.GetLength()-1] != '=')
		m_strURL += strURLTail;
}

//////////////////////////////////////////////////////////////////////////////
// CSQSMSInvestor
//
bool CSQSMSInvestor::SetStockInfo(CHttpFile* pFile, CStock& stock)
{
	return SetStockInfoHelper(pFile, stock, _T("Last\n"), _T("Change\n"));
}

bool CSQSMSInvestor::ParseStockInfo(TCHAR* szBuf, TCHAR* szHeader, CString& strResult)
{
	TCHAR*  temp;
	if (!m_bFoundHeader)
	{
		temp = _tcsstr(szBuf, szHeader);
		if (temp)
		{
			temp += _tcslen(szHeader);
			m_bFoundHeader = true;
		}
	}
	else
		temp = szBuf;

	if (temp)
	{
		// skip leading WS so the first character to be processed can be checked for
		// validity more accurately.
		// also skip everything up to first $.
		bool    bNeg = false;
		while (*temp && *temp != '$')
		{
			if (*temp == '-')
				bNeg = true;
			temp++;
		}
		if (*temp && bNeg)
			strResult += _T("-");

		while(temp && *temp)
		{
			temp++;
			if (_istdigit(*temp) || *temp == '.')
				strResult += *temp;
			else
				break;
		}

		if (!strResult.IsEmpty())
		{
			strResult.TrimLeft();
			strResult.TrimRight();
			StripExtraSpace(strResult);
			m_bFoundHeader = false;
			return true;
		}
	}
	return false;
}

//////////////////////////////////////////////////////////////////////////////
// ISAPI Dll Stock Source
//

bool CSQSISAPIDll::SetStockInfo(CHttpFile* pFile, CStock& stock)
{
	return SetStockInfoHelper(pFile, stock, _T("Current:"), _T("Change:"));
}

//////////////////////////////////////////////////////////////////////////////
// CSQSList
//
void CSQSList::Init()
{
	// add new Stock Source objects here.
	push_back(new CSQSISAPIDll);
}

CStockQuoteSource* CSQSList::GetMSInvestor()
{
	for (iterator i = begin(); i != end(); i++)
		if ((*i)->IsMSInvestor())
			return *i;
	return 0;
}

CStockQuoteSource* CSQSList::GetStockSourceISAPIDll()
{
	for (iterator i = begin(); i != end(); i++)
		if ((*i)->IsISAPIDll())
			return *i;
	return 0;
};


void CSQSList::Cleanup()
{
	for (iterator i = begin(); i != end(); i++)
		delete *i;
	clear();
}
