// ===========================================================================
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright 1996 Microsoft Corporation.  All Rights Reserved.
// ===========================================================================
#include <urlmon.h>
#include <wininet.h>
#include "callback.hpp"

#define BOUNDARY_MAXSIZE 500 
#define RECV_BUF_SIZE   8192

static char szCRLF[] = "\r\n";
static char szLF[]   = "\n";

// ---------------------------------------------------------------------------
// CUrlmonCallback::CUrlmonCallback
// ---------------------------------------------------------------------------
CUrlmonCallback::CUrlmonCallback (PHTTP_REQUEST_PARAM pParam)
{
    m_pBinding = NULL;
    m_pstm = NULL;
    m_cRef = 0;

    m_pParam = pParam;

    if (m_pParam->punkOuter)
        ((IUnknown *) m_pParam->punkOuter)->AddRef();
    
    m_CBParam.cbStruct = sizeof(m_CBParam);
    m_CBParam.dwRequestCtx = m_pParam->dwRequestCtx;

    m_dwOffset = 0;
    m_dwResponseCode = 0;
    m_pszRangeDelimiter = NULL;
}

// ---------------------------------------------------------------------------
// CUrlmonCallback::~CUrlmonCallback
// ---------------------------------------------------------------------------
CUrlmonCallback::~CUrlmonCallback()
{
    if (m_pParam->punkOuter)
        ((IUnknown *) m_pParam->punkOuter)->Release();
    if (m_pstm)
        m_pstm->Release();
    if (m_pszRangeDelimiter)
        LocalFree ((HLOCAL) m_pszRangeDelimiter);
}

// ---------------------------------------------------------------------------
// CUrlmonCallback::QueryInterface
// ---------------------------------------------------------------------------
STDMETHODIMP CUrlmonCallback::QueryInterface(REFIID riid, void** ppv)
{ 
    if(IsEqualGUID(riid,IID_IUnknown))
        *ppv = (IUnknown *) (IBindStatusCallback *) this;
    else if (IsEqualGUID(riid,IID_IBindStatusCallback))
        *ppv = (IBindStatusCallback *) this;
    else if (IsEqualGUID(riid, IID_IHttpNegotiate))
        *ppv = (IHttpNegotiate *) this;
    else
        *ppv = NULL;

    if (!*ppv)
        return E_NOINTERFACE;
    
    // Increment our reference count before we hand out our interface
    ((LPUNKNOWN)*ppv)->AddRef();
    return S_OK;

}


// ---------------------------------------------------------------------------
// CUrlmonCallback::AddRef
// ---------------------------------------------------------------------------
STDMETHODIMP_(ULONG) CUrlmonCallback::AddRef(void)
{
    if (m_pParam->punkOuter)
        ((IUnknown *) m_pParam->punkOuter)->AddRef();
    return m_cRef++;
}


// ---------------------------------------------------------------------------
// CUrlmonCallback::Release
// ---------------------------------------------------------------------------
STDMETHODIMP_(ULONG) CUrlmonCallback::Release(void)
{
    if (m_pParam->punkOuter)
        ((IUnknown *) m_pParam->punkOuter)->Release();

    if (--m_cRef == 0)
    {
        delete this;
        return 0;
    }
    return m_cRef;
}

