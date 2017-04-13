/*
 * AUTOCLI2.CPP
 * Automation Client with Property Pages Chapter 16
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#define INITGUIDS
#include "autocli2.h"


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
 * AutoClientWndProc
 *
 * Purpose:
 *  Window class procedure.  Standard callback.
 */

LRESULT APIENTRY AutoClientWndProc(HWND hWnd, UINT iMsg
    , WPARAM wParam, LPARAM lParam)
    {
    PCApp           pApp;
    WORD            wID;
    DISPID          dispID, dispIDParam;
    DISPPARAMS      dp;
    VARIANTARG      va;
    EXCEPINFO       exInfo;
    UINT            uErr;
    HRESULT         hr;
    TCHAR           szMsg[80];

    pApp=(PCApp)GetWindowLong(hWnd, AUTOCLI2WL_STRUCTURE);

    switch (iMsg)
        {
        case WM_NCCREATE:
            pApp=(PCApp)(((LPCREATESTRUCT)lParam)->lpCreateParams);
            SetWindowLong(hWnd, AUTOCLI2WL_STRUCTURE, (LONG)pApp);
            return (DefWindowProc(hWnd, iMsg, wParam, lParam));

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        case WM_COMMAND:
            wID=LOWORD(wParam);

            switch (wID)
                {
                case IDM_GETSOUND:
                    //Find the dispID we need
                    hr=pApp->NameToID(OLETEXT("Sound"), &dispID);

                    if (FAILED(hr))
                        break;

                    //Get the property
                    SETNOPARAMS(dp);
                    hr=pApp->Invoke(dispID, DISPATCH_PROPERTYGET
                        , &dp, &va, &exInfo, NULL);

                    if (SUCCEEDED(hr))
                        {
                        wsprintf(szMsg, TEXT("Current 'Sound' is 0x%lX")
                            , va.lVal);
                        }
                    else
                        {
                        wsprintf(szMsg
                            , TEXT("Get 'Sound' failed with 0x%lX")
                            , hr);
                        }

                    pApp->Message(szMsg);
                    break;

                case IDM_SETSOUNDDEFAULT:
                case IDM_SETSOUNDHAND:
                case IDM_SETSOUNDQUESTION:
                case IDM_SETSOUNDEXCLAMATION:
                case IDM_SETSOUNDASTERISK:
                case IDM_SETSOUNDBOGUS:
                    //Find the dispID we need
                    hr=pApp->NameToID(OLETEXT("Sound"), &dispID);

                    if (FAILED(hr))
                        break;

                    /*
                     * Call IDispatch::Invoke passing wID which
                     * is a sound identifier (IDM_SETSOUNDDEFAULT
                     * has to set the sound to zero).  The "bogus"
                     * sound should cause an exception.
                     */

                    //Initialize arguments
                    VariantInit(&va);
                    va.vt=VT_I4;
                    va.lVal=(IDM_SETSOUNDDEFAULT==wID)
                        ? 0L : (long)(wID);

                    /*
                     * Passing a named DISPID_PROPERTYPUT
                     * is required when setting properties.
                     */
                    dispIDParam=DISPID_PROPERTYPUT;
                    SETDISPPARAMS(dp, 1, &va, 1, &dispIDParam);

                    hr=pApp->Invoke(dispID, DISPATCH_PROPERTYPUT
                        , &dp, NULL, &exInfo, NULL);

                    /*
                     * Success messages come through
                     * IPropertyNotifySink::OnChanged.
                     */
                    if (FAILED(hr))
                        {
                        wsprintf(szMsg
                            , TEXT("Set 'Sound' failed with 0x%lX"), hr);
                        }

                    break;

                case IDM_BEEP:
                    if (NULL==pApp->m_pIDispatch)
                        break;

                    hr=pApp->NameToID(OLETEXT("Beep"), &dispID);

                    if (FAILED(hr))
                        break;

                    SETNOPARAMS(dp);
                    hr=pApp->Invoke(dispID, DISPATCH_METHOD, &dp
                        , &va, &exInfo, &uErr);

                    /*
                     * va will have the sound played as the return
                     * value of the Beep method.
                     */
                    if (SUCCEEDED(hr))
                        {
                        wsprintf(szMsg, TEXT("'Beep' played 0x%lX")
                            , va.lVal);
                        }
                    else
                        {
                        wsprintf(szMsg
                            , TEXT("'Beep' failed with 0x%lX"), hr);
                        }

                    pApp->Message(szMsg);
                    break;

                //CHAPTER16MOD
                case IDM_PROPERTIES:
                    pApp->ShowProperties();
                    break;

                case IDM_ENFORCEREADONLY:
                    pApp->m_fReadOnly=!pApp->m_fReadOnly;
                    CheckMenuItem(GetMenu(hWnd), wID
                        , pApp->m_fReadOnly
                        ? MF_CHECKED : MF_UNCHECKED);
                    break;
                //End CHAPTER16MOD

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
 *
 */

CApp::CApp(HINSTANCE hInst, HINSTANCE hInstPrev
    , UINT nCmdShow)
    {
    m_hInst=hInst;
    m_hInstPrev=hInstPrev;
    m_nCmdShow=nCmdShow;

    m_hWnd=NULL;
    m_fInitialized=FALSE;
    m_lcid=GetUserDefaultLCID();

    m_szHelpDir[0]=(TCHAR)0;
    m_pIDispatch=NULL;

    //CHAPTER16MOD
    m_fReadOnly=FALSE;
    m_pSink=NULL;
    m_pIConnPt=NULL;
    m_dwConn=0L;
    //End CHAPTER16MOD

    return;
    }


CApp::~CApp(void)
    {
    //CHAPTER16MOD
    if (0!=m_dwConn && NULL!=m_pIConnPt)
        {
        m_pIConnPt->Unadvise(m_dwConn);
        ReleaseInterface(m_pIConnPt);
        }

    ReleaseInterface(m_pSink);
    //End CHAPTER16MOD

    if (NULL!=m_pIDispatch)
        {
        m_pIDispatch->Release();
        m_pIDispatch=NULL;
        }

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
    HRESULT     hr;

    CHECKVER_OLE;

    if (FAILED(CoInitialize(NULL)))
        return FALSE;

    m_fInitialized=TRUE;

    if (!m_hInstPrev)
        {
        wc.style          = CS_HREDRAW | CS_VREDRAW;
        wc.lpfnWndProc    = AutoClientWndProc;
        wc.cbClsExtra     = 0;
        wc.cbWndExtra     = CBWNDEXTRA;
        wc.hInstance      = m_hInst;
        wc.hIcon          = LoadIcon(m_hInst, TEXT("Icon"));
        wc.hCursor        = LoadCursor(NULL, IDC_ARROW);
        wc.hbrBackground  = (HBRUSH)(COLOR_WINDOW + 1);
        wc.lpszMenuName   = MAKEINTRESOURCE(IDR_MENU);
        wc.lpszClassName  = TEXT("AUTOCLI");

        if (!RegisterClass(&wc))
            return FALSE;
        }

    m_hWnd=CreateWindow(TEXT("AUTOCLI")
        , TEXT("Property Page Client"), WS_OVERLAPPEDWINDOW
        , 35, 35, 450, 250, NULL, NULL, m_hInst, this);

    if (NULL==m_hWnd)
        return FALSE;

    //Create the beeper object we want to manipulate.
    hr=CoCreateInstance(CLSID_Beeper, NULL, CLSCTX_INPROC_SERVER
        , IID_IDispatch, (PPVOID)&m_pIDispatch);

    if (FAILED(hr))
        {
        Message(TEXT("Failed to create object--terminating"), MB_OK);
        return FALSE;
        }

    //Try to get the help directory for the object's type information
    HelpDirFromCLSID(CLSID_Beeper, m_szHelpDir);

    //CHAPTER16MOD
    /*
     * Try to hook up our IPropertyNotifySink to the object.
     * On failure, we'll just gray out "Enforce Read-Only" on
     * the menu, but otherwise we continue to run.
     */
    m_pSink=new CPropertyNotifySink(this);

    if (NULL!=m_pSink)
        {
        IConnectionPointContainer  *pICPC;
        HRESULT                     hr;

        m_pSink->AddRef();  //Release destroys it

        hr=m_pIDispatch->QueryInterface(IID_IConnectionPointContainer
            , (void **)&pICPC);

        if (SUCCEEDED(hr))
            {
            if (SUCCEEDED(pICPC->FindConnectionPoint
                (IID_IPropertyNotifySink, &m_pIConnPt)))
                {
                /*
                 * This is the only way m_dwConn is set to non-
                 * zero.  We hold onto m_pIConnPt until we close.
                 */
                m_pIConnPt->Advise(m_pSink, &m_dwConn);
                }

            pICPC->Release();
            }
        }

    if (0==m_dwConn)
        {
        EnableMenuItem(GetMenu(m_hWnd), IDM_ENFORCEREADONLY
            , MF_DISABLED | MF_GRAYED | MF_BYCOMMAND);
        }
    //End CHAPTER16MOD

    ShowWindow(m_hWnd, m_nCmdShow);
    UpdateWindow(m_hWnd);

    return TRUE;
    }



/*
 * CApp::NameToID
 *
 * Purpose:
 *  Calls IDispatch::GetIDsOfNames for a single name to determine
 *  the DISPID to pass to IDispatch::Invoke.
 *
 * Parameters:
 *  pszName         OLECHAR * to the name to map.
 *  pDispID         DISPID * in which to store the dispID.
 *
 * Return Value:
 *  HRESULT         Return value of GetIDsOfNames
 */

HRESULT CApp::NameToID(OLECHAR *pszName, DISPID *pDispID)
    {
    HRESULT     hr;
    TCHAR       szMsg[80];

    hr=m_pIDispatch->GetIDsOfNames(IID_NULL, &pszName, 1
        , m_lcid, pDispID);

    if (FAILED(hr))
        {
        wsprintf(szMsg
            , TEXT("GetIDsOfNames on '%s' failed with 0x%lX")
            , pszName, hr);
        Message(szMsg);
        }

    return hr;
    }




/*
 * CApp::Invoke
 *
 * Purpose:
 *  Calls IDispatch::Invoke using the interface pointer we hold
 *  and using some default parameters.  All the other parameters
 *  to this function are passed straight to Invoke
 *
 * Return Value:
 *  HRESULT         Return value of Invoke.  If DISP_E_EXCEPTION,
 *                  this function generates the appropriate
 *                  message box.
 */

HRESULT CApp::Invoke(DISPID dispID, WORD wFlags, DISPPARAMS *pdp
    , VARIANT *pva, EXCEPINFO *pExInfo, UINT *puErr)
    {
    HRESULT     hr;
    LPTSTR      pszMsg=NULL;
    LPTSTR      pszFmt=NULL;
    UINT        uRet;
    UINT        uStyle;
    TCHAR       szSource[80];

    if (NULL==m_pIDispatch)
        return ResultFromScode(E_POINTER);

    hr=m_pIDispatch->Invoke(dispID, IID_NULL, m_lcid, wFlags
        , pdp, pva, pExInfo, puErr);

    if (DISP_E_EXCEPTION!=GetScode(hr))
        return hr;

    //If we're given a deferred filling function, fill now.
    if (NULL!=pExInfo->pfnDeferredFillIn)
        (*pExInfo->pfnDeferredFillIn)(pExInfo);

    /*
     * To handle the exception, display a message box with the
     * controller's name in the caption and a message:
     *
     *      "Error <code> in <source>:  <description>"
     *
     * where <error> is the exception code in pExInfo->wCode or
     * pExInfo->scode, <source> is the value of the ProdID
     * in pExInfo->bstrSource and <description> is in
     * pExInfo->bstrDescription.
     *
     * For simplicity, we assume that if description is set, so is
     * source.
     *
     * To be complete, if pExInfo->bstrHelpFile is non-NULL,
     * display a Help button.  If Help is pressed, launch WinHelp
     * with that filename and pExInfo->dwHelpContext.
     */

    //Go get the real source name from the ProgID
    lstrcpy(szSource, TEXT("Unknown"));

    if (NULL!=pExInfo->bstrSource)
        {
        LONG    lRet;

        //If this doesn't work, we'll have "Unknown" anyway
       #ifdef WIN32ANSI
        char        szTemp[80];
        WideCharToMultiByte(CP_ACP, 0, pExInfo->bstrSource, -1
            , szTemp, 80, NULL, NULL);
        RegQueryValue(HKEY_CLASSES_ROOT, szTemp, szSource, &lRet);
       #else
        RegQueryValue(HKEY_CLASSES_ROOT, pExInfo->bstrSource
            , szSource, &lRet);
       #endif

        SysFreeString(pExInfo->bstrSource);
        }

    if (NULL!=pExInfo->bstrDescription)
        {
        pszFmt=(LPTSTR)malloc(CCHSTRINGMAX*sizeof(TCHAR));

       #ifdef WIN32ANSI
        UINT    cch;
        char   *pszDesc;

        cch=wcslen(pExInfo->bstrDescription);
        pszDesc=(LPSTR)malloc(cch);

        WideCharToMultiByte(CP_ACP, 0, pExInfo->bstrDescription, -1
            , pszDesc, cch, NULL, NULL);

        pszMsg=(LPTSTR)malloc(CCHSTRINGMAX+lstrlen(szSource)+cch);
       #else
        pszMsg=(LPTSTR)malloc((CCHSTRINGMAX+lstrlen(szSource)
            +lstrlen(pExInfo->bstrDescription))*sizeof(TCHAR));
       #endif

        if (0==pExInfo->wCode)
            {
            //Formatting for SCODE errors
            LoadString(m_hInst, IDS_MESSAGEEXCEPTIONSCODE, pszFmt
                , CCHSTRINGMAX);
            wsprintf(pszMsg, pszFmt, (long)pExInfo->scode
                , (LPTSTR)szSource
               #ifdef WIN32ANSI
                , pszDesc);
               #else
                , (LPTSTR)pExInfo->bstrDescription);
               #endif

            }
        else
            {
            //Formatting for wCode errors
            LoadString(m_hInst, IDS_MESSAGEEXCEPTION, pszFmt
                , CCHSTRINGMAX);
            wsprintf(pszMsg, pszFmt, (UINT)pExInfo->wCode
                , (LPTSTR)szSource
               #ifdef WIN32ANSI
                , pszDesc);
               #else
                , (LPTSTR)pExInfo->bstrDescription);
               #endif
            }

        free(pszFmt);
        }
    else
        {
        pszMsg=(LPTSTR)malloc(CCHSTRINGMAX*sizeof(TCHAR));
        LoadString(m_hInst, IDS_MESSAGEUNKNOWNEXCEPTION, pszMsg
            , CCHSTRINGMAX);
        }

    /*
     * In Windows 95 there is an MB_HELP style that we use in the
     * exception message if pExInfo->bstrHelpFile is non-NULL.  For
     * Windows NT 3.5 and Windows 3.1x, we'll just use a Cancel
     * button to demonstrate since making a Help button is too much
     * effort for this sample (requires a custom dialog box and code
     * to resize the dialog based on the length of the description
     * string which MessageBox does automatically...)
     */
    uStyle=MB_OK | MB_ICONEXCLAMATION;

   #ifdef MB_HELP
    uStyle |=(NULL!=pExInfo->bstrHelpFile) ? MB_HELP : 0;
   #else
    uStyle |=(NULL!=pExInfo->bstrHelpFile) ? MB_OKCANCEL : 0;
   #endif

    uRet=Message(pszMsg, uStyle);

    if (NULL!=pszMsg)
        free(pszMsg);

   #ifdef MB_HELP
    if (IDHELP==uRet)
   #else
    if (IDCANCEL==uRet)
   #endif
        {
        TCHAR       szHelp[512];

        /*
         * If we read a HELPDIR, prepend it to the file.  Otherwise
         * just use the string we got since that's all we have.
         */
        if ((TCHAR)0!=m_szHelpDir[0])
            {
		   #ifdef WIN32ANSI
		    char    szTemp[256];

            WideCharToMultiByte(CP_ACP, 0, pExInfo->bstrHelpFile
                , -1, szTemp, 256, NULL, NULL);
            wsprintf(szHelp, TEXT("%s\\%s"), m_szHelpDir, szTemp);
           #else
            wsprintf(szHelp, TEXT("%s\\%s"), m_szHelpDir
                , pExInfo->bstrHelpFile);
		   #endif
            }
        else
           #ifdef WIN32ANSI
            WideCharToMultiByte(CP_ACP, 0, pExInfo->bstrHelpFile
                , -1, szHelp, 512, NULL, NULL);
           #else
            lstrcpy(szHelp, pExInfo->bstrHelpFile);
           #endif

        WinHelp(NULL, szHelp, HELP_CONTEXT, pExInfo->dwHelpContext);
        }

    //We're responsible for cleaning up the strings.
    SysFreeString(pExInfo->bstrDescription);
    SysFreeString(pExInfo->bstrHelpFile);

    return ResultFromScode(DISP_E_EXCEPTION);
    }



/*
 * CApp::Message (overloaded)
 *
 * Purpose:
 *  Scribbles a message onto the client area of the window
 *  or displays the message in a message box if a message
 *  box style is given.
 *
 * Parameters:
 *  pszMsg          LPTSTR to the message string.
 *  uStyle          (message box only) UINT style bits
 *
 * Return Value:
 *  UINT            Return value of MessageBox (MessageBox version
 *                  only)
 */

void CApp::Message(LPTSTR pszMsg)
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

    ExtTextOut(hDC, 0, 0, ETO_OPAQUE, &rc, pszMsg
        , lstrlen(pszMsg), NULL);

    ReleaseDC(m_hWnd, hDC);
    return;
    }


