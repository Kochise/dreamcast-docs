/*
 * ICLASSF.CPP
 *
 * Template implementation of a Class Factory object.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#include "iclassf.h"


/*
 * CClassFactory::CClassFactory
 * CClassFactory::~CClassFactory
 *
 * Constructor Parameters:
 *  None
 */

CClassFactory::CClassFactory(void)
    {
    m_cRef=0L;
    return;
    }


CClassFactory::~CClassFactory(void)
    {
    return;
    }





/*
 * CClassFactory::QueryInterface
 * CClassFactory::AddRef
 * CClassFactory::Release
 *
 * Purpose:
 *  Non-delegating IUnknown members for CClassFactory.
 */

STDMETHODIMP CClassFactory::QueryInterface(REFIID riid
    , LPVOID *ppv)
    {
    *ppv=NULL;

    if (IID_IUnknown==riid || IID_IClassFactory==riid)
        *ppv=(LPVOID)this;

    if (NULL!=*ppv)
        {
        ((LPUNKNOWN)*ppv)->AddRef();
        return NOERROR;
        }

    return ResultFromScode(E_NOINTERFACE);
    }


STDMETHODIMP_(ULONG) CClassFactory::AddRef(void)
    {
    return ++m_cRef;
    }


STDMETHODIMP_(ULONG) CClassFactory::Release(void)
    {
    if (0L!=--m_cRef)
        return m_cRef;

    //Free the object if the reference and lock counts are zero.
    delete this;
    return 0;
    }







/*
 * CClassFactory::CreateInstance
 *
 * Purpose:
 *  Instantiates an object supported by this class factory.  That
 *  object must at least support IUnknown.
 *
 *  Derived classes should override this function.
 *
 * Parameters:
 *  pUnkOuter       LPUNKNOWN to the controlling IUnknown if we are
 *                  being used in an aggregation.
 *  riid            REFIID identifying the interface the caller
 *                  desires to have for the new object.
 *  ppvObj          LPVOID * in which to store the desired
 *                  interface pointer for the new object.
 *
 * Return Value:
 *  HRESULT         NOERROR if successful, otherwise E_NOINTERFACE
 *                  if we cannot support the requested interface.
 */

STDMETHODIMP CClassFactory::CreateInstance(LPUNKNOWN pUnkOuter
    , REFIID riid, LPVOID *ppvObj)
    {
    *ppvObj=NULL;
    return ResultFromScode(E_OUTOFMEMORY);
    }






/*
 * CClassFactory::LockServer
 *
 * Purpose:
 *  Increments or decrements the lock count of the serving
 *  IClassFactory object.  When the lock count is zero and the
 *  reference count is zero we get rid of this object.
 *
 *  DLL objects should override this to affect their DLL ref count.
 *
 * Parameters:
 *  fLock           BOOL specifying whether to increment or
 *                  decrement the lock count.
 */

STDMETHODIMP CClassFactory::LockServer(BOOL fLock)
    {
    return NOERROR;
    }
