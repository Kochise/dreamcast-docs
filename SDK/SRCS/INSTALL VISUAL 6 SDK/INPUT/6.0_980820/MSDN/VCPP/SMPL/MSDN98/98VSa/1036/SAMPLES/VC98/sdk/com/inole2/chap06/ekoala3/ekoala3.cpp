/*
 * EKOALA3.CPP
 * Koala Object EXE Server Chapter 6
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
#include "ekoala3.h"


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

        //CHAPTER6MOD
        case WM_COMMAND:
            switch (LOWORD(wParam))
                {
                case IDM_CALLBLOCK:
                    pApp->m_fBlock=!pApp->m_fBlock;
                    CheckMenuItem(GetMenu(hWnd), IDM_CALLBLOCK
                        , pApp->m_fBlock ? MF_CHECKED : MF_UNCHECKED);
                    break;

                case IDM_CALLDELAY:
                    pApp->m_fDelay=!pApp->m_fDelay;
                    CheckMenuItem(GetMenu(hWnd), IDM_CALLDELAY
                        , pApp->m_fDelay ? MF_CHECKED : MF_UNCHECKED);
                    break;
                }
            break;


        case WM_CLOSE:
            //Don't close with object's active
            if (0==g_cObj && 0==g_cLock)
                return (DefWindowProc(hWnd, iMsg, wParam, lParam));

            break;
        //End CHAPTER6MOD

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

    //CHAPTER6MOD
    m_pMsgFilter=NULL;
    m_fBlock=FALSE;
    m_fDelay=FALSE;
    //End CHAPTER6MOD
    return;
    }


CApp::~CApp(void)
    {
    //CHAPTER6MOD
    if (NULL!=m_pMsgFilter)
        {
        CoRegisterMessageFilter(NULL, NULL);
        ReleaseInterface(m_pMsgFilter);
        }
    //End CHAPTER6MOD

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
        //CHAPTER6MOD
        wc.lpszMenuName   = MAKEINTRESOURCE(IDR_MENU);
        //End CHAPTER6MOD
        wc.lpszClassName  = TEXT("Koala");

        if (!RegisterClass(&wc))
            return FALSE;
        }

    //CHAPTER6MOD
    m_hWnd=CreateWindow(TEXT("Koala"), TEXT("Koala Object")
        , WS_OVERLAPPEDWINDOW, 400, 35, 350, 250
        , NULL, NULL, m_hInst, this);

    if (NULL==m_hWnd)
        return FALSE;

    ShowWindow(m_hWnd, SW_SHOW);
    UpdateWindow(m_hWnd);
    //End CHAPTER6MOD

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

    //CHAPTER6MOD
    /*
     * Call CoLockObjectExternal to lock and unlock to show
     * its strong lock effect through IExternalConnection.
     */
    CoLockObjectExternal(m_pIClassFactory, TRUE,  FALSE);
    CoLockObjectExternal(m_pIClassFactory, FALSE, FALSE);

    //Create and register the message filter
    m_pMsgFilter=new CMessageFilter(this);

    if (NULL!=m_pMsgFilter)
        {
        m_pMsgFilter->AddRef();

        if (FAILED(CoRegisterMessageFilter(m_pMsgFilter, NULL)))
            ReleaseInterface(m_pMsgFilter);
        }
    //End CHAPTER6MOD

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
    //CHAPTER6MOD
    m_pImpIExtConn=new CImpIExternalConnection(this, this);
    //End CHAPTER6MOD
    return;
    }

