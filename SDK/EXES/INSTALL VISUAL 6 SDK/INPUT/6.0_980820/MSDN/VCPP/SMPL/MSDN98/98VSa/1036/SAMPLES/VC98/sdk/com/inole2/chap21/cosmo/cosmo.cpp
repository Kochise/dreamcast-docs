/*
 * COSMO.CPP
 * Cosmo Chapter 21
 *
 * WinMain and CCosmoFrame implementations.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#define INITGUIDS
#include "cosmo.h"

/*
 * These are for proper implementation of the class factory,
 * OLE Documents support, and shutdown conditions.
 */
ULONG g_cObj=0;
ULONG g_cLock=0;
HWND  g_hWnd=NULL;
BOOL  g_fUser=FALSE;


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
    PCCosmoFrame    pFR;
    FRAMEINIT       fi;
    WPARAM          wRet;

    SETMESSAGEQUEUE;

    //Attempt to allocate and initialize the application
    pFR=new CCosmoFrame(hInst, hPrev, pszCmdLine, nCmdShow);

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
    fi.cx=440;
    fi.cy=460;

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
 *  Function for the Cosmo Figure object to call when it gets
 *  destroyed.  We destroy the main window if the proper conditions
 *  are met for shutdown.
 */

void ObjectDestroyed(void)
    {
    g_cObj--;

    //No more objects, no locks, no user control, shut the app down.
    if (0L==g_cObj && 0L==g_cLock && IsWindow(g_hWnd) && !g_fUser)
        PostMessage(g_hWnd, WM_CLOSE, 0, 0L);

    return;
    }





/*
 * CCosmoFrame::CCosmoFrame
 * CCosmoFrame::~CCosmoFrame
 *
 * Constructor Parameters:
 *  hInst           HINSTANCE from WinMain
 *  hInstPrev       HINSTANCE from WinMain
 *  pszCmdLine      LPSTR from WinMain
 *  nCmdShow        int from WInMain
 */

CCosmoFrame::CCosmoFrame(HINSTANCE hInst, HINSTANCE hInstPrev
    , LPSTR pszCmdLine, int nCmdShow)
    : CFrame(hInst, hInstPrev, pszCmdLine, nCmdShow)
    {
    UINT        i;

    for (i=0; i<5; i++)
        m_hBmpLines[i]=NULL;

    m_uIDCurLine=0;
    m_fInitialized=FALSE;
    m_pIClassDataTran=NULL;

    m_fEmbedding=FALSE;
    m_dwRegCO=0;
    m_pIClassFactory=NULL;

    return;
    }


CCosmoFrame::~CCosmoFrame(void)
    {
    UINT        i;

    //Reverse CoRegisterClassObject, takes class factory ref to 1
    if (0L!=m_dwRegCO)
        CoRevokeClassObject(m_dwRegCO);

    ReleaseInterface(m_pIClassFactory);

    for (i=0; i<5; i++)
        {
        if (NULL!=m_hBmpLines[i])
            DeleteObject(m_hBmpLines[i]);
        }

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
 * CCosmoFrame::Init
 *
 * Purpose:
 *  Call CoInitialize then calling down into the base class
 *  initialization.
 *
 * Parameters:
 *  pFI             PFRAMEINIT containing initialization parameters.
 *
 * Return Value:
 *  BOOL            TRUE if initialization succeeded, FALSE otherwise.
 */

BOOL CCosmoFrame::Init(PFRAMEINIT pFI)
    {
    HRESULT     hr;

    CHECKVER_OLE;

    if (FAILED(OleInitialize(NULL)))
        return FALSE;

    m_fInitialized=TRUE;

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


    /*
     * Create our class factory and register it for this application
     * using CoRegisterClassObject.  The REGCLS_*USE flags have to
     * do with servicable object from this instance, not with MDI or
     * SDI.  Since it's most convenient to be single use, we'll do
     * this in either version.
     *
     * In addition, it only makes sense to do any of this if we're
     * being launched to be a server.
     */
    if (m_fEmbedding)
        {
        m_pIClassFactory=new CFigureClassFactory(this);

        if (NULL==m_pIClassFactory)
            return FALSE;

        //Since we hold on to this, we should AddRef it.
        m_pIClassFactory->AddRef();

        hr=CoRegisterClassObject(CLSID_CosmoFigure, m_pIClassFactory
            , CLSCTX_LOCAL_SERVER, REGCLS_SINGLEUSE, &m_dwRegCO);

        if (FAILED(hr))
            return FALSE;
        }

    return CFrame::Init(pFI);
    }



/*
 * CCosmoFrame::CreateCClient
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

PCClient CCosmoFrame::CreateCClient(void)
    {
    return (PCClient)(new CCosmoClient(m_hInst, this));
    }





/*
 * CCosmoFrame::RegisterAllClasses
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

BOOL CCosmoFrame::RegisterAllClasses(void)
    {
    WNDCLASS        wc;

    //First let the standard frame do its thing
    if (!CFrame::RegisterAllClasses())
        return FALSE;

    /*
     * We want a different background color for the document
     * because the Polyline we put in the document will paint
     * with COLOR_WINDOW which by default which is CLASSLIB's
     * default document color.
     */

    GetClassInfo(m_hInst, SZCLASSDOCUMENT, &wc);
    UnregisterClass(SZCLASSDOCUMENT, m_hInst);

    wc.hbrBackground=(HBRUSH)(COLOR_APPWORKSPACE+1);

    if (!RegisterClass(&wc))
        return FALSE;

    //Register the Polyline window.
    wc.style         = CS_HREDRAW | CS_VREDRAW;
    wc.hInstance     = m_hInst;
    wc.cbClsExtra    = 0;
    wc.lpfnWndProc   = PolylineWndProc;
    wc.cbWndExtra    = CBPOLYLINEWNDEXTRA;
    wc.hIcon         = NULL;
    wc.hCursor       = LoadCursor(NULL, IDC_CROSS);
    wc.hbrBackground = NULL;
    wc.lpszMenuName  = NULL;
    wc.lpszClassName = SZCLASSPOLYLINE;

    if (!RegisterClass(&wc))
        return FALSE;

    return TRUE;
    }






