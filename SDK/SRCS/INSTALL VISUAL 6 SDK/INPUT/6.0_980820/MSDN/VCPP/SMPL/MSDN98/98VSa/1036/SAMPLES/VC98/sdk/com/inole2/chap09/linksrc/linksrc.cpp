/*
 * LINKSRC.CPP
 * Link Source Server Chapter 9
 *
 * Server of various objects that can be named with monikers.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#define INITGUIDS
#include "linksrc.h"


//Count number of objects and number of locks.
ULONG       g_cObj=0;
ULONG       g_cLock=0;
BOOL        g_fUser=FALSE;

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

LRESULT APIENTRY LinkSrcWndProc(HWND hWnd, UINT iMsg
    , WPARAM wParam, LPARAM lParam)
    {
    PAPP        pApp;

    pApp=(PAPP)GetWindowLong(hWnd, LINKSRCWL_STRUCTURE);

    switch (iMsg)
        {
        case WM_NCCREATE:
            pApp=(PAPP)(((LPCREATESTRUCT)lParam)->lpCreateParams);
            SetWindowLong(hWnd, LINKSRCWL_STRUCTURE, (LONG)pApp);
            return (DefWindowProc(hWnd, iMsg, wParam, lParam));

        case WM_COMMAND:
            switch (LOWORD(wParam))
                {
                case IDM_FILECREATEGOOP:
                    pApp->CreateSampleFile(TEXT("goop.lks"));
                    break;

                case IDM_FILEEXIT:
                    PostMessage(hWnd, WM_CLOSE, 0, 0L);
                    break;

                default:
                    break;
                }

            break;

        case WM_CLOSE:
            //Don't close with object's active
            if (0==g_cObj && 0==g_cLock)
                return (DefWindowProc(hWnd, iMsg, wParam, lParam));

            break;

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
 *  Function for the LinkSrc object to call when it gets destroyed.
 *  We destroy the main window if the proper conditions are met
 *  for shutdown.
 */

void ObjectDestroyed(void)
    {
    g_cObj--;

    /*
     * No more objects and no locks, and user is not in
     * control (CApp::m_fEmbedding), then shut down.
     */
    if (0L==g_cObj && 0L==g_cLock && IsWindow(g_hWnd)
        && !g_fUser)
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

    /*
     * We can run stand-alone or at OLE's request, but we
     * remain hidden if run from OLE.
     */
    m_fEmbedding=TRUE;

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

    CHECKVER_COM;

    //Check if we're run stand-alone
    if (lstrcmpiA(m_pszCmdLine, "-Embedding")
        && lstrcmpiA(m_pszCmdLine, "/Embedding"))
        {
        m_fEmbedding=FALSE;
        g_fUser=TRUE;
        }

    //Call CoInitialize so we can call other Co* functions
    if (FAILED(CoInitialize(NULL)))
        return FALSE;

    m_fInitialized=TRUE;

    if (!m_hInstPrev)
        {
        wc.style          = CS_HREDRAW | CS_VREDRAW;
        wc.lpfnWndProc    = LinkSrcWndProc;
        wc.cbClsExtra     = 0;
        wc.cbWndExtra     = CBWNDEXTRA;
        wc.hInstance      = m_hInst;
        wc.hIcon          = LoadIcon(m_hInst, TEXT("Icon"));
        wc.hCursor        = LoadCursor(NULL, IDC_ARROW);
        wc.hbrBackground  = (HBRUSH)(COLOR_WINDOW + 1);
        wc.lpszMenuName   = MAKEINTRESOURCE(IDR_MENU);
        wc.lpszClassName  = TEXT("LinkSrc");

        if (!RegisterClass(&wc))
            return FALSE;
        }

    m_hWnd=CreateWindow(TEXT("LinkSrc"), TEXT("Link Source")
        , WS_OVERLAPPEDWINDOW, 450, 35, 350, 250
        , NULL, NULL, m_hInst, this);

    if (NULL==m_hWnd)
        return FALSE;

    //Don't show the window outside of embedding
    if (!m_fEmbedding)
        {
        ShowWindow(m_hWnd, SW_SHOW);
        UpdateWindow(m_hWnd);
        }

    g_hWnd=m_hWnd;

    /*
     * We only server file objects through a CLSID.  Other
     * items are referenced through the File object.
     */
    m_pIClassFactory=new CFileObjectFactory();

    if (NULL==m_pIClassFactory)
        return FALSE;

    //Since we hold on to this, we should AddRef it.
    m_pIClassFactory->AddRef();

    hr=CoRegisterClassObject(CLSID_LinkedFile, m_pIClassFactory
        , CLSCTX_LOCAL_SERVER, REGCLS_MULTIPLEUSE, &m_dwRegCO);

    if (FAILED(hr))
        return FALSE;

    return TRUE;
    }