// ---------------------------------------------------------------------------
// CUrlmonCallback::BeginningTransaction
// ---------------------------------------------------------------------------
STDMETHODIMP
CUrlmonCallback::BeginningTransaction (LPCWSTR szURL,
    LPCWSTR szHeaders, DWORD dwReserved, LPWSTR *ppszAdditionalHeaders)
{
    static char szRangeHeader[] = "Range: bytes=";
    static char szUnlessHeader[] = "Unless-Modified-Since: ";

    HRESULT hr = S_OK;
    PSTR pszHeader = NULL;
    
    // Don't add any headers if not a range request.
    DWORD cRanges = m_pParam->cRanges;
    if (!cRanges)
    {
        *ppszAdditionalHeaders = NULL;
        goto done;
    }

    PHTTP_REQUEST_RANGE pRanges;
    pRanges = m_pParam->pRanges;

    // Allocate ANSI buffer.
    DWORD cbHeader;
    cbHeader = sizeof(szRangeHeader) + 20 * cRanges + 2;
    if (m_pParam->pstUnlessModifiedSince)
       cbHeader += sizeof(szUnlessHeader) + INTERNET_RFC1123_BUFSIZE + 2;
    pszHeader = (PSTR) LocalAlloc (LMEM_FIXED, cbHeader);
    if (!pszHeader)
    {
        hr = E_OUTOFMEMORY;
        goto done;
    }

    // Format the read range request header.
    UINT cchHeader;
    cchHeader = wsprintf (pszHeader, "%s", szRangeHeader);

    // Add the ranges.
    while (cRanges--)
    {
        if (pRanges->dwSize)
        {
            // Format range, end value is inclusive.
            cchHeader += wsprintf (pszHeader + cchHeader, "%d-%d",
                pRanges->dwOffset, pRanges->dwOffset + pRanges->dwSize - 1);
        }
        else
        {
            // Format range to end of file.
            cchHeader += wsprintf (pszHeader + cchHeader, "%d-",
                pRanges->dwOffset);
        }
            
        pRanges++;
        if (cRanges)
           cchHeader += wsprintf (pszHeader + cchHeader, ", ");
        else
           cchHeader += wsprintf (pszHeader + cchHeader, szCRLF);
    }

    if (m_pParam->pstUnlessModifiedSince)
    {
        // Add unless-modified-since qualifier.
        cchHeader += wsprintf (pszHeader + cchHeader, szUnlessHeader);
        if (!InternetTimeFromSystemTime
        (
            m_pParam->pstUnlessModifiedSince,
            INTERNET_RFC1123_FORMAT,
            pszHeader + cchHeader,
            INTERNET_RFC1123_BUFSIZE
        ))
        {
            hr = E_FAIL;
            goto done;
        }
        
        cchHeader += lstrlen (pszHeader + cchHeader);
        cchHeader += wsprintf (pszHeader + cchHeader, szCRLF);
    }

    cchHeader++; // for NULL termination

    // Allocate Unicode buffer.
    *ppszAdditionalHeaders = (WCHAR *) CoTaskMemAlloc (sizeof(WCHAR) * cchHeader);
    if (*ppszAdditionalHeaders)
    {
        MultiByteToWideChar (CP_ACP, 0, pszHeader, -1, *ppszAdditionalHeaders,
            sizeof(WCHAR) * cchHeader);
    }

    hr = *ppszAdditionalHeaders? S_OK : E_OUTOFMEMORY;

done:
    if (pszHeader)
        LocalFree (pszHeader);
    return hr;
}