UINT CApp::Message(LPTSTR pszMsg, UINT uStyle)
    {
    return MessageBox(m_hWnd, pszMsg, TEXT("Automation Client")
        , uStyle);
    }





/*
 * HelpDirFromCLSID
 *
 * Purpose:
 *  Given a CLSID, looks up the TypeLib entry in the registry then
 *  extracts the HELPDIR entry for that type information, storing
 *  the path in pszPath.
 *
 * Parameters:
 *  clsID           CLSID of the object we're looking up.
 *  pszPath         LPTSTR buffer in which to store the directory.
 *
 * Return Value:
 *  None
 */

void HelpDirFromCLSID(CLSID clsID, LPTSTR pszPath)
    {
    TCHAR       szCLSID[80];
    TCHAR       szKey[512];
    UINT        cch;
    long        lRet;

    if (NULL==pszPath)
        return;

    *pszPath=0;

    cch=sizeof(szCLSID)/sizeof(TCHAR);
    StringFromGUID2(clsID, szCLSID, cch);
    wsprintf(szKey, TEXT("CLSID\\%s\\TypeLib"), szCLSID);

    //Get LIBID from under CLSID
    if (ERROR_SUCCESS==RegQueryValue(HKEY_CLASSES_ROOT, szKey
        , szCLSID, &lRet))
        {
        //Get HELPDIR from under TypeLib
        wsprintf(szKey, TEXT("TypeLib\\%s\\HELPDIR"), szCLSID);
        RegQueryValue(HKEY_CLASSES_ROOT, szKey, pszPath, &lRet);
        }

    return;
    }