/*
 * CApp::CreateSampleFile
 *
 * Purpose:
 *  Creates a file with the structure we can use in binding
 *  monikers.
 *
 * Parameters:
 *  pszFile         LPTSTR to the file name to create.
 *
 * Return Value:
 *  None
 */

void CApp::CreateSampleFile(LPTSTR pszFile)
    {
    HRESULT     hr;
    IStorage   *pIStorage;

    hr=StgCreateDocfile(pszFile, STGM_DIRECT | STGM_READWRITE
        | STGM_CREATE | STGM_SHARE_EXCLUSIVE, 0, &pIStorage);

    if (SUCCEEDED(hr))
        {
        UINT        i;
        TCHAR       szTemp[40];
        TCHAR       szDesc[256];

        WriteDescription(pIStorage
            , TEXT("This is a sample compound file from LinkSource that demonstrates binding to a file moniker."));

        for (i=0; i < 4; i++)
            {
            wsprintf(szTemp, TEXT("Object %d"), i);
            wsprintf(szDesc
                , TEXT("This is the first-level item named %s in the file.")
                , szTemp);

            hr=CreateStore(pIStorage, szTemp, szDesc, 5);

            if (FAILED(hr))
                break;
            }
        }

    pIStorage->SetClass(CLSID_LinkedFile);
    pIStorage->Release();

    if (FAILED(hr))
        {
        MessageBox(m_hWnd, TEXT("File creation failed.")
            , TEXT("Link Source"), MB_OK);
        }
    else
        {
        MessageBox(m_hWnd, TEXT("File created successfully.")
            , TEXT("Link Source"), MB_OK);
        }

    return;
    }



/*
 * CApp::CreateStore
 *
 * Purpose:
 *  Creates a sub-storage below pIStorage with the given name and
 *  writes a description stream using the stringtable string idsDesc.
 *
 * Parameters:
 *  pIStorage       IStorage * in which to create the storage.
 *  pszName         LPTSTR naming the storage to create.
 *  pszDesc         LPTSTR holding the description.
 *  cSubs           UINT number of sub-storages to create in this one
 *
 * Return Value:
 *  HRESULT         Result of the operation.
 */

HRESULT CApp::CreateStore(IStorage *pIStorage, LPTSTR pszName
    , LPTSTR pszDesc, UINT cSubs)
    {
    HRESULT     hr;
    IStorage   *pSub;
    TCHAR       szTemp[40];
    TCHAR       szDesc[256];
    UINT        i;

   #ifdef WIN32ANSI
    OLECHAR     szUNI[40];
    MultiByteToWideChar(CP_ACP, 0, pszName, -1, szUNI, 40);

    hr=pIStorage->CreateStorage(szUNI, STGM_DIRECT
        | STGM_READWRITE | STGM_SHARE_EXCLUSIVE, 0, 0, &pSub);
   #else
    hr=pIStorage->CreateStorage(pszName, STGM_DIRECT
        | STGM_READWRITE | STGM_SHARE_EXCLUSIVE, 0, 0, &pSub);
   #endif

    if (FAILED(hr))
        return hr;

    hr=WriteDescription(pSub, pszDesc);

    if (cSubs > 255)
        cSubs=255;

    /*
     * If cSubs is zero we'll pass to the return statement
     * which allows recursion in the loop below for 2nd level storages.
     */
    for (i=0; i < cSubs; i++)
        {
        wsprintf(szTemp, TEXT("Sub-Object %d"), i);
        wsprintf(szDesc
            , TEXT("This is the second-level item named %s inside the item named %s in the file.")
            , szTemp, pszName);

        hr=CreateStore(pSub, szTemp, szDesc, 0);

        if (FAILED(hr))
            break;
        }

    pSub->Release();
    return hr;
    }




