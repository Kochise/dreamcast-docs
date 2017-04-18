/*
 * EKOALA2.CPP
 * Koala Object EXE Self-Registering Server Chapter 5
 *
 * Example object implemented in an EXE.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#define INITGUIDS
#include "ekoala2.h"


//Count number of objects and number of locks.
ULONG       g_cObj=0;
ULONG       g_cLock=0;

//Make window handle global so other code can cause a shutdown
HWND        g_hWnd=NULL;


/*
 * WinMain
 *
 * Purpose:
 *  Main entry point of application.
 */

int PASCAL WinMain(HINSTANCE hInst, HINSTANCE hInstPrev
    , LPSTR pszCmdLine, int nCmdShow)
    {
    MSG         msg;
    PAPP        pApp;

    SETMESSAGEQUEUE;

    pApp=new CApp(hInst, hInstPrev, pszCmdLine, nCmdShow);

    if (NULL==pApp)
        return -1;

    if (pApp->Init())
        {
        while (GetMessage(&msg, NULL, 0,0 ))
            {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
            }
        }

    delete pApp;
    return msg.wParam;
    }



/*
 * KoalaWndProc
 *
 * Purpose:
 *  Standard window class procedure.
 */

LRESULT APIENTRY KoalaWndProc(HWND hWnd, UINT iMsg
    , WPARAM wParam, LPARAM lParam)
    {
    PAPP        pApp;

    pApp=(PAPP)GetWindowLong(hWnd, KOALAWL_STRUCTURE);

    switch (iMsg)
        {
        case WM_NCCREATE:
            pApp=(PAPP)(((LPCREATESTRUCT)lParam)->lpCreateParams);
            SetWindowLong(hWnd, KOALAWL_STRUCTURE, (LONG)pApp);
            return (DefWindowProc(hWnd, iMsg, wParam, lParam));

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        default:
            return (DefWindowProc(hWnd, iMsg, wParam, lParam));
        }

    return 0L;
    }




/*
 * ObjectDestroyed
 *
 * Purpose:
 *  Function for the Koala object to call when it gets destroyed.
 *  We destroy the main window if the proper conditions are met
 *  for shutdown.
 */

void ObjectDestroyed(void)
    {
    g_cObj--;

    //No more objects and no locks, shut the app down.
    if (0L==g_cObj && 0L==g_cLock && IsWindow(g_hWnd))
        PostMessage(g_hWnd, WM_CLOSE, 0, 0L);

    return;
    }




/*
 * CApp::CApp
 * CApp::~CApp
 *
 * Constructor Parameters:
 *  hInst           HINSTANCE of the Application from WinMain
 *  hInstPrev       HINSTANCE of a previous instance from WinMain
 *  pszCmdLine      LPSTR of the command line.
 *  nCmdShow        UINT specifying how to show the app window,
 *                  from WinMain.
 */

CApp::CApp(HINSTANCE hInst, HINSTANCE hInstPrev
    , LPSTR pszCmdLine, UINT nCmdShow)
    {
    //Initialize WinMain parameter holders.
    m_hInst     =hInst;
    m_hInstPrev =hInstPrev;
    m_pszCmdLine=pszCmdLine;
    m_nCmdShow  =nCmdShow;

    m_hWnd=NULL;
    m_dwRegCO=0;
    m_pIClassFactory=NULL;
    m_fInitialized=FALSE;
    return;
    }


CApp::~CApp(void)
    {
    //Opposite of CoRegisterClassObject; class factory ref is now 1
    if (0L!=m_dwRegCO)
        CoRevokeClassObject(m_dwRegCO);

    //The last Release, which frees the class factory.
    if (NULL!=m_pIClassFactory)
        m_pIClassFactory->Release();

    if (m_fInitialized)
        CoUninitialize();

    return;
    }




/*
 * CApp::Init
 *
 * Purpose:
 *  Initializes an CApp object by registering window classes,
 *  creating the main window, and doing anything else prone to
 *  failure.  If this function fails the caller should guarantee
 *  that the destructor is called.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  BOOL            TRUE if successful, FALSE otherwise.
 */

