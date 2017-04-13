/*
 * BEEPPROP.CPP
 * Beeper Property Page Chapter 16
 *
 * Server module code and class code CBeeperPropertyPage class.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#define INITGUIDS
#include "beepprop.h"


//Count number of objects and number of locks.
ULONG       g_cObj=0;
ULONG       g_cLock=0;
HINSTANCE   g_hInst=NULL;   //For resources

#ifdef WIN32
TCHAR       g_szObj[]=TEXT("Object");
#else
TCHAR       g_szObjHi[]=TEXT("ObjectHi");
TCHAR       g_szObjLo[]=TEXT("ObjectLo");
#endif

/*
 * LibMain(32)
 *
 * Purpose:
 *  Entry point conditionally compiled for Win32 and Windows
 *  3.1.  Provides the proper structure for each environment.
 */

#ifdef WIN32
BOOL WINAPI LibMain32(HINSTANCE hInstance, ULONG ulReason
    , LPVOID pvReserved)
    {
    g_hInst=hInstance;

    if (DLL_PROCESS_DETACH==ulReason)
        {
        return TRUE;
        }
    else
        {
        if (DLL_PROCESS_ATTACH!=ulReason)
            return TRUE;
        }

    return TRUE;
    }
#else
int PASCAL LibMain(HINSTANCE hInstance, WORD wDataSeg
    , WORD cbHeapSize, LPSTR lpCmdLine)
    {
    if (0!=cbHeapSize)
        UnlockData(0);

    g_hInst=hInstance;
    return (int)hInstance;
    }
#endif



/*
 * DllGetClassObject
 * DllCanUnloadNow
 * Standard COM exports for DLL servers.
 */

HRESULT APIENTRY DllGetClassObject(REFCLSID rclsid, REFIID riid
    , PPVOID ppv)
    {
    CBeeperPPFactory *pBF;
    HRESULT         hr;

    if (CLSID_BeeperPropertyPage!=rclsid)
        return ResultFromScode(E_FAIL);

    //Check that we can provide the interface
    if (IID_IUnknown!=riid && IID_IClassFactory!=riid)
        return ResultFromScode(E_NOINTERFACE);

    //Return our beeper factory's IClassFactory
    pBF=new CBeeperPPFactory();

    if (NULL==pBF)
        return ResultFromScode(E_OUTOFMEMORY);

    //If the factory hasn't the interface, delete it
    hr=pBF->QueryInterface(riid, ppv);

    if (FAILED(hr))
        delete pBF;
    else
        g_cObj++;

    return hr;
    }


STDAPI DllCanUnloadNow(void)
    {
    SCODE   sc;

    //Our answer is whether there are any object or locks
    sc=(0L==g_cObj && 0L==g_cLock) ? S_OK : S_FALSE;
    return ResultFromScode(sc);
    }



/*
 * CBeeperPPFactory::CBeeperPPFactory
 * CBeeperPPFactory::~CBeeperPPFactory
 * CBeeperPPFactory::QueryInterface
 * CBeeperPPFactory::AddRef
 * CBeeperPPFactory::Release
 */

CBeeperPPFactory::CBeeperPPFactory(void)
    {
    m_cRef=0L;
    return;
    }

CBeeperPPFactory::~CBeeperPPFactory(void)
    {
    return;
    }

STDMETHODIMP CBeeperPPFactory::QueryInterface(REFIID riid, PPVOID ppv)
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


STDMETHODIMP_(ULONG) CBeeperPPFactory::AddRef(void)
    {
    return ++m_cRef;
    }


STDMETHODIMP_(ULONG) CBeeperPPFactory::Release(void)
    {
    if (0!=--m_cRef)
        return m_cRef;

    delete this;
    g_cObj--;
    return 0;
    }



/*
 * CBeeperPPFactory::CreateInstance
 * CBeeperPPFactory::LockServer
 */

STDMETHODIMP CBeeperPPFactory::CreateInstance(LPUNKNOWN pUnkOuter
    , REFIID riid, PPVOID ppvObj)
    {
    PCBeeperPropPage    pObj;
    HRESULT             hr;

    *ppvObj=NULL;
    hr=ResultFromScode(E_OUTOFMEMORY);

    //No aggregation supported
    if (NULL!=pUnkOuter)
        return ResultFromScode(CLASS_E_NOAGGREGATION);

    //Create the object passing function to notify on destruction.
    pObj=new CBeeperPropPage(g_hInst);

    if (NULL==pObj)
        return hr;

    if (pObj->Init())
        hr=pObj->QueryInterface(riid, ppvObj);

    //Kill the object if initial creation or Init failed.
    if (FAILED(hr))
        delete pObj;
    else
        g_cObj++;

    return hr;
    }


