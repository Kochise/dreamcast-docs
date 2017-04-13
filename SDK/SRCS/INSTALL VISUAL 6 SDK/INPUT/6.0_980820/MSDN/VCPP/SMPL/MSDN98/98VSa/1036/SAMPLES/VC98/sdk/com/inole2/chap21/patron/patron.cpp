/*
 * PATRON.CPP
 * Patron Chapter 21
 *
 * WinMain which is all we need for the basic application.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#define INITGUIDS
#include "patron.h"

//CHAPTER21MOD
ULONG       g_cObj=0;
ULONG       g_cLock=0;
HWND        g_hWnd=NULL;
BOOL        g_fUser=TRUE;
//End CHAPTER21MOD


/*
 * WinMain
 *
 * Purpose:
 *  Main entry point of application.  Should register the app class
 *  if a previous instance has not done so and do any other one-time
 *  initializations.
 */

int PASCAL WinMain (HINSTANCE hInst, HINSTANCE hPrev
    , LPSTR pszCmdLine, int nCmdShow)
    {
    PCPatronFrame   pFR;
    FRAMEINIT       fi;
    WPARAM          wRet=0;

    SETMESSAGEQUEUE;

    //Attempt to allocate and initialize the application
    pFR=new CPatronFrame(hInst, hPrev, pszCmdLine, nCmdShow);

    if (NULL==pFR)
        return -1;

    fi.idsMin=IDS_FRAMEMIN;
    fi.idsMax=IDS_FRAMEMAX;
    fi.idsStatMin=IDS_STATMESSAGEMIN;
    fi.idsStatMax=IDS_STATMESSAGEMAX;
    fi.idStatMenuMin=ID_MENUFILE;
    fi.idStatMenuMax=ID_MENUHELP;
    fi.iPosWindowMenu=WINDOW_MENU;
    fi.cMenus=CMENUS;

    fi.x=CW_USEDEFAULT;
    fi.y=CW_USEDEFAULT;
    fi.cx=CW_USEDEFAULT;
    fi.cy=CW_USEDEFAULT;

    //If we can initialize pFR, start chugging messages
    if (pFR->Init(&fi))
        wRet=pFR->MessageLoop();

    delete pFR;
    return wRet;
    }



//CHAPTER21MOD
/*
 * ObjectDestroyed
 *
 * Purpose:
 *  Function for the Patron Document object to call when it gets
 *  destroyed.  We destroy the main window if the proper conditions
 *  are met for shutdown.
 */

void ObjectDestroyed(void)
    {
    g_cObj--;

    //No more objects, no locks, no user control, shut the app down.
    if (0==g_cObj && 0==g_cLock && IsWindow(g_hWnd) && !g_fUser)
        PostMessage(g_hWnd, WM_CLOSE, 0, 0L);

    return;
    }

//End CHAPTER21MOD




/*
 * CPatronFrame::CPatronFrame
 * CPatronFrame::~CPatronFrame
 *
 * Constructor Parameters:
 *  hInst           HINSTANCE from WinMain
 *  hInstPrev       HINSTANCE from WinMain
 *  pszCmdLine      LPSTR from WinMain
 *  nCmdShow        int from WInMain
 */

CPatronFrame::CPatronFrame(HINSTANCE hInst, HINSTANCE hInstPrev
    , LPSTR pszCmdLine, int nCmdShow)
    : CFrame(hInst, hInstPrev, pszCmdLine, nCmdShow)
    {
    m_fInitialized=FALSE;
    m_pIClassDataTran=NULL;

    //CHAPTER21MOD
    m_pDocCreated=NULL;
    m_fEmbedding=FALSE;

    m_dwRegCO=0;
    m_pIClassFactory=NULL;
    //End CHAPTER21MOD

    return;
    }


CPatronFrame::~CPatronFrame(void)
    {
    //CHAPTER21MOD
    //Opposite of CoRegisterClassObject, takes class factory ref to 1
    if (0L!=m_dwRegCO)
        CoRevokeClassObject(m_dwRegCO);

    //This should be the last Release, which frees the class factory.
    ReleaseInterface(m_pIClassFactory);
    //End CHAPTER21MOD

    if (NULL!=m_pIClassDataTran)
        {
        m_pIClassDataTran->LockServer(FALSE);
        m_pIClassDataTran->Release();
        }

    OleFlushClipboard();

    if (m_fInitialized)
        OleUninitialize();

    return;
    }




