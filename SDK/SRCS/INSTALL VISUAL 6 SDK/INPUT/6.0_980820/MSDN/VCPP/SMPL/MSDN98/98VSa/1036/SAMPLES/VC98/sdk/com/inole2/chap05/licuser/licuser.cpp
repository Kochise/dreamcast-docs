/*
 * LICUSER.CPP
 * Licensed Koala Object User/Client Chapter 5
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#define INITGUIDS
#include "licuser.h"


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

    pApp=new CApp(hInst, hInstPrev, nCmdShow);

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
 * LicensedUserWndProc
 *
 * Purpose:
 *  Window class procedure.  Standard callback.
 */

LRESULT APIENTRY LicensedUserWndProc(HWND hWnd, UINT iMsg
    , WPARAM wParam, LPARAM lParam)
    {
    PAPP            pApp;

    pApp=(PAPP)GetWindowLong(hWnd, LICUSERWL_STRUCTURE);

    switch (iMsg)
        {
        case WM_NCCREATE:
            pApp=(PAPP)(((LPCREATESTRUCT)lParam)->lpCreateParams);
            SetWindowLong(hWnd, LICUSERWL_STRUCTURE, (LONG)pApp);
            return (DefWindowProc(hWnd, iMsg, wParam, lParam));

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        case WM_COMMAND:
            switch (LOWORD(wParam))
                {
                case IDM_CFOBTAINCF:
                    pApp->ObtainClassFactory(FALSE);
                    break;

                case IDM_CFOBTAINCF2:
                    pApp->ObtainClassFactory(TRUE);
                    break;


                case IDM_CFRELEASE:
                    pApp->ReleaseClassFactory(TRUE);
                    break;


                case IDM_CFREQUESTLICKEY:
                    if (NULL==pApp->m_pIClassFac2)
                        {
                        pApp->Message(TEXT("Obtain IClassFactory2 first"));
                        break;
                        }

                    if (NULL!=pApp->m_bstrKey)
                        {
                        pApp->Message(TEXT("You already have a key"));
                        break;
                        }

                    if (SUCCEEDED(pApp->m_pIClassFac2->RequestLicKey(0
                        , &pApp->m_bstrKey)))
                        pApp->Message(TEXT("Got license key"));
                    else
                        pApp->Message(TEXT("Failed to get license key"));

                    break;


                case IDM_CLEARLICKEY:
                    if (NULL!=pApp->m_bstrKey)
                        {
                        SysFreeString(pApp->m_bstrKey);
                        pApp->m_bstrKey=NULL;
                        pApp->Message(TEXT("Cleared license key"));
                        }
                    else
                        pApp->Message(TEXT("No license key to clear"));

                    break;


                case IDM_CFEXIT:
                    PostMessage(hWnd, WM_CLOSE, 0, 0L);
                    break;


                case IDM_OBJECTCREATEINST:
                    pApp->CreateObject(FALSE);
                    break;


                case IDM_OBJECTCREATEINSTLIC:
                    pApp->CreateObject(TRUE);
                    break;
                }
            break;

        default:
            return (DefWindowProc(hWnd, iMsg, wParam, lParam));
        }

    return 0L;
    }





/*
 * CApp::CApp
 * CApp::~CApp
 *
 * Constructor Parameters: (from WinMain)
 *  hInst           HINSTANCE of the application.
 *  hInstPrev       HINSTANCE of a previous instance.
 *  nCmdShow        UINT specifying how to show the app window.
 *
 */

CApp::CApp(HINSTANCE hInst, HINSTANCE hInstPrev
    , UINT nCmdShow)
    {
    m_hInst=hInst;
    m_hInstPrev=hInstPrev;
    m_nCmdShow=nCmdShow;

    m_hWnd=NULL;
    m_fInitialized=FALSE;

    m_fLic=FALSE;
    m_pIClassFac=NULL;
    m_pIClassFac2=NULL;
    m_bstrKey=NULL;
    return;
    }


