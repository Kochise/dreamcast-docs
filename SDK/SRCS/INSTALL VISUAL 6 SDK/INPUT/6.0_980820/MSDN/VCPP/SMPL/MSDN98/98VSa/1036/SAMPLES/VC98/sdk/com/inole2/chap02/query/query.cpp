/*
 * QUERY.CPP
 * Demonstration of QueryInterface and different techniques to
 * implement multiple interfaces.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#define INITGUIDS
#include <windows.h>
#include "query.h"


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
 * QueryWndProc
 *
 * Purpose:
 *  Standard window class procedure.
 */

LRESULT APIENTRY QueryWndProc(HWND hWnd, UINT iMsg, WPARAM wParam
    , LPARAM lParam)
    {
    PAPP        pApp;
    HRESULT     hr;
    BOOL        fRes;
    ISampleOne *pISampleOne;
    ISampleTwo *pISampleTwo;
    const UINT  CCHTEMP=80;
    TCHAR       szTemp[CCHTEMP];

    COMMANDPARAMS(wID, wCode, hWndMsg);

    pApp=(PAPP)GetWindowLong(hWnd, QUERYWL_STRUCTURE);

    switch (iMsg)
        {
        case WM_NCCREATE:
            pApp=(PAPP)(((LPCREATESTRUCT)lParam)->lpCreateParams);
            SetWindowLong(hWnd, QUERYWL_STRUCTURE, (LONG)pApp);
            return (DefWindowProc(hWnd, iMsg, wParam, lParam));


        case WM_DESTROY:
            PostQuitMessage(0);
            break;


        case WM_COMMAND:
            switch (wID)
                {
                case IDM_OBJECTCREATE1:
                    if (NULL!=pApp->m_pIUnknown)
                        pApp->m_pIUnknown->Release();

                    fRes=CreateObject1(&pApp->m_pIUnknown);

                    pApp->Message(fRes ? TEXT("Object 1 created")
                        : TEXT("Object 1 creation failed"));

                    break;


                case IDM_OBJECTCREATE2:
                    if (NULL!=pApp->m_pIUnknown)
                        pApp->m_pIUnknown->Release();

                    fRes=CreateObject2(&pApp->m_pIUnknown);

                    pApp->Message(fRes ? TEXT("Object 2 created")
                        : TEXT("Object 2 creation failed"));

                    break;


                case IDM_OBJECTCREATE3:
                    if (NULL!=pApp->m_pIUnknown)
                        pApp->m_pIUnknown->Release();

                    fRes=CreateObject3(&pApp->m_pIUnknown);

                    pApp->Message(fRes ? TEXT("Object 3 created")
                        : TEXT("Object 3 creation failed"));

                    break;


                case IDM_OBJECTRELEASE:
                    if (NULL==pApp->m_pIUnknown)
                        {
                        pApp->Message(TEXT("There is no object"));
                        break;
                        }

                    if (0==pApp->m_pIUnknown->Release())
                        {
                        pApp->m_pIUnknown=NULL;
                        pApp->Message(TEXT("Object released"));
                        }

                    break;


                case IDM_OBJECTGETMESSAGE:
                    if (NULL==pApp->m_pIUnknown)
                        {
                        pApp->Message(TEXT("There is no object"));
                        break;
                        }

                    hr=pApp->m_pIUnknown->QueryInterface
                        (IID_ISampleOne, (PPVOID)&pISampleOne);

                    if (FAILED(hr))
                        {
                        pApp->Message(TEXT("Failed to get ISampleOne"));
                        break;
                        }

                    hr=pISampleOne->GetMessage(szTemp, CCHTEMP);

                    pApp->Message(SUCCEEDED(hr) ? szTemp
                        : TEXT("ISampleOne::GetMessage failed"));

                    //m_pIUnknown is still valid after this Release
                    pISampleOne->Release();
                    break;


                case IDM_OBJECTGETSTRING:
                    if (NULL==pApp->m_pIUnknown)
                        {
                        pApp->Message(TEXT("There is no object"));
                        break;
                        }

                    hr=pApp->m_pIUnknown->QueryInterface
                        (IID_ISampleTwo, (PPVOID)&pISampleTwo);

                    if (FAILED(hr))
                        {
                        pApp->Message(TEXT("Failed to get ISampleTwo"));
                        break;
                        }

                    hr=pISampleTwo->GetString(szTemp, CCHTEMP);

                    pApp->Message(SUCCEEDED(hr) ? szTemp
                        : TEXT("ISampleTwp::GetString failed"));

                    //m_pIUnknown is still valid after this Release
                    pISampleTwo->Release();
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
 * Constructor Parameters:
 *  hInst           HINSTANCE of the Application from WinMain
 *  hInstPrev       HINSTANCE of a previous instance from WinMain
 *  nCmdShow        UINT specifying how to show the app window,
 *                  from WinMain.
 */

CApp::CApp(HINSTANCE hInst, HINSTANCE hInstPrev
    , UINT nCmdShow)
    {
    //Initialize WinMain parameter holders.
    m_hInst     =hInst;
    m_hInstPrev =hInstPrev;
    m_nCmdShow  =nCmdShow;

    m_hWnd=NULL;
    m_pIUnknown=NULL;

    return;
    }


CApp::~CApp(void)
    {
    //Release the object if we still have it.
    ReleaseInterface(m_pIUnknown);
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

    if (!m_hInstPrev)
        {
        wc.style          = CS_HREDRAW | CS_VREDRAW;
        wc.lpfnWndProc    = QueryWndProc;
        wc.cbClsExtra     = 0;
        wc.cbWndExtra     = CBWNDEXTRA;
        wc.hInstance      = m_hInst;
        wc.hIcon          = LoadIcon(m_hInst, TEXT("Icon"));
        wc.hCursor        = LoadCursor(NULL, IDC_ARROW);
        wc.hbrBackground  = (HBRUSH)(COLOR_WINDOW + 1);
        wc.lpszMenuName   = MAKEINTRESOURCE(IDR_MENU);
        wc.lpszClassName  = TEXT("QUERY");

        if (!RegisterClass(&wc))
            return FALSE;
        }

    m_hWnd=CreateWindow(TEXT("QUERY"), TEXT("QueryInterface Demo")
        , WS_MINIMIZEBOX | WS_OVERLAPPEDWINDOW
        ,35, 35, 350, 250, NULL, NULL, m_hInst, this);

    if (NULL==m_hWnd)
        return FALSE;

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
