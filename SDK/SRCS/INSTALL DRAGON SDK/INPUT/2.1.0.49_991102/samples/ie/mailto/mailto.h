/********************************************************************
 * Copyright (c) 2000 Microsoft Corporation
 *
 * MailTo.h
 *
 * Description
 *   Definition for the CMailToProtocol class.
 ********************************************************************/

#ifndef __MAILTO_H      // Prevent multiple inclusions
#define __MAILTO_H	

// Includes 
#include <urlmon.h>     // IInternetProtocol, et al
#include <wininet.h>    // INTERNET_MAX_URL_LENGTH

class CMailToProtocol : public IClassFactory,      // Class Factory interface (class 
                                                   // factory and main object are the same)
                        public IInternetProtocol   // Internet Protocol interface

{
    public:
        // Constructor/Destructor
                             CMailToProtocol(void);
        virtual             ~CMailToProtocol(void);

        // IUnknown
        STDMETHODIMP         QueryInterface(REFIID riid, LPVOID *ppvObj);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        // IClassFactory
        STDMETHODIMP         CreateInstance(IUnknown *pUnkOuter, REFIID riid, LPVOID *ppvObj);
        STDMETHODIMP         LockServer(BOOL bLock);

        // IInternetProtocolRoot
        STDMETHODIMP         Start(LPCWSTR pchURL, IInternetProtocolSink *pProtocolSink,
                                   IInternetBindInfo *pBindInfo, DWORD grfSTI, DWORD dwReserved);
        STDMETHODIMP         Continue(PROTOCOLDATA *pProtocolData);
        STDMETHODIMP         Abort(HRESULT hrReason, DWORD dwOptions);
        STDMETHODIMP         Terminate(DWORD dwOptions);
        STDMETHODIMP         Suspend(void);
        STDMETHODIMP         Resume(void);

        // IInternetProtocol
        STDMETHODIMP         LockRequest(DWORD dwOptions);
        STDMETHODIMP         UnlockRequest(void);
        STDMETHODIMP         Read(LPVOID pvData, ULONG cb, ULONG *pcbRead);
        STDMETHODIMP         Seek(LARGE_INTEGER dlibMove, DWORD dwOrigin, ULARGE_INTEGER *plibNewPos);

    private:
        // Helpers
        HRESULT              BuildURL(LPCTSTR pszURL, LPCTSTR pszRedir, LPCTSTR pszFrom, TCHAR szNew[INTERNET_MAX_URL_LENGTH]);

        // Member Data
        ULONG                _ulRefCount;       // Reference count for object
};

#endif // __MAILTO_H
