/*
 * DKOALA3.CPP
 * Koala Object DLL Licensed Server Chapter 5
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
#include "dkoala3.h"


//Count number of objects and number of locks.
ULONG       g_cObj=0;
ULONG       g_cLock=0;

HINSTANCE   g_hInst=NULL;


//License key string, stored in ANSI to match contents of LIC file
char    g_szLic[]="Koala Object #3 Copyright (c)1993-1995 Microsoft Corp.";
BOOL    g_fMachineLicensed=FALSE;


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

    g_fMachineLicensed=CheckForLicenseFile(hInstance
        , TEXT("DKOALA3.LIC"), (BYTE *)g_szLic, lstrlenA(g_szLic));

    g_hInst=hInstance;
    return TRUE;
    }
#else
int PASCAL LibMain(HINSTANCE hInstance, WORD wDataSeg
    , WORD cbHeapSize, LPSTR lpCmdLine)
    {
    if (0!=cbHeapSize)
        UnlockData(0);

    g_fMachineLicensed=CheckForLicenseFile(hInstance
        , TEXT("DKOALA3.LIC"), (BYTE *)g_szLic, lstrlen(g_szLic));

    g_hInst=hInstance;
    return (int)hInstance;
    }
#endif




/*
 * CheckForLicenseFile
 *
 * Purpose:
 *  Attempts to load DKOALA3.LIC from the same directory as
 *  this DLL, attempting to match the first part of that file
 *  with our license string (typical licensing scheme).  If
 *  the match is successful, then this DLL can create any
 *  instances of Koala objects without additional trouble.
 *  Otherwise the client has to call IClassFactory2::CreateInstance-
 *  Lic to instantiate anything.
 *
 * Parameters:
 *  hInst           HINSTANCE of the module describing the
 *                  directory in which we expect to find the
 *                  license file.
 *  pszFile         LPTSTR to the name of the file to look for.
 *  pbLic           LPBYTE to the expected contents of the file.
 *  cb              UINT number of butes to compare.
 *
 * Return Value:
 *  BOOL            TRUE if the file is available, FALSE otherwise.
 */