CApp::~CApp(void)
    {
    ReleaseClassFactory(FALSE);

    if (NULL!=m_bstrKey)
        SysFreeString(m_bstrKey);

    if (IsWindow(m_hWnd))
        DestroyWindow(m_hWnd);

    if (m_fInitialized)
        CoUninitialize();

    return;
    }





/*
 * CApp::ObtainClassFactory
 *
 * Purpose:
 *  Calls CoGetClassObject to retrieve either IClassFactory or
 *  IClassFactory2, setting the appropriate CApp member variables
 *  in the process and calling that factory's LockServer.  Any
 *  currently held factory is Released as well.
 *
 * Parameters:
 *  fLic            BOOL indicating if we're to get IClassFactory
 *                  (FALSE) or IClassFactory2 (TRUE)
 */

void CApp::ObtainClassFactory(BOOL fLic)
    {
    IClassFactory **ppCF;
    IID             iid;
    UINT            uIDCheck;
    HRESULT         hr;

    ReleaseClassFactory(FALSE);

    if (fLic)
        {
        ppCF=(IClassFactory **)&m_pIClassFac2;
        iid=IID_IClassFactory2;
        uIDCheck=IDM_CFOBTAINCF2;
        }
    else
        {
        ppCF=&m_pIClassFac;
        iid=IID_IClassFactory;
        uIDCheck=IDM_CFOBTAINCF;
        }

    hr=CoGetClassObject(CLSID_Koala, CLSCTX_INPROC_SERVER, NULL
        , iid, (PPVOID)ppCF);

    if (FAILED(hr))
        {
        Message(TEXT("Failed to obtain the class factory"));

        //This unloads any DLL that might have loaded
        CoFreeUnusedLibraries();
        return;
        }

    m_fLic=fLic;
    (*ppCF)->LockServer(TRUE);
    Message(TEXT("Class factory obtained successfully"));

    CheckMenuItem(GetMenu(m_hWnd), uIDCheck, MF_CHECKED);

    //Enable the object menu.
    EnableMenuItem(GetMenu(m_hWnd), 1, MF_BYPOSITION | MF_ENABLED);
    DrawMenuBar(m_hWnd);
    return;
    }



/*
 * CApp::ReleaseClassFactory
 *
 * Purpose:
 *  Releases any held class factory and unlocks the server.
 *
 * Parameters:
 *  fMsg            BOOL indicating whether or not to display
 *                  any messages.
 */

void CApp::ReleaseClassFactory(BOOL fMsg)
    {
    IClassFactory **ppCF;

    ppCF=m_fLic ? (IClassFactory **)&m_pIClassFac2 : &m_pIClassFac;

    if (NULL==*ppCF)
        {
        if (fMsg)
            Message(TEXT("No class factory to Release"));

        return;
        }

    (*ppCF)->LockServer(FALSE);
    (*ppCF)->Release();
    *ppCF=NULL;

    /*
     * This will unload the DLL, allowing you to reload it so
     * it will reinitialize the flag it uses to know if the
     * LIC file was found.  So before obtaining another class
     * factory you can remove the LIC file and see the results
     * without closing this app down.
     */
    CoFreeUnusedLibraries();

    CheckMenuItem(GetMenu(m_hWnd), IDM_CFOBTAINCF,  MF_UNCHECKED);
    CheckMenuItem(GetMenu(m_hWnd), IDM_CFOBTAINCF2, MF_UNCHECKED);

    EnableMenuItem(GetMenu(m_hWnd), 1, MF_BYPOSITION | MF_DISABLED
        | MF_GRAYED);
    DrawMenuBar(m_hWnd);

    if (fMsg)
        Message(TEXT("Class factory released"));

    return;
    }




/*
 * CApp::CreateObject
 *
 * Purpose:
 *  Creates an object with whatever class factory has been obtained,
 *  the releases it right away.  The purpose here is to see whether
 *  or not the object can be created at all.
 *
 * Parameters:
 *  fLic            BOOL indicating if we're to use IClassFactory
 *                  (FALSE) or IClassFactory2 (TRUE)
 */

