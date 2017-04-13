/*
 * AUTOAPP.CPP
 * Cosmo Chapter 14
 *
 * "Application" object for Cosmo's OLE Automation support, based
 * on CAutoBase which handles the type information and IDispatch
 * part of the object.  What is here are the specific properties
 * and methods for the "Application" object.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Right Reserved.
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  INTERNET>kraigb@microsoft.com
 */


#include "cosmo.h"


/*
 * CAutoApp::CAutoApp
 *
 * Constructor Parameters:
 *  pFR             PCCosmoFrame to the frame object that we use
 *                  to implement much of this interface.
 */

CAutoApp::CAutoApp(PCCosmoFrame pFR)
    : CAutoBase(pFR, pFR->m_hInst, IID_ICosmoApplication
    , DIID_DICosmoApplication, ObjectDestroyed)
    {
    m_fQuitCalled=FALSE;
    return;
    }


/*
 * CAutoApp::QueryInterface
 * CAutoApp::AddRef
 * CAutoApp::Release
 */

STDMETHODIMP CAutoApp::QueryInterface(REFIID riid, PPVOID ppv)
    {
    *ppv=NULL;

    if (IID_IUnknown==riid || IID_ICosmoApplication==riid)
        *ppv=(IUnknown *)this;

    if (IID_IDispatch==riid || m_diid==riid)
        *ppv=m_pImpIDispatch;

    if (IID_IExternalConnection==riid)
        *ppv=m_pImpIExtConn;

    if (NULL!=*ppv)
        {
        ((LPUNKNOWN)*ppv)->AddRef();
        return NOERROR;
        }

    return ResultFromScode(E_NOINTERFACE);
    }

STDMETHODIMP_(ULONG) CAutoApp::AddRef(void)
    {
    return ++m_cRef;
    }


STDMETHODIMP_(ULONG) CAutoApp::Release(void)
    {
    if (0L!=--m_cRef)
        return m_cRef;

    if (!m_fQuitCalled && NULL!=m_pfnDestroy)
        (*m_pfnDestroy)();

    delete this;
    return 0L;
    }


/*
 * CAutoApp::VTableInterface
 *
 * Purpose:
 *  Returns the right vtable pointer to use when calling
 *  ITypeInfo::Invoke (see CImpIDispatch::Invoke in AUTOBASE.CPP).
 */

void *CAutoApp::VTableInterface(void)
    {
    return (ICosmoApplication *)this;
    }


//All that follows is the ICosmoApplication implementation

/*
 * CAutoApp::Application
 * Property, read-only
 *
 * Returns our own IDispatch for use with DISPID_VALUE.
 */

STDMETHODIMP_(IDispatch *) CAutoApp::get_Application(void)
    {
    void       *pv;

    //This will set pv to NULL on failure
    QueryInterface(IID_IDispatch, &pv);
    return (IDispatch *)pv;
    }



/*
 * CAutoApp::ActiveFigure
 * Property, read-only
 *
 * Returns the active document's IDispatch
 */

STDMETHODIMP_(IDispatch *) CAutoApp::get_ActiveFigure(void)
    {
    void           *pv=NULL;
    PCCosmoDoc      pDoc;
    PCAutoFigure    pFig;

    pDoc=(PCCosmoDoc)((PCCosmoClient)m_pFR->m_pCL)->ActiveDocument();

    if (NULL==pDoc)
        return NULL;

    pFig=pDoc->AutoFigure();

    if (NULL!=pFig)
        pFig->QueryInterface(IID_IDispatch, &pv);

    return (IDispatch *)pv;
    }



/*
 * CAutoApp::Caption
 * Property, read-only
 *
 * Retrieve the application's caption bar
 */

STDMETHODIMP_(BSTR) CAutoApp::get_Caption(void)
    {
    const int   cch=256;
    TCHAR       szCaption[cch];

    GetWindowText(m_pFR->Window(), szCaption, cch);

   #ifdef WIN32ANSI
    OLECHAR     szTemp[cch];

    MultiByteToWideChar(CP_ACP, 0, szCaption, -1, szTemp, cch);
    return SysAllocString(szTemp);
   #else
    return SysAllocString(szCaption);
   #endif
    }




/*
 * CAutoApp::Figures
 * Property, read-only
 *
 * Retrieve the collection object for figures (documents)
 */

STDMETHODIMP_(IDispatch *) CAutoApp::get_Figures(void)
    {
    void            *pv=NULL;
    PCAutoFigures    pFigs;

    pFigs=((PCCosmoClient)m_pFR->m_pCL)->AutoFigures();

    if (NULL!=pFigs)
        pFigs->QueryInterface(IID_IDispatch, &pv);

    return (IDispatch *)pv;
    }