STDMETHODIMP CBeeperPPFactory::LockServer(BOOL fLock)
    {
    if (fLock)
        g_cLock++;
    else
        g_cLock--;

    return NOERROR;
    }



/***
 *** CBeeperPropPage implementation
 ***/


/*
 * CBeeperPropPage::CBeeperPropPage
 * CBeeperPropPage::~CBeeperPropPage
 *
 * Constructor Parameters:
 *  hInst           HINSTANCE of the module
 */

CBeeperPropPage::CBeeperPropPage(HINSTANCE hInst)
    {
    m_cRef=0L;

    m_hInst=hInst;
    m_uIDTemplate=IDD_BEEPERPROPS_0;
    m_hDlg=NULL;

    //Default sizes
    m_cx=300;
    m_cy=100;

    m_pIPropertyPageSite=NULL;
    m_ppIBeeper=NULL;
    m_cObjects=0;

    m_uIDLastSound=IDC_BEEPDEFAULT;
    m_fDirty=FALSE;

    m_lcid=LOCALE_USER_DEFAULT;
    return;
    }

CBeeperPropPage::~CBeeperPropPage(void)
    {
    if (NULL!=m_hDlg)
        DestroyWindow(m_hDlg);

    FreeAllObjects();
    ReleaseInterface(m_pIPropertyPageSite);
    return;
    }


/*
 * CBeeperPropPage::QueryInterface
 * CBeeperPropPage::AddRef
 * CBeeperPropPage::Release
 */

STDMETHODIMP CBeeperPropPage::QueryInterface(REFIID riid, PPVOID ppv)
    {
    *ppv=NULL;

    if (IID_IUnknown==riid || IID_IPropertyPage==riid)
        *ppv=this;

    if (NULL!=*ppv)
        {
        ((LPUNKNOWN)*ppv)->AddRef();
        return NOERROR;
        }

    return ResultFromScode(E_NOINTERFACE);
    }


STDMETHODIMP_(ULONG) CBeeperPropPage::AddRef(void)
    {
    return ++m_cRef;
    }


STDMETHODIMP_(ULONG) CBeeperPropPage::Release(void)
    {
    if (0!=--m_cRef)
        return m_cRef;

    g_cObj--;
    delete this;
    return 0;
    }




/*
 * CBeeperPropPage::Init
 *
 * Purpose:
 *  Performs initialization operations that might fail.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  BOOL            TRUE if initialization successful, FALSE
 *                  otherwise.
 */

BOOL CBeeperPropPage::Init(void)
    {
    //Nothing to do
    return TRUE;
    }




/*
 * CBeeperPropPage::FreeAllObjects
 *
 * Purpose:
 *  Releases all the objects from IPropertyPage::SetObjects
 *
 * Parameters:
 *  None
 */

void CBeeperPropPage::FreeAllObjects(void)
    {
    UINT        i;

    if (NULL==m_ppIBeeper)
        return;

    for (i=0; i < m_cObjects; i++)
        ReleaseInterface(m_ppIBeeper[i]);

    delete [] m_ppIBeeper;
    m_ppIBeeper=NULL;
    m_cObjects=0;
    return;
    }



/*
 * CBeeperPropPage::SetPageSite
 *
 * Purpose:
 *  Provides the property page with the IPropertyPageSite
 *  that contains it.  SetPageSite(NULL) will be called as
 *  part of the close sequence.
 *
 * Parameters:
 *  pPageSite       LPPROPERTYPAGESITE pointer to the site.
 */

