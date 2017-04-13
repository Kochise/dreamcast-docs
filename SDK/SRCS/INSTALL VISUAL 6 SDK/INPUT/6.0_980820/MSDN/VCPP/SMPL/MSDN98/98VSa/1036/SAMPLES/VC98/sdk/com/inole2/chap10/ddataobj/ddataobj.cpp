/*
 * DDATAOBJ.CPP
 * Data Object DLL Chapter 10
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#define INITGUIDS
#include "ddataobj.h"


//Count number of objects and number of locks.
ULONG       g_cObj=0;
ULONG       g_cLock=0;

//Make this global for the data object to load resources.
HINSTANCE   g_hInst=NULL;



/*
 * LibMain(32)
 *
 * Purpose:
 *  Entry point conditionally compiled for Windows NT and Windows
 *  3.1.  Provides the proper structure for each environment.
 */

#ifdef WIN32
BOOL WINAPI LibMain32(HINSTANCE hInstance, ULONG ulReason
    , LPVOID pvReserved)
    {
    if (DLL_PROCESS_DETACH==ulReason)
        {
        //Must unregsiter the class we registered
        UnregisterClass(TEXT("Advisor"), hInstance);
        return TRUE;
        }
    else
        {
        if (DLL_PROCESS_ATTACH!=ulReason)
            return TRUE;
        }

    g_hInst=hInstance;
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

HRESULT APIENTRY DllGetClassObject(REFCLSID rclsid
    , REFIID riid, PPVOID ppv)
    {
    HRESULT        hr;
    IClassFactory *pObj;

    *ppv=NULL;

    //Check each of the three CLSIDs we support.
    if (CLSID_DataObjectSmall==rclsid)
        pObj=new CDataObjectClassFactory(DOSIZE_SMALL);

    if (CLSID_DataObjectMedium==rclsid)
        pObj=new CDataObjectClassFactory(DOSIZE_MEDIUM);

    if (CLSID_DataObjectLarge==rclsid)
        pObj=new CDataObjectClassFactory(DOSIZE_LARGE);

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
 * CDataObjectClassFactory::CDataObjectClassFactory
 * CDataObjectClassFactory::~CDataObjectClassFactory
 *
 * Constructor Parameters:
 *  iSize           UINT specifying the data size for this class.
 */

CDataObjectClassFactory::CDataObjectClassFactory(UINT iSize)
    {
    m_cRef=0L;
    m_iSize=iSize;
    return;
    }


CDataObjectClassFactory::~CDataObjectClassFactory(void)
    {
    return;
    }






/*
 * CDataObjectClassFactory::QueryInterface
 * CDataObjectClassFactory::AddRef
 * CDataObjectClassFactory::Release
 */

STDMETHODIMP CDataObjectClassFactory::QueryInterface(REFIID riid
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


STDMETHODIMP_(ULONG) CDataObjectClassFactory::AddRef(void)
    {
    return ++m_cRef;
    }


STDMETHODIMP_(ULONG) CDataObjectClassFactory::Release(void)
    {
    if (0!=--m_cRef)
        return m_cRef;

    delete this;
    ObjectDestroyed();
    return 0;
    }







/*
 * CDataObjectClassFactory::CreateInstance
 *
 * Purpose:
 *  Instantiates a CDataObject object that supports the IDataObject
 *  and IUnknown interfaces.  If the caller asks for a different
 *  interface than these two then we fail.
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

STDMETHODIMP CDataObjectClassFactory::CreateInstance
    (LPUNKNOWN pUnkOuter, REFIID riid, PPVOID ppvObj)
    {
    PCDataObject        pObj;
    HRESULT             hr;

    *ppvObj=NULL;
    hr=ResultFromScode(E_OUTOFMEMORY);

    if (NULL!=pUnkOuter && IID_IUnknown!=riid)
        return ResultFromScode(E_NOINTERFACE);

    //Create the object telling it the data size to work with
    pObj=new CDataObject(pUnkOuter, ObjectDestroyed, m_iSize);

    if (NULL==pObj)
        return hr;

    if (pObj->Init())
        hr=pObj->QueryInterface(riid, ppvObj);

    //Kill the object if initial creation or FInit failed.
    if (FAILED(hr))
        delete pObj;
    else
        g_cObj++;

    return hr;
    }





/*
 * CDataObjectClassFactory::LockServer
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

STDMETHODIMP CDataObjectClassFactory::LockServer(BOOL fLock)
    {
    if (fLock)
        g_cLock++;
    else
        g_cLock--;

    return NOERROR;
    }
