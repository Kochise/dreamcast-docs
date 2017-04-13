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
#include "stockdatamgr.h"

static TCHAR    szSymbolFileName[] = _T("stock_symbols.dat");
static TCHAR    szSymbolFilePath[_MAX_PATH + _MAX_FNAME + sizeof(TCHAR)] = _T("\0");

// Set stock info from ';' separated string.
//
void CStockData::SetFromString(TCHAR* szStockData)
{
	TCHAR*  psz = szStockData;
	TCHAR*   p;

	p = _tcstok(psz, _T(";"));
	ASSERT(p);  // should find at least 1.

	m_strSymbol = p;
	p = _tcstok(0, _T(";"));
	ASSERT(p);
	m_fCur = _tcstod(p, 0);
	p = _tcstok(0, _T(";"));
	ASSERT(p);
	m_fChange = _tcstod(p, 0);
}

// Read stock info from stream.
//
IStream& operator >> (IStream& is, CStockData& sd)
{
	TCHAR  szLine[128];
	szLine[0] = 0;
	is.getline(szLine, 127);

	if (*szLine)
		sd.SetFromString(szLine);
	return is;
}

// Write stock info to stream.
//
OStream& operator << (OStream& os, const CStockData& sd)
{
	os << (LPCTSTR)sd.m_strSymbol << _T(";")
	   << sd.m_fCur << _T(";")
	   << sd.m_fChange;

	return os;
}

// Return stock info for given symbol.  If symbol could not be found then
// added it, generate stock info for it and return.
// Returns true if stock symbol was found.
//
bool CStockDataMgr::LookUp(const CString& strSymbol, CStockData& sd)
{
	CString     s = strSymbol;

	s.MakeUpper();

	CStockData  tmp;
	tmp.m_strSymbol = s;
	CStockSymbolList::iterator  i = std::find(m_stockSymbolList.begin(),
											  m_stockSymbolList.end(), tmp);
	if (i != m_stockSymbolList.end())
	{
		AdjPrice(*i);
		sd = *i;
		return true;
	}
	else
	{
		CreateStockData(strSymbol, sd);
		m_stockSymbolList.push_back(sd);
	}
	return false;
}

// Read stock info data file.
//
void CStockDataMgr::LoadStockSymbols()
{
	SetDataFilePath();
	IFStream                                    file(szSymbolFilePath);
	typedef std::istream_iterator<CStockData>   isIter;

	std::copy(isIter(file), isIter(), std::back_inserter(m_stockSymbolList));
}

// Save stock info to data file.
//
void CStockDataMgr::SaveStockSymbols()
{
	OFStream                                    file(szSymbolFilePath);
	typedef std::ostream_iterator<CStockData>   isIter;

	std::copy(m_stockSymbolList.begin(), m_stockSymbolList.end(), isIter(file, _T("\n")));
}

// Create stock info for new stock data object.
//
void CStockDataMgr::CreateStockData(const CString& strSymbol, CStockData& sd)
{
	sd.m_strSymbol = strSymbol;
	sd.m_strSymbol.MakeUpper();
	sd.m_fCur = GenRandPrice();
	sd.m_fChange = 0.0;
}

// Randomly create stock price.  The price is between 5 and 100.
//
float CStockDataMgr::GenRandPrice()
{
	int     minVal = 5;
	int     maxVal = 100;
	int     maxDec = 7;
	float   tmp = 0;

	// generate a random value for current price.
	//
	tmp = minVal + (rand() % maxVal);
	tmp += .125 * (rand() % maxDec);
	return tmp;
}

// Adjust current price by a calculated delta.  Save change in price as well.
//
void CStockDataMgr::AdjPrice(CStockData& sd)
{
	float   fOrigPrice = sd.m_fCur;
	float   fPercentChange = .01 * (rand() % 5);    // 5% max diff.
	float   fChange = sd.m_fCur * fPercentChange;
	bool    bNeg = false;

	if (fOrigPrice > 5.0 && ((rand() % 4) < 2))     // as low as we can go.
		bNeg = true;
	else if (sd.m_fCur >= 150.0)
		return; // can't go higher than 150.

	// round fractional part to nearest 1/8 of a share.
	//
	double  n;
	float   fFrac = modf(fChange, &n);

	fFrac = (int(fFrac / .125)) * .125;

	float   tmp = n + fFrac;    // put float back together again.

	if (bNeg)
		tmp = _chgsign(tmp);
	sd.m_fCur += tmp;
	sd.m_fChange = sd.m_fCur - fOrigPrice;
}

// For debugging (used in console mode).
//
void CStockDataMgr::Print()
{
	typedef std::ostream_iterator<CStockData>   isIter;
	std::copy(m_stockSymbolList.begin(), m_stockSymbolList.end(), isIter(std::cout, _T("\n")));
}

// Set the path to the data file.
//
void CStockDataMgr::SetDataFilePath()
{
	if (szSymbolFilePath[0])        // already set.
		return;
	if (::GetModuleFileName(AfxGetInstanceHandle(), szSymbolFilePath, _MAX_PATH + _MAX_FNAME))
	{
		// replace DLL file name with data file name.
		//
		int len = _tcslen(szSymbolFilePath);
		if (szSymbolFilePath[len-1] == '\\')
			szSymbolFilePath[len-1] = 0;
		TCHAR* p = _tcsrchr(szSymbolFilePath, '\\');
		if (p)
			*(++p) = 0;
	}
	_tcscat(szSymbolFilePath, szSymbolFileName);
	_tcscat(szSymbolFilePath, _T("\0"));
}
