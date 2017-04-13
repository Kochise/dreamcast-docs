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
#if !defined(__STOCKDATAMGR_H__)
#define __STOCKDATAMGR_H__

typedef std::basic_istream<TCHAR> IStream;
typedef std::basic_ostream<TCHAR> OStream;
typedef std::basic_ifstream<TCHAR> IFStream;
typedef std::basic_ofstream<TCHAR> OFStream;


struct CStockData
{
	CStockData() : m_fCur(0.0), m_fChange(0.0) {}
	CString     m_strSymbol;
	float       m_fCur;
	float       m_fChange;

	bool operator == (const CStockData& sd) const
		{ return m_strSymbol == sd.m_strSymbol; }
	bool operator != (const CStockData& sd) const
		{ return !(*this == sd); }
	bool operator < (const CStockData& sd) const
		{ return m_strSymbol < sd.m_strSymbol; }
	bool operator > (const CStockData& sd) const
		{ return m_strSymbol > sd.m_strSymbol; }

	void SetFromString(TCHAR* szStockData);
};

class CStockDataMgr
{
public:
	CStockDataMgr() { srand((unsigned)time(0)); }
	~CStockDataMgr() {}

	bool                LookUp(const CString& strSymbol, CStockData& sd);
	void                LoadStockSymbols();
	void                SaveStockSymbols();
	void                Print();    // for debugging.

protected:
	typedef std::list<CStockData>   CStockSymbolList;

	CStockSymbolList    m_stockSymbolList;

	void                CreateStockData(const CString& strSymbol, CStockData& sd);
	float               GenRandPrice();
	void                AdjPrice(CStockData& sd);
	void                SetDataFilePath();
};


#endif // __STOCKDATAMGR_H__