/*
 * CCosmoFrame::PreShowInit
 *
 * Purpose:
 *  Called from Init before intially showing the window.  We do
 *  whatever else we want here, modifying nCmdShow as necessary
 *  which affects ShowWindow in Init.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  BOOL            TRUE if this initialization succeeded,
 *                  FALSE otherwise.
 */

BOOL CCosmoFrame::PreShowInit(void)
    {
    CreateLineMenu();
    CheckLineSelection(IDM_LINESOLID);

    //Save the window handle for shutdown if necessary.
    g_hWnd=m_hWnd;

    //If we're under OLE control, don't show the main window.
    if (m_fEmbedding)
        m_nCmdShow=SW_HIDE;

    return TRUE;
    }



/*
 * CCosmoFrame::CreateLineMenu
 *
 * Purpose:
 *  Initializes the bitmaps used to create the Line menu and
 *  replaces the text items defined in the application resources
 *  with these bitmaps.  Note that the contents of m_hBmpLines
 *  must be cleaned up when the application terminates.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  None
 */

void CCosmoFrame::CreateLineMenu(void)
    {
    HMENU       hMenu;
    HDC         hDC, hMemDC;
    HPEN        hPen;
    HGDIOBJ     hObj;
    TEXTMETRIC  tm;
    UINT        i, cx, cy;


    hMenu=GetSubMenu(GetMenu(m_hWnd), 3);   //Line menu.
    hDC=GetDC(m_hWnd);

    //Create each line in a menu item 8 chars wide, one char high.
    GetTextMetrics(hDC, &tm);
    cx=tm.tmAveCharWidth*8;
    cy=tm.tmHeight;

    /*
     * Create a memory DC in which to draw lines, and bitmaps
     * for each line.
     */
    hMemDC=CreateCompatibleDC(hDC);
    ReleaseDC(m_hWnd, hDC);

    for (i=0; i<5; i++)
        {
        m_hBmpLines[i]=CreateCompatibleBitmap(hMemDC, cx, cy);
        SelectObject(hMemDC, m_hBmpLines[i]);

        PatBlt(hMemDC, 0, 0, cx, cy, WHITENESS);

        hPen=CreatePen(i, 1, 0L);       //i=line style like PS_SOLID
        hObj=SelectObject(hMemDC, hPen);

        MoveToEx(hMemDC, 0, cy/2, NULL);
        LineTo(hMemDC, cx, cy/2);

        ModifyMenu(hMenu, IDM_LINEMIN+i, MF_BYCOMMAND | MF_BITMAP
            , IDM_LINEMIN+i, (LPTSTR)(LONG)(UINT)m_hBmpLines[i]);

        SelectObject(hMemDC, hObj);
        DeleteObject(hPen);
        }

    CheckMenuItem(hMenu, IDM_LINESOLID, MF_CHECKED);
    DeleteDC(hMemDC);

    return;
    }









