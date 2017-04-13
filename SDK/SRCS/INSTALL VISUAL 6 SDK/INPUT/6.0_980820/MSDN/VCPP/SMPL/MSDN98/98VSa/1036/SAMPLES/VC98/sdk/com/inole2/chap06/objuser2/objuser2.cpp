/*
 * OBJUSER2.CPP
 * Koala Client #2 Chapter 6
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#define INITGUIDS
#include "objuser2.h"


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
    IUnknown       *pUnk;
    IPersist       *pIPersist;

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
            if (NULL!=pApp)
                pUnk=pApp->m_pIUnknown;

            switch (LOWORD(wParam))
                {
                case IDM_OBJECTCREATE:
                    if (NULL!=pUnk)
                        ReleaseInterface(pApp->m_pIUnknown);

                    hr=CoCreateInstance(CLSID_Koala, NULL
                        , CLSCTX_LOCAL_SERVER, IID_IUnknown
                        , (PPVOID)&pApp->m_pIUnknown);

                    if (SUCCEEDED(hr))
                        pApp->Message(TEXT("Creation succeeded"));
                    else
                        pApp->Message(TEXT("Creation failed"));

                    break;


                case IDM_OBJECTGETCLASSID:
                    if (NULL==pUnk)
                        {
                        pApp->Message(TEXT("There is no object"));
                        break;
                        }

                    if (SUCCEEDED(pUnk->QueryInterface(IID_IPersist
                        , (void **)&pIPersist)))
                        {
                        CLSID       clsID;
                        HRESULT     hr;
                        TCHAR       szMsg[256];

                        hr=pIPersist->GetClassID(&clsID);
                        pIPersist->Release();

                        wsprintf(szMsg
                            , TEXT("IPersist::GetClassID returned 0x%lX")
                            , (DWORD)hr);
                        pApp->Message(szMsg);
                        }
                    else
                        pApp->Message(TEXT("IPersist not available"));

                    break;


                case IDM_OBJECTRELEASE:
                    if (NULL==pUnk)
                        {
                        pApp->Message(TEXT("There is no object"));
                        break;
                        }

                    ReleaseInterface(pApp->m_pIUnknown);
                    pApp->Message(TEXT("Object released"));
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

    m_pIUnknown   =NULL;
    m_fInitialized=FALSE;

    m_pMsgFilter  =NULL;
    return;
    }


CApp::~CApp(void)
    {
    if (NULL!=m_pMsgFilter)
        {
        CoRegisterMessageFilter(NULL, NULL);
        ReleaseInterface(m_pMsgFilter);
        }

    ReleaseInterface(m_pIUnknown);

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
        wc.lpszClassName  = TEXT("OBJUSER2");

        if (!RegisterClass(&wc))
            return FALSE;
        }

    m_hWnd=CreateWindow(TEXT("OBJUSER2")
        , TEXT("Koala Client #2"), WS_OVERLAPPEDWINDOW
        , 35, 35, 350, 250, NULL, NULL, m_hInst, this);

    if (NULL==m_hWnd)
        return FALSE;


    //Create and register a message filter.
    m_pMsgFilter=new CMessageFilter(this);

    if (NULL!=m_pMsgFilter)
        {
        m_pMsgFilter->AddRef();

        if (FAILED(CoRegisterMessageFilter(m_pMsgFilter, NULL)))
            ReleaseInterface(m_pMsgFilter);
        }

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