// ---------------------------------------------------------------------------
// CUrlmonCallback::OnResponse
// ---------------------------------------------------------------------------
STDMETHODIMP CUrlmonCallback::OnResponse
(
    DWORD   dwResponseCode, 
    LPCWSTR szResponseHeaders,
    LPCWSTR szRequestHeaders,
    LPWSTR  *pszAdditionalRequestHeaders
)
{
    // Get the HttpQueryInfo wrapper object.
    IWinInetHttpInfo *pHttpInfo = NULL;
    HRESULT hr = m_pBinding->QueryInterface
        (IID_IWinInetHttpInfo, (void **) &pHttpInfo);
    if (FAILED(hr))
        goto done;

    // Save the response code.
    m_dwResponseCode = dwResponseCode;
    m_CBParam.dwResponseCode = dwResponseCode;

    DWORD cbBuf;

    // Check for partial response.
    if (dwResponseCode == 206)
    {
       // Server responded with byte ranges, ergo must support them.
       m_CBParam.fdwRequestFlags = HTTP_REQUEST_ACCEPT_RANGES;

       // Look for multi-part delimiter embedded in content type.
       const static char szMultiPart[] = "multipart/x-byteranges; boundary";
       const static DWORD cbMultiPart = sizeof(szMultiPart);

       // Get length of buffer to hold content type.
       DWORD cbContentType = 0;
       pHttpInfo->QueryInfo
          (HTTP_QUERY_CONTENT_TYPE, NULL, &cbContentType, NULL, 0);

       if (cbContentType > cbMultiPart + 1)
       {
            // Content type is big enough to embed a delimiter.
            m_pszRangeDelimiter = (PSTR) LocalAlloc (LMEM_FIXED, cbContentType);
            if (!m_pszRangeDelimiter)
            {
                hr = E_OUTOFMEMORY;
                goto done;
            }

            if (S_OK != pHttpInfo->QueryInfo (HTTP_QUERY_CONTENT_TYPE,
                 m_pszRangeDelimiter, &cbContentType, NULL, 0))
            {
                hr = E_FAIL;
                goto done;
            } 
            
            // Split the string at the '='
            m_pszRangeDelimiter[cbMultiPart - 1] = 0;
            if (lstrcmpi (m_pszRangeDelimiter, szMultiPart))
            {
                // Response must not be multi-part.
                LocalFree ((HLOCAL) m_pszRangeDelimiter);
                m_pszRangeDelimiter = NULL;
            }
            else
            {
                m_cchRangeDelimiter =
                    lstrlen (m_pszRangeDelimiter + cbMultiPart);

                // Shift the delimiter to offset 2 of string.
                MoveMemory
                (
                  m_pszRangeDelimiter + 2, // +2 for prefix
                  m_pszRangeDelimiter + cbMultiPart,
                  m_cchRangeDelimiter + 1  // +1 for null
                );    

                // Prefix delimiter with "--"
                m_pszRangeDelimiter[0] = '-';
                m_pszRangeDelimiter[1] = '-';
                m_cchRangeDelimiter += 2;

                // Initialize range boundaries.
                m_dwRangeBeg = 0;
                m_dwRangeEnd = 0;
            }
            
        } // end if (cbContentType > cbMultiPart + 1)

        // Adjust the offset if we have a single range
        if (!m_pszRangeDelimiter)
            m_dwOffset = m_pParam->pRanges[0].dwOffset;
    }
    
    else // if (dwResponseCode != 206)
    {
        // Check if ranges are supported.
        static char szBytes[] = "bytes";
        char szBuf[sizeof(szBytes)];
        cbBuf = sizeof(szBytes);
        hr = pHttpInfo->QueryInfo
            (HTTP_QUERY_ACCEPT_RANGES, szBuf, &cbBuf, NULL, 0);
        if (SUCCEEDED(hr) && !lstrcmpi (szBytes, szBuf))
            m_CBParam.fdwRequestFlags = HTTP_REQUEST_ACCEPT_RANGES;
        else
            m_CBParam.fdwRequestFlags = 0;
    }

    // Get last modified time.
    SYSTEMTIME stLastModified;
    cbBuf = sizeof(stLastModified);
    hr = pHttpInfo->QueryInfo
    (
        HTTP_QUERY_FLAG_SYSTEMTIME | HTTP_QUERY_LAST_MODIFIED,
        &stLastModified, &cbBuf, NULL, 0
    );
    if (hr != S_OK)
    {
        memset (&stLastModified, 0, sizeof(stLastModified));
        hr = S_OK;
    }
    m_CBParam.pstLastModified = &stLastModified;
                
    // Get content length.
    m_CBParam.dwContentLength = 0;
    if (dwResponseCode != 206)
    {   
        cbBuf = sizeof(m_CBParam.dwContentLength);
        hr = pHttpInfo->QueryInfo
        (
            HTTP_QUERY_FLAG_NUMBER | HTTP_QUERY_CONTENT_LENGTH,
            &m_CBParam.dwContentLength, &cbBuf, NULL, 0
        );
        if (hr != S_OK)
        {
            m_CBParam.dwContentLength = 0;
            hr = S_OK;
        }
    }


    // Inform the client the request is started.
    m_CBParam.CallbackType = REQUESTCB_STARTED;
    if (!(*(m_pParam->pfnRequestCB)) (&m_CBParam))
         m_pBinding->Abort();
    hr = S_OK;

done:

    if (pHttpInfo)
        pHttpInfo->Release();
    
    return hr;
}

// ---------------------------------------------------------------------------
// CUrlmonCallback::OnStartBinding
// ---------------------------------------------------------------------------
STDMETHODIMP CUrlmonCallback::OnStartBinding
    (DWORD grfBSCOption, IBinding* pBinding)
{
    if (pBinding != NULL)
    {
         m_pBinding = pBinding;
         m_pBinding->AddRef();
    }
    
    // Initialize receive buffer.
    if (!BufAlloc(RECV_BUF_SIZE))
        return E_OUTOFMEMORY;
        
    return S_OK;
}