/*
 * CCosmoFrame::CreateToolbar
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

UINT CCosmoFrame::CreateToolbar(void)
    {
    UINT            iLast;
    UINT            uState=GIZMO_NORMAL;
    UINT            utCmd =GIZMOTYPE_BUTTONCOMMAND;
    UINT            utEx  =GIZMOTYPE_BUTTONATTRIBUTEEX;

    //Insert the standard ones.
    iLast=CFrame::CreateToolbar();

    /*
     * Insert File Import in the 5th position and account for
     * it in iLast.
     */
    m_pTB->Add(utCmd, 4, IDM_FILEIMPORT, m_dxB, m_dyB
        , NULL, m_hBmp, 2, uState);
    iLast++;

    //Separator
    m_pTB->Add(GIZMOTYPE_SEPARATOR, iLast++, 0, 6, m_dyB
        , NULL, NULL, 0, uState);

    /*
     * For the Background bitmap, preserve our use of black
     * (part of the image)
     */
    m_pTB->Add(utCmd, iLast++, IDM_COLORBACKGROUND, m_dxB, m_dyB
        , NULL, m_hBmp, 3, GIZMO_NORMAL | PRESERVE_BLACK);

    m_pTB->Add(utCmd, iLast++, IDM_COLORLINE, m_dxB, m_dyB
        , NULL, m_hBmp, 4, uState);

    //Separator
    m_pTB->Add(GIZMOTYPE_SEPARATOR, iLast++, 0, 6, m_dyB
        , NULL, NULL, 0, uState);

    //Line styles.
    m_pTB->Add(utEx, iLast++, IDM_LINESOLID, m_dxB, m_dyB
        , NULL, m_hBmp, 5, uState);
    m_pTB->Add(utEx, iLast++, IDM_LINEDASH, m_dxB, m_dyB
        , NULL, m_hBmp, 6, uState);
    m_pTB->Add(utEx, iLast++, IDM_LINEDOT, m_dxB, m_dyB
        , NULL, m_hBmp, 7, uState);
    m_pTB->Add(utEx, iLast++, IDM_LINEDASHDOT, m_dxB, m_dyB
        , NULL, m_hBmp, 8, uState);
    m_pTB->Add(utEx, iLast++, IDM_LINEDASHDOTDOT, m_dxB, m_dyB
        , NULL, m_hBmp, 9, uState);

    return iLast;
    }








/*
 * CCosmoFrame::OnCommand
 *
 * Purpose:
 *  WM_COMMAND handler for the Cosmo frame window that just
 *  processes the line menu and the color menu leaving the
 *  CFrame to do everything else.
 *
 * Parameters:
 *  hWnd            HWND of the frame window.
 *  wParam          WPARAM of the message.
 *  lParam          LPARAM of the message.
 *
 * Return Value:
 *  LRESULT         Return value for the message.
 */

LRESULT CCosmoFrame::OnCommand(HWND hWnd, WPARAM wParam
    , LPARAM lParam)
    {
    PCCosmoDoc      pDoc;
    TCHAR           szFile[CCHPATHMAX];
    BOOL            fOK;
    UINT            i, uTemp;
    COLORREF        rgColors[16];
    CHOOSECOLOR     cc;

    COMMANDPARAMS(wID, wCode, hWndMsg);

    /*
     * Don't bother with anything during first initialization,
     * skipping many toolbar notifications.
     */
    if (m_fInit)
        return 0L;

    pDoc=(PCCosmoDoc)m_pCL->ActiveDocument();

    /*
     * Check for the line style commands which are
     * IDM_LINEMIN+<style>.  We handle this by changing the menu
     * and toolbar, then we pass it to the document for real
     * processing.
     */
    if (NULL!=pDoc && IDM_LINEMIN <= wID && IDM_LINEMAX >=wID)
        {
        CheckLineSelection(wID);
        pDoc->LineStyleSet(wID-IDM_LINEMIN);
        return 0L;
        }

    switch (wID)
        {
        case IDM_FILEIMPORT:
            szFile[0]=0;
            fOK=SaveOpenDialog(szFile, CCHPATHMAX, IDS_FILEIMPORT
                , TRUE, &i);

            if (fOK)
                {
                uTemp=pDoc->Load(FALSE, szFile);
                pDoc->ErrorMessage(uTemp);
                }

            return (LRESULT)fOK;


        case IDM_COLORBACKGROUND:
        case IDM_COLORLINE:
            //Invoke the color chooser for either color
            uTemp=(IDM_COLORBACKGROUND==wID)
                ? DOCCOLOR_BACKGROUND : DOCCOLOR_LINE;

            for (i=0; i<16; i++)
                rgColors[i]=RGB(0, 0, i*16);

            memset(&cc, 0, sizeof(CHOOSECOLOR));
            cc.lStructSize=sizeof(CHOOSECOLOR);
            cc.lpCustColors=rgColors;
            cc.hwndOwner=hWnd;
            cc.Flags=CC_RGBINIT;
            cc.rgbResult=pDoc->ColorGet(uTemp);

            if (ChooseColor(&cc))
                pDoc->ColorSet(uTemp, cc.rgbResult);

            break;


        default:
           CFrame::OnCommand(hWnd, wParam, lParam);
        }

    return 0L;
    }






