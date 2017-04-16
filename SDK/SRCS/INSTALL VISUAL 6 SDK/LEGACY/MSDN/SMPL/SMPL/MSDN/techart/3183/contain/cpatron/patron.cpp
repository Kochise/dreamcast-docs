/*
 * PATRON.CPP
 * Patron Control Containter
 *
 * WinMain which is all we need for the basic application.
 *
 * Copyright (c)1993-1994 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Software Design Engineer
 * Microsoft Systems Developer Relations
 *
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#define INITGUIDS
#include "patron.h"

//Count number of objects and number of locks.
ULONG       g_cObj=0;
ULONG       g_cLock=0;

//Make window handle global so other code can cause a shutdown
HWND        g_hWnd=NULL;

//Indicate if the user has control
BOOL        g_fUser=TRUE;


/*
 * The in-place site needs to have access to the frame and its
 * IOleInPlaceFrame interface.  A global, pardon me, is the simplest
 * way to achieve this.
 */

PCPatronFrame   g_pFR;



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

   #ifndef WIN32
    int             cMsg=96;

    while (!SetMessageQueue(cMsg) && (cMsg-=8));
   #endif

    //Attempt to allocate and initialize the application
    pFR=new CPatronFrame(hInst, hPrev, pszCmdLine, nCmdShow);

    if (NULL==pFR)
        return -1;

    g_pFR=pFR;

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
    if (pFR->FInit(&fi))
        wRet=pFR->MessageLoop();

    delete pFR;
    return wRet;
    }



/*
 * ObjectDestroyed
 *
 * Purpose:
 *  Function for the Patron Document object to call when it gets
 *  destroyed.  We destroy the main window if the proper conditions
 *  are met for shutdown.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  None
 */

void PASCAL ObjectDestroyed(void)
    {
    g_cObj--;

    //No more objects, no locks, no user control, shut the app down.
    if (0==g_cObj && 0==g_cLock && IsWindow(g_hWnd) && !g_fUser)
        PostMessage(g_hWnd, WM_CLOSE, 0, 0L);

    return;
    }





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
    char        szTemp[256];        //ParseCmdLine is ANSI

    m_fInitialized=FALSE;
    m_pIClassDataTran=NULL;

    m_pDocCreated=NULL;
    m_fEmbedding=FALSE; //-Embedding on command line?

    ParseCmdLine(pszCmdLine, &m_fEmbedding, szTemp);
    g_fUser=!m_fEmbedding;

    m_dwRegCO=0;
    m_pIClassFactory=NULL;

    m_cRef=0;
    m_hAccelIP=NULL;
    m_hWndObj=NULL;
    m_hMenuOrg=NULL;
    m_hMenuTop=NULL;
    m_fOurToolsShowing=TRUE;
    m_fInContextHelp=FALSE;
    m_pIOleIPActiveObject=NULL;

    return;
    }


