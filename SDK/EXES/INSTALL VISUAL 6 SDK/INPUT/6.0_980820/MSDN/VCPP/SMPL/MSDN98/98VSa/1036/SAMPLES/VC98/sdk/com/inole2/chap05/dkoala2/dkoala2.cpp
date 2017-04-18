/*
 * DKOALA2.CPP
 * Koala Object DLL Self-Registering Server Chapter 5
 *
 * Example object structured in a DLL server.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#define INITGUIDS
#include "dkoala2.h"


//Count number of objects and number of locks.
ULONG       g_cObj=0;
ULONG       g_cLock=0;

HINSTANCE   g_hInst=NULL;


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

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, PPVOID ppv)
    {
    HRESULT             hr;
    CKoalaClassFactory *pObj;

    if (CLSID_Koala!=rclsid)
        return ResultFromScode(E_FAIL);

    pObj=new CKoalaClassFactory();

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
 * DllRegisterServer
 *
 * Purpose:
 *  Instructs the server to create its own registry entries
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  HRESULT         NOERROR if registration successful, error
 *                  otherwise.
 */

STDAPI DllRegisterServer(void)
    {
    TCHAR       szID[128];
    TCHAR       szCLSID[128];
    TCHAR       szModule[512];

    //Create some base key strings.
    StringFromGUID2(CLSID_Koala, szID, 128);
    lstrcpy(szCLSID, TEXT("CLSID\\"));
    lstrcat(szCLSID, szID);

    //Create ProgID keys
    SetKeyAndValue(TEXT("Koala1.0"), NULL
        , TEXT("Koala Object Chapter 5"));
    SetKeyAndValue(TEXT("Koala1.0"), TEXT("CLSID"), szID);

    //Create VersionIndependentProgID keys
    SetKeyAndValue(TEXT("Koala"), NULL
        , TEXT("Koala Object Chapter 5"));
    SetKeyAndValue(TEXT("Koala"), TEXT("CurVer")
        , TEXT("Koala1.0"));
    SetKeyAndValue(TEXT("Koala"), TEXT("CLSID"), szID);

    //Create entries under CLSID
    SetKeyAndValue(szCLSID, NULL, TEXT("Koala Object Chapter 5"));
    SetKeyAndValue(szCLSID, TEXT("ProgID"), TEXT("Koala1.0"));
    SetKeyAndValue(szCLSID, TEXT("VersionIndependentProgID")
        , TEXT("Koala"));
    SetKeyAndValue(szCLSID, TEXT("NotInsertable"), NULL);

    GetModuleFileName(g_hInst, szModule
        , sizeof(szModule)/sizeof(TCHAR));

   #ifdef WIN32
    SetKeyAndValue(szCLSID, TEXT("InprocServer32"), szModule);
   #else
    SetKeyAndValue(szCLSID, "InprocServer", szModule);
   #endif

	return NOERROR;
    }



/*
 * DllRegisterServer
 *
 * Purpose:
 *  Instructs the server to remove its own registry entries
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  HRESULT         NOERROR if registration successful, error
 *                  otherwise.
 */