STDMETHODIMP CBeeperPropPage::SetPageSite
    (LPPROPERTYPAGESITE pPageSite)
    {
    if (NULL==pPageSite)
        ReleaseInterface(m_pIPropertyPageSite)
    else
        {
        HWND        hDlg;
        RECT        rc;
        LCID        lcid;

        m_pIPropertyPageSite=pPageSite;
        m_pIPropertyPageSite->AddRef();

        if (SUCCEEDED(m_pIPropertyPageSite->GetLocaleID(&lcid)))
            m_lcid=lcid;

        /*
         * Now that we know the locale we're running under, we can
         * load the dialog and determine the size it will be to
         * return through GetPageSize.  We just create the dialog
         * here and destroy it again to retrieve the size,
         * leaving Activate to create it for real.
         */

        switch (PRIMARYLANGID(m_lcid))
            {
            case LANG_GERMAN:
                m_uIDTemplate=IDD_BEEPERPROPS_7;
                break;

            case LANG_NEUTRAL:
            case LANG_ENGLISH:
            default:
                m_uIDTemplate=IDD_BEEPERPROPS_0;
                break;
            }

        hDlg=CreateDialogParam(m_hInst
            , MAKEINTRESOURCE(m_uIDTemplate), GetDesktopWindow()
            , (DLGPROC)BeepPropPageProc, 0L);

        //If creation fails, use default values set in constructor
        if (NULL!=hDlg)
            {
            GetWindowRect(hDlg, &rc);
            m_cx=rc.right-rc.left;
            m_cy=rc.bottom-rc.top;

            DestroyWindow(hDlg);
            }
        }

    return NOERROR;
    }



/*
 * CBeeperPropPage::Activate
 *
 * Purpose:
 *  Instructs the property page to create a window in which to
 *  display its contents, using the given parent window and
 *  rectangle.  The window should be initially visible.
 *
 * Parameters:
 *  hWndParent      HWND of the parent window.
 *  prc             LPCRECT of the rectangle to use.
 *  fModal          BOOL indicating whether the frame is modal.
 */

STDMETHODIMP CBeeperPropPage::Activate(HWND hWndParent
    , LPCRECT prc, BOOL fModal)
    {
    if (NULL!=m_hDlg)
        return ResultFromScode(E_UNEXPECTED);

    m_hDlg=CreateDialogParam(m_hInst, MAKEINTRESOURCE(m_uIDTemplate)
        , hWndParent, BeepPropPageProc, (LPARAM)this);

    if (NULL==m_hDlg)
        return ResultFromScode(E_OUTOFMEMORY);

    //Move the page into position and show it.
    SetWindowPos(m_hDlg, NULL, prc->left, prc->top
        , prc->right-prc->left, prc->bottom-prc->top, 0);

	return NOERROR;
    }



/*
 * CBeeperPropPage::Deactivate
 *
 * Purpose:
 *  Instructs the property page to destroy its window that was
 *  created in Activate.
 *
 * Parameters:
 *  None
 */

STDMETHODIMP CBeeperPropPage::Deactivate(void)
    {
    if (NULL==m_hDlg)
        return ResultFromScode(E_UNEXPECTED);

    DestroyWindow(m_hDlg);
    m_hDlg=NULL;
    return NOERROR;
    }



/*
 * CBeeperPropPage::GetPageInfo
 *
 * Purpose:
 *  Fills a PROPPAGEINFO structure describing the page's size,
 *  contents, and help information.
 *
 * Parameters:
 *  pPageInfo       LPPROPPAGEINFO to the structure to fill.
 */

STDMETHODIMP CBeeperPropPage::GetPageInfo(LPPROPPAGEINFO pPageInfo)
    {
    IMalloc     *pIMalloc;

    if (FAILED(CoGetMalloc(MEMCTX_TASK, &pIMalloc)))
        return ResultFromScode(E_FAIL);

    pPageInfo->pszTitle=(LPOLESTR)pIMalloc->Alloc(CCHSTRINGMAX);

    if (NULL!=pPageInfo->pszTitle)
        {
        UINT        ids=IDS_0_PAGETITLE;

        if (PRIMARYLANGID(m_lcid)==LANG_GERMAN)
            ids=IDS_7_PAGETITLE;

       #ifdef WIN32ANSI
        char        szTemp[80];

        LoadString(m_hInst, ids, szTemp, CCHSTRINGMAX);
        MultiByteToWideChar(CP_ACP, 0, szTemp, -1
           , pPageInfo->pszTitle, 80);
       #else
        LoadString(m_hInst, ids, pPageInfo->pszTitle, CCHSTRINGMAX);
       #endif
        }

    pIMalloc->Release();

	pPageInfo->size.cx      = m_cx;
    pPageInfo->size.cy      = m_cy;
	pPageInfo->pszDocString = NULL;
	pPageInfo->pszHelpFile  = NULL;
	pPageInfo->dwHelpContext= 0;
    return NOERROR;
    }



