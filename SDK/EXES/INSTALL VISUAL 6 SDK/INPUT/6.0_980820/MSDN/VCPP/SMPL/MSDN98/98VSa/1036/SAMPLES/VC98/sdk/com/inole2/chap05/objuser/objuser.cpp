/*
 * OBJUSER.CPP
 * Koala Object User/Client Chapter 5
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#define INITGUIDS
#include "objuser.h"


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
 * ObjectUserWndProc
 *
 * Purpose:
 *  Window class procedure.  Standard callback.
 */

LRESULT APIENTRY ObjectUserWndProc(HWND hWnd, UINT iMsg
    , WPARAM wParam, LPARAM lParam)
    {
    HRESULT         hr;
    PAPP            pApp;
    LPCLASSFACTORY  pIClassFactory;
    DWORD           dwClsCtx;
    ULONG           cRef;
    TCHAR           szTemp[80];

    pApp=(PAPP)GetWindowLong(hWnd, OBJUSERWL_STRUCTURE);

    switch (iMsg)
        {
        case WM_NCCREATE:
            pApp=(PAPP)(((LPCREATESTRUCT)lParam)->lpCreateParams);
            SetWindowLong(hWnd, OBJUSERWL_STRUCTURE, (LONG)pApp);
            return (DefWindowProc(hWnd, iMsg, wParam, lParam));

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        case WM_COMMAND:
            switch (LOWORD(wParam))
                {
                case IDM_OBJECTUSEDLL:
                    pApp->m_fEXE=FALSE;
                    CheckMenuItem(GetMenu(hWnd), IDM_OBJECTUSEDLL
                        , MF_CHECKED);
                    CheckMenuItem(GetMenu(hWnd), IDM_OBJECTUSEEXE
                        , MF_UNCHECKED);
                    break;


                case IDM_OBJECTUSEEXE:
                    pApp->m_fEXE=TRUE;
                    CheckMenuItem(GetMenu(hWnd), IDM_OBJECTUSEDLL
                        , MF_UNCHECKED);
                    CheckMenuItem(GetMenu(hWnd), IDM_OBJECTUSEEXE
                        , MF_CHECKED);
                    break;


                case IDM_OBJECTCREATECOGCO:
                    if (NULL!=pApp->m_pIUnknown)
                        {
                        while (pApp->m_cRefOurs--)
                            ReleaseInterface(pApp->m_pIUnknown);

                        CoFreeUnusedLibraries();
                        }

                    dwClsCtx=(pApp->m_fEXE) ? CLSCTX_LOCAL_SERVER
                        : CLSCTX_INPROC_SERVER;

                    hr=CoGetClassObject(CLSID_Koala, dwClsCtx, NULL
                        , IID_IClassFactory, (PPVOID)&pIClassFactory);

                    if (SUCCEEDED(hr))
                        {
                        hr=pIClassFactory->CreateInstance(NULL
                            , IID_IUnknown
                            , (PPVOID)&pApp->m_pIUnknown);

                        //Release the class factory when done.
                        pIClassFactory->Release();

                        if (SUCCEEDED(hr))
                            {
                            pApp->Message(TEXT("Creation succeeded"));
                            pApp->m_cRefOurs=1;
                            }
                        else
                            pApp->Message(TEXT("Creation failed"));
                        }
                    else
                        pApp->Message(TEXT("CoGetClassObject failed"));

                    break;


                case IDM_OBJECTCREATECOCI:
                    if (NULL!=pApp->m_pIUnknown)
                        {
                        while (pApp->m_cRefOurs--)
                            ReleaseInterface(pApp->m_pIUnknown);

                        CoFreeUnusedLibraries();
                        }

                    //Simpler creation:  use CoCreateInstance
                    dwClsCtx=(pApp->m_fEXE) ? CLSCTX_LOCAL_SERVER
                        : CLSCTX_INPROC_SERVER;

                    hr=CoCreateInstance(CLSID_Koala, NULL, dwClsCtx
                        , IID_IUnknown, (PPVOID)&pApp->m_pIUnknown);

                    if (SUCCEEDED(hr))
                        {
                        pApp->Message(TEXT("Creation succeeded"));
                        pApp->m_cRefOurs=1;
                        }
                    else
                        pApp->Message(TEXT("Creation failed"));

                    break;


                case IDM_OBJECTADDREF:
                    if (NULL==pApp->m_pIUnknown)
                        {
                        pApp->Message(TEXT("There is no object"));
                        break;
                        }


                    /*
                     * We maintain our own usage count so we
                     * know later when to NULL our pointer.
                     */
                    cRef=pApp->m_pIUnknown->AddRef();
                    pApp->m_cRefOurs++;

                    wsprintf(szTemp, TEXT("Object Count=%lu, Usage=%lu")
                        , cRef, pApp->m_cRefOurs);

                    pApp->Message(szTemp);
                    break;


                case IDM_OBJECTRELEASE:
                    if (NULL==pApp->m_pIUnknown)
                        {
                        pApp->Message(TEXT("There is no object"));
                        break;
                        }

                    cRef=pApp->m_pIUnknown->Release();

                    /*
                     * Our private usage count tells us when we
                     * believe we're done with the object.  We can't
                     * use the ref count from Release to tell us
                     * if the object is really destroyed or not--so
                     * in this case we maintain our own count.
                     */
                    if (0==--pApp->m_cRefOurs)
                        {
                        pApp->m_pIUnknown=NULL;
                        CoFreeUnusedLibraries();
                        }

                    wsprintf(szTemp, TEXT("Object Count=%lu, Usage=%lu")
                        , cRef, pApp->m_cRefOurs);
                    pApp->Message(szTemp);
                    break;


                case IDM_OBJECTEXIT:
                    PostMessage(hWnd, WM_CLOSE, 0, 0L);
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
    m_hInst       =hInst;
    m_hInstPrev   =hInstPrev;
    m_nCmdShow    =nCmdShow;

    m_hWnd        =NULL;
    m_fEXE        =FALSE;

    m_cRefOurs    =0L;
    m_pIUnknown   =NULL;
    m_fInitialized=FALSE;
    return;
    }


CApp::~CApp(void)
    {
    while (m_cRefOurs-- > 0)
        m_pIUnknown->Release();

    m_pIUnknown=NULL;

    if (IsWindow(m_hWnd))
        DestroyWindow(m_hWnd);

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
        wc.lpfnWndProc    = ObjectUserWndProc;
        wc.cbClsExtra     = 0;
        wc.cbWndExtra     = CBWNDEXTRA;
        wc.hInstance      = m_hInst;
        wc.hIcon          = LoadIcon(m_hInst, TEXT("Icon"));
        wc.hCursor        = LoadCursor(NULL, IDC_ARROW);
        wc.hbrBackground  = (HBRUSH)(COLOR_WINDOW + 1);
        wc.lpszMenuName   = MAKEINTRESOURCE(IDR_MENU);
        wc.lpszClassName  = TEXT("OBJUSER");

        if (!RegisterClass(&wc))
            return FALSE;
        }

    m_hWnd=CreateWindow(TEXT("OBJUSER")
        , TEXT("DLL and EXE Object User/Client"), WS_OVERLAPPEDWINDOW
        , 35, 35, 350, 250, NULL, NULL, m_hInst, this);

    if (NULL==m_hWnd)
        return FALSE;

    ShowWindow(m_hWnd, m_nCmdShow);
    UpdateWindow(m_hWnd);

    CheckMenuItem(GetMenu(m_hWnd), IDM_OBJECTUSEDLL, MF_CHECKED);
    CheckMenuItem(GetMenu(m_hWnd), IDM_OBJECTUSEEXE, MF_UNCHECKED);

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

void CApp::Message(LPTSTR psz)
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
