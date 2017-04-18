/********************************************************************
 * Copyright (c) 2000 Microsoft Corporation
 *
 * MailTo.cpp
 *
 * Description
 *   Implementation for the CMailToProtocol class. Also the 
 *   implementation for DllGetClassObject and DllCanUnloadNow.
 ********************************************************************/

// Includes
#include <windows.h>    // Standard Windows API
#include <initguid.h>   // DEFINE_GUID

#include "mailto.h"     // Definition of CMailToProtocol

// CLSID for CMailToProtocol {40B4BA40-C477-11d3-B16F-0008C76BE5B9}
DEFINE_GUID(CLSID_MailToProtocol, 
            0x40b4ba40, 0xc477, 0x11d3, 0xb1, 0x6f, 0x0, 0x8, 0xc7, 0x6b, 0xe5, 0xb9);

// Global data
DWORD     g_ulLocks = 0;        // Number of objects/locks on DLL
HINSTANCE g_hInst   = NULL;     // HINSTANCE for DLL

/********************************************************************
 * CMailToProtocol::CMailToProtocol
 *
 * Description
 *   Only constructor for the CMailToProtocol class. It starts with a 
 *   zero reference count, and increments the number of objects in the 
 *   DLL.
 ********************************************************************/
CMailToProtocol::CMailToProtocol(void)
{ 
    g_ulLocks++;             // Increment object/lock count for DLL
    _ulRefCount     = 0;     // Initialize ref count to 0. Caller MUST AddRef.
}

/********************************************************************
 * CMailToProtocol::~CMailToProtocol
 *
 * Description
 *   Destructor for the CMailToProtocol class. It decrements the 
 *   number of objects in the DLL.
 ********************************************************************/
CMailToProtocol::~CMailToProtocol(void)
{ 
    g_ulLocks--;            // Decrement object/lock count for DLL
}

/********************************************************************
 * IUnknown
 ********************************************************************/

/********************************************************************
 * CMailToProtocol::IUnknown::QueryInterface
 *
 * Description
 *    Return requested interface pointer.
 *
 * Parameters
 *    riid    in  Interface ID.
 *    ppvObj  out Pointer to requested interface pointer.
 *
 * Result
 *    S_OK           Success.
 *    E_POINTER      If ppvObj not supplied.
 *    E_NOINTERFACE  If IID is not known. 
 ********************************************************************/
STDMETHODIMP CMailToProtocol::QueryInterface(REFIID riid, LPVOID *ppvObj)
{
    // Validate return parameter.
    if (!ppvObj)
    {
        return E_POINTER;
    }

    // Initialize return pointer to NULL;
    *ppvObj = NULL;

    // Check for known and handled interface ID.
    if (riid == IID_IUnknown)
    {
        *ppvObj = (IUnknown *)(IClassFactory *)this;
    }
    else if (riid == IID_IClassFactory)
    {
        *ppvObj = (IClassFactory *)this;
    }
    else if (riid == IID_IInternetProtocolRoot)
    {
        *ppvObj = (IInternetProtocolRoot *)this;
    }
    else if (riid == IID_IInternetProtocol)
    {
        *ppvObj = (IInternetProtocol *)this;
    }
    else
    {
        // IID unknown, return error.
        return E_NOINTERFACE;
    }

    // Found interface, Add Ref it and return success
    ((IUnknown *)(*ppvObj))->AddRef();

    return S_OK;
}

/********************************************************************
 * CMailToProtocol::IUnknown::AddRef
 *
 * Description
 *    Increments refrerence count.
 *
 * Parameters
 *    None.
 *
 * Result
 *    Number of reference counts on object.
 ********************************************************************/
STDMETHODIMP_(ULONG) CMailToProtocol::AddRef(void)
{
    _ulRefCount++;

    return _ulRefCount;
}

/********************************************************************
 * CMailToProtocol::IUnknown::Release
 *
 * Description
 *    Decrements reference count, and deletes object when count = 0.
 *
 * Parameters
 *    None.
 *
 * Result
 *    Number of reference counts on object.
 ********************************************************************/
