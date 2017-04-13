/*
 * PATRON.CPP
 * Patron Chapter 24
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

ULONG       g_cObj=0;
ULONG       g_cLock=0;
HWND        g_hWnd=NULL;
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

    SETMESSAGEQUEUE;

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
    if (pFR->Init(&fi))
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
 */

void ObjectDestroyed(void)
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
    m_fInitialized=FALSE;
    m_pIClassDataTran=NULL;

    m_pDocCreated=NULL;
    m_fEmbedding=FALSE;

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
    ReleaseInterface(m_pIClassFactory);

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
    BOOL        fRet;

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

    //Load in-place accelerators
    m_hAccelIP=LoadAccelerators(m_hInst
        , MAKEINTRESOURCE(IDR_INPLACEACCELERATORS));

    if (NULL==m_hAccelIP)
        return FALSE;

    fRet=CFrame::Init(pFI);

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
    //CHAPTER24MOD
    BOOL            fTemp;
    //End CHAPTER24MOD

    COMMANDPARAMS(wID, wCode, hWndMsg);

    /*
     * Don't bother with anything during first initialization,
     * skipping many toolbar notifications.
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

        //CHAPTER24MOD
        case IDM_EDITOBJECTEVENTS:
            pDoc->AssignEvents(m_hWnd);
            break;
        //End CHAPTER24MOD

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

        //CHAPTER24MOD
        case IDM_PAGEDESIGNMODE:
            fTemp=pDoc->FToggleOrQueryDesignMode(TRUE, FALSE);
            pDoc->FToggleOrQueryDesignMode(FALSE, !fTemp);
            break;

        case IDM_PAGEUIDISABLED:
            fTemp=pDoc->FToggleOrQueryUIDead(TRUE, FALSE);
            pDoc->FToggleOrQueryUIDead(FALSE, !fTemp);
            break;

         case IDM_PAGESHOWHATCHHANDLES:
            fTemp=pDoc->FToggleOrQueryHatchHandles(TRUE, FALSE);
            pDoc->FToggleOrQueryHatchHandles(FALSE, !fTemp);
            break;
        //End CHAPTER24MOD

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

        //CHAPTER24MOD
        //Enable Events... if we have a control
        fOK=FALSE;

        if (NULL!=pDoc)
            fOK=pDoc->FQueryEnableEvents();

        EnableMenuItem(hMenu, IDM_EDITOBJECTEVENTS
            , (fOK) ? uTempE : uTempD);
        //End CHAPTER24MOD

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

        //CHAPTER24MOD
        //Check the Design Mode command or not.
        if (NULL!=pDoc)
            fOK=pDoc->FToggleOrQueryDesignMode(TRUE, FALSE);
        else
            fOK=FALSE;

        CheckMenuItem(hMenu, IDM_PAGEDESIGNMODE, MF_BYCOMMAND
            | ((fOK) ? MF_CHECKED : MF_UNCHECKED));
        EnableMenuItem(hMenu, IDM_PAGEDESIGNMODE, uTemp);

        //Check the UI Disabled command or not.
        if (NULL!=pDoc)
            fOK=pDoc->FToggleOrQueryUIDead(TRUE, FALSE);
        else
            fOK=FALSE;

        CheckMenuItem(hMenu, IDM_PAGEUIDISABLED, MF_BYCOMMAND
            | ((fOK) ? MF_CHECKED : MF_UNCHECKED));
        EnableMenuItem(hMenu, IDM_PAGEUIDISABLED, uTemp);

        //Check the Show Hatch and Handles command or not.
        if (NULL!=pDoc)
            fOK=pDoc->FToggleOrQueryHatchHandles(TRUE, FALSE);
        else
            fOK=FALSE;

        CheckMenuItem(hMenu, IDM_PAGESHOWHATCHHANDLES, MF_BYCOMMAND
            | ((fOK) ? MF_CHECKED : MF_UNCHECKED));
        EnableMenuItem(hMenu, IDM_PAGESHOWHATCHHANDLES, uTemp);
        //End CHAPTER24MOD
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
    //CHAPTER24MOD
    PCPatronDoc pDoc;
    MSG         msg;
    DWORD       dw;
    //End CHAPTER24MOD

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

            //Change the Toolbar and StatStrip widths to match
            m_pTB->OnSize(hWnd);
            m_pSL->OnSize(hWnd);

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
                    m_pDocCreated->Save(0, NULL);
                    }
                }

            return FALSE;

        case WM_MENUSELECT:
            break;      //Continue processing below.

        //CHAPTER24MOD
        /*
         * Keyboard mnemonics can be Control- or Alt-keys with
         * any other modifier.  That means WM_KEYDOWN with
         * Control on or WM_SYSKEYDOWN by itself.
         */
        case WM_KEYDOWN:
            //Filter out things without Control
            if (!(0x8000 & GetKeyState(VK_CONTROL)))
                return FALSE;

            //FALL-THROUGH

        case WM_SYSKEYDOWN:
            pDoc=(PCPatronDoc)m_pCL->ActiveDocument();

            if (NULL==pDoc)
                return FALSE;

            msg.hwnd=hWnd;
            msg.message=iMsg;
            msg.wParam=wParam;
            msg.lParam=lParam;
            msg.time=GetMessageTime();
            dw=GetMessagePos();
            msg.pt.x=LOWORD(dw);
            msg.pt.y=HIWORD(dw);
            return pDoc->TryMnemonic(&msg);
        //End CHAPTER24MOD

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
    HWND    hWndTB;

    //This is the only menu case...restore our original menu
    if (fMenu && fShow)
        SetMenu(NULL, NULL, NULL);

    /*
     * If we're trying to hide our tools but the object didn't
     * want any space, then just leave our tools up and active.
     */

    hWndTB=m_pTB->Window();
    ShowWindow(hWndTB, fShow ? SW_SHOW : SW_HIDE);

    if (fShow)
        {
        InvalidateRect(hWndTB, NULL, TRUE);
        UpdateWindow(hWndTB);
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
 */

STDMETHODIMP CPatronFrame::QueryInterface(REFIID riid, PPVOID ppv)
    {
    //We only know IUnknown and IOleInPlaceFrame
    *ppv=NULL;

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
 *  pointer
 *
 * Parameters:
 *  pIIPActiveObj   LPOLEINPLACEACTIVEOBJECT of interest.
 *  pszObj          LPCOLESTR naming the object.  Not used.
 *
 * Return Value:
 *  HRESULT         NOERROR
 */

STDMETHODIMP CPatronFrame::SetActiveObject
    (LPOLEINPLACEACTIVEOBJECT pIIPActiveObj, LPCOLESTR pszObj)
    {
    if (NULL!=m_pIOleIPActiveObject)
        m_pIOleIPActiveObject->Release();

    //NULLs m_pIOleIPActiveObject if pIIPActiveObj is NULL
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
 *  pszText         LPCOLESTR to display.
 *
 * Return Value:
 *  HRESULT         NOERROR if successful, S_TRUNCATED if not all
 *                  of the text could be displayed, or E_FAIL if
 *                  the container has no status line.
 */

STDMETHODIMP CPatronFrame::SetStatusText(LPCOLESTR pszText)
    {
    /*
     * Just send this to the StatStrip.  Unfortunately it won't tell
     * us about truncation.  Oh well, we'll just act like it worked.
     */
   #ifdef WIN32ANSI
    TCHAR       szTemp[256];

    WideCharToMultiByte(CP_ACP, 0, pszText, -1, szTemp, 256
        , NULL, NULL);
    m_pSL->MessageSet(szTemp);
   #else
    m_pSL->MessageSet((LPTSTR)pszText);
   #endif

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
