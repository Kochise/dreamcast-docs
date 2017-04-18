/*
 * MALLOC1.C
 * C Malloc Demonstration Chapter 2
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#include "malloc1.h"


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

    pApp=App_Create(hInst, hInstPrev, nCmdShow);

    if (NULL!=pApp)
        {
        if (App_Init(pApp))
            {
            while (GetMessage(&msg, NULL, 0,0 ))
                {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
                }
            }

        App_Destroy(pApp);
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
                    App_GetAllocator(pApp);
                    break;


                case IDM_RELEASE:
                    if (!App_HaveAllocator(pApp))
                        break;

                    App_FreeAllocations(pApp, TRUE);
                    App_Message(pApp, TEXT("Release complete"));
                    break;


                case IDM_ALLOC:
                    if (!App_HaveAllocator(pApp))
                        break;

                    fResult=App_DoAllocations(pApp, FALSE);

                    App_Message(pApp, fResult
                        ? TEXT("Alloc succeeded")
                        : TEXT("Alloc failed"));

                    break;


                case IDM_FREE:
                    if (!App_HaveAllocations(pApp))
                        break;

                    App_FreeAllocations(pApp, FALSE);
                    App_Message(pApp, TEXT("Free complete"));
                    break;


                case IDM_REALLOC:
                    if (!App_HaveAllocator(pApp))
                        break;

                    fResult=App_DoAllocations(pApp, TRUE);

                    App_Message(pApp, fResult
                        ? TEXT("Realloc succeeded")
                        : TEXT("Realloc failed"));

                    break;


                case IDM_GETSIZE:
                    if (!App_HaveAllocations(pApp))
                        break;

                    fResult=TRUE;

                    for (i=0; i < CALLOCS; i++)
                        {
                        cb=pApp->m_pIMalloc->lpVtbl->GetSize
                            (pApp->m_pIMalloc, pApp->m_rgpv[i]);

                        /*
                         * We test that the size is *at least*
                         * what we wanted.
                         */
                        fResult &= (pApp->m_rgcb[i] <= cb);
                        }

                    App_Message(pApp, fResult
                        ? TEXT("Sizes matched")
                        : TEXT("Sizes mismatch"));

                    break;


                case IDM_DIDALLOC:
                    if (!App_HaveAllocations(pApp))
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
                        fResult &= pApp->m_pIMalloc->lpVtbl->DidAlloc
                            (pApp->m_pIMalloc, pApp->m_rgpv[i]);
                        }

                    if (0==fResult)
                        App_Message(pApp, TEXT("DidAlloc is FALSE"));

                    if (1==fResult)
                        App_Message(pApp, TEXT("DidAlloc is TRUE"));

                    if (-1==fResult)
                        App_Message(pApp, TEXT("DidAlloc is unknown"));

                    break;


                case IDM_HEAPMINIMIZE:
                    if (!App_HaveAllocator(pApp))
                        break;

                    pApp->m_pIMalloc->lpVtbl->HeapMinimize
                        (pApp->m_pIMalloc);
                    App_Message(pApp, TEXT("HeapMinimize finished"));
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
 * App_Create
 * App_Destroy
 *
 * Constructor Parameters: (from WinMain)
 *  hInst           HINSTANCE of the application.
 *  hInstPrev       HINSTANCE of a previous instance.
 *  nCmdShow        UINT specifying how to show the app window.
 */

PAPP App_Create(HINSTANCE hInst, HINSTANCE hInstPrev, UINT nCmdShow)
    {
    UINT        i;
    ULONG       cb;
    PAPP        pApp;

    pApp=(PAPP)malloc(sizeof(APP));

    if (NULL==pApp)
        return NULL;

    pApp->m_hInst       =hInst;
    pApp->m_hInstPrev   =hInstPrev;
    pApp->m_nCmdShow    =nCmdShow;

    pApp->m_hWnd        =NULL;
    pApp->m_pIMalloc    =NULL;
    pApp->m_fAllocated  =FALSE;

    //100 is arbitrary.  IMalloc can handle larger.
    cb=100;

    for (i=0; i < CALLOCS; i++)
        {
        pApp->m_rgcb[i]=cb;
        pApp->m_rgpv[i]=NULL;

        cb*=2;
        }

    return pApp;
    }