/*
 * CApp::WriteDescription
 *
 * Purpose:
 *  Creates a stream with the name SZDESCRIPTION in the given
 *  storage and writes into that stream the string identified
 *  by idsDesc that exists in the stringtable.
 *
 * Parameters:
 *  pIStorage       IStorage * in which to create the stream.
 *  pszDesc         LPTSTR describing the storage.
 *
 * Return Value:
 *  HRESULT         NOERROR or an error code.
 */

HRESULT CApp::WriteDescription(IStorage *pIStorage, LPTSTR pszDesc)
    {
    HRESULT     hr;
    IStream    *pIStream;

    hr=pIStorage->CreateStream(SZDESCRIPTION, STGM_DIRECT
        | STGM_READWRITE | STGM_SHARE_EXCLUSIVE, 0, 0, &pIStream);

    if (FAILED(hr))
        return hr;

    hr=pIStream->Write(pszDesc
        , (lstrlen(pszDesc)+1)*sizeof(TCHAR), NULL);
    pIStream->Release();
    return hr;
    }





/*
 * CFileObjectFactory::CFileObjectFactory
 * CFileObjectFactory::~CFileObjectFactory
 * CFileObjectFactory::QueryInterface
 * CFileObjectFactory::AddRef
 * CFileObjectFactory::Release
 *
 * Basic class factory members
 */

CFileObjectFactory::CFileObjectFactory(void)
    {
    m_cRef=0L;
    return;
    }

CFileObjectFactory::~CFileObjectFactory(void)
    {
    return;
    }

STDMETHODIMP CFileObjectFactory::QueryInterface(REFIID riid
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


STDMETHODIMP_(ULONG) CFileObjectFactory::AddRef(void)
    {
    return ++m_cRef;
    }


STDMETHODIMP_(ULONG) CFileObjectFactory::Release(void)
    {
    if (0L!=--m_cRef)
        return m_cRef;

    delete this;
    return 0;
    }






/*
 * CFileObjectFactory::CreateInstance
 *
 * Purpose:
 *  Instantiates a LinkSrc object returning an interface pointer.
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

STDMETHODIMP CFileObjectFactory::CreateInstance(LPUNKNOWN pUnkOuter
    , REFIID riid, PPVOID ppvObj)
    {
    PCFileObject        pObj;
    HRESULT             hr;

    *ppvObj=NULL;
    hr=ResultFromScode(E_OUTOFMEMORY);

    if (NULL!=pUnkOuter && IID_IUnknown!=riid)
        return ResultFromScode(CLASS_E_NOAGGREGATION);

    pObj=new CFileObject(pUnkOuter, ObjectDestroyed);

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

    if (FAILED(hr))
        {
        delete pObj;
        ObjectDestroyed();  //Handle shutdown cases.
        }

    return hr;
    }






/*
 * CFileObjectFactory::LockServer
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

STDMETHODIMP CFileObjectFactory::LockServer(BOOL fLock)
    {
    if (fLock)
        g_cLock++;
    else
        {
        g_cLock--;
        g_cObj++;
        ObjectDestroyed();
        }

    return NOERROR;
    }