/*
 * CAutoApp::FullName, Name, Path
 * Properties, read-only
 *
 * Retrieve the full pathname of the application module (FullName),
 * just the module name (Name), or just the path (Path).
 */

STDMETHODIMP_(BSTR) CAutoApp::get_FullName(void)
    {
    const int   cch=512;
    TCHAR       szModule[cch];

    GetModuleFileName(m_pFR->Instance(), szModule, cch);

   #ifdef WIN32ANSI
    OLECHAR     szTemp[cch];
    MultiByteToWideChar(CP_ACP, 0, szModule, -1, szTemp, cch);
    return SysAllocString(szTemp);
   #else
    return SysAllocString(szModule);
   #endif
    }


STDMETHODIMP_(BSTR) CAutoApp::get_Name(void)
    {
    BSTR        bstrFull=NULL;
    BSTR        bstrName=NULL;
    const int   cch=256;
    TCHAR       szName[256];

    //Get the full path
    bstrFull=get_FullName();

    if (NULL==bstrFull)
        return NULL;

    //Now retrieve just the filename
   #ifdef WIN32ANSI
    char        szTemp[cch];
    OLECHAR     szTempW[cch];

    WideCharToMultiByte(CP_ACP, 0, bstrFull, -1, szTemp
        , cch, NULL, NULL);
    if (0==GetFileTitle(szTemp, szName, cch))
        {
        MultiByteToWideChar(CP_ACP, 0, szName, -1, szTempW, cch);
        bstrName=SysAllocString(szTempW);
        }
   #else
    if (0==GetFileTitle(bstrFull, szName, cch))
        bstrName=SysAllocString(szName);
   #endif

    SysFreeString(bstrFull);
    return bstrName;
    }


STDMETHODIMP_(BSTR) CAutoApp::get_Path(void)
    {
    BSTR        bstrFull=NULL;
    BSTR        bstrName=NULL;
    BSTR        bstrPath=NULL;

    bstrFull=get_FullName();

    if (NULL==bstrFull)
        return NULL;

    bstrName=get_Name();

    if (NULL!=bstrName)
        {
        LPOLESTR    psz;

        /*
         * Find the position of bstrName in bstrFull then copy
         * only charaters up to that point into bstrPath.
         */
       #ifdef WIN32ANSI
        psz=wcsstr(bstrFull, bstrName);
       #else
        psz=_tcsstr(bstrFull, bstrName);
       #endif

        //The -1 accounts for the \ before the filename
        bstrPath=SysAllocStringLen(bstrFull
            , ((DWORD)psz-(DWORD)bstrFull)/sizeof(OLECHAR)-1);
        SysFreeString(bstrName);
        }

    SysFreeString(bstrFull);
    return bstrPath;
    }



/*
 * CAutoApp::Left, Top, Width, Height
 * Properties, read-write
 *
 * Horizontal (Left) and vertical (Top) positions of the frame
 * window from the left and top edges of the screen; horizontal
 * (Width) and  vertical (Height) dimensions of the frame
 * window.  All of these functions call our private member
 * MoveSize, a helper function.
 */

STDMETHODIMP_(long) CAutoApp::get_Left(void)
    {
    return MoveSize(MOVESIZEACTION_GETLEFT, 0, 0, 0, 0);
    }

STDMETHODIMP_(void) CAutoApp::put_Left(long x)
    {
    MoveSize(MOVESIZEACTION_LEFT, x, 0, 0, 0);
    return;
    }

STDMETHODIMP_(long) CAutoApp::get_Top(void)
    {
    return MoveSize(MOVESIZEACTION_GETTOP, 0, 0, 0, 0);
    }

STDMETHODIMP_(void) CAutoApp::put_Top(long y)
    {
    MoveSize(MOVESIZEACTION_TOP, 0, y, 0, 0);
    return;
    }

STDMETHODIMP_(long) CAutoApp::get_Width(void)
    {
    return MoveSize(MOVESIZEACTION_GETWIDTH, 0, 0, 0, 0);
    }

STDMETHODIMP_(void) CAutoApp::put_Width(long cx)
    {
    MoveSize(MOVESIZEACTION_WIDTH, 0, 0, cx, 0);
    return;
    }

STDMETHODIMP_(long) CAutoApp::get_Height(void)
    {
    return MoveSize(MOVESIZEACTION_GETHEIGHT, 0, 0, 0, 0);
    }

STDMETHODIMP_(void) CAutoApp::put_Height(long cy)
    {
    MoveSize(MOVESIZEACTION_HEIGHT, 0, 0, 0, cy);
    return;
    }




/*
 * CAutoApp::Visible
 * Properties, read-write
 *
 * Controls visibility of the frame window (which is hidden by
 * default when the application is launched for Automation.
 */

