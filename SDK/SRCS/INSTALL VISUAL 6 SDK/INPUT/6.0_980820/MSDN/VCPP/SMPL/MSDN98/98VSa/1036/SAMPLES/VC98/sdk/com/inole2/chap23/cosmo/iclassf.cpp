/*
 * ICLASSF.CPP
 * Cosmo Chapter 23
 *
 * Implementation of Cosmo's class factory.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#include "cosmo.h"


/*
 * CFigureClassFactory::CFigureClassFactory
 * CFigureClassFactory::~CFigureClassFactory
 *
 * Constructor Parameters:
 *  pFR             PCCosmoFrame that can create documents.
 */

CFigureClassFactory::CFigureClassFactory(PCCosmoFrame pFR)
    {
    m_cRef=0L;
    m_pFR=pFR;
    m_fCreated=FALSE;
    return;
    }


CFigureClassFactory::~CFigureClassFactory(void)
    {
    return;
    }






/*
 * CFigureClassFactory::QueryInterface
 * CFigureClassFactory::AddRef
 * CFigureClassFactory::Release
 */

STDMETHODIMP CFigureClassFactory::QueryInterface(REFIID riid
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


STDMETHODIMP_(ULONG) CFigureClassFactory::AddRef(void)
    {
    return ++m_cRef;
    }


STDMETHODIMP_(ULONG) CFigureClassFactory::Release(void)
    {
    if (0!=--m_cRef)
        return m_cRef;

    delete this;
    return 0;
    }







/*
 * CFigureClassFactory::CreateInstance
 *
 * Purpose:
 *  Instantiates a Figure object that supports embedding.
 *
 * Parameters:
 *  pUnkOuter       LPUNKNOWN to the controlling IUnknown if we are
 *                  being used in an aggregation.
 *  riid            REFIID identifying the interface the caller
 *                  desires to have for the new object.
 *  ppvObj          PPVOID in which to store the desired
 *                  interface pointer for the new object.
 *
 * Return Value:
 *  HRESULT         NOERROR if successful, otherwise contains
 *                  E_NOINTERFACE if we cannot support the requested
 *                  interface.
 */

STDMETHODIMP CFigureClassFactory::CreateInstance(LPUNKNOWN pUnkOuter
    , REFIID riid, PPVOID ppvObj)
    {
    PCCosmoDoc          pDoc;
    HRESULT             hr;

    *ppvObj=NULL;

    //Great idea to protect yourself from multiple creates here.
    if (m_fCreated)
        return ResultFromScode(E_UNEXPECTED);

    m_fCreated=TRUE;
    hr=ResultFromScode(E_OUTOFMEMORY);

    //We don't support aggregation
    if (NULL!=pUnkOuter)
        return ResultFromScode(CLASS_E_NOAGGREGATION);

    //Try creating a new document, which creates the object.
    pDoc=(PCCosmoDoc)m_pFR->m_pCL->NewDocument(TRUE);

    if (NULL==pDoc)
        {
        //This will cause shutdown; object count will go to zero.
        g_cObj++;
        ObjectDestroyed();
        return hr;
        }

    //Insure the document is untitled; get the requested interface.
    pDoc->Load(TRUE, NULL);
    pDoc->m_pFigure->FrameSet(m_pFR);
    hr=pDoc->m_pFigure->QueryInterface(riid, ppvObj);

    //Closing the document will destroy the objec, cause shutdown.
    if (FAILED(hr))
        {
        m_pFR->m_pCL->CloseDocument(pDoc);
        return hr;
        }

    return NOERROR;
    }






/*
 * CFigureClassFactory::LockServer
 *
 * Purpose:
 *  Increments or decrements the lock count of the serving
 *  IClassFactory object.  When the number of locks goes to
 *  zero and the number of objects is zero, we shut down the
 *  application.
 *
 * Parameters:
 *  fLock           BOOL specifying whether to increment or
 *                  decrement the lock count.
 *
 * Return Value:
 *  HRESULT         NOERROR always.
 */

STDMETHODIMP CFigureClassFactory::LockServer(BOOL fLock)
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
