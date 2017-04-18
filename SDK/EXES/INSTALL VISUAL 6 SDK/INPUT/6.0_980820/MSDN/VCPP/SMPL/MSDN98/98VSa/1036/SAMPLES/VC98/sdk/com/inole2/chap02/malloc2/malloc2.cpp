/*
 * MALLOC2.CPP
 * C++ Malloc Demonstration Chapter 2
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#include "malloc2.h"


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
    DWORD       dwVer;
    HRESULT     hr;

    SETMESSAGEQUEUE;

    //Make sure COM is the right version
    dwVer=CoBuildVersion();

    if (rmm!=HIWORD(dwVer))
        return 0;

    //Initialize OLE
    hr=CoInitialize(NULL);

    if (FAILED(hr))
        return 0;

    pApp=new CApp(hInst, hInstPrev, nCmdShow);

    if (NULL!=pApp)
        {
        if (pApp->Init())
            {
            while (GetMessage(&msg, NULL, 0,0 ))
                {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
                }
            }

        delete pApp;
        }

    //Only call this if CoInitialize worked
    CoUninitialize();
    return 0;
    }





/*
 * MallocWndProc
 *
 * Purpose:
 *  Standard window class procedure.
 */

LRESULT APIENTRY MallocWndProc(HWND hWnd, UINT iMsg
    , WPARAM wParam, LPARAM lParam)
    {
    PAPP        pApp;
    ULONG       cb;
    UINT        i;
    BOOL        fResult;

    pApp=(PAPP)GetWindowLong(hWnd, MALLOCWL_STRUCTURE);

    switch (iMsg)
        {
        case WM_NCCREATE:
            pApp=(PAPP)(((LPCREATESTRUCT)lParam)->lpCreateParams);
            SetWindowLong(hWnd, MALLOCWL_STRUCTURE, (LONG)pApp);
            return (DefWindowProc(hWnd, iMsg, wParam, lParam));

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        case WM_COMMAND:
            switch (LOWORD(wParam))
                {
                case IDM_COGETMALLOC:
                    pApp->GetAllocator();
                    break;


                case IDM_RELEASE:
                    if (!pApp->HaveAllocator())
                        break;

                    pApp->FreeAllocations(TRUE);
                    pApp->Message(TEXT("Release complete"));
                    break;


                case IDM_ALLOC:
                    if (!pApp->HaveAllocator())
                        break;

                    fResult=pApp->DoAllocations(FALSE);

                    pApp->Message(fResult ? TEXT("Alloc succeeded")
                        : TEXT("Alloc failed"));

                    break;


                case IDM_FREE:
                    if (!pApp->HaveAllocations())
                        break;

                    pApp->FreeAllocations(FALSE);
                    pApp->Message(TEXT("Free complete"));
                    break;


                case IDM_REALLOC:
                    if (!pApp->HaveAllocator())
                        break;

                    fResult=pApp->DoAllocations(TRUE);

                    pApp->Message(fResult ? TEXT("Realloc succeeded")
                        : TEXT("Realloc failed"));

                    break;


                case IDM_GETSIZE:
                    if (!pApp->HaveAllocations())
                        break;

                    fResult=TRUE;

                    for (i=0; i < CALLOCS; i++)
                        {
                        cb=pApp->m_pIMalloc->GetSize(pApp->m_rgpv[i]);

                        /*
                         * We test that the size is *at least*
                         * what we wanted.
                         */
                        fResult &= (pApp->m_rgcb[i] <= cb);
                        }

                    pApp->Message(fResult ? TEXT("Sizes matched")
                        : TEXT("Sizes mismatch"));

                    break;


                case IDM_DIDALLOC:
                    if (!pApp->HaveAllocations())
                        break;

                    /*
                     * DidAlloc may return -1 if it does not know
                     * whether or not it actually allocated
                     * something.  In that case we just blindly
                     * & in a -1 with no affect.
                     */

                    fResult=(BOOL)-1;

                    for (i=0; i < CALLOCS; i++)
                        {
                        fResult &= pApp->m_pIMalloc
                            ->DidAlloc(pApp->m_rgpv[i]);
                        }

                    if (0==fResult)
                        pApp->Message(TEXT("DidAlloc is FALSE"));

                    if (1==fResult)
                        pApp->Message(TEXT("DidAlloc is TRUE"));

                    if (-1==fResult)
                        pApp->Message(TEXT("DidAlloc is unknown"));

                    break;


                case IDM_HEAPMINIMIZE:
                    if (!pApp->HaveAllocator())
                        break;

                    pApp->m_pIMalloc->HeapMinimize();
                    pApp->Message(TEXT("HeapMinimize finished"));
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
 * Constructor Parameters: (from WinMain)
 *  hInst           HINSTANCE of the application.
 *  hInstPrev       HINSTANCE of a previous instance.
 *  nCmdShow        UINT specifying how to show the app window.
 */

CApp::CApp(HINSTANCE hInst, HINSTANCE hInstPrev
    , UINT nCmdShow)
    {
    UINT        i;
    ULONG       cb;

    m_hInst       =hInst;
    m_hInstPrev   =hInstPrev;
    m_nCmdShow    =nCmdShow;

    m_hWnd        =NULL;
    m_pIMalloc    =NULL;
    m_fAllocated  =FALSE;

    //100 is arbitrary.  IMalloc can handle larger.
    cb=100;

    for (i=0; i < CALLOCS; i++)
        {
        m_rgcb[i]=cb;
        m_rgpv[i]=NULL;

        cb*=2;
        }

    return;
    }



CApp::~CApp(void)
    {
    FreeAllocations(TRUE);
    return;
    }





/*
 * CApp::Init
 *
 * Purpose:
 *  Initializes an CApp object by registering window classes,
 *  creating the main window, and doing anything else prone to
 *  failure.  If this function fails the caller should insure
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
        wc.lpfnWndProc    = MallocWndProc;
        wc.cbClsExtra     = 0;
        wc.cbWndExtra     = CBWNDEXTRA;
        wc.hInstance      = m_hInst;
        wc.hIcon          = LoadIcon(m_hInst, TEXT("Icon"));
        wc.hCursor        = LoadCursor(NULL, IDC_ARROW);
        wc.hbrBackground  = (HBRUSH)(COLOR_WINDOW + 1);
        wc.lpszMenuName   = MAKEINTRESOURCE(IDR_MENU);
        wc.lpszClassName  = TEXT("MALLOC2");

        if (!RegisterClass(&wc))
            return FALSE;
        }

    m_hWnd=CreateWindow(TEXT("MALLOC2"), TEXT("C++ Malloc Demo")
        , WS_OVERLAPPEDWINDOW, 35, 35, 350, 250, NULL, NULL
        , m_hInst, this);

    if (NULL==m_hWnd)
        return FALSE;

    ShowWindow(m_hWnd, m_nCmdShow);
    UpdateWindow(m_hWnd);

    return TRUE;
    }




/*
 * CApp::GetAllocator
 *
 * Purpose:
 *  Retrieves the current allocator.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  None
 */

void CApp::GetAllocator(void)
    {
    HRESULT     hr;
    TCHAR       szTemp[80];

    //This also releases m_pIMalloc
    FreeAllocations(TRUE);

    hr=CoGetMalloc(MEMCTX_TASK, &m_pIMalloc);

    wsprintf(szTemp, TEXT("CoGetMalloc %s")
        , SUCCEEDED(hr) ? TEXT("succeeded") : TEXT("failed"));

    Message(szTemp);
    return;
    }



/*
 * CApp::HaveAllocator
 *
 * Purpose:
 *  Checks if there's a valid allocator and displays a
 *  message if not.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  BOOL            TRUE if there is an allocator, FALSE otherwise.
 */

BOOL CApp::HaveAllocator(void)
    {
    if (NULL==m_pIMalloc)
        {
        Message(TEXT("Create the allocator first"));
        return FALSE;
        }

    return TRUE;
    }




/*
 * CApp::DoAllocations
 *
 * Purpose:
 *  Centralized place to clean up allocations made on
 *  the current IMalloc.
 *
 * Parameters:
 *  fRelease        BOOL indicating if we're to
 *                  IMalloc::Release as well.
 *
 * Return Value:
 *  BOOL            TRUE if all allocations succeeded.
 */

BOOL CApp::DoAllocations(BOOL fRealloc)
    {
    UINT        i;
    ULONG       iByte;
    BOOL        fResult=TRUE;
    ULONG       cb;
    LPVOID      pv;

    if (!fRealloc)
        FreeAllocations(FALSE);

    for (i=0; i < CALLOCS; i++)
        {
        //cb is set in the code below for later initialization
        if (fRealloc)
            {
            m_rgcb[i]+=128;
            cb=m_rgcb[i];

            //Old memory is not freed if Realloc fails
            pv=m_pIMalloc->Realloc(m_rgpv[i], cb);
            }
        else
            {
            cb=m_rgcb[i];
            pv=m_pIMalloc->Alloc(cb);
            }

        m_rgpv[i]=pv;

        //Fill the memory with letters.
        if (NULL!=pv)
            {
            LPBYTE  pb=(LPBYTE)pv;

            for (iByte=0; iByte < cb; iByte++)
                *pb++=('a'+i);
            }

        fResult &= (NULL!=pv);
        }

    m_fAllocated=fResult;

    //Clean up whatever we might have allocated
    if (!fResult)
        FreeAllocations(FALSE);

    return fResult;
    }




/*
 * CApp::HaveAllocations
 *
 * Purpose:
 *  Checks if we have allocated memory from the current allocator,
 *  displaying a message if not.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  BOOL            TRUE if there are allocations, FALSE otherwise.
 */

BOOL CApp::HaveAllocations(void)
    {
    if (!HaveAllocator())
        return FALSE;

    if (!m_fAllocated)
        {
        Message(TEXT("Choose Alloc first"));
        return FALSE;
        }

    return TRUE;
    }






/*
 * CApp::FreeAllocations
 *
 * Purpose:
 *  Centralized place to clean up allocations made on
 *  the current IMalloc.
 *
 * Parameters:
 *  fRelease        BOOL indicating if we're to
 *                  IMalloc::Release as well.
 *
 * Return Value:
 *  None
 */

void CApp::FreeAllocations(BOOL fRelease)
    {
    UINT    i;

    if (NULL==m_pIMalloc)
        return;

    if (m_fAllocated)
        {
        for (i=0; i < CALLOCS; i++)
            {
            if (NULL!=m_rgpv[i])
                m_pIMalloc->Free(m_rgpv[i]);

            m_rgpv[i]=NULL;
            }

        m_fAllocated=FALSE;
        }

    if (fRelease)
        {
        m_pIMalloc->Release();
        m_pIMalloc=NULL;
        }

    return;
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