/*
 * CCosmoFrame::OnDocumentDataChange
 *
 * Purpose:
 *  Update the Line menu and toolbar if the style in the data
 *  changes.
 *
 * Parameters:
 *  pDoc            PCDocument notifying the sink.
 *
 * Return Value:
 *  None
 */

void CCosmoFrame::OnDocumentDataChange(PCDocument pDoc)
    {
    CheckLineSelection(IDM_LINEMIN
        +((PCCosmoDoc)pDoc)->LineStyleGet());
    return;
    }




/*
 * CCosmoFrame::OnDocumentActivate
 *
 * Purpose:
 *  Informs us that document activation changed, so update the UI
 *  for that new document.
 *
 * Parameters:
 *  pDoc            PCDocument notifying the sink.
 *
 * Return Value:
 *  None
 */

void CCosmoFrame::OnDocumentActivate(PCDocument pDoc)
    {
    CheckLineSelection(IDM_LINEMIN
        +((PCCosmoDoc)pDoc)->LineStyleGet());
    return;
    }







/*
 * CCosmoFrame::UpdateMenus
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

void CCosmoFrame::UpdateMenus(HMENU hMenu, UINT iMenu)
    {
    PCDocument  pDoc;
    BOOL        fOK=FALSE;
    BOOL        fCallDefault=TRUE;
    UINT        i;
    UINT        uTemp;
    UINT        uTempE;
    UINT        uTempD;

    pDoc=m_pCL->ActiveDocument();

    uTempE=MF_ENABLED | MF_BYCOMMAND;
    uTempD=MF_DISABLED | MF_GRAYED | MF_BYCOMMAND;
    uTemp=((NULL!=pDoc) ? uTempE : uTempD);

    //File menu:  If there is document window, disable Import.
    if (m_phMenu[0]==hMenu)
        EnableMenuItem(hMenu, IDM_FILEIMPORT, uTemp);

    //Color menu:  no document, no commands
    if (m_phMenu[2]==hMenu)
        {
        EnableMenuItem(hMenu, IDM_COLORBACKGROUND, uTemp);
        EnableMenuItem(hMenu, IDM_COLORLINE,       uTemp);
        fCallDefault=FALSE;
        }

    //Line menu:  no document, no commands
    if (m_phMenu[3]==hMenu)
        {
        for (i=IDM_LINEMIN; i<=IDM_LINEMAX; i++)
            EnableMenuItem(hMenu, i, uTemp);

        fCallDefault=FALSE;
        }

    if (fCallDefault)
        CFrame::UpdateMenus(hMenu, iMenu);

    return;
    }






/*
 * CCosmoFrame::UpdateToolbar
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

void CCosmoFrame::UpdateToolbar(void)
    {
    BOOL        fLast;
    UINT        i;

    //Save the last enabled state before CFrame changes it
    fLast=m_fLastEnable;

    //Let the default hack on its tools
    CFrame::UpdateToolbar();

    /*
     * If CFrame::UpdateToolbar changed anything, then we need
     * to change as well--if nothing changes, nothing to do.
     */
    if (fLast!=m_fLastEnable)
        {
        m_pTB->Enable(IDM_FILEIMPORT, m_fLastEnable);

        m_pTB->Enable(IDM_COLORBACKGROUND, m_fLastEnable);
        m_pTB->Enable(IDM_COLORLINE,       m_fLastEnable);

        for (i=IDM_LINEMIN; i <= IDM_LINEMAX; i++)
            m_pTB->Enable(i, m_fLastEnable);
        }

    return;
    }






/*
 * CCosmoFrame::CheckLineSelection
 *
 * Purpose:
 *  Maintains the bitmap menu and the tools for the line selection.
 *  Both are mutially exclusive option lists where a selection in
 *  one has to affect the other.
 *
 * Parameters:
 *  uID             UINT ID of the item to be selected
 *
 * Return Value:
 *  None
 */

