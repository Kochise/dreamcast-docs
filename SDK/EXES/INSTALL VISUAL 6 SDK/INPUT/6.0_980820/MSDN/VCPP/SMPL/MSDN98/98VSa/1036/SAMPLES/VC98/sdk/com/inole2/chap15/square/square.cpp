/*
 * SQUARE.CPP
 * Square Rendering/Calculation Automation Object Chapter 15
 *
 * An automation object that draws a square in various rotational
 * states and provides access to it through IDispatch.
 *
 * This file contains all the code for this sample.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#define INITGUIDS
#include "square.h"

ULONG       g_cObj=0;
ULONG       g_cLock=0;
HWND        g_hWnd=NULL;


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
    PCApp       pApp;

    SETMESSAGEQUEUE;

    pApp=new CApp(hInst, hInstPrev, pszCmdLine, nCmdShow);

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
 * MainWndProc
 *
 * Purpose:
 *  Standard window class procedure.
 */

LRESULT APIENTRY MainWndProc(HWND hWnd, UINT iMsg
    , WPARAM wParam, LPARAM lParam)
    {
    switch (iMsg)
        {
        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        default:
            return (DefWindowProc(hWnd, iMsg, wParam, lParam));
        }

    return 0L;
    }





/*
 * ObjectDestroyed
 *
 * Purpose:
 *  Function for the object to call when it gets destroyed.
 *  We destroy the main window if the proper conditions are met
 *  for shutdown.
 */

void ObjectDestroyed(void)
    {
    g_cObj--;

    //No more objects and no locks, shut the app down.
    if (0L==g_cObj && 0L==g_cLock && IsWindow(g_hWnd))
        PostMessage(g_hWnd, WM_CLOSE, 0, 0L);

    return;
    }




/*
 * CApp::CApp
 * CApp::~CApp
 *
 * Constructor Parameters:
 *  hInst           HINSTANCE of the Application from WinMain
 *  hInstPrev       HINSTANCE of a previous instance from WinMain
 *  pszCmdLine      LPSTR of the command line.
 *  nCmdShow        UINT specifying how to show the app window,
 *                  from WinMain.
 */

CApp::CApp(HINSTANCE hInst, HINSTANCE hInstPrev
    , LPSTR pszCmdLine, UINT nCmdShow)
    {
    //Initialize WinMain parameter holders.
    m_hInst     =hInst;
    m_hInstPrev =hInstPrev;
    m_pszCmdLine=pszCmdLine;
    m_nCmdShow  =nCmdShow;

    m_dwRegCO=0;
    m_pIClassFactory=NULL;
    m_fInitialized=FALSE;
    return;
    }