CPatronFrame::~CPatronFrame(void)
    {
    //Opposite of CoRegisterClassObject, takes class factory ref to 1
    if (0L!=m_dwRegCO)
        CoRevokeClassObject(m_dwRegCO);

    //This should be the last Release, which frees the class factory.
    if (NULL!=m_pIClassFactory)
        m_pIClassFactory->Release();

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
 * CPatronFrame::FInit
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

BOOL CPatronFrame::FInit(PFRAMEINIT pFI)
    {
    DWORD       dwVer;
    HRESULT     hr;
    BOOL        fRet;

    dwVer=OleBuildVersion();

    if (rmm!=HIWORD(dwVer))
        return FALSE;

    if (FAILED(OleInitialize(NULL)))
        return FALSE;

    m_fInitialized=TRUE;

    //Lock the data transfer object factory as an optimization.
    hr=CoGetClassObject(CLSID_DataTransferObject
        , CLSCTX_INPROC_SERVER, NULL, IID_IClassFactory
        , (PPVOID)&m_pIClassDataTran);

    if (SUCCEEDED(hr))
        m_pIClassDataTran->LockServer(TRUE);

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

    //Load in-place accelerators
    m_hAccelIP=LoadAccelerators(m_hInst
        , MAKEINTRESOURCE(IDR_INPLACEACCELERATORS));

    if (NULL==m_hAccelIP)
        return FALSE;

    fRet=CFrame::FInit(pFI);

    m_hMenuOrg=GetMenu(m_hWnd);
    return fRet;
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
    return (PCClient)(new CPatronClient(m_hInst));
    }






/*
 * CPatronFrame::FRegisterAllClasses
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

BOOL CPatronFrame::FRegisterAllClasses(void)
    {
    WNDCLASS        wc;

    //First let the standard frame do its thing
    if (!CFrame::FRegisterAllClasses())
        return FALSE;

    //We need double-clicks now and for object activation later.
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




/*
 * CPatronFrame::FPreShowInit
 *
 * Purpose:
 *  Called from FInit before intially showing the window.  We do
 *  whatever else we want here, modifying m_nCmdShow as necessary
 *  which affects ShowWindow in FInit.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  BOOL            TRUE if this successful, FALSE otherwise.
 */

BOOL CPatronFrame::FPreShowInit(void)
    {
    //Base class does nothing
    CFrame::FPreShowInit();

    //Save the window handle for shutdown if necessary.
    g_hWnd=m_hWnd;

    //If we're -Embedding, don't show the window initially.
    if (m_fEmbedding)
        m_nCmdShow=SW_HIDE;

    return TRUE;
    }



/*
 * CPatronFrame::ParseCommandLine
 *
 * Purpose:
 *  Allows the application to parse the command line and take action
 *  after the window has possibly been shown.  For a compound
 *  document server we need to just make sure that if -Embedding is
 *  there that we take no file action.  FPreShowInit has already
 *  handled the window visibility.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  BOOL            TRUE if this successful, FALSE otherwise.
 */

void CPatronFrame::ParseCommandLine(void)
    {
    //If -Embedding was there, prevent any attempt to load a file.
    if (m_fEmbedding)
        return;

    CFrame::ParseCommandLine();
    return;
    }





/*
 * CPatronFrame::OnCommand
 *
 * Purpose:
 *  WM_COMMAND handler for the Patron frame window that processes extra
 *  File menu items as well as the Page menu.
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
    BOOL            fTemp;

    COMMANDPARAMS(wID, wCode, hWndMsg);

    /*
     * Don't bother with anything during first initialization,
     * skipping many GizmoBar notifications.
     */
    if (m_fInit)
        return 0L;

    pDoc=(PCPatronDoc)m_pCL->ActiveDocument();

    //Also check for the open command now too.
    if (NULL!=pDoc && ((IDM_VERBMIN <= wID) && (IDM_VERBMAX >= wID)
        || IDM_OPENOBJECT==wID))
        {
        MSG     msg;
        DWORD   dw;
        LONG    iVerb=(long)(wID-IDM_VERBMIN);

        //Include a message for in-place objects.
        msg.hwnd=NULL;
        msg.message=WM_COMMAND;
        msg.wParam=wParam;
        msg.lParam=lParam;
        msg.time=GetMessageTime();

        dw=GetMessagePos();
        SETPOINT(msg.pt, LOWORD(dw), HIWORD(dw));

        if (IDM_OPENOBJECT==wID)
            iVerb=OLEIVERB_OPEN;

        pDoc->ActivateObject(iVerb, &msg);
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
            pDoc->FPasteSpecial(m_hWnd);
            return 0L;

        case IDM_EDITDELETEOBJECT:
            pDoc->Delete();
            return 0L;

        case IDM_EDITINSERTOBJECT:
            pDoc->FInsertObject(m_hWnd);
            return 0L;

        case IDM_EDITLINKS:
            pDoc->FEditLinks(m_hWnd);
            return 0L;

        case IDM_EDITCONVERT:
            pDoc->FConvertObject(m_hWnd);
            return 0L;

        //CONTROLMOD
        case IDM_EDITOBJECTEVENTS:
            pDoc->AssignEvents(m_hWnd);
            break;
        //End CONTROLMOD

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
            //First get the current state, then toggle it.
            fTemp=pDoc->FShowOrQueryObjectTypes(TRUE, FALSE);
            pDoc->FShowOrQueryObjectTypes(FALSE, !fTemp);
            break;

        //CONTROLMOD
        case IDM_PAGEDESIGNMODE:
            //Get the current state and toggle it.
            fTemp=pDoc->FToggleOrQueryDesignMode(TRUE, FALSE);
            pDoc->FToggleOrQueryDesignMode(FALSE, !fTemp);
            break;
        //End CONTROLMOD

        case IDM_ENTERCONTEXTHELP:
        case IDM_ESCAPECONTEXTHELP:
            //Notify the object on entry and exit.
            ContextSensitiveHelp(IDM_ENTERCONTEXTHELP==wID);
            break;

        default:
           return CFrame::OnCommand(hWnd, wParam, lParam);
        }

    return 0L;
    }








/*
 * CPatronFrame::CreateGizmos
 *
 * Purpose:
 *  Procedure to create all the necessary gizmobar buttons.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  UINT            Number of gizmos added to the bar.
 */