void App_Destroy(PAPP pApp)
    {
    App_FreeAllocations(pApp, TRUE);
    free(pApp);
    return;
    }





/*
 * App_Init
 *
 * Purpose:
 *  Initializes an CApp object by registering window classes,
 *  creating the main window, and doing anything else prone to
 *  failure.  If this function fails the caller should insure
 *  that the destructor is called.
 *
 * Parameters:
 *  pApp            PAPP identifying the object.
 *
 * Return Value:
 *  BOOL            TRUE if successful, FALSE otherwise.
 */

BOOL App_Init(PAPP pApp)
    {
    WNDCLASS    wc;

    if (!pApp->m_hInstPrev)
        {
        wc.style          = CS_HREDRAW | CS_VREDRAW;
        wc.lpfnWndProc    = MallocWndProc;
        wc.cbClsExtra     = 0;
        wc.cbWndExtra     = CBWNDEXTRA;
        wc.hInstance      = pApp->m_hInst;
        wc.hIcon          = LoadIcon(pApp->m_hInst, TEXT("Icon"));
        wc.hCursor        = LoadCursor(NULL, IDC_ARROW);
        wc.hbrBackground  = (HBRUSH)(COLOR_WINDOW + 1);
        wc.lpszMenuName   = MAKEINTRESOURCE(IDR_MENU);
        wc.lpszClassName  = TEXT("MALLOC");

        if (!RegisterClass(&wc))
            return FALSE;
        }

    pApp->m_hWnd=CreateWindow(TEXT("MALLOC")
        , TEXT("C Malloc Demo"), WS_OVERLAPPEDWINDOW, 35, 35
        , 350, 250, NULL, NULL, pApp->m_hInst, pApp);

    if (NULL==pApp->m_hWnd)
        return FALSE;

    ShowWindow(pApp->m_hWnd, pApp->m_nCmdShow);
    UpdateWindow(pApp->m_hWnd);

    return TRUE;
    }




/*
 * App_GetAllocator
 *
 * Purpose:
 *  Retrieves the current allocator.
 *
 * Parameters:
 *  pApp            PAPP identifying the object.
 *
 * Return Value:
 *  None
 */

void App_GetAllocator(PAPP pApp)
    {
    HRESULT     hr;
    TCHAR       szTemp[80];

    //This also releases pApp->m_pIMalloc
    App_FreeAllocations(pApp, TRUE);

    hr=CoGetMalloc(MEMCTX_TASK, &pApp->m_pIMalloc);

    wsprintf(szTemp, TEXT("CoGetMalloc %s")
        , SUCCEEDED(hr) ? TEXT("succeeded") : TEXT("failed"));

    App_Message(pApp, szTemp);
    return;
    }



/*
 * App_HaveAllocator
 *
 * Purpose:
 *  Checks if there's a valid allocator and displays a
 *  message if not.
 *
 * Parameters:
 *  pApp            PAPP identifying the object.
 *
 * Return Value:
 *  BOOL            TRUE if there is an allocator, FALSE otherwise.
 */

BOOL App_HaveAllocator(PAPP pApp)
    {
    if (NULL==pApp->m_pIMalloc)
        {
        App_Message(pApp, TEXT("Create the allocator first"));
        return FALSE;
        }

    return TRUE;
    }




/*
 * App_DoAllocations
 *
 * Purpose:
 *  Centralized place to clean up allocations made on
 *  the current IMalloc.
 *
 * Parameters:
 *  pApp            PAPP identifying the object.
 *  fRelease        BOOL indicating if we're to
 *                  IMalloc::Release as well.
 *
 * Return Value:
 *  BOOL            TRUE if all allocations succeeded.
 */