STDMETHODIMP_(ULONG) CMailToProtocol::Release(void)
{
    _ulRefCount--;

    if (_ulRefCount)
    {
        return _ulRefCount;
    }

    delete this;

    return 0;
}

/********************************************************************
 * IClassFactory implementation of CMailToProtocol
 ********************************************************************/

/********************************************************************
 * CMailToProtocol::IClassFactory::CreateInstance
 *
 * Description
 *    The protocol object and the class factory are the same object,
 *    so CreateInstance simply gets the requested interface from itself.
 *
 * Parameters
 *    pUnkOuter  in  Not used.
 *    riid       in  Interface ID.
 *    ppvObj     out Pointer to requested interface pointer.
 *
 * Result
 *    S_OK                   Success.
 *    CLASS_E_NOAGGREGATION  If pUnkOuter is non null.
 *    other                  Result of QueryInterface
 ********************************************************************/
STDMETHODIMP CMailToProtocol::CreateInstance(IUnknown *pUnkOuter, 
                                             REFIID riid, LPVOID *ppvObj)
{
    if (pUnkOuter)
    {
        return CLASS_E_NOAGGREGATION;
    }

    return QueryInterface(riid, ppvObj);
}

/********************************************************************
 * CMailToProtocol::IClassFactory::LockServer
 *
 * Description
 *    Locks or unlocks the DLL.
 *
 * Parameters
 *    bLock  in  TRUE   Lock the DLL from being unloaded.
 *               FALSE  Unlock the DLL.
 *
 * Result
 *    S_OK
 ********************************************************************/
STDMETHODIMP CMailToProtocol::LockServer(BOOL bLock)
{
    if (bLock)
    {
        g_ulLocks++;
    }
    else
    {
        g_ulLocks--;
    }

    return S_OK;
}

/********************************************************************
 * IInternetProtocolRoot implementation of CMailToProtocol
 ********************************************************************/

/********************************************************************
 * CMailToProtocol::IInternetProtocolRoot::Start
 *
 * Description
 *    Parse the mailto URL and redirect it to the page specified in
 *    the registry.
 *
 * Parameters
 *    pszURL        in  URL to retrieve.
 *    pProtocolSink in  Object to receive notifications.
 *    pBindInfo     in  Bind data.
 *    grfSTI        in  Parse flags.
 *    dwReserved    in  Ignored.
 *
 * Result
 *    S_OK           Success and non-async.
 *    E_INVALIDARG   If pProtocolSink is null.
 *    E_FAIL         If parsing error.
 *    other          Result from called functions.
 ********************************************************************/
HRESULT CMailToProtocol::Start(LPCWSTR pszURL, IInternetProtocolSink *pProtocolSink,
                            IInternetBindInfo *pBindInfo, DWORD grfSTI, DWORD dwReserved)
{
    // Validate arguments.
    if (!pProtocolSink)
    {
        return E_INVALIDARG;
    }

    // Encode URL.
    TCHAR szEncodedURL[INTERNET_MAX_URL_LENGTH];
    DWORD dwSize;

    HRESULT hr = CoInternetParseUrl(pszURL, PARSE_ENCODE, 0, szEncodedURL, 
                                    INTERNET_MAX_URL_LENGTH, &dwSize, 0);
    if (FAILED(hr))
    {
        return hr;
    }

    // Load redirect site from registry.
    TCHAR szRedirSite[MAX_PATH];
    TCHAR szFrom[MAX_PATH];
    *szRedirSite = 0;
    *szFrom = 0;

    HKEY hkey;
    if (ERROR_SUCCESS == RegOpenKeyEx(HKEY_CURRENT_USER, TEXT("Software\\Microsoft\\Internet Explorer\\Dreamcast Mailto"), 0, NULL, &hkey)) 
    {
        DWORD dwType;
        DWORD dwSize = sizeof(szRedirSite);
        RegQueryValueEx(hkey, TEXT("Redirect Site"), NULL, &dwType, (LPBYTE)szRedirSite, &dwSize);
        dwSize = sizeof(szFrom);
        RegQueryValueEx(hkey, TEXT("Mail From"), NULL, &dwType, (LPBYTE)szFrom, &dwSize);
        RegCloseKey(hkey);
    }

    if (!*szRedirSite)
    {
        OutputDebugString(TEXT("Error: Need to set mailto redirect site in registry.\n"));
        return E_FAIL;
    }

    TCHAR szRedirURL[INTERNET_MAX_URL_LENGTH];
    hr = BuildURL(szEncodedURL, szRedirSite, szFrom, szRedirURL);
    if (FAILED(hr))
    {
        return hr;
    }

    hr = pProtocolSink->ReportResult(INET_E_REDIRECTING, 0, szRedirURL);

    return hr;
}