/*
 * CPatronFrame::Init
 *
 * Purpose:
 *  Call OleInitialize then calling down into the base class
 *  initialization.
 *
 * Parameters:
 *  pFI             PFRAMEINIT containing initialization
 *                  parameters.
 *
 * Return Value:
 *  BOOL            TRUE if initialization succeeded,
 *                  FALSE otherwise.
 */

BOOL CPatronFrame::Init(PFRAMEINIT pFI)
    {
    HRESULT     hr;

    CHECKVER_OLE;

    if (FAILED(OleInitialize(NULL)))
        return FALSE;

    m_fInitialized=TRUE;

    //Lock the data transfer object factory as an optimization.
    hr=CoGetClassObject(CLSID_DataTransferObject
        , CLSCTX_INPROC_SERVER, NULL, IID_IClassFactory
        , (PPVOID)&m_pIClassDataTran);

    if (SUCCEEDED(hr))
        m_pIClassDataTran->LockServer(TRUE);

    //CHAPTER21MOD
    //Check for command line flags
    ParseCommandLine();

    if (NULL!=m_ppszCmdArgs)
        {
        if(0==lstrcmpi(m_ppszCmdArgs[0], TEXT("-Embedding"))
           || 0==lstrcmpi(m_ppszCmdArgs[0], TEXT("/Embedding")))
            m_fEmbedding=TRUE;
        }

    g_fUser=!m_fEmbedding;

    if (m_fEmbedding)
        {
        HRESULT     hr;

        m_pIClassFactory=new CLinkClassFactory(this);

        if (NULL==m_pIClassFactory)
            return FALSE;

        //Since we hold on to this, we should AddRef it.
        m_pIClassFactory->AddRef();

        hr=CoRegisterClassObject(CLSID_PatronPages, m_pIClassFactory
            , CLSCTX_LOCAL_SERVER, REGCLS_SINGLEUSE, &m_dwRegCO);

        if (FAILED(hr))
            return FALSE;
        }
    //End CHAPTER21MOD

    return CFrame::Init(pFI);
    }





/*
 * CPatronFrame::CreateCClient
 *
 * Purpose:
 *  Constructs a new client specific to the application.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  PCClient        Pointer to the new client object.
 */

PCClient CPatronFrame::CreateCClient(void)
    {
    return (PCClient)(new CPatronClient(m_hInst, this));
    }






/*
 * CPatronFrame::RegisterAllClasses
 *
 * Purpose:
 *  Registers all classes used in this application.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  BOOL            TRUE if registration succeeded, FALSE otherwise.
 */

BOOL CPatronFrame::RegisterAllClasses(void)
    {
    WNDCLASS        wc;

    //First let the standard frame do its thing
    if (!CFrame::RegisterAllClasses())
        return FALSE;

    //We need double-clicks now and for object activation.
    wc.style         = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
    wc.hInstance     = m_hInst;
    wc.cbClsExtra    = 0;
    wc.lpfnWndProc   = PagesWndProc;
    wc.cbWndExtra    = CBPAGESWNDEXTRA;
    wc.hIcon         = NULL;
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_APPWORKSPACE+1);
    wc.lpszMenuName  = NULL;
    wc.lpszClassName = SZCLASSPAGES;

    if (!RegisterClass(&wc))
        return FALSE;

    return TRUE;
    }




//CHAPTER21MOD
/*
 * CPatronFrame::PreShowInit
 *
 * Purpose:
 *  Called from Init before intially showing the window.  We do
 *  whatever else we want here, modifying m_nCmdShow as necessary
 *  which affects ShowWindow in Init.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  BOOL            TRUE if this successful, FALSE otherwise.
 */

BOOL CPatronFrame::PreShowInit(void)
    {
    //Base class does nothing
    CFrame::PreShowInit();

    //Save the window handle for shutdown if necessary.
    g_hWnd=m_hWnd;

    //If we're -Embedding, don't show the window initially.
    if (m_fEmbedding)
        m_nCmdShow=SW_HIDE;

    return TRUE;
    }
//End CHAPTER21MOD