/*
 * CBeeperPropPage::SetObjects
 *
 * Purpose:
 *  Identifies the objects that are being affected by this property
 *  page (and all other pages in the frame).  These are the object
 *  to which to send new property values in the Apply member.
 *
 * Parameters:
 *  cObjects        ULONG number of objects
 *  ppUnk           IUnknown ** to the array of objects being
 *                  passed to the page.
 */

STDMETHODIMP CBeeperPropPage::SetObjects(ULONG cObjects
    , IUnknown **ppUnk)
    {
    BOOL        fRet=TRUE;

    FreeAllObjects();

    if (0!=cObjects)
        {
        UINT        i;
        HRESULT     hr;

        m_ppIBeeper=new IBeeper * [(UINT)cObjects];

	    for (i=0; i < cObjects; i++)
	        {
            hr=ppUnk[i]->QueryInterface(IID_IBeeper
                , (void **)&m_ppIBeeper[i]);

            if (FAILED(hr))
                fRet=FALSE;
	        }
	    }

    //If we didn't get one of our objects, fail this call.
    if (!fRet)
        return ResultFromScode(E_FAIL);

    m_cObjects=cObjects;
    return NOERROR;
    }



/*
 * CBeeperPropPage::Show
 *
 * Purpose:
 *  Instructs the page to show or hide its window created in
 *  Activate.
 *
 * Parameters:
 *  nCmdShow        UINT to pass to ShowWindow.
 */

STDMETHODIMP CBeeperPropPage::Show(UINT nCmdShow)
    {
    if (NULL==m_hDlg)
        ResultFromScode(E_UNEXPECTED);

    ShowWindow(m_hDlg, nCmdShow);

    //Take the focus
    if (SW_SHOWNORMAL==nCmdShow || SW_SHOW==nCmdShow)
		SetFocus(m_hDlg);

    return NOERROR;
    }



/*
 * CBeeperPropPage::Move
 *
 * Purpose:
 *  Instructs the property page to change its position.
 *
 * Parameters:
 *  prc             LPCRECT containing the new position.
 */

STDMETHODIMP CBeeperPropPage::Move(LPCRECT prc)
    {
    SetWindowPos(m_hDlg, NULL, prc->left, prc->top
        , prc->right-prc->left, prc->bottom-prc->top, 0);

    return NOERROR;
    }



/*
 * CBeeperPropPage::IsPageDirty
 *
 * Purpose:
 *  Asks the page if anything's changed in it, that is, if the
 *  property values in the page are out of sync with the objects
 *  under consideration.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  HRESULT         NOERROR if dirty, S_FALSE if not.
 */

STDMETHODIMP CBeeperPropPage::IsPageDirty(void)
    {
    return ResultFromScode(m_fDirty ? S_OK : S_FALSE);
    }




/*
 * CBeeperPropPage::Apply
 *
 * Purpose:
 *  Instructs the page to send changes in its page to whatever
 *  objects it knows about through SetObjects.  This is the only
 *  time the page should change the objects' properties, and not
 *  when the value is changed on the page.
 *
 * Parameters:
 *  None
 */

STDMETHODIMP CBeeperPropPage::Apply(void)
    {
    UINT        i;
    UINT        lSound, lSoundNew;
    BOOL        fChanged;

    if (0==m_cObjects)
        return NOERROR;

    /*
     * The dialog's last known Sound selection is in
     * m_uIDLastSound, so we can just send it via
     * IBeeper::put_Sound.  Since this method has no
     * return value, we have to ask for it again to
     * see if it really changed because the client may
     * be blocking changes through IPropertyNotifySink,
     * in which case we do not clear the dirty flag.
     */

    lSound=(IDC_BEEPDEFAULT==m_uIDLastSound) ? 0L : m_uIDLastSound;
    fChanged=TRUE;

    for (i=0; i < m_cObjects; i++)
        {
        m_ppIBeeper[i]->put_Sound(lSound);
        lSoundNew=m_ppIBeeper[i]->get_Sound();

        fChanged &= (lSound==lSoundNew);
        }

    m_fDirty=!fChanged;
    return NOERROR;
    }



