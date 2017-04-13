/*
 * DBEEPER.CPP
 * Beeper Automation Object Chapter 14
 *
 * Server module code for the Beeper object.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#define INITGUIDS
#include "dbeeper.h"


//Count number of objects and number of locks.
ULONG       g_cObj=0;
ULONG       g_cLock=0;
HINSTANCE   g_hInst=NULL;   //For LoadString

#ifdef WIN32
DWORD       g_dwTLS;        //For thread-local storage
#endif

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
    g_hInst=hInstance;

    if (DLL_PROCESS_DETACH==ulReason)
        {
        TlsFree(g_dwTLS);
        return TRUE;
        }
    else
        {
        if (DLL_PROCESS_ATTACH!=ulReason)
            return TRUE;

        g_dwTLS=TlsAlloc();
        }

    return TRUE;
    }
#else
int PASCAL LibMain(HINSTANCE hInstance, WORD wDataSeg
    , WORD cbHeapSize, LPSTR lpCmdLine)
    {
    if (0!=cbHeapSize)
        UnlockData(0);

    g_hInst=hInstance;
    return (int)hInstance;
    }
#endif



/*
 * DllGetClassObject
 * DllCanUnloadNow
 * Standard COM exports for DLL servers.
 */

HRESULT APIENTRY DllGetClassObject(REFCLSID rclsid, REFIID riid
    , PPVOID ppv)
    {
    CBeeperFactory *pBF;
    HRESULT         hr;

    if (CLSID_Beeper!=rclsid)
        return ResultFromScode(E_FAIL);

    //Check that we can provide the interface
    if (IID_IUnknown!=riid && IID_IClassFactory!=riid)
        return ResultFromScode(E_NOINTERFACE);

    //Return our beeper factory's IClassFactory
    pBF=new CBeeperFactory();

    if (NULL==pBF)
        return ResultFromScode(E_OUTOFMEMORY);

    //If the factory hasn't the interface, delete it
    hr=pBF->QueryInterface(riid, ppv);

    if (FAILED(hr))
        delete pBF;
    else
        g_cObj++;

    return hr;
    }


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
 *  Function for the object to call when it gets destroyed.  Since
 *  we're in a DLL we only track the number of objects here, letting
 *  DllCanUnloadNow take care of the rest.
 */

void ObjectDestroyed(void)
    {
    g_cObj--;
    return;
    }



/*
 * CBeeperFactory::CBeeperFactory
 * CBeeperFactory::~CBeeperFactory
 */

CBeeperFactory::CBeeperFactory(void)
    {
    m_cRef=0L;
    return;
    }


CBeeperFactory::~CBeeperFactory(void)
    {
    return;
    }






/*
 * CBeeperFactory::QueryInterface
 * CBeeperFactory::AddRef
 * CBeeperFactory::Release
 */

STDMETHODIMP CBeeperFactory::QueryInterface(REFIID riid, PPVOID ppv)
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


STDMETHODIMP_(ULONG) CBeeperFactory::AddRef(void)
    {
    return ++m_cRef;
    }


STDMETHODIMP_(ULONG) CBeeperFactory::Release(void)
    {
    if (0!=--m_cRef)
        return m_cRef;

    delete this;
    ObjectDestroyed();
    return 0;
    }



/*
 * CBeeperFactory::CreateInstance
 * CBeeperFactory::LockServer
 */

STDMETHODIMP CBeeperFactory::CreateInstance(LPUNKNOWN pUnkOuter
    , REFIID riid, PPVOID ppvObj)
    {
    PCBeeper            pObj;
    HRESULT             hr;

    *ppvObj=NULL;
    hr=ResultFromScode(E_OUTOFMEMORY);

    //Verify that a controlling unknown asks for IUnknown
    if (NULL!=pUnkOuter && IID_IUnknown!=riid)
        return ResultFromScode(CLASS_E_NOAGGREGATION);

    //Create the object passing function to notify on destruction.
    pObj=new CBeeper(pUnkOuter, ObjectDestroyed);

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


STDMETHODIMP CBeeperFactory::LockServer(BOOL fLock)
    {
    if (fLock)
        g_cLock++;
    else
        g_cLock--;

    return NOERROR;
    }