/********************************************************************
 * CMailToProtocol::IInternetProtocolRoot::Continue
 *
 * Description
 *    Nothing really to continue since everything was handled only in 
 *    the Start function.
 *
 * Parameters
 *    pProtocolData  in  Current protocol state.
 *
 * Result
 *    S_OK          Success.
 ********************************************************************/
STDMETHODIMP CMailToProtocol::Continue(PROTOCOLDATA *pProtocolData)
{ 
    return S_OK;
}

/********************************************************************
 * CMailToProtocol::IInternetProtocolRoot::Abort
 *
 * Description
 *    Nothing really to stop since everything was handled only in 
 *    the Start function.
 *
 * Parameters
 *    hrReason   in  Reason for abort.
 *    dwOptions  in  Abort options.
 *
 * Result
 *    S_OK
 ********************************************************************/
STDMETHODIMP CMailToProtocol::Abort(HRESULT hrReason, DWORD dwOptions)
{
    return S_OK;
}

/********************************************************************
 * CMailToProtocol::IInternetProtocolRoot::Terminate
 *
 * Description
 *    Nothing really to stop since everything was handled only in 
 *    the Start function.
 *
 * Parameters
 *    dwOptions  in  Terminate options.
 *
 * Result
 *    S_OK
 ********************************************************************/
STDMETHODIMP CMailToProtocol::Terminate(DWORD dwOptions)
{ 
    return S_OK; 
}

/********************************************************************
 * CMailToProtocol::IInternetProtocolRoot::Suspend
 *
 * Description
 *    Not used by SDK.
 *
 * Parameters
 *    None.
 *
 * Result
 *    E_NOTIMPL
 ********************************************************************/
STDMETHODIMP CMailToProtocol::Suspend(void)
{ 
    return E_NOTIMPL; 
}

/********************************************************************
 * CMailToProtocol::IInternetProtocolRoot::Resume
 *
 * Description
 *    Not used by SDK.
 *
 * Parameters
 *    None.
 *
 * Result
 *    E_NOTIMPL
 ********************************************************************/
STDMETHODIMP CMailToProtocol::Resume(void)
{ 
    return E_NOTIMPL; 
}

/********************************************************************
 * IInternetProtocol implementation of CMailToProtocol
 ********************************************************************/

/********************************************************************
 * CMailToProtocol::IInternetProtocol::LockRequest
 *
 * Description
 *    Nothing really to lock since everything was handled only in 
 *    the Start function.
 *
 * Parameters
 *    dwOptions  in  Lock options.
 *
 * Result
 *    S_OK
 ********************************************************************/
STDMETHODIMP CMailToProtocol::LockRequest(DWORD dwOptions)    
{ 
    return S_OK; 
}

/********************************************************************
 * CMailToProtocol::IInternetProtocol::UnlockRequest
 *
 * Description
 *    Nothing really to unlock since everything was handled only in 
 *    the Start function.
 *
 * Parameters
 *    None.
 *
 * Result
 *    S_OK
 ********************************************************************/
STDMETHODIMP CMailToProtocol::UnlockRequest(void)    
{ 
    return S_OK; 
}

/********************************************************************
 * CMailToProtocol::IInternetProtocol::Read
 *
 * Description
 *    Nothing really to read since this is just a redirect.
 *
 * Parameters
 *    pvData   out Pointer to buffer in which to return data.
 *    cb       in  Size of pvData buffer in bytes.
 *    pchRead  out Pointer to number of bytes actually read.
 *
 * Result
 *    E_NOTIMPL	  not implemented
 ********************************************************************/
