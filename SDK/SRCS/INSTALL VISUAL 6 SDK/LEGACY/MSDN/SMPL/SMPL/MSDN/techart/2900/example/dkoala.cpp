
/* @doc
 *
 * @module DKOALA.CPP - Koala Object DLL Chapter 4 |
 *
 * Example object implemented in a DLL.  This object supports
 * IUnknown and IPersist interfaces, meaning it doesn't know
 * anything more than how to return its class ID, but it
 * demonstrates a component object in a DLL.
 *
 * Copyright (c)1993 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Software Design Engineer
 * Microsoft Systems Developer Relations
 *
 * Autoduck example by Eric Artzt (erica@microsoft.com)
 */


//Do this once in the entire build
#define INITGUIDS

#include "dkoala.h"


//@globalv Count number of objects.
ULONG       g_cObj=0;

//@globalv Count number of locks
ULONG       g_cLock=0;


/* @doc INTERNAL
 */

#ifdef WIN32

/*
 * @func Entry point conditionally compiled for Windows NT and Windows
 *  3.1. Provides the proper structure for each environment.
 */

BOOL WINAPI LibMain(HINSTANCE hInstance, ULONG ulReason
    , LPVOID pvReserved)
    {
    if (DLL_PROCESS_DETACH==ulReason)
        {
        WEP(0);
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
int FAR PASCAL LibMain(HINSTANCE hInstance, WORD wDataSeg
    , WORD cbHeapSize, LPSTR lpCmdLine)
    {
    if (0!=cbHeapSize)
        UnlockData(0);

    return (int)hInstance;
    }
#endif




/*
 * @func Required DLL Exit function.  Does nothing.
 *
 * @parm int | bSystemExit | BOOL indicating if the system is being shut
 *  down or the DLL has just been unloaded.
 *
 * @rdesc Unused.
 *
 */

int FAR PASCAL WEP(int bSystemExit)
    {
    return 0;
    }




/*
 * @func Provides an IClassFactory for a given CLSID that this DLL is
 *  registered to support.  This DLL is placed under the CLSID
 *  in the registration database as the InProcServer.
 *
 * @parm REFCLSID | clsID | Identifies the class factory
 *                  desired.  Since this parameter is passed this
 *                  DLL can handle any number of objects simply
 *                  by returning different class factories here
 *                  for different CLSIDs.
 *
 * @parm REFIID | riid | Specifies the interface the caller wants
 *                  on the class object, usually IID_ClassFactory.
 *
 * @parm LPLPVOID | ppv | Address at which to return the interface
 *                  pointer.
 *
 * @rdesc NOERROR on success, otherwise an error code.
 */

HRESULT EXPORT FAR PASCAL DllGetClassObject(REFCLSID rclsid, REFIID riid,
    LPLPVOID ppv)
    {
    if (!IsEqualCLSID(rclsid, CLSID_Koala))
        return ResultFromScode(E_FAIL);

    //Check that we can provide the interface
    if (!IsEqualIID(riid, IID_IUnknown)
        && !IsEqualIID(riid, IID_IClassFactory))
        return ResultFromScode(E_NOINTERFACE);

    //Return our IClassFactory for Koala objects
    *ppv=(LPVOID)new CKoalaClassFactory();

    if (NULL==*ppv)
        return ResultFromScode(E_OUTOFMEMORY);

    //AddRef the object through any interface we return
    ((LPUNKNOWN)*ppv)->AddRef();

    return NOERROR;
    }





/*
 * @func Answers if the DLL can be freed, that is, if there are no
 *  references to anything this DLL provides.
 *
 * @rdesc TRUE if nothing is using us, FALSE otherwise.
 */

STDAPI DllCanUnloadNow(void)
    {
    SCODE   sc;

    //Our answer is whether there are any object or locks
    sc=(0L==g_cObj && 0L==g_cLock) ? S_OK : S_FALSE;
    return ResultFromScode(sc);
    }




/*
 * @func Function for the Koala object to call when it gets destroyed.
 *  Since we're in a DLL we only track the number of objects here,
 *  letting DllCanUnloadNow take care of the rest.
 *
 * @rdesc None
 */

void FAR PASCAL ObjectDestroyed(void)
    {
    g_cObj--;
    return;
    }





/*
 * @mfunc <c CKoalaClassFactory> constructor.
 */
CKoalaClassFactory::CKoalaClassFactory(void)
    {
    m_cRef=0L;
    return;
    }


/*
 * @mfunc <c CKoalaClassFactory> destructor.
 */
CKoalaClassFactory::~CKoalaClassFactory(void)
    {
    return;
    }


/*
 * @mfunc QueryInterface for CKoalaClassFactory.
 */
STDMETHODIMP CKoalaClassFactory::QueryInterface(REFIID riid
    , LPLPVOID ppv)
    {
    *ppv=NULL;

    //Any interface on this object is the object pointer.
    if (IsEqualIID(riid, IID_IUnknown)
        || IsEqualIID(riid, IID_IClassFactory))
        *ppv=(LPVOID)this;

    /*
     * If we actually assign an interface to ppv we need to AddRef
     * it since we're returning a new pointer.
     */
    if (NULL!=*ppv)
        {
        ((LPUNKNOWN)*ppv)->AddRef();
        return NOERROR;
        }

    return ResultFromScode(E_NOINTERFACE);
    }


/*
 * @mfunc Increments a reference count for every new copy of an interface 
 *  pointer.
 */
STDMETHODIMP_(ULONG) CKoalaClassFactory::AddRef(void)
    {
    return ++m_cRef;
    }


/*
 * @mfunc Decrements the reference count on the interface.
 */
STDMETHODIMP_(ULONG) CKoalaClassFactory::Release(void)
    {
    ULONG           cRefT;

    cRefT=--m_cRef;

    if (0L==m_cRef)
        delete this;

    return cRefT;
    }







/*
 * @mfunc Instantiates a Koala object that supports the IPersist
 *  and IUnknown interfaces.  If the caller asks for a different
 *  interface than these two then we fail.
 *
 * @parm LPUNKNOWN | pUnkOuter | Points to the controlling <om .IUnknown> 
 *                  if we are being used in an aggregation.
 *
 * @parm REFIID | riid | Identifies the interface the caller
 *                  desires to have for the new object.
 *
 * @parm LPLPVOID | ppvObj | Location in which to store the desired
 *                  interface pointer for the new object.
 *
 * @rvalue NOERROR | If successful
 *
 * @rvalue E_NOINTERFACE | If we cannot support the requested interface.
 */

STDMETHODIMP CKoalaClassFactory::CreateInstance(LPUNKNOWN pUnkOuter
    , REFIID riid, LPLPVOID ppvObj)
    {
    LPCKoala            pObj;
    HRESULT             hr;

    *ppvObj=NULL;
    hr=ResultFromScode(E_OUTOFMEMORY);

    //Verify that a controlling unknown asks for IUnknown
    if (NULL!=pUnkOuter && !IsEqualIID(riid, IID_IUnknown))
        return ResultFromScode(E_NOINTERFACE);

    //Create the object passing function to notify on destruction.
    pObj=new CKoala(pUnkOuter, ObjectDestroyed);

    if (NULL==pObj)
        return hr;

    if (pObj->FInit())
        hr=pObj->QueryInterface(riid, ppvObj);

    //Kill the object if initial creation or FInit failed.
    if (FAILED(hr))
        delete pObj;
    else
        g_cObj++;

    return hr;
    }



/*
 * @mfunc Increments or decrements the lock count of the DLL.  If the
 *  lock count goes to zero and there are no objects, the DLL
 *  is allowed to unload.  See DllCanUnloadNow.
 *
 * @parm BOOL | fLock | Specifies whether to increment or
 *                  decrement the lock count.
 *
 * @rvalue NOERROR | Always.
 */

STDMETHODIMP CKoalaClassFactory::LockServer(BOOL fLock)
    {
    if (fLock)
        g_cLock++;
    else
        g_cLock--;

    return NOERROR;
    }