BOOL App_DoAllocations(PAPP pApp, BOOL fRealloc)
    {
    UINT        i;
    ULONG       iByte;
    BOOL        fResult=TRUE;
    ULONG       cb;
    LPVOID      pv;

    if (!fRealloc)
        App_FreeAllocations(pApp, FALSE);

    for (i=0; i < CALLOCS; i++)
        {
        //cb is set in the code below for later initialization
        if (fRealloc)
            {
            pApp->m_rgcb[i]+=128;
            cb=pApp->m_rgcb[i];

            //Old memory is not freed if Realloc fails
            pv=pApp->m_pIMalloc->lpVtbl->Realloc(pApp->m_pIMalloc
                , pApp->m_rgpv[i], cb);
            }
        else
            {
            cb=pApp->m_rgcb[i];
            pv=pApp->m_pIMalloc->lpVtbl->Alloc(pApp->m_pIMalloc, cb);
            }

        pApp->m_rgpv[i]=pv;

        //Fill the memory with letters.
        if (NULL!=pv)
            {
            LPBYTE  pb=(LPBYTE)pv;

            for (iByte=0; iByte < cb; iByte++)
                *pb++=('a'+i);
            }

        fResult &= (NULL!=pv);
        }

    pApp->m_fAllocated=fResult;

    //Clean up whatever we might have allocated
    if (!fResult)
        App_FreeAllocations(pApp, FALSE);

    return fResult;
    }




/*
 * App_HaveAllocations
 *
 * Purpose:
 *  Checks if we have allocated memory from the current allocator,
 *  displaying a message if not.
 *
 * Parameters:
 *  pApp            PAPP identifying the object.
 *
 * Return Value:
 *  BOOL            TRUE if there are allocations, FALSE otherwise.
 */

BOOL App_HaveAllocations(PAPP pApp)
    {
    if (!App_HaveAllocator(pApp))
        return FALSE;

    if (!pApp->m_fAllocated)
        {
        App_Message(pApp, TEXT("Choose Alloc first"));
        return FALSE;
        }

    return TRUE;
    }






/*
 * App_FreeAllocations
 *
 * Purpose:
 *  Centralized place to clean up allocations made on
 *  the current IMalloc.
 *
 * Parameters:
 *  pApp            PAPP identifying the object.
 *  fRelease        BOOL indicating if we're to
 *                  IMalloc::Release as well.
 *
 * Return Value:
 *  None
 */

void App_FreeAllocations(PAPP pApp, BOOL fRelease)
    {
    UINT    i;

    if (NULL==pApp->m_pIMalloc)
        return;

    if (pApp->m_fAllocated)
        {
        for (i=0; i < CALLOCS; i++)
            {
            if (NULL!=pApp->m_rgpv[i])
                {
                pApp->m_pIMalloc->lpVtbl->Free(pApp->m_pIMalloc
                    , pApp->m_rgpv[i]);
                }

            pApp->m_rgpv[i]=NULL;
            }

        pApp->m_fAllocated=FALSE;
        }

    if (fRelease)
        {
        pApp->m_pIMalloc->lpVtbl->Release(pApp->m_pIMalloc);
        pApp->m_pIMalloc=NULL;
        }

    return;
    }





/*
 * App_Message
 *
 * Purpose:
 *  Displays a message in the client area of the window.  This is
 *  just to centralize the call to simpify other code.
 *
 * Parameters:
 *  pApp            PAPP identifying the object.
 *  psz             LPTSTR to the string to display.
 *
 * Return Value:
 *  None
 */

void App_Message(PAPP pApp, LPTSTR psz)
    {
    HDC     hDC;
    RECT    rc;

    hDC=GetDC(pApp->m_hWnd);
    GetClientRect(pApp->m_hWnd, &rc);

    SetBkColor(hDC, GetSysColor(COLOR_WINDOW));
    SetTextColor(hDC, GetSysColor(COLOR_WINDOWTEXT));

    /*
     * We'll just be sloppy and clear the whole window as
     * well as write the string with one ExtTextOut call.
     * No word wrapping here...
     */

    ExtTextOut(hDC, 0, 0, ETO_OPAQUE, &rc, psz, lstrlen(psz), NULL);
    ReleaseDC(pApp->m_hWnd, hDC);
    return;
    }