/*
 * CApp::ShowProperties
 *
 * Purpose:
 *  Invokes the standard property page frame using the
 *  property pages specified by the object we maintain
 *  (only a single one).
 */

void CApp::ShowProperties(void)
    {
    ISpecifyPropertyPages  *pISPP;
    CAUUID                  caGUID;
    HRESULT                 hr;

    if (FAILED(m_pIDispatch->QueryInterface
        (IID_ISpecifyPropertyPages, (void **)&pISPP)))
        {
        Message(TEXT("Object has no property pages"));
        return;
        }

    hr=pISPP->GetPages(&caGUID);
    pISPP->Release();

    if (FAILED(hr))
        {
        Message(TEXT("Failed to retrieve property page GUIDs"));
        return;
        }

    hr=OleCreatePropertyFrame(m_hWnd, 10, 10, OLETEXT("Beeper")
        , 1, (IUnknown **)&m_pIDispatch, caGUID.cElems
        , caGUID.pElems, m_lcid, 0L, NULL);

    if (FAILED(hr))
        Message(TEXT("OleCreatePropertyFrame failed"));

    //Free the GUIDs
    CoTaskMemFree((void *)caGUID.pElems);
    return;
    }





/***
 *** IPropertyNotifySink Object
 ***/

/*
 * CPropertyNotifySink::CPropertyNotifySink
 * CPropertyNotifySink::~CPropertyNotifySink
 *
 * Constructor Parameters:
 *  pApp            PCApp of the application.
 */