UINT CPatronFrame::CreateGizmos(void)
    {
    UINT            iLast;
    UINT            uState=GIZMO_NORMAL;
    UINT            utCmd =GIZMOTYPE_BUTTONCOMMAND;

    //Insert the standard ones.
    iLast=CFrame::CreateGizmos();

    //Remove Undo:  we don't use it.
    m_pGB->Remove(IDM_EDITUNDO);

    /*
     * Insert Print File Import in the 5th position and account
     * for it in iLast.
     */
    m_pGB->Add(utCmd, 4, IDM_FILEPRINT, m_dxB, m_dyB
        , NULL, NULL, 6, uState);

    iLast++;

    m_pGB->Add(GIZMOTYPE_SEPARATOR, iLast++, 0, 6, m_dyB
        , NULL, NULL, 0, uState);

    //Add New Page, and Delete Page
    m_pGB->Add(utCmd, iLast++, IDM_PAGENEWPAGE, m_dxB, m_dyB
        , NULL, m_hBmp, 2, uState);
    m_pGB->Add(utCmd, iLast++, IDM_PAGEDELETEPAGE, m_dxB, m_dyB
        , NULL, m_hBmp, 3, uState);

    m_pGB->Add(GIZMOTYPE_SEPARATOR, iLast++, 0, 6, m_dyB
        , NULL, NULL, 0, uState);

    //First, Prev, Next, Last pages.
    m_pGB->Add(utCmd, iLast++, IDM_PAGEFIRSTPAGE, m_dxB, m_dyB
        , NULL, m_hBmp, 4, uState);
    m_pGB->Add(utCmd, iLast++, IDM_PAGEPREVIOUSPAGE, m_dxB, m_dyB
        , NULL, m_hBmp, 5, uState);
    m_pGB->Add(utCmd, iLast++, IDM_PAGENEXTPAGE, m_dxB, m_dyB
        , NULL, m_hBmp, 6, uState);
    m_pGB->Add(utCmd, iLast++, IDM_PAGELASTPAGE, m_dxB, m_dyB
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
        fOK=FALSE;

        if (NULL!=pDoc)
            fOK=pDoc->FQueryObjectSelected(hMenu);

        EnableMenuItem(hMenu, IDM_EDITCUT, (fOK) ? uTempE : uTempD);
        EnableMenuItem(hMenu, IDM_EDITCOPY
            , (fOK) ? uTempE : uTempD);
        EnableMenuItem(hMenu, IDM_EDITDELETEOBJECT
            , (fOK) ? uTempE : uTempD);

        EnableMenuItem(hMenu, IDM_EDITINSERTOBJECT, uTemp);

        fOK=FALSE;

        if (NULL!=pDoc)
            fOK=pDoc->FQueryEnableEditLinks();

        EnableMenuItem(hMenu, IDM_EDITLINKS
            , (fOK) ? uTempE : uTempD);

        //CONTROLMOD
        //Enable Events... if we have a control
        fOK=FALSE;

        if (NULL!=pDoc)
            fOK=pDoc->FQueryEnableEvents();

        EnableMenuItem(hMenu, IDM_EDITOBJECTEVENTS
            , (fOK) ? uTempE : uTempD);
        //End CONTROLMOD

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
            fOK=pDoc->FShowOrQueryObjectTypes(TRUE, FALSE);
        else
            fOK=FALSE;

        CheckMenuItem(hMenu, IDM_PAGESHOWOBJECTS, MF_BYCOMMAND
            | ((fOK) ? MF_CHECKED : MF_UNCHECKED));
        EnableMenuItem(hMenu, IDM_PAGESHOWOBJECTS, uTemp);

        //CONTROLMOD
        //Check the Design Mode command or not.
        if (NULL!=pDoc)
            fOK=pDoc->FToggleOrQueryDesignMode(TRUE, FALSE);
        else
            fOK=FALSE;

        CheckMenuItem(hMenu, IDM_PAGEDESIGNMODE, MF_BYCOMMAND
            | ((fOK) ? MF_CHECKED : MF_UNCHECKED));
        EnableMenuItem(hMenu, IDM_PAGEDESIGNMODE, uTemp);
        //End CONTROLMOD
        }

    if (fCallDefault)
        CFrame::UpdateMenus(hMenu, iMenu);

    return;
    }






/*
 * CPatronFrame::UpdateGizmos
 *
 * Purpose:
 *  Enables and disables gizmos depending on whether we have
 *  a document or not.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  None
 */