STDAPI DllUnregisterServer(void)
    {
    TCHAR       szID[128];
    TCHAR       szCLSID[128];
    TCHAR       szTemp[256];

    //Create some base key strings.
    StringFromGUID2(CLSID_Koala, szID, 128);
    lstrcpy(szCLSID, TEXT("CLSID\\"));
    lstrcat(szCLSID, szID);

    RegDeleteKey(HKEY_CLASSES_ROOT, TEXT("Koala\\CurVer"));
    RegDeleteKey(HKEY_CLASSES_ROOT, TEXT("Koala\\CLSID"));
    RegDeleteKey(HKEY_CLASSES_ROOT, TEXT("Koala"));

    RegDeleteKey(HKEY_CLASSES_ROOT, TEXT("Koala1.0\\CLSID"));
    RegDeleteKey(HKEY_CLASSES_ROOT, TEXT("Koala1.0"));

    wsprintf(szTemp, TEXT("%s\\%s"), szCLSID, TEXT("ProgID"));
    RegDeleteKey(HKEY_CLASSES_ROOT, szTemp);

    wsprintf(szTemp, TEXT("%s\\%s"), szCLSID, TEXT("VersionIndependentProgID"));
    RegDeleteKey(HKEY_CLASSES_ROOT, szTemp);

    wsprintf(szTemp, TEXT("%s\\%s"), szCLSID, TEXT("NotInsertable"));
    RegDeleteKey(HKEY_CLASSES_ROOT, szTemp);

   #ifdef WIN32
    wsprintf(szTemp, TEXT("%s\\%s"), szCLSID, TEXT("InprocServer32"));
   #else
    wsprintf(szTemp, "%s\\%s", szCLSID, "InprocServer");
   #endif
    RegDeleteKey(HKEY_CLASSES_ROOT, szTemp);

    RegDeleteKey(HKEY_CLASSES_ROOT, szCLSID);
    return NOERROR;
    }



/*
 * SetKeyAndValue
 *
 * Purpose:
 *  Private helper function for DllRegisterServer that creates
 *  a key, sets a value, and closes that key.
 *
 * Parameters:
 *  pszKey          LPTSTR to the ame of the key
 *  pszSubkey       LPTSTR ro the name of a subkey
 *  pszValue        LPTSTR to the value to store
 *
 * Return Value:
 *  BOOL            TRUE if successful, FALSE otherwise.
 */

BOOL SetKeyAndValue(LPTSTR pszKey, LPTSTR pszSubkey
    , LPTSTR pszValue)
    {
    HKEY        hKey;
    TCHAR       szKey[256];

    lstrcpy(szKey, pszKey);

    if (NULL!=pszSubkey)
        {
        lstrcat(szKey, TEXT("\\"));
        lstrcat(szKey, pszSubkey);
        }

    if (ERROR_SUCCESS!=RegCreateKeyEx(HKEY_CLASSES_ROOT
        , szKey, 0, NULL, REG_OPTION_NON_VOLATILE
        , KEY_ALL_ACCESS, NULL, &hKey, NULL))
        return FALSE;

    if (NULL!=pszValue)
        {
        RegSetValueEx(hKey, NULL, 0, REG_SZ, (BYTE *)pszValue
            , (lstrlen(pszValue)+1)*sizeof(TCHAR));
        }

    RegCloseKey(hKey);
    return TRUE;
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
 * CKoalaClassFactory::CKoalaClassFactory
 * CKoalaClassFactory::~CKoalaClassFactory
 *
 * Constructor Parameters:
 *  None
 */

CKoalaClassFactory::CKoalaClassFactory(void)
    {
    m_cRef=0L;
    return;
    }

CKoalaClassFactory::~CKoalaClassFactory(void)
    {
    return;
    }




/*
 * CKoalaClassFactory::QueryInterface
 * CKoalaClassFactory::AddRef
 * CKoalaClassFactory::Release
 */

STDMETHODIMP CKoalaClassFactory::QueryInterface(REFIID riid
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


STDMETHODIMP_(ULONG) CKoalaClassFactory::AddRef(void)
    {
    return ++m_cRef;
    }


STDMETHODIMP_(ULONG) CKoalaClassFactory::Release(void)
    {
    if (0L!=--m_cRef)
        return m_cRef;

    delete this;
    ObjectDestroyed();
    return 0L;
    }







/*
 * CKoalaClassFactory::CreateInstance
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

STDMETHODIMP CKoalaClassFactory::CreateInstance(LPUNKNOWN pUnkOuter
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
 * CKoalaClassFactory::LockServer
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

STDMETHODIMP CKoalaClassFactory::LockServer(BOOL fLock)
    {
    if (fLock)
        g_cLock++;
    else
        g_cLock--;

    return NOERROR;
    }
