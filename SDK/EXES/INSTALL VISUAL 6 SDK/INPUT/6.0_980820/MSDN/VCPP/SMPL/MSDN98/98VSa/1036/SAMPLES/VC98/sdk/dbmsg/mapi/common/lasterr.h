/////////////////////////////////////////////////////////////////
//  LASTERR.H
//
// Copyright 1986-1996 Microsoft Corporation. All Rights Reserved.
//
//
// last err support object.
//

//There should be no global objects of this class
// because by the time the dectructor of a global CLastError
// is called, MAPIFreeBuffer does not work.

#ifndef __LASTERR_H__
#define __LASTERR_H__

class CLastError
{
public:
    CLastError(LPSTR);
    ~CLastError(void);

    // standard OLE or MAPI errors.
    HRESULT     HrSetLastError(HRESULT hr);

    // our internal extended error codes or a non-standard string for OLE or MAPI errors
    // scFORM is one of the errors defined by MAKE_FORM_X_SCODE macro family
    HRESULT     HrSetLastError(HRESULT hr, SCODE scFORM, ...);

    // errors returned from underlying objects.
    HRESULT     HrSetLastError(HRESULT hr, IUnknown* punk);

    // our implementation of GetLastError
    HRESULT     HrGetLastError(HRESULT hr, DWORD dwFlags,
                               LPMAPIERROR * lppMAPIError);
    
    //displays the last error info
    int         ShowError(HWND);


private:
    // we have three possible error types: our internal errors which
    //  we signify by MAPI_E_EXTENDED to the user, standard errors
    //  defined by MAPI and errors returned by objects we keep and utilize.

    enum {eNoError, eExtended, eMAPI, eObject} m_eLastErr;

    HRESULT     m_hrLast;

    HRESULT     m_hrGLE;  // what GetLastError on the object returned; mostly 0
    LPMAPIERROR m_pmapierr;
    LPSTR m_szComponent;
};


inline CLastError::CLastError(LPSTR szComponent)
{
    m_eLastErr = eNoError;
    m_hrLast = 0;
    m_hrGLE = 0;
    m_pmapierr = 0;

    m_szComponent = NULL;
    
    if(!MAPIAllocateBuffer(lstrlen(szComponent) +1,
                        (LPVOID *) &m_szComponent))
    {
        lstrcpy(m_szComponent, szComponent);
    }
    
}

inline CLastError::~CLastError()
{
    if (m_pmapierr != NULL)
    {
        MAPIFreeBuffer(m_pmapierr);
    }
    if(m_szComponent != NULL)
    {
        MAPIFreeBuffer(m_szComponent);
    }
}

#endif // __LASTERR_H__