void CPatronFrame::UpdateGizmos(void)
    {
    PCDocument  pDoc;
    BOOL        fEnable;

    //Let the default hack on its gizmos.
    CFrame::UpdateGizmos();

    pDoc=m_pCL->ActiveDocument();
    fEnable=(NULL!=pDoc);

    //No document, disable just about everything
    m_pGB->Enable(IDM_FILEPRINT,        fEnable);
    m_pGB->Enable(IDM_FILEPRINTERSETUP, fEnable);

    m_pGB->Enable(IDM_PAGENEWPAGE,      fEnable);
    m_pGB->Enable(IDM_PAGEDELETEPAGE,   fEnable);
    m_pGB->Enable(IDM_PAGEFIRSTPAGE,    fEnable);
    m_pGB->Enable(IDM_PAGEPREVIOUSPAGE, fEnable);
    m_pGB->Enable(IDM_PAGENEXTPAGE,     fEnable);
    m_pGB->Enable(IDM_PAGELASTPAGE,     fEnable);

    return;
    }





/*
 * CPatronFrame::MessageLoop
 *
 * Purpose:
 *  Override of standard message loop function in CLASSLIB to use
 *  in-place accelerators when necessary.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  WPARAM          Contents of msg.wParam from WM_QUIT.
 */

WPARAM CPatronFrame::MessageLoop(void)
    {
    MSG     msg;

    while (GetMessage(&msg, NULL, 0,0 ))
        {
        HACCEL      hAccel=m_hAccel;

        //Always give the object first crack at translation.
        if (NULL!=m_pIOleIPActiveObject)
            {
            HRESULT     hr;

            hAccel=m_hAccelIP;
            hr=m_pIOleIPActiveObject->TranslateAccelerator(&msg);

            //If the object translated the accelerator, we're done
            if (NOERROR==hr)
                continue;
            }

        if (!m_pCL->TranslateAccelerator(&msg))
            {
            //hAccel is either the normal ones or the in-place ones.

            if (!::TranslateAccelerator(m_hWnd, hAccel, &msg))
                {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
                }
            }
        }

    return msg.wParam;
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
    int         dx, dy;
    MENUSELECTPARAMS(wItem, wMenuFlags, hMenu);

    *pLRes=0;

    /*
     * We use a switch now because we previously only processed
     * WM_MENUSELECT which did not use a case statement.
     */

    switch (iMsg)
        {
        case WM_SIZE:
            if (NULL!=m_pIOleIPActiveObject)
                {
                RECT        rc;

                GetClientRect(m_hWnd, &rc);
                m_pIOleIPActiveObject->ResizeBorder(&rc
                    , this, TRUE);
                }

            /*
             * If we're not showing our tools, don't let CLASSLIB
             * resize the client, instead doing it ourselves.
             */
            if (m_fOurToolsShowing)
                return FALSE;

            m_fSizing=TRUE;
            dx=LOWORD(lParam);
            dy=HIWORD(lParam);

            //Change the GizmoBar and StatStrip widths to match
            m_pGB->OnSize(hWnd);
            m_pSS->OnSize(hWnd);

            //Adjust the client properly, remembering the StatStrip.
            m_pCL->OnSize(m_cxLeft, m_cyTop, dx-m_cxLeft-m_cxRight
                , dy-m_cyTop-m_cyBottom-CYSTATSTRIP);

            m_fSizing=FALSE;
            return TRUE;

        case WM_ACTIVATEAPP:
            if (NULL!=m_pIOleIPActiveObject)
                {
                m_pIOleIPActiveObject->OnFrameWindowActivate
                    ((BOOL)wParam);
                }

            return FALSE;

        case WM_SETFOCUS:
            if (NULL!=m_pIOleIPActiveObject)
                {
                HWND    hWndObj;

                m_pIOleIPActiveObject->GetWindow(&hWndObj);
                SetFocus(hWndObj);
                }

            return TRUE;

        case WM_CLOSE:
            if (NULL!=m_pDocCreated)
                {
                if (m_pDocCreated->FDirtyGet())
                    {
                    CHourglass  wait;
                    m_pDocCreated->USave(0, NULL);
                    }
                }

            return FALSE;

        case WM_MENUSELECT:
            break;      //Continue processing below.

        default:
            return FALSE;
        }

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
        fRet=((HMENU)wItem==GetSubMenu(m_phMenu[1],MENUPOS_OBJECT));
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
        m_pSS->MessageDisplay(IDM_EDITOBJECT);

    return fRet;
    }





/*
 * CPatronFrame::ShowUIAndTools
 *
 * Purpose:
 *  Installs or removes the in-place user interface which includes
 *  the menus and the tools.  The tools may be affected outside of
 *  the menu.
 *
 * Parameters:
 *  fShow           BOOL indicating to show (TRUE) or hide (FALSE)
 *  fMenu           BOOl indicating if the menu is also affected.
 *
 * Return Value:
 *  None
 */

