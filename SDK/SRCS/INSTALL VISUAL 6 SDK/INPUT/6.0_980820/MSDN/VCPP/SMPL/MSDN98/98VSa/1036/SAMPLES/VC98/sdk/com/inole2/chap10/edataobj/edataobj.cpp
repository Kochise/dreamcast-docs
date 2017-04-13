/*
 * EDATAOBJ.CPP
 * Data Object EXE Chapter 10
 *
 * Data Object implemented in an application.  This object supports
 * IUnknown and IDataObject interfaces.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#define INITGUIDS
#include "edataobj.h"


//Count number of objects and number of locks.
ULONG       g_cObj=0;
ULONG       g_cLock=0;

//Make window handle global so other code can cause a shutdown
HWND        g_hWnd=NULL;
HINSTANCE   g_hInst=NULL;



/*
 * WinMain
 *
 * Purpose:
 *  Main entry point of application.
 */

int PASCAL WinMain(HINSTANCE hInst, HINSTANCE hInstPrev
    , LPSTR pszCmdLine, int nCmdShow)
    {
    MSG     msg;
    PAPP    pApp;

    SETMESSAGEQUEUE(96);

    g_hInst=hInst;

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
 * DataObjectWndProc
 *
 * Purpose:
 *  Standard window class procedure.
 */

LRESULT APIENTRY DataObjectWndProc(HWND hWnd, UINT iMsg
    , WPARAM wParam, LPARAM lParam)
    {
    switch (iMsg)
        {
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
 *  Function for the DataObject object to call when it gets
 *  destroyed. We destroy the main window if the proper
 *  conditions are met for shutdown.
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
    UINT        i;

    m_hInst     =hInst;
    m_hInstPrev =hInstPrev;
    m_pszCmdLine=pszCmdLine;

    m_hWnd=NULL;

    for (i=0; i < DOSIZE_CSIZES; i++)
        {
        m_rgdwRegCO[i]=0;
        m_rgpIClassFactory[i]=NULL;
        }

    m_fInitialized=FALSE;
    return;
    }


CApp::~CApp(void)
    {
    UINT        i;

    //Revoke and destroy the class factories of all sizes
    for (i=0; i < DOSIZE_CSIZES; i++)
        {
        if (0L!=m_rgdwRegCO[i])
            CoRevokeClassObject(m_rgdwRegCO[i]);

        ReleaseInterface(m_rgpIClassFactory[i]);
        }

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
    WNDCLASS        wc;
    HRESULT         hr, hr2, hr3;
    UINT            i;

    CHECKVER_COM;

    //Check command line for -Embedding
    if (lstrcmpiA(m_pszCmdLine, "-Embedding"))
        return FALSE;

    if (FAILED(CoInitialize(NULL)))
        return FALSE;

    m_fInitialized=TRUE;

    if (!m_hInstPrev)
        {
        wc.style          = CS_HREDRAW | CS_VREDRAW;
        wc.lpfnWndProc    = DataObjectWndProc;
        wc.cbClsExtra     = 0;
        wc.cbWndExtra     = 0;
        wc.hInstance      = m_hInst;
        wc.hIcon          = NULL;
        wc.hCursor        = NULL;
        wc.hbrBackground  = (HBRUSH)(COLOR_WINDOW + 1);
        wc.lpszMenuName   = NULL;
        wc.lpszClassName  = TEXT("EXEDataObject");

        if (!RegisterClass(&wc))
            return FALSE;
        }

    m_hWnd=CreateWindow(TEXT("EXEDataObject")
        , TEXT("EXE DataObject"), WS_OVERLAPPEDWINDOW
        , 35, 35, 350, 250, NULL, NULL, m_hInst, NULL);

    if (NULL==m_hWnd)
        return FALSE;

    g_hWnd=m_hWnd;

    /*
     * This code supplies three different classes, one for each type
     * of data object that handles a different size of data. All the
     * class factories share the same implementation, but their
     * instantiations differ by the type passed in the constructor.
     * When the class factories create objects, they pass that size
     * to the CDataObject contstructor as well.
     */

    for (i=0; i < DOSIZE_CSIZES; i++)
        {
        m_rgpIClassFactory[i]=new CDataObjectClassFactory(i);

        if (NULL==m_rgpIClassFactory[i])
            return FALSE;

        m_rgpIClassFactory[i]->AddRef();
        }

    hr=CoRegisterClassObject(CLSID_DataObjectSmall
        , m_rgpIClassFactory[0], CLSCTX_LOCAL_SERVER
        , REGCLS_MULTIPLEUSE, &m_rgdwRegCO[0]);

    hr2=CoRegisterClassObject(CLSID_DataObjectMedium
        , m_rgpIClassFactory[1], CLSCTX_LOCAL_SERVER
        , REGCLS_MULTIPLEUSE, &m_rgdwRegCO[1]);

    hr3=CoRegisterClassObject(CLSID_DataObjectLarge
        , m_rgpIClassFactory[2], CLSCTX_LOCAL_SERVER
        , REGCLS_MULTIPLEUSE, &m_rgdwRegCO[2]);

    if (FAILED(hr) || FAILED(hr2) || FAILED(hr3))
        return FALSE;

    return TRUE;
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
 *  ppvObj          PPVOID in which to store the desired interface
 *                  pointer for the new object.
 *
 * Return Value:
 *  HRESULT         NOERROR if successful, otherwise contains
 *                  E_NOINTERFACE if we cannot support the
 *                  requested interface.
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

    g_cObj++;

    if (FAILED(hr))
        {
        delete pObj;
        ObjectDestroyed();  //Decrements g_cObj
        }

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
        {
        g_cLock--;

        g_cObj++;
        ObjectDestroyed();
        }

    return NOERROR;
    }
