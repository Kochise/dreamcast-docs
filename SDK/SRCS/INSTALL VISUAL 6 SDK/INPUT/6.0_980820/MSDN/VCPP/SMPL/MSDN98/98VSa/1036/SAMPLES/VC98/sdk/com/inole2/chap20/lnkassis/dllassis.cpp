/*
 * DLLASSIS.CPP
 * Links Assistant Chapter 20
 *
 * DLL housing for the LinksAssistant component object for
 * container applications that use the Links dialog.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#define INITGUIDS
#include "dllassis.h"


//Count number of objects and number of locks.
ULONG       g_cObj=0;
ULONG       g_cLock=0;



/*
 * LibMain(32)
 *
 * Purpose:
 *  Entry point conditionally compiled for Win32 and Windows
 *  3.1.  Provides the proper structure for each environment.
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
 * DllCanUnloadNow
 *
 * Purpose:
 *  Standard exports for DLL component objects.
 */

HRESULT APIENTRY DllGetClassObject(REFCLSID rclsid
    , REFIID riid, PPVOID ppv)
    {
    if (CLSID_LinksAssistant!=rclsid)
        return ResultFromScode(E_FAIL);

    if (IID_IUnknown!=riid && IID_IClassFactory!=riid)
        return ResultFromScode(E_NOINTERFACE);

    *ppv=new CLinksClassFactory();

    if (NULL==*ppv)
        return ResultFromScode(E_OUTOFMEMORY);

    ((LPUNKNOWN)*ppv)->AddRef();
    g_cObj++;
    return NOERROR;
    }


STDAPI DllCanUnloadNow(void)
    {
    SCODE   sc;

    sc=(0L==g_cObj && 0L==g_cLock) ? S_OK : S_FALSE;
    return ResultFromScode(sc);
    }




/*
 * ObjectDestroyed
 *
 * Purpose:
 *  Function for the object to call when it gets destroyed.
 *  Since we're in a DLL we only track the number of objects here
 *  letting DllCanUnloadNow take care of the rest.
 */

void ObjectDestroyed(void)
    {
    g_cObj--;
    return;
    }





/*
 * CLinksClassFactory::CLinksClassFactory
 * CLinksClassFactory::~CLinksClassFactory
 */

CLinksClassFactory::CLinksClassFactory(void)
    {
    m_cRef=0L;
    return;
    }


CLinksClassFactory::~CLinksClassFactory(void)
    {
    return;
    }






/*
 * CLinksClassFactory::QueryInterface
 * CLinksClassFactory::AddRef
 * CLinksClassFactory::Release
 */

STDMETHODIMP CLinksClassFactory::QueryInterface(REFIID riid
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


STDMETHODIMP_(ULONG) CLinksClassFactory::AddRef(void)
    {
    return ++m_cRef;
    }


STDMETHODIMP_(ULONG) CLinksClassFactory::Release(void)
    {
    if (0L!=--m_cRef)
        return m_cRef;

    delete this;
    ObjectDestroyed();
    return 0;
    }





/*
 * CLinksClassFactory::CreateInstance
 *
 * Purpose:
 *  Instantiates a Links Assistant object that supports the
 *  IOleUILinkContainer interface for helping container do the
 *  Links Dialog.
 *
 * Parameters:
 *  pUnkOuter       LPUNKNOWN to the controlling IUnknown if we
 *                  are being used in an aggregation.
 *  riid            REFIID identifying the interface the caller
 *                  desires to have for the new object.
 *  ppvObj          PPVOID in which to store the desired
 *                  interface pointer for the new object.
 *
 * Return Value:
 *  HRESULT         NOERROR if successful, otherwise contains
 *                  E_NOINTERFACE if we cannot support the
 *                  requested interface.
 */

STDMETHODIMP CLinksClassFactory::CreateInstance(LPUNKNOWN pUnkOuter
    , REFIID riid, PPVOID ppvObj)
    {
    PCLinks             pObj;
    HRESULT             hr;

    *ppvObj=NULL;
    hr=ResultFromScode(E_OUTOFMEMORY);

    //We don't support aggregation
    if (NULL!=pUnkOuter)
        return ResultFromScode(CLASS_E_NOAGGREGATION);

    pObj=new CLinks(ObjectDestroyed);

    if (NULL==pObj)
        return hr;

    hr=pObj->QueryInterface(riid, ppvObj);

    if (FAILED(hr))
        delete pObj;
    else
        g_cObj++;

    return hr;
    }






/*
 * CLinksClassFactory::LockServer
 *
 * Purpose:
 *  Increments or decrements the lock count of the DLL.  If the lock
 *  count goes to zero and there are no objects, the DLL is allowed
 *  to unload.  See DllCanUnloadNow.
 *
 * Parameters:
 *  fLock           BOOL specifying whether to increment or
 *                  decrement the lock count.
 *
 * Return Value:
 *  HRESULT         NOERROR always.
 */

STDMETHODIMP CLinksClassFactory::LockServer(BOOL fLock)
    {
    if (fLock)
        g_cLock++;
    else
        g_cLock--;

    return NOERROR;
    }