void CPatronFrame::ShowUIAndTools(BOOL fShow, BOOL fMenu)
    {
    HWND    hWndGB;

    //This is the only menu case...restore our original menu
    if (fMenu && fShow)
        SetMenu(NULL, NULL, NULL);

    /*
     * If we're trying to hide our tools but the object didn't
     * want any space, then just leave our tools up and active.
     */

    hWndGB=m_pGB->Window();
    ShowWindow(hWndGB, fShow ? SW_SHOW : SW_HIDE);

    if (fShow)
        {
        InvalidateRect(hWndGB, NULL, TRUE);
        UpdateWindow(hWndGB);
        }

    m_fOurToolsShowing=fShow;
    return;
    }




/*
 * CPatronFrame::ReinstateUI
 *
 * Purpose:
 *  Reinstalls the application's normal toolbar and menu and
 *  readjusts the position of the client window and the documents
 *  within it.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  None
 */

void CPatronFrame::ReinstateUI(void)
    {
    BORDERWIDTHS    bw;

    ShowUIAndTools(TRUE, TRUE);

    SetRect((LPRECT)&bw, 0, m_cyBar, 0, 0);
    SetBorderSpace(&bw);
    return;
    }



/*
 * CPatronFrame::QueryInterface
 * CPatronFrame::AddRef
 * CPatronFrame::Release
 *
 * Purpose:
 *  IUnknown members for CPatronFrame object.
 */

STDMETHODIMP CPatronFrame::QueryInterface(REFIID riid, PPVOID ppv)
    {
    //We only know IUnknown and IOleInPlaceFrame
    *ppv=NULL;

    //Remember to do ALL base interfaces
    if (IID_IUnknown==riid || IID_IOleInPlaceUIWindow==riid
        || IID_IOleWindow==riid || IID_IOleInPlaceFrame==riid)
        *ppv=(LPOLEINPLACEFRAME)this;

    if (NULL!=*ppv)
        {
        ((LPUNKNOWN)*ppv)->AddRef();
        return NOERROR;
        }

    return ResultFromScode(E_NOINTERFACE);
    }


STDMETHODIMP_(ULONG) CPatronFrame::AddRef(void)
    {
    return ++m_cRef;
    }

STDMETHODIMP_(ULONG) CPatronFrame::Release(void)
    {
    /*
     * We don't do anything with this since we're not controlled
     * by a reference count as far as in-place stuff is concerned.
     */
    return --m_cRef;
    }




/*
 * CPatronFrame::GetWindow
 *
 * Purpose:
 *  Retrieves the handle of the window associated with the object
 *  on which this interface is implemented.
 *
 * Parameters:
 *  phWnd           HWND * in which to store the window handle.
 *
 * Return Value:
 *  HRESULT         NOERROR if successful, E_FAIL if there is no
 *                  window.
 */

STDMETHODIMP CPatronFrame::GetWindow(HWND *phWnd)
    {
    *phWnd=m_hWnd;
    return NOERROR;
    }




/*
 * CPatronFrame::ContextSensitiveHelp
 *
 * Purpose:
 *  Instructs the object on which this interface is implemented to
 *  enter or leave a context-sensitive help mode.
 *
 * Parameters:
 *  fEnterMode      BOOL TRUE to enter the mode, FALSE otherwise.
 *
 * Return Value:
 *  HRESULT         NOERROR
 */

STDMETHODIMP CPatronFrame::ContextSensitiveHelp(BOOL fEnterMode)
    {
    /*
     * Don't bother if there is no active object since we don't do
     * context help on our own.
     */
    if (NULL==m_pIOleIPActiveObject)
        return NOERROR;

    /*
     * If the state changes, an MDI frame should call the same
     * function in all documents.  An SDI frame should just call
     * the active object, if it has one.
     */

    if (m_fInContextHelp!=fEnterMode)
        {
        m_fInContextHelp=fEnterMode;

       #ifdef MDI
        ((PCPatronClient)m_pCL)->CallContextHelpOnDocuments
           (fEnterMode);
       #else
        m_pIOleIPActiveObject->ContextSensitiveHelp(fEnterMode);
       #endif
        }

    return NOERROR;
    }




/*
 * CPatronFrame::GetBorder
 *
 * Purpose:
 *  Returns the rectangle in which the container is willing to
 *  negotiate about an object's adornments.
 *
 * Parameters:
 *  prcBorder       LPRECT in which to store the rectangle.
 *
 * Return Value:
 *  HRESULT         NOERROR if all is well, INPLACE_E_NOTOOLSPACE
 *                  if there is no negotiable space.
 */

