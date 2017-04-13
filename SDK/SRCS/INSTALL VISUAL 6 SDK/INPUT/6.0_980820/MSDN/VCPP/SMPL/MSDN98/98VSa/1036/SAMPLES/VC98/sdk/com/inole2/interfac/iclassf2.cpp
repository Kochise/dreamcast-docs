/*
 * ICLASSF2.CPP
 *
 * Template implementation of a Class Factory object that
 * supports licensing.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#include "iclassf2.h"


/*
 * CClassFactory2::CClassFactory2
 * CClassFactory2::~CClassFactory2
 *
 * Constructor Parameters:
 *  None
 */

CClassFactory2::CClassFactory2(void)
    {
    m_cRef=0L;
    return;
    }


CClassFactory2::~CClassFactory2(void)
    {
    return;
    }





/*
 * CClassFactory2::QueryInterface
 * CClassFactory2::AddRef
 * CClassFactory2::Release
 *
 * Purpose:
 *  Non-delegating IUnknown members for CClassFactory2.
 */

STDMETHODIMP CClassFactory2::QueryInterface(REFIID riid
    , LPVOID *ppv)
    {
    *ppv=NULL;

    if (IID_IUnknown==riid || IID_IClassFactory2==riid
        || IID_IClassFactory2==riid)
        *ppv=(LPVOID)this;

    if (NULL!=*ppv)
        {
        ((LPUNKNOWN)*ppv)->AddRef();
        return NOERROR;
        }

    return ResultFromScode(E_NOINTERFACE);
    }


STDMETHODIMP_(ULONG) CClassFactory2::AddRef(void)
    {
    return ++m_cRef;
    }


STDMETHODIMP_(ULONG) CClassFactory2::Release(void)
    {
    if (0L!=--m_cRef)
        return m_cRef;

    //Free the object if the reference and lock counts are zero.
    delete this;
    return 0;
    }







/*
 * CClassFactory2::CreateInstance
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

STDMETHODIMP CClassFactory2::CreateInstance(LPUNKNOWN pUnkOuter
    , REFIID riid, LPVOID *ppvObj)
    {
    *ppvObj=NULL;
    return ResultFromScode(E_OUTOFMEMORY);
    }






/*
 * CClassFactory2::LockServer
 *
 * Purpose:
 *  Increments or decrements the lock count of the serving
 *  IClassFactory2 object.  When the lock count is zero and the
 *  reference count is zero we get rid of this object.
 *
 *  DLL objects should override this to affect their DLL ref count.
 *
 * Parameters:
 *  fLock           BOOL specifying whether to increment or
 *                  decrement the lock count.
 */

STDMETHODIMP CClassFactory2::LockServer(BOOL fLock)
    {
    return NOERROR;
    }



/*
 * CClassFactory2::GetLicInfo
 *
 * Purpose:
 *  Fills a LICINFO structure with license information for
 *  this class factory.
 *
 * Parameters:
 *  pLicInfo        LPLICINFO to the structure to fill
 */

STDMETHODIMP CClassFactory2::GetLicInfo(LPLICINFO pLicInfo)
    {
    if (NULL==pLicInfo)
        return ResultFromScode(E_POINTER);

    return ResultFromScode(E_NOTIMPL);
    }




/*
 * CClassFactory2::RequestLicKey
 *
 * Purpose:
 *  Retrieves a license key from this class factory for use with
 *  CreateInstanceLic.
 *
 * Parameters:
 *  dwReserved      DWORD reserved
 *  pbstrKey        BSTR * in which to return the key.
 */

STDMETHODIMP CClassFactory2::RequestLicKey(DWORD dwReserved
    , BSTR *pbstrKey)
    {
    *pbstrKey=NULL;
    return ResultFromScode(E_NOTIMPL);
    }



/*
 * CClassFactory2::CreateInstanceLic
 *
 * Purpose:
 *  Creates and instance of the object given a license key.
 *  Same as CreateInstance, and implementations of this function
 *  will typically just validate the key and call CreateInstance.
 *
 * Parameters:
 *  pUnkOuter       LPUNKNOWN to the controlling IUnknown if we are
 *                  being used in an aggregation.
 *  pUnkReserved    LPUNKNOWN reserved.
 *  riid            REFIID identifying the interface the caller
 *                  desires to have for the new object.
 *  bstrKey         BSTR key used to validate creation.
 *  ppvObj          LPVOID * in which to store the desired
 *                  interface pointer for the new object.
 */

STDMETHODIMP CClassFactory2::CreateInstanceLic(LPUNKNOWN pUnkOuter
    , LPUNKNOWN pUnkReserved, REFIID riid, BSTR bstrKey
    , LPVOID *ppvObj)
    {
    *ppvObj=NULL;

    //Validate bstrKey

    //Create an instance once the key is validated.
    return CreateInstance(pUnkOuter, riid, ppvObj);
    }
