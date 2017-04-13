/*
 * ICLASSF.CPP
 * Patron Chapter 21
 *
 * Implementation of an IClassFactory interface for Patron to
 * enable linking to its embedded objects.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#include "patron.h"


/*
 * CLinkClassFactory::CLinkClassFactory
 * CLinkClassFactory::~CLinkClassFactory
 *
 * Constructor Parameters:
 *  pFR             PCLinkFrame that can create documents.
 */

CLinkClassFactory::CLinkClassFactory(PCPatronFrame pFR)
    {
    m_cRef=0L;
    m_pFR=pFR;
    return;
    }


CLinkClassFactory::~CLinkClassFactory(void)
    {
    return;
    }






/*
 * CLinkClassFactory::QueryInterface
 * CLinkClassFactory::AddRef
 * CLinkClassFactory::Release
 */

STDMETHODIMP CLinkClassFactory::QueryInterface(REFIID riid
    , PPVOID ppv)
    {
    *ppv=NULL;

    if (IID_IUnknown==riid || IID_IClassFactory==riid)
        *ppv=this;

    if (NULL!=*ppv)
        {
        ((LPUNKNOWN)*ppv)->AddRef();
        return NOERROR;
        }

    return ResultFromScode(E_NOINTERFACE);
    }


STDMETHODIMP_(ULONG) CLinkClassFactory::AddRef(void)
    {
    return ++m_cRef;
    }


STDMETHODIMP_(ULONG) CLinkClassFactory::Release(void)
    {
    if (0!=--m_cRef)
        return m_cRef;

    delete this;
    return 0;
    }







/*
 * CLinkClassFactory::CreateInstance
 *
 * Purpose:
 *  Instantiates an object to resolve a link to an embedding.
 */

STDMETHODIMP CLinkClassFactory::CreateInstance(LPUNKNOWN pUnkOuter
    , REFIID riid, PPVOID ppvObj)
    {
    PCPatronDoc         pDoc;
    HRESULT             hr;

    *ppvObj=NULL;

    hr=ResultFromScode(E_OUTOFMEMORY);

    //We don't support aggregation
    if (NULL!=pUnkOuter)
        return ResultFromScode(CLASS_E_NOAGGREGATION);

    //Try creating a new document, which creates the object.
    pDoc=(PCPatronDoc)m_pFR->m_pCL->NewDocument(TRUE);

    //ObjectDestroyed has already been called.
    if (NULL==pDoc)
        {
        g_cObj++;
        ObjectDestroyed();
        return hr;
        }

    /*
     * We don't want to do any file initialization here because we
     * want to wait for IPersistFile calls.  If we called Load(NULL)
     * we'd create storages and whatnot that we don't want in this
     * case.
     */

    hr=pDoc->QueryInterface(riid, ppvObj);

    if (FAILED(hr))
        {
        m_pFR->m_pCL->CloseDocument(pDoc);
        g_cObj++;
        ObjectDestroyed();
        return hr;
        }

    m_pFR->m_pDocCreated=pDoc;
    return NOERROR;
    }






/*
 * CLinkClassFactory::LockServer
 *
 * Purpose:
 *  Provides control of the application in memory.
 */

STDMETHODIMP CLinkClassFactory::LockServer(BOOL fLock)
    {
    if (fLock)
        g_cLock++;
    else
        {
        g_cLock--;
        g_cObj++;
        ObjectDestroyed();
        }

    return NOERROR;
    }