STDMETHODIMP CPatronFrame::GetBorder(LPRECT prcBorder)
    {
    if (NULL==prcBorder)
        return ResultFromScode(E_INVALIDARG);

    /*
     * We return all the client area space sans the StatStrip,
     * which we control
     */
    GetClientRect(m_hWnd, prcBorder);
    prcBorder->bottom-=CYSTATSTRIP;

    return NOERROR;
    }




/*
 * CPatronFrame::RequestBorderSpace
 *
 * Purpose:
 *  Asks the container if it can surrender the amount of space
 *  in pBW that the object would like for it's adornments.  The
 *  container does nothing but validate the spaces on this call.
 *
 * Parameters:
 *  pBW             LPCBORDERWIDTHS containing the requested space.
 *                  The values are the amount of space requested
 *                  from each side of the relevant window.
 *
 * Return Value:
 *  HRESULT         NOERROR if we can give up space,
 *                  INPLACE_E_NOTOOLSPACE otherwise.
 */

STDMETHODIMP CPatronFrame::RequestBorderSpace(LPCBORDERWIDTHS pBW)
    {
    //Everything is fine with us, so always return an OK.
    return NOERROR;
    }




/*
 * CPatronFrame::SetBorderSpace
 *
 * Purpose:
 *  Called when the object now officially requests that the
 *  container surrender border space it previously allowed
 *  in RequestBorderSpace.  The container should resize windows
 *  appropriately to surrender this space.
 *
 * Parameters:
 *  pBW             LPCBORDERWIDTHS containing the amount of space
 *                  from each side of the relevant window that the
 *                  object is now reserving.
 *
 * Return Value:
 *  HRESULT         NOERROR
 */

STDMETHODIMP CPatronFrame::SetBorderSpace(LPCBORDERWIDTHS pBW)
    {
    RECT            rc;
    POINT           pt1, pt2;
    PCPatronDoc     pDoc;

    pDoc=(PCPatronDoc)m_pCL->ActiveDocument();

    /*
     * If pBW is NULL, the object is not interested in tools, so we
     * can just leave ours up if we want.
     */

    if (NULL==pBW)
        {
        if (NULL!=pDoc)
            {
            pDoc->NoObjectFrameTools(TRUE, TRUE);

            /*
             * In some cases IOleInPlaceSite::OnUIActivate might
             * have been called before SetBorderSpace, so we might
             * have already hidden our tools (OnUIActivate calls
             * pDoc->NoObjectFrameTools before we set it to TRUE
             * here).  So we have to insure they are visible now
             * by a call to ShowUIAndTools.
             */
            if (!m_fOurToolsShowing)
                ShowUIAndTools(TRUE, FALSE);
            }

        return NOERROR;
        }

    if (NULL!=pDoc)
        pDoc->NoObjectFrameTools(FALSE, TRUE);

    /*
     * This tells CFrame::FMessageHook (WM_SIZE) how much space
     * to reserve off the sides when resizing the client when
     * the frame is resized.
     */

    m_cyTop   =pBW->top;
    m_cyBottom=pBW->bottom;
    m_cxLeft  =pBW->left;
    m_cxRight =pBW->right;


    //Get the current offset of the client
    GetWindowRect(m_pCL->Window(), &rc);
    SETPOINT(pt1, rc.left, rc.top);
    SETPOINT(pt2, rc.right, rc.bottom);
    ScreenToClient(m_hWnd, &pt1);
    ScreenToClient(m_hWnd, &pt2);

    /*
     * Now move the client, keeping documents steady. pBW->left-pt.x
     * and pBW->top-pt.y are the deltas for the documents.
     */

    GetClientRect(m_hWnd, &rc);
    rc.left+=pBW->left;
    rc.right-=pBW->right;
    rc.top+=pBW->top;
    rc.bottom-=pBW->bottom+CYSTATSTRIP; //Remember the status line

    //Only bother the client if necessary.
    if (!(pt1.x==rc.left && pt1.y==rc.top
        && pt2.x==rc.right && pt2.y==rc.bottom))
        {
        ((PCPatronClient)m_pCL)->MoveWithoutFamily(&rc
            , pBW->left-pt1.x, pBW->top-pt1.y);
        }

    return NOERROR;
    }




/*
 * CPatronFrame::SetActiveObject
 *
 * Purpose:
 *  Provides the container with the object's IOleInPlaceActiveObject
 *  pointer and a name of the object to show in the container's
 *  caption.
 *
 * Parameters:
 *  pIIPActiveObj   LPOLEINPLACEACTIVEOBJECT of interest.
 *  pszObj          LPCTSTR to use in the container's caption bar.
 *
 * Return Value:
 *  HRESULT         NOERROR
 */

