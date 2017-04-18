/*
 * DLLPOLY.CPP
 * Polyline Component Chapter 24
 *
 * Polyline component object used in CoCosmo that supports a custom
 * interface IPolyline.  Contains DLL entry code and the component
 * object exports DllGetClassObject and DllCanUnloadNow and the
 * class factory object.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#define INITGUIDS
#include "polyline.h"


//Count number of objects and number of locks.
ULONG       g_cObj=0;
ULONG       g_cLock=0;

//DLL Instance handle
HINSTANCE   g_hInst=0;



/*
 * LibMain32 (Win32)
 *
 * Purpose:
 *  Entry point for Win32 DLLs that calls the Win16 LibMain.
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

    return (0!=LibMain(hInstance, 0,  0, NULL));
    }
#endif



/*
 * LibMain (also called from Win32 LibMain32)
 *
 * Purpose:
 *  DLL-specific entry point called from LibEntry.
 */

int PASCAL LibMain(HINSTANCE hInst, WORD wDataSeg
    , WORD cbHeapSize, LPSTR lpCmdLine)
    {
    WNDCLASS    wc;

    if (GetClassInfo(hInst, SZCLASSPOLYLINE, &wc))
        return (int)hInst;

   #ifndef WIN32
    if (0!=cbHeapSize)
        UnlockData(0);
   #endif

    wc.style         = CS_HREDRAW | CS_VREDRAW;
    wc.hInstance     = hInst;
    wc.cbClsExtra    = 0;
    wc.lpfnWndProc   = PolylineWndProc;
    wc.cbWndExtra    = CBPOLYLINEWNDEXTRA;
    wc.hIcon         = NULL;
    wc.hCursor       = LoadCursor(NULL, IDC_CROSS);
    wc.hbrBackground = NULL;
    wc.lpszMenuName  = NULL;
    wc.lpszClassName = SZCLASSPOLYLINE;

    if (!RegisterClass(&wc))
        return 0;

    if (!HatchWindowRegister(hInst))
        return 0;

    g_hInst=hInst;
    return (int)hInst;
    }







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
    if (CLSID_Polyline19!=rclsid)
        return ResultFromScode(E_FAIL);

    //Check that we can provide the interface
    if (IID_IUnknown!=riid && IID_IClassFactory!=riid)
        return ResultFromScode(E_NOINTERFACE);

    //Return our IClassFactory for Polyline objects
    *ppv=new CPolylineClassFactory;

    if (NULL==*ppv)
        return ResultFromScode(E_OUTOFMEMORY);

    //AddRef the object through any interface we return
    ((LPUNKNOWN)*ppv)->AddRef();
    g_cObj++;
    return NOERROR;
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
 *  Function for the Polyline object to call when it gets destroyed.
 *  Since we're in a DLL we only track the number of objects here
 *  letting DllCanUnloadNow take care of the rest.
 */

void ObjectDestroyed(void)
    {
    g_cObj--;
    return;
    }






/*
 * CPolylineClassFactory::CPolylineClassFactory
 *
 * Purpose:
 *  Constructor for an object supporting an IClassFactory that
 *  instantiates Polyline objects.
 *
 * Parameters:
 *  None
 */

CPolylineClassFactory::CPolylineClassFactory(void)
    {
    m_cRef=0L;
    return;
    }





/*
 * CPolylineClassFactory::~CPolylineClassFactory
 *
 * Purpose:
 *  Destructor for a CPolylineClassFactory object.  This will be
 *  called when we Release the object to a zero reference count.
 */

CPolylineClassFactory::~CPolylineClassFactory(void)
    {
    return;
    }






/*
 * CPolylineClassFactory::QueryInterface
 * CPolylineClassFactory::AddRef
 * CPolylineClassFactory::Release
 */

STDMETHODIMP CPolylineClassFactory::QueryInterface(REFIID riid
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


STDMETHODIMP_(ULONG) CPolylineClassFactory::AddRef(void)
    {
    return ++m_cRef;
    }


STDMETHODIMP_(ULONG) CPolylineClassFactory::Release(void)
    {
    if (0L!=--m_cRef)
        return m_cRef;

    delete this;
    ObjectDestroyed();
    return 0L;
    }







/*
 * CPolylineClassFactory::CreateInstance
 *
 * Purpose:
 *  Instantiates a Polyline object.
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
 *  HRESULT         NOERROR if successful, otherwise E_NOINTERFACE
 *                  if we cannot support the requested interface.
 */

STDMETHODIMP CPolylineClassFactory::CreateInstance
    (LPUNKNOWN pUnkOuter, REFIID riid, PPVOID ppvObj)
    {
    PCPolyline          pObj;
    HRESULT             hr;

    *ppvObj=NULL;
    hr=ResultFromScode(E_OUTOFMEMORY);

    //Verify that a controlling unknown asks for IUnknown
    if (NULL!=pUnkOuter && IID_IUnknown!=riid)
        return ResultFromScode(E_NOINTERFACE);

    //Create the object.  This also creates a window.
    pObj=new CPolyline(pUnkOuter, ObjectDestroyed, g_hInst);

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
 * CPolylineClassFactory::LockServer
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

STDMETHODIMP CPolylineClassFactory::LockServer(BOOL fLock)
    {
    if (fLock)
        g_cLock++;
    else
        g_cLock--;

    return NOERROR;
    }