STDMETHODIMP_(VARIANT_BOOL) CAutoApp::get_Visible(void)
    {
    return (VARIANT_BOOL)IsWindowVisible(m_pFR->Window());
    }

STDMETHODIMP_(void) CAutoApp::put_Visible(VARIANT_BOOL fShow)
    {
    ShowWindow(m_pFR->Window(), fShow ? SW_SHOW : SW_HIDE);
    return;
    }



/*
 * CAutoApp::StatusBar
 * Properties, read-write
 *
 * Retrieve or modify the status line text.
 * default when the application is launched for Automation.
 */

STDMETHODIMP_(BSTR) CAutoApp::get_StatusBar(void)
    {
    const int   cch=256;
    TCHAR       szText[cch];
    BSTR        bstrText=NULL;

   #ifdef WIN32ANSI
    if (0!=m_pFR->StatusLine()->MessageGet(szText, cch))
        {
        OLECHAR szTemp[cch];

        MultiByteToWideChar(CP_ACP, 0, szText, -1, szTemp, cch);
        bstrText=SysAllocString(szTemp);
        }
   #else
    if (0!=m_pFR->StatusLine()->MessageGet(szText, cch))
        bstrText=SysAllocString(szText);
   #endif

    return bstrText;
    }

STDMETHODIMP_(void) CAutoApp::put_StatusBar(BSTR bstrText)
    {
    if (NULL==bstrText)
        return;

   #ifdef WIN32ANSI
    char    szTemp[256];

    WideCharToMultiByte(CP_ACP, 0, bstrText, -1, szTemp, 256
        , NULL, NULL);
    m_pFR->StatusLine()->MessageSet(szTemp);
   #else
    m_pFR->StatusLine()->MessageSet(bstrText);
   #endif
    return;
    }



/*
 * CAutoApp::Quit
 * Method
 *
 * Instructs the application to terminate.  This behaves as
 * if the user closes the app directly.
 */

STDMETHODIMP_(void) CAutoApp::Quit(void)
    {
    ObjectDestroyed();
    m_fQuitCalled=TRUE;
    return;
    }


/*
 * CAutoApp::MoveSize
 *
 * Purpose:
 *  Helper function for the Left, Top, Width, and Height properties
 *  that centralizes calls to GetWindowRect and SetWindowPos,
 *  reducing overall code somewhat.
 *
 * Parameters:
 *  iAction         MOVESIZEACTION enum value to indicate what
 *                  type of moving/sizing to perform
 *  x, y            long position coordinates;  x is only meaningful
 *                  with MOVESIZEACTION_LEFT, y only with _TOP
 *  cx, cy          long extents;  cx is only meaningful
 *                  with MOVESIZEACTION_WIDTH, cy only with _HEIGHT
 *
 * Return Value:
 *  long            The current x, y, cx, or cy value depending on
 *                  iAction being _GETLEFT, _GETTOP, _GETWIDTH, or
 *                  _GETHEIGHT.
 */

long CAutoApp::MoveSize(MOVESIZEACTION iAction, long x, long y
    , long cx, long cy)
    {
    RECT        rc;
    long        x1, y1, cx1, cy1;
    UINT        uFlags;

    GetWindowRect(m_pFR->Window(), &rc);

    //By default we'll do nothing
    x1=rc.left;
    y1=rc.top;
    cx1=rc.right-rc.left;
    cy1=rc.bottom-rc.top;
    uFlags=0L;

    switch (iAction)
        {
        /*
         * Each individual property modifies the appropriate
         * variable x1, y1, cx1, cy1, as well as uFlags to set
         * up SetWindowPos call.
         */
        case MOVESIZEACTION_LEFT:
            x1=x;
            uFlags=SWP_NOSIZE;
            break;

        case MOVESIZEACTION_TOP:
            y1=y;
            uFlags=SWP_NOSIZE;
            break;

        case MOVESIZEACTION_WIDTH:
            cx1=cx;
            uFlags=SWP_NOMOVE;
            break;

        case MOVESIZEACTION_HEIGHT:
            cy1=cy;
            uFlags=SWP_NOMOVE;
            break;


        case MOVESIZEACTION_GETLEFT:
            return rc.left;

        case MOVESIZEACTION_GETTOP:
            return rc.top;

        case MOVESIZEACTION_GETWIDTH:
            return rc.right-rc.left;

        case MOVESIZEACTION_GETHEIGHT:
            return rc.bottom-rc.top;

        default:
            return 0;
        }

    //We only get here on propety changes
    SetWindowPos(m_pFR->Window(), NULL
        , (int)x1, (int)y1, (int)cx1, (int)cy1
        , SWP_NOZORDER | SWP_NOACTIVATE | uFlags);

    //Irrelevant for property changes.
    return 0;
    }
