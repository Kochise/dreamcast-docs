/*
 * POLYPROP.CPP
 * Polyline Property Page Chapter 24
 *
 * Server module code and class code CPolyPropertyPage class.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#define INITGUIDS
#include "polyprop.h"


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
    CPolyPPFactory *pPF;
    HRESULT         hr;

    if (CLSID_PolylinePropPage!=rclsid)
        return ResultFromScode(E_FAIL);

    //Check that we can provide the interface
    if (IID_IUnknown!=riid && IID_IClassFactory!=riid)
        return ResultFromScode(E_NOINTERFACE);

    //Return our factory's IClassFactory
    pPF=new CPolyPPFactory();

    if (NULL==pPF)
        return ResultFromScode(E_OUTOFMEMORY);

    //If the factory hasn't the interface, delete it
    hr=pPF->QueryInterface(riid, ppv);

    if (FAILED(hr))
        delete pPF;
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
 * CPolyPPFactory::CPolyPPFactory
 * CPolyPPFactory::~CPolyPPFactory
 * CPolyPPFactory::QueryInterface
 * CPolyPPFactory::AddRef
 * CPolyPPFactory::Release
 */

CPolyPPFactory::CPolyPPFactory(void)
    {
    m_cRef=0L;
    return;
    }

CPolyPPFactory::~CPolyPPFactory(void)
    {
    return;
    }

STDMETHODIMP CPolyPPFactory::QueryInterface(REFIID riid, PPVOID ppv)
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


STDMETHODIMP_(ULONG) CPolyPPFactory::AddRef(void)
    {
    return ++m_cRef;
    }


STDMETHODIMP_(ULONG) CPolyPPFactory::Release(void)
    {
    if (0!=--m_cRef)
        return m_cRef;

    delete this;
    g_cObj--;
    return 0;
    }



/*
 * CPolyPPFactory::CreateInstance
 * CPolyPPFactory::LockServer
 */