BOOL CApp::Init(void)
    {
    WNDCLASS    wc;
    HRESULT     hr;
   #ifndef WIN32
    DWORD       dwVer;
   #endif

    /*
     * Check if we're being run for self-registration.  If so,
     * do the job, then quit by returning FALSE from here.
     */
    if (0==lstrcmpiA(m_pszCmdLine, "-RegServer")
        || 0==lstrcmpiA(m_pszCmdLine, "/RegServer"))
        {
        RegisterServer();
        return FALSE;
        }

    if (0==lstrcmpiA(m_pszCmdLine, "-UnregServer")
        || 0==lstrcmpiA(m_pszCmdLine, "/UnregServer"))
        {
        UnregisterServer();
        return FALSE;
        }

    //Fail if we're run outside of CoGetClassObject
    if (lstrcmpiA(m_pszCmdLine, "-Embedding")
        && lstrcmpiA(m_pszCmdLine, "/Embedding"))
        return FALSE;

   #ifndef WIN32
    dwVer=CoBuildVersion();

    if (rmm!=HIWORD(dwVer))
        return FALSE;

    //No need to check minor versions.
   #endif

    //Call CoInitialize so we can call other Co* functions
    if (FAILED(CoInitialize(NULL)))
        return FALSE;

    m_fInitialized=TRUE;

    if (!m_hInstPrev)
        {
        wc.style          = CS_HREDRAW | CS_VREDRAW;
        wc.lpfnWndProc    = KoalaWndProc;
        wc.cbClsExtra     = 0;
        wc.cbWndExtra     = CBWNDEXTRA;
        wc.hInstance      = m_hInst;
        wc.hIcon          = NULL;
        wc.hCursor        = NULL;
        wc.hbrBackground  = (HBRUSH)(COLOR_WINDOW + 1);
        wc.lpszMenuName   = NULL;
        wc.lpszClassName  = TEXT("Koala");

        if (!RegisterClass(&wc))
            return FALSE;
        }

    m_hWnd=CreateWindow(TEXT("Koala"), TEXT("Koala")
        , WS_OVERLAPPEDWINDOW, 35, 35, 350, 250
        , NULL, NULL, m_hInst, this);

    if (NULL==m_hWnd)
        return FALSE;

    g_hWnd=m_hWnd;

    /*
     * Create our class factory and register it for this application
     * using CoRegisterClassObject. We are able to service more than
     * one object at a time so we use REGCLS_MULTIPLEUSE.
     */
    m_pIClassFactory=new CKoalaClassFactory();

    if (NULL==m_pIClassFactory)
        return FALSE;

    //Since we hold on to this, we should AddRef it.
    m_pIClassFactory->AddRef();

    hr=CoRegisterClassObject(CLSID_Koala, m_pIClassFactory
        , CLSCTX_LOCAL_SERVER, REGCLS_MULTIPLEUSE, &m_dwRegCO);

    if (FAILED(hr))
        return FALSE;

    return TRUE;
    }





/*
 * CApp::RegisterServer
 *
 * Purpose:
 *  Creates registry enties for this server.
 */

void CApp::RegisterServer(void)
    {
    TCHAR       szID[128];
    TCHAR       szCLSID[128];
    TCHAR       szModule[512];

    //Create some bas key strings.
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

    GetModuleFileName(m_hInst, szModule
        , sizeof(szModule)/sizeof(TCHAR));

   #ifdef WIN32
    SetKeyAndValue(szCLSID, TEXT("LocalServer32"), szModule);
   #else
    SetKeyAndValue(szCLSID, TEXT("LocalServer"), szModule);
   #endif

	return;
    }



/*
 * CApp::RegisterServer
 *
 * Purpose:
 *  Removes registry entries for this server
 */


void CApp::UnregisterServer(void)
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
    wsprintf(szTemp, TEXT("%s\\%s"), szCLSID, TEXT("LocalServer32"));
   #else
    wsprintf(szTemp, "%s\\%s", szCLSID, "LocalServer");
   #endif
    RegDeleteKey(HKEY_CLASSES_ROOT, szTemp);

    RegDeleteKey(HKEY_CLASSES_ROOT, szCLSID);
    return;
    }



/*
 * CApp::SetKeyAndValue
 *
 * Purpose:
 *  Private helper function for RegisterServer that creates
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

BOOL CApp::SetKeyAndValue(LPTSTR pszKey, LPTSTR pszSubkey
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
    return 0;
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

    //Create the object telling us to notify us when it's gone.
    pObj=new CKoala(pUnkOuter, ObjectDestroyed);

    if (NULL==pObj)
        {
        //This starts shutdown if there are no other objects.
        g_cObj++;
        ObjectDestroyed();
        return hr;
        }

    if (pObj->Init())
        hr=pObj->QueryInterface(riid, ppvObj);

    g_cObj++;

    /*
     * Kill the object if initial creation or Init failed. If
     * the object failed, we handle the g_cObj increment above
     * in ObjectDestroyed.
     */
    if (FAILED(hr))
        {
        delete pObj;
        ObjectDestroyed();  //Handle shutdown cases.
        }

    return hr;
    }






/*
 * CKoalaClassFactory::LockServer
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

STDMETHODIMP CKoalaClassFactory::LockServer(BOOL fLock)
    {
    if (fLock)
        g_cLock++;
    else
        {
        g_cLock--;

        /*
         * Fake an object destruction:  this centralizes
         * all the shutdown code in the ObjectDestroyed
         * function, eliminating duplicate code here.
         */
        g_cObj++;
        ObjectDestroyed();
        }

    return NOERROR;
    }