STDMETHODIMP CPatronFrame::SetActiveObject
    (LPOLEINPLACEACTIVEOBJECT pIIPActiveObj, LPCTSTR pszObj)
    {
   #ifndef MDI
    PCDocument      pDoc;

    pDoc=m_pCL->ActiveDocument();

    if (NULL!=pIIPActiveObj)
        {
        TCHAR       szPath[CCHPATHMAX];
        TCHAR       szFile[40];

        //For SDI, we have to change the caption bar
        pDoc->FilenameGet(szPath, CCHPATHMAX);

        if (0==szPath[0])
            lstrcpy(szFile, PSZ(IDS_UNTITLED));
        else
            {
            GetFileTitle(szPath, szFile, sizeof(szFile));

           #ifndef WIN32
            //Force filenames to uppercase in DOS versions.
            AnsiUpper(szFile);
           #endif
            }

        wsprintf(szPath, PSZ(IDS_IPFRAMECAPTION), pszObj
            , (LPTSTR)szFile);
        SetWindowText(m_hWnd, szPath);
        }
    else
        {
        //Set the title back to normal.
        m_pAdv->OnCaptionChange(pDoc);
        }
   #endif

    if (NULL!=m_pIOleIPActiveObject)
        m_pIOleIPActiveObject->Release();

    //This will set our member to NULL on deactivation
    m_pIOleIPActiveObject=pIIPActiveObj;

    if (NULL!=m_pIOleIPActiveObject)
        m_pIOleIPActiveObject->AddRef();

    return NOERROR;
    }




/*
 * CPatronFrame::InsertMenus
 *
 * Purpose:
 *  Instructs the container to place its in-place menu items where
 *  necessary in the given menu and to fill in elements 0, 2, and 4
 *  of the OLEMENUGROUPWIDTHS array to indicate how many top-level
 *  items are in each group.
 *
 * Parameters:
 *  hMenu           HMENU in which to add popups.
 *  pMGW            LPOLEMENUGROUPWIDTHS in which to store the
 *                  width of each container menu group.
 *
 * Return Value:
 *  HRESULT         NOERROR
 */

STDMETHODIMP CPatronFrame::InsertMenus(HMENU hMenu
    , LPOLEMENUGROUPWIDTHS pMGW)
    {
    /*
     * Here Patron needs to copy it's File, Page, and Window menu
     * items into the object-supplied menu, meaning that we have
     * three menu groups.  The actual handles of these popup menus
     * are already in CPatronFrame::m_phMenu where File is element
     * 0 and Page is element 2, and in m_hMenuWindow which is the
     * Window menu.  The latter we do only for MDI, of course.
     */

    InsertMenu(hMenu, 0, MF_BYPOSITION | MF_POPUP, (UINT)m_phMenu[0]
        , PSZ(IDS_FILEMENU));
    InsertMenu(hMenu, 1, MF_BYPOSITION | MF_POPUP, (UINT)m_phMenu[2]
        , PSZ(IDS_PAGEMENU));

    pMGW->width[0]=1;
    pMGW->width[2]=1;

   #ifdef MDI
    InsertMenu(hMenu, 2, MF_BYPOSITION | MF_POPUP
       , (UINT)m_hMenuWindow, PSZ(IDS_WINDOWMENU));

    pMGW->width[4]=1;
   #else
    pMGW->width[4]=0;
   #endif

    return NOERROR;
    }




/*
 * CPatronFrame::SetMenu
 *
 * Purpose:
 *  Instructs the container to replace whatever menu it's currently
 *  using with the given menu and to call OleSetMenuDescritor so OLE
 *  knows to whom to dispatch messages.
 *
 * Parameters:
 *  hMenu           HMENU to show.
 *  hOLEMenu        HOLEMENU to the menu descriptor.
 *  hWndObj         HWND of the active object to which messages are
 *                  dispatched.
 * Return Value:
 *  HRESULT         NOERROR
 */

STDMETHODIMP CPatronFrame::SetMenu(HMENU hMenu
    , HOLEMENU hOLEMenu, HWND hWndObj)
    {
    HRESULT         hr;
    PCPatronClient  pCL=(PCPatronClient)m_pCL;

    /*
     * Our responsibilities here are to put the menu on the frame
     * window and call OleSetMenuDescriptor.
     * CPatronClient::SetMenu which we call here takes care of
     * MDI/SDI differences.
     *
     * We also want to save the object's hWnd for use in WM_SETFOCUS
     * processing.
     */

    if (NULL==hMenu)
        {
        m_hWndObj=NULL;

        //Prevent redundant calls, or debug warnings on startup.
        if (NULL==m_hMenuTop)
            return NOERROR;

        hMenu=m_hMenuTop;
        m_hMenuTop=NULL;
        }
    else
        {
        m_hMenuTop=m_hMenuOrg;
        m_hWndObj=hWndObj;
        }

    pCL->SetMenu(m_hWnd, hMenu, m_hMenuWindow);
    hr=OleSetMenuDescriptor(hOLEMenu, m_hWnd, hWndObj, NULL, NULL);
    return hr;
    }




