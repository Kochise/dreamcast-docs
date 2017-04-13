// ===========================================================================
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright 1996 Microsoft Corporation.  All Rights Reserved.
// ===========================================================================
#include <windows.h>

// ===========================================================================
//                     RecvBuf utility class
// ===========================================================================
class RecvBuf
{
    DWORD  m_cbBufSize; // size of buffer
    PBYTE  m_pbBufBeg;  // start of buffer
    PBYTE  m_pbBufEnd;  // end of buffer

public:

    PBYTE  m_pbDataBeg; // start of data
    PBYTE  m_pbDataEnd; // end of data

    RecvBuf()
    {
        m_pbBufBeg = NULL;
    }

    ~RecvBuf()
    {
        if (m_pbBufBeg)
            LocalFree ((HLOCAL) m_pbBufBeg);
    }

    PBYTE BufBeg(void)   { return m_pbBufBeg; }
    DWORD BufSpace(void) { return m_pbBufEnd - m_pbDataEnd; }
    DWORD BufSize(void)  { return m_cbBufSize; }

    void  BufReset(void)
    {
        m_pbDataBeg = m_pbBufBeg;
        m_pbDataEnd = m_pbBufBeg;
    }

    void BufShift (void)
    {    
        if (m_pbDataBeg > m_pbBufBeg)
        {
            // Shift the data to front of buffer.
            DWORD cbData = m_pbDataEnd - m_pbDataBeg;
            MoveMemory (m_pbBufBeg, m_pbDataBeg, cbData);
            m_pbDataBeg  = m_pbBufBeg;
            m_pbDataEnd  = m_pbBufBeg + cbData;
        }
    }

    BOOL BufAlloc (DWORD dwSize);
    BOOL BufScanStr (PSTR pszSearch, DWORD cbSearch);
    BOOL BufScanInt (DWORD *pdwRet, BYTE cDelimit);
};