CKoalaClassFactory::~CKoalaClassFactory(void)
    {
    //CHAPTER6MOD
    DeleteInterfaceImp(m_pImpIExtConn);
    //End CHAPTER6MOD
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

    //CHAPTER6MOD
    if (IID_IExternalConnection==riid && NULL!=m_pImpIExtConn)
        *ppv=m_pImpIExtConn;
    //End CHAPTER6MOD

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




//CHAPTER6MOD
//Class factory implementation of IExternalConnection

/*
 * CImpIExternalConnection::CImpIExternalConnection
 * CImpIExternalConnection::~CImpIExternalConnection
 *
 * Parameters (Constructor):
 *  pObj            PCKoalaClassFactory of the object we're in.
 *  pUnkOuter       LPUNKNOWN to which we delegate.
 */

CImpIExternalConnection::CImpIExternalConnection
    (PCKoalaClassFactory pObj, LPUNKNOWN pUnkOuter)
    {
    m_cRef=0;
    m_pObj=pObj;
    m_pUnkOuter=pUnkOuter;

    m_cStrong=0;
    m_cWeak=0;
    return;
    }

CImpIExternalConnection::~CImpIExternalConnection(void)
    {
    return;
    }



/*
 * CImpIExternalConnection::QueryInterface
 * CImpIExternalConnection::AddRef
 * CImpIExternalConnection::Release
 *
 * Purpose:
 *  Delegating IUnknown members for CImpIExternalConnection.
 */

STDMETHODIMP CImpIExternalConnection::QueryInterface(REFIID riid
    , LPVOID *ppv)
    {
    return m_pUnkOuter->QueryInterface(riid, ppv);
    }

STDMETHODIMP_(ULONG) CImpIExternalConnection::AddRef(void)
    {
    ++m_cRef;
    return m_pUnkOuter->AddRef();
    }

STDMETHODIMP_(ULONG) CImpIExternalConnection::Release(void)
    {
    --m_cRef;
    return m_pUnkOuter->Release();
    }





/*
 * CImpIExternalConnection::AddConnection
 *
 * Purpose:
 *  Informs the object that a strong connection has been made to it.
 *
 * Parameters:
 *  dwConn          DWORD identifying the type of connection, taken
 *                  from the EXTCONN enumeration.
 *  dwReserved      DWORD reserved.  This is used inside OLE and
 *                  should not be validated.
 *
 * Return Value:
 *  DWORD           The number of connection counts on the
 *                  object, used for debugging purposes only.
 */

STDMETHODIMP_(DWORD) CImpIExternalConnection::AddConnection
    (DWORD dwConn, DWORD dwReserved)
    {
    DWORD       dwRet;
    TCHAR       szTemp[80];

    if (EXTCONN_STRONG & dwConn)
        {
        dwRet=++m_cStrong;
        wsprintf(szTemp
            , TEXT("AddConnection cStrong=%lu"), m_cStrong);
        }

   #ifdef WIN32
    if (EXTCONN_WEAK & dwConn)
        {
        dwRet=++m_cWeak;
        wsprintf(szTemp
            , TEXT("ReleaseConnection cWeak=%lu"), m_cWeak);
        }
   #endif

   #ifndef WIN32
    ODS(szTemp);
   #else
    MessageBox(NULL, szTemp
        , TEXT("EKoala3: CKoalaClassFactory::IExternalConnection")
        , MB_OK);
   #endif

    return dwRet;
    }



/*
 * CImpIExternalConnection::ReleaseConnection
 *
 * Purpose:
 *  Informs an object that a connection has been taken away from
 *  it in which case the object may need to shut down.
 *
 * Parameters:
 *  dwConn              DWORD identifying the type of connection,
 *                      taken from the EXTCONN enumeration.
 *  dwReserved          DWORD reserved.  This is used inside OLE and
 *                      should not be validated.
 *  dwRerved            DWORD reserved
 *  fLastReleaseCloses  BOOL indicating if the last call to this
 *                      function should close the object.
 *
 * Return Value:
 *  DWORD           The number of remaining connection counts on
 *                  the object, used for debugging purposes only.
 */

STDMETHODIMP_(DWORD) CImpIExternalConnection::ReleaseConnection
    (DWORD dwConn, DWORD dwReserved, BOOL fLastReleaseCloses)
    {
    DWORD       dwRet;
    TCHAR       szTemp[80];

    if (EXTCONN_STRONG & dwConn)
        {
        /*
         * Note:  We don't need to close ourselves when the last
         * strong lock is removed; we're just implementing this
         * interface for demonstration.
         */

        dwRet=--m_cStrong;
        wsprintf(szTemp
            , TEXT("ReleaseConnection cStrong=%lu"), m_cStrong);
        }

   #ifdef WIN32
    if (EXTCONN_WEAK & dwConn)
        {
        dwRet=--m_cWeak;
        wsprintf(szTemp
            , TEXT("ReleaseConnection cWeak=%lu"), m_cWeak);
        }
   #endif

   #ifndef WIN32
    ODS(szTemp);
   #else
    MessageBox(NULL, szTemp
        , TEXT("EKoala3: CKoalaClassFactory::IExternalConnection")
        , MB_OK);
   #endif

    return dwRet;
    }

//End CHAPTER6MOD