CPropertyNotifySink::CPropertyNotifySink(PCApp pApp)
    {
    m_cRef=0;
    m_pApp=pApp;
    return;
    }

CPropertyNotifySink::~CPropertyNotifySink(void)
    {
    return;
    }



/*
 * CPropertyNotifySink::QueryInterface
 * CPropertyNotifySink::AddRef
 * CPropertyNotifySink::Release
 */

STDMETHODIMP CPropertyNotifySink::QueryInterface(REFIID riid
    , LPVOID *ppv)
    {
    *ppv=NULL;

    if (IID_IUnknown==riid || IID_IPropertyNotifySink==riid)
        *ppv=this;

    if (NULL!=*ppv)
        {
        ((LPUNKNOWN)*ppv)->AddRef();
        return NOERROR;
        }

    return ResultFromScode(E_NOINTERFACE);
    }

STDMETHODIMP_(ULONG) CPropertyNotifySink::AddRef(void)
    {
    return ++m_cRef;
    }

STDMETHODIMP_(ULONG) CPropertyNotifySink::Release(void)
    {
    if (0!=--m_cRef)
        return m_cRef;

    delete this;
    return 0;
    }



/*
 * CPropertyNotifySink::OnChanged
 *
 * Purpose:
 *  Notifies this sink that the property identified with dispID
 *  has changed in whatever object this sink is connected to.
 *
 * Parameters:
 *  dispID          DISPID of the property that changed,
 *                  which can be DISPID_UNKNOWN for unspecified
 *                  changes to multiple properties.
 *
 * Return Value:
 *  HRESULT         NOERROR always.
 */