STDMETHODIMP CMailToProtocol::Read(LPVOID pvData, ULONG cb, ULONG *pcbRead)
{ 
    return E_NOTIMPL;
}

/********************************************************************
 * CMailToProtocol::IInternetProtocol::Seek
 *
 * Description
 *    Nothing really to seek since this is just a redirect.
 *
 * Parameters
 *    dlibMove    in  Amount to offset.
 *    dwOrigin    in  Where to start offset (beginning, current pos, end).
 *    plibNewPos  out New position of file after seek.
 *
 * Result
 *    E_NOTIMPL	  not implemented
 ********************************************************************/
STDMETHODIMP CMailToProtocol::Seek(LARGE_INTEGER dlibMove, DWORD dwOrigin,
                                ULARGE_INTEGER *plibNewPos) 
{ 
    return E_NOTIMPL;
}

/********************************************************************
 * Helper function implementation of CMailToProtocol
 ********************************************************************/

/********************************************************************
 * CMailToProtocol::BuildURL
 *
 * Description
 *    Convert the given URL to the redirect URL with the parameter list. 
 *
 * Parameters
 *    pszURL      in  URL to parse and use for parameters.
 *    pszRedir    in  URL of server to redirect.
 *    pszFrom     in  Name of user sending mail.
 *    szNew       out Full redirect URL with parameters.
 *
 * Result
 *    S_OK    Success.
 *    E_FAIL  If malformed URL.
 ********************************************************************/
HRESULT CMailToProtocol::BuildURL(LPCTSTR pszURL, LPCTSTR pszRedir, LPCTSTR pszFrom,
                                  TCHAR szNew[INTERNET_MAX_URL_LENGTH])
{
    // Validate arguments.
    if (!szNew)
    {
        return E_INVALIDARG;
    }

    // Set up the default.
    *szNew = 0;

    if (!pszURL || !pszRedir || !pszFrom)
    {
        return E_INVALIDARG;
    }

    UINT nRedirLen = _tcslen(pszRedir);
    if (nRedirLen >= INTERNET_MAX_URL_LENGTH)
    {
        return E_INVALIDARG;
    }

    _tcscpy(szNew, pszRedir);
    UINT nURLLen = nRedirLen;

    // Check for not enough room for any parameters.
    if (nURLLen >= (INTERNET_MAX_URL_LENGTH - 1))
    {
        return S_OK;
    }

    // Skip over the protocol. Do not check it against MailTo: since it really 
    // can be anything as long as the registry is set up correctly.
    while (*pszURL && (*pszURL != TEXT(':')))
    {
        pszURL++;
    }

    // Nothing left to parse (no recipient or subject). 
    if (!*pszURL)
    {
        return S_OK;
    }

    // Skip over the :
    pszURL++;

    // Nothing left to parse (no recipient or subject). 
    if (!*pszURL)
    {
        return S_OK;
    }

    // Add parameter delimiter.
    _tcscpy(szNew + nURLLen, TEXT("?"));
    nURLLen++;

    // Check for not enough room for "to=" parameter label.
    if (nURLLen >= (INTERNET_MAX_URL_LENGTH - 3))
    {
        return S_OK;
    }

    _tcscpy(szNew + nURLLen, TEXT("to="));
    nURLLen += 3;

    // Find end of recipient data.
    LPCTSTR pszTo = pszURL;
    while (*pszURL && (*pszURL != TEXT('?')))
    {
        pszURL++;
    }
    
    UINT nToLen = (int)(pszURL - pszTo);

    // Check for not enough room for "to=" parameter data.
    if (nURLLen >= (INTERNET_MAX_URL_LENGTH - nToLen))
    {
        return S_OK;
    }

    _tcsncpy(szNew + nURLLen, pszTo, nToLen);
    nURLLen += nToLen;

    if (*pszFrom)
    {
        // Check for not enough room for "from=" parameter label.
        if (nURLLen < (INTERNET_MAX_URL_LENGTH - 6))
        {
            _tcscpy(szNew + nURLLen, TEXT("&from="));
            nURLLen += 6;
            UINT nFromLen = _tcslen(pszFrom);

            // Check for not enough room for "from=" parameter data.
            if (nURLLen < (INTERNET_MAX_URL_LENGTH - nFromLen))
            {
                _tcsncpy(szNew + nURLLen, pszFrom, nFromLen);
                nURLLen += nFromLen;
            }
        }
    }

    // Check for additional data (subject).
    if (*pszURL == TEXT('?'))
    {
        pszURL++;
    }

    if (*pszURL)
    {
        // Check for not enough room for "&" parameter delimiter.
        if (nURLLen >= (INTERNET_MAX_URL_LENGTH - 1))
        {
            return S_OK;
        }

        _tcscpy(szNew + nURLLen, TEXT("&"));
        nURLLen++;

        // Concatenate the rest of the data (subject).
        _tcsncpy(szNew + nURLLen, pszURL, INTERNET_MAX_URL_LENGTH - nURLLen);
    }

    OutputDebugString(TEXT("Redirected URL = "));
    OutputDebugString(szNew);
    OutputDebugString(TEXT("\n"));

    return S_OK;
}

