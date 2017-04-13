/*
 * LINKUSER.CPP
 * Link User Chapter 9
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#define INITGUIDS
#include "linkuser.h"


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

    SETMESSAGEQUEUE(96);

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
 * DataUserWndProc
 *
 * Purpose:
 *  Window class procedure.  Standard callback.
 */

LRESULT APIENTRY LinkUserWndProc(HWND hWnd, UINT iMsg
    , WPARAM wParam, LPARAM lParam)
    {
    PAPP    pApp;
    RECT    rc;

    COMMANDPARAMS(wID, wCode, hWndMsg);

    pApp=(PAPP)GetWindowLong(hWnd, LINKUSERWL_STRUCTURE);

    switch (iMsg)
        {
        case WM_NCCREATE:
            pApp=(PAPP)((LPCREATESTRUCT)lParam)->lpCreateParams;
            SetWindowLong(hWnd, LINKUSERWL_STRUCTURE, (LONG)pApp);
            return (DefWindowProc(hWnd, iMsg, wParam, lParam));

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        case WM_SIZE:
            //Keep the listbox filling the client area
            GetClientRect(hWnd, &rc);
            SetWindowPos(pApp->m_hWndList, NULL, rc.left, rc.top
                , rc.right-rc.left, rc.bottom-rc.top
                , SWP_NOZORDER | SWP_NOACTIVATE);
            break;

        case WM_COMMAND:
            wID=LOWORD(wParam);

            switch (wID)
                {
                case ID_LISTOLINKS:
                    switch (wCode)
                        {
                        case LBN_DBLCLK:
                            pApp->ShowDescription();
                            break;
                        }

                    break;

                case IDM_LINKSHOWDESCRIPTION:
                    //Same as double-clicking in listbox
                    pApp->ShowDescription();
                    break;

                case IDM_LINKPARSEANDBIND:
                    pApp->ParseAndBind();
                    break;

                case IDM_LINKEXIT:
                    PostMessage(hWnd, WM_CLOSE, 0, 0L);
                    break;

                default:
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

    m_hInst=hInst;
    m_hInstPrev=hInstPrev;
    m_nCmdShow=nCmdShow;

    m_hWnd=NULL;
    m_fInitialized=FALSE;
    m_hWndList=NULL;

    for (i=0; i < CMONIKERS; i++)
        m_rgpmk[i]=NULL;

    return;
    }


CApp::~CApp(void)
    {
    UINT        i;

    for (i=0; i < CMONIKERS; i++)
        ReleaseInterface(m_rgpmk[i]);

    if (IsWindow(m_hWnd))
        DestroyWindow(m_hWnd);  //Destroys listbox

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
    BOOL        fRet;
    RECT        rc;

    CHECKVER_COM;

    if (FAILED(CoInitialize(NULL)))
        return FALSE;

    m_fInitialized=TRUE;

    //Register our window classes.
    if (!m_hInstPrev)
        {
        wc.style          = CS_HREDRAW | CS_VREDRAW;
        wc.lpfnWndProc    = LinkUserWndProc;
        wc.cbClsExtra     = 0;
        wc.cbWndExtra     = CBWNDEXTRA;
        wc.hInstance      = m_hInst;
        wc.hIcon          = LoadIcon(m_hInst, TEXT("Icon"));
        wc.hCursor        = LoadCursor(NULL, IDC_ARROW);
        wc.hbrBackground  = (HBRUSH)(COLOR_WINDOW + 1);
        wc.lpszMenuName   = MAKEINTRESOURCE(IDR_MENU);
        wc.lpszClassName  = TEXT("LINKUSER");

        if (!RegisterClass(&wc))
            return FALSE;
        }

    //Create the main window.
    m_hWnd=CreateWindow(TEXT("LINKUSER"), TEXT("Link User")
        , WS_OVERLAPPEDWINDOW,35, 35, 420, 250, NULL
        , NULL, m_hInst, this);

    if (NULL==m_hWnd)
        return FALSE;

    //Create the list of monikers
    GetClientRect(m_hWnd, &rc);
    m_hWndList=CreateWindow(TEXT("listbox"), TEXT("LinkList")
        , WS_CHILD | WS_VISIBLE | LBS_NOTIFY | LBS_NOINTEGRALHEIGHT
        , rc.left, rc.top, rc.right-rc.left, rc.bottom-rc.top
        , m_hWnd, (HMENU)ID_LISTOLINKS, m_hInst, NULL);

    if (NULL==m_hWndList)
        return FALSE;

    if (!CreateMonikers())
        return FALSE;

    if (!ListInitialize())
        return FALSE;

    ShowWindow(m_hWnd, m_nCmdShow);
    UpdateWindow(m_hWnd);

    return fRet;
    }



/*
 * CApp::CreateMonikers
 *
 * Purpose:
 *  Creates monikers and stores them in m_rgpmk.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  BOOL            TRUE if successful, FALSE otherwise.
 */

BOOL CApp::CreateMonikers(void)
    {
    TCHAR       szFile[]=TEXT("c:\\inole\\chap09\\linksrc\\goop.lks");
    TCHAR       szItem1[]=TEXT("Object 2");
    TCHAR       szItem2[]=TEXT("Sub-Object 3");
    TCHAR       szDelim[]=TEXT("!");
    IMoniker   *pmkItem;
    HRESULT     hr;

    //Create a simple file moniker
    if (FAILED(CreateFileMoniker(szFile, &m_rgpmk[0])))
        return FALSE;

    //Create File!Item moniker, item first, then composite
    if (FAILED(CreateItemMoniker(szDelim, szItem1, &pmkItem)))
        return FALSE;

    //The output here will be the File!Item moniker
    hr=m_rgpmk[0]->ComposeWith(pmkItem, FALSE, &m_rgpmk[1]);
    pmkItem->Release();

    if (FAILED(hr))
        return FALSE;

    /*
     * Now create the File!Item!Item by appending another item
     * onto the File!Item just created.
     */
    if (FAILED(CreateItemMoniker(szDelim, szItem2, &pmkItem)))
        return FALSE;

    hr=m_rgpmk[1]->ComposeWith(pmkItem, FALSE, &m_rgpmk[2]);
    pmkItem->Release();

    if (FAILED(hr))
        return FALSE;

    return TRUE;
    }




/*
 * CApp::ListInitialize
 *
 * Purpose:
 *  Retrieves the display names for each moniker in our
 *  array and displays that name in the listbox.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  BOOL            TRUE if successful, FALSE otherwise.
 */

BOOL CApp::ListInitialize(void)
    {
    UINT        i;

    for (i=0; i < CMONIKERS; i++)
        {
        LPOLESTR    pszName;
        HRESULT     hr;
        IBindCtx   *pbc;

        if (FAILED(CreateBindCtx(0, &pbc)))
            return FALSE;

        hr=m_rgpmk[i]->GetDisplayName(pbc, NULL, &pszName);
        pbc->Release();

        if (FAILED(hr))
            return FALSE;

       #ifdef WIN32ANSI
        char    szTemp[256];

        WideCharToMultiByte(CP_ACP, 0, pszName, -1, szTemp, 256
            , NULL, NULL);
        SendMessage(m_hWndList, LB_ADDSTRING, 0, (LPARAM)szTemp);
       #else
        SendMessage(m_hWndList, LB_ADDSTRING, 0, (LPARAM)pszName);
       #endif
        }

    return TRUE;
    }




/*
 * CApp::ShowDescription
 *
 * Purpose:
 *  Tells CApp to retrieve the description text for a particular
 *  item in its listbox.  This is done in response to a double-click
 *  on a moniker display name which we bind to an ask for
 *  IDescription.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  None
 */

void CApp::ShowDescription(void)
    {
    int             i;

    i=(int)SendMessage(m_hWndList, LB_GETCURSEL, 0, 0L);

    if (LB_ERR==i)
        return;

    BindAndShow(m_rgpmk[i], NULL);
    return;
    }




/*
 * CApp::ParseAndBind
 *
 * Purpose:
 *  Recreates a moniker from the display name under the current
 *  selection then attempts to bind as with ShowDescription.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  None
 */

void CApp::ParseAndBind(void)
    {
    HRESULT         hr;
    IBindCtx       *pbc;
    IMoniker       *pmk;
    int             i;
    TCHAR           szName[512];
    ULONG           chEaten=0;

    i=(int)SendMessage(m_hWndList, LB_GETCURSEL, 0, 0L);

    if (LB_ERR==i)
        return;

    SendMessage(m_hWndList, LB_GETTEXT, i, (LPARAM)(LPTSTR)szName);

    if (FAILED(CreateBindCtx(0, &pbc)))
        {
        MessageBox(m_hWnd, TEXT("Failed to create bind context")
            , TEXT("Link User"), MB_OK);
        return;
        }


    hr=MkParseDisplayName(pbc, szName, &chEaten, &pmk);

    if (SUCCEEDED(hr))
        {
        MessageBox(m_hWnd, TEXT("Name parsed.  Press OK to bind...")
            , TEXT("Link User"), MB_OK);

        BindAndShow(pmk, pbc);
        pmk->Release();
        }
    else
        {
        //Tell the user how far parsing got
        wsprintf(szName, TEXT("Parsing failed after %lu characters")
            , chEaten);

        MessageBox(m_hWnd, szName, TEXT("Link User"), MB_OK);
        }

    pbc->Release();
    return;
    }




/*
 * CApp::BindAndShow
 *
 * Purpose:
 *  Binds to a given moniker to given moniker and requests
 *  IDescription, asking that object for display text.
 *
 * Parameters:
 *  pmk             IMoniker * naming the object.
 *  pbc             IBindCtx * to use.  If NULL, this will use
 *                  a default.
 *
 * Return Value:
 *  None
 */

void CApp::BindAndShow(IMoniker *pmk, IBindCtx *pbc)
    {
    HRESULT         hr;
    IDescription    *pIDescription;

    if (NULL==pbc)
        {
        hr=BindMoniker(pmk, 0, IID_IDescription
            , (void **)&pIDescription);
        }
    else
        {
        hr=pmk->BindToObject(pbc, NULL, IID_IDescription
            , (void **)&pIDescription);
        }

    if (SUCCEEDED(hr))
        {
        const ULONG cch=512;
        TCHAR       szText[cch];

	   #ifdef WIN32ANSI
	    WCHAR       szw[cch];
		hr=pIDescription->GetText(szw, cch);
        WideCharToMultiByte(CP_ACP, 0, szw, -1, szText, cch, NULL, NULL);
	   #else
        hr=pIDescription->GetText(szText, cch);
	   #endif
        pIDescription->Release();

        if (SUCCEEDED(hr))
            {
            MessageBox(m_hWnd, szText, TEXT("Description Is:")
                , MB_OK);
            }
        else
            {
            MessageBox(m_hWnd, TEXT("Failed to get description text")
                , TEXT("Link User"), MB_OK);
            }
        }
    else
        {
        MessageBox(m_hWnd, TEXT("BindMoniker failed")
            , TEXT("Link User"), MB_OK);
        }

    return;
    }
