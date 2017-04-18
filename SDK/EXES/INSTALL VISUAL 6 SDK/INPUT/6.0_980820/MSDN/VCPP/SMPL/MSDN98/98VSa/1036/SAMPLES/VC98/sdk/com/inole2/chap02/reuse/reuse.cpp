/*
 * REUSE.CPP
 * Demonstration of COM Reusability mechanisms.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#define INITGUIDS
#include <windows.h>
#include "reuse.h"


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
 * ReuseWndProc
 *
 * Purpose:
 *  Standard window class procedure.
 */

LRESULT APIENTRY ReuseWndProc(HWND hWnd, UINT iMsg, WPARAM wParam
    , LPARAM lParam)
    {
    PAPP        pApp;
    BOOL        fRes;
    IAnimal    *pIAnimal;
    IKoala     *pIKoala;

    COMMANDPARAMS(wID, wCode, hWndMsg);

    pApp=(PAPP)GetWindowLong(hWnd, REUSEWL_STRUCTURE);

    switch (iMsg)
        {
        case WM_NCCREATE:
            pApp=(PAPP)(((LPCREATESTRUCT)lParam)->lpCreateParams);
            SetWindowLong(hWnd, REUSEWL_STRUCTURE, (LONG)pApp);
            return (DefWindowProc(hWnd, iMsg, wParam, lParam));


        case WM_DESTROY:
            PostQuitMessage(0);
            break;


        case WM_COMMAND:
            switch (wID)
                {
                case IDM_CREATECONTAINMENT:
                    if (NULL!=pApp->m_pIUnknown)
                        pApp->m_pIUnknown->Release();

                    fRes=CreateKoalaContainment(&pApp->m_pIUnknown);

                    pApp->Message(fRes ? TEXT("KoalaC created")
                        : TEXT("KoalaC creation failed"));

                    break;


                case IDM_CREATEAGGREGATION:
                    if (NULL!=pApp->m_pIUnknown)
                        pApp->m_pIUnknown->Release();

                    fRes=CreateKoalaAggregation(&pApp->m_pIUnknown);

                    pApp->Message(fRes ? TEXT("KoalaA created")
                        : TEXT("KoalaA creation failed"));

                    break;

                case IDM_ANIMALEAT:
                    if (!pApp->GetInterface(IID_IAnimal, (void **)&pIAnimal))
                        break;

                    pIAnimal->Eat();
                    pApp->Message(TEXT("IAnimal::Eat called"));
                    pIAnimal->Release();
                    break;


                case IDM_ANIMALSLEEP:
                    if (!pApp->GetInterface(IID_IAnimal, (void **)&pIAnimal))
                        break;

                    pIAnimal->Sleep();
                    pApp->Message(TEXT("IAnimal::Sleep called"));
                    pIAnimal->Release();
                    break;


                case IDM_ANIMALPROCREATE:
                    if (!pApp->GetInterface(IID_IAnimal, (void **)&pIAnimal))
                        break;

                    pIAnimal->Procreate();
                    pApp->Message(TEXT("IAnimal::Procreate called"));
                    pIAnimal->Release();
                    break;


                case IDM_KOALACLIMBEUCALYPTUSTREES:
                    if (!pApp->GetInterface(IID_IKoala, (void **)&pIKoala))
                        break;

                    pIKoala->ClimbEucalyptusTrees();
                    pApp->Message(TEXT("IKoala::ClimbEucalyptusTrees called"));
                    pIKoala->Release();
                    break;


                case IDM_KOALAPOUCHOPENSDOWN:
                    if (!pApp->GetInterface(IID_IKoala, (void **)&pIKoala))
                        break;

                    pIKoala->PouchOpensDown();
                    pApp->Message(TEXT("IKoala::PouchOpensDown called"));
                    pIKoala->Release();
                    break;


                case IDM_KOALASLEEPFORHOURSAFTEREATING:
                    if (!pApp->GetInterface(IID_IKoala, (void **)&pIKoala))
                        break;

                    pIKoala->SleepForHoursAfterEating();
                    pApp->Message(TEXT("IKoala::SleepForHoursAfterEating called"));
                    pIKoala->Release();
                    break;


                case IDM_RELEASE:
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


                case IDM_EXIT:
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
        wc.lpfnWndProc    = ReuseWndProc;
        wc.cbClsExtra     = 0;
        wc.cbWndExtra     = CBWNDEXTRA;
        wc.hInstance      = m_hInst;
        wc.hIcon          = LoadIcon(m_hInst, TEXT("Icon"));
        wc.hCursor        = LoadCursor(NULL, IDC_ARROW);
        wc.hbrBackground  = (HBRUSH)(COLOR_WINDOW + 1);
        wc.lpszMenuName   = MAKEINTRESOURCE(IDR_MENU);
        wc.lpszClassName  = TEXT("REUSE");

        if (!RegisterClass(&wc))
            return FALSE;
        }

    m_hWnd=CreateWindow(TEXT("REUSE"), TEXT("COM Reusability Demo")
        , WS_MINIMIZEBOX | WS_OVERLAPPEDWINDOW
        ,35, 35, 350, 250, NULL, NULL, m_hInst, this);

    if (NULL==m_hWnd)
        return FALSE;

    ShowWindow(m_hWnd, m_nCmdShow);
    UpdateWindow(m_hWnd);

    return TRUE;
    }




/*
 * GetInterface
 *
 * Purpose:
 *  Centralized function to query for an interface and
 *  return the pointer.
 *
 * Parameters:
 *  riid            REFIID of the interface to query for.
 *  ppv             void ** in which to return the pointer.
 *
 * Return Value:
 *  BOOL            TRUE if the interface was retrieved, FALSE
 *                  otherwise.
 */

BOOL CApp::GetInterface(REFIID riid, void **ppv)
    {
    HRESULT     hr;

    *ppv=NULL;

    if (NULL==m_pIUnknown)
        {
        Message(TEXT("There is no object"));
        return FALSE;
        }

    hr=m_pIUnknown->QueryInterface(riid, ppv);

    if (FAILED(hr))
        {
        Message(TEXT("Failed to get the interface"));
        return FALSE;
        }

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