/********************************************************************
 * Exported functions
 ********************************************************************/

/********************************************************************
 * DllGetClassObject
 *
 * Description
 *    Create requested object and return requested interface. Object
 *    should have a reference count of 1 when returned to caller.
 *
 * Parameters
 *    rclsid  in  Class ID of object to create.
 *    riid    in  Interface ID of object to create.
 *    ppvObj  out Pointer to requested interface pointer.
 *
 * Result
 *    S_OK           Success.
 *    E_POINTER      If ppvObj not supplied.
 *    E_NOINTERFACE  If IID is not known. 
 *    E_FAIL         If CLSID is not known.
 ********************************************************************/
STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID *ppvObj)
{
    // Validate return parameter.
    if (!ppvObj)
    {
        return E_POINTER;
    }

    // Initialize return pointer to NULL;
    *ppvObj = NULL;

    // Check for known and handled interface ID.
    if ((IID_IUnknown != riid) && (IID_IClassFactory != riid))
    {
        return E_NOINTERFACE;
    }

    // Check for known and handled class ID.
    if (CLSID_MailToProtocol == rclsid)
    {
        // Create new protocol handler object with initial ref count = 0.
        CMailToProtocol *pMailToProtocol = new CMailToProtocol;

        // Get requested interface (will make ref count = 1)
        if (FAILED(pMailToProtocol->QueryInterface(riid, ppvObj)))
        {
            // If could not get requested interface, delete object.
            // Do not use release since ref count = 0.
            delete pMailToProtocol;
        }
        else
        {
            // Got requested interface.
            return S_OK;
        }
    }

    // No interface or no class ID.
    return E_FAIL;
}

/********************************************************************
 * DllCanUnloadNow
 *
 * Description
 *    Return if it is okay to unload the DLL (no objects still in use).
 *
 * Parameters
 *    None.
 *
 * Result
 *    S_OK     If no objects in DLL are still in use.
 *    S_FALSE  If any objects in DLL are still in use.
 ********************************************************************/
STDAPI DllCanUnloadNow(void)
{
    return (g_ulLocks) ? S_FALSE : S_OK;
}

/********************************************************************
 * DllMain
 *
 * Description
 *    Handle initialization and shutdown of DLL.
 *
 * Parameters
 *    None.
 *
 * Result
 *    TRUE   All ok
 ********************************************************************/
BOOL WINAPI DllMain(HANDLE hinst, DWORD dwReason, LPVOID lpvReserved)
{
    // Keep track of DLL instance handle while DLL is active.

    if (dwReason == DLL_PROCESS_ATTACH)
    {
        g_hInst = (HINSTANCE)hinst;
    }
    else if (dwReason == DLL_PROCESS_DETACH)
    {
        g_hInst = NULL;
    }

    // Nothing went wrong.
    return TRUE;
}