void CApp::CreateObject(BOOL fLic)
    {
    HRESULT         hr;
    IUnknown       *pObj;

    if ((fLic && NULL==m_pIClassFac2)
        || (!fLic && (NULL==m_pIClassFac && NULL==m_pIClassFac2)))
        {
        Message(TEXT("There is no class factory"));
        return;
        }

    if (fLic && NULL==m_bstrKey)
        {
        Message(TEXT("Get a license key first"));
        return;
        }

    if (fLic)
        {
        hr=m_pIClassFac2->CreateInstanceLic(NULL, NULL, IID_IUnknown
            , m_bstrKey, (PPVOID)&pObj);
        }
    else
        {
        if (NULL!=m_pIClassFac2)
            {
            hr=m_pIClassFac2->CreateInstance(NULL, IID_IUnknown
                , (PPVOID)&pObj);
            }
        else
            {
            hr=m_pIClassFac->CreateInstance(NULL, IID_IUnknown
                , (PPVOID)&pObj);
            }
        }

    if (SUCCEEDED(hr))
        {
        Message(TEXT("Creation successful"));
        pObj->Release();
        return;
        }

    //Tell the user if creation failed for license reasons
    if (CLASS_E_NOTLICENSED==GetScode(hr))
        {
        if (fLic)
            Message(TEXT("Creation failed: license key doesn't match"));
        else
            Message(TEXT("Creation failed: no license"));
        }
    else
        Message(TEXT("Creation licensed, but failed anyway"));

    return;
    }





/*
 * CApp::Init
 *
 * Purpose:
 *  Initializes an CApp object by registering window classes,
 *  creating the main window, and doing anything else prone to
 *  failure such as calling CoInitialize.  If this function fails
 *  the caller should insure that the destructor is called.
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

    CHECKVER_COM;

    if (FAILED(CoInitialize(NULL)))
        return FALSE;

    m_fInitialized=TRUE;

    if (!m_hInstPrev)
        {
        wc.style          = CS_HREDRAW | CS_VREDRAW;
        wc.lpfnWndProc    = LicensedUserWndProc;
        wc.cbClsExtra     = 0;
        wc.cbWndExtra     = CBWNDEXTRA;
        wc.hInstance      = m_hInst;
        wc.hIcon          = LoadIcon(m_hInst, TEXT("Icon"));
        wc.hCursor        = LoadCursor(NULL, IDC_ARROW);
        wc.hbrBackground  = (HBRUSH)(COLOR_WINDOW + 1);
        wc.lpszMenuName   = MAKEINTRESOURCE(IDR_MENU);
        wc.lpszClassName  = TEXT("LICUSER");

        if (!RegisterClass(&wc))
            return FALSE;
        }

    m_hWnd=CreateWindow(TEXT("LICUSER")
        , TEXT("Licensed Object User/Client"), WS_OVERLAPPEDWINDOW
        , 35, 35, 350, 250, NULL, NULL, m_hInst, this);

    if (NULL==m_hWnd)
        return FALSE;

    //Initially disable the object menu
    EnableMenuItem(GetMenu(m_hWnd), 1, MF_BYPOSITION | MF_DISABLED
        | MF_GRAYED);

    ShowWindow(m_hWnd, m_nCmdShow);
    UpdateWindow(m_hWnd);

    return TRUE;
    }



/*
 * CApp::Message
 *
 * Purpose:
 *  Displays a message in the client area of the window.  This is
 *  just to centralize the call to simpify other code.
 *
 * Parameters:
 *  psz             LPTSTR to the string to display.
 *
 * Return Value:
 *  None
 */

void inline CApp::Message(LPTSTR psz)
    {
    HDC     hDC;
    RECT    rc;

    hDC=GetDC(m_hWnd);
    GetClientRect(m_hWnd, &rc);

    SetBkColor(hDC, GetSysColor(COLOR_WINDOW));
    SetTextColor(hDC, GetSysColor(COLOR_WINDOWTEXT));

    /*
     * We'll just be sloppy and clear the whole window as
     * well as write the string with one ExtTextOut call.
     * No word wrapping here...
     */

    ExtTextOut(hDC, 0, 0, ETO_OPAQUE, &rc, psz, lstrlen(psz), NULL);
    ReleaseDC(m_hWnd, hDC);
    return;
    }
