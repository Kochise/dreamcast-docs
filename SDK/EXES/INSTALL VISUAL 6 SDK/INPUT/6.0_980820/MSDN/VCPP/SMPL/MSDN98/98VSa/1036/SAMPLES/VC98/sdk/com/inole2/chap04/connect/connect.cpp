/*
 * CONNECT.CPP
 * Demonstration of connectable objects and connection points,
 * Chapter 4
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#define INITGUIDS
#include "connect.h"


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
 * ConnectWndProc
 *
 * Purpose:
 *  Standard window class procedure.
 */

LRESULT APIENTRY ConnectWndProc(HWND hWnd, UINT iMsg, WPARAM wParam
    , LPARAM lParam)
    {
    PAPP            pApp;
    BOOL            fRes;
    PCConnObject    pObj;

    COMMANDPARAMS(wID, wCode, hWndMsg);

    pApp=(PAPP)GetWindowLong(hWnd, CONNECTWL_STRUCTURE);

    switch (iMsg)
        {
        case WM_NCCREATE:
            pApp=(PAPP)(((LPCREATESTRUCT)lParam)->lpCreateParams);
            SetWindowLong(hWnd, CONNECTWL_STRUCTURE, (LONG)pApp);
            return (DefWindowProc(hWnd, iMsg, wParam, lParam));


        case WM_DESTROY:
            PostQuitMessage(0);
            break;


        case WM_COMMAND:
            switch (wID)
                {
                case IDM_OBJECTCREATE:
                    if (NULL!=pApp->m_pObj)
                        {
                        //Make sure the sinks disconnect
                        pApp->Disconnect(SINK1);
                        pApp->Disconnect(SINK2);
                        pApp->m_pObj->Release();
                        }

                    fRes=FALSE;

                    /*
                     * OLE clients never have direct access to
                     * an object's C++ class like this, so the
                     * sequence from here through the AddRef will
                     * always be encapsulated within the object's
                     * own creation functions.  This sample is a
                     * little contrived.
                     */
                    pObj=new CConnObject();

                    if (NULL!=pObj)
                        {
                        fRes=pObj->Init();
                        pObj->AddRef();
                        }

                    pApp->m_pObj=pObj;
                    pApp->Message(fRes ? TEXT("Object created")
                        : TEXT("Object creation failed"));

                    break;


                case IDM_OBJECTRELEASE:
                    if (NULL==pApp->m_pObj)
                        {
                        pApp->Message(TEXT("There is no object"));
                        break;
                        }

                    //Make sure the sinks disconnect
                    pApp->Disconnect(SINK1);
                    pApp->Disconnect(SINK2);

                    if (0==pApp->m_pObj->Release())
                        {
                        pApp->m_pObj=NULL;
                        pApp->Message(TEXT("Object released"));
                        }

                    break;


                case IDM_OBJECTSINK1CONNECT:
                    pApp->Connect(SINK1);
                    break;

                case IDM_OBJECTSINK1DISCONNECT:
                    pApp->Disconnect(SINK1);
                    break;

                case IDM_OBJECTSINK2CONNECT:
                    pApp->Connect(SINK2);
                    break;

                case IDM_OBJECTSINK2DISCONNECT:
                    pApp->Disconnect(SINK2);
                    break;

                case IDM_OBJECTEXIT:
                    PostMessage(hWnd, WM_CLOSE, 0, 0L);
                    break;


                case IDM_TRIGGERQUACK:
                case IDM_TRIGGERFLAP:
                case IDM_TRIGGERPADDLE:
                    if (NULL==pApp->m_pObj)
                        {
                        pApp->Message(TEXT("There is no object"));
                        break;
                        }

                    //The math gets the right ID for the event
                    if (!pApp->m_pObj->TriggerEvent
                        (wID-IDM_TRIGGERQUACK+EVENT_QUACK))
                        {
                        pApp->Message
                            (TEXT("There are no connected sinks"));
                        }

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
    m_pObj=NULL;

    m_rgpSink[0]=NULL;
    m_rgpSink[1]=NULL;

    return;
    }


CApp::~CApp(void)
    {
    //Release the object if we still have it.
    ReleaseInterface(m_pObj);
    Disconnect(SINK1);
    Disconnect(SINK2);

    ReleaseInterface(m_rgpSink[SINK1]);
    ReleaseInterface(m_rgpSink[SINK2]);
    return;
    }




/*
 * CApp::Connect
 * CApp::Disconnect
 *
 * Purpose:
 *  Connects or disconnects a sink object to or from the
 *  connectable object we have.
 *
 * Parameters:
 *  uID             UINT identifying which sink to use.
 */

void CApp::Connect(UINT uID)
    {
    HRESULT             hr;
    IConnectionPoint   *pCP;

    if (NULL==m_pObj)
        {
        Message(TEXT("There is no object"));
        return;
        }

    if (SINK2 < uID)
        return;

    //Is this sink connected already?
    if (0!=m_rgpSink[uID]->m_dwCookie)
        {
        Message(TEXT("This sink is already connected"));
        return;
        }

    pCP=GetConnectionPoint();

    if (NULL!=pCP)
        {
        hr=pCP->Advise(m_rgpSink[uID]
            , &m_rgpSink[uID]->m_dwCookie);

        if (FAILED(hr))
            Message(TEXT("Connection failed"));
        else
            Message(TEXT("Connection complete"));

        pCP->Release();
        }
    else
        Message(TEXT("Failed to get IConnectionPoint"));

    return;
    }


void CApp::Disconnect(UINT uID)
    {
    HRESULT             hr;
    IConnectionPoint   *pCP;

    if (NULL==m_pObj)
        {
        Message(TEXT("There is no object"));
        return;
        }

    //Is the sink connected at all?
    if (0==m_rgpSink[uID]->m_dwCookie)
        {
        Message(TEXT("This sink is not connected"));
        return;
        }

    pCP=GetConnectionPoint();

    if (NULL!=pCP)
        {
        hr=pCP->Unadvise(m_rgpSink[uID]->m_dwCookie);

        if (FAILED(hr))
            Message(TEXT("Disconnection failed"));
        else
            {
            Message(TEXT("Disconnection complete"));
            m_rgpSink[uID]->m_dwCookie=0;
            }

        pCP->Release();
        }
    else
        Message(TEXT("Failed to get IConnectionPoint"));

    return;
    }




/*
 * CApp::GetConnectionPoint
 *
 * Purpose:
 *  Asks the connectable object for an IConnectionPoint for
 *  IDuckEvents.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  IConnectionPoint * to the interface
 */

IConnectionPoint * CApp::GetConnectionPoint(void)
    {
    HRESULT                     hr;
    IConnectionPointContainer  *pCPCont;
    IConnectionPoint           *pCP=NULL;

    hr=m_pObj->QueryInterface(IID_IConnectionPointContainer
        , (PPVOID)&pCPCont);

    if (FAILED(hr))
        return NULL;

    hr=pCPCont->FindConnectionPoint(IID_IDuckEvents, &pCP);
    pCPCont->Release();

    //This check isn't necessary...just adds clarity
    if (FAILED(hr))
        return NULL;

    return pCP;
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

    //Create the two sink objects we might use
    m_rgpSink[SINK1]=new CDuckEvents(this, SINK1);
    m_rgpSink[SINK2]=new CDuckEvents(this, SINK2);

    if (NULL==m_rgpSink[SINK1] || NULL==m_rgpSink[SINK2])
        return FALSE;

    //Lock the lifetimes of these two objects
    m_rgpSink[SINK1]->AddRef();
    m_rgpSink[SINK2]->AddRef();

    //Create windows and such
    if (!m_hInstPrev)
        {
        wc.style          = CS_HREDRAW | CS_VREDRAW;
        wc.lpfnWndProc    = ConnectWndProc;
        wc.cbClsExtra     = 0;
        wc.cbWndExtra     = CBWNDEXTRA;
        wc.hInstance      = m_hInst;
        wc.hIcon          = LoadIcon(m_hInst, TEXT("Icon"));
        wc.hCursor        = LoadCursor(NULL, IDC_ARROW);
        wc.hbrBackground  = (HBRUSH)(COLOR_WINDOW + 1);
        wc.lpszMenuName   = MAKEINTRESOURCE(IDR_MENU);
        wc.lpszClassName  = TEXT("CONNECT");

        if (!RegisterClass(&wc))
            return FALSE;
        }

    m_hWnd=CreateWindow(TEXT("CONNECT"), TEXT("Connectable Object Demo")
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
