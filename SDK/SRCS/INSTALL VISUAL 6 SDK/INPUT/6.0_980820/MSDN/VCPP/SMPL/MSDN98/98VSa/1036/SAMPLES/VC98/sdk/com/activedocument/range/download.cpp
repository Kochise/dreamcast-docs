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
// #include <datapath.h>
#include "range.h"
#include "callback.hpp"

//==============================================================================
HRESULT GetAnInterface
(
    IUnknown  *     punk,
    const IID &     riid,
    void **         pout,
    BOOL            bCheckServiceProvider,
    const IID &     siid,
    const IID &     siid_riid,
    void **         sout
)
{
    IOleObject *      oleObj    = 0;
    IOleClientSite *  oleSite   = 0;
    IOleContainer *   container = 0;
    IUnknown *        service   = 0;

    HRESULT       hr = E_FAIL;

    // Initialize passed in interface pointers: calling code assumes NULL for failure
    if(pout)
        *pout = NULL;
    if(sout)
        *sout = NULL;

    if(punk)
        hr = punk->QueryInterface( IID_IOleObject, (void **)&oleObj );

    while( SUCCEEDED(hr) && oleObj )
    {
        if( oleSite )
        {
            //oleSite->Release();
            oleSite = 0;
        }

        hr = oleObj->GetClientSite(&oleSite);

        if( FAILED(hr) )
            break;

        if( bCheckServiceProvider )
        {
            IServiceProvider * servProv;

            hr = oleSite->QueryInterface( IID_IServiceProvider, (void**)&servProv);

            if( SUCCEEDED(hr) )
            {
                hr = servProv->QueryService
                    (siid, siid_riid, (void **) &service);
                servProv->Release();
            }

            if( SUCCEEDED(hr) )
            {
                bCheckServiceProvider = FALSE;

                hr = service->QueryInterface( riid, pout );
            }

            if( SUCCEEDED(hr) )
                break;

        }

        if( container )
        {
            container->Release();
            container = 0;
        }

        hr = oleSite->GetContainer( &container );

        if( FAILED(hr) )
            break;

        hr = container->QueryInterface( riid, pout );

        if( SUCCEEDED(hr) )
            break;

        oleObj->Release();
        oleObj = 0;

        hr = container->QueryInterface( IID_IOleObject, (void**)&oleObj );

    }

    if( oleSite )
    {
        //oleSite->Release();
    }

    if( oleObj )
        oleObj->Release();

    if( container )
        container->Release();

    if( service )
        *sout = service;

    return( hr );

}

//==============================================================================
BOOL HttpReadFromServer (PHTTP_REQUEST_PARAM pParam)
{
    IMoniker*            m_pmk   = NULL;
    IBindStatusCallback* m_pbsc  = NULL;
    HRESULT hr = S_OK;
    
    IBindHost *pBindHost = NULL;

    // Create a callback object.
    m_pbsc = new CUrlmonCallback (pParam);
    if (m_pbsc == NULL)
    {
        hr = E_OUTOFMEMORY;
        goto err;
    }

    // Look for a bind host.
    if (pParam->punkOuter)
    {
        hr = GetAnInterface
        (
            (IUnknown *) pParam->punkOuter,
            IID_IBindHost,           // const IID &  riid,
            (void **) &pBindHost,    // void **      pout,  
            TRUE,                    // BOOL         bCheckServiceProvider,
            IID_IBindHost,           // const IID &  siid,
            IID_IBindHost,           // const IID &  siid_riid,
            (void **) &pBindHost     // void **      sout
        );
    }

    // Convert ANSI URL to Unicode.
    WCHAR wszUrl[INTERNET_MAX_URL_LENGTH];
    MultiByteToWideChar(CP_ACP, 0, pParam->pszUrl, -1, wszUrl, sizeof(wszUrl));

    // Initialize bind context, stream.
    IBindCtx *pbc;
    IStream *pstm;
    pbc =  NULL;
    pstm = NULL;

    // Call the appropriate BindToStorage.
    if (pBindHost)
    {
         pBindHost->CreateMoniker (wszUrl, NULL, &m_pmk, 0);
         pBindHost->MonikerBindToStorage
             (m_pmk, NULL, m_pbsc, IID_IStream, (void **) &pstm);
    }   
    else
    {
        CreateURLMoniker(NULL, wszUrl, &m_pmk);
        CreateAsyncBindCtx(0, m_pbsc, NULL, &pbc);
        m_pmk->BindToStorage(pbc, NULL, IID_IStream, (void **) &pstm);
    }

    // Clean up bind context, stream.
    if (pbc)
        pbc->Release();
    if (pstm)
        pstm->Release();

    return SUCCEEDED(hr);

err:
    delete m_pbsc;

    if (m_pmk != NULL)
    {
        m_pmk->Release();
        m_pmk = NULL;
    }
    return FALSE;

}