/*
 * CPatronFrame::OnCommand
 *
 * Purpose:
 *  WM_COMMAND handler for the Patron frame window that processes
 *  extra File menu items as well as the Page menu.
 *
 * Parameters:
 *  hWnd            HWND of the frame window.
 *  wParam          WPARAM of the message.
 *  lParam          LPARAM of the message.
 *
 * Return Value:
 *  LRESULT         Return value for the message.
 */

LRESULT CPatronFrame::OnCommand(HWND hWnd, WPARAM wParam
    , LPARAM lParam)
    {
    PCPatronDoc     pDoc;

    COMMANDPARAMS(wID, wCode, hWndMsg);

    /*
     * Don't bother with anything during first initialization,
     * skipping many toolbar notifications.
     */
    if (m_fInit)
        return 0L;

    pDoc=(PCPatronDoc)m_pCL->ActiveDocument();

    if (NULL!=pDoc && (IDM_VERBMIN <= wID) && (IDM_VERBMAX >= wID))
        {
        pDoc->ActivateObject(wID-IDM_VERBMIN);
        return 0L;
        }

    switch (wID)
        {
        case IDM_FILEPRINT:
            pDoc->Print(m_hWnd);
            return 0L;

        case IDM_FILEPRINTERSETUP:
            pDoc->PrinterSetup(m_hWnd, FALSE);
            return 0L;

        case IDM_EDITPASTESPECIAL:
            pDoc->PasteSpecial(m_hWnd);
            return 0L;

        case IDM_EDITDELETEOBJECT:
            pDoc->Delete();
            return 0L;

        case IDM_EDITINSERTOBJECT:
            pDoc->InsertObject(m_hWnd);
            return 0L;

        case IDM_EDITCONVERT:
            pDoc->ConvertObject(m_hWnd);
            return 0L;

        case IDM_EDITLINKS:
            pDoc->EditLinks(m_hWnd);
            return 0L;

        case IDM_PAGENEWPAGE:
            pDoc->NewPage();
            break;

        case IDM_PAGEDELETEPAGE:
            pDoc->DeletePage();
            break;

        case IDM_PAGENEXTPAGE:
            pDoc->NextPage();
            break;

        case IDM_PAGEPREVIOUSPAGE:
            pDoc->PreviousPage();
            break;

        case IDM_PAGEFIRSTPAGE:
            pDoc->FirstPage();
            break;

        case IDM_PAGELASTPAGE:
            pDoc->LastPage();
            break;

        case IDM_PAGESHOWOBJECTS:
            {
            BOOL    fTemp;

            //First get the current state, then toggle it.
            fTemp=pDoc->ShowOrQueryObjectTypes(TRUE, FALSE);
            pDoc->ShowOrQueryObjectTypes(FALSE, !fTemp);
            }
            break;

        default:
           return CFrame::OnCommand(hWnd, wParam, lParam);
        }

    return 0L;
    }








/*
 * CPatronFrame::CreateToolbar
 *
 * Purpose:
 *  Procedure to create all the necessary toolbar buttons.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  UINT            Number of tools added to the bar.
 */

UINT CPatronFrame::CreateToolbar(void)
    {
    UINT            iLast;
    UINT            uState=GIZMO_NORMAL;
    UINT            utCmd =GIZMOTYPE_BUTTONCOMMAND;

    //Insert the standard ones.
    iLast=CFrame::CreateToolbar();

    //Remove Undo:  we don't use it.
    m_pTB->Remove(IDM_EDITUNDO);

    /*
     * Insert Print File Import in the 5th position and account
     * for it in iLast.
     */
    m_pTB->Add(utCmd, 4, IDM_FILEPRINT, m_dxB, m_dyB
        , NULL, NULL, 6, uState);

    iLast++;

    m_pTB->Add(GIZMOTYPE_SEPARATOR, iLast++, 0, 6, m_dyB
        , NULL, NULL, 0, uState);

    //Add New Page, and Delete Page
    m_pTB->Add(utCmd, iLast++, IDM_PAGENEWPAGE, m_dxB, m_dyB
        , NULL, m_hBmp, 2, uState);
    m_pTB->Add(utCmd, iLast++, IDM_PAGEDELETEPAGE, m_dxB, m_dyB
        , NULL, m_hBmp, 3, uState);

    m_pTB->Add(GIZMOTYPE_SEPARATOR, iLast++, 0, 6, m_dyB
        , NULL, NULL, 0, uState);

    //First, Prev, Next, Last pages.
    m_pTB->Add(utCmd, iLast++, IDM_PAGEFIRSTPAGE, m_dxB, m_dyB
        , NULL, m_hBmp, 4, uState);
    m_pTB->Add(utCmd, iLast++, IDM_PAGEPREVIOUSPAGE, m_dxB, m_dyB
        , NULL, m_hBmp, 5, uState);
    m_pTB->Add(utCmd, iLast++, IDM_PAGENEXTPAGE, m_dxB, m_dyB
        , NULL, m_hBmp, 6, uState);
    m_pTB->Add(utCmd, iLast++, IDM_PAGELASTPAGE, m_dxB, m_dyB
        , NULL, m_hBmp, 7, uState);

    return iLast;
    }







