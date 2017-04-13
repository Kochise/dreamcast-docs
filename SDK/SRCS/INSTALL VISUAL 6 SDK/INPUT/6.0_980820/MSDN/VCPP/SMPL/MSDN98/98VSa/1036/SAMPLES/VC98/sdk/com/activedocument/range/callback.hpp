// ===========================================================================
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright 1996 Microsoft Corporation.  All Rights Reserved.
// ===========================================================================
#include <urlmon.h>
#include "recvbuf.hpp"
#include "range.h"

class CUrlmonCallback :
    public IBindStatusCallback,
    public IHttpNegotiate,
    public RecvBuf
{
public:

    // IUnknown methods
    STDMETHODIMP    QueryInterface(REFIID riid,void ** ppv);
    STDMETHODIMP_(ULONG) AddRef(void);
    STDMETHODIMP_(ULONG) Release(void);

	// IHttpNegotiate methods
	STDMETHODIMP BeginningTransaction (LPCWSTR szURL, LPCWSTR szHeaders,
        DWORD dwReserved, LPWSTR __RPC_FAR *pszAdditionalHeaders);
	STDMETHODIMP OnResponse (DWORD dwResponseCode, LPCWSTR szResponseHeaders, 
        LPCWSTR szRequestHeaders, LPWSTR *pszAdditionalRequestHeaders);

    // IBindStatusCallback methods
    STDMETHODIMP    OnStartBinding(DWORD grfBSCOption, IBinding* pBinding);
    STDMETHODIMP    GetPriority(LONG* pnPriority);
    STDMETHODIMP    OnLowResource(DWORD dwReserved);
    STDMETHODIMP    OnProgress(ULONG ulProgress, ULONG ulProgressMax,
        ULONG ulStatusCode, LPCWSTR pwzStatusText);
    STDMETHODIMP    OnStopBinding(HRESULT hrResult, LPCWSTR szError);
    STDMETHODIMP    GetBindInfo(DWORD* pgrfBINDF, BINDINFO* pbindinfo);
    STDMETHODIMP    OnDataAvailable(DWORD grfBSCF, DWORD dwSize,
        FORMATETC *pfmtetc, STGMEDIUM* pstgmed);
    STDMETHODIMP    OnObjectAvailable(REFIID riid, IUnknown* punk);

    // constructors/destructors
    CUrlmonCallback (PHTTP_REQUEST_PARAM);
    ~CUrlmonCallback();

    // read range processing functions
    BOOL ParseMultiPartHeader (void);
    HRESULT ParseMultiPartBuffer (BOOL fLastCall);
    
    // data members
    DWORD           m_cRef;
    IBinding*       m_pBinding;
    IStream*        m_pstm;
    DWORD           m_dwOffset;
    
    PHTTP_REQUEST_PARAM  m_pParam;  // initialization parameters
    HTTP_REQUESTCB_PARAM m_CBParam;

    DWORD  m_dwResponseCode;

    // range variables
    PSTR   m_pszRangeDelimiter;
    DWORD  m_cchRangeDelimiter;
    DWORD  m_dwRangeBeg;
    DWORD  m_dwRangeEnd;
};