/*
 * CPatronFrame::RemoveMenus
 *
 * Purpose:
 *  Asks the container to remove any menus it put into hMenu in
 *  InsertMenus.
 *
 * Parameters:
 *  hMenu           HMENU from which to remove the container's
 *                  items.
 *
 * Return Value:
 *  HRESULT         NOERROR
 */

STDMETHODIMP CPatronFrame::RemoveMenus(HMENU hMenu)
    {
    int         cItems, i, j;
    HMENU       hMenuT;

    /*
     * To be defensive, loop through this menu removing anything
     * we recognize (that is, anything in m_phMenu) just in case
     * the server didn't clean it up right.  At least we can
     * give ourselves the prophylactic benefit.
     */

    if (NULL==hMenu)
        return NOERROR;

    cItems=GetMenuItemCount(hMenu);

    /*
     * Walk backwards down the menu.  For each popup, see if it
     * matches any other popup we know about, and if so, remove
     * it from the shared menu.
     */
    for (i=cItems; i >=0; i--)
        {
        hMenuT=GetSubMenu(hMenu, i);

        for (j=0; j <= CMENUS; j++)
            {
            if (hMenuT==m_phMenu[j])
                RemoveMenu(hMenu, i, MF_BYPOSITION);
            }
        }

    //The menu should now be empty.
    return NOERROR;
    }




/*
 * CPatronFrame::SetStatusText
 *
 * Purpose:
 *  Asks the container to place some text in a status line, if one
 *  exists.  If the container does not have a status line it
 *  should return E_FAIL here in which case the object could
 *  display its own.
 *
 * Parameters:
 *  pszText         LPCTSTR to display.
 *
 * Return Value:
 *  HRESULT         NOERROR if successful, S_TRUNCATED if not all
 *                  of the text could be displayed, or E_FAIL if
 *                  the container has no status line.
 */

STDMETHODIMP CPatronFrame::SetStatusText(LPCTSTR pszText)
    {
    /*
     * Just send this to the StatStrip.  Unfortunately it won't tell
     * us about truncation.  Oh well, we'll just act like it worked.
     */
    m_pSS->MessageSet((LPTSTR)pszText);

    return NOERROR;
    }




/*
 * CPatronFrame::EnableModeless
 *
 * Purpose:
 *  Instructs the container to show or hide any modeless popup
 *  windows that it may be using.
 *
 * Parameters:
 *  fEnable         BOOL indicating to enable/show the windows
 *                  (TRUE) or to hide them (FALSE).
 *
 * Return Value:
 *  HRESULT         NOERROR
 */

STDMETHODIMP CPatronFrame::EnableModeless(BOOL fEnable)
    {
    return NOERROR;
    }




/*
 * CPatronFrame::TranslateAccelerator
 *
 * Purpose:
 *  When dealing with an in-place object from an EXE server, this
 *  is called to give the container a chance to process accelerators
 *  after the server has looked at the message.
 *
 * Parameters:
 *  pMSG            LPMSG for the container to examine.
 *  wID             WORD the identifier in the container's
 *                  accelerator table (from IOleInPlaceSite
 *                  ::GetWindowContext) for this message (OLE does
 *                  some translation before calling).
 *
 * Return Value:
 *  HRESULT         NOERROR if the keystroke was used,
 *                  S_FALSE otherwise.
 */

STDMETHODIMP CPatronFrame::TranslateAccelerator(LPMSG pMSG, WORD wID)
    {
    SCODE       sc;

    /*
     * wID already has anything translated from m_hAccelIP for us,
     * so we can just check for the commands we want and process
     * them instead of calling TranslateAccelerator which would be
     * redundant and which also has a possibility of dispatching to
     * the wrong window.
     */
    if ((IDM_PAGENEWPAGE <= wID && IDM_PAGELASTPAGE >= wID)
        || IDM_OPENOBJECT==wID || IDM_ENTERCONTEXTHELP==wID
        || IDM_ESCAPECONTEXTHELP==wID)
        {
        //wID properly expands to 32-bits
        OnCommand(m_hWnd, (WPARAM)wID, 0L);
        sc=S_OK;
        }
   #ifdef MDI
    else if (TranslateMDISysAccel(m_pCL->Window(), pMSG))
        sc=S_OK;
   #endif
    else
        sc=S_FALSE;

    return ResultFromScode(sc);
    }
