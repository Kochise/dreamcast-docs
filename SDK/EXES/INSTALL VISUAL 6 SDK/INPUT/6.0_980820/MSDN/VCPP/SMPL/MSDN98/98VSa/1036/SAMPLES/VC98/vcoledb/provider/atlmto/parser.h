#ifndef __PARSER_H
#define __PARSER_H

class CMtoProvCommand;

class CParser
{

	enum ParamStates
	{
		moreParams,
		eop,
		errorState
	};


public:
	BOOL HasRetval();
	int CParamsWORetval();
	LPCTSTR GetMethod();
	CParser(CMtoProvCommand* pCommand)
	{
		m_pCommand = pCommand;
		m_fRequiresInit     = TRUE;
		m_fRetVal           = FALSE;
		m_szMethod          = NULL;
		m_cBindableParams   = 0;
		m_cByValParams      = 0;
	}
	~CParser()
	{
		if (NULL != m_szMethod)
			delete [] m_szMethod;
	}

	BOOL        FParseSQLCall(LPCTSTR szSQL);
	int         CBindableParameters();

protected:
	int              m_cBindableParams;
	int              m_cByValParams;
	BOOL             m_fRetVal;
	BOOL             m_fRequiresInit;
	TCHAR*           m_szCall;
	TCHAR*           m_szParamMarker;
	TCHAR*           m_szMethod;
	CMtoProvCommand* m_pCommand;


	BOOL        FInit();
	void        RemoveWhiteSpace(LPCTSTR sz, int& ich);
	void        FindNextWhiteSpace(LPCTSTR sz, int& ich);
	void        FindEndParam(LPCTSTR sz, int& ich);
	void        FindEndMethod(LPCTSTR sz, int& ich, BOOL fIsQuoted);
	BOOL        FParseCallParams(LPCTSTR sz, int& ich, BOOL fCallOpen);
	BOOL        FCopyByValParam(LPCTSTR sz, int& ich);
};

inline void CParser::RemoveWhiteSpace(LPCTSTR sz, int& ich)
{
	while(isspace(sz[ich]))
		ich++;
}

inline void CParser::FindNextWhiteSpace(LPCTSTR sz, int& ich)
{
	while(NULL != sz[ich] && !isspace(sz[ich]))
		ich++;
}

inline void CParser::FindEndParam(LPCTSTR sz, int& ich)
{
	while('\0' != sz[ich] && !isspace(sz[ich]) && ',' != sz[ich] &&
		  ')' != sz[ich])
		ich++;
}

inline void CParser::FindEndMethod(LPCTSTR sz, int& ich, BOOL fIsQuoted)
{
	if (fIsQuoted)
	{
		while('\0' != sz[ich] && ',' != sz[ich] && '"' != sz[ich] &&
			  ')' != sz[ich])
			ich++;
	}
	else
	{
		while('\0' != sz[ich] && !isspace(sz[ich]) && ',' != sz[ich] &&
			  ')' != sz[ich])
			ich++;
	}
}

inline int CParser::CBindableParameters()
{
	return (m_fRetVal) ? m_cBindableParams + 1 : m_cBindableParams;
}

inline LPCTSTR CParser::GetMethod()
{
	return m_szMethod;
}

inline int CParser::CParamsWORetval()
{
	return m_cBindableParams + m_cByValParams;
}

inline BOOL CParser::HasRetval()
{
	return m_fRetVal;
}

#endif //__PARSER_H
