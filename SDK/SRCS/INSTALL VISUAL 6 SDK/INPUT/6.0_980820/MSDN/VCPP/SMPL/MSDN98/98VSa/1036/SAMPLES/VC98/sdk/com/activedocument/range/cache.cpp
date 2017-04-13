// ===========================================================================
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright 1996 Microsoft Corporation.  All Rights Reserved.
// ===========================================================================
#include <windows.h>
#include <wininet.h>
#include "range.h"

//==============================================================================
BOOL QueryHeaders
(
     HANDLE                hRequest,
     PHTTP_REQUESTCB_PARAM pCBParam,
     SYSTEMTIME*           pstLastModified
)
{
    DWORD cbBuf;
    BOOL fRet;

    pCBParam->CallbackType     = REQUESTCB_STARTED;
    pCBParam->fdwRequestFlags  = HTTP_REQUEST_FROM_CACHE;
        
    // Get if the server supports ranges from the response headers.
    static char szBytes[] ="bytes";
    char szBuf[sizeof(szBytes)];
    cbBuf = sizeof(szBytes);
    fRet = HttpQueryInfo
        (hRequest, HTTP_QUERY_ACCEPT_RANGES, szBuf, &cbBuf, 0);
    if (fRet && !lstrcmpi (szBuf, szBytes))
        pCBParam->fdwRequestFlags |= HTTP_REQUEST_ACCEPT_RANGES;

    // Get the response code.
    cbBuf = sizeof(pCBParam->dwResponseCode);
    fRet = HttpQueryInfo
    (
        hRequest,
        HTTP_QUERY_FLAG_NUMBER | HTTP_QUERY_STATUS_CODE,
        &pCBParam->dwResponseCode,
        &cbBuf,
        NULL
    );
    if (!fRet)
       pCBParam->dwResponseCode = 0;
  
    // Get the last modified time from the response headers.
    cbBuf = sizeof(*pstLastModified);
    fRet = HttpQueryInfo
    (
        hRequest,
        HTTP_QUERY_FLAG_SYSTEMTIME | HTTP_QUERY_LAST_MODIFIED,
        pstLastModified,
        &cbBuf, 
        NULL
    );
    pCBParam->pstLastModified = fRet? pstLastModified : NULL;

    // Get the content length from the cache file size.
    pCBParam->dwContentLength =
        InternetSetFilePointer (hRequest, NULL, 0, FILE_END, 0);

    return TRUE;
}

//==============================================================================
BOOL HttpReadFromCache (PHTTP_REQUEST_PARAM pParam)
{
    // Locals that must be initialized before goto done.
    BOOL fSuccess = FALSE;
    HANDLE hInternet = NULL;
    HANDLE hConnect  = NULL;
    HANDLE hRequest  = NULL;
    PVOID pRead = NULL;
    HRESULT hrRequest = S_OK;
    
    // Initialize wininet
    hInternet = InternetOpen
        ("RR", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, INTERNET_FLAG_OFFLINE);
    if (!hInternet)
        goto done;
    hRequest = InternetOpenUrl
        (hInternet, pParam->pszUrl, NULL, 0, INTERNET_FLAG_OFFLINE, 0);
    if (!hRequest)
        goto done;

    // Initialize callback parameters.
    HTTP_REQUESTCB_PARAM CBParam;
    CBParam.cbStruct         = sizeof(CBParam);
    CBParam.dwRequestCtx     = pParam->dwRequestCtx;

    // Allocate read buffer
    DWORD cbRead;
    cbRead = 4096;
    pRead  = LocalAlloc (LMEM_FIXED, cbRead);
    if (!pRead)
    {
        SetLastError (ERROR_NOT_ENOUGH_MEMORY);
        goto done;
    }

    SYSTEMTIME st;
    if (!QueryHeaders (hRequest, &CBParam, &st))
        goto done;

    fSuccess = TRUE;
    
    // Notify the client that request is started.
    if (!(*pParam->pfnRequestCB) (&CBParam))
        goto notify;

    // Set up ranges to read.    
    HTTP_REQUEST_RANGE EntireRange;
    PHTTP_REQUEST_RANGE pRanges;
    DWORD cRanges;

    if (pParam->cRanges)
    {
        pRanges = pParam->pRanges;
        cRanges = pParam->cRanges;
    }
    else
    {
        EntireRange.dwOffset = 0;
        EntireRange.dwSize = CBParam.dwContentLength;   
        pRanges = &EntireRange;
        cRanges = 1;
    }

    // Loop over the ranges, reading into the buffer.
    CBParam.CallbackType = REQUESTCB_DATA;
    CBParam.lpDataBuffer = pRead;

    while (cRanges--)
    {
        CBParam.dwDataOffset = pRanges->dwOffset;
        DWORD cbRange        = pRanges->dwSize;
        if (!cbRange)
            cbRange = InternetSetFilePointer (hRequest, 0, NULL, FILE_END, 0)
              - pRanges->dwOffset;
              
        while (cbRange) // Loop until we have all the data for the range.
        {
            InternetSetFilePointer
                (hRequest, CBParam.dwDataOffset, NULL, FILE_BEGIN, 0);
            
            if (!InternetReadFile
                (hRequest, pRead, min(cbRead, cbRange), &CBParam.cbDataLength))
            {
                hrRequest = E_FAIL;
                goto notify;
            }

            // Check for EOF
            if (!CBParam.cbDataLength)
                break;

            // Call the client with data.
            if (!(*pParam->pfnRequestCB) (&CBParam))
                goto notify;

            CBParam.dwDataOffset += CBParam.cbDataLength;
            cbRange              -= CBParam.cbDataLength;
        }

        // Advance to next range.
        pRanges++;
        
    } // end while (cRanges--)

notify:

    // Notify the client we are done.
    CBParam.CallbackType = REQUESTCB_DONE;
    CBParam.hrRequest = hrRequest;
    (*pParam->pfnRequestCB) (&CBParam);
    
done:
    if (pRead)
        LocalFree ((HLOCAL) pRead);
    if (hRequest)
        InternetCloseHandle (hRequest);
    if (hConnect)
        InternetCloseHandle (hConnect);
    if (hInternet)
        InternetCloseHandle (hInternet);
    return fSuccess;
}

//==============================================================================
BOOL HttpReadRequest (PHTTP_REQUEST_PARAM pParam)
{
    if (pParam->cbStruct != sizeof(HTTP_REQUEST_PARAM))
    {
        SetLastError (ERROR_INVALID_PARAMETER);
        return FALSE;
    }

    if (HttpReadFromCache (pParam))
        return TRUE;
    return HttpReadFromServer (pParam);
}