void CCosmoFrame::CheckLineSelection(UINT uID)
    {
    UINT        i;
    HMENU       hMenu;

    //Update menus and tools if the selection changed.
    if (uID!=m_uIDCurLine)
        {
        m_uIDCurLine=uID;
        hMenu=GetMenu(m_hWnd);

        //Uncheck all lines initially.
        for (i=IDM_LINEMIN; i<=IDM_LINEMAX; i++)
            CheckMenuItem(hMenu, i, MF_UNCHECKED | MF_BYCOMMAND);

        CheckMenuItem(hMenu, uID, MF_CHECKED | MF_BYCOMMAND);
        m_pTB->Check(uID, TRUE);
        }

    return;
    }



/*
 * CCosmoFrame::UpdateEmbeddingUI
 *
 * Purpose:
 *  Puts the application into the user interface for editing an
 *  embedded object, manipulating menus and title bars.
 *
 * Parameters:
 *  fEmbedding      BOOL TRUE to go in the mode, FALSE to leave it.
 *  pszApp          LPCTSTR name of the container application as
 *                  received in IOleObject::SetHostNames.
 *  pszObj          LPCTSTR name of the object in the container as
 *                  received in IOleObject::SetHostNames.
 *
 * Return Value:
 *  None
 */

void CCosmoFrame::UpdateEmbeddingUI(BOOL fEmbedding
    , PCDocument pDoc, LPCTSTR pszApp, LPCTSTR pszObj)
    {
    HMENU           hMenu;
    TCHAR           szTemp[256];

    //First let's play with the File menu.
    hMenu=m_phMenu[0];

    //Remove or add the File New, Open, and Save items
    if (fEmbedding)
        {
        DeleteMenu(m_phMenu[0], IDM_FILENEW,   MF_BYCOMMAND);
        DeleteMenu(m_phMenu[0], IDM_FILEOPEN,  MF_BYCOMMAND);
        DeleteMenu(m_phMenu[0], IDM_FILECLOSE, MF_BYCOMMAND);
        DeleteMenu(m_phMenu[0], IDM_FILESAVE,  MF_BYCOMMAND);

        //Save As->Save Copy As
        ModifyMenu(m_phMenu[0], IDM_FILESAVEAS, MF_BYCOMMAND
            , IDM_FILESAVEAS, PSZ(IDS_SAVECOPYAS));
        }
    else
        {
        InsertMenu(m_phMenu[0], 0, MF_BYPOSITION, IDM_FILENEW
            , PSZ(IDS_NEW));
        InsertMenu(m_phMenu[0], 1, MF_BYPOSITION, IDM_FILEOPEN
            , PSZ(IDS_OPEN));
        InsertMenu(m_phMenu[0], 2, MF_BYPOSITION, IDM_FILESAVE
            , PSZ(IDS_SAVE));
        InsertMenu(m_phMenu[0], 3, MF_BYPOSITION, IDM_FILECLOSE
            , PSZ(IDS_SAVE));

        //Save Copy As->Save As
        ModifyMenu(m_phMenu[0], IDM_FILESAVEAS, MF_BYCOMMAND
            , IDM_FILESAVEAS, PSZ(IDS_SAVEAS));
        }

    //Change "Exit" to "Exit & Return to xx" or vice-versa for SDI
    if (fEmbedding)
        wsprintf(szTemp, PSZ(IDS_EXITANDRETURN), (LPSTR)pszObj);
    else
        lstrcpy(szTemp, PSZ(IDS_EXIT));

    ModifyMenu(m_phMenu[0], IDM_FILEEXIT, MF_STRING, IDM_FILEEXIT
        , szTemp);
    DrawMenuBar(m_hWnd);

    //Now let's play with the toolbar.
    m_pTB->Show(IDM_FILENEW,   !fEmbedding);
    m_pTB->Show(IDM_FILEOPEN,  !fEmbedding);
    m_pTB->Show(IDM_FILECLOSE, !fEmbedding);
    m_pTB->Show(IDM_FILESAVE,  !fEmbedding);

    //Enable what's left appropriately.
    UpdateToolbar();

    //Now play with the title bar.

    //IDS_EMBEDDINGCAPTION is MDI/SDI sensitive in COSMO.RC.
    wsprintf(szTemp, PSZ(IDS_EMBEDDINGCAPTION), pszObj);

    /*
     * Remember that in MDI situations that Windows takes care of
     * the frame window caption bar when the document is maximized.
     */
   #ifdef MDI
    SetWindowText(pDoc->Window(), szTemp);
   #else
    SetWindowText(m_hWnd, szTemp);
   #endif

    return;
    }
