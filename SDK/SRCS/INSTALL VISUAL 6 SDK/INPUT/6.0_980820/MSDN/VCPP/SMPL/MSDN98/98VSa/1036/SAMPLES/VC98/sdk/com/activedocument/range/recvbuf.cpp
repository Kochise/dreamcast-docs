// ===========================================================================
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright 1996 Microsoft Corporation.  All Rights Reserved.
// ===========================================================================
#include "recvbuf.hpp"
#include <limits.h>

#define upcase(c)  ((BYTE) CharUpper ((LPSTR) (BYTE) (c)))

// ---------------------------------------------------------------------------
// CUrlmonCallback::BufScanStr
// Utility to seek for a string in a memory buffer.
// ---------------------------------------------------------------------------
BOOL RecvBuf::BufAlloc (DWORD dwSize)
{
    m_cbBufSize = dwSize;
    m_pbBufBeg = (PBYTE) LocalAlloc (LMEM_FIXED, m_cbBufSize);
    if (!m_pbBufBeg)
        return FALSE;
    m_pbBufEnd = m_pbBufBeg + m_cbBufSize;
    m_pbDataBeg = m_pbBufBeg;
    m_pbDataEnd = m_pbBufBeg;
    return TRUE;
}

// ---------------------------------------------------------------------------
// CUrlmonCallback::SeekPastString
// Utility to seek for a string in a memory buffer.
// ---------------------------------------------------------------------------
BOOL RecvBuf::BufScanStr (PSTR pszSearch, DWORD cbSearch)
{
	PBYTE pbLimit = m_pbDataEnd - cbSearch;
	
	while (1)
	{
	    DWORD ibSearch;
	    
		// Check for overflow.
		if (m_pbDataBeg >= pbLimit)
			return FALSE;

	    for (ibSearch = 0; ibSearch < cbSearch; ibSearch++)
	    {
	        if (upcase(m_pbDataBeg[ibSearch]) != upcase(pszSearch[ibSearch]))
	            break;
	    }

	    if (ibSearch == cbSearch)
	    {
	        // Found it.
   	        m_pbDataBeg += cbSearch;
	        return TRUE;
	    }
	    else
	    {
	        m_pbDataBeg++;
	        continue;
	    }
	}
}

// ---------------------------------------------------------------------------
// Utility to scan a 32-bit integer from memory buffer.
// Returns FALSE on integer overflow or end of buffer.
// ---------------------------------------------------------------------------
BOOL RecvBuf::BufScanInt (DWORD *pdwRet, BYTE cDelimit)
{
	DWORD dwRet = 0;

	// Scan past non-delimiters and non-digits.
	while (*m_pbDataBeg != cDelimit && !isdigit(*m_pbDataBeg))
	{
		if (++m_pbDataBeg >= m_pbDataEnd)
			return FALSE;
	}
	
	while (*m_pbDataBeg != cDelimit)
	{
		if (!isdigit(*m_pbDataBeg))
			return FALSE;
		if (dwRet > ULONG_MAX / 10)
			return FALSE;
		dwRet *= 10;
		dwRet += *m_pbDataBeg - '0';
		if (++m_pbDataBeg >= m_pbDataEnd)
			return FALSE;
	}

	*pdwRet = dwRet;
	return TRUE;
}