/*
 * CBeeperPropPage::Help
 *
 * Purpose:
 *  Invokes help for this property page when the user presses
 *  the Help button.  If you return NULLs for the help file
 *  in GetPageInfo, the button will be grayed.  Otherwise the
 *  page can perform its own help here.
 *
 * Parameters:
 *  pszHelpDir      LPCOLESTR identifying the default location of
 *                  the help information
 *
 * Return Value:
 *  HRESULT         NOERROR to tell the frame that we've done our
 *                  own help.  Returning an error code or S_FALSE
 *                  causes the frame to use any help information
 *                  in PROPPAGEINFO.
 */

STDMETHODIMP CBeeperPropPage::Help(LPCOLESTR pszHelpDir)
    {
    /*
     * We can either provide help ourselves, or rely on the
     * information in PROPPAGEINFO.
     */
    return ResultFromScode(S_FALSE);
    }




/*
 * CBeeperPropPage::TranslateAccelerator
 *
 * Purpose:
 *  Provides the page with the messages that occur in the frame.
 *  This gives the page to do whatever it wants with the message,
 *  such as handle keyboard mnemonics.
 *
 * Parameters:
 *  pMsg            LPMSG containing the keyboard message.
 */

STDMETHODIMP CBeeperPropPage::TranslateAccelerator(LPMSG lpMsg)
    {
    //No keyboard interface supported here
    return ResultFromScode(E_NOTIMPL);
    }



/*
 * BeepPropPageProc
 *
 * Purpose:
 *  Dialog procedure for the Beeper Property Page.
 */

BOOL APIENTRY BeepPropPageProc(HWND hDlg, UINT iMsg
    , WPARAM wParam, LPARAM lParam)
    {
    PCBeeperPropPage    pObj;
    WORD                wID;

   #ifdef WIN32
    pObj=(PCBeeperPropPage)(ULONG)GetProp(hDlg, g_szObj);
   #else
    pObj=(PCBeeperPropPage)MAKELONG((WORD)GetProp(hDlg, g_szObjLo)
       , (WORD)GetProp(hDlg, g_szObjHi));
   #endif

    switch (iMsg)
        {
        case WM_INITDIALOG:
            pObj=(PCBeeperPropPage)(ULONG)lParam;
           #ifdef WIN32
            SetProp(hDlg, g_szObj, (HANDLE)lParam);
           #else
            SetProp(hDlg, g_szObjHi, (HANDLE)HIWORD(lParam));
            SetProp(hDlg, g_szObjLo, (HANDLE)LOWORD(lParam));
           #endif

            if (NULL==pObj)
                return TRUE;

            SetFocus(GetDlgItem(hDlg, IDOK));

            /*
             * If we have one object then we can try to set the
             * right field in the dialog box.  Otherwise we could
             * ask for the value from all of the objects and see
             * if they all match.
             */
            if (1==pObj->m_cObjects)
                {
                UINT        iButton;

                iButton=(UINT)pObj->m_ppIBeeper[0]->get_Sound();

                if (0==iButton)
                    iButton=IDC_BEEPDEFAULT;

                CheckRadioButton(hDlg, IDC_BEEPDEFAULT
                    , IDC_BEEPASTERISK, iButton);

                pObj->m_uIDLastSound=iButton;
                }

            return FALSE;

        case WM_DESTROY:
           #ifdef WIN32
            RemoveProp(hDlg, g_szObj);
           #else
            RemoveProp(hDlg, g_szObjHi);
            RemoveProp(hDlg, g_szObjLo);
           #endif
            return FALSE;

        case WM_COMMAND:
            wID=LOWORD(wParam);

            switch (wID)
                {
                case IDC_BEEPDEFAULT:
                case IDC_BEEPHAND:
                case IDC_BEEPQUESTION:
                case IDC_BEEPEXCLAMATION:
                case IDC_BEEPASTERISK:
                    if (NULL==pObj)
                        break;

                    //Selecting the same one doesn't dirty
                    if (pObj->m_uIDLastSound==wID)
                        break;

                    //Save the most recently selected
                    pObj->m_uIDLastSound=LOWORD(wParam);
                    pObj->m_fDirty=TRUE;

                    if (NULL!=pObj->m_pIPropertyPageSite)
                        {
                        pObj->m_pIPropertyPageSite
                            ->OnStatusChange(PROPPAGESTATUS_DIRTY);
                        }

                    break;


                case IDOK:
                    /*
                     * We could call the object's Beep, but
                     * as it's property page, we know what
                     * it will do so we can just do it.
                     */
                    if (NULL!=pObj)
                        MessageBeep(pObj->m_uIDLastSound);

                    break;
                }
            break;
        }
    return FALSE;
    }