/*
 * CPatronFrame::UpdateMenus
 *
 * Purpose:
 *  Handles the WM_INITMENU message for the frame window.  Depending
 *  on the existence of an active window, menu items are selectively
 *  enabled and disabled.
 *
 * Parameters:
 *  hMenu           HMENU of the menu to intialize
 *  iMenu           UINT position of the menu.
 *
 * Return Value:
 *  None
 */

void CPatronFrame::UpdateMenus(HMENU hMenu, UINT iMenu)
    {
    PCPatronDoc     pDoc;
    BOOL            fOK=FALSE;
    BOOL            fCallDefault=TRUE;
    UINT            uTemp;
    UINT            uTempE;
    UINT            uTempD;

    pDoc=(PCPatronDoc)m_pCL->ActiveDocument();

    uTempE=MF_ENABLED | MF_BYCOMMAND;
    uTempD=MF_DISABLED | MF_GRAYED | MF_BYCOMMAND;
    uTemp=((NULL!=pDoc) ? uTempE : uTempD);

    if (m_phMenu[0]==hMenu)
        {
        EnableMenuItem(hMenu, IDM_FILEPRINT, uTemp);

        if (NULL!=pDoc)
            fOK=pDoc->FQueryPrinterSetup();

        EnableMenuItem(hMenu, IDM_FILEPRINTERSETUP
            , (fOK) ? uTempE : uTempD);
        }

    if (m_phMenu[1]==hMenu)
        {
        if (NULL!=pDoc)
            fOK=pDoc->FQueryPaste();

        EnableMenuItem(hMenu, IDM_EDITPASTE
            , (fOK) ? uTempE : uTempD);
        EnableMenuItem(hMenu, IDM_EDITPASTESPECIAL
            , (fOK) ? uTempE : uTempD);

        //Cut, Copy, Delete depends on there being a selection.
        if (NULL!=pDoc)
            fOK=pDoc->FQueryObjectSelected(hMenu);
        else
            fOK=FALSE;

        EnableMenuItem(hMenu, IDM_EDITCUT, (fOK) ? uTempE : uTempD);
        EnableMenuItem(hMenu, IDM_EDITCOPY
            , (fOK) ? uTempE : uTempD);
        EnableMenuItem(hMenu, IDM_EDITDELETEOBJECT
            , (fOK) ? uTempE : uTempD);

        EnableMenuItem(hMenu, IDM_EDITINSERTOBJECT, uTemp);

        if (NULL!=pDoc)
            fOK=pDoc->FQueryEnableEditLinks();
        else
            fOK=FALSE;

        EnableMenuItem(hMenu, IDM_EDITLINKS
            , (fOK) ? uTempE : uTempD);

        //We did the whole menu...
        fCallDefault=FALSE;
        }

    //Page menu
    if (m_phMenu[2]==hMenu)
        {
        EnableMenuItem(hMenu, IDM_PAGENEWPAGE,      uTemp);
        EnableMenuItem(hMenu, IDM_PAGEDELETEPAGE,   uTemp);
        EnableMenuItem(hMenu, IDM_PAGENEXTPAGE,     uTemp);
        EnableMenuItem(hMenu, IDM_PAGEPREVIOUSPAGE, uTemp);
        EnableMenuItem(hMenu, IDM_PAGEFIRSTPAGE,    uTemp);
        EnableMenuItem(hMenu, IDM_PAGELASTPAGE,     uTemp);

        //Check the Show Objects command or not.
        if (NULL!=pDoc)
            fOK=pDoc->ShowOrQueryObjectTypes(TRUE, FALSE);
        else
            fOK=FALSE;

        CheckMenuItem(hMenu, IDM_PAGESHOWOBJECTS, MF_BYCOMMAND
            | ((fOK) ? MF_CHECKED : MF_UNCHECKED));
        EnableMenuItem(hMenu, IDM_PAGESHOWOBJECTS, uTemp);
        }

    if (fCallDefault)
        CFrame::UpdateMenus(hMenu, iMenu);

    return;
    }