STDMETHODIMP CPolyPPFactory::CreateInstance(LPUNKNOWN pUnkOuter
    , REFIID riid, PPVOID ppvObj)
    {
    PCPolyPropPage      pObj;
    HRESULT             hr;

    *ppvObj=NULL;
    hr=ResultFromScode(E_OUTOFMEMORY);

    //No aggregation supported
    if (NULL!=pUnkOuter)
        return ResultFromScode(CLASS_E_NOAGGREGATION);

    //Create the object passing function to notify on destruction.
    pObj=new CPolyPropPage(g_hInst);

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


STDMETHODIMP CPolyPPFactory::LockServer(BOOL fLock)
    {
    if (fLock)
        g_cLock++;
    else
        g_cLock--;

    return NOERROR;
    }



/***
 *** CPolyPropPage implementation
 ***/


/*
 * CPolyPropPage::CPolyPropPage
 * CPolyPropPage::~CPolyPropPage
 *
 * Constructor Parameters:
 *  hInst           HINSTANCE of the module
 */

CPolyPropPage::CPolyPropPage(HINSTANCE hInst)
    {
    m_cRef=0L;

    m_hInst=hInst;
    m_hDlg=NULL;

    //Default sizes
    m_cx=300;
    m_cy=100;

    m_pIPropertyPageSite=NULL;
    m_ppObj=NULL;
    m_cObjects=0;

    m_uIDLastLine=ID_LINESOLID;
    m_crLastBack=0;
    m_crLastLine=0;

    m_fDirty=FALSE;
    return;
    }

CPolyPropPage::~CPolyPropPage(void)
    {
    if (NULL!=m_hDlg)
        DestroyWindow(m_hDlg);

    FreeAllObjects();
    ReleaseInterface(m_pIPropertyPageSite);
    return;
    }


/*
 * CPolyPropPage::QueryInterface
 * CPolyPropPage::AddRef
 * CPolyPropPage::Release
 */

STDMETHODIMP CPolyPropPage::QueryInterface(REFIID riid, PPVOID ppv)
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


STDMETHODIMP_(ULONG) CPolyPropPage::AddRef(void)
    {
    return ++m_cRef;
    }


STDMETHODIMP_(ULONG) CPolyPropPage::Release(void)
    {
    if (0!=--m_cRef)
        return m_cRef;

    g_cObj--;
    delete this;
    return 0;
    }




/*
 * CPolyPropPage::Init
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

BOOL CPolyPropPage::Init(void)
    {
    //Nothing to do
    return TRUE;
    }




/*
 * CPolyPropPage::FreeAllObjects
 *
 * Purpose:
 *  Releases all the objects from IPropertyPage::SetObjects
 *
 * Parameters:
 *  None
 */

void CPolyPropPage::FreeAllObjects(void)
    {
    UINT        i;

    if (NULL==m_ppObj)
        return;

    for (i=0; i < m_cObjects; i++)
        ReleaseInterface(m_ppObj[i]);

    delete [] m_ppObj;
    m_ppObj=NULL;
    m_cObjects=0;
    return;
    }



/*
 * CPolyPropPage::SetPageSite
 *
 * Purpose:
 *  Provides the property page with the IPropertyPageSite
 *  that contains it.  SetPageSite(NULL) will be called as
 *  part of the close sequence.
 *
 * Parameters:
 *  pPageSite       LPPROPERTYPAGESITE pointer to the site.
 */

STDMETHODIMP CPolyPropPage::SetPageSite
    (LPPROPERTYPAGESITE pPageSite)
    {
    if (NULL==pPageSite)
        ReleaseInterface(m_pIPropertyPageSite)
    else
        {
        HWND        hDlg;
        RECT        rc;

        m_pIPropertyPageSite=pPageSite;
        m_pIPropertyPageSite->AddRef();

        //We ignore locales

        /*
         * Load the dialog and determine the size it will be to
         * return through GetPageSize.  We just create the dialog
         * here and destroy it again to retrieve the size,
         * leaving Activate to create it for real.
         */
        hDlg=CreateDialogParam(m_hInst
            , MAKEINTRESOURCE(IDD_POLYLINEPROPS), GetDesktopWindow()
            , (DLGPROC)PolyPropPageProc, 0L);

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
 * CPolyPropPage::Activate
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

STDMETHODIMP CPolyPropPage::Activate(HWND hWndParent
    , LPCRECT prc, BOOL fModal)
    {
    if (NULL!=m_hDlg)
        return ResultFromScode(E_UNEXPECTED);

    m_hDlg=CreateDialogParam(m_hInst
        , MAKEINTRESOURCE(IDD_POLYLINEPROPS)
        , hWndParent, PolyPropPageProc, (LPARAM)this);

    if (NULL==m_hDlg)
        return ResultFromScode(E_OUTOFMEMORY);

    //Move the page into position and show it.
    SetWindowPos(m_hDlg, NULL, prc->left, prc->top
        , prc->right-prc->left, prc->bottom-prc->top, 0);

	return NOERROR;
    }



/*
 * CPolyPropPage::Deactivate
 *
 * Purpose:
 *  Instructs the property page to destroy its window that was
 *  created in Activate.
 *
 * Parameters:
 *  None
 */

STDMETHODIMP CPolyPropPage::Deactivate(void)
    {
    if (NULL==m_hDlg)
        return ResultFromScode(E_UNEXPECTED);

    DestroyWindow(m_hDlg);
    m_hDlg=NULL;
    return NOERROR;
    }



/*
 * CPolyPropPage::GetPageInfo
 *
 * Purpose:
 *  Fills a PROPPAGEINFO structure describing the page's size,
 *  contents, and help information.
 *
 * Parameters:
 *  pPageInfo       LPPROPPAGEINFO to the structure to fill.
 */

STDMETHODIMP CPolyPropPage::GetPageInfo(LPPROPPAGEINFO pPageInfo)
    {
    IMalloc     *pIMalloc;

    if (FAILED(CoGetMalloc(MEMCTX_TASK, &pIMalloc)))
        return ResultFromScode(E_FAIL);

    pPageInfo->pszTitle=(LPOLESTR)pIMalloc->Alloc(80*sizeof(TCHAR));

    if (NULL!=pPageInfo->pszTitle)
       #ifdef WIN32ANSI
        wcscpy(pPageInfo->pszTitle, OLETEXT("General"));
       #else
        lstrcpy(pPageInfo->pszTitle, TEXT("General"));
       #endif

    pIMalloc->Release();

	pPageInfo->size.cx      = m_cx;
    pPageInfo->size.cy      = m_cy;
	pPageInfo->pszDocString = NULL;
	pPageInfo->pszHelpFile  = NULL;
	pPageInfo->dwHelpContext= 0;
    return NOERROR;
    }



/*
 * CPolyPropPage::SetObjects
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

STDMETHODIMP CPolyPropPage::SetObjects(ULONG cObjects
    , IUnknown **ppUnk)
    {
    BOOL        fRet=TRUE;

    FreeAllObjects();

    if (0!=cObjects)
        {
        UINT        i;
        HRESULT     hr;

        m_ppObj=new IPolylineControl * [(UINT)cObjects];

	    for (i=0; i < cObjects; i++)
	        {
            hr=ppUnk[i]->QueryInterface(IID_IPolylineControl
                , (void **)&m_ppObj[i]);

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
 * CPolyPropPage::Show
 *
 * Purpose:
 *  Instructs the page to show or hide its window created in
 *  Activate.
 *
 * Parameters:
 *  nCmdShow        UINT to pass to ShowWindow.
 */

STDMETHODIMP CPolyPropPage::Show(UINT nCmdShow)
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
 * CPolyPropPage::Move
 *
 * Purpose:
 *  Instructs the property page to change its position.
 *
 * Parameters:
 *  prc             LPCRECT containing the new position.
 */

STDMETHODIMP CPolyPropPage::Move(LPCRECT prc)
    {
    SetWindowPos(m_hDlg, NULL, prc->left, prc->top
        , prc->right-prc->left, prc->bottom-prc->top, 0);

    return NOERROR;
    }



/*
 * CPolyPropPage::IsPageDirty
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

STDMETHODIMP CPolyPropPage::IsPageDirty(void)
    {
    return ResultFromScode(m_fDirty ? S_OK : S_FALSE);
    }




/*
 * CPolyPropPage::Apply
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

STDMETHODIMP CPolyPropPage::Apply(void)
    {
    UINT        i;
    UINT        iLine, iLineNew;
    COLORREF    crNew;
    BOOL        fChanged;

    if (0==m_cObjects)
        return NOERROR;

    /*
     * The dialog's last known line selection is in m_uIDLastLine,
     * colors in m_crLastBack and m_crLastLine, so we can just
     * send these to IPolylineControl member functions.
     * We the test if the change took place to determine whether
     * we set our dirty flag.
     */

    iLine=m_uIDLastLine-ID_LINEMIN;
    fChanged=FALSE;

    for (i=0; i < m_cObjects; i++)
        {
        m_ppObj[i]->put_LineStyle(iLine);
        iLineNew=m_ppObj[i]->get_LineStyle();

        fChanged |= (iLine!=iLineNew);

        m_ppObj[i]->put_BackColor(m_crLastBack);
        crNew=m_ppObj[i]->get_BackColor();

        fChanged |= (m_crLastBack!=crNew);

        m_ppObj[i]->put_LineColor(m_crLastLine);
        crNew=m_ppObj[i]->get_LineColor();

        fChanged |= (m_crLastLine!=crNew);
        }

    m_fDirty=!fChanged;
    return NOERROR;
    }



/*
 * CPolyPropPage::Help
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

STDMETHODIMP CPolyPropPage::Help(LPCOLESTR pszHelpDir)
    {
    /*
     * We can either provide help ourselves, or rely on the
     * information in PROPPAGEINFO.
     */
    return ResultFromScode(S_FALSE);
    }




/*
 * CPolyPropPage::TranslateAccelerator
 *
 * Purpose:
 *  Provides the page with the messages that occur in the frame.
 *  This gives the page to do whatever it wants with the message,
 *  such as handle keyboard mnemonics.
 *
 * Parameters:
 *  pMsg            LPMSG containing the keyboard message.
 */

STDMETHODIMP CPolyPropPage::TranslateAccelerator(LPMSG lpMsg)
    {
    //No keyboard interface supported here
    return ResultFromScode(E_NOTIMPL);
    }



/*
 * PolyPropPageProc
 *
 * Purpose:
 *  Dialog procedure for the Polyline Property Page.
 */

BOOL APIENTRY PolyPropPageProc(HWND hDlg, UINT iMsg
    , WPARAM wParam, LPARAM lParam)
    {
    PCPolyPropPage      pObj;
    WORD                wID;
    UINT                i;
    COLORREF            rgColors[16];
    CHOOSECOLOR         cc;

   #ifdef WIN32
    pObj=(PCPolyPropPage)(ULONG)GetProp(hDlg, g_szObj);
   #else
    pObj=(PCPolyPropPage)MAKELONG((WORD)GetProp(hDlg, g_szObjLo)
       , (WORD)GetProp(hDlg, g_szObjHi));
   #endif

    switch (iMsg)
        {
        case WM_INITDIALOG:
            pObj=(PCPolyPropPage)(ULONG)lParam;
           #ifdef WIN32
            SetProp(hDlg, g_szObj, (HANDLE)lParam);
           #else
            SetProp(hDlg, g_szObjHi, (HANDLE)HIWORD(lParam));
            SetProp(hDlg, g_szObjLo, (HANDLE)LOWORD(lParam));
           #endif

            if (NULL==pObj)
                return TRUE;

            /*
             * If we have one object then we can try to set the
             * right field in the dialog box.  Otherwise we could
             * ask for the value from all of the objects and see
             * if they all match.
             */
            if (1==pObj->m_cObjects)
                {
                UINT        iLine;

                iLine=pObj->m_ppObj[0]->get_LineStyle();

                CheckRadioButton(hDlg, ID_LINESOLID
                    , ID_LINEDASHDOTDOT, iLine+ID_LINEMIN);

                SetFocus(GetDlgItem(hDlg, iLine+ID_LINEMIN));

                pObj->m_uIDLastLine=iLine;

                pObj->m_crLastBack=pObj->m_ppObj[0]->get_BackColor();
                pObj->m_crLastLine=pObj->m_ppObj[0]->get_LineColor();
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
                case ID_LINESOLID:
                case ID_LINEDASH:
                case ID_LINEDOT:
                case ID_LINEDASHDOT:
                case ID_LINEDASHDOTDOT:
                    if (NULL==pObj)
                        break;

                    //Selecting the same one doesn't dirty
                    if (pObj->m_uIDLastLine==wID)
                        break;

                    //Save the most recently selected
                    pObj->m_uIDLastLine=LOWORD(wParam);
                    pObj->m_fDirty=TRUE;

                    if (NULL!=pObj->m_pIPropertyPageSite)
                        {
                        pObj->m_pIPropertyPageSite
                            ->OnStatusChange(PROPPAGESTATUS_DIRTY);
                        }

                    break;


                case ID_COLORLINE:
                case ID_COLORBACK:
                    if (NULL==pObj)
                        break;

                    for (i=0; i<16; i++)
                        rgColors[i]=RGB(0, 0, i*16);

                    memset(&cc, 0, sizeof(CHOOSECOLOR));
                    cc.lStructSize=sizeof(CHOOSECOLOR);
                    cc.lpCustColors=rgColors;
                    cc.hwndOwner=GetParent(hDlg);
                    cc.Flags=CC_RGBINIT;
                    cc.rgbResult=(ID_COLORBACK==wID)
                        ? pObj->m_crLastBack
                        : pObj->m_crLastLine;

                    if (ChooseColor(&cc))
                        {
                        COLORREF    cr;
                        ;
                        if (ID_COLORBACK==wID)
                            {
                            cr=pObj->m_crLastBack;
                            pObj->m_crLastBack=cc.rgbResult;
                            }
                        else
                            {
                            cr=pObj->m_crLastLine;
                            pObj->m_crLastLine=cc.rgbResult;
                            }

                        pObj->m_fDirty=(cr!=cc.rgbResult);

                        if (pObj->m_fDirty
                            && NULL!=pObj->m_pIPropertyPageSite)
                            {
                            pObj->m_pIPropertyPageSite
                                ->OnStatusChange(PROPPAGESTATUS_DIRTY);
                            }
                        }
                    break;

                }
            break;
        }
    return FALSE;
    }
