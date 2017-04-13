/*
 * KOALAPRX.CPP
 * Koala Custom Marshaling Proxy Chapter 6
 *
 * Example proxy for an object using custom marshaling
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#define INITGUIDS
#include "koalaprx.h"

//Count number of objects and number of locks.
ULONG       g_cObj=0;
ULONG       g_cLock=0;


/*
 * LibMain(32)
 *
 * Purpose:
 *  Entry point conditionally compiled for Win32 and Win16.
 *  Provides the proper structure for each environment.
 */

#ifdef WIN32
BOOL WINAPI LibMain32(HINSTANCE hInstance, ULONG ulReason
    , LPVOID pvReserved)
    {
    if (DLL_PROCESS_DETACH==ulReason)
        {
        return TRUE;
        }
    else
        {
        if (DLL_PROCESS_ATTACH!=ulReason)
            return TRUE;
        }

    return TRUE;
    }
#else
int PASCAL LibMain(HINSTANCE hInstance, WORD wDataSeg
    , WORD cbHeapSize, LPSTR lpCmdLine)
    {
    if (0!=cbHeapSize)
        UnlockData(0);

    return (int)hInstance;
    }
#endif



/*
 * DllGetClassObject
 *
 * Purpose:
 *  Provides an IClassFactory for a given CLSID that this DLL is
 *  registered to support.  This DLL is placed under the CLSID
 *  in the registration database as the InProcServer.
 *
 * Parameters:
 *  clsID           REFCLSID that identifies the class factory
 *                  desired.  Since this parameter is passed this
 *                  DLL can handle any number of objects simply
 *                  by returning different class factories here
 *                  for different CLSIDs.
 *
 *  riid            REFIID specifying the interface the caller wants
 *                  on the class object, usually IID_ClassFactory.
 *
 *  ppv             PPVOID in which to return the interface
 *                  pointer.
 *
 * Return Value:
 *  HRESULT         NOERROR on success, otherwise an error code.
 */

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, PPVOID ppv)
    {
    HRESULT             hr;
    CKoalaProxyFactory *pObj;

    if (CLSID_KoalaProxy!=rclsid)
        return ResultFromScode(E_FAIL);

    pObj=new CKoalaProxyFactory();

    if (NULL==pObj)
        return ResultFromScode(E_OUTOFMEMORY);

    hr=pObj->QueryInterface(riid, ppv);

    if (FAILED(hr))
        delete pObj;
    else
        g_cObj++;

    return hr;
    }





/*
 * DllCanUnloadNow
 *
 * Purpose:
 *  Answers if the DLL can be freed, that is, if there are no
 *  references to anything this DLL provides.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  BOOL            TRUE if nothing is using us, FALSE otherwise.
 */

STDAPI DllCanUnloadNow(void)
    {
    SCODE   sc;

    //Our answer is whether there are any object or locks
    sc=(0L==g_cObj && 0L==g_cLock) ? S_OK : S_FALSE;
    return ResultFromScode(sc);
    }




/*
 * ObjectDestroyed
 *
 * Purpose:
 *  Function for the Koala object to call when it gets destroyed.
 *  Since we're in a DLL we only track the number of objects here,
 *  letting DllCanUnloadNow take care of the rest.
 */

void ObjectDestroyed(void)
    {
    g_cObj--;
    return;
    }





/*
 * CKoalaProxyFactory::CKoalaProxyFactory
 * CKoalaProxyFactory::~CKoalaProxyFactory
 *
 * Constructor Parameters:
 *  None
 */

CKoalaProxyFactory::CKoalaProxyFactory(void)
    {
    m_cRef=0L;
    return;
    }

CKoalaProxyFactory::~CKoalaProxyFactory(void)
    {
    return;
    }




/*
 * CKoalaProxyFactory::QueryInterface
 * CKoalaProxyFactory::AddRef
 * CKoalaProxyFactory::Release
 */

STDMETHODIMP CKoalaProxyFactory::QueryInterface(REFIID riid
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


STDMETHODIMP_(ULONG) CKoalaProxyFactory::AddRef(void)
    {
    return ++m_cRef;
    }


STDMETHODIMP_(ULONG) CKoalaProxyFactory::Release(void)
    {
    if (0L!=--m_cRef)
        return m_cRef;

    delete this;
    ObjectDestroyed();
    return 0L;
    }







/*
 * CKoalaProxyFactory::CreateInstance
 *
 * Purpose:
 *  Instantiates a Koala object returning an interface pointer.
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
 *  HRESULT         NOERROR if successful, otherwise E_NOINTERFACE
 *                  if we cannot support the requested interface.
 */

STDMETHODIMP CKoalaProxyFactory::CreateInstance(LPUNKNOWN pUnkOuter
    , REFIID riid, PPVOID ppvObj)
    {
    PCKoala             pObj;
    HRESULT             hr;

    *ppvObj=NULL;
    hr=ResultFromScode(E_OUTOFMEMORY);

    //Verify that a controlling unknown asks for IUnknown
    if (NULL!=pUnkOuter && IID_IUnknown!=riid)
        return ResultFromScode(CLASS_E_NOAGGREGATION);

    //Create the object passing function to notify on destruction.
    pObj=new CKoala(pUnkOuter, ObjectDestroyed);

    if (NULL==pObj)
        return hr;

    if (pObj->Init())
        hr=pObj->QueryInterface(riid, ppvObj);

    //Kill the object if initial creation or Init failed.
    if (FAILED(hr))
        delete pObj;
    else
        g_cObj++;

    return hr;
    }






/*
 * CKoalaProxyFactory::LockServer
 *
 * Purpose:
 *  Increments or decrements the lock count of the DLL.  If the
 *  lock count goes to zero and there are no objects, the DLL
 *  is allowed to unload.  See DllCanUnloadNow.
 *
 * Parameters:
 *  fLock           BOOL specifying whether to increment or
 *                  decrement the lock count.
 *
 * Return Value:
 *  HRESULT         NOERROR always.
 */

STDMETHODIMP CKoalaProxyFactory::LockServer(BOOL fLock)
    {
    if (fLock)
        g_cLock++;
    else
        g_cLock--;

    return NOERROR;
    }