// ---------------------------------------------------------------------------
// CUrlmonCallback::GetPriority
// ---------------------------------------------------------------------------
STDMETHODIMP CUrlmonCallback::GetPriority(LONG* pnPriority) 
{
    return E_NOTIMPL;
}

// ---------------------------------------------------------------------------
// CUrlmonCallback::OnLowResource
// ---------------------------------------------------------------------------
STDMETHODIMP CUrlmonCallback::OnLowResource(DWORD dwReserved)
{
    return E_NOTIMPL;
}

// ---------------------------------------------------------------------------
// CUrlmonCallback::OnProgress
// ---------------------------------------------------------------------------
STDMETHODIMP CUrlmonCallback::OnProgress
    (ULONG ulProgress, ULONG ulProgressMax, ULONG ulStatusCode, LPCWSTR szStatusText)
{
    return S_OK;
}

// ---------------------------------------------------------------------------
// CUrlmonCallback::OnStopBinding
// ---------------------------------------------------------------------------
STDMETHODIMP CUrlmonCallback::OnStopBinding
    (HRESULT hrStatus, LPCWSTR pszError) 
{
    // Release the binding, which will eventually release the callback object.
    m_pBinding->Release();
    m_pBinding = NULL;

    // Notify the client that we are done.
    m_CBParam.CallbackType = REQUESTCB_DONE;
    m_CBParam.hrRequest = hrStatus;
    (*(m_pParam->pfnRequestCB)) (&m_CBParam);
    
    return S_OK;
}

// ---------------------------------------------------------------------------
// CUrlmonCallback::GetBindInfo
// ---------------------------------------------------------------------------
STDMETHODIMP CUrlmonCallback::GetBindInfo
    (DWORD* pgrfBINDF, BINDINFO* pbindInfo)
{
    *pgrfBINDF = BINDF_ASYNCHRONOUS | BINDF_ASYNCSTORAGE | BINDF_PULLDATA;
    *pgrfBINDF |= BINDF_GETNEWESTVERSION;
    pbindInfo->cbSize = sizeof(BINDINFO);
    pbindInfo->szExtraInfo = NULL;
    ZeroMemory (&pbindInfo->stgmedData, sizeof(STGMEDIUM));
    pbindInfo->grfBindInfoF = 0;
    pbindInfo->dwBindVerb = BINDVERB_GET;
    pbindInfo->szCustomVerb = NULL;
    return S_OK;
}

// ---------------------------------------------------------------------------
// CUrlmonCallback::OnDataAvailable
// ---------------------------------------------------------------------------
STDMETHODIMP CUrlmonCallback::OnDataAvailable
    (DWORD grfBSCF, DWORD dwSize, FORMATETC* pfmtetc, STGMEDIUM* pstgmed) 
{
    if (!m_pstm && pstgmed->tymed == TYMED_ISTREAM)
    {
        m_pstm = pstgmed->pstm;
        m_pstm->AddRef();
        m_CBParam.CallbackType = REQUESTCB_DATA;
    }

    // Check for multi-part response.
    if (m_pszRangeDelimiter)
       return ParseMultiPartBuffer (grfBSCF & BSCF_LASTDATANOTIFICATION);

    HRESULT hrRead;
    DWORD cbActual;

    do // until hrRead != S_OK
    {
        // Read some more data.
        hrRead = m_pstm->Read (BufBeg(), BufSize(), &cbActual);

        // Notify the client we got some data.
        if (cbActual)
        {
            m_CBParam.dwDataOffset = m_dwOffset;
            m_CBParam.lpDataBuffer = BufBeg();
            m_CBParam.cbDataLength = cbActual;
            if (!(*(m_pParam->pfnRequestCB)) (&m_CBParam))
            {
                 // Client wants to stop.
                 m_pBinding->Abort();
                 return S_OK;
            }
        }   

        m_dwOffset += cbActual;
        
    } while (hrRead == S_OK);

    return (hrRead == S_FALSE || hrRead == E_PENDING)? S_OK : hrRead;
}

// ---------------------------------------------------------------------------
// CUrlmonCallback::OnObjectAvailable
// ---------------------------------------------------------------------------
STDMETHODIMP CUrlmonCallback::OnObjectAvailable(REFIID riid, IUnknown* punk) 
{
    return E_NOTIMPL;
}