BOOL CheckForLicenseFile(HINSTANCE hInst, LPTSTR pszFile
    , LPBYTE pbLic, UINT cb)
    {
    BOOL        fFound=FALSE;
    TCHAR       szPath[_MAX_PATH];
    LPTSTR      pszTemp;
    LPBYTE      pbCompare;
   #ifdef WIN32
    HANDLE      hFile;
   #else
    OFSTRUCT    of;
    HFILE       hFile;
   #endif
    UINT        cbRead;
    ULONG       cbWasRead;

    //Get the module path, then replace DLL name with LIC filename
	GetModuleFileName(hInst, szPath, _MAX_PATH);
	pszTemp=_tcsrchr(szPath, '\\')+1;
    lstrcpy(pszTemp, pszFile);

    /*
     * Now open the file and read contents into an allocated
     * pbCompare.  The check if the contents of that file and
     * pbLic match.  If so, then return success, otherwise
     * failure.
     */
   #ifdef WIN32
    hFile=CreateFile(szPath, GENERIC_READ, FILE_SHARE_READ
        , NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
   #else
    hFile=OpenFile(szPath, &of, OF_READ);
   #endif

    /*
     * NOTE:  INVALID_HANDLE_VALUE, ReadFile, and CloseHandle
     * are macros in INC\book1632.h when compiling for Win16.
     */
    if (INVALID_HANDLE_VALUE==hFile)
        return FALSE;

    cbRead=cb*sizeof(BYTE);
    pbCompare=(LPBYTE)malloc(cbRead+4);

    if (NULL!=pbCompare)
        {
        ReadFile(hFile, pbCompare, cbRead, &cbWasRead, NULL);
	    fFound=(0==memcmp(pbLic, pbCompare, cb));
	    free(pbCompare);
        }

    CloseHandle(hFile);
    return fFound;
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

    if (IID_IUnknown==riid || IID_IClassFactory==riid
        || IID_IClassFactory2==riid)
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
 * CKoalaClassFactory::CreateAnObject
 * (Private)
 *
 * Purpose:
 *  Central function to create instances of objects that is called
 *  from CreateInstance and CreateInstanceLic.  This takes the same
 *  parameters as CreateInstance below.
 */

HRESULT CKoalaClassFactory::CreateAnObject(LPUNKNOWN pUnkOuter
    , REFIID riid, PPVOID ppvObj)
    {
    PCKoala             pObj;
    HRESULT             hr;

    //Verify that a controlling unknown asks for IUnknown
    if (NULL!=pUnkOuter && IID_IUnknown!=riid)
        return ResultFromScode(CLASS_E_NOAGGREGATION);

    hr=ResultFromScode(E_OUTOFMEMORY);

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
    *ppvObj=NULL;

    /*
     * The license file *must* be around for this simple
     * CreateInstance to work.  One we've checked, call the central
     * creation function.
     */
    if (!g_fMachineLicensed)
        return ResultFromScode(CLASS_E_NOTLICENSED);

    return CreateAnObject(pUnkOuter, riid, ppvObj);
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




/*
 * CKoalaClassFactory::GetLicInfo
 *
 * Purpose:
 *  Fills a LICINFO structure with license information for
 *  this class factory.
 *
 * Parameters:
 *  pLicInfo        LPLICINFO to the structure to fill
 */

STDMETHODIMP CKoalaClassFactory::GetLicInfo(LPLICINFO pLicInfo)
    {
    if (NULL==pLicInfo)
        return ResultFromScode(E_POINTER);

    pLicInfo->cbLicInfo=sizeof(LICINFO);

    //This says whether RequestLicKey will work
    pLicInfo->fRuntimeKeyAvail=g_fMachineLicensed;

    //This says whether the standard CreateInstance will work
    pLicInfo->fLicVerified=g_fMachineLicensed;

    return NOERROR;
    }




/*
 * CKoalaClassFactory::RequestLicKey
 *
 * Purpose:
 *  Retrieves a license key from this class factory for use with
 *  CreateInstanceLic.
 *
 * Parameters:
 *  dwReserved      DWORD reserved for future use with multiple
 *                  licenses.
 *  pbstrKey        BSTR * in which to return the key.
 */

STDMETHODIMP CKoalaClassFactory::RequestLicKey(DWORD dwReserved
    , BSTR *pbstrKey)
    {
    OLECHAR     szTemp[256];

    //Can't give away a key on an unlicensed machine
    if (!g_fMachineLicensed)
        return ResultFromScode(CLASS_E_NOTLICENSED);

   #ifndef WIN32
    lstrcpy(g_szLic, szTemp);
   #else
    mbstowcs(szTemp, g_szLic, sizeof(g_szLic));
   #endif
    *pbstrKey=SysAllocString(szTemp);
    return (NULL!=*pbstrKey) ? NOERROR : ResultFromScode(E_OUTOFMEMORY);
    }





/*
 * CKoalaClassFactory::CreateInstanceLic
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
 *  ppvObj          PPVOID in which to store the desired
 *                  interface pointer for the new object.
 */

STDMETHODIMP CKoalaClassFactory::CreateInstanceLic(LPUNKNOWN pUnkOuter
    , LPUNKNOWN pUnkReserved, REFIID riid, BSTR bstrKey
    , PPVOID ppvObj)
    {
    BOOL        fMatch;
    BSTR        bstrTemp;
    UINT        cch;
    OLECHAR     szLic[256];
   #ifdef WIN32ANSI
    char        szTemp[256];
   #endif

    *ppvObj=NULL;

    /*
     * Get our own license key that should match bstrKey exactly.
     * This code is coped from RequestLicKey.
     */
   #ifndef WIN32
    lstrcpy(g_szLic, szLic);
   #else
    mbstowcs(szLic, g_szLic, sizeof(g_szLic));
   #endif
    bstrTemp=SysAllocString(szLic);

    if (NULL==bstrTemp)
        return ResultFromScode(E_OUTOFMEMORY);

   #ifdef WIN32ANSI
    WideCharToMultiByte(CP_ACP, 0, bstrTemp, -1, szTemp
        , 256, NULL, NULL);
    cch=lstrlen(szTemp);
   #else
    cch=lstrlen(bstrTemp);
   #endif
    fMatch=(0==memcmp(bstrTemp, bstrKey, cch*sizeof(OLECHAR)));
    SysFreeString(bstrTemp);

    if (!fMatch)
        return ResultFromScode(CLASS_E_NOTLICENSED);

    return CreateAnObject(pUnkOuter, riid, ppvObj);
    }
