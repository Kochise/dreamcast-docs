/*
 * ENUMRECT.CPP
 * C/C++ Enumerator Demonstartion Chapter 2
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#define INITGUIDS
#include "enumrect.h"


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
 * EnumWndProc
 *
 * Purpose:
 *  Standard window class procedure.
 */

LRESULT APIENTRY EnumWndProc(HWND hWnd, UINT iMsg, WPARAM wParam
    , LPARAM lParam)
    {
    PAPP        pApp;
    RECT        rc;
    DWORD       cRect;
    BOOL        fRes;
    PENUMRECT   pClone;

    COMMANDPARAMS(wID, wCode, hWndMsg);

    pApp=(PAPP)GetWindowLong(hWnd, ENUMWL_STRUCTURE);

    switch (iMsg)
        {
        case WM_NCCREATE:
            pApp=(PAPP)(((LPCREATESTRUCT)lParam)->lpCreateParams);
            SetWindowLong(hWnd, ENUMWL_STRUCTURE, (LONG)pApp);
            return (DefWindowProc(hWnd, iMsg, wParam, lParam));


        case WM_DESTROY:
            PostQuitMessage(0);
            break;


        case WM_COMMAND:
            switch (wID)
                {
                case IDM_ENUMCREATEC:
                    if (NULL!=pApp->m_pIEnumRect)
                        pApp->m_pIEnumRect->Release();

                    fRes=CreateRECTEnumeratorC(&pApp->m_pIEnumRect);

                    pApp->Message(fRes ? TEXT("C Object created")
                        : TEXT("C Object creation failed"));

                    break;

                case IDM_ENUMCREATECPP:
                    if (NULL!=pApp->m_pIEnumRect)
                        pApp->m_pIEnumRect->Release();

                    fRes=CreateRECTEnumeratorCPP(&pApp->m_pIEnumRect);

                    pApp->Message(fRes ? TEXT("C++ Object created")
                        : TEXT("C++ Object creation failed"));

                    break;


                case IDM_ENUMRELEASE:
                    if (NULL==pApp->m_pIEnumRect)
                        {
                        pApp->Message(TEXT("There is no object"));
                        break;
                        }

                    if (0==pApp->m_pIEnumRect->Release())
                        {
                        pApp->m_pIEnumRect=NULL;
                        pApp->Message(TEXT("Object released"));
                        }

                    break;


                case IDM_ENUMRUNTHROUGH:
                    if (NULL==pApp->m_pIEnumRect)
                        {
                        pApp->Message(TEXT("There is no object"));
                        break;
                        }

                    while (pApp->m_pIEnumRect->Next(1, &rc, &cRect))
                        ;

                    pApp->Message(TEXT("Enumeration complete"));
                    break;


                case IDM_ENUMEVERYTHIRD:
                    if (NULL==pApp->m_pIEnumRect)
                        {
                        pApp->Message(TEXT("There is no object"));
                        break;
                        }

                    while (NOERROR==pApp->m_pIEnumRect->Next(1
                        , &rc, &cRect))
                        {
                        if (NOERROR!=pApp->m_pIEnumRect->Skip(2))
                            break;
                        }

                    pApp->Message(TEXT("Enumeration complete"));
                    break;


                case IDM_ENUMRESET:
                    if (NULL==pApp->m_pIEnumRect)
                        {
                        pApp->Message(TEXT("There is no object"));
                        break;
                        }

                    pApp->m_pIEnumRect->Reset();
                    pApp->Message(TEXT("Reset complete"));
                    break;


                case IDM_ENUMCLONE:
                    if (NULL==pApp->m_pIEnumRect)
                        {
                        pApp->Message(TEXT("There is no object"));
                        break;
                        }

                    pApp->m_pIEnumRect->Clone((PENUMRECT *)&pClone);

                    if (NULL==pClone)
                        pApp->Message(TEXT("Clone failed"));
                    else
                        {
                        pApp->Message(TEXT("Clone succeeded"));
                        pClone->Release();
                        }
                    break;


                case IDM_ENUMEXIT:
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
    m_pIEnumRect=NULL;

    return;
    }


CApp::~CApp(void)
    {
    //Free the enumerator object if we have one.
    if (NULL!=m_pIEnumRect)
        m_pIEnumRect->Release();

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
        wc.lpfnWndProc    = EnumWndProc;
        wc.cbClsExtra     = 0;
        wc.cbWndExtra     = CBWNDEXTRA;
        wc.hInstance      = m_hInst;
        wc.hIcon          = LoadIcon(m_hInst, TEXT("Icon"));
        wc.hCursor        = LoadCursor(NULL, IDC_ARROW);
        wc.hbrBackground  = (HBRUSH)(COLOR_WINDOW + 1);
        wc.lpszMenuName   = MAKEINTRESOURCE(IDR_MENU);
        wc.lpszClassName  = TEXT("ENUMRECT");

        if (!RegisterClass(&wc))
            return FALSE;
        }

    m_hWnd=CreateWindow(TEXT("ENUMRECT"), TEXT("RECT Enumerator")
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
