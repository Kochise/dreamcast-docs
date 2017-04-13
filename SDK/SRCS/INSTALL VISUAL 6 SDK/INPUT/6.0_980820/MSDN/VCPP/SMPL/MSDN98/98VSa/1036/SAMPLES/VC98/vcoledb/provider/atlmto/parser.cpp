#include "stdafx.h"
#include "parser.h"
#include "params.h"
#include "mtoprovrs.h"

BOOL CParser::FParseSQLCall(LPCTSTR szSQL)
{
	BOOL    fRet        = TRUE;
	int     ich         = 0;
	BOOL    fCallOpen   = FALSE;

	if (NULL == szSQL)
	{
		ATLTRACE("FParseSQLCall called with NULL pointer!\n");
		return FALSE;
	}

	if (m_fRequiresInit && !FInit())
	{
		ATLTRACE("Parser failed to Initialize in FFParseSQLCall\n");
		return FALSE;
	}


	RemoveWhiteSpace(szSQL, ich);

	if (_tcschr(&(szSQL[ich]), '{') == &(szSQL[ich]))
	{
		ich++;
		fCallOpen = TRUE;
	}

	RemoveWhiteSpace(szSQL, ich);

	if (_tcschr(&(szSQL[ich]), m_szParamMarker[0]) == &(szSQL[ich]))
	{
		ich++;
		RemoveWhiteSpace(szSQL, ich);

		if (_tcschr(&(szSQL[ich]), '=') == &(szSQL[ich]))
		{
			ich++;
			RemoveWhiteSpace(szSQL, ich);
			m_fRetVal = TRUE;
		}
		else
		{
			ATLTRACE("Bad SQL Format: '?' followed by char other that '='\n");
			return FALSE;
		}
	}

	if (_tcsnicmp(&(szSQL[ich]), m_szCall, lstrlen(m_szCall)))
	{
		ATLTRACE("Could not lolcate call keyword in SQL\n");
		return FALSE;
	}

	ich += lstrlen(m_szCall);

	RemoveWhiteSpace(szSQL, ich);

	// Capture Method Name

	BOOL fIsQuoted = szSQL[ich] == '"';

	if (fIsQuoted)
		ich++;

	int ichEndMethod = ich;

	FindEndMethod(szSQL, ichEndMethod, fIsQuoted);

	if (ichEndMethod == ich)
	{
		ATLTRACE("Could not locate a method to call\n");
		return FALSE;
	}

	if ('"' == szSQL[ichEndMethod])
	{
		if (!fIsQuoted)
		{
			ATLTRACE("Found end quote but had no begin\n");
			return FALSE;
		}

	}
	else
	{
		if (fIsQuoted)
		{
			ATLTRACE("Could not find end quote\n");
			return FALSE;
		}
	}

	m_szMethod = new TCHAR[(ichEndMethod - ich) + 1];

	lstrcpyn(m_szMethod, &(szSQL[ich]), (ichEndMethod - ich) + 1);

	ich = ichEndMethod;

	if ('"' == szSQL[ich])
		ich++;

	RemoveWhiteSpace(szSQL, ich);

	if ('(' != szSQL[ich])
	{
		ATLTRACE("Error : ( not found in call\n");
		return FALSE;
	}

	ich++;
	RemoveWhiteSpace(szSQL, ich);

	if (!FParseCallParams(szSQL, ich, fCallOpen))
	{
		ATLTRACE("Failed to parse Call parameter list\n");
		return FALSE;
	}

	return TRUE;
}


BOOL CParser::FInit()
{

	m_szCall = _T("Call");
	m_szParamMarker = _T("?");
	m_fRequiresInit = FALSE;
	return TRUE;
}


BOOL CParser::FParseCallParams(LPCTSTR sz, int& ich, BOOL fCallOpen)
{

	if (_tcschr(&(sz[ich]), m_szParamMarker[0]) == &(sz[ich]))
	{
		ATLTRACE("Handling Bindable Argument\n");
		ich++;
		RemoveWhiteSpace(sz, ich);
		m_cBindableParams++;
	}
	else
	{
		ATLTRACE("Handling ByVal Argument\n");
		if (!FCopyByValParam(sz, ich))
			return FALSE;
		m_cByValParams++;
	}

	if (',' == sz[ich])
	{
		ich++;
		RemoveWhiteSpace(sz, ich);
		return FParseCallParams(sz, ich, fCallOpen);
	}

	if ( '\0' == sz[ich])
	{
		ATLTRACE("Error : Illegal Param list termination, never saw a )\n");

		if (fCallOpen)
			ATLTRACE("Error : Encountered a { but never encountered a }\n");

		return FALSE;
	}

	if (')' == sz[ich])
	{
		ich++;
		RemoveWhiteSpace(sz, ich);

		if (fCallOpen && !('}' == sz[ich]))
		{
			ATLTRACE("Detected an { but not a }\n");
			return FALSE;
		}

		return TRUE;
	}

	ATLTRACE("Bad Param List Format: '?' followed by char other ','\n");
	return FALSE;

	// Got a ByVal Param

	if (',' == sz[ich])
	{
		ich++;
		RemoveWhiteSpace(sz, ich);
		return FParseCallParams(sz, ich, fCallOpen);
	}

	return TRUE;
}


BOOL CParser::FCopyByValParam(LPCTSTR sz, int& ich)
{
	int iBegin = ich;

	FindEndParam(sz, ich);

	if ('\0' == sz[ich])
	{
		ATLTRACE("Error : Illegal Param list termination, never saw a )\n");
		return FALSE;
	}

	if (ich <= iBegin)
	{
		ATLTRACE("In a weird state, Unable to find Param list!!!!\n");
		return FALSE;
	}

	LPTSTR  szParam = new TCHAR[ich - iBegin + 1];

	if (NULL == szParam)
	{
		ATLTRACE("Failed to allocate %d bytes for sz\n", ich - iBegin + 1);
		return FALSE;
	}

	lstrcpyn(szParam, &(sz[iBegin]), ich - iBegin + 1);

	if (m_pCommand == NULL)
	{
		ATLTRACE("ERROR: FCopyByValParam called when m_pStmt == NULL\n");
	   return FALSE;
	}

//  Add ByVal to list at m_cBindableParams + m_cByValParams

	CByValParameter* pByValParam = new CByValParameter(m_cBindableParams +
													   m_cByValParams, szParam);

	if (pByValParam == NULL)
	{
		ATLTRACE("Failed to allocate ByValParam\n");
		return FALSE;
	}

	if (!m_pCommand->m_rgParams.Add(pByValParam))
	{
		ATLTRACE("Failed to add ByVal Param\n");
		delete pByValParam;
		return FALSE;
	}

	RemoveWhiteSpace(sz, ich);

	return TRUE;

}