/*
 * CPatronFrame::UpdateToolbar
 *
 * Purpose:
 *  Enables and disables tools depending on whether we have
 *  a document or not.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  None
 */

void CPatronFrame::UpdateToolbar(void)
    {
    PCDocument  pDoc;
    BOOL        fEnable;

    //Let the default hack on its tools.
    CFrame::UpdateToolbar();

    pDoc=m_pCL->ActiveDocument();
    fEnable=(NULL!=pDoc);

    //No document, disable just about everything
    m_pTB->Enable(IDM_FILEPRINT,        fEnable);
    m_pTB->Enable(IDM_FILEPRINTERSETUP, fEnable);

    m_pTB->Enable(IDM_PAGENEWPAGE,      fEnable);
    m_pTB->Enable(IDM_PAGEDELETEPAGE,   fEnable);
    m_pTB->Enable(IDM_PAGEFIRSTPAGE,    fEnable);
    m_pTB->Enable(IDM_PAGEPREVIOUSPAGE, fEnable);
    m_pTB->Enable(IDM_PAGENEXTPAGE,     fEnable);
    m_pTB->Enable(IDM_PAGELASTPAGE,     fEnable);

    return;
    }



/*
 * CPatronFrame::FMessageHook
 *
 * Purpose:
 *  Override of CFrame::FMessageHook so we can specifically trap
 *  WM_MENUSELECT messages for the Object verb menu to provide some
 *  meaningful information on the status strip.
 *
 * Parameters:
 *  <WndProc Parameters>
 *  pLRes           LRESULT * in which to store the return value
 *                  for the message.
 *
 * Return Value:
 *  BOOL            TRUE to prevent further processing,
 *                  FALSE otherwise.
 */

BOOL CPatronFrame::FMessageHook(HWND hWnd, UINT iMsg, WPARAM wParam
    , LPARAM lParam, LRESULT *pLRes)
    {
    BOOL        fRet=FALSE;

    *pLRes=0;

    MENUSELECTPARAMS(wItem, wMenuFlags, hMenu);

    //CHAPTER21MOD
    /*
     * When closing, make sure any document create from the
     * class factory is saved since the object in it might
     * have been changed.  We want to save without showing
     * the user any message or asking if the user wants to save.
     */
    if (WM_CLOSE==iMsg)
        {
        if (NULL!=m_pDocCreated)
            {
            if (m_pDocCreated->FDirtyGet())
                {
                CHourglass  wait;
                m_pDocCreated->Save(0, NULL);
                }
            }

        return FALSE;
        }
    //End CHAPTER21MOD

    //If this is the wrong message, nothing to do.
    if (WM_MENUSELECT!=iMsg)
        return FALSE;

    //This happens when there's no menu selection.
    if (-1==wMenuFlags)
        return FALSE;

    if (MF_POPUP & wMenuFlags)
        {
        /*
         * If this is the cascade verb menu itself, display the same
         * message.  m_phMenu[1] contains the current edit menu
         * handle.
         */
        if (0!=wItem)
            {
            fRet=((HMENU)wItem==GetSubMenu(m_phMenu[1]
                , MENUPOS_OBJECT));
            }
        }
    else
        {
        /*
         * If the ID is in the verb range, use
         * IDS_ITEMMESSAGEEDITOBJECT message
         */
        fRet=(IDM_VERBMIN <= wItem && IDM_VERBMAX >= wItem);
        }

    if (fRet)
        m_pSL->MessageDisplay(IDM_EDITOBJECT);

    return fRet;
    }