STDMETHODIMP CPropertyNotifySink::OnChanged(DISPID dispID)
    {
    TCHAR       szTemp[200];

    wsprintf(szTemp
        , TEXT("OnChanged notification received for DISPID=%lu")
        , dispID);

    m_pApp->Message(szTemp);
    return NOERROR;
    }



/*
 * CPropertyNotifySink::OnRequestEdit
 *
 * Purpose:
 *  Notifies this sink that the property identified with dispID
 *  is about to change and that the sink can prevent the change
 *  if desired.  This can be used to enforce read-only states or
 *  to save prior states before the change occurs.
 *
 * Parameters:
 *  dispID          DISPID of the property that is changing
 *                  which can be DISPID_UNKNOWN for multiple
 *                  properties.
 *
 * Return Value:
 *  HRESULT         NOERROR if the property can change, S_FALSE
 *                  if it cannot change, error code otherwise.
 */

STDMETHODIMP CPropertyNotifySink::OnRequestEdit(DISPID dispID)
    {
    TCHAR       szTemp[200];

    wsprintf(szTemp
        , TEXT("OnRequestEdit received for DISPID=%lu"), dispID);
    m_pApp->Message(szTemp);

    return ResultFromScode(m_pApp->m_fReadOnly ? S_FALSE : S_OK);
    }