CApp::~CApp(void)
    {
    //Opposite of CoRegisterClassObject; class factory ref is now 1
    if (0L!=m_dwRegCO)
        CoRevokeClassObject(m_dwRegCO);

    //The last Release, which frees the class factory.
    if (NULL!=m_pIClassFactory)
        m_pIClassFactory->Release();

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
 *  failure.  If this function fails the caller should guarantee
 *  that the destructor is called.
 *
 * Return Value:
 *  BOOL            TRUE if successful, FALSE otherwise.
 */

BOOL CApp::Init(void)
    {
    WNDCLASS    wc;
    HRESULT     hr;
    HWND        hWnd;

    if (lstrcmpiA(m_pszCmdLine, "-Embedding"))
        return FALSE;

    CHECKVER_OLE;

    if (FAILED(CoInitialize(NULL)))
        return FALSE;

    m_fInitialized=TRUE;

    if (!m_hInstPrev)
        {
        wc.style          = CS_HREDRAW | CS_VREDRAW;
        wc.lpfnWndProc    = MainWndProc;
        wc.cbClsExtra     = 0;
        wc.cbWndExtra     = 0;
        wc.hInstance      = m_hInst;
        wc.hIcon          = NULL;
        wc.hCursor        = NULL;
        wc.hbrBackground  = (HBRUSH)(COLOR_WINDOW + 1);
        wc.lpszMenuName   = NULL;
        wc.lpszClassName  = TEXT("SphereSquare");

        if (!RegisterClass(&wc))
            return FALSE;

        //Child window in which to draw
        wc.lpfnWndProc    = SquareWndProc;
        wc.cbWndExtra     = CBSQUAREWNDEXTRA;
        wc.hCursor        = (HCURSOR)LoadCursor(NULL, IDC_ARROW);
        wc.lpszClassName  = SZCLASSSQUARE;

        if (!RegisterClass(&wc))
            return FALSE;

        }

    //This window is never shown
    hWnd=CreateWindow(TEXT("SphereSquare"), TEXT("SphereSquare")
        , WS_OVERLAPPEDWINDOW, 100, 100, 400, 400
        , NULL, NULL, m_hInst, NULL);

    if (NULL==hWnd)
        return FALSE;

    g_hWnd=hWnd;

    m_pIClassFactory=new CSquareClassFactory(hWnd, m_hInst);

    if (NULL==m_pIClassFactory)
        return FALSE;

    m_pIClassFactory->AddRef();

    hr=CoRegisterClassObject(CLSID_SphereSquare, m_pIClassFactory
        , CLSCTX_LOCAL_SERVER, REGCLS_MULTIPLEUSE, &m_dwRegCO);

    if (FAILED(hr))
        return FALSE;

    return TRUE;
    }



//Class Factory implementation



/*
 * CSquareClassFactory::CSquareClassFactory
 * CSquareClassFactory::~CSquareClassFactory
 *
 * Constructor Parameters:
 *  hWnd            HWND of the application.
 *  hInst           HINSTANCE to pass to objects we create.
 */

CSquareClassFactory::CSquareClassFactory(HWND hWnd
    , HINSTANCE hInst)
    {
    m_cRef=0L;
    m_hWnd=hWnd;
    m_hInst=hInst;
    return;
    }


CSquareClassFactory::~CSquareClassFactory(void)
    {
    return;
    }




/*
 * CSquareClassFactory::QueryInterface
 * CSquareClassFactory::AddRef
 * CSquareClassFactory::Release
 */

STDMETHODIMP CSquareClassFactory::QueryInterface(REFIID riid
    , PPVOID ppv)
    {
    *ppv=NULL;

    if (IID_IUnknown==riid || IID_IClassFactory==riid)
        *ppv=this;

    if (NULL!=*ppv)
        {
        ((LPUNKNOWN)*ppv)->AddRef();
        return NOERROR;
        }

    return ResultFromScode(E_NOINTERFACE);
    }


STDMETHODIMP_(ULONG) CSquareClassFactory::AddRef(void)
    {
    return ++m_cRef;
    }


STDMETHODIMP_(ULONG) CSquareClassFactory::Release(void)
    {
    if (0!=--m_cRef)
        return m_cRef;

    delete this;
    return 0;
    }




/*
 * CSquareClassFactory::CreateInstance
 * CSquareClassFactory::LockServer
 */

STDMETHODIMP CSquareClassFactory::CreateInstance(LPUNKNOWN pUnkOuter
    , REFIID riid, PPVOID ppvObj)
    {
    PCSquare    pObj;
    HRESULT     hr;

    *ppvObj=NULL;

    if (NULL!=pUnkOuter)
        return ResultFromScode(CLASS_E_NOAGGREGATION);

    pObj=new CSquare();

    g_cObj++;
    hr=ResultFromScode(E_OUTOFMEMORY);

    if (NULL!=pObj)
        {
        if (pObj->Init(m_hWnd, m_hInst))
            {
            hr=pObj->QueryInterface(riid, ppvObj);
            }
        }

    if (FAILED(hr))
        {
        if (NULL!=pObj)
            delete pObj;

        ObjectDestroyed();
        }

    return hr;
    }



STDMETHODIMP CSquareClassFactory::LockServer(BOOL fLock)
    {
    if (fLock)
        g_cLock++;
    else
        {
        g_cLock--;

        //Centralizes shutdown in ObjectDestroyed
        g_cObj++;
        ObjectDestroyed();
        }

    return NOERROR;
    }



//Object implementation


/*
 * CSquare::CSquare
 * CSquare::~CSquare
 */

CSquare::CSquare(void)
    {
    m_cRef=0;
    m_hWnd=NULL;

    m_pITypeInfo=NULL;
    m_pIUnkDisp=NULL;

    m_cRadius=100.0;
    m_dDeclin=0.0;
    m_dTheta=0.0;

    m_xOrg=(int)(1.5*m_cRadius);
    m_yOrg=m_xOrg;

    m_crBack=GetSysColor(COLOR_WINDOW);
    m_crLinePos=RGB(255, 255, 0);
    m_crLineNeg=RGB(255, 0, 0);
    m_hPenPos=NULL;
    m_hPenNeg=NULL;

    m_cx=200;
    m_cy=220;
    m_xPos=100;
    m_yPos=100;

    return;
    }


CSquare::~CSquare(void)
    {
    ReleaseInterface(m_pITypeInfo);
    ReleaseInterface(m_pIUnkDisp);

    if (NULL!=m_hPenPos)
        DeleteObject(m_hPenPos);

    if (NULL!=m_hPenNeg)
        DeleteObject(m_hPenNeg);

    if (NULL!=m_hWnd)
        DestroyWindow(m_hWnd);

    return;
    }



/*
 * CSquare::Init
 *
 * Purpose:
 *  Creates the window in which we draw.
 */

BOOL CSquare::Init(HWND hWndOwner, HINSTANCE hInst)
    {
    ITypeLib       *pITypeLib;
    HRESULT         hr;

    //Create both default pens
    CreatePens(TRUE, TRUE);

    m_hWnd=CreateWindow(SZCLASSSQUARE, SZCLASSSQUARE
        , WS_CAPTION | WS_POPUP, m_xPos, m_yPos, m_cx, m_cy
        , hWndOwner, NULL, hInst, this);


    if (NULL==m_hWnd)
        return NULL;


    if (FAILED(LoadRegTypeLib(LIBID_SphereSquareLibrary, 1, 0
        , LANG_NEUTRAL, &pITypeLib)))
        {
        if (FAILED(LoadTypeLib(OLETEXT("SQUARE.TLB"), &pITypeLib)))
            return FALSE;
        }

    hr=pITypeLib->GetTypeInfoOfGuid(IID_ISphereSquare, &m_pITypeInfo);

    if (FAILED(hr))
        {
        pITypeLib->Release();
        return FALSE;
        }

    hr=CreateStdDispatch((IUnknown *)this, (ISphereSquare *)this
        , m_pITypeInfo, &m_pIUnkDisp);

    pITypeLib->Release();

    if (FAILED(hr))
        return FALSE;

    return TRUE;
    }




/*
 * CSquare::CreatePens
 *
 * Purpose:
 *  Creates one or both line color pens
 *
 * Parameters:
 *  fPositive       BOOL instructing us to create positive line color.
 *  fNegative       BOOL instructing us to create negative line color.
 *
 * Return Value:
 *  None
 */

void CSquare::CreatePens(BOOL fPositive, BOOL fNegative)
    {
    if (fPositive)
        {
        if (NULL!=m_hPenPos)
            DeleteObject(m_hPenPos);

        m_hPenPos=CreatePen(PS_SOLID, 1, m_crLinePos);

        if (NULL==m_hPenPos)
            m_hPenPos=(HPEN)GetStockObject(BLACK_PEN);
        }

    if (fNegative)
        {
        if (NULL!=m_hPenNeg)
            DeleteObject(m_hPenNeg);

        m_hPenNeg=CreatePen(PS_SOLID, 1, m_crLineNeg);

        if (NULL==m_hPenNeg)
            m_hPenNeg=(HPEN)GetStockObject(BLACK_PEN);
        }

    return;
    }




/*
 * CSquare::Draw
 *
 * Purpose:
 *  Draws the image of a square rotated according to m_dDeclin
 *  and m_dTheta with an edge length of m_cRadius.
 *
 * Parameters:
 *  hDC             HDC on which to draw.
 *
 * Return Value;
 *  None
 */

void CSquare::Draw(HDC hDC)
    {
    POINT           pt[5];
    int             x, y;
    double          rad;
    RECT            rc;
    HGDIOBJ         hGDI;

    SetBkColor(hDC, m_crBack);

    //Erase the background
    SetRect(&rc, 0, 0, m_xOrg*2, m_yOrg*2);
    ExtTextOut(hDC, 0, 0, ETO_OPAQUE, &rc, NULL, 0, NULL);

    rad=cos(m_dDeclin);

    x=(int)(m_cRadius*cos(m_dTheta));
    y=(int)(m_cRadius*rad*sin(m_dTheta));

    SETPOINT(pt[0], m_xOrg+x, m_yOrg+y);
    SETPOINT(pt[2], m_xOrg-x, m_yOrg-y);

    x=(int)(m_cRadius*cos(m_dTheta+PI/2));
    y=(int)(m_cRadius*rad*sin(m_dTheta+PI/2));

    SETPOINT(pt[3], m_xOrg+x, m_yOrg+y);
    SETPOINT(pt[1], m_xOrg-x, m_yOrg-y);

    pt[4]=pt[0];

    /*
     * Set the line color according to which side of the square
     * is facing out of the screen.  We'll draw the positive
     * z lines a yellow (default), the negative face red
     * (default).  Both colors can be changed by the controller.
     *
     * To determine which side is out, we only have to look at
     * the rad value which is cos(m_dDeclin).  If positive, then
     * we're in the positive range.
     */

    hGDI=SelectObject(hDC, (rad > 0) ? m_hPenPos : m_hPenNeg);
    Polyline(hDC, pt, sizeof(pt)/sizeof(POINT));

    SelectObject(hDC, GetStockObject(WHITE_PEN));
    MoveToEx(hDC, m_xOrg, m_yOrg, NULL);
    LineTo(hDC, pt[0].x, pt[0].y);

    SelectObject(hDC, hGDI);
    return;
    }




/*
 * SquareWndProc
 *
 * Purpose:
 *  Window procedure for the Square window.
 */

LRESULT APIENTRY SquareWndProc(HWND hWnd, UINT iMsg, WPARAM wParam
    , LPARAM lParam)
    {
    PCSquare    pcp;
    PAINTSTRUCT         ps;
    HDC                 hDC;
    RECT                rc;

    pcp=(PCSquare)GetWindowLong(hWnd, SQWL_STRUCTURE);

    switch (iMsg)
        {
        case WM_CREATE:
            pcp=(PCSquare)((LPCREATESTRUCT)lParam)
                ->lpCreateParams;
            SetWindowLong(hWnd, SQWL_STRUCTURE, (LONG)pcp);
            break;

        case WM_ERASEBKGND:
            hDC=(HDC)wParam;
            SetBkColor(hDC, pcp->m_crBack);
            GetClientRect(hWnd, &rc);
            ExtTextOut(hDC, 0, 0, ETO_OPAQUE, &rc, NULL, 0, NULL);
            break;

        case WM_PAINT:
            hDC=BeginPaint(hWnd, &ps);
            pcp->Draw(hDC);
            EndPaint(hWnd, &ps);
            break;

        case WM_CLOSE:
            /*
             * Eat this or Alt+F4 can destroy the window, even
             * though we don't have a system menu.
             */
            break;

        default:
            return DefWindowProc(hWnd, iMsg, wParam, lParam);
        }

    return 0L;
    }






/*
 * CSquare::QueryInterface
 * CSquare::AddRef
 * CSquare::Release
 *
 * Purpose:
 *  IUnknown members for CSquare object.
 */

STDMETHODIMP CSquare::QueryInterface(REFIID riid, PPVOID ppv)
    {
    *ppv=NULL;

    if (IID_IUnknown==riid || IID_ISphereSquare==riid)
        *ppv=this;

    if (IID_IDispatch==riid || DIID_DISphereSquare==riid)
        return m_pIUnkDisp->QueryInterface(IID_IDispatch, ppv);

    if (NULL!=*ppv)
        {
        ((IUnknown *)*ppv)->AddRef();
        return NOERROR;
        }

    return ResultFromScode(E_NOINTERFACE);
    }


STDMETHODIMP_(ULONG) CSquare::AddRef(void)
    {
    return ++m_cRef;
    }


STDMETHODIMP_(ULONG) CSquare::Release(void)
    {
    if (0L!=--m_cRef)
        return m_cRef;

    ObjectDestroyed();
    delete this;
    return 0L;
    }



//ISphereSquare members

STDMETHODIMP_(double) CSquare::get_Radius(void)
    {
    return m_cRadius;
    }

STDMETHODIMP_(void) CSquare::put_Radius(double cRadius)
    {
    //Only use positive radii.
    if (cRadius > 0.0)
        m_cRadius=cRadius;

    //We'll be lazy and not throw exceptions.
    return;
    }


STDMETHODIMP_(double) CSquare::get_Theta(void)
    {
    return m_dTheta;
    }

STDMETHODIMP_(void) CSquare::put_Theta(double dTheta)
    {
    //Anything is valid when you do trig
    m_dTheta=dTheta;
    return;
    }


STDMETHODIMP_(double) CSquare::get_Declination(void)
    {
    return m_dDeclin;
    }

STDMETHODIMP_(void) CSquare::put_Declination(double dDeclin)
    {
    m_dDeclin=dDeclin;
    return;
    }


STDMETHODIMP_(long) CSquare::get_BackColor(void)
    {
    return m_crBack;
    }

STDMETHODIMP_(void) CSquare::put_BackColor(long crBack)
    {
    m_crBack=crBack;
    return;
    }


STDMETHODIMP_(long) CSquare::get_LineColorPositive(void)
    {
    return m_crLinePos;
    }

STDMETHODIMP_(void) CSquare::put_LineColorPositive(long crLinePos)
    {
    m_crLinePos=crLinePos;
    return;
    }


STDMETHODIMP_(long) CSquare::get_LineColorNegative(void)
    {
    return m_crLineNeg;
    }

STDMETHODIMP_(void) CSquare::put_LineColorNegative(long crLineNeg)
    {
    m_crLineNeg=crLineNeg;
    return;
    }


STDMETHODIMP_(void) CSquare::Draw(void)
    {
    InvalidateRect(m_hWnd, NULL, FALSE);
    UpdateWindow(m_hWnd);
    return;
    }

STDMETHODIMP_(void) CSquare::SetCenterPoint(int cx, int cy)
    {
    //No validation...we're deing lazy
    m_xOrg=cx;
    m_yOrg=cy;
    return;
    }

STDMETHODIMP_(void) CSquare::ShowWindow(int nCmdShow)
    {
    ::ShowWindow(m_hWnd, nCmdShow);
    UpdateWindow(m_hWnd);
    return;
    }

STDMETHODIMP_(void) CSquare::SetWindowPosition(int xPos, int yPos)
    {
    m_xPos=xPos;
    m_yPos=yPos;

    SetWindowPos(m_hWnd, NULL, m_xPos, m_yPos, 0, 0
        , SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
    return;
    }

STDMETHODIMP_(void) CSquare::SetWindowSize(int cx, int cy)
    {
    m_cx=cx;
    m_cy=cy;

    SetWindowPos(m_hWnd, NULL, 0, 0, m_cx, m_cy
        , SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
    return;
    }
