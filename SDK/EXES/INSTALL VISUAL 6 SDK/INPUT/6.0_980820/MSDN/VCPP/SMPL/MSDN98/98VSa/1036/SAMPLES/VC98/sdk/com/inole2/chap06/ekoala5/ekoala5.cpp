/*
 * EKOALA5.CPP
 * Koala Object EXE Server with Custom Marshaling Chapter 6
 *
 * Example object with custom marshaling
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#define INITGUIDS
#include "ekoala5.h"


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

        //Window created for each object.
        wc.lpfnWndProc    = ObjectWndProc;
        wc.cbWndExtra     = CBOBJECTWNDEXTRA;
        wc.lpszClassName  = TEXT("KoalaObject");

        if (!RegisterClass(&wc))
            return FALSE;
        }

    //Create main window
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
    m_pIClassFactory=new CKoalaClassFactory(m_hInst, m_hWnd);

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
 * CKoalaClassFactory::CKoalaClassFactory
 * CKoalaClassFactory::~CKoalaClassFactory
 *
 * Constructor Parameters:
 *  hInst           HINSTANCE to pass on to Koalas.
 *  hWnd            HWND to pass on to Koalas.
 */

CKoalaClassFactory::CKoalaClassFactory(HINSTANCE hInst, HWND hWnd)
    {
    m_cRef=0L;
    m_hInst=hInst;
    m_hWnd=hWnd;
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
    if (NULL!=pUnkOuter)
        return ResultFromScode(CLASS_E_NOAGGREGATION);

    //Create the object telling us to notify us when it's gone.
    pObj=new CKoala(ObjectDestroyed);

    if (NULL==pObj)
        {
        //This starts shutdown if there are no other objects.
        g_cObj++;
        ObjectDestroyed();
        return hr;
        }

    if (pObj->Init(m_hInst, m_hWnd))
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