// ---------------------------------------------------------------------------
// CUrlmonCallback::ParseMultiPartHeader
// ---------------------------------------------------------------------------
BOOL CUrlmonCallback::ParseMultiPartHeader (void)
{
    // multi-part boundary string literals.
    static char szContentType[]  = "Content-Type: ";
    static char szContentRange[] = "Content-Range: bytes ";

// Some macros for prettiness...
#define GrokStr(str) if (!BufScanStr (str, sizeof(str)-1)) return FALSE;
#define GrokInt(pint, delim) if (!BufScanInt (pint,delim)) return FALSE;

	// Check for presence of boundary.
    if (m_dwRangeBeg > 0) // must not be first range
	    GrokStr (szLF);   // will also detect a CR-LF
	if (!BufScanStr (m_pszRangeDelimiter, m_cchRangeDelimiter))
	    return FALSE;

	// Check for end boundary.
	if
	(    m_pbDataBeg + 2 <= m_pbDataEnd
		&& m_pbDataBeg[0] == '-'
		&& m_pbDataBeg[1] == '-'
	)
	{
	    m_dwRangeBeg = 0;
	    m_dwRangeEnd = 0;
	    return TRUE;
    }
    
	// Scan content type and data range.
	GrokStr (szLF);
	GrokStr (szContentType);
	GrokStr (szLF);
	GrokStr (szContentRange);
    GrokInt (&m_dwRangeBeg, '-');
    GrokInt (&m_dwRangeEnd, '/');
    GrokStr (szLF);
    GrokStr (szLF);
    
    // Range end is inclusive; make it exclusive.
    m_dwRangeEnd++; 
    return TRUE;

#undef GrokStr
#undef GrokInt
}

// ---------------------------------------------------------------------------
// CUrlmonCallback::ParseMultiPartBuffer
// ---------------------------------------------------------------------------
HRESULT CUrlmonCallback::ParseMultiPartBuffer (BOOL fLastCall)
{
    HRESULT hrRead;
    DWORD cbActual;

    do // until hrRead != S_OK
    {
        // Read data and append to buffer.
        hrRead = m_pstm->Read(m_pbDataEnd, BufSpace(), &cbActual);
        m_pbDataEnd += cbActual;

        // Dispatch to current state handler.
        if (m_dwRangeBeg != m_dwRangeEnd)
            goto process_data;
        else
            goto parse_header;
            
parse_header:

        // If download not at EOF, don't try to parse multi-part
        // boundary if any chance it would be split across buffers.
        if (hrRead != S_FALSE && m_pbDataBeg > m_pbDataEnd - BOUNDARY_MAXSIZE)
        {
            BufShift();
            continue;
        }

        // Attempt to parse the multi-part boundary.
        if (!ParseMultiPartHeader())
            break;
               
        // Check if we got termination boundary.
        if (m_dwRangeBeg == m_dwRangeEnd)
            break;

        goto process_data;

process_data:

        // Calculate amount of data to report.
        DWORD cbData   = m_pbDataEnd  - m_pbDataBeg;
        DWORD cbRange  = m_dwRangeEnd - m_dwRangeBeg;
        DWORD cbLength = min (cbData, cbRange);

        if (cbLength)
        {
            // Call back the client with more data.
            m_CBParam.dwDataOffset = m_dwRangeBeg;
            m_CBParam.lpDataBuffer = m_pbDataBeg;
            m_CBParam.cbDataLength = cbLength;
            if (!(*(m_pParam->pfnRequestCB)) (&m_CBParam))
            {
                 // Client wants to stop.
                 m_pBinding->Abort();
                 break;
            }
            m_dwRangeBeg += cbLength;
        }

        // Adjust the buffer depending on next state.
        if (m_dwRangeBeg == m_dwRangeEnd) // (cbLength == cbRange)
        {
            // Consume the data and look for next header.
            m_pbDataBeg += cbLength;
            goto parse_header;
        }
        else
        {
            // Reset buffer and get some more data.
            BufReset();
            continue;
        }

    } while (hrRead == S_OK);

    return (hrRead == S_FALSE || hrRead == E_PENDING)? S_OK : hrRead;
}

